/*---------------------------------------------------------------------------*/
//       Author : hiyohiyo
//         Mail : hiyohiyo@crystalmark.info
//          Web : https://crystalmark.info/
//      License : MIT License
/*---------------------------------------------------------------------------*/

//#include "stdafx.h"
#include "DiskMarkDlg.h"
#include "AboutDlg.h"

CAboutDlg::CAboutDlg(QWidget* parent)
	: QDialog(parent),
	m_CtrlLogo(new QPushButton(this)),
	m_CtrlSecretVoice(new QPushButton(this)),
	m_CtrlProjectSite1(new QPushButton(this)),
	m_CtrlProjectSite2(new QPushButton(this)),
	m_CtrlProjectSite3(new QPushButton(this)),
	m_CtrlProjectSite4(new QPushButton(this)),
	m_CtrlProjectSite5(new QPushButton(this)),
	m_CtrlVersion(new QPushButton(this)),
	m_CtrlLicense(new QPushButton(this)),
	m_CtrlEdition(new QLabel(this)),
	m_CtrlRelease(new QLabel(this)),
	m_CtrlCopyright1(new QLabel(this)),
	m_CtrlCopyright2(new QLabel(this))
{
	// CMainDialogFx* p = static_cast<CMainDialogFx*>(parent);

	// m_ZoomType = p->GetZoomType();
	// m_FontScale = p->GetFontScale();
	// m_FontRatio = p->GetFontRatio();
	// m_FontFace = p->GetFontFace();
	// m_FontRender = p->GetFontRender();
	// m_CurrentLangPath = p->GetCurrentLangPath();
	// m_DefaultLangPath = p->GetDefaultLangPath();
	// m_ThemeDir = p->GetThemeDir();
	// m_CurrentTheme = p->GetCurrentTheme();
	// m_DefaultTheme = p->GetDefaultTheme();
	// m_Ini = p->GetIniPath();

// #ifdef SUISHO_SHIZUKU_SUPPORT
// 	m_BackgroundName = L"About";
// #else
// 	m_BackgroundName = "";
// #endif
}

CAboutDlg::~CAboutDlg()
{
	delete m_CtrlLogo;
	delete m_CtrlSecretVoice;
	delete m_CtrlProjectSite1;
	delete m_CtrlProjectSite2;
	delete m_CtrlProjectSite3;
	delete m_CtrlProjectSite4;
	delete m_CtrlProjectSite5;
	delete m_CtrlVersion;
	delete m_CtrlLicense;
	delete m_CtrlEdition;
	delete m_CtrlRelease;
	delete m_CtrlCopyright1;
	delete m_CtrlCopyright2;
}

// void CAboutDlg::DoDataExchange(CDataExchange* pDX)
// {
// 	CDialogFx::DoDataExchange(pDX);
// 	DDX_Control(pDX, IDC_LOGO, m_CtrlLogo);

// 	DDX_Control(pDX, IDC_PROJECT_SITE_1, m_CtrlProjectSite1);
// 	DDX_Control(pDX, IDC_PROJECT_SITE_2, m_CtrlProjectSite2);
// 	DDX_Control(pDX, IDC_PROJECT_SITE_3, m_CtrlProjectSite3);
// 	DDX_Control(pDX, IDC_PROJECT_SITE_4, m_CtrlProjectSite4);
// 	DDX_Control(pDX, IDC_PROJECT_SITE_5, m_CtrlProjectSite5);

// 	DDX_Control(pDX, IDC_VERSION, m_CtrlVersion);
// 	DDX_Control(pDX, IDC_LICENSE, m_CtrlLicense);	
// 	DDX_Control(pDX, IDC_RELEASE, m_CtrlRelease);
// 	DDX_Control(pDX, IDC_COPYRIGHT1, m_CtrlCopyright1);
// 	DDX_Control(pDX, IDC_COPYRIGHT2, m_CtrlCopyright2);
// 	DDX_Control(pDX, IDC_EDITION, m_CtrlEdition);
// }

void CAboutDlg::showEvent(QShowEvent* event)
{
	// CDialogFx::showEvent(event);
	// CDialogFx::OnInitDialog();

	// SetWindowTitle(i18n(L"WindowTitle", L"ABOUT"));

	// m_bShowWindow = TRUE;
	// m_CtrlVersion.SetWindowTextW(PRODUCT_NAME L" " PRODUCT_VERSION);
	// m_CtrlEdition.SetWindowTextW(PRODUCT_EDITION);
	// m_CtrlRelease.SetWindowTextW(L"Release: " PRODUCT_RELEASE);
	// m_CtrlCopyright1.SetWindowTextW(PRODUCT_COPYRIGHT_1);
	// m_CtrlCopyright2.SetWindowTextW(PRODUCT_COPYRIGHT_2);
	// m_CtrlLicense.SetWindowTextW(PRODUCT_LICENSE);

	// UpdateDialogSize();

	// CenterWindow();
	// ShowWindow(SW_SHOW);
	// return TRUE;
}

// BEGIN_MESSAGE_MAP(CAboutDlg, CDialogFx)
// 	ON_BN_CLICKED(IDC_LOGO, &CAboutDlg::OnLogo)
// 	ON_BN_CLICKED(IDC_LICENSE, &CAboutDlg::OnLicense)
// 	ON_BN_CLICKED(IDC_VERSION, &CAboutDlg::OnVersion)
// #ifdef SUISHO_SHIZUKU_SUPPORT
// 	ON_BN_CLICKED(IDC_PROJECT_SITE_1, &CAboutDlg::OnProjectSite1)
// 	ON_BN_CLICKED(IDC_PROJECT_SITE_2, &CAboutDlg::OnProjectSite2)
// 	ON_BN_CLICKED(IDC_PROJECT_SITE_3, &CAboutDlg::OnProjectSite3)
// 	ON_BN_CLICKED(IDC_PROJECT_SITE_4, &CAboutDlg::OnProjectSite4)
// 	ON_BN_CLICKED(IDC_PROJECT_SITE_5, &CAboutDlg::OnProjectSite5)
// #endif
// END_MESSAGE_MAP()


void CAboutDlg::resizeEvent(QResizeEvent* event)
{
	// CDialogFx::resizeEvent(event);

	// m_bHighContrast = false;

// 	ChangeZoomType(m_ZoomType);
	setFixedSize(SIZE_X, SIZE_Y);
// 	UpdateBackground(TRUE, m_bDarkMode);

#ifdef SUISHO_AOI_SUPPORT
	m_CtrlLogo.InitControl(32, 484, 128, 144, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlSecretVoice.InitControl(392, 288, 60, 20, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlProjectSite1.InitControl(184, 508, 148, 16, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlProjectSite2.InitControl(244, 540, 108, 16, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlProjectSite3.InitControl(232, 556, 180, 16, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlProjectSite4.InitControl(244, 576, 120, 16, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlProjectSite5.InitControl(0, 0, 0, 0, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlSecretVoice.SetHandCursor();
	m_CtrlProjectSite1.SetHandCursor();
	m_CtrlProjectSite2.SetHandCursor();
	m_CtrlProjectSite3.SetHandCursor();
	m_CtrlProjectSite4.SetHandCursor();
	m_CtrlProjectSite5.SetHandCursor();

#elif MSI_MEI_SUPPORT
	m_CtrlProjectSite1.InitControl(24, 460, 348, 128, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlProjectSite2.InitControl(168, 604, 36, 24, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlProjectSite3.InitControl(332, 604, 104, 24, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlProjectSite4.InitControl(20, 20, 120, 40, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlProjectSite5.InitControl(464, 604, 168, 24, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlLogo.InitControl(80, 64, 128, 128, m_ZoomRatio, &m_BkDC, IP(L"Logo"), 1, BS_CENTER, OwnerDrawImage, FALSE, FALSE, FALSE);
	m_CtrlProjectSite1.SetHandCursor();
	m_CtrlProjectSite2.SetHandCursor();
	m_CtrlProjectSite3.SetHandCursor();
	m_CtrlProjectSite4.SetHandCursor();
	m_CtrlProjectSite5.SetHandCursor();

#elif SUISHO_SHIZUKU_SUPPORT
	m_CtrlProjectSite1.InitControl(64, 372, 140, 16, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlProjectSite2.InitControl(64, 416, 148, 16, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlProjectSite3.InitControl(64, 432, 184, 16, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlProjectSite4.InitControl(40, 460, 208, 16, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlProjectSite5.InitControl(92, 504, 432, 124, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlLogo.InitControl(80, 12, 128, 128, m_ZoomRatio, &m_BkDC, IP(L"Logo"), 1, BS_CENTER, OwnerDrawImage, FALSE, FALSE, FALSE);
	m_CtrlProjectSite1.SetHandCursor();
	m_CtrlProjectSite2.SetHandCursor();
	m_CtrlProjectSite3.SetHandCursor();
	m_CtrlProjectSite4.SetHandCursor();
	m_CtrlProjectSite5.SetHandCursor();
#else
	m_CtrlLogo->setGeometry(12, 12, 128, 128);
	// m_CtrlLogo->setPixmap(QPixmap(":/resources/Logo.png"));
	// m_CtrlLogo->setScaledContents(true);
	m_CtrlProjectSite1->hide();
	m_CtrlProjectSite2->hide();
	m_CtrlProjectSite3->hide();
	m_CtrlProjectSite4->hide();
	m_CtrlProjectSite5->hide();
#endif

	m_CtrlLogo->setCursor(Qt::PointingHandCursor);

#ifdef MSI_MEI_SUPPORT
	QColor fontColor = QColor(255, 255, 255);
#else
	QColor fontColor = QColor(0, 0, 0);
#endif

	// m_CtrlVersion.SetFontEx(m_FontFace, 22, 22, m_ZoomRatio, m_FontRatio, fontColor, FW_BOLD, m_FontRender);
	// m_CtrlEdition.SetFontEx(m_FontFace, 18, 18, m_ZoomRatio, m_FontRatio, fontColor, FW_BOLD, m_FontRender);
	// m_CtrlRelease.SetFontEx(m_FontFace, 16, 16, m_ZoomRatio, m_FontRatio, fontColor, FW_NORMAL, m_FontRender);
	// m_CtrlCopyright1.SetFontEx(m_FontFace, 16, 16, m_ZoomRatio, m_FontRatio, fontColor, FW_NORMAL, m_FontRender);
	// m_CtrlCopyright2.SetFontEx(m_FontFace, 16, 16, m_ZoomRatio, m_FontRatio, fontColor, FW_NORMAL, m_FontRender);
	// m_CtrlLicense.SetFontEx(m_FontFace, 16, 16, m_ZoomRatio, m_FontRatio, fontColor, FW_NORMAL, m_FontRender);

	m_CtrlVersion->setCursor(Qt::PointingHandCursor);
	m_CtrlLicense->setCursor(Qt::PointingHandCursor);

#ifdef SUISHO_AOI_SUPPORT
	m_CtrlVersion.InitControl(0, 152, 288, 28, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlEdition.InitControl(0, 180, 288, 28, m_ZoomRatio, &m_BkDC, NULL, 0, SS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlRelease.InitControl(0, 216, 288, 20, m_ZoomRatio, &m_BkDC, NULL, 0, SS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlCopyright1.InitControl(0, 236, 288, 20, m_ZoomRatio, &m_BkDC, NULL, 0, SS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlCopyright2.InitControl(0, 256, 288, 20, m_ZoomRatio, &m_BkDC, NULL, 0, SS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlLicense.InitControl(0, 276, 288, 20, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);

#elif MSI_MEI_SUPPORT
	m_CtrlVersion.InitControl(0, 204, 288, 28, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlEdition.InitControl(0, 232, 288, 28, m_ZoomRatio, &m_BkDC, NULL, 0, SS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlRelease.InitControl(0, 268, 288, 20, m_ZoomRatio, &m_BkDC, NULL, 0, SS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlCopyright1.InitControl(0, 288, 288, 20, m_ZoomRatio, &m_BkDC, NULL, 0, SS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlCopyright2.InitControl(0, 308, 288, 20, m_ZoomRatio, &m_BkDC, NULL, 0, SS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlLicense.InitControl(0, 0, 0, 0, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);

#elif SUISHO_SHIZUKU_SUPPORT
	m_CtrlVersion.InitControl(0, 152, 288, 28, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlEdition.InitControl(0, 180, 288, 28, m_ZoomRatio, &m_BkDC, NULL, 0, SS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlRelease.InitControl(0, 216, 288, 20, m_ZoomRatio, &m_BkDC, NULL, 0, SS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlCopyright1.InitControl(0, 236, 288, 20, m_ZoomRatio, &m_BkDC, NULL, 0, SS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlCopyright2.InitControl(0, 256, 288, 20, m_ZoomRatio, &m_BkDC, NULL, 0, SS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);
	m_CtrlLicense.InitControl(0, 276, 288, 20, m_ZoomRatio, &m_BkDC, NULL, 0, BS_CENTER, OwnerDrawTransparent, FALSE, FALSE, FALSE);

#else
	m_CtrlVersion->setGeometry(140, 12, 340, 28);
	m_CtrlEdition->setGeometry(140, 40, 340, 28);
	m_CtrlRelease->setGeometry(140, 76, 340, 20);
	m_CtrlCopyright1->setGeometry(140, 100, 340, 20);
	m_CtrlLicense->setGeometry(140, 120, 340, 20);
	m_CtrlCopyright2->hide();
#endif

	update();
}

void CAboutDlg::OnLogo()
{
	// if (GetUserDefaultLCID() == 0x0411)// Japanese
	// {
	// 	OpenUrl(URL_MAIN_JA);
	// }
	// else // Other Language
	// {
	// 	OpenUrl(URL_MAIN_EN);
	// }
}

void CAboutDlg::OnVersion()
{
	// if (GetUserDefaultLCID() == 0x0411)// Japanese
	// {
	// 	OpenUrl(URL_VERSION_JA);
	// }
	// else // Other Language
	// {
	// 	OpenUrl(URL_VERSION_EN);
	// }

}
void CAboutDlg::OnLicense()
{
	// if (GetUserDefaultLCID() == 0x0411)// Japanese
	// {
	// 	OpenUrl(URL_LICENSE_JA);
	// }
	// else // Other Language
	// {
	// 	OpenUrl(URL_LICENSE_EN);
	// }
}

#ifdef SUISHO_SHIZUKU_SUPPORT
void CAboutDlg::OnProjectSite1()
{
	OpenUrl(URL_PROJECT_SITE_1);
}

void CAboutDlg::OnProjectSite2()
{
	OpenUrl(URL_PROJECT_SITE_2);
}

void CAboutDlg::OnProjectSite3()
{
	OpenUrl(URL_PROJECT_SITE_3);
}

void CAboutDlg::OnProjectSite4()
{
	OpenUrl(URL_PROJECT_SITE_4);
}

void CAboutDlg::OnProjectSite5()
{
	OpenUrl(URL_PROJECT_SITE_5);
}
#endif