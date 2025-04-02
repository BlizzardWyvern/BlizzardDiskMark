/*  
 * Copyright (c) 2025  BlizzardWyvern, All rights reserved.
 *   
 * This file incorporates work covered by the following copyright and  
 * permission notice:  
 *  
 *     Copyright (c) 2007-2021 hiyohiyo
 * 
 *     Permission is hereby granted, free of charge, to any person obtaining
 * 	   a copy of this software and associated documentation files (the “Software”), 
 *     to deal in the Software without restriction, including without limitation 
 *     the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 *     and/or sell copies of the Software, and to permit persons to whom the 
 *     Software is furnished to do so, subject to the following conditions:
 * 
 * 	   The above copyright notice and this permission notice shall be included 
 *     in all copies or substantial portions of the Software.
 * 
 *     THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS 
 *     OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 *     FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 *     THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR 
 *     OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 *     ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
 *     OTHER DEALINGS IN THE SOFTWARE.
 */

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml/qqmlextensionplugin.h>
#include <QtPlugin>
#include <QtWebView/QtWebView>

#include "DiskMarkDlg.h"

int main(int argc, char *argv[])
{
	QGuiApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);
	// QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
	// QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
	// QtWebView::initialize();
	QGuiApplication app(argc, argv);
	// QWebEngineProfile::defaultProfile()->setCachePath("cache");
	// QWebEngineProfile::defaultProfile()->setHttpCacheMaximumSize(50 * 1024 * 1024); // 50 MB
	QPalette palette;
	palette.setColor(QPalette::Window, Qt::white);
	palette.setColor(QPalette::WindowText, Qt::black);
	palette.setColor(QPalette::Base, Qt::white);
	palette.setColor(QPalette::AlternateBase, Qt::lightGray);
	palette.setColor(QPalette::ToolTipBase, Qt::white);
	palette.setColor(QPalette::ToolTipText, Qt::black);
	palette.setColor(QPalette::Text, Qt::black);
	palette.setColor(QPalette::Button, Qt::lightGray);
	palette.setColor(QPalette::ButtonText, Qt::black);
	palette.setColor(QPalette::BrightText, Qt::red);
	palette.setColor(QPalette::Light, Qt::lightGray);
	palette.setColor(QPalette::Midlight, Qt::lightGray);
	palette.setColor(QPalette::Dark, Qt::darkGray);
	palette.setColor(QPalette::Mid, Qt::lightGray);
	palette.setColor(QPalette::Shadow, Qt::darkGray);
	palette.setColor(QPalette::Highlight, QColor("#965ec6"));
	palette.setColor(QPalette::Accent, QColor("#965ec6"));
	palette.setColor(QPalette::HighlightedText, Qt::white);
	palette.setColor(QPalette::Link, Qt::blue);
	palette.setColor(QPalette::LinkVisited, Qt::darkBlue);
	palette.setColor(QPalette::NoRole, Qt::white);
	app.setPalette(palette);
	
	QQmlApplicationEngine engine;
	engine.addImportPath(QStringLiteral("qrc:/"));
	engine.rootContext()->setContextProperty("VERSION", QStringLiteral(VERSION));
	engine.rootContext()->setContextProperty("ARCHITECTURE", QStringLiteral(ARCHITECTURE));
	engine.rootContext()->setContextProperty("BUILDTYPE", QStringLiteral(BUILDTYPE));
	engine.load(QUrl(QStringLiteral("qrc:/DiskMarkDlg.qml")));

	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}
