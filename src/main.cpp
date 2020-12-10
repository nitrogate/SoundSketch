#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include "waveformplot.h"
#include "audiofile.h"
#include "cliplistmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("ITU");

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("src/images/ikona.ico"));
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    qmlRegisterType<WaveformPlot>("itu.project.frontend", 1, 0, "WaveformPlot");
    qmlRegisterType<AudioFile>("itu.project.backend", 1, 0, "AudioFile");
    qmlRegisterType<ClipListModel>("itu.project.backend", 1, 0, "ClipListModel");
    qmlRegisterSingletonType(QUrl("qrc:///Style.qml"), "itu.project.frontend", 1, 0, "Style");
    engine.load(url);

    return app.exec();
}
