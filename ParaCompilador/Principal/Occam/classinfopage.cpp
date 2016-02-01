#include "classinfopage.h"

ClassInfoPage::ClassInfoPage(QWidget *parent) : QWizardPage(parent){
   setTitle(tr("Class Information"));
   setSubTitle(tr("Specify basic information about the class for wich you "
                  "want to generate skeleton source code file."));
   setPixmap(QWizard::LogoPixmap, QPixmap(":/Images/logo1.png"));

   classNameLabel = new QLabel(tr("&Class name:"));
   classNameLineEdit = new QLineEdit;
   classNameLabel->setBuddy(classNameLineEdit);


   baseClassLabel = new QLabel(tr("B&ase class:"));
   baseClassLineEdit = new QLineEdit;
   baseClassLabel->setBuddy(baseClassLineEdit);

   qobjectMacroCheckBox = new QCheckBox(tr("Generate Q_OBJECT &macro"));

   groupBox = new QGroupBox(tr("C&onstructor"));

   registerField("className*", classNameLineEdit);
   registerField("baseClass", baseClassLineEdit);
   registerField("qobjectMacro", qobjectMacroCheckBox);
   registerField("qobjectCtor", qobjectCtorRadioButton);
   registerField("qobjectCtor", qwidgetCtorRadioButton);
   registerField("defaultCtor", defaultCtorRadioButton);
   registerField("copyCtor", copyCtorCheckBox);

   QVBoxLayout *groupBoxLayout = new QVBoxLayout;

}

