/*---------------------------------------------------------------------------*/
//       Author : hiyohiyo
//         Mail : hiyohiyo@crystalmark.info
//          Web : https://crystalmark.info/
//      License : MIT License
/*---------------------------------------------------------------------------*/

//#include "stdafx.h"
#include "DiskMark.h"
#include "DiskMarkDlg.h"
#include "DiskMark.h"
#include "DiskBench.h"
#include <unistd.h>
#include <mach-o/dyld.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/statvfs.h>
#include <sys/mount.h>
#include <sys/stat.h>
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

int ExecAndWait(QString *pszCmd, bool bNoWindow, double *score, double *latency)
{
	int Code = 0;
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

		if (bNoWindow) {
			int fd = open("/dev/null", O_WRONLY);
			if (fd == -1) {
				perror("open");
				exit(EXIT_FAILURE);
			}
			dup2(fd, STDOUT_FILENO);
			dup2(fd, STDERR_FILENO);
			close(fd);
		}

		dup2(pipefd[1], STDOUT_FILENO);
		dup2(pipefd[1], STDERR_FILENO);
		close(pipefd[1]);

		execl("/bin/sh", "sh", "-c", pszCmd->toStdString().c_str(), (char *)NULL);
		perror("execl");
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
			Code = WEXITSTATUS(status);
		}

		/*Sample fio output:
{
  "fio version" : "fio-3.39",
  "timestamp" : 1741208676,
  "timestamp_ms" : 1741208676700,
  "time" : "Wed Mar  5 22:04:36 2025",
  "global options" : {
    "bs" : "1K",
    "iodepth" : "8",
    "numjobs" : "1",
    "direct" : "1",
    "rw" : "randwrite",
    "ioengine" : "posixaio"
  },
  "jobs" : [
    {
      "jobname" : "/Users/alexander/CrystalDiskMark/CrystalDiskMark195681fd01a/CrystalDiskMark195681fd01a.tmp",
      "groupid" : 0,
      "job_start" : 1741208675800,
      "error" : 0,
      "eta" : 2147483647,
      "elapsed" : 2,
      "job options" : {
        "name" : "/Users/alexander/CrystalDiskMark/CrystalDiskMark195681fd01a/CrystalDiskMark195681fd01a.tmp",
        "size" : "16Mi"
      },
      "read" : {
        "io_bytes" : 0,
        "io_kbytes" : 0,
        "bw_bytes" : 0,
        "bw" : 0,
        "iops" : 0.000000,
        "runtime" : 0,
        "total_ios" : 0,
        "short_ios" : 0,
        "drop_ios" : 0,
        "slat_ns" : {
          "min" : 0,
          "max" : 0,
          "mean" : 0.000000,
          "stddev" : 0.000000,
          "N" : 0
        },
        "clat_ns" : {
          "min" : 0,
          "max" : 0,
          "mean" : 0.000000,
          "stddev" : 0.000000,
          "N" : 0
        },
        "lat_ns" : {
          "min" : 0,
          "max" : 0,
          "mean" : 0.000000,
          "stddev" : 0.000000,
          "N" : 0
        },
        "bw_min" : 0,
        "bw_max" : 0,
        "bw_agg" : 0.000000,
        "bw_mean" : 0.000000,
        "bw_dev" : 0.000000,
        "bw_samples" : 0,
        "iops_min" : 0,
        "iops_max" : 0,
        "iops_mean" : 0.000000,
        "iops_stddev" : 0.000000,
        "iops_samples" : 0
      },
      "write" : {
        "io_bytes" : 16777216,
        "io_kbytes" : 16384,
        "bw_bytes" : 20092474,
        "bw" : 19621,
        "iops" : 19621.556886,
        "runtime" : 835,
        "total_ios" : 16384,
        "short_ios" : 0,
        "drop_ios" : 0,
        "slat_ns" : {
          "min" : 0,
          "max" : 35000,
          "mean" : 400.146484,
          "stddev" : 848.775545,
          "N" : 16384
        },
        "clat_ns" : {
          "min" : 2000,
          "max" : 9112000,
          "mean" : 406584.472656,
          "stddev" : 703756.851897,
          "N" : 16384,
          "percentile" : {
            "1.000000" : 22912,
            "5.000000" : 50944,
            "10.000000" : 76288,
            "20.000000" : 112128,
            "30.000000" : 140288,
            "40.000000" : 166912,
            "50.000000" : 189440,
            "60.000000" : 214016,
            "70.000000" : 238592,
            "80.000000" : 296960,
            "90.000000" : 1482752,
            "95.000000" : 1859584,
            "99.000000" : 3489792,
            "99.500000" : 3719168,
            "99.900000" : 4816896,
            "99.950000" : 7503872,
            "99.990000" : 8978432
          },
          "bins" : {
            "2008" : 1,
            "4016" : 1,
            "5984" : 9,
            "7008" : 5,
            "8032" : 6,
            "9024" : 10,
            "10048" : 12,
            "10944" : 6,
            "11968" : 11,
            "12992" : 10,
            "14016" : 8,
            "15040" : 6,
            "16064" : 9,
            "17024" : 13,
            "18048" : 13,
            "19072" : 5,
            "20096" : 11,
            "21120" : 15,
            "21888" : 11,
            "22912" : 16,
            "23936" : 13,
            "24960" : 20,
            "25984" : 20,
            "27008" : 9,
            "28032" : 13,
            "29056" : 21,
            "30080" : 13,
            "31104" : 16,
            "32128" : 16,
            "33024" : 19,
            "34048" : 22,
            "35072" : 26,
            "36096" : 22,
            "37120" : 25,
            "38144" : 20,
            "39168" : 26,
            "40192" : 32,
            "41216" : 24,
            "42240" : 30,
            "42752" : 37,
            "43776" : 30,
            "44800" : 28,
            "45824" : 38,
            "46848" : 26,
            "47872" : 23,
            "48896" : 37,
            "49920" : 24,
            "50944" : 39,
            "51968" : 33,
            "52992" : 27,
            "54016" : 23,
            "55040" : 31,
            "56064" : 17,
            "57088" : 33,
            "58112" : 27,
            "59136" : 30,
            "60160" : 30,
            "61184" : 20,
            "62208" : 26,
            "63232" : 35,
            "64256" : 33,
            "64768" : 31,
            "66048" : 41,
            "67072" : 44,
            "68096" : 32,
            "69120" : 42,
            "70144" : 38,
            "71168" : 44,
            "72192" : 48,
            "73216" : 33,
            "74240" : 26,
            "75264" : 35,
            "76288" : 37,
            "77312" : 39,
            "78336" : 36,
            "79360" : 38,
            "80384" : 44,
            "81408" : 32,
            "82432" : 34,
            "83456" : 38,
            "84480" : 38,
            "85504" : 98,
            "86528" : 41,
            "87552" : 44,
            "88576" : 38,
            "89600" : 47,
            "90624" : 40,
            "91648" : 49,
            "92672" : 43,
            "93696" : 49,
            "94720" : 39,
            "95744" : 63,
            "96768" : 51,
            "97792" : 52,
            "98816" : 51,
            "99840" : 44,
            "100864" : 44,
            "101888" : 55,
            "102912" : 40,
            "103936" : 60,
            "104960" : 46,
            "105984" : 62,
            "107008" : 49,
            "108032" : 55,
            "109056" : 54,
            "110080" : 46,
            "111104" : 47,
            "112128" : 56,
            "113152" : 57,
            "114176" : 54,
            "115200" : 52,
            "116224" : 56,
            "117248" : 49,
            "118272" : 55,
            "119296" : 64,
            "120320" : 68,
            "121344" : 51,
            "122368" : 63,
            "123392" : 65,
            "124416" : 54,
            "125440" : 71,
            "126464" : 55,
            "127488" : 56,
            "128512" : 108,
            "129536" : 62,
            "130560" : 54,
            "132096" : 107,
            "134144" : 125,
            "136192" : 114,
            "138240" : 131,
            "140288" : 139,
            "142336" : 138,
            "144384" : 125,
            "146432" : 116,
            "148480" : 110,
            "150528" : 98,
            "152576" : 136,
            "154624" : 129,
            "156672" : 114,
            "158720" : 123,
            "160768" : 139,
            "162816" : 128,
            "164864" : 142,
            "166912" : 113,
            "168960" : 134,
            "171008" : 190,
            "173056" : 146,
            "175104" : 142,
            "177152" : 128,
            "179200" : 157,
            "181248" : 148,
            "183296" : 135,
            "185344" : 130,
            "187392" : 121,
            "189440" : 129,
            "191488" : 133,
            "193536" : 148,
            "195584" : 130,
            "197632" : 128,
            "199680" : 129,
            "201728" : 149,
            "203776" : 158,
            "205824" : 131,
            "207872" : 145,
            "209920" : 160,
            "211968" : 138,
            "214016" : 214,
            "216064" : 143,
            "218112" : 156,
            "220160" : 148,
            "222208" : 141,
            "224256" : 118,
            "226304" : 122,
            "228352" : 111,
            "230400" : 137,
            "232448" : 115,
            "234496" : 118,
            "236544" : 120,
            "238592" : 106,
            "240640" : 102,
            "242688" : 120,
            "244736" : 92,
            "246784" : 102,
            "248832" : 64,
            "250880" : 80,
            "252928" : 51,
            "254976" : 87,
            "257024" : 94,
            "259072" : 55,
            "261120" : 71,
            "264192" : 124,
            "268288" : 100,
            "272384" : 88,
            "276480" : 92,
            "280576" : 67,
            "284672" : 63,
            "288768" : 65,
            "292864" : 67,
            "296960" : 58,
            "301056" : 55,
            "305152" : 39,
            "309248" : 51,
            "313344" : 51,
            "317440" : 45,
            "321536" : 35,
            "325632" : 40,
            "329728" : 40,
            "333824" : 41,
            "337920" : 46,
            "342016" : 47,
            "346112" : 37,
            "350208" : 34,
            "354304" : 42,
            "358400" : 31,
            "362496" : 34,
            "366592" : 25,
            "370688" : 30,
            "374784" : 32,
            "378880" : 25,
            "382976" : 30,
            "387072" : 28,
            "391168" : 24,
            "395264" : 28,
            "399360" : 25,
            "403456" : 19,
            "407552" : 16,
            "411648" : 14,
            "415744" : 15,
            "419840" : 23,
            "423936" : 13,
            "428032" : 17,
            "432128" : 17,
            "436224" : 15,
            "440320" : 15,
            "444416" : 10,
            "448512" : 16,
            "452608" : 12,
            "456704" : 11,
            "460800" : 12,
            "464896" : 7,
            "468992" : 10,
            "473088" : 10,
            "477184" : 12,
            "481280" : 8,
            "485376" : 9,
            "489472" : 3,
            "493568" : 5,
            "497664" : 4,
            "501760" : 5,
            "505856" : 9,
            "509952" : 2,
            "514048" : 9,
            "518144" : 6,
            "522240" : 6,
            "528384" : 6,
            "536576" : 11,
            "544768" : 8,
            "552960" : 10,
            "561152" : 7,
            "569344" : 10,
            "577536" : 8,
            "585728" : 8,
            "593920" : 6,
            "602112" : 7,
            "610304" : 4,
            "618496" : 6,
            "626688" : 3,
            "634880" : 3,
            "643072" : 3,
            "651264" : 4,
            "659456" : 3,
            "667648" : 4,
            "675840" : 4,
            "684032" : 2,
            "692224" : 5,
            "700416" : 1,
            "708608" : 3,
            "716800" : 2,
            "733184" : 1,
            "741376" : 1,
            "765952" : 3,
            "790528" : 2,
            "798720" : 2,
            "806912" : 1,
            "815104" : 1,
            "831488" : 2,
            "856064" : 1,
            "864256" : 2,
            "872448" : 1,
            "897024" : 1,
            "905216" : 2,
            "913408" : 3,
            "929792" : 1,
            "937984" : 1,
            "970752" : 1,
            "987136" : 2,
            "995328" : 1,
            "1019904" : 2,
            "1044480" : 2,
            "1056768" : 1,
            "1073152" : 1,
            "1089536" : 5,
            "1105920" : 2,
            "1122304" : 6,
            "1138688" : 2,
            "1155072" : 5,
            "1171456" : 4,
            "1187840" : 2,
            "1204224" : 1,
            "1220608" : 4,
            "1236992" : 1,
            "1253376" : 3,
            "1269760" : 2,
            "1286144" : 2,
            "1302528" : 2,
            "1318912" : 6,
            "1335296" : 6,
            "1351680" : 7,
            "1368064" : 12,
            "1384448" : 7,
            "1400832" : 18,
            "1417216" : 18,
            "1433600" : 24,
            "1449984" : 19,
            "1466368" : 27,
            "1482752" : 27,
            "1499136" : 20,
            "1515520" : 31,
            "1531904" : 30,
            "1548288" : 37,
            "1564672" : 44,
            "1581056" : 39,
            "1597440" : 30,
            "1613824" : 38,
            "1630208" : 48,
            "1646592" : 35,
            "1662976" : 32,
            "1679360" : 26,
            "1695744" : 34,
            "1712128" : 47,
            "1728512" : 36,
            "1744896" : 42,
            "1761280" : 36,
            "1777664" : 34,
            "1794048" : 38,
            "1810432" : 34,
            "1826816" : 45,
            "1843200" : 36,
            "1859584" : 23,
            "1875968" : 38,
            "1892352" : 30,
            "1908736" : 23,
            "1925120" : 23,
            "1941504" : 18,
            "1957888" : 16,
            "1974272" : 22,
            "1990656" : 22,
            "2007040" : 23,
            "2023424" : 13,
            "2039808" : 9,
            "2056192" : 15,
            "2072576" : 11,
            "2088960" : 8,
            "2113536" : 17,
            "2146304" : 14,
            "2179072" : 9,
            "2211840" : 13,
            "2244608" : 8,
            "2277376" : 5,
            "2310144" : 6,
            "2342912" : 5,
            "2375680" : 6,
            "2408448" : 2,
            "2441216" : 5,
            "2473984" : 5,
            "2506752" : 2,
            "2539520" : 5,
            "2572288" : 1,
            "2637824" : 6,
            "2670592" : 7,
            "2801664" : 4,
            "2834432" : 1,
            "2867200" : 6,
            "2899968" : 2,
            "2932736" : 1,
            "2965504" : 1,
            "2998272" : 3,
            "3031040" : 4,
            "3063808" : 11,
            "3096576" : 6,
            "3129344" : 3,
            "3162112" : 23,
            "3194880" : 17,
            "3227648" : 20,
            "3260416" : 19,
            "3293184" : 20,
            "3325952" : 15,
            "3358720" : 12,
            "3391488" : 23,
            "3424256" : 26,
            "3457024" : 26,
            "3489792" : 14,
            "3522560" : 12,
            "3555328" : 21,
            "3588096" : 11,
            "3620864" : 15,
            "3653632" : 10,
            "3686400" : 8,
            "3719168" : 9,
            "3751936" : 15,
            "3784704" : 4,
            "3817472" : 5,
            "3850240" : 2,
            "3883008" : 4,
            "3915776" : 4,
            "3948544" : 4,
            "3981312" : 2,
            "4014080" : 1,
            "4227072" : 3,
            "4292608" : 1,
            "4423680" : 1,
            "4489216" : 2,
            "4620288" : 1,
            "4685824" : 2,
            "4751360" : 4,
            "4816896" : 3,
            "6520832" : 3,
            "6717440" : 1,
            "7176192" : 1,
            "7503872" : 3,
            "8716288" : 1,
            "8847360" : 1,
            "8978432" : 4,
            "9109504" : 1
          }
        },
        "lat_ns" : {
          "min" : 4000,
          "max" : 9113000,
          "mean" : 406984.619141,
          "stddev" : 703767.851671,
          "N" : 16384
        },
        "bw_min" : 19205,
        "bw_max" : 19205,
        "bw_agg" : 97.877046,
        "bw_mean" : 19205.000000,
        "bw_dev" : 0.000000,
        "bw_samples" : 1,
        "iops_min" : 19205,
        "iops_max" : 19205,
        "iops_mean" : 19205.000000,
        "iops_stddev" : 0.000000,
        "iops_samples" : 1
      },
      "trim" : {
        "io_bytes" : 0,
        "io_kbytes" : 0,
        "bw_bytes" : 0,
        "bw" : 0,
        "iops" : 0.000000,
        "runtime" : 0,
        "total_ios" : 0,
        "short_ios" : 0,
        "drop_ios" : 0,
        "slat_ns" : {
          "min" : 0,
          "max" : 0,
          "mean" : 0.000000,
          "stddev" : 0.000000,
          "N" : 0
        },
        "clat_ns" : {
          "min" : 0,
          "max" : 0,
          "mean" : 0.000000,
          "stddev" : 0.000000,
          "N" : 0
        },
        "lat_ns" : {
          "min" : 0,
          "max" : 0,
          "mean" : 0.000000,
          "stddev" : 0.000000,
          "N" : 0
        },
        "bw_min" : 0,
        "bw_max" : 0,
        "bw_agg" : 0.000000,
        "bw_mean" : 0.000000,
        "bw_dev" : 0.000000,
        "bw_samples" : 0,
        "iops_min" : 0,
        "iops_max" : 0,
        "iops_mean" : 0.000000,
        "iops_stddev" : 0.000000,
        "iops_samples" : 0
      },
      "sync" : {
        "total_ios" : 0,
        "lat_ns" : {
          "min" : 0,
          "max" : 0,
          "mean" : 0.000000,
          "stddev" : 0.000000,
          "N" : 0
        }
      },
      "job_runtime" : 834,
      "usr_cpu" : 3.477218,
      "sys_cpu" : 3.836930,
      "ctx" : 12221,
      "majf" : 0,
      "minf" : 6,
      "iodepth_level" : {
        "1" : 0.100000,
        "2" : 0.109863,
        "4" : 16.723633,
        "8" : 83.148193,
        "16" : 0.000000,
        "32" : 0.000000,
        ">=64" : 0.000000
      },
      "iodepth_submit" : {
        "0" : 0.000000,
        "4" : 100.000000,
        "8" : 0.000000,
        "16" : 0.000000,
        "32" : 0.000000,
        "64" : 0.000000,
        ">=64" : 0.000000
      },
      "iodepth_complete" : {
        "0" : 0.000000,
        "4" : 99.863370,
        "8" : 0.136630,
        "16" : 0.000000,
        "32" : 0.000000,
        "64" : 0.000000,
        ">=64" : 0.000000
      },
      "latency_ns" : {
        "2" : 0.000000,
        "4" : 0.000000,
        "10" : 0.000000,
        "20" : 0.000000,
        "50" : 0.000000,
        "100" : 0.000000,
        "250" : 0.000000,
        "500" : 0.000000,
        "750" : 0.000000,
        "1000" : 0.000000
      },
      "latency_us" : {
        "2" : 0.000000,
        "4" : 0.010000,
        "10" : 0.189209,
        "20" : 0.567627,
        "50" : 4.022217,
        "100" : 11.492920,
        "250" : 56.866455,
        "500" : 14.465332,
        "750" : 1.019287,
        "1000" : 0.164795
      },
      "latency_ms" : {
        "2" : 7.482910,
        "4" : 3.521729,
        "10" : 0.201416,
        "20" : 0.000000,
        "50" : 0.000000,
        "100" : 0.000000,
        "250" : 0.000000,
        "500" : 0.000000,
        "750" : 0.000000,
        "1000" : 0.000000,
        "2000" : 0.000000,
        ">=2000" : 0.000000
      },
      "latency_depth" : 8,
      "latency_target" : 0,
      "latency_percentile" : 100.000000,
      "latency_window" : 0
    }
  ]
}
*/

		//printf("fio output:\n%s\n", output.toStdString().c_str());
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
				*latency = lat_ns["mean"].toDouble();
				*score = read["bw_bytes"].toDouble() / 1024.0 / 1024.0;
			} else if (rw.contains("write")) {
				QJsonArray jobs = jsonObject["jobs"].toArray();
				QJsonObject job = jobs[0].toObject();
				QJsonObject write = job["write"].toObject();
				QJsonObject lat_ns = write["lat_ns"].toObject();
				*latency = lat_ns["mean"].toDouble();
				*score = write["bw_bytes"].toDouble() / 1024.0 / 1024.0;
			}
		} else {
			if (Code == 0) {
				Code = -1;
				return Code;
			}
		}
	}
	//printf("latency: %f, score: %f\n", *latency, *score);

	return Code;
}


void ShowErrorMessage(QString message)
{
	QString errorMessage = QString("Error: %1\n%2").arg(message).arg(strerror(errno));
	QMetaObject::invokeMethod(QApplication::instance(), [errorMessage]() {
		QMessageBox::critical(nullptr, QObject::tr("Error"), errorMessage);
	}, Qt::QueuedConnection);
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
		QMetaObject::invokeMethod(((CDiskMarkDlg*) dlg), "OnUpdateMessage", Qt::QueuedConnection, Q_ARG(QString*, &title));
		sleep(1);
	}
}

uint ExecDiskBenchAll(void* dlg)
{
	int benchmark = ((CDiskMarkDlg*)dlg)->m_Benchmark;

	if(Init(dlg))
	{
		if (benchmark & BENCHMARK_READ)
		{
			DiskSpd(dlg, TEST_READ_0); Interval(dlg);
			DiskSpd(dlg, TEST_READ_1); Interval(dlg);
			DiskSpd(dlg, TEST_READ_2); Interval(dlg);
			DiskSpd(dlg, TEST_READ_3);
		}
		if ((benchmark & BENCHMARK_READ) && (benchmark & BENCHMARK_WRITE))
		{
			Interval(dlg);
		}
		if (benchmark & BENCHMARK_WRITE)
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

uint ExecDiskBenchAllPeak(void* dlg)
{
	int benchmark = ((CDiskMarkDlg*)dlg)->m_Benchmark;

	if (Init(dlg))
	{
		if (benchmark & BENCHMARK_READ)
		{
			DiskSpd(dlg, TEST_READ_4); Interval(dlg);
			DiskSpd(dlg, TEST_READ_5);
		}
		if ((benchmark & BENCHMARK_READ) && (benchmark & BENCHMARK_WRITE))
		{
			Interval(dlg);
		}
		if (benchmark & BENCHMARK_WRITE)
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

uint ExecDiskBenchAllReal(void* dlg)
{
	int benchmark = ((CDiskMarkDlg*)dlg)->m_Benchmark;

	if (Init(dlg))
	{
		if (benchmark & BENCHMARK_READ)
		{
			DiskSpd(dlg, TEST_READ_6); Interval(dlg);
			DiskSpd(dlg, TEST_READ_7);
		}
		if ((benchmark & BENCHMARK_READ) && (benchmark & BENCHMARK_WRITE))
		{
			Interval(dlg);
		}
		if (benchmark & BENCHMARK_WRITE)
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

uint ExecDiskBenchAllDemo(void* dlg)
{
	int benchmark = ((CDiskMarkDlg*)dlg)->m_Benchmark;

	if (Init(dlg))
	{
		if (benchmark & BENCHMARK_READ)
		{
			DiskSpd(dlg, TEST_READ_8);
		}
		if ((benchmark & BENCHMARK_READ) && (benchmark & BENCHMARK_WRITE))
		{
			Interval(dlg);
		}
		if (benchmark & BENCHMARK_WRITE)
		{
			DiskSpd(dlg, TEST_WRITE_8);
		}
	}

	return Exit(dlg);
}

u_int ExecDiskBench0(void* dlg)
{
	int benchmark = ((CDiskMarkDlg*)dlg)->m_Benchmark;

	if (Init(dlg))
	{
		if (benchmark & BENCHMARK_READ)
		{
			DiskSpd(dlg, TEST_READ_0);
		}
		if ((benchmark & BENCHMARK_READ) && (benchmark & BENCHMARK_WRITE))
		{
			Interval(dlg);
		}
		if (benchmark & BENCHMARK_WRITE)
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

uint ExecDiskBench1(void* dlg)
{
	int benchmark = ((CDiskMarkDlg*)dlg)->m_Benchmark;

	if (Init(dlg))
	{
		if (benchmark & BENCHMARK_READ)
		{
			DiskSpd(dlg, TEST_READ_1);
		}
		if ((benchmark & BENCHMARK_READ) && (benchmark & BENCHMARK_WRITE))
		{
			Interval(dlg);
		}
		if (benchmark & BENCHMARK_WRITE)
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

uint ExecDiskBench2(void* dlg)
{
	int benchmark = ((CDiskMarkDlg*)dlg)->m_Benchmark;

	if (Init(dlg))
	{
		if (benchmark & BENCHMARK_READ)
		{
			DiskSpd(dlg, TEST_READ_2);
		}
		if ((benchmark & BENCHMARK_READ) && (benchmark & BENCHMARK_WRITE))
		{
			Interval(dlg);
		}
		if (benchmark & BENCHMARK_WRITE)
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

uint ExecDiskBench3(void* dlg)
{
	int benchmark = ((CDiskMarkDlg*)dlg)->m_Benchmark;

	if (Init(dlg))
	{
		if (benchmark & BENCHMARK_READ)
		{
			DiskSpd(dlg, TEST_READ_3);
		}
		if ((benchmark & BENCHMARK_READ) && (benchmark & BENCHMARK_WRITE))
		{
			Interval(dlg);
		}
		if (benchmark & BENCHMARK_WRITE)
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

uint ExecDiskBench4(void* dlg)
{
	int benchmark = ((CDiskMarkDlg*)dlg)->m_Benchmark;

	if (Init(dlg))
	{
		if (benchmark & BENCHMARK_READ)
		{
			DiskSpd(dlg, TEST_READ_4);
		}
		if ((benchmark & BENCHMARK_READ) && (benchmark & BENCHMARK_WRITE))
		{
			Interval(dlg);
		}
		if (benchmark & BENCHMARK_WRITE)
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

uint ExecDiskBench5(void* dlg)
{
	int benchmark = ((CDiskMarkDlg*)dlg)->m_Benchmark;

	if (Init(dlg))
	{
		if (benchmark & BENCHMARK_READ)
		{
			DiskSpd(dlg, TEST_READ_5);
		}
		if ((benchmark & BENCHMARK_READ) && (benchmark & BENCHMARK_WRITE))
		{
			Interval(dlg);
		}
		if (benchmark & BENCHMARK_WRITE)
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

uint ExecDiskBench6(void* dlg)
{
	int benchmark = ((CDiskMarkDlg*)dlg)->m_Benchmark;

	if (Init(dlg))
	{
		if (benchmark & BENCHMARK_READ)
		{
			DiskSpd(dlg, TEST_READ_6);
		}
		if ((benchmark & BENCHMARK_READ) && (benchmark & BENCHMARK_WRITE))
		{
			Interval(dlg);
		}
		if (benchmark & BENCHMARK_WRITE)
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

uint ExecDiskBench7(void* dlg)
{
	int benchmark = ((CDiskMarkDlg*)dlg)->m_Benchmark;

	if (Init(dlg))
	{
		if (benchmark & BENCHMARK_READ)
		{
			DiskSpd(dlg, TEST_READ_7);
		}
		if ((benchmark & BENCHMARK_READ) && (benchmark & BENCHMARK_WRITE))
		{
			Interval(dlg);
		}
		if (benchmark & BENCHMARK_WRITE)
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

	quint64 freeBytesAvailableToCaller;
	quint64 totalNumberOfBytes;
	quint64 totalNumberOfFreeBytes;

	char temp[PATH_MAX];
	uint32_t size = sizeof(temp);
	if (_NSGetExecutablePath(temp, &size) != 0) {
		perror("_NSGetExecutablePath");
		return false;
	}
	char *ptrEnd = strrchr(temp, '/');
	if (ptrEnd != NULL) {
		*ptrEnd = '\0';
	}

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
	if(((CDiskMarkDlg*)dlg)->m_MaxIndexTestDrive != ((CDiskMarkDlg*)dlg)->m_IndexTestDrive)
	{
		drive = ((CDiskMarkDlg*)dlg)->m_ValueTestDrive.at(0);
		cstr = QString("/Volumes/%1").arg(drive);
		struct statvfs stat;
		if (statvfs(cstr.toStdString().c_str(), &stat) != 0) {
			perror("statvfs");
			return false;
		}
		freeBytesAvailableToCaller = stat.f_bavail * stat.f_frsize;
		totalNumberOfBytes = stat.f_blocks * stat.f_frsize;
		totalNumberOfFreeBytes = stat.f_bfree * stat.f_frsize;
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
		TempPath = QDir().tempPath();
		TestFileDir = QString("%1/CrystalDiskMark%2").arg(TempPath).arg(QDateTime::currentMSecsSinceEpoch(), 8, 16, QChar('0'));
	}
	else
	{
		RootPath = ((CDiskMarkDlg*)dlg)->m_TestTargetPath;
		TestFileDir = QString("%1/CrystalDiskMark%2").arg(RootPath).arg(QDateTime::currentMSecsSinceEpoch(), 8, 16, QChar('0'));
	}
	mkdir(TestFileDir.toStdString().c_str(), 0777);
	TestFilePath = QString("%1/CrystalDiskMark%2.tmp").arg(TestFileDir).arg(QDateTime::currentMSecsSinceEpoch(), 8, 16, QChar('0'));

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

	freeBytesAvailableToCaller = stat.f_bavail * stat.f_frsize;
	totalNumberOfBytes = stat.f_blocks * stat.f_frsize;
	totalNumberOfFreeBytes = stat.f_bfree * stat.f_frsize;

	if(DiskTestSize > totalNumberOfFreeBytes / 1024 / 1024 )
	{
		ShowErrorMessage(((CDiskMarkDlg*)dlg)->m_MesDiskCapacityError);
		((CDiskMarkDlg*)dlg)->m_DiskBenchStatus = false;
		return false;
	}

	QString title;
	title = QString::asprintf("Preparing... Create Test File");
	QMetaObject::invokeMethod(((CDiskMarkDlg*)dlg), "OnUpdateMessage", Qt::QueuedConnection, Q_ARG(QString*, &title));
	// Prepare Test File
	int hFile = open(TestFilePath.toStdString().c_str(), O_CREAT | O_RDWR, 0666);

	if (hFile == -1)
	{
		perror("open");
		((CDiskMarkDlg*)dlg)->m_DiskBenchStatus = false;
		return false;
	}

// Set End Of File to prevent fragmentation of test file
	if (ftruncate(hFile, 1024 * 1024 * DiskTestSize) == -1) {
		perror("ftruncate");
		close(hFile);
		((CDiskMarkDlg*)dlg)->m_DiskBenchStatus = false;
		return false;
	}
	lseek(hFile, 0, SEEK_SET);

// COMPRESSION_FORMAT_NONE
	// USHORT lpInBuffer = COMPRESSION_FORMAT_NONE;
	// DWORD lpBytesReturned = 0;
	// DeviceIoControl(hFile, FSCTL_SET_COMPRESSION, (LPVOID) &lpInBuffer,
	// 			sizeof(USHORT), NULL, 0, (LPDWORD)&lpBytesReturned, NULL);

// Fill Test Data
	char* buf = NULL;
	int BufSize;
	int Loop;
	int i;
	ssize_t writesize;
	BufSize = 1024 * 1024;
	Loop = (int)DiskTestSize;

	buf = (char*) malloc(BufSize);
	if (buf == NULL)
	{
		perror("malloc");
		((CDiskMarkDlg*) dlg)->m_DiskBenchStatus = false;
		close(hFile);
		return false;
	}

	if (((CDiskMarkDlg*) dlg)->m_TestData == TEST_DATA_ALL0X00)
	{
		memset(buf, 0, BufSize);
	}
	else
	{
		// Compatible with DiskSpd
		for (i = 0; i < BufSize; i++)
		{
			buf[i] = (char) (rand() % 256);
		}
	}

	for (i = 0; i < Loop; i++)
	{
		if (((CDiskMarkDlg*) dlg)->m_DiskBenchStatus)
		{
			writesize = write(hFile, buf, BufSize);
			if (writesize == -1)
			{
				perror("write");
				free(buf);
				close(hFile);
				((CDiskMarkDlg*) dlg)->m_DiskBenchStatus = false;
				return false;
			}
		}
		else
		{
			free(buf);
			close(hFile);
			((CDiskMarkDlg*) dlg)->m_DiskBenchStatus = false;
			return false;
		}
	}
	free(buf);
	close(hFile);

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

	if(((CDiskMarkDlg*)dlg)->m_TestData == TEST_DATA_ALL0X00)
	{
		cstr = ALL_0X00_0FILL;
	}

	QMetaObject::invokeMethod(((CDiskMarkDlg*)dlg), "OnUpdateMessage", Qt::QueuedConnection, Q_ARG(QString*, &cstr));
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

	if (((CDiskMarkDlg*) dlg)->m_TestData == TEST_DATA_ALL0X00)
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
			option = QString("--bs=%1K --iodepth=%2 --numjobs=%3 --direct=1 --rw=read").arg(BenchSize[index]).arg(BenchQueues[index]).arg(BenchThreads[index]);
			//option = QString("-b%1K -o%2 -t%3 -W0 -S -w0").arg(BenchSize[index]).arg(BenchQueues[index]).arg(BenchThreads[index]);
		}
		maxScore = &(((CDiskMarkDlg*) dlg)->m_ReadScore[index]);
		minLatency = &(((CDiskMarkDlg*)dlg)->m_ReadLatency[index]);
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
		maxScore = &(((CDiskMarkDlg*)dlg)->m_WriteScore[index]);
		minLatency = &(((CDiskMarkDlg*)dlg)->m_WriteLatency[index]);
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
	//option += QStringLiteral(" -ag");

	option += QStringLiteral(" --ioengine=posixaio --output-format=json+");

	double score = 0.0;
	double latency = 0.0;

	if (maxScore == NULL || minLatency == NULL)
	{
		return ;
	}
	*maxScore = 0.0;
	*minLatency = -1.0;

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
		QMetaObject::invokeMethod(static_cast<CDiskMarkDlg*>(dlg), "OnUpdateMessage", Qt::QueuedConnection, Q_ARG(QString*, &cstr));
		
		
		//command = QString::asprintf("\"%s\" %s -d%d -A%d -L \"%s\"", DiskSpdExe.toStdString().c_str(), option.toStdString().c_str(), duration, getpid(), TestFilePath.toStdString().c_str());
		command = QString::asprintf("%s %s --name=%s --size=%lldMi", "/opt/homebrew/bin/fio", option.toStdString().c_str(), TestFilePath.toStdString().c_str(), DiskTestSize);
		int ret = ExecAndWait(&command, true, &score, &latency);
		if (ret != 0)
		{
			ShowErrorMessage(command);
			return;
		}

		if (score > *maxScore)
		{
			*maxScore = score;
			QMetaObject::invokeMethod(static_cast<CDiskMarkDlg*>(dlg), "OnUpdateScore", Qt::QueuedConnection);
		}

		if (score > 0.0 && (latency < *minLatency || *minLatency < 0))
		{
			*minLatency = latency;
			QMetaObject::invokeMethod(static_cast<CDiskMarkDlg*>(dlg), "OnUpdateScore", Qt::QueuedConnection);
		}

		if (!((CDiskMarkDlg*) dlg)->m_DiskBenchStatus)
		{
			return;
		}
	}
	QMetaObject::invokeMethod(static_cast<CDiskMarkDlg*>(dlg), "OnUpdateScore", Qt::QueuedConnection);
}
