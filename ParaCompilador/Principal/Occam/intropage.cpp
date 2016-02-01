#include "intropage.h"

IntroPage::IntroPage(QWidget *parent) : QWizardPage(parent) {
    setTitle(tr("Introduction"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/Images/watermark1.png"));

    label = new QLabel(tr("This wizard will generate a skelenton C++ class "
                          "definition, including a few function. You simplify "
                          "need to spicify the class name a set a few "
                          "options to produce a header file and an "
                          "Implementation file for your new C++ class."));
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

