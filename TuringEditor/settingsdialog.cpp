#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QSettings>

#include "osinterop.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    // populate themese
    ui->theme->addItem("Default");
    ui->theme->addItem("Dark");

    // load settings
    QSettings settings;

    QString theme = settings.value("theme", "Default").toString();
    ui->theme->setCurrentIndex(theme == "Default" ? 0 : 1);

    QFont curFont = QFont(settings.value("editorFont","Courier New").toString());
    ui->fontSelect->setCurrentFont(curFont);

    // ints
    ui->fontSize->setValue(settings.value("fontSize", 10).toInt());
    ui->indentSize->setValue(settings.value("indentSize", 4).toInt());
    ui->autoCompThresh->setValue(settings.value("autoCompleteThreshold", 5).toInt());
    // bools
    ui->autoComp->setChecked(settings.value("autoCompleteEnabled", true).toBool());
    ui->saveOnRun->setChecked(settings.value("saveOnRun", true).toBool());
    ui->confirmSave->setChecked(settings.value("confirmSave", true).toBool());
    //ui->lineNumbers->setChecked(settings.value("showLineNumbers", true).toBool());
    ui->stringEOLHighlight->setChecked(settings.value("stringEOLHighlight", false).toBool());
}

void SettingsDialog::accept() {
    QSettings settings;

    settings.setValue("theme",ui->theme->currentText());

    settings.setValue("editorFont",ui->fontSelect->currentFont().family());

    // ints
    settings.setValue("fontSize",ui->fontSize->value());
    settings.setValue("indentSize",ui->indentSize->value());
    settings.setValue("autoCompleteThreshold",ui->autoCompThresh->value());
    // bools
    settings.setValue("autoCompleteEnabled",(ui->autoComp->checkState() == Qt::Checked));
    settings.setValue("saveOnRun",(ui->saveOnRun->checkState() == Qt::Checked));
    settings.setValue("confirmSave",(ui->confirmSave->checkState() == Qt::Checked));
    //settings.setValue("showLineNumbers",(ui->lineNumbers->checkState() == Qt::Checked));
    settings.setValue("stringEOLHighlight",(ui->stringEOLHighlight->checkState() == Qt::Checked));

    done(QDialog::Accepted);
}

void SettingsDialog::associateFiles() {
    OSInterop::associateTuringFiles();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
