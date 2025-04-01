#include <QApplication>
#include <QQmlApplicationEngine>

#include "DiskMarkDlg.h"
#include "ScoreLabel.h"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);
	QGuiApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);

	qmlRegisterUncreatableType<ScoreLabel>("ScoreLabel", 1, 0, "ScoreLabel", "ScoreLabel is an attached property");

	QQmlApplicationEngine engine;
	engine.addImportPath(QStringLiteral("qrc:/"));
	qDebug() << engine.importPathList();
	engine.load(QUrl(QStringLiteral("qrc:/DiskMarkDlg.qml")));

	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}
