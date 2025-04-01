/*---------------------------------------------------------------------------*/
//       Author : hiyohiyo
//         Mail : hiyohiyo@crystalmark.info
//          Web : https://crystalmark.info/
//      License : MIT License
/*---------------------------------------------------------------------------*/

#pragma once

#define MAX_THREADS 64
#define MAX_QUEUES 512

#include <QMainWindow>
#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QThread>
#include <QCloseEvent>
#include <QShowEvent>
#include <QResizeEvent>
#include <QVector>
#include <QtQml/qqmlregistration.h>
#include <QQmlListProperty>
#include <QQmlEngine>

#include "DiskBench.h"
#include "SettingsDlg.h"

class CDiskMarkDlg : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString m_WindowTitle MEMBER m_WindowTitle NOTIFY m_WindowTitleChanged)
	Q_PROPERTY(CDiskMarkDlg::Profile m_Profile READ m_getProfile NOTIFY m_ProfileChanged)
	Q_PROPERTY(CDiskMarkDlg::TEST_DATA_TYPE m_TestData READ m_getTestData NOTIFY m_TestDataChanged)
	Q_PROPERTY(CDiskMarkDlg::BENCHMODE m_Benchmark READ m_getBenchmark NOTIFY m_BenchmarkChanged)

	Q_PROPERTY(QStringList m_DriveList MEMBER m_DriveList NOTIFY m_DriveListChanged)
	Q_PROPERTY(int m_IndexTestCount MEMBER m_IndexTestCount NOTIFY m_ValueTestCountChanged)
	Q_PROPERTY(int m_IndexTestDrive MEMBER m_IndexTestDrive NOTIFY m_ValueTestDriveChanged)
	Q_PROPERTY(QString m_TestTargetPath MEMBER m_TestTargetPath NOTIFY m_TestTargetPathChanged)
	Q_PROPERTY(QString m_ValueTestCount MEMBER m_ValueTestCount NOTIFY m_ValueTestCountChanged)
	Q_PROPERTY(QString m_ValueTestSize MEMBER m_ValueTestSize NOTIFY m_ValueTestSizeChanged)
	Q_PROPERTY(QString m_ValueTestDrive MEMBER m_ValueTestDrive NOTIFY m_ValueTestDriveChanged)
	Q_PROPERTY(QString m_ValueTestUnit MEMBER m_ValueTestUnit NOTIFY m_ValueTestUnitChanged)

	Q_PROPERTY(QList<double> m_readScoreList READ m_readScoreList NOTIFY m_scoreChanged)
	Q_PROPERTY(QList<double> m_writeScoreList READ m_writeScoreList NOTIFY m_scoreChanged)
	Q_PROPERTY(QList<double> m_readLatencyList READ m_readLatencyList NOTIFY m_scoreChanged)
	Q_PROPERTY(QList<double> m_writeLatencyList READ m_writeLatencyList NOTIFY m_scoreChanged)
	Q_PROPERTY(QList<double> m_ReadIops MEMBER m_ReadIops NOTIFY m_scoreChanged)
	Q_PROPERTY(QList<double> m_WriteIops MEMBER m_WriteIops NOTIFY m_scoreChanged)

	Q_PROPERTY(QList<int> m_benchTypeList READ m_benchTypeList NOTIFY m_DiskBenchStatusChanged)
	Q_PROPERTY(QList<int> m_blockSizeList READ m_blockSizeList NOTIFY m_DiskBenchStatusChanged)
	Q_PROPERTY(QList<int> m_benchQueuesList READ m_benchQueuesList NOTIFY m_DiskBenchStatusChanged)
	Q_PROPERTY(QList<int> m_benchThreadsList READ m_benchThreadsList NOTIFY m_DiskBenchStatusChanged)

	Q_PROPERTY(QStringList m_buttonTextList MEMBER m_buttonTextList NOTIFY m_buttonsChanged)
	Q_PROPERTY(QStringList m_buttonToolTipList MEMBER m_buttonToolTipList NOTIFY m_buttonsChanged)
	Q_PROPERTY(bool m_DiskBenchStatus MEMBER m_DiskBenchStatus NOTIFY m_DiskBenchStatusChanged)
	QML_ELEMENT

public:
	CDiskMarkDlg(QObject* parent = nullptr);
	~CDiskMarkDlg();

	enum Profile
	{
		PROFILE_DEFAULT = 0,
		PROFILE_PEAK,
		PROFILE_REAL,
		PROFILE_DEMO,
		PROFILE_DEFAULT_MIX,
		PROFILE_PEAK_MIX,
		PROFILE_REAL_MIX,
	};
	Q_ENUM(Profile)
	enum TEST_DATA_TYPE
	{
		TEST_DATA_RANDOM = 0,
		TEST_DATA_ALL0X00,
		TEST_DATA_ALL0XFF,
	};
	Q_ENUM(TEST_DATA_TYPE)
	enum SCORE_UNIT
	{
		SCORE_MBS = 0,
		SCORE_GBS,
		SCORE_IOPS,
		SCORE_US,
	};
	Q_ENUM(SCORE_UNIT)
	enum BENCHMODE
	{
		BENCH_READ = 1,
		BENCH_WRITE,
		BENCH_READ_WRITE,
	};
	Q_ENUM(BENCHMODE)
	enum BENCH_TYPE
	{
		BENCH_SEQ = 0,
		BENCH_RND,
	};
	Q_ENUM(BENCH_TYPE)

	QString m_WindowTitle = "";
	QString m_TestTargetPath;

	Profile m_getProfile() const;
	TEST_DATA_TYPE m_getTestData() const;
	BENCHMODE m_getBenchmark() const;

	QList<double> m_readScoreList() const;
	QList<double> m_writeScoreList() const;
	QList<double> m_readLatencyList() const;
	QList<double> m_writeLatencyList() const;

	QList<int> m_benchTypeList() const;
	QList<int> m_blockSizeList() const;
	QList<int> m_benchQueuesList() const;
	QList<int> m_benchThreadsList() const;

signals:
	void m_WindowTitleChanged();
	void m_ProfileChanged();
	void m_TestDataChanged();
	void m_BenchmarkChanged();

	void m_ValueTestCountChanged();
	void m_ValueTestSizeChanged();
	void m_ValueTestDriveChanged();
	void m_ValueTestUnitChanged();

	void m_DriveListChanged();
	void m_TestTargetPathChanged();

	void m_buttonsChanged();
	void m_scoreChanged();
	
	void m_DiskBenchStatusChanged();

	void error(const QString& message);
private:
	QString m_ValueTestCount;
	QString m_ValueTestUnit;

	int m_IndexTestUnit;

	QStringList m_DriveList;
	QStringList m_buttonTextList;
	QStringList m_buttonToolTipList;
	QStringList m_readScoreToolTipList;
	QStringList m_writeScoreToolTipList;

public:
	int m_IndexTestCount;
	int m_IndexTestDrive;
	QString m_ValueTestSize;
	QString m_ValueTestDrive;

	QVector<double*> m_ReadScore;
	QVector<double*> m_WriteScore;
	QVector<double*> m_ReadLatency;
	QVector<double*> m_WriteLatency;
	QList<double> m_ReadIops;
	QList<double> m_WriteIops;

	int m_BenchType[9];
	int m_BenchSize[9];
	int m_BenchQueues[9];
	int m_BenchThreads[9];

	QThread* m_WinThread;
	volatile bool m_DiskBenchStatus;

	void SetMeter(int index, double score, double latency, int blockSize, int unit);
	void ChangeLang();
	void ChangeButtonStatus(bool status);
	void SetScoreToolTip(QLabel* cx, double score, double latency, int blockSize);

	QString m_TestDriveInfo;

	int m_MaxIndexTestDrive;

	int m_IntervalTime;
	int m_MeasureTime;

	int m_TestData;
	int m_Profile;
	int m_Benchmark;

	bool m_AdminMode;
	bool m_MixMode;
	int m_MixRatio;

	// DIALOGFX
	QString m_FontFace;

	// Message //
	QString m_MesDiskCapacityError;
	QString m_MesDiskWriteError;
	QString m_MesDiskReadError;
	QString m_MesStopBenchmark;
	QString m_MesDiskCreateFileError;
	QString m_MesDiskSpdNotFound;

	void SetWindowTitle(QString message);

public slots:
	void OnCopy();
	void OnModeDefault();
	void OnModeAll0x00();
	void OnSettingDefault();
	void OnSettingNVMe8();
	// void OnSettingNVMe9();

	void OnProfileDefault();
	void OnProfilePeak();
	void OnProfileReal();
	void OnProfileDemo();
	void OnProfileDefaultMix();
	void OnProfilePeakMix();
	void OnProfileRealMix();

	void OnSaveText();
	void OnSaveImage();
	void OnSettingsQueuesThreads();

	void OnAll();
	void OnTest0();
	void OnTest1();
	void OnTest2();
	void OnTest3();
	void Stop();
	void OnSequentialPeak();
	void OnRandomPeak();
	void OnSequentialReal();
	void OnRandomReal();

	void OnUpdateScore();
	void OnExitBenchmark();

	void OnExit();
	void OnSettings();

	void OnBenchmarkReadWrite();
	void OnBenchmarkReadOnly();
	void OnBenchmarkWriteOnly();
protected:
	QString GetResultString(int type, double score, double latency, int size, int queues, int threads);
	
	QString m_TitleTestDrive;
	QString m_TitleTestCount;
	QString m_TitleTestSize;
	QString m_TitleTestQSize;

protected:
	CSettingsDlg*	m_SettingsDlg;

	void InitDrive();

	void CheckRadioPresetMode();
	void UpdateQueuesThreads();

	void SaveText(QString fileName);

	void UpdateComboTooltip();

	bool IsDefaultMode();
	bool IsNVMe8Mode();
//	BOOL IsNVMe9Mode();

#ifdef MIX_MODE
	QLabel* m_TestMix0;
	QLabel* m_TestMix1;
	QLabel* m_TestMix2;
	QLabel* m_TestMix3;
	QLabel* m_MixUnit;
	QComboBox* m_ComboMix;
#endif

	QPushButton* m_ButtonAll;
	QPushButton* m_ButtonTest0;
	QPushButton* m_ButtonTest1;
	QPushButton* m_ButtonTest2;
	QPushButton* m_ButtonTest3;

	QLabel* m_TestRead0;
	QLabel* m_TestRead1;
	QLabel* m_TestRead2;
	QLabel* m_TestRead3;

	QLabel* m_TestWrite0;
	QLabel* m_TestWrite1;
	QLabel* m_TestWrite2;
	QLabel* m_TestWrite3;

	QLineEdit* m_Comment;

	QComboBox* m_ComboCount;
	QComboBox* m_ComboSize;
	QComboBox* m_ComboDrive;
	QComboBox* m_ComboUnit;

	QLabel* m_WriteUnit;
	QLabel* m_ReadUnit;
	QLabel* m_DemoSetting;

public:
	void ProfileDefault();
	void ProfilePeak();
	void ProfileReal();
	void ProfileDemo();
	void ProfileDefaultMix();
	void ProfilePeakMix();
	void ProfileRealMix();

	void InitScore();

	void SettingsQueuesThreads(int type);

	void BenchmarkReadWrite();
	void BenchmarkReadOnly();
	void BenchmarkWriteOnly();
};
