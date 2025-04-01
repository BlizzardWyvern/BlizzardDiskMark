/*---------------------------------------------------------------------------*/
//       Author : hiyohiyo
//         Mail : hiyohiyo@crystalmark.info
//          Web : https://crystalmark.info/
//      License : MIT License
/*---------------------------------------------------------------------------*/

#pragma once
//#include "DialogFx.h"
//#include "StaticFx.h"
//#include "ButtonFx.h"

#include <QDialog>
#include <QPushButton>
#include <QLabel>

class CAboutDlg : public QDialog
{
	Q_OBJECT

#ifdef SUISHO_AOI_SUPPORT
	static const int SIZE_X = 640;
	static const int SIZE_Y = 640;
#elif MSI_MEI_SUPPORT
	static const int SIZE_X = 640;
	static const int SIZE_Y = 640;
#elif SUISHO_SHIZUKU_SUPPORT
	static const int SIZE_X = 640;
	static const int SIZE_Y = 660;
#else
	static const int SIZE_X = 480;
	static const int SIZE_Y = 152;
#endif

public:
	CAboutDlg(QWidget* parent = nullptr);
	virtual ~CAboutDlg();

protected:
	// virtual void DoDataExchange(CDataExchange* pDX);
	void showEvent(QShowEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;

	// DECLARE_MESSAGE_MAP()
	// afx_msg void OnLogo();
	// afx_msg void OnVersion();
	// afx_msg void OnLicense();
	// afx_msg void OnProjectSite1();
	// afx_msg void OnProjectSite2();
	// afx_msg void OnProjectSite3();
	// afx_msg void OnProjectSite4();
	// afx_msg void OnProjectSite5();

private:
	QPushButton* m_CtrlLogo;
	QPushButton* m_CtrlSecretVoice;
	QPushButton* m_CtrlProjectSite1;
	QPushButton* m_CtrlProjectSite2;
	QPushButton* m_CtrlProjectSite3;
	QPushButton* m_CtrlProjectSite4;
	QPushButton* m_CtrlProjectSite5;
	QPushButton* m_CtrlVersion;
	QPushButton* m_CtrlLicense;

	QLabel* m_CtrlEdition;
	QLabel* m_CtrlRelease;
	QLabel* m_CtrlCopyright1;
	QLabel* m_CtrlCopyright2;
};;
