#ifndef CODESTYLEPAGE_H
#define CODESTYLEPAGE_H
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QWizardPage>

class CodeStylePage : QWizardPage{
    Q_OBJECT
public:
    CodeStylePage(QWidget *parent = 0);
protected:
    void initializePage() Q_DECL_OVERRIDE;

private:
    QCheckBox *commentCheckBox;
    QCheckBox *protectedCheckBox;
    QCheckBox *includeBaseCheckBox;
    QLabel *macroNameLabel;
    QLabel *baseIncludeLabel;
    QLineEdit *macroNameLineEdit;
    QLineEdit *baseIncludeLineEdit;
};

#endif // CODESTYLEPAGE_H
