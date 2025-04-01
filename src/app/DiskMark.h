/*---------------------------------------------------------------------------*/
//       Author : hiyohiyo
//         Mail : hiyohiyo@crystalmark.info
//          Web : https://crystalmark.info/
//      License : MIT License
/*---------------------------------------------------------------------------*/

#pragma once

#include <QApplication>

class CDiskMarkApp : public QApplication
{
public:
	CDiskMarkApp(int &argc, char **argv);
	
public:
	virtual bool InitInstance(int argc, char *argv[]);
};

extern CDiskMarkApp theApp;