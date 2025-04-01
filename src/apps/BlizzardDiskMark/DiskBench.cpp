/*---------------------------------------------------------------------------*/
//       Author : hiyohiyo
//         Mail : hiyohiyo@crystalmark.info
//          Web : https://crystalmark.info/
//      License : MIT License
/*---------------------------------------------------------------------------*/

//#include "stdafx.h"
#include "DiskMarkDlg.h"
#include "DiskBench.h"

#ifdef __APPLE__
#include <unistd.h>
#include <mach-o/dyld.h>
#include <sys/statvfs.h>
#include <sys/mount.h>
#include <sys/stat.h>
#elif defined(_WIN32)
#include <windows.h>
#endif
#include <fcntl.h>
#include <limits.h>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QDir>

#pragma warning(disable : 4996)

static QString TestFilePath;
static QString TestFileDir;

//static HANDLE hFile;
static int DiskTestCount;
static uint64_t DiskTestSize;
static int BenchType[9];
static int BenchSize[9];
static int BenchQueues[9];
static int BenchThreads[9];
// static int Affinity;
static bool MixMode;
static int MixRatio;

static void ShowErrorMessage(QString message);
static void Interval(void* dlg);

static bool Init(void* dlg);
static void DiskSpd(void* dlg, DISK_SPD_CMD cmd);

static unsigned int Exit(void* dlg);
//static void CALLBACK TimerProc(int hwnd, unsigned int uMsg, unsigned int* idEvent, int dwTime);
static volatile bool WaitFlag;

int ExecAndWait(QString *pszCmd, double *score, double *latency, double *iops)
{
	int Code = 0;
	QString output;
	char buffer[128];

#ifdef __APPLE__
	int status;
	pid_t pid;
	int pipefd[2];

	if (pipe(pipefd) == -1) {
		perror("pipe");
		return false;
	}

	pid = fork();
	if (pid == -1) {
		perror("fork");
		return -1;
	}

	if (pid == 0) {
		// Child process
		close(pipefd[0]); // Close unused read end

		int fd = open("/dev/null", O_WRONLY);
		if (fd == -1) {
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		dup2(fd, STDERR_FILENO);
		close(fd);

		dup2(pipefd[1], STDOUT_FILENO);
		dup2(pipefd[1], STDERR_FILENO);
		close(pipefd[1]);

		execl("/bin/sh", "sh", "-c", pszCmd->toStdString().c_str(), (char *)NULL);
		perror("execl");
		exit(EXIT_FAILURE);
	} else {
		// Parent process
		close(pipefd[1]); // Close unused write end
		ssize_t count;

		while ((count = read(pipefd[0], buffer, sizeof(buffer))) != 0) {
			if (count == -1) {
				if (errno == EINTR) {
					continue;
				} else {
					perror("read");
					break;
				}
			}
			output.append(QString::fromUtf8(buffer, count));
		}

		close(pipefd[0]);

		waitpid(pid, &status, 0);
		if (WIFEXITED(status)) {
			Code = WEXITSTATUS(status);
		}
	}

#elif defined(_WIN32)
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead, hWrite;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	DWORD exitCode;

	// Set up security attributes
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;

	// Create a pipe for the child process's STDOUT
	if (!CreatePipe(&hRead, &hWrite, &sa, 0)) {
		perror("CreatePipe");
		return -1;
	}

	// Ensure the read handle to the pipe for STDOUT is not inherited
	if (!SetHandleInformation(hRead, HANDLE_FLAG_INHERIT, 0)) {
		perror("SetHandleInformation");
		return -1;
	}

	// Set up members of the STARTUPINFO structure
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.hStdError = hWrite;
	si.hStdOutput = hWrite;
	si.dwFlags |= STARTF_USESTDHANDLES;

	// Set up members of the PROCESS_INFORMATION structure
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	// Create the child process without showing a window
	std::wstring commandW = (*pszCmd).toStdWString();
	if (!CreateProcessW(NULL, (LPWSTR)commandW.c_str(), NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
		perror("CreateProcess");
		return -1;
	}

	// Close the write end of the pipe before reading from the read end of the pipe
	CloseHandle(hWrite);

	// Read output from the child process
	DWORD bytesRead;
	while (ReadFile(hRead, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
		buffer[bytesRead] = '\0';
		output.append(QString::fromUtf8(buffer));
	}

	// Wait until child process exits
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Get the exit code of the child process
	if (!GetExitCodeProcess(pi.hProcess, &exitCode)) {
		perror("GetExitCodeProcess");
		return -1;
	}

	// Close handles
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	CloseHandle(hRead);

	Code = exitCode;
#endif

	// printf("Output: %s\n", output.toStdString().c_str());
	QJsonDocument jsonResponse = QJsonDocument::fromJson(output.toUtf8());
	if (!jsonResponse.isNull()) {
		QJsonObject jsonObject = jsonResponse.object();
		QJsonObject global = jsonObject["global options"].toObject();
		QString rw = global["rw"].toString();
		if (rw.contains("read")) {
			QJsonArray jobs = jsonObject["jobs"].toArray();
			QJsonObject job = jobs[0].toObject();
			QJsonObject read = job["read"].toObject();
			QJsonObject lat_ns = read["lat_ns"].toObject();
			*latency = lat_ns["mean"].toDouble() / 1000.0;
			*score = read["bw_bytes"].toDouble() / 1000.0 / 1000.0;
			*iops = read["iops"].toDouble();
		} else if (rw.contains("write")) {
			QJsonArray jobs = jsonObject["jobs"].toArray();
			QJsonObject job = jobs[0].toObject();
			QJsonObject write = job["write"].toObject();
			QJsonObject lat_ns = write["lat_ns"].toObject();
			*latency = lat_ns["mean"].toDouble() / 1000.0;
			*score = write["bw_bytes"].toDouble() / 1000.0 / 1000.0;
			*iops = write["iops"].toDouble();
		}
	} else {
		if (Code == 0) {
			Code = -1;
			return Code;
		}
	}

	return Code;
}


void ShowErrorMessage(QString message)
{
	// QString errorMessage = QString("Error: %1\n%2").arg(message).arg(strerror(errno));
	// QMetaObject::invokeMethod(QApplication::instance(), [errorMessage]() {
	// 	QMessageBox::critical(nullptr, QObject::tr("Error"), errorMessage);
	// }, Qt::QueuedConnection);
}

void Interval(void* dlg)
{
	int intervalTime = ((CDiskMarkDlg*) dlg)->m_IntervalTime;
	QString title;

	for (int i = 0; i < intervalTime; i++)
	{
		if (!((CDiskMarkDlg*) dlg)->m_DiskBenchStatus)
		{
			return;
		}
		title = QString("Interval Time %1/%2 sec").arg(i).arg(intervalTime);
		//QMetaObject::invokeMethod(((CDiskMarkDlg*) dlg), "OnUpdateMessage", Qt::QueuedConnection, Q_ARG(QString*, &title));
		((CDiskMarkDlg*) dlg)->m_WindowTitle = title;
		((CDiskMarkDlg*) dlg)->m_WindowTitleChanged();
		#ifdef _WIN32
				Sleep(1000); // Sleep for 1000 milliseconds
		#else
				sleep(1); // Sleep for 1 second
		#endif
	}
}

quint64 ExecDiskBenchAll(void* dlg)
{
	int benchmark = ((CDiskMarkDlg*)dlg)->m_Benchmark;

	if(Init(dlg))
	{
		if (benchmark & CDiskMarkDlg::BENCH_READ)
		{
			DiskSpd(dlg, TEST_READ_0); Interval(dlg);
			DiskSpd(dlg, TEST_READ_1); Interval(dlg);
			DiskSpd(dlg, TEST_READ_2); Interval(dlg);
			DiskSpd(dlg, TEST_READ_3);
		}
		if ((benchmark & CDiskMarkDlg::BENCH_READ) && (benchmark & CDiskMarkDlg::BENCH_WRITE))
		{
			Interval(dlg);
		}
		if (benchmark & CDiskMarkDlg::BENCH_WRITE)
		{
			DiskSpd(dlg, TEST_WRITE_0); Interval(dlg);
			DiskSpd(dlg, TEST_WRITE_1); Interval(dlg);
			DiskSpd(dlg, TEST_WRITE_2); Interval(dlg);
			DiskSpd(dlg, TEST_WRITE_3);
		}

#ifdef MIX_MODE
		if (MixMode)
		{
			Interval(dlg);
			DiskSpd(dlg, TEST_MIX_0); Interval(dlg);
			DiskSpd(dlg, TEST_MIX_1); Interval(dlg);
			DiskSpd(dlg, TEST_MIX_2); Interval(dlg);
			DiskSpd(dlg, TEST_MIX_3); 
		}
#endif
	}

	return Exit(dlg);
}

quint64 ExecDiskBenchAllPeak(void* dlg)
{
	int benchmark = ((CDiskMarkDlg*)dlg)->m_Benchmark;

	if (Init(dlg))
	{
		if (benchmark & CDiskMarkDlg::BENCH_READ)
		{
			DiskSpd(dlg, TEST_READ_4); Interval(dlg);
			DiskSpd(dlg, TEST_READ_5);
		}
		if ((benchmark & CDiskMarkDlg::BENCH_READ) && (benchmark & CDiskMarkDlg::BENCH_WRITE))
		{
			Interval(dlg);
		}
		if (benchmark & CDiskMarkDlg::BENCH_WRITE)
		{
			DiskSpd(dlg, TEST_WRITE_4); Interval(dlg);
			DiskSpd(dlg, TEST_WRITE_5);
		}

#ifdef MIX_MODE
		if (MixMode)
		{
			Interval(dlg);
			DiskSpd(dlg, TEST_MIX_4); Interval(dlg);
			DiskSpd(dlg, TEST_MIX_5);
		}
#endif
	}

	return Exit(dlg);
}

quint64 ExecDiskBenchAllReal(void* dlg)
{
	int benchmark = ((CDiskMarkDlg*)dlg)->m_Benchmark;

	if (Init(dlg))
	{
		if (benchmark & CDiskMarkDlg::BENCH_READ)
		{
			DiskSpd(dlg, TEST_READ_6); Interval(dlg);
			DiskSpd(dlg, TEST_READ_7);
		}
		if ((benchmark & CDiskMarkDlg::BENCH_READ) && (benchmark & CDiskMarkDlg::BENCH_WRITE))
		{
			Interval(dlg);
		}
		if (benchmark & CDiskMarkDlg::BENCH_WRITE)
		{
			DiskSpd(dlg, TEST_WRITE_6); Interval(dlg);
			DiskSpd(dlg, TEST_WRITE_7);
		}

#ifdef MIX_MODE
		if (MixMode)
		{
			Interval(dlg);
			DiskSpd(dlg, TEST_MIX_6); Interval(dlg);
			DiskSpd(dlg, TEST_MIX_7);
		}
#endif
	}

	return Exit(dlg);
}

quint64 ExecDiskBenchAllDemo(void* dlg)
{
	int benchmark = ((CDiskMarkDlg*)dlg)->m_Benchmark;

	if (Init(dlg))
	{
		if (benchmark & CDiskMarkDlg::BENCH_READ)
		{
			DiskSpd(dlg, TEST_READ_8);
		}
		if ((benchmark & CDiskMarkDlg::BENCH_READ) && (benchmark & CDiskMarkDlg::BENCH_WRITE))
		{
			Interval(dlg);
		}
		if (benchmark & CDiskMarkDlg::BENCH_WRITE)
		{
			DiskSpd(dlg, TEST_WRITE_8);
		}
	}

	return Exit(dlg);
}

quint64 ExecDiskBench0(void* dlg)
{
	int benchmark = ((CDiskMarkDlg*)dlg)->m_Benchmark;

	if (Init(dlg))
	{
		if (benchmark & CDiskMarkDlg::BENCH_READ)
		{
			DiskSpd(dlg, TEST_READ_0);
		}
		if ((benchmark & CDiskMarkDlg::BENCH_READ) && (benchmark & CDiskMarkDlg::BENCH_WRITE))
		{
			Interval(dlg);
		}
		if (benchmark & CDiskMarkDlg::BENCH_WRITE)
		{
			DiskSpd(dlg, TEST_WRITE_0);
		}

#ifdef MIX_MODE
		if (MixMode)
		{
			Interval(dlg);
			DiskSpd(dlg, TEST_MIX_0);
		}
#endif
	}
	return Exit(dlg);
}

quint64 ExecDiskBench1(void* dlg)
{
	int benchmark = ((CDiskMarkDlg*)dlg)->m_Benchmark;

	if (Init(dlg))
	{
		if (benchmark & CDiskMarkDlg::BENCH_READ)
		{
			DiskSpd(dlg, TEST_READ_1);
		}
		if ((benchmark & CDiskMarkDlg::BENCH_READ) && (benchmark & CDiskMarkDlg::BENCH_WRITE))
		{
			Interval(dlg);
		}
		if (benchmark & CDiskMarkDlg::BENCH_WRITE)
		{
			DiskSpd(dlg, TEST_WRITE_1);
		}
#ifdef MIX_MODE
		if (MixMode)
		{
			Interval(dlg);
			DiskSpd(dlg, TEST_MIX_1);
		}
#endif
	}
	return Exit(dlg);
}

quint64 ExecDiskBench2(void* dlg)
{
	int benchmark = ((CDiskMarkDlg*)dlg)->m_Benchmark;

	if (Init(dlg))
	{
		if (benchmark & CDiskMarkDlg::BENCH_READ)
		{
			DiskSpd(dlg, TEST_READ_2);
		}
		if ((benchmark & CDiskMarkDlg::BENCH_READ) && (benchmark & CDiskMarkDlg::BENCH_WRITE))
		{
			Interval(dlg);
		}
		if (benchmark & CDiskMarkDlg::BENCH_WRITE)
		{
			DiskSpd(dlg, TEST_WRITE_2);
		}
#ifdef MIX_MODE
		if (MixMode)
		{
			Interval(dlg);
			DiskSpd(dlg, TEST_MIX_2);
		}
#endif
	}
	return Exit(dlg);
}

quint64 ExecDiskBench3(void* dlg)
{
	int benchmark = ((CDiskMarkDlg*)dlg)->m_Benchmark;

	if (Init(dlg))
	{
		if (benchmark & CDiskMarkDlg::BENCH_READ)
		{
			DiskSpd(dlg, TEST_READ_3);
		}
		if ((benchmark & CDiskMarkDlg::BENCH_READ) && (benchmark & CDiskMarkDlg::BENCH_WRITE))
		{
			Interval(dlg);
		}
		if (benchmark & CDiskMarkDlg::BENCH_WRITE)
		{
			DiskSpd(dlg, TEST_WRITE_3);
		}
#ifdef MIX_MODE
		if (MixMode)
		{
			Interval(dlg);
			DiskSpd(dlg, TEST_MIX_3);
		}
#endif
	}
	return Exit(dlg);
}

quint64 ExecDiskBench4(void* dlg)
{
	int benchmark = ((CDiskMarkDlg*)dlg)->m_Benchmark;

	if (Init(dlg))
	{
		if (benchmark & CDiskMarkDlg::BENCH_READ)
		{
			DiskSpd(dlg, TEST_READ_4);
		}
		if ((benchmark & CDiskMarkDlg::BENCH_READ) && (benchmark & CDiskMarkDlg::BENCH_WRITE))
		{
			Interval(dlg);
		}
		if (benchmark & CDiskMarkDlg::BENCH_WRITE)
		{
			DiskSpd(dlg, TEST_WRITE_4);
		}
#ifdef MIX_MODE
		if (MixMode)
		{
			Interval(dlg);
			DiskSpd(dlg, TEST_MIX_4);
		}
#endif
	}
	return Exit(dlg);
}

quint64 ExecDiskBench5(void* dlg)
{
	int benchmark = ((CDiskMarkDlg*)dlg)->m_Benchmark;

	if (Init(dlg))
	{
		if (benchmark & CDiskMarkDlg::BENCH_READ)
		{
			DiskSpd(dlg, TEST_READ_5);
		}
		if ((benchmark & CDiskMarkDlg::BENCH_READ) && (benchmark & CDiskMarkDlg::BENCH_WRITE))
		{
			Interval(dlg);
		}
		if (benchmark & CDiskMarkDlg::BENCH_WRITE)
		{
			DiskSpd(dlg, TEST_WRITE_5);
		}
#ifdef MIX_MODE
		if (MixMode)
		{
			Interval(dlg);
			DiskSpd(dlg, TEST_MIX_5);
		}
#endif
	}
	return Exit(dlg);
}

quint64 ExecDiskBench6(void* dlg)
{
	int benchmark = ((CDiskMarkDlg*)dlg)->m_Benchmark;

	if (Init(dlg))
	{
		if (benchmark & CDiskMarkDlg::BENCH_READ)
		{
			DiskSpd(dlg, TEST_READ_6);
		}
		if ((benchmark & CDiskMarkDlg::BENCH_READ) && (benchmark & CDiskMarkDlg::BENCH_WRITE))
		{
			Interval(dlg);
		}
		if (benchmark & CDiskMarkDlg::BENCH_WRITE)
		{
			DiskSpd(dlg, TEST_WRITE_6);
		}
#ifdef MIX_MODE
		if (MixMode)
		{
			Interval(dlg);
			DiskSpd(dlg, TEST_MIX_6);
		}
#endif
	}
	return Exit(dlg);
}

quint64 ExecDiskBench7(void* dlg)
{
	int benchmark = ((CDiskMarkDlg*)dlg)->m_Benchmark;

	if (Init(dlg))
	{
		if (benchmark & CDiskMarkDlg::BENCH_READ)
		{
			DiskSpd(dlg, TEST_READ_7);
		}
		if ((benchmark & CDiskMarkDlg::BENCH_READ) && (benchmark & CDiskMarkDlg::BENCH_WRITE))
		{
			Interval(dlg);
		}
		if (benchmark & CDiskMarkDlg::BENCH_WRITE)
		{
			DiskSpd(dlg, TEST_WRITE_7);
		}
#ifdef MIX_MODE
		if (MixMode)
		{
			Interval(dlg);
			DiskSpd(dlg, TEST_MIX_7);
		}
#endif
	}
	return Exit(dlg);
}

bool Init(void* dlg)
{
	bool FlagArc;
	bool result;
	static QString cstr;
	QString drive;

	// quint64 freeBytesAvailableToCaller;
	// quint64 totalNumberOfBytes;
	// quint64 totalNumberOfFreeBytes;

	// // Get Current Path of Executable
	// char temp[PATH_MAX];
	// uint32_t size = sizeof(temp);
	// if (_NSGetExecutablePath(temp, &size) != 0) {
	// 	perror("_NSGetExecutablePath");
	// 	return false;
	// }
	// char *ptrEnd = strrchr(temp, '/');
	// if (ptrEnd != NULL) {
	// 	*ptrEnd = '\0';
	// }

	DiskTestCount = ((CDiskMarkDlg*) dlg)->m_IndexTestCount + 1;
	
	QString testSize = ((CDiskMarkDlg*)dlg)->m_ValueTestSize;
	if (!testSize.contains("M")) // GiB
	{
		DiskTestSize = (uint64_t)testSize.remove("GiB").toInt() * 1024;
	}
	else // MiB
	{
		DiskTestSize = (uint64_t)testSize.remove("MiB").toInt();
	}

	for (int i = 0; i < 9; i++)
	{
		BenchType[i] = ((CDiskMarkDlg*)dlg)->m_BenchType[i];
		BenchSize[i] = ((CDiskMarkDlg*)dlg)->m_BenchSize[i];
		BenchQueues[i] = ((CDiskMarkDlg*)dlg)->m_BenchQueues[i];
		BenchThreads[i] = ((CDiskMarkDlg*)dlg)->m_BenchThreads[i];
	}

	MixMode = ((CDiskMarkDlg*)dlg)->m_MixMode;
	MixRatio = ((CDiskMarkDlg*)dlg)->m_MixRatio;

	QString RootPath, TempPath;
	// If not Select Folder
	if(((CDiskMarkDlg*)dlg)->m_MaxIndexTestDrive != ((CDiskMarkDlg*)dlg)->m_IndexTestDrive)
	{
		drive = ((CDiskMarkDlg*)dlg)->m_ValueTestDrive.at(0);
#ifdef __APPLE__
		cstr = QString("/Volumes/%1").arg(drive);
		struct statvfs stat;
		if (statvfs(cstr.toStdString().c_str(), &stat) != 0) {
			perror("statvfs");
			return false;
		}
		quint64 freeBytesAvailableToCaller = stat.f_bavail * stat.f_frsize;
		quint64 totalNumberOfBytes = stat.f_blocks * stat.f_frsize;
		quint64 totalNumberOfFreeBytes = stat.f_bfree * stat.f_frsize;
		if (totalNumberOfBytes < ((quint64)8 * 1024 * 1024 * 1024)) // < 8 GB
		{
			((CDiskMarkDlg*)dlg)->m_TestDriveInfo = QString("%1: %2.1f%% (%3.1f/%4.1f MiB)")
				.arg(drive)
				.arg((double)(totalNumberOfBytes - totalNumberOfFreeBytes) / (double)totalNumberOfBytes * 100)
				.arg((totalNumberOfBytes - totalNumberOfFreeBytes) / 1024 / 1024.0)
				.arg(totalNumberOfBytes / 1024 / 1024.0);
		}
		else
		{
			((CDiskMarkDlg*)dlg)->m_TestDriveInfo = QString("%1: %2.1f%% (%3.1f/%4.1f GiB)")
				.arg(drive)
				.arg((double)(totalNumberOfBytes - totalNumberOfFreeBytes) / (double)totalNumberOfBytes * 100)
				.arg((totalNumberOfBytes - totalNumberOfFreeBytes) / 1024 / 1024 / 1024.0)
				.arg(totalNumberOfBytes / 1024 / 1024 / 1024.0);
		}
		RootPath = QString("/Volumes/%1").arg(drive);
		RootPath = QDir().tempPath();
#elif defined(_WIN32)
		cstr = QString("%1:\\").arg(drive);
		ULARGE_INTEGER freeBytesAvailableToCaller;
		ULARGE_INTEGER totalNumberOfBytes;
		ULARGE_INTEGER totalNumberOfFreeBytes;
		if (GetDiskFreeSpaceEx(cstr.toStdWString().c_str(), &freeBytesAvailableToCaller, &totalNumberOfBytes, &totalNumberOfFreeBytes) == 0) {
			perror("GetDiskFreeSpaceEx");
			return false;
		}
		if (totalNumberOfBytes.QuadPart < ((quint64)8 * 1024 * 1024 * 1024)) // < 8 GB
		{
			((CDiskMarkDlg*)dlg)->m_TestDriveInfo = QString("%1: %2.1f%% (%3.1f/%4.1f MiB)")
				.arg(drive)
				.arg((double)(totalNumberOfBytes.QuadPart - totalNumberOfFreeBytes.QuadPart) / (double)totalNumberOfBytes.QuadPart * 100)
				.arg((totalNumberOfBytes.QuadPart - totalNumberOfFreeBytes.QuadPart) / 1024 / 1024.0)
				.arg(totalNumberOfBytes.QuadPart / 1024 / 1024.0);
		}
		else
		{
			((CDiskMarkDlg*)dlg)->m_TestDriveInfo = QString("%1: %2.1f%% (%3.1f/%4.1f GiB)")
				.arg(drive)
				.arg((double)(totalNumberOfBytes.QuadPart - totalNumberOfFreeBytes.QuadPart) / (double)totalNumberOfBytes.QuadPart * 100)
				.arg((totalNumberOfBytes.QuadPart - totalNumberOfFreeBytes.QuadPart) / 1024 / 1024 / 1024.0)
				.arg(totalNumberOfBytes.QuadPart / 1024 / 1024 / 1024.0);
		}
		RootPath = QString("%1:\\").arg(drive);
#endif
		TestFileDir = QString("%1/BlizzardDiskMark%2").arg(RootPath).arg(QDateTime::currentMSecsSinceEpoch(), 8, 16, QChar('0'));
	}
	else
	{
		RootPath = ((CDiskMarkDlg*)dlg)->m_TestTargetPath;
		TestFileDir = QString("%1/BlizzardDiskMark%2").arg(RootPath).arg(QDateTime::currentMSecsSinceEpoch(), 8, 16, QChar('0'));
	}
	printf("Test path %s", TestFileDir.toStdString().c_str());
#ifdef __APPLE__
	if (mkdir(TestFileDir.toStdString().c_str(), 0777) != 0) {
		perror("mkdir");
		return false;
	}
#elif defined(_WIN32)
	if (!CreateDirectory(TestFileDir.toStdWString().c_str(), NULL)) {
		perror("CreateDirectory");
		return false;
	}
#endif
	TestFilePath = QString("%1/BlizzardDiskMark%2.tmp").arg(TestFileDir).arg(QDateTime::currentMSecsSinceEpoch(), 8, 16, QChar('0'));

#ifdef __APPLE__
	// Check Read Only //
	struct statfs fsInfo;
	if (statfs(RootPath.toStdString().c_str(), &fsInfo) == 0) {
		FlagArc = (fsInfo.f_flags & ST_RDONLY) != 0;
	} else {
		perror("statfs");
		FlagArc = false;
	}
	// Check Disk Capacity //
	struct statvfs stat;
	if (statvfs(RootPath.toStdString().c_str(), &stat) != 0) {
		perror("statvfs");
		return false;
	}
	quint64 freeBytesAvailableToCaller = stat.f_bavail * stat.f_frsize;
	quint64 totalNumberOfBytes = stat.f_blocks * stat.f_frsize;
	quint64 totalNumberOfFreeBytes = stat.f_bfree * stat.f_frsize;
	if(DiskTestSize > totalNumberOfFreeBytes / 1024 / 1024 )
	{
		ShowErrorMessage(((CDiskMarkDlg*)dlg)->m_MesDiskCapacityError);
		((CDiskMarkDlg*)dlg)->m_DiskBenchStatus = false;
		return false;
	}
#elif defined(_WIN32)
	// Check Read Only //
	DWORD dwAttributes = GetFileAttributes(RootPath.toStdWString().c_str());
	FlagArc = (dwAttributes & FILE_ATTRIBUTE_READONLY) != 0;
	// Check Disk Capacity //
	ULARGE_INTEGER freeBytesAvailableToCaller;
	ULARGE_INTEGER totalNumberOfBytes;
	ULARGE_INTEGER totalNumberOfFreeBytes;
	if (GetDiskFreeSpaceEx(RootPath.toStdWString().c_str(), &freeBytesAvailableToCaller, &totalNumberOfBytes, &totalNumberOfFreeBytes) == 0) {
		perror("GetDiskFreeSpaceEx");
		return false;
	}
	if(DiskTestSize > totalNumberOfFreeBytes.QuadPart / 1024 / 1024 )
	{
		ShowErrorMessage(((CDiskMarkDlg*)dlg)->m_MesDiskCapacityError);
		((CDiskMarkDlg*)dlg)->m_DiskBenchStatus = false;
		return false;
	}
#endif

	QString title;
	title = QString::asprintf("Preparing... Create Test File");
	// QMetaObject::invokeMethod(((CDiskMarkDlg*)dlg), "OnUpdateMessage", Qt::QueuedConnection, Q_ARG(QString*, &title));
	((CDiskMarkDlg*)dlg)->m_WindowTitle = title;
	((CDiskMarkDlg*)dlg)->m_WindowTitleChanged();

#ifdef __APPLE__
	// Prepare Test File
	int status;
	pid_t pid;
	int pipefd[2];

	if (pipe(pipefd) == -1) {
		perror("pipe");
		return -1;
	}

	pid = fork();
	if (pid == -1) {
		perror("fork");
		return -1;
	}

	if (pid == 0) {
		// Child process
		close(pipefd[0]); // Close unused read end

		int fd = open("/dev/null", O_WRONLY);
		if (fd == -1) {
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		dup2(fd, STDERR_FILENO);
		close(fd);

		dup2(pipefd[1], STDOUT_FILENO);
		dup2(pipefd[1], STDERR_FILENO);
		close(pipefd[1]);

		execlp("fio", "fio", 
			("--name=" + TestFilePath.toStdString()).c_str(), 
			"--kb_base=1000",
			("--size=" + std::to_string(DiskTestSize) + "Mi").c_str(), 
			"--create_only=1", 
			"--rw=write", 
			(char *)NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	} else {
		// Parent process
		close(pipefd[1]); // Close unused write end

		char buffer[128];
		ssize_t count;
		QString output;

		while ((count = read(pipefd[0], buffer, sizeof(buffer))) != 0) {
			if (count == -1) {
				if (errno == EINTR) {
					continue;
				} else {
					perror("read");
					break;
				}
			}
			output.append(QString::fromUtf8(buffer, count));
		}

		close(pipefd[0]);

		waitpid(pid, &status, 0);
		if (WIFEXITED(status)) {
			printf("Exit status: %d\n", WEXITSTATUS(status));
			// perror(std::to_string(WEXITSTATUS(status)).c_str());
		}

		// printf("Output: %s\n", output.toStdString().c_str());
	}
#elif defined(_WIN32)
	// Prepare Test File
	QString command = QString("fio --name=%1 --kb_base=1000 --size=%2Mi --create_only=1 --rw=write --thread").arg(TestFilePath).arg(DiskTestSize);
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead, hWrite;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	DWORD exitCode;

	// Set up security attributes
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;

	// Create a pipe for the child process's STDOUT
	if (!CreatePipe(&hRead, &hWrite, &sa, 0)) {
		perror("CreatePipe");
		return -1;
	}

	// Ensure the read handle to the pipe for STDOUT is not inherited
	if (!SetHandleInformation(hRead, HANDLE_FLAG_INHERIT, 0)) {
		perror("SetHandleInformation");
		return -1;
	}

	// Set up members of the STARTUPINFO structure
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.hStdError = hWrite;
	si.hStdOutput = hWrite;
	si.dwFlags |= STARTF_USESTDHANDLES;

	// Set up members of the PROCESS_INFORMATION structure
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	// Create the child process
	std::wstring commandW = command.toStdWString();
	if (!CreateProcessW(NULL, (LPWSTR)commandW.c_str(), NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
		DWORD error = GetLastError();
		LPVOID lpMsgBuf;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			error,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0, NULL);
		// fprintf(stderr, "CreateProcess failed with error %d: %s\n", error, (wchar_t*)lpMsgBuf);
		LocalFree(lpMsgBuf);
		return false;
	}

	// Close the write end of the pipe before reading from the read end of the pipe
	CloseHandle(hWrite);

	// Read output from the child process
	DWORD bytesRead;
	QString output;
	char buffer[128];
	while (ReadFile(hRead, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
		buffer[bytesRead] = '\0';
		output.append(QString::fromUtf8(buffer));
	}

	// Wait until child process exits
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Get the exit code of the child process
	if (!GetExitCodeProcess(pi.hProcess, &exitCode)) {
		perror("GetExitCodeProcess");
		return -1;
	}

	// Close handles
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	CloseHandle(hRead);

	// printf("Output: %s\n", output.toStdString().c_str());
#endif

	// printf("TestFilePath: %s\n", TestFilePath.toStdString().c_str());
// 	int hFile = open(TestFilePath.toStdString().c_str(), O_CREAT | O_RDWR, 0666);
// 	if (hFile == -1)
// 	{
// 		perror("open");
// 		((CDiskMarkDlg*)dlg)->m_DiskBenchStatus = false;
// 		return false;
// 	}

// // Set End Of File to prevent fragmentation of test file
// 	if (ftruncate(hFile, 1024 * 1024 * DiskTestSize) == -1) {
// 		perror("ftruncate");
// 		close(hFile);
// 		((CDiskMarkDlg*)dlg)->m_DiskBenchStatus = false;
// 		return false;
// 	}
// 	lseek(hFile, 0, SEEK_SET);

// // COMPRESSION_FORMAT_NONE
// 	// USHORT lpInBuffer = COMPRESSION_FORMAT_NONE;
// 	// DWORD lpBytesReturned = 0;
// 	// DeviceIoControl(hFile, FSCTL_SET_COMPRESSION, (LPVOID) &lpInBuffer,
// 	// 			sizeof(USHORT), NULL, 0, (LPDWORD)&lpBytesReturned, NULL);

// // Fill Test Data
// 	char* buf = NULL;
// 	int BufSize;
// 	int Loop;
// 	int i;
// 	ssize_t writesize;
// 	BufSize = 1024 * 1024;
// 	Loop = (int)DiskTestSize;

// 	buf = (char*) malloc(BufSize);
// 	if (buf == NULL)
// 	{
// 		perror("malloc");
// 		((CDiskMarkDlg*) dlg)->m_DiskBenchStatus = false;
// 		close(hFile);
// 		return false;
// 	}

// 	if (((CDiskMarkDlg*) dlg)->m_TestData == CDiskMarkDlg::TEST_DATA_ALL0X00)
// 	{
// 		memset(buf, 0, BufSize);
// 	}
// 	else
// 	{
// 		// Compatible with DiskSpd
// 		for (i = 0; i < BufSize; i++)
// 		{
// 			buf[i] = (char) (rand() % 256);
// 		}
// 	}

// 	for (i = 0; i < Loop; i++)
// 	{
// 		if (((CDiskMarkDlg*) dlg)->m_DiskBenchStatus)
// 		{
// 			writesize = write(hFile, buf, BufSize);
// 			if (writesize == -1)
// 			{
// 				perror("write");
// 				free(buf);
// 				close(hFile);
// 				((CDiskMarkDlg*) dlg)->m_DiskBenchStatus = false;
// 				return false;
// 			}
// 		}
// 		else
// 		{
// 			free(buf);
// 			close(hFile);
// 			((CDiskMarkDlg*) dlg)->m_DiskBenchStatus = false;
// 			return false;
// 		}
// 	}
// 	free(buf);
// 	close(hFile);

	return true;
}

//void CALLBACK TimerProc(int hwnd, unsigned int uMsg, unsigned int* idEvent, int dwTime)
//{
	// if(idEvent == TIMER_ID)
	// {
	// 	WaitFlag = FALSE;
	// 	KillTimer(hwnd, idEvent);
	// }
//}

uint Exit(void* dlg)
{
	if (unlink(TestFilePath.toStdString().c_str()) != 0) {
		perror("unlink");
	}
	QDir dir(TestFileDir);
	if (!dir.removeRecursively()) {
		perror("removeRecursively");
	}
	static QString cstr;
	cstr = "";

	if(((CDiskMarkDlg*)dlg)->m_TestData == CDiskMarkDlg::TEST_DATA_ALL0X00)
	{
		cstr = ALL_0X00_0FILL;
	}
	{
		cstr = ALL_0X00_0FILL;
	}

	// QMetaObject::invokeMethod(((CDiskMarkDlg*)dlg), "OnUpdateMessage", Qt::QueuedConnection, Q_ARG(QString*, &cstr));
	((CDiskMarkDlg*)dlg)->m_WindowTitle = cstr;
	((CDiskMarkDlg*)dlg)->m_WindowTitleChanged();
	QMetaObject::invokeMethod(((CDiskMarkDlg*)dlg), "OnExitBenchmark", Qt::QueuedConnection);

	((CDiskMarkDlg*)dlg)->m_DiskBenchStatus = false;
	((CDiskMarkDlg*)dlg)->m_WinThread = NULL;

	return 0;
}

void DiskSpd(void* dlg, DISK_SPD_CMD cmd)
{
	static QString cstr;
	double *maxScore = NULL;
	double *minLatency = NULL;
	double *maxIops = NULL;
	QString command;
	QString title;
	QString option;
	QString bufOption;

	int duration = 5;
	int index = 0;
	int j = 0;

	if (!((CDiskMarkDlg*) dlg)->m_DiskBenchStatus)
	{
		return;
	}

	if (((CDiskMarkDlg*) dlg)->m_TestData == CDiskMarkDlg::TEST_DATA_ALL0X00)
	{
		bufOption.append(" --zero_buffers");
	}
	else
	{
		switch (cmd)
		{
		case TEST_WRITE_0:
		case TEST_WRITE_1:
		case TEST_WRITE_2:
		case TEST_WRITE_3:
		case TEST_WRITE_4:
		case TEST_WRITE_5:
		case TEST_WRITE_6:
		case TEST_WRITE_7:
		case TEST_WRITE_8:
			index = cmd - TEST_WRITE_0;
			//cstr = QString(" -Z%1K").arg(BenchSize[index]);
			//bufOption += cstr;
			break;
		case TEST_MIX_0:
		case TEST_MIX_1:
		case TEST_MIX_2:
		case TEST_MIX_3:
		case TEST_MIX_4:
		case TEST_MIX_5:
		case TEST_MIX_6:
		case TEST_MIX_7:
		case TEST_MIX_8:
			index = cmd - TEST_MIX_0;
			//cstr = QString(" -Z%1K").arg(BenchSize[index]);
			//bufOption += cstr;
			break;
		}
	}

	switch (cmd)
	{
	case TEST_READ_0:
	case TEST_READ_1:
	case TEST_READ_2:
	case TEST_READ_3:
	case TEST_READ_4:
	case TEST_READ_5:
	case TEST_READ_6:
	case TEST_READ_7:
	case TEST_READ_8:
		index = cmd - TEST_READ_0;
		if (BenchType[index])
		{
			title = QString::asprintf("Random Read");
			option = QString("--bs=%1K --iodepth=%2 --numjobs=%3 --direct=1 --rw=randread").arg(BenchSize[index]).arg(BenchQueues[index]).arg(BenchThreads[index]);
			//option = QString("-b%1K -o%2 -t%3 -W0 -S -w0 -r").arg(BenchSize[index]).arg(BenchQueues[index]).arg(BenchThreads[index]);
		}
		else
		{
			title = QString::asprintf("Sequential Read");
			option = QString("--bs=%1K --iodepth=%2 --numjobs=%3 --startdelay=0 --direct=1 --rw=read").arg(BenchSize[index]).arg(BenchQueues[index]).arg(BenchThreads[index]);
			//option = QString("-b%1K -o%2 -t%3 -W0 -S -w0").arg(BenchSize[index]).arg(BenchQueues[index]).arg(BenchThreads[index]);
		}
		maxScore = ((CDiskMarkDlg*) dlg)->m_ReadScore[index];
		minLatency = ((CDiskMarkDlg*)dlg)->m_ReadLatency[index];
		maxIops = &((CDiskMarkDlg*)dlg)->m_ReadIops[index];
		break;
	case TEST_WRITE_0:
	case TEST_WRITE_1:
	case TEST_WRITE_2:
	case TEST_WRITE_3:
	case TEST_WRITE_4:
	case TEST_WRITE_5:
	case TEST_WRITE_6:
	case TEST_WRITE_7:
	case TEST_WRITE_8:
		index = cmd - TEST_WRITE_0;
		if (BenchType[index])
		{
			title = QString::asprintf("Random Write");
			option = QString("--bs=%1K --iodepth=%2 --numjobs=%3 --direct=1 --rw=randwrite").arg(BenchSize[index]).arg(BenchQueues[index]).arg(BenchThreads[index]);
			//option = QString("-b%1K -o%2 -t%3 -W0 -S -w100 -r").arg(BenchSize[index]).arg(BenchQueues[index]).arg(BenchThreads[index]);
		}
		else
		{
			title = QString::asprintf("Sequential Write");
			option = QString("--bs=%1K --iodepth=%2 --numjobs=%3 --direct=1 --rw=write").arg(BenchSize[index]).arg(BenchQueues[index]).arg(BenchThreads[index]);
			//option = QString("-b%1K -o%2 -t%3 -W0 -S -w100").arg(BenchSize[index]).arg(BenchQueues[index]).arg(BenchThreads[index]);
		}
		option += bufOption;
		maxScore = ((CDiskMarkDlg*)dlg)->m_WriteScore[index];
		minLatency = ((CDiskMarkDlg*)dlg)->m_WriteLatency[index];
		maxIops = &((CDiskMarkDlg*)dlg)->m_WriteIops[index];
		break;
#ifdef MIX_MODE
	case TEST_MIX_0:
	case TEST_MIX_1:
	case TEST_MIX_2:
	case TEST_MIX_3:
	case TEST_MIX_4:
	case TEST_MIX_5:
	case TEST_MIX_6:
	case TEST_MIX_7:
	case TEST_MIX_8:
		index = cmd - TEST_MIX_0;
		if (BenchType[index])
		{
			title.Format(L"Random Mix");
			option.Format(L"-b%dK -o%d -t%d -W0 -S -w%d -r", BenchSize[index], BenchQueues[index], BenchThreads[index], MixRatio);
		}
		else
		{
			title.Format(L"Sequential Mix");
			option.Format(L"-b%dK -o%d -t%d -W0 -S -w%d", BenchSize[index], BenchQueues[index], BenchThreads[index], MixRatio);
		}
		option += bufOption;
		maxScore = &(((CDiskMarkDlg*)dlg)->m_MixScore[index]);
		minLatency = &(((CDiskMarkDlg*)dlg)->m_MixLatency[index]);
		break;
#endif
	}
	//option += QStringLiteral(" --cpus_allowed_policy=shared");

#ifdef __APPLE__
	option += QStringLiteral(" --ioengine=posixaio --output-format=json+");
#elif defined(_WIN32)
	option += QStringLiteral(" --ioengine=windowsaio --thread --output-format=json+");
#endif

	double score = 0.0;
	double latency = 0.0;
	double iops = 0.0;

	if (maxScore == NULL || minLatency == NULL || maxIops == NULL)
	{
		return ;
	}
	*maxScore = 0.0;
	*minLatency = -1.0;
	*maxIops = 0.0;

	for (j = 0; j < DiskTestCount; j++)
	{
		if (j == 0)
		{
			duration = 5;
			cstr = QString("Preparing... %1").arg(title);
		}
		else
		{
			duration = ((CDiskMarkDlg*)dlg)->m_MeasureTime;
			cstr = QString::asprintf("%s (%d/%d)", title.toStdString().c_str(), j, DiskTestCount);
		}
		// QMetaObject::invokeMethod(static_cast<CDiskMarkDlg*>(dlg), "OnUpdateMessage", Qt::QueuedConnection, Q_ARG(QString*, &cstr));
		((CDiskMarkDlg*)dlg)->m_WindowTitle = cstr;
		((CDiskMarkDlg*)dlg)->m_WindowTitleChanged();
		
		//command = QString::asprintf("\"%s\" %s -d%d -A%d -L \"%s\"", DiskSpdExe.toStdString().c_str(), option.toStdString().c_str(), duration, getpid(), TestFilePath.toStdString().c_str());
		command = QString::asprintf("%s %s --name=%s --kb_base=1000 --size=%lldMi", "fio", option.toStdString().c_str(), TestFilePath.toStdString().c_str(), DiskTestSize);
		int ret = ExecAndWait(&command, &score, &latency, &iops);
		if (ret != 0)
		{
			ShowErrorMessage(command);
			return;
		}

		if (score > *maxScore)
		{
			*maxScore = score;
			QMetaObject::invokeMethod(((CDiskMarkDlg*)dlg), "OnUpdateScore", Qt::QueuedConnection);
		}

		if (score > 0.0 && (latency < *minLatency || *minLatency < 0))
		{
			*minLatency = latency;
			QMetaObject::invokeMethod(((CDiskMarkDlg*)dlg), "OnUpdateScore", Qt::QueuedConnection);
		}

		if (iops > *maxIops)
		{
			*maxIops = iops;
			QMetaObject::invokeMethod(((CDiskMarkDlg*)dlg), "OnUpdateScore", Qt::QueuedConnection);
		}

		if (!((CDiskMarkDlg*) dlg)->m_DiskBenchStatus)
		{
			return;
		}
	}
	QMetaObject::invokeMethod(((CDiskMarkDlg*)dlg), "OnUpdateScore", Qt::QueuedConnection);
}
