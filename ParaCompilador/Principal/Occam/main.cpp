#include "mainwindow.h"
#include "classwizard.h"
#include <QApplication>
#include <QLibraryInfo>
#include <QTranslator>
#include <QLocale>
int main(int argc, char *argv[]) {
    //    QApplication a(argc, argv);
    //    MainWindow w;
    //    w.show();

    //    return a.exec();
   Q_INIT_RESOURCE(classwizard);

    QApplication app(argc, argv);

    #ifndef QT_NO_TRANSLATION
    QString translatorFileName = QLatin1String("qt_");
    translatorFileName += QLocale::system().name();
    QTranslator *translator = new QTranslator(&app);
    if (translator->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
    app.installTranslator(translator);
    #endif

    ClassWizard wizard;
    wizard.show();
    return app.exec();
}
