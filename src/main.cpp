#include "MainWindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDir>

QStringList findQmFiles()
{
    QDir dir(":/i18n");
    QStringList fileNames = dir.entryList(QStringList("*.qm"), QDir::Files, QDir::Name);
    for (QString &fileName : fileNames)
        fileName = dir.filePath(fileName);
    return fileNames;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("WilliamQiufeng");
    QCoreApplication::setOrganizationDomain("williamqiufeng");
    QCoreApplication::setApplicationName("QuaverMetadataEditor");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    // const QStringList uiLanguages = {"zh_CN"};
    auto x = findQmFiles();
    qInfo() << x;
    for (const QString &locale : uiLanguages) {
        const QString baseName = "QuaverMetadataChanger_" + QLocale(locale).name();
        qInfo() << "trying to load " << baseName;
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            qInfo() << baseName << " loaded.";
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
