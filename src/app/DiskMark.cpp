#include <QApplication>
#include <QQmlApplicationEngine>
#include "DiskMarkDlg.h"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);
	QGuiApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);

	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/DiskMarkDlg.qml")));

	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}
