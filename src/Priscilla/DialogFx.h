/*---------------------------------------------------------------------------*/
//       Author : hiyohiyo
//         Mail : hiyohiyo@crystalmark.info
//          Web : https://crystalmark.info/
//      License : MIT License
/*---------------------------------------------------------------------------*/

#pragma once

#include "CommonFx.h"
//#include "DarkMode.h"

#include <QDialog>
#include <QTimer>
#include <QUrl>
#include <QDesktopServices>
#include <QFont>
#include <QPalette>
#include <QBitmap>
#include <QBrush>
#include <QImage>
#include <QPainter>
#include <QEvent>

class CDialogFx : public QDialog
{
	Q_OBJECT

public:
	CDialogFx(QWidget* parent = nullptr);
	virtual ~CDialogFx();

	// Dialog
	virtual bool createDialog();

	// Font
	int getFontScale();
	QByteArray getFontRender();
	double getFontRatio();
	QString getFontFace();

	// Theme
	bool isDisableDarkMode();

protected:
	// Dialog
	virtual void initDialog();
	virtual bool eventFilter(QObject* obj, QEvent* event);
	virtual void closeEvent(QCloseEvent* event);
	virtual void updateDialogSize();
	virtual void setClientSize(int sizeX, int sizeY, double zoomRatio);
	virtual void updateBackground(bool resize, bool darkMode);
	virtual void setWindowTitle(const QString& title);
	virtual void accept();
	virtual void reject();

	// Zoom
	quint32 changeZoomType(quint32 zoomType);

	// Theme
	bool isHighContrast();

	// Utility
	virtual QString ip(const QString& imageName);
	QString i18n(const QString& section, const QString& key, bool inEnglish = false);
	void openUrl(const QString& url);
	void setLayeredWindow(WId hWnd, quint8 alpha);
	int getDpi();

protected slots:
	void onTimer();
	bool onEraseBkgnd(QPainter* painter);
	void onDpiChanged();
	void onDisplayChange();
	void onSysColorChange();
	void onSettingChange();
	void onEnterSizeMove();
	void onExitSizeMove();

public:
	// Dialog
	bool m_bInitializing;
	bool m_bDpiChanging;
	bool m_bShowWindow;
	bool m_bModelessDlg;
	bool m_bHighContrast;
	bool m_bDarkMode;
	bool m_bDisableDarkMode;
	bool m_bBkImage;
	QWidget* m_ParentWnd;
	QWidget* m_DlgWnd;
	QString m_Ini;
	bool m_bDrag;
	QString m_FontFace;
	int m_FontScale;
	double m_FontRatio;
	QByteArray m_FontRender;

	int m_SizeX;
	int m_MaxSizeX;
	int m_MinSizeX;
	int m_SizeY;
	int m_MaxSizeY;
	int m_MinSizeY;

	// Zoom
	int m_Dpi;
	quint32 m_ZoomType;
	double m_ZoomRatio;

	// Color for SubClass
	QColor m_LabelText;
	QColor m_MeterText;
	QColor m_ComboText;
	QColor m_ComboTextSelected;
	QColor m_ComboBk;
	QColor m_ComboBkSelected;
	QColor m_ButtonText;
	QColor m_EditText;
	QColor m_EditBk;
	QColor m_ListText1;
	QColor m_ListText2;
	QColor m_ListTextSelected;
	QColor m_ListBk1;
	QColor m_ListBk2;
	QColor m_ListBkSelected;
	QColor m_ListLine1;
	QColor m_ListLine2;
	QColor m_Glass;
	QColor m_Frame;
	QColor m_Background;

	quint8 m_ComboAlpha;
	quint8 m_EditAlpha;
	quint8 m_GlassAlpha;

	quint8 m_CharacterPosition;

	// Theme for SubClass
	int m_OffsetX;
	QString m_ThemeDir;
	QString m_CurrentTheme;
	QString m_DefaultTheme;
	QString m_ParentTheme1;
	QString m_ParentTheme2;
	QString m_RandomThemeLabel;
	QString m_RandomThemeName;

	// Language for SubClass
	QString m_LangDir;
	QString m_CurrentLang;
	QString m_CurrentLangPath;
	QString m_DefaultLangPath;
	QString m_BackgroundName;

	// Voice for SubClass
	QString m_VoiceDir;
	QString m_CurrentVoice;
	int m_VoiceVolume;

	// Class
	QBitmap m_BkBitmap;
	QImage m_BkImage;
	QBrush m_BrushDlg;
};;
