#pragma encoding("UTF-8")
#pragma execution_character_set("utf-8")

#include "utilitiesenhence.h"

#include "activatedialog.h"
#include "ui_activatedialog.h"

ActivateDialog::ActivateDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ActivateDialog)
{
    ui->setupUi(this);

    this->ui->lineEdit_MacCode->setText( macAddress);
}
void ActivateDialog::set_ui_mac(){
    this->ui->lineEdit_MacCode->setText( macAddress);
}

ActivateDialog::~ActivateDialog()
{
    delete ui;
}


#include <QMessageBox>
void ActivateDialog::on_pushButton_Activate_clicked()
{
    if(!m_licenseManager)return ;
    licenseKey = this->ui->lineEdit_ActivateCode->text();
    if (m_licenseManager->validateLicense(licenseKey, macAddress)) {
        m_licenseManager->saveLicense(licenseKey);
        if(0) QMessageBox::information(this, "Success", "License activated successfully!");
        showCustomInfoMessageBox(this, "Success", "License activated successfully!");
    } else {
        if(0)QMessageBox::critical(this, "Error", "Invalid license key");
        showCustomCriticalMessageBox(this, "Error", "激活失败！");
    }
}


void ActivateDialog::on_pushButton_Cancel_clicked()
{
    // 关闭对话框
    reject(); // 等同于调用 done(QDialog::Rejected);
    if(0) QMessageBox::information(this, "Info", "continue using free version!");
    showCustomInfoMessageBox(this, "Info", "continue using free version!");
}


void ActivateDialog::on_pushButton_Free_clicked()
{
    // 关闭对话框
    reject(); // 等同于调用 done(QDialog::Rejected);
    if(0)  QMessageBox::information(this, "Info", "continue using free version!");
    showCustomInfoMessageBox(this, "Info", "continue using free version!");
}

void ActivateDialog::closeEvent(QCloseEvent *event)   {
    // 在关闭对话框前显示确认消息
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认关闭", "确定要关闭对话框吗？",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // 接受关闭事件，允许对话框关闭
        event->accept();
        // 可以在这里添加关闭前的清理工作
    } else {
        // 忽略关闭事件，阻止对话框关闭
        event->ignore();
    }
    showCustomInfoMessageBox(this, "Info", "continue using free version!");
}

#include "MacAddressHelper.h"
#include "activatedialog.h"
#include "lisencechecker.h"
#if  1
void check_is_activated(){
    bool activated = false;
    // QWidget * ui;
    if (!activated) {
        // ui->plainTextEdit_cmd->setEnabled(false);
        // ui->plainTextEdit_cmd->hide();

        // ui->tabWidget_Editor->widget(1)->setEnabled(false);
        // ui->tabWidget_Editor->widget(1)->hide();

        // ui->tabWidget_Editor->setCurrentIndex(0);

        QMessageBox::warning(NULL, "提示",
                             "系统查询到您是免费用户，如果需要专业功能请升级到高"
                             "级版。请联系http://github.com/roie2022/abc");

        {
            LisenceChecker checker;
            // checker.m_licenseManager = m_licenseManager;
            activated = checker.check_activated();
            if (!activated) {
                // ui->plainTextEdit_cmd->setEnabled(false);
                // ui->plainTextEdit_cmd->hide();

                // ui->tabWidget_Editor->widget(1)->setEnabled(false);
                // ui->tabWidget_Editor->widget(1)->hide();

                // ui->tabWidget_Editor->setCurrentIndex(0);

                ActivateDialog * actor;
                // if(!actor)
                // actor = new ActivateDialog ;
                actor->macAddress = MacAddressHelper::getMacAddress();
                actor->set_ui_mac();
                actor->m_licenseManager = checker.m_licenseManager;
                actor->setModal(true);
                actor->show();
            }
        }

        return;
    }
    // else {
    //     // m_cmd.use_gpu = false;
    //     ui->plainTextEdit_cmd->setEnabled(true);
    //     ui->plainTextEdit_cmd->show();

    //     ui->tabWidget_Editor->widget(1)->setEnabled(true);
    //     ui->tabWidget_Editor->widget(1)->show();
    //     // ui->tabWidget_Editor->setCurrentIndex(1);
    // }
}
#endif

