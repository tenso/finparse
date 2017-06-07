#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "System.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    System sys;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("System", &sys);
    engine.rootContext()->setContextProperty("PdfDocument", sys.model());
    engine.addImageProvider("pdf", sys.model());
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
