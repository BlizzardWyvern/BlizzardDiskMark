/*---------------------------------------------------------------------------*/
//       Author : hiyohiyo
//         Mail : hiyohiyo@crystalmark.info
//          Web : https://crystalmark.info/
//      License : MIT License
/*---------------------------------------------------------------------------*/

#pragma once

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

#include "../lib/resource.h"

#include "AboutDlg.h"
#include "DiskBench.h"
#include "SettingsDlg.h"
//#include "FontSelectionDlg.h"

//#include "../Priscilla/DialogFx.h"
//#include "../Priscilla/MainDialogFx.h"
//#include "ButtonFx.h"
//#include "../Priscilla/StaticFx.h"
//#include "ComboBoxFx.h"
//#include "EditFx.h"
//#include "UtilityFx.h"
//#include "OsInfoFx.h"

class CDiskMarkDlg : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString m_WindowTitle MEMBER m_WindowTitle NOTIFY m_WindowTitleChanged)
	Q_PROPERTY(CDiskMarkDlg::Profile m_Profile READ m_getProfile NOTIFY m_ProfileChanged)
	Q_PROPERTY(CDiskMarkDlg::TEST_DATA_TYPE m_TestData READ m_getTestData NOTIFY m_TestDataChanged)
	Q_PROPERTY(CDiskMarkDlg::BENCHMODE m_Benchmark READ m_getBenchmark NOTIFY m_BenchmarkChanged)

	Q_PROPERTY(QStringList m_DriveList MEMBER m_DriveList)
	Q_PROPERTY(int m_IndexTestCount MEMBER m_IndexTestCount)
	Q_PROPERTY(int m_IndexTestDrive MEMBER m_IndexTestDrive)
	Q_PROPERTY(long m_TestDriveLetter MEMBER m_TestDriveLetter)
	Q_PROPERTY(QString m_TestTargetPath MEMBER m_TestTargetPath)
	Q_PROPERTY(QString m_ValueTestCount MEMBER m_ValueTestCount NOTIFY m_ValueTestCountChanged)
	Q_PROPERTY(QString m_ValueTestSize MEMBER m_ValueTestSize NOTIFY m_ValueTestSizeChanged)
	Q_PROPERTY(QString m_ValueTestDrive MEMBER m_ValueTestDrive NOTIFY m_ValueTestDriveChanged)
	Q_PROPERTY(QString m_ValueTestUnit MEMBER m_ValueTestUnit NOTIFY m_ValueTestUnitChanged)

	Q_PROPERTY(QList<double> m_readScoreList READ m_readScoreList NOTIFY m_scoreChanged)
	Q_PROPERTY(QList<double> m_writeScoreList READ m_writeScoreList NOTIFY m_scoreChanged)
	Q_PROPERTY(QList<double> m_readLatencyList READ m_readLatencyList NOTIFY m_scoreChanged)
	Q_PROPERTY(QList<double> m_writeLatencyList READ m_writeLatencyList NOTIFY m_scoreChanged)
	Q_PROPERTY(QList<int> m_blockSizeList READ m_blockSizeList NOTIFY m_scoreChanged)

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

	QString m_WindowTitle;
	QString m_TestTargetPath;

	Profile m_getProfile() const;
	TEST_DATA_TYPE m_getTestData() const;
	BENCHMODE m_getBenchmark() const;

	QList<double> m_readScoreList() const;
	QList<double> m_writeScoreList() const;
	QList<double> m_readLatencyList() const;
	QList<double> m_writeLatencyList() const;
	QList<int> m_blockSizeList() const;

	void OnCbnSelchangeComboDrive();

signals:
	void m_WindowTitleChanged();
	void m_ProfileChanged();
	void m_TestDataChanged();
	void m_BenchmarkChanged();

	void m_ValueTestCountChanged();
	void m_ValueTestSizeChanged();
	void m_ValueTestDriveChanged();
	void m_ValueTestUnitChanged();

	void m_buttonsChanged();
	void m_scoreChanged();
	
	void m_DiskBenchStatusChanged();
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
	int m_IndexTestCount = 0;
	int m_IndexTestDrive;
	QString m_ValueTestSize;
	QString m_ValueTestDrive;

	QVector<double*> m_ReadScore;
	QVector<double*> m_WriteScore;
	QVector<double*> m_ReadLatency;
	QVector<double*> m_WriteLatency;

	QVector<int*> m_BenchType;
	int m_BenchSize[9];
	int m_BenchQueues[9];
	int m_BenchThreads[9];

	enum BENCH_TYPE
	{
		BENCH_SEQ = 0,
		BENCH_RND,
	};

	QThread* m_WinThread;
	volatile bool m_DiskBenchStatus;

	void UpdateScore();

#ifdef MIX_MODE
	double m_MixScore[9];
	double m_MixLatency[9];
#endif

	void SetMeter(int index, double score, double latency, int blockSize, int unit);
	void ChangeLang();
	// void resizeEvent(QResizeEvent* event) override;
	void ChangeButtonStatus(bool status);
	void SetScoreToolTip(QLabel* cx, double score, double latency, int blockSize);
	void UpdateThemeInfo();

	QString m_TestDriveInfo;
	long m_TestDriveLetter;

	int m_MaxIndexTestDrive;


	int m_IntervalTime;
	int m_MeasureTime;

	int m_TestData;
	int m_Profile;
	int m_Benchmark;

	int m_MarginButtonTop;
	int m_MarginButtonLeft;
	int m_MarginButtonBottom;
	int m_MarginButtonRight;
	int m_MarginMeterTop;
	int m_MarginMeterLeft;
	int m_MarginMeterBottom;
	int m_MarginMeterRight;
	int m_MarginCommentTop;
	int m_MarginCommentLeft;
	int m_MarginCommentBottom;
	int m_MarginCommentRight;
	int m_MarginDemoTop;
	int m_MarginDemoLeft;
	int m_MarginDemoBottom;
	int m_MarginDemoRight;

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
	void OnHelp();
	void OnBlizzardWorld();
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
	void UpdateUnitLabel();

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

	void OnUpdateMessage(QString* message);
	void OnUpdateScore();
	void OnExitBenchmark();

	void OnExit();
	void OnAbout();
	void OnSettings();
	void OnFontSetting();

	void OnBenchmarkReadWrite();
	void OnBenchmarkReadOnly();
	void OnBenchmarkWriteOnly();
protected:
	void SelectDrive();
	QString GetResultString(int type, double score, double latency, int size, int queues, int threads);
	QString GetButtonText(int type, int size, int queues, int threads, int unit) const;
	QString GetButtonToolTipText(int type, int size, int queues, int threads, int unit) const;
	
	QString m_TitleTestDrive;
	QString m_TitleTestCount;
	QString m_TitleTestSize;
	QString m_TitleTestQSize;

protected:
	QIcon m_hIcon;
	QIcon m_hIconMini;

	int m_SizeX;
	int m_SizeY;

	CAboutDlg*		m_AboutDlg;
	CSettingsDlg*	m_SettingsDlg;

	void SetControlFont();
	void InitDrive();
	void UpdateDriveToolTip();

	bool CheckRadioZoomType(int id, int value);
	void CheckRadioZoomType();
	void CheckRadioPresetMode();
	void UpdateQueuesThreads();

	void SaveText(QString fileName);

	void UpdateComboTooltip();

	virtual bool CheckThemeEdition(QString name);

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

	// void showEvent(QShowEvent* event) override;
	virtual void OnCancel();
	// void paintEvent(QPaintEvent* event) override;
	// void closeEvent(QCloseEvent* event) override;
	//LRESULT OnQueryEndSession(WPARAM wParam, LPARAM lParam);

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

	//afx_msg void OnCbnSelchangeComboMix();

	void BenchmarkReadWrite();
	void BenchmarkReadOnly();
	void BenchmarkWriteOnly();
};
