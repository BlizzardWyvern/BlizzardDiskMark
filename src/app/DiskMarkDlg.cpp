/*---------------------------------------------------------------------------*/
//       Author : hiyohiyo
//         Mail : hiyohiyo@crystalmark.info
//          Web : https://crystalmark.info/
//      License : MIT License
/*---------------------------------------------------------------------------*/

#include "DiskMarkDlg.h"
#include "DiskBench.h"
#include "../lib/stdafx.h"

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

	// InitThemeLang();
	// InitMenu();
	UpdateThemeInfo();
	ChangeLang();

	// Drive
	InitDrive();
	InitScore();
	UpdateUnitLabel();
	UpdateQueuesThreads();
	//UpdateDialogSize();
	ChangeButtonStatus(true);

	UpdateScore();

// #ifdef MIX_MODE
// 	m_ComboMix = new QComboBox(this);
// 	connect(m_ComboMix, SIGNAL(currentIndexChanged(int)), this, SLOT(OnCbnSelchangeComboMix(int)));
// #endif

// 	m_DemoSetting = new QLabel(this);

// 	m_AboutDlg = nullptr;
// 	m_SettingsDlg = nullptr;

	//m_DefaultTheme = L"Default";
	//m_ThemeKeyName = L"Theme";

	// m_MarginDemoTop = 8;
	// m_MarginDemoLeft = 8;
	// m_MarginDemoBottom = 8;
	// m_MarginDemoRight = 8;

	//m_BackgroundName = L"Background";
	//m_RandomThemeLabel = L"Random";
	//m_RandomThemeName = L"";
}


void CDiskMarkDlg::UpdateThemeInfo()
{
// 	//CMainDialogFx::UpdateThemeInfo();

// 	//QString theme = m_ThemeDir + m_CurrentTheme + L"\\theme.ini";

// 	//m_MarginButtonTop = GetPrivateProfileInt(L"Margin", L"ButtonTop", 4, theme);
// 	//m_MarginButtonLeft = GetPrivateProfileInt(L"Margin", L"ButtonLeft", 0, theme);
// 	// m_MarginButtonBottom = GetPrivateProfileInt(L"Margin", L"ButtonBottom", 4, theme);
// 	// m_MarginButtonRight = GetPrivateProfileInt(L"Margin", L"ButtonRight", 0, theme);
// 	// m_MarginMeterTop = GetPrivateProfileInt(L"Margin", L"MeterTop", 0, theme);
// 	// m_MarginMeterLeft = GetPrivateProfileInt(L"Margin", L"MeterLeft", 0, theme);
// 	// m_MarginMeterBottom = GetPrivateProfileInt(L"Margin", L"MeterBottom", 0, theme);
// 	// m_MarginMeterRight = GetPrivateProfileInt(L"Margin", L"MeterRight", 4, theme);
// 	// m_MarginCommentTop = GetPrivateProfileInt(L"Margin", L"CommentTop", 0, theme);
// 	// m_MarginCommentLeft = GetPrivateProfileInt(L"Margin", L"CommentLeft", 8, theme);
// 	// m_MarginCommentBottom = GetPrivateProfileInt(L"Margin", L"CommentBottom", 0, theme);
// 	// m_MarginCommentRight = GetPrivateProfileInt(L"Margin", L"CommentRight", 8, theme);
// 	// m_MarginDemoTop = GetPrivateProfileInt(L"Margin", L"DemoTop", 8, theme);
// 	// m_MarginDemoLeft = GetPrivateProfileInt(L"Margin", L"DemoLeft", 8, theme);
// 	// m_MarginDemoBottom = GetPrivateProfileInt(L"Margin", L"DemoBottom", 8, theme);
// 	// m_MarginDemoRight = GetPrivateProfileInt(L"Margin", L"DemoRight", 8, theme);
}


CDiskMarkDlg::~CDiskMarkDlg()
{
}


bool CDiskMarkDlg::CheckThemeEdition(QString name)
{
// 	if(name.startsWith(QStringLiteral("Shizuku")) || name.startsWith(QStringLiteral("Aoi")) || name.startsWith(QStringLiteral("MSIMei")) || name.startsWith(QStringLiteral("Tokka")) || name.startsWith(QStringLiteral("KureiKei")) || name.startsWith(QStringLiteral("."))) { return true; }

  return false;
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

// void CDiskMarkDlg::showEvent(QShowEvent* event)
// {
// 	QMainWindow::showEvent(event);

// 	setWindowIcon(m_hIcon);
// // 	//setWindowIcon(m_hIconMini);

// 	char str[256];
// // 	// if (hasDefaultFont)
// // 	// {
// // 	// 	defaultFontFace = DEFAULT_FONT_FACE_1;
// // 	// }
// // 	// else
// // 	// {
// // 	// 	defaultFontFace = DEFAULT_FONT_FACE_2;
// // 	// }

// // 	// GetPrivateProfileString(L"Setting", L"FontFace", defaultFontFace, str, 256, m_Ini);
// 	m_FontFace = str;

// // 	// m_TestData = GetPrivateProfileInt(L"Setting", L"TestData", TEST_DATA_RANDOM, m_Ini);
// 	if (m_TestData != TEST_DATA_ALL0X00)
// 	{
// 		m_TestData = TEST_DATA_RANDOM;
// 	}

// // 	// m_Profile = GetPrivateProfileInt(L"Setting", L"Profile", PROFILE_DEFAULT, m_Ini);

// #ifdef MIX_MODE
// 	if (PROFILE_DEFAULT > m_Profile || m_Profile > PROFILE_REAL_MIX)
// #else
// 	if (PROFILE_DEFAULT > m_Profile || m_Profile > PROFILE_DEMO)
// #endif
// 	{
// 		m_Profile = PROFILE_DEFAULT;
// 	}

// // // 	m_Benchmark = GetPrivateProfileInt(L"Setting", L"Benchmark", BENCHMARK_READ_WRITE, m_Ini);

// 	if (m_Profile == PROFILE_DEFAULT_MIX || m_Profile == PROFILE_PEAK_MIX || m_Profile == PROFILE_REAL_MIX)
// 	{
// 		m_MixMode = true;
// 	}
// 	else
// 	{
// 		m_MixMode = false;
// 	}

// // // 	m_FontScale = GetPrivateProfileInt(L"Setting", L"FontScale", 100, m_Ini);
// // // 	if (m_FontScale > 200 || m_FontScale < 50)
// // // 	{
// // // 		m_FontScale = 100;
// // // 		m_FontRatio = 1.0;
// // // 	}
// // // 	else
// // // 	{
// // // 		m_FontRatio = m_FontScale / 100.0;
// // // 	}

// // // 	m_FontRender = GetPrivateProfileInt(L"Setting", L"FontRender", CLEARTYPE_NATURAL_QUALITY, m_Ini);
// // // 	if (m_FontRender > CLEARTYPE_NATURAL_QUALITY)
// // // 	{
// // // 		m_FontRender = CLEARTYPE_NATURAL_QUALITY;
// // // 	}

// #ifdef MIX_MODE
// 	// Mix
// 	for (int i = 1; i < 10; i++)
// 	{
// 		CString cstr;
// 		cstr.Format(L"R%d%%/W%d%%", i * 10, 100 - i*10);
// 		m_ComboMix.AddString(cstr);
// 	}
// #endif

// // 	// m_IndexTestCount = GetPrivateProfileInt(L"Setting", L"TestCount", 4, m_Ini);
// // 	m_IndexTestSize = GetPrivateProfileInt(L"Setting", L"TestSize", 6, m_Ini);
// // 	// m_IndexTestUnit = GetPrivateProfileInt(L"Setting", L"TestUnit", 0, m_Ini);

// // 	// m_IndexTestMix = GetPrivateProfileInt(L"Setting", L"TestMix", 6, m_Ini);
// 	if (m_IndexTestMix < 0 || m_IndexTestMix > 10)
// 	{
// 		m_IndexTestMix = 6;	// default retio is R70W30;
// 	}
// 	m_MixRatio = (9 - m_IndexTestMix) * 10;

// #ifdef MIX_MODE
// 	m_ComboMix.SetCurSel(m_IndexTestMix);
// #endif

// #ifdef MIX_MODE
// 	if (m_MixMode)
// 	{
// 		m_SizeX = SIZE_X_MIX;
// 	}
// #endif

// 	setWindowTitle("");

// // 	// m_bShowWindow = true;

// // 	//m_bInitializing = FALSE;
// }

// void CDiskMarkDlg::resizeEvent(QResizeEvent* event)
// {
// 	QMainWindow::resizeEvent(event);
// // 	CDialogFx::UpdateDialogSize();
// // 	m_bHighContrast = FALSE;

// // 	ShowWindow(SW_HIDE);
// #ifdef MIX_MODE
// 	if (m_MixMode)
// 	{
// 		m_SizeX = SIZE_X_MIX;
// 	}
// #endif

// // 	UpdateBackground(TRUE, m_bDarkMode);
// // 	SetControlFont();

// 	if (m_Profile != PROFILE_DEFAULT && m_Profile != PROFILE_DEFAULT_MIX)
// 	{
// 		comboDriveX = 72;
// 	}
// 	else
// 	{
// 		comboDriveX = 0;
// 	}

// 	// m_TestRead0.SetDrawFrame(m_bHighContrast);
// 	// m_TestRead1.SetDrawFrame(m_bHighContrast);
// 	// m_TestRead2.SetDrawFrame(m_bHighContrast);
// 	// m_TestRead3.SetDrawFrame(m_bHighContrast);
// 	// m_TestWrite0.SetDrawFrame(m_bHighContrast);
// 	// m_TestWrite1.SetDrawFrame(m_bHighContrast);
// 	// m_TestWrite2.SetDrawFrame(m_bHighContrast);
// 	// m_TestWrite3.SetDrawFrame(m_bHighContrast);
// 	// m_Comment.SetDrawFrame(m_bHighContrast);

// #ifdef MIX_MODE
// 	m_TestMix0.SetDrawFrame(m_bHighContrast);
// 	m_TestMix1.SetDrawFrame(m_bHighContrast);
// 	m_TestMix2.SetDrawFrame(m_bHighContrast);
// 	m_TestMix3.SetDrawFrame(m_bHighContrast);
// #endif

// 	if (m_Profile == PROFILE_DEMO)
// 	{
// 		m_DemoSetting->show();
// 	}
// 	else
// 	{
// 		m_DemoSetting->hide();
// 	}

// 	if (m_Profile == PROFILE_DEMO)
// 	{
// 		// m_TestRead0.SetDrawFrameEx(TRUE, m_Frame);
// 		// m_TestWrite0.SetDrawFrameEx(TRUE, m_Frame);

// 		m_ButtonAll->setGeometry(8 + offsetX, 8, 72, 48);

// // 		m_TestRead0.SetGlassColor(m_Glass, m_GlassAlpha);
// // 		m_TestWrite0.SetGlassColor(m_Glass, m_GlassAlpha);

// 		m_TestRead0->setGeometry(8 + offsetX, 64, 228, 196);
// 		m_TestWrite0->setGeometry(244 + offsetX, 64, 228, 196);

// 		// m_Comment.Adjust(); // Removed invalid method call

// 		m_DemoSetting->setGeometry(84 + offsetX, 36, 320, 24);
// 	}
// 	else
// 	{
// 		if (m_MixMode)
// 		{
// 			m_Comment->setGeometry(8 + offsetX, 268, 664, 24);
// 		}
// 		else
// 		{
// 			m_Comment->setGeometry(8 + offsetX, 268, 464, 24);
// 		}
// // 		m_Comment.Adjust();

// 		if (m_Profile == PROFILE_PEAK || m_Profile == PROFILE_REAL || m_Profile == PROFILE_PEAK_MIX || m_Profile == PROFILE_REAL_MIX)
// 		{
// 			m_ComboDrive->setGeometry(212 + offsetX, 8, 260, 30);
// 		}
// 		else
// 		{
// 			m_ComboDrive->setGeometry(212 + offsetX, 8, 188, 30);
// 		}
// 	}

// #ifdef MIX_MODE
// // 	m_TestMix0.InitControl(480 + offsetX, 60, 192, 48, m_ZoomRatio,  &m_BkDC, IP(L"Meter"), 2, SS_RIGHT, OwnerDrawImage, m_bHighContrast, FALSE, FALSE);
// // 	m_TestMix1.InitControl(480 + offsetX, 112, 192, 48, m_ZoomRatio, &m_BkDC, IP(L"Meter"), 2, SS_RIGHT, OwnerDrawImage, m_bHighContrast, FALSE, FALSE);
// // 	m_TestMix2.InitControl(480 + offsetX, 164, 192, 48, m_ZoomRatio, &m_BkDC, IP(L"Meter"), 2, SS_RIGHT, OwnerDrawImage, m_bHighContrast, FALSE, FALSE);
// // 	m_TestMix3.InitControl(480 + offsetX, 216, 192, 48, m_ZoomRatio, &m_BkDC, IP(L"Meter"), 2, SS_RIGHT, OwnerDrawImage, m_bHighContrast, FALSE, FALSE);
// // 	m_ComboMix.InitControl(480 + offsetX, 8, 192, 300, m_ZoomRatio,  &m_BkDC, NULL, 0, ES_LEFT, OwnerDrawGlass, m_bHighContrast, FALSE, m_ComboBk, m_ComboBkSelected, m_Glass, m_GlassAlpha);
// // 	m_MixUnit.InitControl(480 + offsetX, 36, 192, 24, m_ZoomRatio,   &m_BkDC, NULL, 0, SS_CENTER, OwnerDrawTransparent, m_bHighContrast, FALSE, FALSE);

// // 	m_TestMix0.SetMargin(m_MarginMeterTop, m_MarginMeterLeft, m_MarginMeterBottom, m_MarginMeterRight, m_ZoomRatio);
// // 	m_TestMix1.SetMargin(m_MarginMeterTop, m_MarginMeterLeft, m_MarginMeterBottom, m_MarginMeterRight, m_ZoomRatio);
// // 	m_TestMix2.SetMargin(m_MarginMeterTop, m_MarginMeterLeft, m_MarginMeterBottom, m_MarginMeterRight, m_ZoomRatio);
// // 	m_TestMix3.SetMargin(m_MarginMeterTop, m_MarginMeterLeft, m_MarginMeterBottom, m_MarginMeterRight, m_ZoomRatio);
// // 	m_ComboMix.SetMargin(0, 4, 0, 0, m_ZoomRatio);

// // 	if (m_MixMode)
// // 	{
// // 		m_TestMix0.ShowWindow(SW_SHOW);
// // 		m_TestMix1.ShowWindow(SW_SHOW);
// // 		m_TestMix2.ShowWindow(SW_SHOW);
// // 		m_TestMix3.ShowWindow(SW_SHOW);
// // 		m_ComboMix.ShowWindow(SW_SHOW);
// // 		m_MixUnit.ShowWindow(SW_SHOW);
// // 	}
// // 	else
// // 	{
// // 		m_TestMix0.ShowWindow(SW_HIDE);
// // 		m_TestMix1.ShowWindow(SW_HIDE);
// // 		m_TestMix2.ShowWindow(SW_HIDE);
// // 		m_TestMix3.ShowWindow(SW_HIDE);
// // 		m_ComboMix.ShowWindow(SW_HIDE);
// // 		m_MixUnit.ShowWindow(SW_HIDE);
// // 	}
// #endif

// // 	m_Comment.Adjust();

// 	UpdateScore();

// 	m_ComboCount->hide();
// 	m_ComboSize->hide();
// 	m_ComboDrive->hide();

// // 	COMBOBOXINFO info = { 0 };
// // 	info.cbSize = sizeof(COMBOBOXINFO);
// // 	m_ComboCount.GetComboBoxInfo(&info);
// // 	SetLayeredWindow(info.hwndList, m_ComboAlpha);
// // 	m_ComboSize.GetComboBoxInfo(&info);
// // 	SetLayeredWindow(info.hwndList, m_ComboAlpha);
// // 	m_ComboDrive.GetComboBoxInfo(&info);
// // 	SetLayeredWindow(info.hwndList, m_ComboAlpha);
// 	// m_ComboUnit->comboBoxInfo(&info);
// // 	SetLayeredWindow(info.hwndList, m_ComboAlpha);
// #ifdef MIX_MODE
// // 	if (m_MixMode)
// // 	{
// // 		m_ComboMix.GetComboBoxInfo(&info);
// // 		SetLayeredWindow(info.hwndList, m_ComboAlpha);
// // 		m_ComboMix.ShowWindow(SW_SHOW);
// // 	}
// #endif

// 	m_ComboCount->show();
// 	m_ComboSize->show();
// 	m_ComboDrive->show();

// 	UpdateComboTooltip();

// 	// ShowWindow(SW_SHOW);
// }


void CDiskMarkDlg::SetControlFont()
{
// #ifdef SUISHO_SHIZUKU_SUPPORT
// 	BYTE textAlpha = 255;
// 	COLORREF textColor = RGB(0, 0, 0);
// #else
// 	std::byte textAlpha = std::byte{255};
// 	QColor textColor = QColor(0, 0, 0);
// #endif

// #ifdef SUISHO_SHIZUKU_SUPPORT
// 	m_ButtonAll.SetFontEx(m_FontFace, 28, 28, m_ZoomRatio, m_FontRatio, m_ButtonText, FW_BOLD, m_FontRender);
// 	m_ButtonTest0.SetFontEx(m_FontFace, 20, 20, m_ZoomRatio, m_FontRatio, m_ButtonText, FW_BOLD, m_FontRender);
// 	m_ButtonTest1.SetFontEx(m_FontFace, 20, 20, m_ZoomRatio, m_FontRatio, m_ButtonText, FW_BOLD, m_FontRender);
// 	m_ButtonTest2.SetFontEx(m_FontFace, 20, 20, m_ZoomRatio, m_FontRatio, m_ButtonText, FW_BOLD, m_FontRender);
// 	m_ButtonTest3.SetFontEx(m_FontFace, 20, 20, m_ZoomRatio, m_FontRatio, m_ButtonText, FW_BOLD, m_FontRender);

// 	if (m_Profile == PROFILE_DEMO)
// 	{
// 		m_TestRead0.SetFontEx(m_FontFace, 80, 28, m_ZoomRatio, m_FontRatio, m_MeterText, FW_BOLD, m_FontRender);
// 		m_TestWrite0.SetFontEx(m_FontFace,80, 28, m_ZoomRatio, m_FontRatio, m_MeterText, FW_BOLD, m_FontRender);
// 	}
// 	else
// 	{
// 		m_TestRead0.SetFontEx(m_FontFace, 52, 28, m_ZoomRatio, m_FontRatio, m_MeterText, FW_BOLD, m_FontRender);
// 		m_TestWrite0.SetFontEx(m_FontFace, 52, 28, m_ZoomRatio, m_FontRatio, m_MeterText, FW_BOLD, m_FontRender);
// 	}

// // 	m_TestRead1.SetFontEx(m_FontFace, 52, 28, m_ZoomRatio, m_FontRatio, m_MeterText, FW_BOLD, m_FontRender);
// // 	m_TestRead2.SetFontEx(m_FontFace, 52, 28, m_ZoomRatio, m_FontRatio, m_MeterText, FW_BOLD, m_FontRender);
// // 	m_TestRead3.SetFontEx(m_FontFace, 52, 28, m_ZoomRatio, m_FontRatio, m_MeterText, FW_BOLD, m_FontRender);

// // 	m_TestWrite1.SetFontEx(m_FontFace, 52, 28, m_ZoomRatio, m_FontRatio, m_MeterText, FW_BOLD, m_FontRender);
// // 	m_TestWrite2.SetFontEx(m_FontFace, 52, 28, m_ZoomRatio, m_FontRatio, m_MeterText, FW_BOLD, m_FontRender);
// // 	m_TestWrite3.SetFontEx(m_FontFace, 52, 28, m_ZoomRatio, m_FontRatio, m_MeterText, FW_BOLD, m_FontRender);

// // 	m_Comment.SetFontEx(m_FontFace, 28, 28, m_ZoomRatio, m_FontRatio, m_EditText, FW_BOLD, m_FontRender);

// // 	m_ReadUnit.SetFontEx(m_FontFace, 28, 28, m_ZoomRatio, m_FontRatio, m_LabelText, FW_BOLD, m_FontRender);
// // 	m_WriteUnit.SetFontEx(m_FontFace, 28, 28, m_ZoomRatio, m_FontRatio, m_LabelText, FW_BOLD, m_FontRender);
// // 	m_DemoSetting.SetFontEx(m_FontFace, 28, 28, m_ZoomRatio, m_FontRatio, m_MeterText, FW_BOLD, m_FontRender);

// // 	m_ComboCount.SetFontEx(m_FontFace, 28, 28, m_ZoomRatio, m_FontRatio, m_ComboText, m_ComboTextSelected, FW_NORMAL, m_FontRender);
// // 	m_ComboSize.SetFontEx(m_FontFace, 28, 28, m_ZoomRatio, m_FontRatio, m_ComboText, m_ComboTextSelected, FW_NORMAL, m_FontRender);
// // 	m_ComboDrive.SetFontEx(m_FontFace, 28, 28, m_ZoomRatio, m_FontRatio, m_ComboText, m_ComboTextSelected, FW_NORMAL, m_FontRender);
// // 	m_ComboUnit.SetFontEx(m_FontFace, 28, 28, m_ZoomRatio, m_FontRatio, m_ComboText, m_ComboTextSelected, FW_NORMAL, m_FontRender);

// // 	m_ButtonTest0.SetMargin(m_MarginButtonTop, m_MarginButtonLeft, m_MarginButtonBottom, m_MarginButtonRight, m_ZoomRatio);
// // 	m_ButtonTest1.SetMargin(m_MarginButtonTop, m_MarginButtonLeft, m_MarginButtonBottom, m_MarginButtonRight, m_ZoomRatio);
// // 	m_ButtonTest2.SetMargin(m_MarginButtonTop, m_MarginButtonLeft, m_MarginButtonBottom, m_MarginButtonRight, m_ZoomRatio);
// // 	m_ButtonTest3.SetMargin(m_MarginButtonTop, m_MarginButtonLeft, m_MarginButtonBottom, m_MarginButtonRight, m_ZoomRatio);

// // 	m_ComboCount.SetItemHeightAll(40, m_ZoomRatio, m_FontRatio);
// // 	m_ComboSize.SetItemHeightAll(40, m_ZoomRatio, m_FontRatio);
// // 	m_ComboDrive.SetItemHeightAll(40, m_ZoomRatio, m_FontRatio);
// // 	m_ComboUnit.SetItemHeightAll(40, m_ZoomRatio, m_FontRatio);
// #else
// 	QFont font;
// 	font.setFamily(m_FontFace);
// 	font.setPointSize(16);
// 	font.setBold(true);

// 	m_ButtonAll->setFont(font);
// 	m_ButtonTest0->setFont(font);
// 	m_ButtonTest1->setFont(font);
// 	m_ButtonTest2->setFont(font);
// 	m_ButtonTest3->setFont(font);

// 	if (m_Profile == PROFILE_DEMO)
// 	{
// 		m_TestRead0->setFont(QFont(m_FontFace, 48, QFont::Bold));
// 		m_TestWrite0->setFont(QFont(m_FontFace, 48, QFont::Bold));
// 	}
// 	else
// 	{
// 		m_TestRead0->setFont(QFont(m_FontFace, 35, QFont::Bold));
// 		m_TestWrite0->setFont(QFont(m_FontFace, 35, QFont::Bold));
// 	}

// 	m_TestRead1->setFont(QFont(m_FontFace, 35, QFont::Bold));
// 	m_TestRead2->setFont(QFont(m_FontFace, 35, QFont::Bold));
// 	m_TestRead3->setFont(QFont(m_FontFace, 35, QFont::Bold));

// 	m_TestWrite1->setFont(QFont(m_FontFace, 35, QFont::Bold));
// 	m_TestWrite2->setFont(QFont(m_FontFace, 35, QFont::Bold));
// 	m_TestWrite3->setFont(QFont(m_FontFace, 35, QFont::Bold));

// 	m_Comment->setFont(QFont(m_FontFace, 16, QFont::Bold));

// 	m_ReadUnit->setFont(QFont(m_FontFace, 16, QFont::Bold));
// 	m_WriteUnit->setFont(QFont(m_FontFace, 16, QFont::Bold));
// 	m_DemoSetting->setFont(QFont(m_FontFace, 16, QFont::Bold));

// 	m_ComboCount->setFont(QFont(m_FontFace, 16));
// 	m_ComboSize->setFont(QFont(m_FontFace, 16));
// 	m_ComboDrive->setFont(QFont(m_FontFace, 16));
// 	m_ComboUnit->setFont(QFont(m_FontFace, 16));

// // 	m_ButtonTest0.SetMargin(m_MarginButtonTop, m_MarginButtonLeft, m_MarginButtonBottom, m_MarginButtonRight, m_ZoomRatio);
// // 	m_ButtonTest1.SetMargin(m_MarginButtonTop, m_MarginButtonLeft, m_MarginButtonBottom, m_MarginButtonRight, m_ZoomRatio);
// // 	m_ButtonTest2.SetMargin(m_MarginButtonTop, m_MarginButtonLeft, m_MarginButtonBottom, m_MarginButtonRight, m_ZoomRatio);
// // 	m_ButtonTest3.SetMargin(m_MarginButtonTop, m_MarginButtonLeft, m_MarginButtonBottom, m_MarginButtonRight, m_ZoomRatio);

// // 	m_ComboCount.SetItemHeightAll(24, m_ZoomRatio, m_FontRatio);
// // 	m_ComboSize.SetItemHeightAll(24, m_ZoomRatio, m_FontRatio);
// // 	m_ComboDrive.SetItemHeightAll(24, m_ZoomRatio, m_FontRatio);
// // 	m_ComboUnit.SetItemHeightAll(24, m_ZoomRatio, m_FontRatio);

// #ifdef MIX_MODE
// // 	if(m_MixMode)
// // 	{
// // 		m_ComboMix.SetFontEx(m_FontFace, 16, 16, m_ZoomRatio, m_FontRatio, m_ComboText, m_ComboTextSelected, FW_NORMAL, m_FontRender);
// // 		m_ComboMix.SetItemHeightAll(24, m_ZoomRatio, m_FontRatio);

// // 		m_MixUnit.SetFontEx(m_FontFace, 16, 16, m_ZoomRatio, m_FontRatio, m_LabelText, FW_BOLD, m_FontRender);

// // 		m_TestMix0.SetFontEx(m_FontFace, 35, 35, m_ZoomRatio, m_FontRatio, m_MeterText, FW_BOLD, m_FontRender);
// // 		m_TestMix1.SetFontEx(m_FontFace, 35, 35, m_ZoomRatio, m_FontRatio, m_MeterText, FW_BOLD, m_FontRender);
// // 		m_TestMix2.SetFontEx(m_FontFace, 35, 35, m_ZoomRatio, m_FontRatio, m_MeterText, FW_BOLD, m_FontRender);
// // 		m_TestMix3.SetFontEx(m_FontFace, 35, 35, m_ZoomRatio, m_FontRatio, m_MeterText, FW_BOLD, m_FontRender);
// // 	}
// #endif

// #endif

}

void CDiskMarkDlg::UpdateQueuesThreads()
{
	QString cstr;

	int type[9] =   {    0,    0,  1, 1,    0,  1,    0, 1,    0 };
	int size[9] =   { 1024, 1024,  4, 4, 1024,  4, 1024, 4, 1024 };
	int queues[9] = {    8,    1, 32, 1,    8, 32,    1, 1,    8 };
	int threads[9] ={    1,    1,  1, 1,    1,  1,    1, 1,    1 };
	int measureTimes[5] = { 5, 10, 20, 30, 60 };
	int intervalTimes[10] = { 0, 1, 3, 5, 10, 30, 60, 180, 300, 600 };

	for (int i = 0; i < 9; i++)
	{
		cstr = QString("BenchType%1").arg(i);
		//m_BenchType[i] = GetPrivateProfileInt(L"Setting", cstr, type[i], m_Ini);
		if (*m_BenchType.at(i) < 0 || m_BenchSize[i] > 1) { m_BenchSize[i] = type[i]; }

		cstr = QString("BenchSize%1").arg(i);
		//m_BenchSize[i] = GetPrivateProfileInt(L"Setting", cstr, size[i], m_Ini);
		if (m_BenchSize[i] <= 0 || m_BenchSize[i] > 8192) { m_BenchSize[i] = size[i]; }

		cstr = QString("BenchQueues%1").arg(i);
		//m_BenchQueues[i] = GetPrivateProfileInt(L"Setting", cstr,queues[i], m_Ini);
		if (m_BenchQueues[i] <= 0 || m_BenchQueues[i] > MAX_QUEUES) { m_BenchQueues[i] = queues[i]; }

		cstr = QString("BenchThreads%1").arg(i);
		//m_BenchThreads[i] = GetPrivateProfileInt(L"Setting", cstr, threads[i], m_Ini);
		if (m_BenchThreads[i] <= 0 || m_BenchThreads[i] > MAX_THREADS) { m_BenchThreads[i] = threads[i]; }
	}

	//m_TestData = GetPrivateProfileInt(L"Setting", L"TestData", TEST_DATA_RANDOM, m_Ini);
	if (m_TestData < 0 || m_TestData > 1)
	{
		m_TestData = TEST_DATA_RANDOM;
	}
	//SetWindowTitle("");

	bool bMeasureflag = false;
	//m_MeasureTime = GetPrivateProfileInt(L"Setting", L"MeasureTime", 5, m_Ini);
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
	//m_IntervalTime = GetPrivateProfileInt(L"Setting", L"IntervalTime", 5, m_Ini);
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
				// WritePrivateProfileString(L"Setting", key, value, m_Ini);
				key = QString("BenchSize%1").arg(i); value = QString::number(size[i]);
				// WritePrivateProfileString(L"Setting", key, value, m_Ini);
				key = QString("BenchQueues%1").arg(i); value = QString::number(queues[i]);
				// WritePrivateProfileString(L"Setting", key, value, m_Ini);
				key = QString("BenchThreads%1").arg(i); value = QString::number(threads[i]);
				// WritePrivateProfileString(L"Setting", key, value, m_Ini);
			}
			// WritePrivateProfileString(L"Setting", L"Affinity", L"1", m_Ini);
		}
		UpdateQueuesThreads();
		ChangeButtonStatus(true);
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
				// WritePrivateProfileString(L"Setting", key, value, m_Ini);
				key = QString("BenchSize%1").arg(i); value = QString::number(size[i]);
				// WritePrivateProfileString(L"Setting", key, value, m_Ini);
				key = QString("BenchQueues%1").arg(i); value = QString::number(queues[i]);
				// WritePrivateProfileString(L"Setting", key, value, m_Ini);
				key = QString("BenchThreads%1").arg(i); value = QString::number(threads[i]);
				// WritePrivateProfileString(L"Setting", key, value, m_Ini);
			}
			// WritePrivateProfileString(L"Setting", L"Affinity", L"1", m_Ini);
		}
		UpdateQueuesThreads();
		ChangeButtonStatus(true);
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
			WritePrivateProfileString(L"Setting", key, value, m_Ini);
			key.Format(L"BenchSize%d", i); value.Format(L"%d", size[i]);
			WritePrivateProfileString(L"Setting", key, value, m_Ini);
			key.Format(L"BenchQueues%d", i); value.Format(L"%d", queues[i]);
			WritePrivateProfileString(L"Setting", key, value, m_Ini);
			key.Format(L"BenchThreads%d", i); value.Format(L"%d", threads[i]);
			WritePrivateProfileString(L"Setting", key, value, m_Ini);
		}
		WritePrivateProfileString(L"Setting", L"Affinity", L"0", m_Ini);
	}
		UpdateQueuesThreads();
		ChangeButtonStatus(TRUE);
	break;
	*/
	default:
		OnSettingsQueuesThreads();
		break;
	}
}

/*INT_PTR CALLBACK BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	// switch (uMsg)
	// {
	// case BFFM_INITIALIZED:
	// 	if (lpData != NULL)
	// 	{
	// 		::SendMessage(hWnd, BFFM_SETSELECTION, TRUE, lpData);
	// 	}
	// 	break;
	// }
	// return 0;
}*/

void CDiskMarkDlg::SelectDrive()
{
	QString cstr;
	if (m_DiskBenchStatus)
	{
		return ;
	}

	int previousComboDriveIndex = m_IndexTestDrive;

	// UpdateData(TRUE);
	
	if (m_ComboDrive->currentIndex() == m_MaxIndexTestDrive)
	{
		// QFileDialog dialog(this);
		// dialog.setFileMode(QFileDialog::Directory);
		// dialog.setOption(QFileDialog::ShowDirsOnly, true);
		// dialog.setWindowTitle("Select Folder");

		// if (dialog.exec())
		// {
		// 	QString selectedDir = dialog.selectedFiles().first();
		// 	m_TestTargetPath = selectedDir;
		// // 	m_ComboDrive->setToolTip(m_TestTargetPath);
		// }
		// else
		// {
		// 	m_IndexTestDrive = previousComboDriveIndex;
		// 	// m_ComboDrive->setToolTip("TEST_DRIVE");
		// }
	}
	else
	{
		// m_ComboDrive->setToolTip("TEST_DRIVE");
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
#ifdef MIX_MODE
		m_MixScore[i] = 0.0;
		m_MixLatency[i] = 0.0;
#endif
	}

	UpdateScore();
}

void CDiskMarkDlg::OnUpdateScore()
{
	UpdateScore();
	m_scoreChanged();
}

void CDiskMarkDlg::OnExit()
{
	OnCancel();
}

void CDiskMarkDlg::OnAbout()
{
	// Show About Dialog
	// m_AboutDlg = new CAboutDlg(this);
	// m_AboutDlg->show();
}

void CDiskMarkDlg::OnCancel()
{
// 	if (m_WinThread != NULL)
// 	{
// 		AfxMessageBox(m_MesStopBenchmark);
// 		return;
// 	}

// 	UpdateData(TRUE);
// 	CString cstr;
// 	cstr.Format(L"%d", m_IndexTestUnit);
// 	WritePrivateProfileString(L"Setting", L"TestUnit", cstr, m_Ini);
// 	cstr.Format(L"%d", m_IndexTestCount);
// 	WritePrivateProfileString(L"Setting", L"TestCount", cstr, m_Ini);
// 	cstr.Format(L"%d", m_IndexTestSize);
// 	WritePrivateProfileString(L"Setting", L"TestSize", cstr, m_Ini);
// #ifdef MIX_MODE
// 	if (m_MixMode)
// 	{
// 		cstr.Format(L"%d", m_IndexTestMix);
// 		WritePrivateProfileString(L"Setting", L"TestMix", cstr, m_Ini);
// 	}
// #endif

// 	if(m_IndexTestDrive != m_MaxIndexTestDrive)
// 	{ 
// 		cstr.Format(L"%d", m_ValueTestDrive.GetAt(0) - 'A');
// 	}
// 	else
// 	{
// 		cstr.Format(L"%d", 99);
// 	}
// 	WritePrivateProfileString(L"Setting", L"DriveLetter", cstr, m_Ini);

	QApplication::quit();
}

void CDiskMarkDlg::UpdateScore()
{
// // 	UpdateData(TRUE);
// 	if (m_Profile == PROFILE_DEMO)
// 	{
// 		SetMeter(m_TestRead0, *m_ReadScore.at(8), *m_ReadLatency.at(8), m_BenchSize[8] * 1024, m_IndexTestUnit);
// 		SetMeter(m_TestWrite0, *m_WriteScore.at(8), *m_WriteLatency.at(8), m_BenchSize[8] * 1024, m_IndexTestUnit);
// 	}
// 	else if (m_Profile == PROFILE_PEAK || m_Profile == PROFILE_PEAK_MIX)
// 	{
// 		SetMeter(m_TestRead0, *m_ReadScore.at(4), *m_ReadLatency.at(4), m_BenchSize[4] * 1024, SCORE_MBS);
// 		SetMeter(m_TestRead1, *m_ReadScore.at(5), *m_ReadLatency.at(5), m_BenchSize[5] * 1024, SCORE_MBS);
// 		SetMeter(m_TestRead2, *m_ReadScore.at(5), *m_ReadLatency.at(5), m_BenchSize[5] * 1024, SCORE_IOPS);
// 		SetMeter(m_TestRead3, *m_ReadScore.at(5), *m_ReadLatency.at(5), m_BenchSize[5] * 1024, SCORE_US);
// 		SetMeter(m_TestWrite0, *m_WriteScore.at(4), *m_WriteLatency.at(4), m_BenchSize[4] * 1024, SCORE_MBS);
// 		SetMeter(m_TestWrite1, *m_WriteScore.at(5), *m_WriteLatency.at(5), m_BenchSize[5] * 1024, SCORE_MBS);
// 		SetMeter(m_TestWrite2, *m_WriteScore.at(5), *m_WriteLatency.at(5), m_BenchSize[5] * 1024, SCORE_IOPS);
// 		SetMeter(m_TestWrite3, *m_WriteScore.at(5), *m_WriteLatency.at(5), m_BenchSize[5] * 1024, SCORE_US);
// #ifdef MIX_MODE
// 		if (m_MixMode)
// 		{
// 			SetMeter(&m_TestMix0, m_MixScore[4], m_MixLatency[4], m_BenchSize[4] * 1024, SCORE_MBS);
// 			SetMeter(&m_TestMix1, m_MixScore[5], m_MixLatency[5], m_BenchSize[5] * 1024, SCORE_MBS);
// 			SetMeter(&m_TestMix2, m_MixScore[5], m_MixLatency[5], m_BenchSize[5] * 1024, SCORE_IOPS);
// 			SetMeter(&m_TestMix3, m_MixScore[5], m_MixLatency[5], m_BenchSize[5] * 1024, SCORE_US);
// 		}
// #endif
// 	}
// 	else if (m_Profile == PROFILE_REAL || m_Profile == PROFILE_REAL_MIX)
// 	{
// 		SetMeter(m_TestRead0, *m_ReadScore.at(6), *m_ReadLatency.at(6), 1024 * 1024, SCORE_MBS);
// 		SetMeter(m_TestRead1, *m_ReadScore.at(7), *m_ReadLatency.at(7), 4 * 1024, SCORE_MBS);
// 		SetMeter(m_TestRead2, *m_ReadScore.at(7), *m_ReadLatency.at(7), 4 * 1024, SCORE_IOPS);
// 		SetMeter(m_TestRead3, *m_ReadScore.at(7), *m_ReadLatency.at(7), 4 * 1024, SCORE_US);
// 		SetMeter(m_TestWrite0, *m_WriteScore.at(6), *m_WriteLatency.at(6), 1024 * 1024, SCORE_MBS);
// 		SetMeter(m_TestWrite1, *m_WriteScore.at(7), *m_WriteLatency.at(7), 4 * 1024, SCORE_MBS);
// 		SetMeter(m_TestWrite2, *m_WriteScore.at(7), *m_WriteLatency.at(7), 4 * 1024, SCORE_IOPS);
// 		SetMeter(m_TestWrite3, *m_WriteScore.at(7), *m_WriteLatency.at(7), 4 * 1024, SCORE_US);
// #ifdef MIX_MODE
// 		if (m_MixMode)
// 		{
// 			SetMeter(&m_TestMix0, m_MixScore[6], m_MixLatency[6], 1024 * 1024, SCORE_MBS);
// 			SetMeter(&m_TestMix1, m_MixScore[7], m_MixLatency[7], 4 * 1024, SCORE_MBS);
// 			SetMeter(&m_TestMix2, m_MixScore[7], m_MixLatency[7], 4 * 1024, SCORE_IOPS);
// 			SetMeter(&m_TestMix3, m_MixScore[7], m_MixLatency[7], 4 * 1024, SCORE_US);
// 		}
// #endif
// 	}
// 	else
// 	{

// #ifdef MIX_MODE
// 		if (m_MixMode)
// 		{
// 			SetMeter(&m_TestMix0, m_MixScore.at(0], m_MixLatency.at(0], m_BenchSize[0] * 1024, m_IndexTestUnit);
// 			SetMeter(&m_TestMix1, m_MixScore.at(1], m_MixLatency.at(1], m_BenchSize[1] * 1024, m_IndexTestUnit);
// 			SetMeter(&m_TestMix2, m_MixScore.at(2], m_MixLatency.at(2], m_BenchSize[2] * 1024, m_IndexTestUnit);
// 			SetMeter(&m_TestMix3, m_MixScore.at(3], m_MixLatency.at(3], m_BenchSize[3] * 1024, m_IndexTestUnit);
// 		}
// #endif
// 	}
}

void CDiskMarkDlg::OnSequentialPeak()
{
	if (m_WinThread == NULL)
	{
		*m_ReadScore[4] = 0.0;
		*m_WriteScore[4] = 0.0;
		*m_ReadLatency[4] = 0.0;
		*m_WriteLatency[4] = 0.0;
#ifdef MIX_MODE
		m_MixScore[4] = 0.0;
		m_MixLatency.at(4] = 0.0;
#endif
		UpdateScore();
		m_DiskBenchStatus = true;
		m_WinThread = QThread::create([this]() { ExecDiskBench4(this); });
		m_WinThread->start();
		if (m_WinThread == NULL)
		{
			m_DiskBenchStatus = false;
		}
		else
		{
			ChangeButtonStatus(false);
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
#ifdef MIX_MODE
		m_MixScore[5] = 0.0;
		m_MixLatency.at(5] = 0.0;
#endif
		UpdateScore();
		m_DiskBenchStatus = true;
		m_WinThread = QThread::create([this]() { ExecDiskBench5(this); });
		m_WinThread->start();
		if (m_WinThread == NULL)
		{
			m_DiskBenchStatus = false;
		}
		else
		{
			ChangeButtonStatus(false);
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
#ifdef MIX_MODE
		m_MixScore[6] = 0.0;
		m_MixLatency.at(6] = 0.0;
#endif
		UpdateScore();
		m_DiskBenchStatus = true;
		m_WinThread = QThread::create([this]() { ExecDiskBench6(this); });
		m_WinThread->start();
		if (m_WinThread == NULL)
		{
			m_DiskBenchStatus = false;
		}
		else
		{
			ChangeButtonStatus(false);
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
#ifdef MIX_MODE
		m_MixScore[7] = 0.0;
		m_MixLatency.at(7] = 0.0;
#endif
		UpdateScore();
		m_DiskBenchStatus = true;
		m_WinThread = QThread::create([this]() { ExecDiskBench7(this); });
		m_WinThread->start();
		if (m_WinThread == NULL)
		{
			m_DiskBenchStatus = false;
		}
		else
		{
			ChangeButtonStatus(false);
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
#ifdef MIX_MODE
		m_MixScore[0] = 0.0;
		m_MixLatency.at(0] = 0.0;
#endif
		UpdateScore();
		m_DiskBenchStatus = true;
		m_WinThread = QThread::create([this]() { ExecDiskBench0(this); });
		m_WinThread->start();
		if(m_WinThread == NULL)
		{
			m_DiskBenchStatus = false;
		}
		else
		{
			ChangeButtonStatus(false);
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
#ifdef MIX_MODE
		m_MixScore[1] = 0.0;
		m_MixLatency.at(1] = 0.0;
#endif
		UpdateScore();
		m_DiskBenchStatus = true;
		m_WinThread = QThread::create([this]() { ExecDiskBench1(this); });
		m_WinThread->start();
		if (m_WinThread == NULL)
		{
			m_DiskBenchStatus = false;
		}
		else
		{
			ChangeButtonStatus(false);
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
#ifdef MIX_MODE
		m_MixScore[2] = 0.0;
		m_MixLatency.at(2] = 0.0;
#endif
		UpdateScore();
		m_DiskBenchStatus = true;
		m_WinThread = QThread::create([this]() { ExecDiskBench2(this); });
		m_WinThread->start();
		if(m_WinThread == NULL)
		{
			m_DiskBenchStatus = false;
		}
		else
		{
			ChangeButtonStatus(false);
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
#ifdef MIX_MODE
		m_MixScore[3] = 0.0;
		m_MixLatency.at(3] = 0.0;
#endif
		UpdateScore();
		m_DiskBenchStatus = true;
		m_WinThread = QThread::create([this]() { ExecDiskBench3(this); });
		m_WinThread->start();
		if(m_WinThread == NULL)
		{
			m_DiskBenchStatus = false;
		}
		else
		{
			ChangeButtonStatus(false);
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
		else
		{
			ChangeButtonStatus(false);
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

QString CDiskMarkDlg::GetButtonText(int type, int size, int queues, int threads, int unit) const
{
	QString text;

	if (size >= 1024)
	{
		if (type == BENCH_RND)
		{
			if (m_Profile == PROFILE_PEAK || m_Profile == PROFILE_PEAK_MIX || m_Profile == PROFILE_REAL || m_Profile == PROFILE_REAL_MIX)
			{
				if (unit == SCORE_IOPS)
				{
					text = QString("RND%1M\n(IOPS)").arg(size / 1024);
				}
				else if (unit == SCORE_US)
				{
					text = QString("RND%1M\n(μs)").arg(size / 1024);
				}
				else if (unit == SCORE_GBS)
				{
					text = QString("RND%1M\nQ%2T%3").arg(size / 1024).arg(queues).arg(threads);
				}
				else
				{
					text = QString("RND%1M\nQ%2T%3").arg(size / 1024).arg(queues).arg(threads);
				}
			}
			else
			{
				if (unit == SCORE_GBS)
				{
					text = QString("RND%1M\nQ%2T%3").arg(size / 1024).arg(queues).arg(threads);
				}
				else
				{
					text = QString("RND%1M\nQ%2T%3").arg(size / 1024).arg(queues).arg(threads);
				}
			}
		}
		else
		{
			if (unit == SCORE_GBS)
			{
				text = QString("SEQ%1M\nQ%2T%3").arg(size / 1024).arg(queues).arg(threads);
			}
			else
			{
				text = QString("SEQ%1M\nQ%2T%3").arg(size / 1024).arg(queues).arg(threads);
			}
		}
	}
	else
	{
		if (type == BENCH_RND)
		{
			if (m_Profile == PROFILE_PEAK || m_Profile == PROFILE_PEAK_MIX || m_Profile == PROFILE_REAL || m_Profile == PROFILE_REAL_MIX)
			{
				if (unit == SCORE_IOPS)
				{
					text = QString("RND%1K\n(IOPS)").arg(size);
				}
				else if (unit == SCORE_US)
				{
					text = QString("RND%1K\n(μs)").arg(size);
				}
				else if (unit == SCORE_GBS)
				{
					text = QString("RND%1K\nQ%2T%3").arg(size).arg(queues).arg(threads);
				}
				else
				{
					text = QString("RND%1K\nQ%2T%3").arg(size).arg(queues).arg(threads);
				}
			}
			else
			{
				if (unit == SCORE_GBS)
				{
					text = QString("RND%1K\nQ%2T%3").arg(size).arg(queues).arg(threads);
				}
				else
				{
					text = QString("RND%1K\nQ%2T%3").arg(size).arg(queues).arg(threads);
				}
			}
		}
		else
		{
			if (unit == SCORE_GBS)
			{
				text = QString("SEQ%1K\nQ%2T%3").arg(size).arg(queues).arg(threads);
			}
			else
			{
				text = QString("SEQ%1K\nQ%2T%3").arg(size).arg(queues).arg(threads);
			}
		}
	}

	return text;
}

QString CDiskMarkDlg::GetButtonToolTipText(int type, int size, int queues, int threads, int unit) const
{
	QString text;

	if (size >= 1024)
	{
		if (type == BENCH_RND)
		{
			if (unit == SCORE_IOPS)
			{
				text = QString("Random %1MiB\nQueues=%2\nThreads=%3\n(IOPS)").arg(size / 1024).arg(queues).arg(threads);
			}
			else if (unit == SCORE_US)
			{
				text = QString("Random %1MiB\nQueues=%2\nThreads=%3\n(μs)").arg(size / 1024).arg(queues).arg(threads);
			}
			else if (unit == SCORE_GBS)
			{
				text = QString("Random %1MiB\nQueues=%2\nThreads=%3\n(GB/s)").arg(size / 1024).arg(queues).arg(threads);
			}
			else
			{
				text = QString("Random %1MiB\nQueues=%2\nThreads=%3\n(MB/s)").arg(size / 1024).arg(queues).arg(threads);
			}
		}
		else
		{
			if (unit == SCORE_GBS)
			{
				text = QString("Sequential %1MiB\nQueues=%2\nThreads=%3\n(GB/s)").arg(size / 1024).arg(queues).arg(threads);
			}
			else
			{
				text = QString("Sequential %1MiB\nQueues=%2\nThreads=%3\n(MB/s)").arg(size / 1024).arg(queues).arg(threads);
			}
		}
	}
	else
	{
		if (type == BENCH_RND)
		{
			if (unit == SCORE_IOPS)
			{
				text = QString("Random %1KiB\nQueues=%2\nThreads=%3\n(IOPS)").arg(size).arg(queues).arg(threads);
			}
			else if (unit == SCORE_US)
			{
				text = QString("Random %1KiB\nQueues=%2\nThreads=%3\n(μs)").arg(size).arg(queues).arg(threads);
			}
			else if (unit == SCORE_GBS)
			{
				text = QString("Random %1KiB\nQueues=%2\nThreads=%3\n(GB/s)").arg(size).arg(queues).arg(threads);
			}
			else
			{
				text = QString("Random %1KiB\nQueues=%2\nThreads=%3\n(MB/s)").arg(size).arg(queues).arg(threads);
			}
		}
		else
		{
			if (unit == SCORE_GBS)
			{
				text = QString("Sequential %1KiB\nQueues=%2\nThreads=%3\n(GB/s)").arg(size).arg(queues).arg(threads);
			}
			else
			{
				text = QString("Sequential %1KiB\nQueues=%2\nThreads=%3\n(MB/s)").arg(size).arg(queues).arg(threads);
			}
		}
	}

	return text;
}

void CDiskMarkDlg::OnUpdateMessage(QString* message)
{
	if(message != NULL)
	{
		m_WindowTitle = *(message);
		m_WindowTitleChanged();
	}
}

void CDiskMarkDlg::SetMeter(int index, double score, double latency, int blockSize, int unit)
{
	// else if (unit == SCORE_UNIT::SCORE_US)
	// {
		// if (m_Profile == PROFILE_DEMO)
		// {
		// 	else if (latency >= 1000000.0)
		// 	{
		// 		cstr = QString::number((int)latency / 1000);
		// 		if (control == m_TestRead0) { m_TestRead0->setText("Read (ms)"); }
		// 		if (control == m_TestWrite0) { m_TestWrite0->setText("Write (ms)"); }
		// 	}
		// }
	// }
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

	// UpdateDriveToolTip();

	// UpdateData(FALSE);
}

void CDiskMarkDlg::ChangeLang()
{
// 	m_CurrentLangPath.Format(L"%s\\%s.lang", (LPTSTR)m_LangDir.GetString(), (LPTSTR)LangName.GetString());

	// QString cstr;
	// QMenuBar *menuBar = this->menuBar();
	// QMenu *menu;

	// menu = menuBar->actions().at(0)->menu();
	// cstr = tr("FILE");
	// menu->setTitle(cstr);

	// menu = menuBar->actions().at(1)->menu();
	// cstr = tr("SETTINGS");
	// menu->setTitle(cstr);

	// menu = menuBar->actions().at(2)->menu();
	// cstr = tr("PROFILE");
	// menu->setTitle(cstr);

	// menu = menuBar->actions().at(3)->menu();
	// cstr = tr("THEME");
	// menu->setTitle(cstr);

	// menu = menuBar->actions().at(4)->menu();
	// cstr = tr("HELP");
	// menu->setTitle(cstr);

	// menu = menuBar->actions().at(5)->menu();
	// cstr = tr("LANGUAGE");
	// if (cstr.contains("Language"))
	// {
	// 	cstr = "&Language";
	// 	menu->setTitle(cstr);
	// }
	// else
	// {
	// 	menu->setTitle(cstr + "(&Language)");
	// }

// 	QAction *action;

// 	action = menuBar->findChild<QAction*>("ID_EXIT");
// 	cstr = tr("FILE_EXIT") + "\tAlt + F4";
// 	action->setText(cstr);

// 	action = menuBar->findChild<QAction*>("ID_SAVE_TEXT");
// 	cstr = tr("SAVE_TEXT") + "\tCtrl + T";
// 	action->setText(cstr);

// 	action = menuBar->findChild<QAction*>("ID_SAVE_IMAGE");
// 	cstr = tr("SAVE_IMAGE") + "\tCtrl + S";
// 	action->setText(cstr);

// 	action = menuBar->findChild<QAction*>("ID_COPY");
// 	cstr = tr("EDIT_COPY") + "\tCtrl + Shift + C";
// 	action->setText(cstr);

// 	menu = menuBar->actions().at(1)->menu();
// 	cstr = tr("TEST_DATA");
// 	menu->actions().at(0)->setText(cstr);

// 	action = menuBar->findChild<QAction*>("ID_MODE_DEFAULT");
// 	cstr = tr("DEFAULT_RANDOM");
// 	action->setText(cstr);

// 	action = menuBar->findChild<QAction*>("ID_MODE_ALL0X00");
// 	cstr = tr("ALL_ZERO");
// 	action->setText(cstr);

// 	if (m_TestData == TEST_DATA_ALL0X00)
// 	{
// 		OnModeAll0x00();
// 	}
// 	else
// 	{
// 		OnModeDefault();
// 	}

// 	cstr = tr("DEFAULT");
// 	menu->actions().at(1)->menu()->actions().at(0)->setText(cstr);

// 	CheckRadioPresetMode();

// 	cstr = tr("SETTINGS") + "\tCtrl + Q";
// 	menu->actions().at(1)->menu()->actions().at(1)->setText(cstr);

// 	cstr = tr("PROFILE_DEFAULT");
// 	menu->actions().at(2)->menu()->actions().at(0)->setText(cstr);
// 	cstr = tr("PROFILE_PEAK");
// 	menu->actions().at(2)->menu()->actions().at(1)->setText(cstr);
// 	cstr = tr("PROFILE_REAL");
// 	menu->actions().at(2)->menu()->actions().at(2)->setText(cstr);
// 	cstr = tr("PROFILE_DEMO");
// 	menu->actions().at(2)->menu()->actions().at(3)->setText(cstr);

// #ifdef MIX_MODE
// 	cstr = i18n(L"Menu", L"PROFILE_DEFAULT") + L" [+Mix]";
// 	menu->ModifyMenu(ID_PROFILE_DEFAULT_MIX, MF_STRING, ID_PROFILE_DEFAULT_MIX, cstr);
// 	cstr = i18n(L"Menu", L"PROFILE_PEAK") + L" [+Mix]";
// 	menu->ModifyMenu(ID_PROFILE_PEAK_MIX, MF_STRING, ID_PROFILE_PEAK_MIX, cstr);
// 	cstr = i18n(L"Menu", L"PROFILE_REAL") + L" [+Mix]";
// 	menu->ModifyMenu(ID_PROFILE_REAL_MIX, MF_STRING, ID_PROFILE_REAL_MIX, cstr);
// #endif

// 	cstr = tr("HELP") + " [Web]" + "\tF1";
// 	menu->actions().at(4)->setText(cstr);
// 	cstr = tr("HELP_ABOUT");
// 	menu->actions().at(4)->menu()->actions().at(0)->setText(cstr);

// 	// Theme
// 	menu = menuBar->actions().at(3)->menu();
// 	cstr = tr("ZOOM");
// 	menu->actions().at(0)->setText(cstr);

// 	cstr = tr("AUTO");
// 	menu->actions().at(1)->setText(cstr);

// 	cstr = tr("FONT_SETTING") + "\tCtrl + F";
// 	menu->actions().at(2)->setText(cstr);

// 	CheckRadioZoomType();

// 	switch (m_Profile)
// 	{
// 	case PROFILE_DEFAULT:
// 		ProfileDefault();
// 		break;
// 	case PROFILE_PEAK:
// 		ProfilePeak();
// 		break;
// 	case PROFILE_REAL:
// 		ProfileReal();
// 		break;
// 	case PROFILE_DEMO:
// 		ProfileDemo();
// 		break;
// #ifdef MIX_MODE
// 	case PROFILE_DEFAULT_MIX:
// 		ProfileDefaultMix();
// 		break;
// 	case PROFILE_PEAK_MIX:
// 		ProfilePeakMix();
// 		break;
// 	case PROFILE_REAL_MIX:
// 		ProfileRealMix();
// 		break;
// #endif
// 	default:
// 		ProfileDefault();
// 		break;
// 	}

// 	switch (m_Benchmark)
// 	{
// 	case BENCHMARK_READ_WRITE:
// 		BenchmarkReadWrite();
// 		break;
// 	case BENCHMARK_READ:
// 		BenchmarkReadOnly();
// 		break;
// 	case BENCHMARK_WRITE:
// 		BenchmarkWriteOnly();
// 		break;
// 	default:
// 		BenchmarkReadWrite();
// 		break;
// 	}

// 	m_MesStopBenchmark = tr("STOP_BENCHMARK");
// 	m_MesDiskCapacityError = tr("DISK_CAPACITY_ERROR");
// 	m_MesDiskCreateFileError = tr("DISK_CREATE_FILE_ERROR");
// 	m_MesDiskWriteError = tr("DISK_WRITE_ERROR");
// 	m_MesDiskReadError = tr("DISK_READ_ERROR");
// 	m_MesDiskSpdNotFound = tr("DISK_SPD_NOT_FOUND");

// 	UpdateDriveToolTip();

// 	WritePrivateProfileString(L"Setting", L"Language", LangName, m_Ini);
}

// bool CDiskMarkDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
// {
	// // Select Theme
	// if (WM_THEME_ID <= wParam && wParam < WM_THEME_ID + (UINT)m_MenuArrayTheme.GetSize())
	// {
	// 	CMenu menu;
	// 	CMenu subMenu;
	// 	menu.Attach(GetMenu()->GetSafeHmenu());
	// 	subMenu.Attach(menu.GetSubMenu(MENU_THEME_INDEX)->GetSafeHmenu());

	// 	m_CurrentTheme = m_MenuArrayTheme.GetAt(wParam - WM_THEME_ID);
	// 	if (m_CurrentTheme.Compare(m_RandomThemeLabel) == 0)
	// 	{
	// 		m_CurrentTheme = GetRandomTheme();
	// 		m_RandomThemeLabel = L"Random";
	// 		m_RandomThemeName = L" (" + m_CurrentTheme + L")";

	// 		// ChangeTheme save the theme configuration to profile; so if we are on
	// 		// Random, then save Random to profile.
	// 		ChangeTheme(m_RandomThemeLabel);
	// 	}
	// 	else
	// 	{
	// 		ChangeTheme(m_MenuArrayTheme.GetAt(wParam - WM_THEME_ID));
	// 		m_RandomThemeName = L"";
	// 	}

	// 	subMenu.ModifyMenu(WM_THEME_ID, MF_STRING, WM_THEME_ID, m_RandomThemeLabel + m_RandomThemeName);
	// 	subMenu.CheckMenuRadioItem(WM_THEME_ID, WM_THEME_ID + (UINT)m_MenuArrayTheme.GetSize(),
	// 		(UINT)wParam, MF_BYCOMMAND);
	// 	subMenu.Detach();
	// 	menu.Detach();

	// 	if (m_Profile == PROFILE_DEMO && IsFileExist(m_ThemeDir + m_CurrentTheme + L"\\BackgroundDemo-300.png"))
	// 	{
	// 		m_BackgroundName = L"BackgroundDemo";
	// 	}
	// 	else
	// 	{
	// 		m_BackgroundName = L"Background";
	// 	}

	// 	UpdateThemeInfo();
	// 	UpdateDialogSize();

	// 	return TRUE;
	// }

	// // Select Language
	// if(WM_LANGUAGE_ID <= wParam && wParam < WM_LANGUAGE_ID + (UINT)m_MenuArrayLang.GetSize())
	// {
	// 	CMenu menu;
	// 	CMenu subMenu;
	// 	CMenu subMenuAN;
	// 	CMenu subMenuOZ;
	// 	menu.Attach(GetMenu()->GetSafeHmenu());
	// 	subMenu.Attach(menu.GetSubMenu(MENU_LANG_INDEX)->GetSafeHmenu());
	// 	subMenuAN.Attach(subMenu.GetSubMenu(0)->GetSafeHmenu());
	// 	subMenuOZ.Attach(subMenu.GetSubMenu(1)->GetSafeHmenu());

	// 	m_CurrentLang = m_MenuArrayLang.GetAt(wParam - WM_LANGUAGE_ID);
	// 	ChangeLang(m_MenuArrayLang.GetAt(wParam - WM_LANGUAGE_ID));
	// 	subMenuAN.CheckMenuRadioItem(WM_LANGUAGE_ID, WM_LANGUAGE_ID + (UINT)m_MenuArrayLang.GetSize(),
	// 								(UINT)wParam, MF_BYCOMMAND);
	// 	subMenuOZ.CheckMenuRadioItem(WM_LANGUAGE_ID, WM_LANGUAGE_ID + (UINT)m_MenuArrayLang.GetSize(),
	// 								(UINT)wParam, MF_BYCOMMAND);

	// 	subMenuOZ.Detach();
	// 	subMenuAN.Detach();
	// 	subMenu.Detach();
	// 	menu.Detach();

	// 	UpdateComboTooltip();
	// }

	// return CMainDialogFx::OnCommand(wParam, lParam);
// }

void CDiskMarkDlg::OnCopy()
{
	// SaveText(L"");
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

bool CDiskMarkDlg::CheckRadioZoomType(int id, int value)
{
	// if(m_ZoomType == value)
	// {
	// 	return FALSE;
	// }

	// CMenu *menu = GetMenu();
	// menu->CheckMenuRadioItem(ID_ZOOM_100, ID_ZOOM_AUTO, id, MF_BYCOMMAND);
	// SetMenu(menu);
	// DrawMenuBar();

	// m_ZoomType = value;

	// CString cstr;
	// cstr.Format(L"%d", value);
	// WritePrivateProfileString(L"Setting", L"ZoomType", cstr, m_Ini);

	// ChangeZoomType(m_ZoomType);

	return true;
}

void CDiskMarkDlg::CheckRadioZoomType()
{
	// int id = ID_ZOOM_AUTO;

	// switch(m_ZoomType)
	// {
	// case 100: id = ID_ZOOM_100;	break;
	// case 125: id = ID_ZOOM_125;	break;
	// case 150: id = ID_ZOOM_150;	break;
	// case 200: id = ID_ZOOM_200;	break;
	// case 250: id = ID_ZOOM_250;	break;
	// case 300: id = ID_ZOOM_300;	break;
	// default:  id = ID_ZOOM_AUTO;break;
	// }

	// CMenu *menu = GetMenu();
	// menu->CheckMenuRadioItem(ID_ZOOM_100, ID_ZOOM_AUTO, id, MF_BYCOMMAND);
	// SetMenu(menu);
	// DrawMenuBar();
}

void CDiskMarkDlg::OnHelp()
{
	// if (GetUserDefaultLCID() == 0x0411) // Japanese
	// {
	// 	OpenUrl(URL_HELP_JA);
	// }
	// else // Other Language
	// {
	// 	OpenUrl(URL_HELP_EN);
	// }
}

void CDiskMarkDlg::OnBlizzardWorld()
{
	// if (GetUserDefaultLCID() == 0x0411) // Japanese
	// {
	// 	OpenUrl(URL_CRYSTAL_DEW_WORLD_JA);
	// }
	// else // Other Language
	// {
	// 	OpenUrl(URL_CRYSTAL_DEW_WORLD_EN);
	// }
}

#ifdef MIX_MODE
	#define ID_PROFILE_MAX ID_PROFILE_REAL_MIX
#else
	#define ID_PROFILE_MAX ID_PROFILE_DEMO
#endif

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
	// WritePrivateProfileString(L"Setting", L"TestData", L"0", m_Ini);
	// SetWindowTitle("");
	m_TestDataChanged();
}

void CDiskMarkDlg::OnModeAll0x00()
{
	m_TestData = TEST_DATA_ALL0X00;
	// WritePrivateProfileString(L"Setting", L"TestData", L"1", m_Ini);
	// SetWindowTitle("");
	m_TestDataChanged();
}

void CDiskMarkDlg::OnProfileDefault()
{
	// ShowWindow(SW_HIDE);
	ProfileDefault();
	UpdateUnitLabel();
	InitScore();
	// UpdateDialogSize();
	ChangeButtonStatus(true);
	// SetWindowTitle(L"");
}

void CDiskMarkDlg::ProfileDefault()
{
	m_Profile = PROFILE_DEFAULT;
	m_MixMode = false;
	// WritePrivateProfileString(L"Setting", L"Profile", L"0", m_Ini);
	// m_BackgroundName = "Background";
	emit m_ProfileChanged();
}

void CDiskMarkDlg::OnProfilePeak()
{
	// ShowWindow(SW_HIDE);
	ProfilePeak();
	UpdateUnitLabel();
	InitScore();
	// UpdateDialogSize();
	ChangeButtonStatus(true);
	// SetWindowTitle(L"");
}

void CDiskMarkDlg::ProfilePeak()
{
	m_Profile = PROFILE_PEAK;
	m_MixMode = false;
	// WritePrivateProfileString(L"Setting", L"Profile", L"1", m_Ini);
	// m_BackgroundName = L"Background";
	emit m_ProfileChanged();
}

void CDiskMarkDlg::OnProfileReal()
{
	// ShowWindow(SW_HIDE);
	ProfileReal();
	UpdateUnitLabel();
	InitScore();
	// UpdateDialogSize();
	ChangeButtonStatus(true);
	// SetWindowTitle(L"");
}

void CDiskMarkDlg::ProfileReal()
{
	m_Profile = PROFILE_REAL;
	m_MixMode = false;
	// WritePrivateProfileString(L"Setting", L"Profile", L"2", m_Ini);
	// m_BackgroundName = L"Background";
	emit m_ProfileChanged();
}

void CDiskMarkDlg::OnProfileDemo()
{
	// ShowWindow(SW_HIDE);
	ProfileDemo();
	UpdateUnitLabel();
	InitScore();
	// UpdateDialogSize();
	ChangeButtonStatus(true);
	// SetWindowTitle(L"");
}

void CDiskMarkDlg::ProfileDemo()
{
	m_Profile = PROFILE_DEMO;
	m_MixMode = false;
	// WritePrivateProfileString(L"Setting", L"Profile", L"3", m_Ini);

	// if (IsFileExist(m_ThemeDir + m_CurrentTheme + L"\\BackgroundDemo-300.png"))
	// {
	// 	m_BackgroundName = L"BackgroundDemo";
	// }
	// else
	// {
	// 	m_BackgroundName = L"Background";
	// }
	m_ProfileChanged();
}

void CDiskMarkDlg::OnProfileDefaultMix()
{
	ProfileDefaultMix();
	UpdateUnitLabel();
	InitScore();
	// UpdateDialogSize();
	ChangeButtonStatus(true);
	// SetWindowTitle(L"");
}

void CDiskMarkDlg::ProfileDefaultMix()
{
	m_Profile = PROFILE_DEFAULT_MIX;
	m_MixMode = true;
	// WritePrivateProfileString(L"Setting", L"Profile", L"4", m_Ini);
	// m_BackgroundName = L"Background";
	emit m_ProfileChanged();
}

void CDiskMarkDlg::OnProfilePeakMix()
{
	ProfilePeakMix();
	ChangeButtonStatus(true);
	UpdateUnitLabel();
	InitScore();
	// UpdateDialogSize();
	// SetWindowTitle(L"");
}

void CDiskMarkDlg::ProfilePeakMix()
{
	m_Profile = PROFILE_PEAK_MIX;
	m_MixMode = true;
	// WritePrivateProfileString(L"Setting", L"Profile", L"5", m_Ini);
	// m_BackgroundName = L"Background";
	emit m_ProfileChanged();
}

void CDiskMarkDlg::OnProfileRealMix()
{
	ProfileRealMix();
	ChangeButtonStatus(true);
	UpdateUnitLabel();
	InitScore();
	// UpdateDialogSize();
	// SetWindowTitle(L"");
}

void CDiskMarkDlg::ProfileRealMix()
{
	m_Profile = PROFILE_REAL_MIX;
	m_MixMode = true;
	// WritePrivateProfileString(L"Setting", L"Profile", L"6", m_Ini);
	// m_BackgroundName = L"Background";
}

void CDiskMarkDlg::OnBenchmarkReadWrite()
{
	BenchmarkReadWrite();
}

void CDiskMarkDlg::BenchmarkReadWrite()
{
	m_Benchmark = BENCH_READ_WRITE;
	// WritePrivateProfileString(L"Setting", L"Benchmark", L"3", m_Ini);
	m_BenchmarkChanged();
}

void CDiskMarkDlg::OnBenchmarkReadOnly()
{
	BenchmarkReadOnly();
}

void CDiskMarkDlg::BenchmarkReadOnly()
{
	m_Benchmark = BENCH_READ;
	// WritePrivateProfileString(L"Setting", L"Benchmark", L"1", m_Ini);
	m_BenchmarkChanged();
}

void CDiskMarkDlg::OnBenchmarkWriteOnly()
{
	BenchmarkWriteOnly();
}

void CDiskMarkDlg::BenchmarkWriteOnly()
{
	m_Benchmark = BENCH_WRITE;
	// WritePrivateProfileString(L"Setting", L"Benchmark", L"2", m_Ini);
	m_BenchmarkChanged();
}

void CDiskMarkDlg::OnSettingsQueuesThreads()
{
	if (! m_DiskBenchStatus)
	{
		// CSettingsDlg* dlg = new CSettingsDlg(this);
		// dlg->DoModal();
		// UpdateQueuesThreads();
		// ChangeButtonStatus(true);

		// UpdateData(FALSE);

		// delete dlg;
	}
}

void CDiskMarkDlg::OnFontSetting()
{
	// CFontSelectionDlg fontSelection(this);
	// if (fontSelection.DoModal() == IDOK)
	// {
	// 	m_FontFace = fontSelection.GetFontFace();
	// 	m_FontScale = fontSelection.GetFontScale();
	// 	m_FontRatio = m_FontScale / 100.0;
	// 	m_FontRender = fontSelection.GetFontRender();

	// 	CString cstr;
	// 	WritePrivateProfileString(L"Setting", L"FontFace", L"\"" + m_FontFace + L"\"", m_Ini);
	// 	cstr.Format(L"%d", m_FontScale);
	// 	WritePrivateProfileString(L"Setting", L"FontScale", cstr, m_Ini);
	// 	cstr.Format(L"%d", m_FontRender);
	// 	WritePrivateProfileString(L"Setting", L"FontRender", cstr, m_Ini);

	// 	UpdateDialogSize();
// 	// }
}

void CDiskMarkDlg::OnCbnSelchangeComboDrive()
{
	SelectDrive();
}

#ifdef MIX_MODE
void CDiskMarkDlg::OnCbnSelchangeComboMix()
{
	UpdateData(TRUE);

	m_MixRatio = (9 - m_IndexTestMix) * 10;

	CString cstr;
	cstr.Format(L"%d", m_MixRatio);
	WritePrivateProfileString(L"Setting", L"TestMix", cstr, m_Ini);
}
#endif

void CDiskMarkDlg::UpdateUnitLabel()
{
// 	if (m_Profile == PROFILE_DEMO)
// 	{
// 		if (m_IndexTestUnit == SCORE_UNIT::SCORE_IOPS)
// 		{
// 			m_TestRead0->setText("Read (IOPS)");
// 			m_TestWrite0->setText("Write (IOPS)");
// 		}
// 		else if (m_IndexTestUnit == SCORE_UNIT::SCORE_US)
// 		{
// 			if (*m_ReadLatency.at(8) >= 1000000)
// 			{
// 				m_TestRead0->setText("Read (ms)");
// 			}
// 			else
// 			{
// 				m_TestRead0->setText("Read (μs)");
// 			}

// 			if (*m_WriteLatency.at(8) >= 1000000)
// 			{
// 				m_TestWrite0->setText("Write (ms)");
// 			}
// 			else
// 			{
// 				m_TestWrite0->setText("Write (μs)");
// 			}
// 		}
// 		else if (m_IndexTestUnit == SCORE_UNIT::SCORE_GBS)
// 		{
// 			m_TestRead0->setText("Read (GB/s)");
// 			m_TestWrite0->setText("Write (GB/s)");
// 		}
// 		else
// 		{
// 			m_TestRead0->setText("Read (MB/s)");
// 			m_TestWrite0->setText("Write (MB/s)");
// 		}
// 	}
// 	else
// 	{
// 		m_TestRead0->setText("");
// 		m_TestWrite0->setText("");
// 	}

// 	m_TestRead0->update();
// 	m_TestWrite0->update();

// 	if (m_Profile == PROFILE_REAL || m_Profile == PROFILE_REAL_MIX)
// 	{
// #ifdef MIX_MODE
// 		m_MixUnit->setText("Mix (MB/s)");
// #endif
// 		return;
// 	}
// 	else if (m_Profile == PROFILE_PEAK || m_Profile == PROFILE_PEAK_MIX)
// 	{
// #ifdef MIX_MODE
// 		m_MixUnit->setText("Mix (MB/s)");
// #endif
// 		return;
// 	}

// 	if (m_IndexTestUnit == SCORE_UNIT::SCORE_IOPS)
// 	{
// #ifdef MIX_MODE
// 		m_MixUnit->setText("Mix (IOPS)");
// #endif
// 	}
// 	else if (m_IndexTestUnit == SCORE_UNIT::SCORE_US)
// 	{
// #ifdef MIX_MODE
// 		m_MixUnit->setText("Mix (μs)");
// #endif
// 	}
// 	else if (m_IndexTestUnit == SCORE_UNIT::SCORE_GBS)
// 	{
// #ifdef MIX_MODE
// 		m_MixUnit->setText("Mix (GB/s)");
// #endif
// 	}
// 	else
// 	{
// #ifdef MIX_MODE
// 		m_MixUnit->setText("Mix (MB/s)");
// #endif
// 	}
}

void CDiskMarkDlg::SetWindowTitle(QString message)
{
	QString title;

	if (!message.isEmpty())
	{
		title = QString("%1").arg(message);
	}
	else
	{
		title = QString("%1 %2 %3").arg(PRODUCT_NAME).arg(PRODUCT_VERSION).arg(PRODUCT_EDITION);
	}

	if (m_TestData == TEST_DATA_ALL0X00)
	{
		title.append(" <0Fill>");
	}

	if (m_AdminMode)
	{
		title.append(" [Admin]");
	}
	
	m_WindowTitle = " " + title + " ";
	m_WindowTitleChanged();
}

void CDiskMarkDlg::OnSettings()
{
	// Show Setting Dialog
	// m_SettingsDlg = new CSettingsDlg(this);
	// m_SettingsDlg->show();
}

void CDiskMarkDlg::ChangeButtonStatus(bool status)
{
	m_buttonTextList.clear();

 	if(status)
	{
		m_buttonToolTipList.clear();
// 		QString title;

		m_buttonTextList.append("All");

		if (m_Profile == PROFILE_DEMO)
		{
			QString text, type;
			if (*m_BenchType[8] == BENCH_SEQ)
			{
				type = QStringLiteral("SEQ");
			}
			else
			{
				type = QStringLiteral("RND");
			}
			if (m_BenchSize[8] > 1000)
			{
				text = QString("%1 %2MiB, Q=%3, T=%4").arg(type).arg(m_BenchSize[8] / 1024).arg(m_BenchQueues[8]).arg(m_BenchThreads[8]);
			}
			else
			{
				text = QString("%1 %2KiB, Q=%3, T=%4").arg(type).arg(m_BenchSize[8]).arg(m_BenchQueues[8]).arg(m_BenchThreads[8]);
			}

// 			m_DemoSetting->setText(text);
		}
		else if (m_Profile == PROFILE_PEAK || m_Profile == PROFILE_PEAK_MIX)
		{
			m_buttonTextList.append(GetButtonText(BENCH_SEQ, m_BenchSize[4], m_BenchQueues[4], m_BenchThreads[4], SCORE_MBS));
			m_buttonTextList.append(GetButtonText(BENCH_RND, m_BenchSize[5], m_BenchQueues[5], m_BenchThreads[5], SCORE_MBS));
			m_buttonTextList.append(GetButtonText(BENCH_RND, m_BenchSize[5], m_BenchQueues[5], m_BenchThreads[5], SCORE_IOPS));
			m_buttonTextList.append(GetButtonText(BENCH_RND, m_BenchSize[5], m_BenchQueues[5], m_BenchThreads[5], SCORE_US));

			m_buttonToolTipList.append(GetButtonToolTipText(BENCH_SEQ, m_BenchSize[4], m_BenchQueues[4], m_BenchThreads[4], SCORE_MBS));
			m_buttonToolTipList.append(GetButtonToolTipText(BENCH_RND, m_BenchSize[5], m_BenchQueues[5], m_BenchThreads[5], SCORE_MBS));
			m_buttonToolTipList.append(GetButtonToolTipText(BENCH_RND, m_BenchSize[5], m_BenchQueues[5], m_BenchThreads[5], SCORE_IOPS));
			m_buttonToolTipList.append(GetButtonToolTipText(BENCH_RND, m_BenchSize[5], m_BenchQueues[5], m_BenchThreads[5], SCORE_US));
		}
		else if (m_Profile == PROFILE_REAL || m_Profile == PROFILE_REAL_MIX)
		{
			m_buttonTextList.append(GetButtonText(BENCH_SEQ, 1024, 1, 1, SCORE_MBS));
			m_buttonTextList.append(GetButtonText(BENCH_RND, 4, 1, 1, SCORE_MBS));
			m_buttonTextList.append(GetButtonText(BENCH_RND, 4, 1, 1, SCORE_IOPS));
			m_buttonTextList.append(GetButtonText(BENCH_RND, 4, 1, 1, SCORE_US));

			m_buttonToolTipList.append(GetButtonToolTipText(BENCH_SEQ, 1024, 1, 1, SCORE_MBS));
			m_buttonToolTipList.append(GetButtonToolTipText(BENCH_RND, 4, 1, 1, SCORE_MBS));
			m_buttonToolTipList.append(GetButtonToolTipText(BENCH_RND, 4, 1, 1, SCORE_IOPS));
			m_buttonToolTipList.append(GetButtonToolTipText(BENCH_RND, 4, 1, 1, SCORE_US));
		}
		else
		{
			m_buttonTextList.append(GetButtonText(*m_BenchType[0], m_BenchSize[0], m_BenchQueues[0], m_BenchThreads[0], m_IndexTestUnit));
			m_buttonTextList.append(GetButtonText(*m_BenchType[1], m_BenchSize[1], m_BenchQueues[1], m_BenchThreads[1], m_IndexTestUnit));
			m_buttonTextList.append(GetButtonText(*m_BenchType[2], m_BenchSize[2], m_BenchQueues[2], m_BenchThreads[2], m_IndexTestUnit));
			m_buttonTextList.append(GetButtonText(*m_BenchType[3], m_BenchSize[3], m_BenchQueues[3], m_BenchThreads[3], m_IndexTestUnit));

			m_buttonToolTipList.append(GetButtonToolTipText(*m_BenchType[0], m_BenchSize[0], m_BenchQueues[0], m_BenchThreads[0], m_IndexTestUnit));
			m_buttonToolTipList.append(GetButtonToolTipText(*m_BenchType[1], m_BenchSize[1], m_BenchQueues[1], m_BenchThreads[1], m_IndexTestUnit));
			m_buttonToolTipList.append(GetButtonToolTipText(*m_BenchType[2], m_BenchSize[2], m_BenchQueues[2], m_BenchThreads[2], m_IndexTestUnit));
			m_buttonToolTipList.append(GetButtonToolTipText(*m_BenchType[3], m_BenchSize[3], m_BenchQueues[3], m_BenchThreads[3], m_IndexTestUnit));
		}
	}
	else
	{
		m_buttonTextList.append("Stop");
		m_buttonTextList.append("Stop");
		m_buttonTextList.append("Stop");
		m_buttonTextList.append("Stop");
		m_buttonTextList.append("Stop");
	}

	m_buttonsChanged();
	m_DiskBenchStatusChanged();
}


void CDiskMarkDlg::OnExitBenchmark()
{
	ChangeButtonStatus(true);
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
QList<int> CDiskMarkDlg::m_blockSizeList() const
{
	QList<int> list;
	for (int size : m_BenchSize)
	{
		list.append(size);
	}
	return list;
}
