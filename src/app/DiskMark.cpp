#include <QApplication>
#include <QQmlApplicationEngine>

#include "DiskMarkDlg.h"
#include "ScoreLabel/ScoreLabel.h"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);
	QGuiApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);
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
	palette.setColor(QPalette::Link, Qt::blue);
	palette.setColor(QPalette::Highlight, Qt::blue);
	palette.setColor(QPalette::HighlightedText, Qt::white);
	app.setPalette(palette);

	qmlRegisterUncreatableType<ScoreLabel>("ScoreLabel", 1, 0, "ScoreLabel", "ScoreLabel is an attached property");

	QQmlApplicationEngine engine;
	engine.addImportPath(QStringLiteral("qrc:/"));
	engine.load(QUrl(QStringLiteral("qrc:/DiskMarkDlg.qml")));

	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}
