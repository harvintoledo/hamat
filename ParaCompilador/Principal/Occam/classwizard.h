#ifndef CLASSWIZARD_H
#define CLASSWIZARD_H
#include <QWizard>
#include <QByteArray>
#include "classinfopage.h"
#include "codestylepage.h"
#include "intropage.h"
#include "outputfilespage.h"
#include "conclusionpage.h"
class ClassWizard: public QWizard {
    Q_OBJECT
public:
    ClassWizard(QWidget *parent = 0);

    void accept() Q_DECL_OVERRIDE;
};

#endif // CLASSWIZARD_H
