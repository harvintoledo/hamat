#include "classwizard.h"

ClassWizard::ClassWizard(QWidget *parent) : QWizard(parent) {
        addPage(new IntroPage);
        addPage(new ClassInfoPage);
        addPage(new CodeStylePage);
        addPage(new OutputFilesPage);
        addPage(new ConclusionPage);

        setPixmap(QWizard::BannerPixmap, QPixmap(":/Images/banners.png"));
        setPixmap(QWizard::BackgroundPixmap, QPixmap(":/Images/background.png"));

        setWindowTitle("Class Wizard");
}

void ClassWizard::accept() {
    QByteArray className = field("className").toByteArray();
    QByteArray baseClass = field("baseClass").toByteArray();
    QByteArray macroName = field("macroName").toByteArray();
    QByteArray baseInclude = field("baseInclude").toByteArray();

    QString outputDir = field("outputDir").toString();
    QString header = field("header").toString();
    QString implementation = field("implementation").toString();

    QDialog::accept();
}
