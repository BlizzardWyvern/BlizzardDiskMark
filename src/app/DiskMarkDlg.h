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

class CDiskMarkDlg : public QMainWindow
{
	Q_OBJECT
public:
	CDiskMarkDlg(QWidget* pParent = nullptr);
	~CDiskMarkDlg();

	enum { IDD = IDD_DISKMARK_DIALOG };

	enum SCORE_UNIT
	{
		SCORE_MBS = 0,
		SCORE_GBS,
		SCORE_IOPS,
		SCORE_US,
	};

	enum BENCH_TYPE
	{
		BENCH_SEQ = 0,
		BENCH_RND,
	};

	QThread* m_WinThread;
	volatile bool m_DiskBenchStatus;

	void InitScore();
	void UpdateScore();

	double m_ReadScore[9];
	double m_WriteScore[9];
	double m_ReadLatency[9];
	double m_WriteLatency[9];

#ifdef MIX_MODE
	double m_MixScore[9];
	double m_MixLatency[9];
#endif

	void SetMeter(QLabel* control, double score, double latency, int blockSize, int unit);
	void ChangeLang();
	void resizeEvent(QResizeEvent* event) override;
	void ChangeButtonStatus(bool status);
	void SetScoreToolTip(QLabel* cx, double score, double latency, int blockSize);
	void UpdateThemeInfo();

	QString m_ValueTestUnit;
	QString m_ValueTestCount;
	QString m_ValueTestSize;
	QString m_ValueTestDrive;
	QString m_TestDriveInfo;
	QString m_TestTargetPath;
	long m_TestDriveLetter;

	int m_MaxIndexTestDrive;
	int m_IndexTestUnit;
	int m_IndexTestCount;
	int m_IndexTestSize;
	int m_IndexTestDrive;
	int m_IndexTestMix;

	int m_BenchType[9];
	int m_BenchSize[9];
	int m_BenchQueues[9];
	int m_BenchThreads[9];
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
	//virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

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

	void OnCbnSelchangeComboCount(int);
	void OnCbnSelchangeComboSize(int);
	void OnCbnSelchangeComboDrive(int);
	void OnCbnSelchangeComboUnit(int);

	void OnUpdateMessage(QString* message);
	void OnUpdateScore();
	void OnExitBenchmark();

	void OnExit();
	void OnAbout();
	void OnSettings();
protected:
	void SelectDrive();
	QString GetResultString(int type, double score, double latency, int size, int queues, int threads);
	QString GetButtonText(int type, int size, int queues, int threads, int unit);
	QString GetButtonToolTipText(int type, int size, int queues, int threads, int unit);
	
	QString m_TitleTestDrive;
	QString m_TitleTestCount;
	QString m_TitleTestSize;
	QString m_TitleTestQSize;

protected:
	QIcon m_hIcon;
	QIcon m_hIconMini;
	//HACCEL m_hAccelerator;

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

	void EnableMenus();
	void DisableMenus();

	void SaveText(QString fileName);

	//void SetLayeredWindow(HWND hWnd, BYTE alpha);
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

	void showEvent(QShowEvent* event) override;
	virtual void OnOK();
	virtual void OnCancel();
	//virtual bool OnCommand(WPARAM wParam, LPARAM lParam);
	//virtual bool PreTranslateMessage(MSG* pMsg);

	void paintEvent(QPaintEvent* event) override;
	//afx_msg QCursor OnQueryDragIcon();
	
	void closeEvent(QCloseEvent* event) override;
	//afx_msg void OnFontSetting();

	//LRESULT OnQueryEndSession(WPARAM wParam, LPARAM lParam);

public:
	//afx_msg void OnCopy();
	//afx_msg void OnHelp();
	//afx_msg void OnCrystalDewWorld();
	void OnModeDefault();
	void OnModeAll0x00();
	//afx_msg void OnSettingDefault();
	//afx_msg void OnSettingNVMe8();
//	afx_msg void OnSettingNVMe9();

	//afx_msg void OnProfileDefault();
	//afx_msg void OnProfilePeak();
	//afx_msg void OnProfileReal();
	//afx_msg void OnProfileDemo();
	//afx_msg void OnSaveText();
	//afx_msg void OnSaveImage();
	//afx_msg void OnSettingsQueuesThreads();
	void UpdateUnitLabel();
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	void ProfileDefault();
	void ProfilePeak();
	void ProfileReal();
	void ProfileDemo();

	void SettingsQueuesThreads(int type);

#ifdef MIX_MODE
	//afx_msg void OnProfileDefaultMix();
	//afx_msg void OnProfilePeakMix();
	//afx_msg void OnProfileRealMix();
	void ProfileDefaultMix();
	void ProfilePeakMix();
	void ProfileRealMix();
	//afx_msg void OnCbnSelchangeComboMix();
#endif

	//afx_msg void OnBenchmarkReadWrite();
	//afx_msg void OnBenchmarkReadOnly();
	//afx_msg void OnBenchmarkWriteOnly();
	void BenchmarkReadWrite();
	void BenchmarkReadOnly();
	void BenchmarkWriteOnly();
};
