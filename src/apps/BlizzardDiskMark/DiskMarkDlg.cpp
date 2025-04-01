/*---------------------------------------------------------------------------*/
//       Author : hiyohiyo
//         Mail : hiyohiyo@crystalmark.info
//          Web : https://crystalmark.info/
//      License : MIT License
/*---------------------------------------------------------------------------*/

#include "DiskMarkDlg.h"
#include "DiskBench.h"
#include "../../lib/stdafx.h"

#include <math.h>
#include <QApplication>
#include <QWidget>
#include <QWindow>
#include <QScreen>
#include <QMainWindow>
#include <QMenuBar>
#include <QLayout>
#include <QCloseEvent>
#include <QShowEvent>
#include <QFileInfoList>
#include <QDir>
#include <QStorageInfo>
#include <QFileDialog>

#define SIZE_X_MIX	680
#define MAX_METER_LENGTH	192

CDiskMarkDlg::CDiskMarkDlg(QObject* parent)
	: QObject(parent)
{
	m_ReadScore = QVector<double*>(9, nullptr);
	m_WriteScore = QVector<double*>(9, nullptr);
	m_ReadLatency = QVector<double*>(9, nullptr);
	m_WriteLatency = QVector<double*>(9, nullptr);
	for (int i = 0; i < m_ReadScore.size(); ++i) {
		m_ReadScore[i] = new double(0.0);
	}
	for (int i = 0; i < m_WriteScore.size(); ++i) {
		m_WriteScore[i] = new double(0.0);
	}
	for (int i = 0; i < m_ReadLatency.size(); ++i) {
		m_ReadLatency[i] = new double(0.0);
	}
	for (int i = 0; i < m_WriteLatency.size(); ++i) {
		m_WriteLatency[i] = new double(0.0);
	}

	m_BenchType = QVector<int*>(9, nullptr);
	for (int i = 0; i < m_BenchType.size(); ++i) {
		m_BenchType[i] = new int(0);
	}

	m_IndexTestCount = 4;
	m_DriveList = QStringList();
	m_buttonTextList = QStringList();
	m_buttonToolTipList = QStringList();

	m_WinThread = NULL;
	m_DiskBenchStatus = false;

	if (BENCH_READ > m_Benchmark || m_Benchmark > BENCH_READ_WRITE)
	{
		m_Benchmark = BENCH_READ_WRITE;
	}

	m_SizeX = 480;
	m_SizeY = 300;

	ChangeLang();

	// Drive
	InitDrive();
	InitScore();
	
	UpdateQueuesThreads();
	
// #ifdef MIX_MODE
// 	m_ComboMix = new QComboBox(this);
// 	connect(m_ComboMix, SIGNAL(currentIndexChanged(int)), this, SLOT(OnCbnSelchangeComboMix(int)));
// #endif

// 	m_DemoSetting = new QLabel(this);

// 	m_AboutDlg = nullptr;
// 	m_SettingsDlg = nullptr;
}
CDiskMarkDlg::~CDiskMarkDlg()
{
}

bool CDiskMarkDlg::IsDefaultMode()
{
	if (m_BenchSize[0] == 1024 && m_BenchQueues[0] == 8  && m_BenchThreads[0] == 1 && *m_BenchType.at(0) == BENCH_SEQ
	&&  m_BenchSize[1] == 1024 && m_BenchQueues[1] == 1  && m_BenchThreads[1] == 1 && *m_BenchType.at(1) == BENCH_SEQ
	&&  m_BenchSize[2] == 4    && m_BenchQueues[2] == 32 && m_BenchThreads[2] == 1 && *m_BenchType.at(2) == BENCH_RND
	&&  m_BenchSize[3] == 4    && m_BenchQueues[3] == 1  && m_BenchThreads[3] == 1 && *m_BenchType.at(3) == BENCH_RND
	&&  m_BenchSize[4] == 1024 && m_BenchQueues[4] == 8  && m_BenchThreads[4] == 1 && *m_BenchType.at(4) == BENCH_SEQ
	&&  m_BenchSize[5] == 4    && m_BenchQueues[5] == 32 && m_BenchThreads[5] == 1 && *m_BenchType.at(5) == BENCH_RND
	&&  m_BenchSize[8] == 1024 && m_BenchQueues[8] == 8  && m_BenchThreads[8] == 1 && *m_BenchType.at(8) == BENCH_SEQ
	)
	{
		return true;
	}
 return false;
}
bool CDiskMarkDlg::IsNVMe8Mode()
{
	if (m_BenchSize[0] == 1024 && m_BenchQueues[0] == 8  && m_BenchThreads[0] == 1  && *m_BenchType[0] == BENCH_SEQ
	&&  m_BenchSize[1] == 128  && m_BenchQueues[1] == 32 && m_BenchThreads[1] == 1  && *m_BenchType[1] == BENCH_SEQ
	&&  m_BenchSize[2] == 4    && m_BenchQueues[2] == 32 && m_BenchThreads[2] == 16 && *m_BenchType[2] == BENCH_RND
	&&  m_BenchSize[3] == 4    && m_BenchQueues[3] == 1  && m_BenchThreads[3] == 1  && *m_BenchType[3] == BENCH_RND
	&&  m_BenchSize[4] == 1024 && m_BenchQueues[4] == 8  && m_BenchThreads[4] == 1  && *m_BenchType[4] == BENCH_SEQ
	&&  m_BenchSize[5] == 4    && m_BenchQueues[5] == 32 && m_BenchThreads[5] == 16 && *m_BenchType[5] == BENCH_RND
	&&  m_BenchSize[8] == 1024 && m_BenchQueues[8] == 8  && m_BenchThreads[8] == 1  && *m_BenchType[8] == BENCH_SEQ
	)
	{
		return true;
	}
	return false;
}
/*
BOOL CDiskMarkDlg::IsNVMe9Mode()
{
	if (m_BenchSize[0] == 1024 && m_BenchQueues[0] == 8  && m_BenchThreads[0] == 4  && m_BenchType[0] == BENCH_SEQ
	&&  m_BenchSize[1] == 128  && m_BenchQueues[1] == 32 && m_BenchThreads[1] == 4  && m_BenchType[1] == BENCH_SEQ
	&&  m_BenchSize[2] == 4    && m_BenchQueues[2] == 32 && m_BenchThreads[2] == 16 && m_BenchType[2] == BENCH_RND
	&&  m_BenchSize[3] == 4    && m_BenchQueues[3] == 1  && m_BenchThreads[3] == 1  && m_BenchType[3] == BENCH_RND
	&&  m_BenchSize[4] == 1024 && m_BenchQueues[4] == 8  && m_BenchThreads[4] == 4  && m_BenchType[4] == BENCH_SEQ
	&&  m_BenchSize[5] == 4    && m_BenchQueues[5] == 32 && m_BenchThreads[5] == 16 && m_BenchType[5] == BENCH_RND
	&&  m_BenchSize[8] == 1024 && m_BenchQueues[8] == 8  && m_BenchThreads[8] == 4  && m_BenchType[8] == BENCH_SEQ
	)
	{
		return TRUE;
	}
	return FALSE;
}
*/

void CDiskMarkDlg::UpdateQueuesThreads()
{
	int type[9] =   {    0,    0,  1, 1,    0,  1,    0, 1,    0 };
	int size[9] =   { 1024, 1024,  4, 4, 1024,  4, 1024, 4, 1024 };
	int queues[9] = {    8,    1, 32, 1,    8, 32,    1, 1,    8 };
	int threads[9] ={    1,    1,  1, 1,    1,  1,    1, 1,    1 };
	int measureTimes[5] = { 5, 10, 20, 30, 60 };
	int intervalTimes[10] = { 0, 1, 3, 5, 10, 30, 60, 180, 300, 600 };

	for (int i = 0; i < 9; i++)
	{
		if (*m_BenchType.at(i) < 0 || m_BenchSize[i] > 1) { m_BenchSize[i] = type[i]; }
		if (m_BenchSize[i] <= 0 || m_BenchSize[i] > 8192) { m_BenchSize[i] = size[i]; }
		if (m_BenchQueues[i] <= 0 || m_BenchQueues[i] > MAX_QUEUES) { m_BenchQueues[i] = queues[i]; }
		if (m_BenchThreads[i] <= 0 || m_BenchThreads[i] > MAX_THREADS) { m_BenchThreads[i] = threads[i]; }
	}
	if (m_TestData < 0 || m_TestData > 1)
	{
		m_TestData = TEST_DATA_RANDOM;
	}

	bool bMeasureflag = false;
	for (int i = 0; i < 5; i++)
	{
		if (m_MeasureTime == measureTimes[i])
		{
			bMeasureflag = true;
		}
	}
	if (! bMeasureflag)
	{
		m_MeasureTime = 5;
	}

	bool bIntervalFlag = false;
	for (int i = 0; i < 10; i++)
	{
		if (m_IntervalTime == intervalTimes[i])
		{
			bIntervalFlag = true;
		}
	}
	if (! bIntervalFlag)
	{
		m_IntervalTime = 5;
	}

	CheckRadioPresetMode();
}
void CDiskMarkDlg::SettingsQueuesThreads(int type)
{
	QString key, value;

	switch (type)
	{
	case 0:// Default
		{
			int type[9] =   {    0,    0,  1, 1,    0,  1,    0, 1,    0 };
			int size[9] =   { 1024, 1024,  4, 4, 1024,  4, 1024, 4, 1024 };
			int queues[9] = {    8,    1, 32, 1,    8, 32,    1, 1,    8 };
			int threads[9] ={    1,    1,  1, 1,    1,  1,    1, 1,    1 };

			for (int i = 0; i < 9; i++)
			{
				key = QString("BenchType%1").arg(i); value = QString::number(type[i]);
				key = QString("BenchSize%1").arg(i); value = QString::number(size[i]);
				key = QString("BenchQueues%1").arg(i); value = QString::number(queues[i]);
				key = QString("BenchThreads%1").arg(i); value = QString::number(threads[i]);
			}
		}
		UpdateQueuesThreads();
		break;
	case 1: // NVMe SSD Ver.8
		{
			int type[9] =    {    0,    0,  1, 1,    0,  1,    0, 1,    0 };
			int size[9] =    { 1024,  128,  4, 4, 1024,  4, 1024, 4, 1024 };
			int queues[9] =  {    8,   32, 32, 1,    8, 32,    1, 1,    8 };
			int threads[9] = {    1,    1, 16, 1,    1, 16,    1, 1,    1 };
			for (int i = 0; i < 9; i++)
			{
				key = QString("BenchType%1").arg(i); value = QString::number(type[i]);
				key = QString("BenchSize%1").arg(i); value = QString::number(size[i]);
				key = QString("BenchQueues%1").arg(i); value = QString::number(queues[i]);
				key = QString("BenchThreads%1").arg(i); value = QString::number(threads[i]);
			}
		}
		UpdateQueuesThreads();
		break;
	/*
	case 2: // NVMe SSD Ver.9
	{
		int type[9] =    {    0,    0,  1, 1,    0,  1,    0, 1,    0 };
		int size[9] =    { 1024,  128,  4, 4, 1024,  4, 1024, 4, 1024 };
		int queues[9] =  {    8,   32, 32, 1,    8, 32,    1, 1,    8 };
		int threads[9] = {    4,    4, 16, 1,    4, 16,    1, 1,    4 };
		for (int i = 0; i < 9; i++)
		{
			key.Format(L"BenchType%d", i); value.Format(L"%d", type[i]);
			key.Format(L"BenchSize%d", i); value.Format(L"%d", size[i]);
			key.Format(L"BenchQueues%d", i); value.Format(L"%d", queues[i]);
			key.Format(L"BenchThreads%d", i); value.Format(L"%d", threads[i]);
		}
	}
		UpdateQueuesThreads();
	break;
	*/
	default:
		OnSettingsQueuesThreads();
		break;
	}
}

void CDiskMarkDlg::InitScore()
{
	for (int i = 0; i < 9; i++)
	{
		*m_ReadScore[i] = 0.0;
		*m_ReadLatency[i] = 0.0;
		*m_WriteScore[i] = 0.0;
		*m_WriteLatency[i] = 0.0;
	}	
}

void CDiskMarkDlg::OnUpdateScore()
{
	m_scoreChanged();
}
void CDiskMarkDlg::OnExit()
{
	OnCancel();
}
void CDiskMarkDlg::OnAbout()
{
}

void CDiskMarkDlg::OnCancel()
{
// 	if (m_WinThread != NULL)
// 	{
// 		AfxMessageBox(m_MesStopBenchmark);
// 		return;
// 	}
	QApplication::quit();
}

void CDiskMarkDlg::OnSequentialPeak()
{
	if (m_WinThread == NULL)
	{
		*m_ReadScore[4] = 0.0;
		*m_WriteScore[4] = 0.0;
		*m_ReadLatency[4] = 0.0;
		*m_WriteLatency[4] = 0.0;
		m_DiskBenchStatus = true;
		m_WinThread = QThread::create([this]() { ExecDiskBench4(this); });
		m_WinThread->start();
		if (m_WinThread == NULL)
		{
			m_DiskBenchStatus = false;
		}
		;
	}
	else
	{
		Stop();
	}
}
void CDiskMarkDlg::OnRandomPeak()
{
	if (m_WinThread == NULL)
	{
		*m_ReadScore[5] = 0.0;
		*m_WriteScore[5] = 0.0;
		*m_ReadLatency[5] = 0.0;
		*m_WriteLatency[5] = 0.0;
		m_DiskBenchStatus = true;
		m_WinThread = QThread::create([this]() { ExecDiskBench5(this); });
		m_WinThread->start();
		if (m_WinThread == NULL)
		{
			m_DiskBenchStatus = false;
		}
		;
	}
	else
	{
		Stop();
	}
}
void CDiskMarkDlg::OnSequentialReal()
{
	if (m_WinThread == NULL)
	{
		*m_ReadScore[6] = 0.0;
		*m_WriteScore[6] = 0.0;
		*m_ReadLatency[6] = 0.0;
		*m_WriteLatency[6] = 0.0;
		m_DiskBenchStatus = true;
		m_WinThread = QThread::create([this]() { ExecDiskBench6(this); });
		m_WinThread->start();
		if (m_WinThread == NULL)
		{
			m_DiskBenchStatus = false;
		}
		;
	}
	else
	{
		Stop();
	}
}
void CDiskMarkDlg::OnRandomReal()
{
	if (m_WinThread == NULL)
	{
		*m_ReadScore[7] = 0.0;
		*m_WriteScore[7] = 0.0;
		*m_ReadLatency[7] = 0.0;
		*m_WriteLatency[7] = 0.0;
		m_DiskBenchStatus = true;
		m_WinThread = QThread::create([this]() { ExecDiskBench7(this); });
		m_WinThread->start();
		if (m_WinThread == NULL)
		{
			m_DiskBenchStatus = false;
		}
		;
	}
	else
	{
		Stop();
	}
}

void CDiskMarkDlg::OnTest0()
{
	if (m_Profile == PROFILE_PEAK || m_Profile == PROFILE_PEAK_MIX)
	{
		OnSequentialPeak();
		return;
	}
	else if (m_Profile == PROFILE_REAL || m_Profile == PROFILE_REAL_MIX)
	{
		OnSequentialReal();
		return;
	}

	if(m_WinThread == NULL)
	{
		*m_ReadScore[0] = 0.0;
		*m_WriteScore[0] = 0.0;
		*m_ReadLatency[0] = 0.0;
		*m_WriteLatency[0] = 0.0;
		m_DiskBenchStatus = true;
		m_WinThread = QThread::create([this]() { ExecDiskBench0(this); });
		m_WinThread->start();
		if(m_WinThread == NULL)
		{
			m_DiskBenchStatus = false;
		}
		;
	}
	else
	{
		Stop();
	}
}
void CDiskMarkDlg::OnTest1()
{
	if (m_Profile == PROFILE_PEAK || m_Profile == PROFILE_PEAK_MIX)
	{
		OnRandomPeak();
		return;
	}
	else if (m_Profile == PROFILE_REAL || m_Profile == PROFILE_REAL_MIX)
	{
		OnRandomReal();
		return;
	}

	if (m_WinThread == NULL)
	{
		*m_ReadScore[1] = 0.0;
		*m_WriteScore[1] = 0.0;
		*m_ReadLatency[1] = 0.0;
		*m_WriteLatency[1] = 0.0;
		m_DiskBenchStatus = true;
		m_WinThread = QThread::create([this]() { ExecDiskBench1(this); });
		m_WinThread->start();
		if (m_WinThread == NULL)
		{
			m_DiskBenchStatus = false;
		}
		;
	}
	else
	{
		Stop();
	}
}
void CDiskMarkDlg::OnTest2()
{
	if (m_Profile == PROFILE_PEAK || m_Profile == PROFILE_PEAK_MIX)
	{
		OnRandomPeak();
		return;
	}
	else if (m_Profile == PROFILE_REAL || m_Profile == PROFILE_REAL_MIX)
	{
		OnRandomReal();
		return;
	}

	if(m_WinThread == NULL)
	{
		*m_ReadScore[2] = 0.0;
		*m_WriteScore[2] = 0.0;
		*m_ReadLatency[2] = 0.0;
		*m_WriteLatency[2] = 0.0;
		m_DiskBenchStatus = true;
		m_WinThread = QThread::create([this]() { ExecDiskBench2(this); });
		m_WinThread->start();
		if(m_WinThread == NULL)
		{
			m_DiskBenchStatus = false;
		}
		;
	}
	else
	{
		Stop();
	}
}
void CDiskMarkDlg::OnTest3()
{
	if (m_Profile == PROFILE_PEAK || m_Profile == PROFILE_PEAK_MIX)
	{
		OnRandomPeak();
		return;
	}
	else if (m_Profile == PROFILE_REAL || m_Profile == PROFILE_REAL_MIX)
	{
		OnRandomReal();
		return;
	}

	if(m_WinThread == NULL)
	{
		*m_ReadScore[3] = 0.0;
		*m_WriteScore[3] = 0.0;
		*m_ReadLatency[3] = 0.0;
		*m_WriteLatency[3] = 0.0;
		m_DiskBenchStatus = true;
		m_WinThread = QThread::create([this]() { ExecDiskBench3(this); });
		m_WinThread->start();
		if(m_WinThread == NULL)
		{
			m_DiskBenchStatus = false;
		}
		;
	}
	else
	{
		Stop();
	}
}

void CDiskMarkDlg::OnAll()
{
	if(m_WinThread == NULL)
	{
		m_DiskBenchStatus = true;
		if (m_Profile == PROFILE_DEMO)
		{
			m_WinThread = QThread::create([this]() { ExecDiskBenchAllDemo(this); });
			m_WinThread->start();
		}
		else if (m_Profile == PROFILE_PEAK || m_Profile == PROFILE_PEAK_MIX)
		{
			m_WinThread = QThread::create([this]() { ExecDiskBenchAllPeak(this); });
			m_WinThread->start();
		}
		else if (m_Profile == PROFILE_REAL || m_Profile == PROFILE_REAL_MIX)
		{
			m_WinThread = QThread::create([this]() { ExecDiskBenchAllReal(this); });
			m_WinThread->start();
		}
		else
		{
			m_WinThread = QThread::create([this]() { ExecDiskBenchAll(this); });
			m_WinThread->start();
		}

		if(m_WinThread == NULL)
		{
			m_DiskBenchStatus = false;
		}
		;
	}
	else
	{
		Stop();
	}
}
void CDiskMarkDlg::Stop()
{
	if(m_DiskBenchStatus)
	{
		m_DiskBenchStatus = false;

		if (m_WinThread != NULL)
		{
			m_WinThread->quit();
			m_WinThread = NULL;
		}
	}
	m_DiskBenchStatusChanged();
}

void CDiskMarkDlg::InitDrive()
{
	m_DriveList.clear();

	QString cstr;
	QString select;

	// list up drive
	QFileInfoList drives = QDir::drives();
	int count = 0;

	m_IndexTestDrive = 0;
	QString testDriveLetter = ""; // Default to empty

	for (const QFileInfo &drive : drives)
	{
		QString drivePath = drive.absoluteFilePath();
		QStorageInfo storage(drivePath);

		if (storage.isValid() && storage.isReady())
		{
			QString displayName = QString("%1: %2% (%3/%4)")
				.arg(drivePath)
				.arg((double)(storage.bytesTotal() - storage.bytesFree()) / (double)storage.bytesTotal() * 100, 0, 'f', 0)
				.arg((storage.bytesTotal() - storage.bytesFree()) / 1024 / 1024.0, 0, 'f', 0)
				.arg(storage.bytesTotal() / 1024 / 1024.0, 0, 'f', 0);

			if (storage.bytesTotal() >= ((quint64)8 * 1024 * 1024 * 1024)) // >= 8 GB
			{
				displayName = QString("%1: %2% (%3/%4 GiB)")
					.arg(drivePath)
					.arg((double)(storage.bytesTotal() - storage.bytesFree()) / (double)storage.bytesTotal() * 100, 0, 'f', 0)
					.arg((storage.bytesTotal() - storage.bytesFree()) / 1024 / 1024 / 1024.0, 0, 'f', 0)
					.arg(storage.bytesTotal() / 1024 / 1024 / 1024.0, 0, 'f', 0);
			}

			select += displayName;

			if (testDriveLetter == drivePath)
			{
				m_IndexTestDrive = count;
			}
			count++;

			m_DriveList.append(displayName);
		}
	}

	m_DriveList.append("Select Folder");

	QString targetPath = ""; // Default to empty
	m_TestTargetPath = targetPath;
	m_MaxIndexTestDrive = count;

	m_DriveListChanged();
	m_TestTargetPathChanged();
}

void CDiskMarkDlg::ChangeLang()
{
	// 	m_MesStopBenchmark = tr("STOP_BENCHMARK");
	// 	m_MesDiskCapacityError = tr("DISK_CAPACITY_ERROR");
	// 	m_MesDiskCreateFileError = tr("DISK_CREATE_FILE_ERROR");
	// 	m_MesDiskWriteError = tr("DISK_WRITE_ERROR");
	// 	m_MesDiskReadError = tr("DISK_READ_ERROR");
	// 	m_MesDiskSpdNotFound = tr("DISK_SPD_NOT_FOUND");
}

void CDiskMarkDlg::OnCopy()
{
	// SaveText("");
}
void CDiskMarkDlg::OnSaveText()
{
	// CString path;
	// SYSTEMTIME st;
	// GetLocalTime(&st);
	// path.Format(L"%s_%04d%02d%02d%02d%02d%02d", PRODUCT_NAME, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	// CString filter = L"TEXT (*.txt)|*.txt||";
	// CFileDialog save(FALSE, L"txt", path, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER, filter);

	// if (save.DoModal() == IDOK)
	// {
	// 	SaveText(save.GetPathName());
	// }
}
void CDiskMarkDlg::OnSaveImage()
{
	// SaveImage();
}

QString CDiskMarkDlg::GetResultString(int type, double score, double latency, int size, int queues, int threads)
{
	QString result;
	double iops = 0.0;

	iops = score * 1000 * 1000 / ((double)size * 1024);
	if (latency < 0.0)
	{
		latency = 0.0;
	}

	if (type == BENCH_RND)
	{
		if (size >= 1024)
		{
			result = QString("  RND %1MiB (Q=%2, T=%3): %4 MB/s [%5 IOPS] <%6 us>")
				.arg(size / 1024)
				.arg(queues)
				.arg(threads)
				.arg(score, 0, 'f', 3)
				.arg(iops, 0, 'f', 1)
				.arg(latency, 0, 'f', 2);
		}
		else
		{
			result = QString("  RND %1KiB (Q=%2, T=%3): %4 MB/s [%5 IOPS] <%6 us>")
				.arg(size)
				.arg(queues)
				.arg(threads)
				.arg(score, 0, 'f', 3)
				.arg(iops, 0, 'f', 1)
				.arg(latency, 0, 'f', 2);
		}
	}
	else
	{
		if (size >= 1024)
		{
			result = QString("  SEQ %1MiB (Q=%2, T=%3): %4 MB/s [%5 IOPS] <%6 us>")
				.arg(size / 1024)
				.arg(queues)
				.arg(threads)
				.arg(score, 0, 'f', 3)
				.arg(iops, 0, 'f', 1)
				.arg(latency, 0, 'f', 2);
		}
		else
		{
			result = QString("  SEQ %1KiB (Q=%2, T=%3): %4 MB/s [%5 IOPS] <%6 us>")
				.arg(size)
				.arg(queues)
				.arg(threads)
				.arg(score, 0, 'f', 3)
				.arg(iops, 0, 'f', 1)
				.arg(latency, 0, 'f', 2);
		}
	}

	return result;
}
void CDiskMarkDlg::SaveText(QString fileName)
{
// 	CString cstr, clip;

// 	UpdateData(TRUE);

// 	if (m_Profile == PROFILE_DEMO)
// 	{
// 		clip = L"\
// ------------------------------------------------------------------------------\r\n\
// %PRODUCT% %VERSION%%EDITION% (C) %COPY_YEAR% hiyohiyo\r\n\
//                                   Crystal Dew World: https://crystalmark.info/\r\n\
// ------------------------------------------------------------------------------\r\n\
// * MB/s = 1,000,000 bytes/s [SATA/600 = 600,000,000 bytes/s]\r\n\
// * KB = 1000 bytes, KiB = 1024 bytes\r\n\
// \r\n\
// [Read]\r\n\
// %BenchRead1%\r\n\
// \r\n\
// [Write]\r\n\
// %BenchWrite1%\r\n\
// \r\n\
// Profile: Demo\r\n\
//    Test: %TestSize% (x%TestCount%)%Capacity%\r\n\
//    Mode:%TestMode%\r\n\
//    Time: Measure %MeasureTime% / Interval %IntervalTime% \r\n\
//    Date: %Date%\r\n\
//      OS: %OS%\r\n\
// %Comment%";
// 	}
// 	else if (m_Profile == PROFILE_DEFAULT || m_Profile == PROFILE_DEFAULT_MIX)
// 	{
// 		clip = L"\
// ------------------------------------------------------------------------------\r\n\
// %PRODUCT% %VERSION%%EDITION% (C) %COPY_YEAR% hiyohiyo\r\n\
//                                   Crystal Dew World: https://crystalmark.info/\r\n\
// ------------------------------------------------------------------------------\r\n\
// * MB/s = 1,000,000 bytes/s [SATA/600 = 600,000,000 bytes/s]\r\n\
// * KB = 1000 bytes, KiB = 1024 bytes\r\n\
// \r\n\
// [Read]\r\n\
// %BenchRead1%\r\n\
// %BenchRead2%\r\n\
// %BenchRead3%\r\n\
// %BenchRead4%\r\n\
// \r\n\
// [Write]\r\n\
// %BenchWrite1%\r\n\
// %BenchWrite2%\r\n\
// %BenchWrite3%\r\n\
// %BenchWrite4%\r\n\
// \r\n\
// ";

// #ifdef MIX_MODE
// 		if (m_MixMode)
// 		{
// 			clip += L"\
// [Mix] %MixRatio%\r\n\
// %BenchMix1%\r\n\
// %BenchMix2%\r\n\
// %BenchMix3%\r\n\
// %BenchMix4%\r\n\
// \r\n\
// ";
// 		}
// #endif

// 		clip += L"\
// Profile: Default\r\n\
//    Test: %TestSize% (x%TestCount%)%Capacity%\r\n\
//    Mode:%TestMode%\r\n\
//    Time: Measure %MeasureTime% / Interval %IntervalTime% \r\n\
//    Date: %Date%\r\n\
//      OS: %OS%\r\n\
// %Comment%";
// 	}
// 	else
// 	{
// 		clip = L"\
// ------------------------------------------------------------------------------\r\n\
// %PRODUCT% %VERSION%%EDITION% (C) %COPY_YEAR% hiyohiyo\r\n\
//                                   Crystal Dew World: https://crystalmark.info/\r\n\
// ------------------------------------------------------------------------------\r\n\
// * MB/s = 1,000,000 bytes/s [SATA/600 = 600,000,000 bytes/s]\r\n\
// * KB = 1000 bytes, KiB = 1024 bytes\r\n\
// \r\n\
// [Read]\r\n\
// %SequentialRead1%\r\n\
// %RandomRead1%\r\n\
// \r\n\
// [Write]\r\n\
// %SequentialWrite1%\r\n\
// %RandomWrite1%\r\n\
// \r\n\
// ";

// #ifdef MIX_MODE
// 		if (m_MixMode)
// 		{
// 			clip += L"\
// [Mix] %MixRatio%\r\n\
// %SequentialMix1%\r\n\
// %RandomMix1%\r\n\
// \r\n\
// ";
// 		}
// #endif

// 		if (m_Profile == PROFILE_PEAK || m_Profile == PROFILE_PEAK_MIX)
// 		{
// 			clip += L"\
// Profile: Peak\r\n\
// ";
// 		}
// 		else
// 		{
// 			clip += L"\
// Profile: Real\r\n\
// ";
// 		}

// 		clip += L"\
//    Test: %TestSize% (x%TestCount%)%Capacity%\r\n\
//    Mode:%TestMode%\r\n\
//    Time: Measure %MeasureTime% / Interval %IntervalTime% \r\n\
//    Date: %Date%\r\n\
//      OS: %OS%\r\n\
// %Comment%";
// 	}

// 	clip.Replace(L"%PRODUCT%", PRODUCT_NAME);
// 	clip.Replace(L"%VERSION%", PRODUCT_VERSION);
	
// 	cstr = PRODUCT_EDITION;
// 	if(! cstr.IsEmpty())
// 	{
// 		clip.Replace(L"%EDITION%", L" " PRODUCT_EDITION);
// 	}
// 	else
// 	{
// 		clip.Replace(L"%EDITION%", PRODUCT_EDITION);
// 	}	
// 	clip.Replace(L"%COPY_YEAR%", PRODUCT_COPY_YEAR);

// 	double iops = 0.0;
// 	double latency = 0.0;

// 	if (m_Profile == PROFILE_DEMO)
// 	{
// 		clip.Replace(L"%BenchRead1%", GetResultString(m_BenchType[8], m_ReadScore.at(8), m_ReadLatency[8], m_BenchSize[8], m_BenchQueues[8], m_BenchThreads[8]));
// 		clip.Replace(L"%BenchWrite1%", GetResultString(m_BenchType[8], m_WriteScore[8], m_WriteLatency[8], m_BenchSize[8], m_BenchQueues[8], m_BenchThreads[8]));

// 	}
// 	else if (m_Profile == PROFILE_PEAK || m_Profile == PROFILE_PEAK_MIX)
// 	{
// 		clip.Replace(L"%SequentialRead1%", GetResultString(BENCH_SEQ, m_ReadScore.at(4), m_ReadLatency[4], m_BenchSize[4], m_BenchQueues[4], m_BenchThreads[4]));
// 		clip.Replace(L"%SequentialWrite1%", GetResultString(BENCH_SEQ, m_WriteScore[4], m_WriteLatency[4], m_BenchSize[4], m_BenchQueues[4], m_BenchThreads[4]));
// 		clip.Replace(L"%RandomRead1%", GetResultString(BENCH_RND, m_ReadScore.at(5), m_ReadLatency[5], m_BenchSize[5], m_BenchQueues[5], m_BenchThreads[5]));
// 		clip.Replace(L"%RandomWrite1%", GetResultString(BENCH_RND, m_WriteScore[5], m_WriteLatency[5], m_BenchSize[5], m_BenchQueues[5], m_BenchThreads[5]));

// #ifdef MIX_MODE
// 		if (m_MixMode)
// 		{
// 			clip.Replace(L"%SequentialMix1%", GetResultString(BENCH_SEQ, m_MixScore[4], m_MixLatency[4], m_BenchSize[4], m_BenchQueues[4], m_BenchThreads[4]));
// 			clip.Replace(L"%RandomMix1%", GetResultString(BENCH_RND, m_MixScore[5], m_MixLatency[5], m_BenchSize[5], m_BenchQueues[5], m_BenchThreads[5]));
// 			cstr.Format(L"Read %d%%/Write %d%%", 100 - m_MixRatio, m_MixRatio);
// 			clip.Replace(L"%MixRatio%", cstr);
// 		}
// #endif
// 	}
// 	else if (m_Profile == PROFILE_REAL || m_Profile == PROFILE_REAL_MIX)
// 	{
// 		clip.Replace(L"%SequentialRead1%", GetResultString(BENCH_SEQ, m_ReadScore.at(6), m_ReadLatency[6], 1024, 1, 1));
// 		clip.Replace(L"%SequentialWrite1%", GetResultString(BENCH_SEQ, m_WriteScore[6], m_WriteLatency[6], 1024, 1, 1));
// 		clip.Replace(L"%RandomRead1%", GetResultString(BENCH_RND, m_ReadScore.at(7), m_ReadLatency[7], 4, 1, 1));
// 		clip.Replace(L"%RandomWrite1%", GetResultString(BENCH_RND, m_WriteScore[7], m_WriteLatency[7], 4, 1, 1));

// #ifdef MIX_MODE
// 		if (m_MixMode)
// 		{
// 			clip.Replace(L"%SequentialMix1%", GetResultString(BENCH_SEQ, m_MixScore[6], m_MixLatency[6], 1024, 1, 1));
// 			clip.Replace(L"%RandomMix1%", GetResultString(BENCH_RND, m_MixScore[7], m_MixLatency[7], 4, 1, 1));
// 			cstr.Format(L"Read %d%%/Write %d%%", 100 - m_MixRatio, m_MixRatio);
// 			clip.Replace(L"%MixRatio%", cstr);
// 		}
// #endif
// 	}

// 	else 
// 	{
// 		clip.Replace(L"%BenchRead1%", GetResultString(m_BenchType[0], m_ReadScore.at(0), m_ReadLatency[0], m_BenchSize[0], m_BenchQueues[0], m_BenchThreads[0]));
// 		clip.Replace(L"%BenchRead2%", GetResultString(m_BenchType[1], m_ReadScore.at(1), m_ReadLatency[1], m_BenchSize[1], m_BenchQueues[1], m_BenchThreads[1]));
// 		clip.Replace(L"%BenchRead3%", GetResultString(m_BenchType[2], m_ReadScore.at(2), m_ReadLatency[2], m_BenchSize[2], m_BenchQueues[2], m_BenchThreads[2]));
// 		clip.Replace(L"%BenchRead4%", GetResultString(m_BenchType[3], m_ReadScore.at(3), m_ReadLatency[3], m_BenchSize[3], m_BenchQueues[3], m_BenchThreads[3]));

// 		clip.Replace(L"%BenchWrite1%", GetResultString(m_BenchType[0], m_WriteScore[0], m_WriteLatency[0], m_BenchSize[0], m_BenchQueues[0], m_BenchThreads[0]));
// 		clip.Replace(L"%BenchWrite2%", GetResultString(m_BenchType[1], m_WriteScore[1], m_WriteLatency[1], m_BenchSize[1], m_BenchQueues[1], m_BenchThreads[1]));
// 		clip.Replace(L"%BenchWrite3%", GetResultString(m_BenchType[2], m_WriteScore[2], m_WriteLatency[2], m_BenchSize[2], m_BenchQueues[2], m_BenchThreads[2]));
// 		clip.Replace(L"%BenchWrite4%", GetResultString(m_BenchType[3], m_WriteScore[3], m_WriteLatency[3], m_BenchSize[3], m_BenchQueues[3], m_BenchThreads[3]));

// #ifdef MIX_MODE
// 		if (m_MixMode)
// 		{
// 			clip.Replace(L"%BenchMix1%", GetResultString(m_BenchType[0], m_MixScore[0], m_MixLatency[0], m_BenchSize[0], m_BenchQueues[0], m_BenchThreads[0]));
// 			clip.Replace(L"%BenchMix2%", GetResultString(m_BenchType[1], m_MixScore[1], m_MixLatency[1], m_BenchSize[1], m_BenchQueues[1], m_BenchThreads[1]));
// 			clip.Replace(L"%BenchMix3%", GetResultString(m_BenchType[2], m_MixScore[2], m_MixLatency[2], m_BenchSize[2], m_BenchQueues[2], m_BenchThreads[2]));
// 			clip.Replace(L"%BenchMix4%", GetResultString(m_BenchType[3], m_MixScore[3], m_MixLatency[3], m_BenchSize[3], m_BenchQueues[3], m_BenchThreads[3]));

// 			cstr.Format(L"Read %d%%/Write %d%%", 100 - m_MixRatio, m_MixRatio);
// 			clip.Replace(L"%MixRatio%", cstr);
// 		}
// #endif
// 	}

// 	if (m_ValueTestSize.Find(L"MiB") == -1)
// 	{
// 		cstr.Format(L"%d GiB", _tstoi(m_ValueTestSize));
// 	}
// 	else
// 	{
// 		cstr.Format(L"%d MiB", _tstoi(m_ValueTestSize));
// 	}

// 	clip.Replace(L"%TestSize%", cstr);
// 	cstr.Format(L"%d", _tstoi(m_ValueTestCount));
// 	clip.Replace(L"%TestCount%", cstr);

// 	cstr = L"";
// 	if (m_AdminMode){ cstr += L" [Admin]"; }
// 	if (m_TestData) { cstr += L" <0Fill>"; }
// 	clip.Replace(L"%TestMode%", cstr);

// 	m_Comment.GetWindowText(cstr);
// 	if (cstr.IsEmpty())
// 	{
// 		clip.Replace(L"%Comment%", L"");
// 	}else
// 	{
// 		clip.Replace(L"%Comment%", L"Comment: " + cstr + L"\r\n");
// 	}

// 	cstr.Format(L"%d sec", m_IntervalTime);
// 	clip.Replace(L"%IntervalTime%", cstr);
// 	cstr.Format(L"%d sec", m_MeasureTime);
// 	clip.Replace(L"%MeasureTime%", cstr);

// 	CString null;
// 	GetOsName(cstr, null, null, null);
// 	clip.Replace(L"%OS%", cstr);

// 	SYSTEMTIME st;
// 	GetLocalTime(&st);
// 	cstr.Format(L"%04d/%02d/%02d %d:%02d:%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
// 	clip.Replace(L"%Date%", cstr);

// 	if (m_ValueTestDrive.FindOneOf(L":") != -1)
// 	{
// 		clip.Replace(L"%Capacity%", L" [" + m_ValueTestDrive + L"]");
// 	}
// 	else
// 	{
// 		clip.Replace(L"%Capacity%", L"");
// 	}

// 	if (fileName.IsEmpty())
// 	{
// 		if (OpenClipboard())
// 		{
// 			HGLOBAL clipbuffer;
// 			TCHAR* buffer;
// 			EmptyClipboard();
// 			clipbuffer = GlobalAlloc(GMEM_DDESHARE, sizeof(TCHAR) * (clip.GetLength() + 1));
// 			if (clipbuffer != NULL)
// 			{
// 				buffer = (TCHAR*)GlobalLock(clipbuffer);
// 				_tcscpy_s(buffer, clip.GetLength() + 1, LPCTSTR(clip));
// 				GlobalUnlock(clipbuffer);
// 				SetClipboardData(CF_UNICODETEXT, clipbuffer);
// 			}
// 			CloseClipboard();
// 		}
// 	}
// 	else
// 	{
// 		CT2A utf8(clip, CP_UTF8);

// 		CFile file;
// 		if (file.Open(fileName, CFile::modeCreate | CFile::modeWrite))
// 		{
// 			file.Write((char*)utf8, (UINT)strlen(utf8));
// 			file.Close();
// 		}
// 	}
}

void CDiskMarkDlg::CheckRadioPresetMode()
{
	if (IsDefaultMode())
	{
		// QAction *action = menuBar()->findChild<QAction*>("ID_SETTING_DEFAULT");
		// if (action) {
		// 	action->setChecked(true);
		// }
	}
	else if (IsNVMe8Mode())
	{
		// QAction *action = menuBar()->findChild<QAction*>("ID_SETTING_NVME_8");
		// if (action) {
		// 	action->setChecked(true);
		// }
	}
	/*
	else if (IsNVMe9Mode())
	{
		QAction *action = menuBar()->findChild<QAction*>("ID_SETTING_NVME_9");
		if (action) {
			action->setChecked(true);
		}
	}
	*/
	else
	{
		// QAction *action = menuBar()->findChild<QAction*>("ID_SETTING_DEFAULT");
		// if (action) {
		// 	action->setChecked(false);
		// }
		// action = menuBar()->findChild<QAction*>("ID_SETTING_NVME_8");
		// if (action) {
		// 	action->setChecked(false);
		// }
	}
}

void CDiskMarkDlg::OnHelp()
{
}
void CDiskMarkDlg::OnBlizzardWorld()
{
}

void CDiskMarkDlg::OnSettingDefault()
{
	SettingsQueuesThreads(0);
}
void CDiskMarkDlg::OnSettingNVMe8()
{
	SettingsQueuesThreads(1);
}
/*
void CDiskMarkDlg::OnSettingNVMe9()
{
	CMenu* menu = GetMenu();
	menu->CheckMenuRadioItem(ID_SETTING_DEFAULT, ID_SETTING_NVME_9, ID_SETTING_NVME_9, MF_BYCOMMAND);
	SetMenu(menu);
	DrawMenuBar();

	SettingsQueuesThreads(2);
}
*/

void CDiskMarkDlg::OnModeDefault()
{
	m_TestData = TEST_DATA_RANDOM;
	m_TestDataChanged();
}
void CDiskMarkDlg::OnModeAll0x00()
{
	m_TestData = TEST_DATA_ALL0X00;
	m_TestDataChanged();
}

void CDiskMarkDlg::OnProfileDefault()
{
	ProfileDefault();
	
	InitScore();
}
void CDiskMarkDlg::ProfileDefault()
{
	m_Profile = PROFILE_DEFAULT;
	m_MixMode = false;
	emit m_ProfileChanged();
}

void CDiskMarkDlg::OnProfilePeak()
{
	ProfilePeak();
	
	InitScore();
}
void CDiskMarkDlg::ProfilePeak()
{
	m_Profile = PROFILE_PEAK;
	m_MixMode = false;
	emit m_ProfileChanged();
}

void CDiskMarkDlg::OnProfileReal()
{
	ProfileReal();
	
	InitScore();
}
void CDiskMarkDlg::ProfileReal()
{
	m_Profile = PROFILE_REAL;
	m_MixMode = false;
	emit m_ProfileChanged();
}

void CDiskMarkDlg::OnProfileDemo()
{
	ProfileDemo();
	
	InitScore();
}
void CDiskMarkDlg::ProfileDemo()
{
	m_Profile = PROFILE_DEMO;
	m_MixMode = false;
	m_ProfileChanged();
}

void CDiskMarkDlg::OnProfileDefaultMix()
{
	ProfileDefaultMix();
	
	InitScore();
}
void CDiskMarkDlg::ProfileDefaultMix()
{
	m_Profile = PROFILE_DEFAULT_MIX;
	m_MixMode = true;
	emit m_ProfileChanged();
}

void CDiskMarkDlg::OnProfilePeakMix()
{
	ProfilePeakMix();
	
	InitScore();
}
void CDiskMarkDlg::ProfilePeakMix()
{
	m_Profile = PROFILE_PEAK_MIX;
	m_MixMode = true;
	emit m_ProfileChanged();
}

void CDiskMarkDlg::OnProfileRealMix()
{
	ProfileRealMix();
	
	InitScore();
}
void CDiskMarkDlg::ProfileRealMix()
{
	m_Profile = PROFILE_REAL_MIX;
	m_MixMode = true;
}

void CDiskMarkDlg::OnBenchmarkReadWrite()
{
	BenchmarkReadWrite();
}
void CDiskMarkDlg::BenchmarkReadWrite()
{
	m_Benchmark = BENCH_READ_WRITE;
	m_BenchmarkChanged();
}

void CDiskMarkDlg::OnBenchmarkReadOnly()
{
	BenchmarkReadOnly();
}
void CDiskMarkDlg::BenchmarkReadOnly()
{
	m_Benchmark = BENCH_READ;
	m_BenchmarkChanged();
}

void CDiskMarkDlg::OnBenchmarkWriteOnly()
{
	BenchmarkWriteOnly();
}
void CDiskMarkDlg::BenchmarkWriteOnly()
{
	m_Benchmark = BENCH_WRITE;
	m_BenchmarkChanged();
}

void CDiskMarkDlg::OnSettingsQueuesThreads()
{
	if (! m_DiskBenchStatus)
	{
	}
}
void CDiskMarkDlg::OnSettings()
{
}

void CDiskMarkDlg::OnExitBenchmark()
{
}

CDiskMarkDlg::Profile CDiskMarkDlg::m_getProfile() const
{
	return static_cast<CDiskMarkDlg::Profile>(m_Profile);
}
CDiskMarkDlg::TEST_DATA_TYPE CDiskMarkDlg::m_getTestData() const
{
	return static_cast<CDiskMarkDlg::TEST_DATA_TYPE>(m_TestData);
}
CDiskMarkDlg::BENCHMODE CDiskMarkDlg::m_getBenchmark() const
{
	return static_cast<CDiskMarkDlg::BENCHMODE>(m_Benchmark);
}

QList<double> CDiskMarkDlg::m_readScoreList() const
{
	QList<double> list;
	for (double* score : m_ReadScore)
	{
		list.append(*score);
	}
	return list;
}
QList<double> CDiskMarkDlg::m_writeScoreList() const
{
	QList<double> list;
	for (double* score : m_WriteScore)
	{
		list.append(*score);
	}
	return list;
}
QList<double> CDiskMarkDlg::m_readLatencyList() const
{
	QList<double> list;
	for (double* latency : m_ReadLatency)
	{
		list.append(*latency);
	}
	return list;
}
QList<double> CDiskMarkDlg::m_writeLatencyList() const
{
	QList<double> list;
	for (double* latency : m_WriteLatency)
	{
		list.append(*latency);
	}
	return list;
}

QList<int> CDiskMarkDlg::m_benchTypeList() const
{
	QList<int> list;
	for (int* size : m_BenchType)
	{
		list.append(*size);
	}
	return list;
}
QList<int> CDiskMarkDlg::m_blockSizeList() const
{
	QList<int> list;
	for (int size : m_BenchSize)
	{
		list.append(size);
	}
	return list;
}
QList<int> CDiskMarkDlg::m_benchQueuesList() const
{
	QList<int> list;
	for (int size : m_BenchQueues)
	{
		list.append(size);
	}
	return list;
}
QList<int> CDiskMarkDlg::m_benchThreadsList() const
{
	QList<int> list;
	for (int size : m_BenchThreads)
	{
		list.append(size);
	}
	return list;
}