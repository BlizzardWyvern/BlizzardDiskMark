/*---------------------------------------------------------------------------*/
//       Author : hiyohiyo
//         Mail : hiyohiyo@crystalmark.info
//          Web : https://crystalmark.info/
//      License : MIT License
/*---------------------------------------------------------------------------*/

#include <QApplication>
#include "DiskMark.h"
#include "DiskMarkDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDiskMarkApp::CDiskMarkApp(int &argc, char **argv)
	: QApplication(argc, argv)
{
}

bool CDiskMarkApp::InitInstance(int argc, char *argv[])
{
	CDiskMarkDlg dlg;
	dlg.show();
	return exec();
}

int main(int argc, char *argv[])
{
	CDiskMarkApp app(argc, argv);
	return app.InitInstance(argc, argv);
}
