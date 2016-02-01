#ifndef INTROPAGE_H
#define INTROPAGE_H
#include <QWizardPage>
#include <QLabel>
#include <QVBoxLayout>
class IntroPage : QWizardPage {
    Q_OBJECT
public:
    IntroPage(QWidget *parent = 0);
private:
    QLabel *label;
};

#endif // INTROPAGE_H
