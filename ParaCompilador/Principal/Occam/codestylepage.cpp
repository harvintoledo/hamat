#include "codestylepage.h"
CodeStylePage::CodeStylePage(QWidget *parent) : QWizardPage(parent) {
    setStyle(tr("Code Style Options"));
    setSubTitle(tr("Choose the formating of the generated code."));
    setPixmap(QWizard::LogoPixmap, QPixmap(":/Images/logo2.png"));

    commentCheckBox = new QCheckBox("&Start generated files with a ");

    setLayout(layout);
}


void CodeStylePage::initializePage() {
    QString className = field("className").toString();
    macroNameLineEdit->setText(className.toUpper()+ "_H");

    QString baseClass = field("baseClass").toString();

    includeBaseCheckBox->setChecked(!baseClass.isEmpty());
    includeBaseCheckBox->setEnabled(!baseClass.isEmpty());
    baseIncludeLabel->setEnabled(!baseClass.isEmpty());
    baseIncludeLineEdit->setEnabled(!baseClass.isEmpty());

    if(baseClass.isEmpty()) {
        baseIncludeLineEdit->clear();
    }
    else if(QRegExp("Q[A-Z].*").exactMatch(baseClass)) {
        baseIncludeLineEdit->setText("<" + baseClass + ">");
    }
    else {
        baseIncludeLineEdit->setText("\"" + baseClass.toLower() + ".h\"");
    }
}
