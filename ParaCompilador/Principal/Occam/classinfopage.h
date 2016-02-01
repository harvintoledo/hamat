#ifndef CLASSINFOPAGE_H
#define CLASSINFOPAGE_H
#include <QWizardPage>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QVBoxLayout>
class ClassInfoPage : public QWizardPage {
    Q_OBJECT
public:
    ClassInfoPage(QWidget *parent = 0);
private:
    QLabel *classNameLabel;
    QLabel *baseClassLabel;
    QLineEdit *classNameLineEdit;
    QLineEdit *baseClassLineEdit;
    QCheckBox  *qobjectMacroCheckBox;
    QGroupBox *groupBox;
    QRadioButton *qobjectCtorRadioButton;
    QRadioButton *qwidgetCtorRadioButton;
    QRadioButton *defaultCtorRadioButton;
    QCheckBox *copyCtorCheckBox;
};

#endif // CLASSINFOPAGE_H
