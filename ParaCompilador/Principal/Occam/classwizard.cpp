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

    QByteArray block;

    if(field("comment").toBool()) {
        block +="/*\n";
        block += "   " + header.toLatin1() + "\n";
        block += "*/\n";
        block += "\n";
    }

    if(field("protected").toBool()) {
        block += "#ifndef " + macroName + "\n";
        block += "#define " + macroName + "\n";
        block += "\n";
    }

    if(field("includeBase").toBool()) {
        block += "#include " + baseInclude + "\n";
        block += "\n";
    }

    block += "class " + className;
    if(!baseClass.isEmpty())
        block += " : public " + baseClass;

    block += "\n";
    block += "{\n";

    /*qmake ignore Q_OBJECT */

    if(field("qobjectMacro").toBool()) {
        block += "    Q_OBJECT\n";
        block += "\n";
    }

    block += "public:\n";

    if(field("qobjectCtor").toBool()) {
        block += "   " + className + "(QObject *parent = 0);\n";
    }
    else if(field("qwidgetCtor").toBool()) {
        block += "   " + className + "(QWidget *parent = 0);\n";
    }
    else if(field("defaultCtor").toBool()) {
        block += "    " + className + "();\n";
        if(field("copyCtor").toBool()) {
            block += "    " + className + "(const " + className + " &other);\n";
            block += "\n";
            block += "    " + className + " &operator = " + "(const " + className + " &other);\n";
        }
    }
    block += "};\n";

    QFile headerFile(outputDir + "/" + header);
    if(!headerFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Simple Wizard"),
                             QObject::tr("Cannot write file %1:\n%2")
                             .arg(headerFile.fileName())
                             .arg(headerFile.errorString()));
        return;
    }
    headerFile.write(block);

    block.clear();

    if(field("comment").toBool()) {
        block += "/*\n";
        block += "    " + implementation.toLatin1() + "\n";
        block += "*/\n";
        block += "\n";
    }

    block += "#include \"" + header.toLatin1() +"\"\n";
    block += "\n";

    if(field("qobjectCtor").toBool()) {
        block += className + "::" + className + "(QObject *parent)\n";
        block += "    : " + baseClass + "(parent)\n";
        block += "{\n";
        block += "}\n";
    }
    else if(field("qwidgetCtor").toBool()) {
        block += className + "::" +className + "(QWidget *parent)\n";
        block += "    : " + baseClass + "(parent)\n";
        block += "{\n";
        block += "}\n";
    }
    else if(field("defaultCtor").toBool()) {
        block += className + "::" + className + "()\n";
        block += "{\n";
        block += "    // mising code";
        block += "}\n";
        if(field("copyCtor").toBool()) {
            block += "\n";
            block += className + "::" + className + "(const " + className
                    + " &other)\n";
            block += "{\n";
            block += "    *this = other;\n";
            block += "}\n";
            block += "\n";
            block += className + " &" + className + "::operator=(const "
                    + className + " &other\n";
            block += "{\n";
            if(!baseClass.isEmpty())
                block += "    " + baseClass + "::operator=(other);\n";
            block += "    //missing code\n";
            block += "    return *this;\n";
            block += "}\n";
        }
    }

    QFile implementationFile(outputDir + "/" + implementation);

    if(!implementationFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Simple Wizard"),
                             QObject::tr("Cannot write file %1:\n%2")
                             .arg(implementationFile.fileName())
                             .arg(implementationFile.errorString()));
        // Retornar sino tuvo éxito al abrir el archivo
        return;
    }
    implementationFile.write(block);
    QDialog::accept();
}

IntroPage::IntroPage(QWidget *parent) : QWizardPage(parent) {
    setTitle(tr("Introduction"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/Images/watermark1.png"));

    label = new QLabel(tr("This wizard will generate a skelenton C++ class "
                          "definition, including a few function. You simply "
                          "need to specify the class name a set a few "
                          "options to produce a header file and an "
                          "Implementation file for your new C++ class."));
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}


ClassInfoPage::ClassInfoPage(QWidget *parent)
    : QWizardPage(parent) {
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

   qobjectCtorRadioButton = new QRadioButton(tr("&QObject-style constructor"));
   qwidgetCtorRadioButton = new QRadioButton(tr("&QWidget-style consturctor"));
   defaultCtorRadioButton = new QRadioButton(tr("&Default constructor"));
   copyCtorCheckBox = new QCheckBox(tr("&Generate copy constructor and "
                                      "operator="));


   defaultCtorRadioButton->setChecked(true);

   connect(defaultCtorRadioButton, SIGNAL(toggled(bool)),
           copyCtorCheckBox, SLOT(setEnabled(bool)));

   registerField("className*", classNameLineEdit);
   registerField("baseClass", baseClassLineEdit);
   registerField("qobjectMacro", qobjectMacroCheckBox);
   registerField("qobjectCtor", qobjectCtorRadioButton);
   registerField("qwidgetCtor", qwidgetCtorRadioButton);
   registerField("defaultCtor", defaultCtorRadioButton);
   registerField("copyCtor", copyCtorCheckBox);

   QVBoxLayout *groupBoxLayout = new QVBoxLayout;

   groupBoxLayout->addWidget(qobjectCtorRadioButton);
   groupBoxLayout->addWidget(qwidgetCtorRadioButton);
   groupBoxLayout->addWidget(defaultCtorRadioButton);
   groupBoxLayout->addWidget(copyCtorCheckBox);

   groupBox->setLayout(groupBoxLayout);

   QGridLayout *layout = new QGridLayout;
   layout->addWidget(classNameLabel, 0, 0);
   layout->addWidget(classNameLineEdit, 0, 1);
   layout->addWidget(baseClassLabel, 1, 0);
   layout->addWidget(baseClassLineEdit, 1, 1);
   layout->addWidget(qobjectMacroCheckBox, 2, 0, 1, 2);
   layout->addWidget(groupBox, 3, 0, 1, 2);

   setLayout(layout);

}

CodeStylePage::CodeStylePage(QWidget *parent) : QWizardPage(parent) {
    setStyle(tr("Code Style Options"));
    setSubTitle(tr("Choose the formating of the generated code."));
    setPixmap(QWizard::LogoPixmap, QPixmap(":/Images/logo2.png"));

    commentCheckBox = new QCheckBox("&Start generated files with a ");

    commentCheckBox->setChecked(true);

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
