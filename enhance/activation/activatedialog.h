#ifndef ACTIVATEDIALOG_H
#define ACTIVATEDIALOG_H
#include <QDialog>
#include <QCloseEvent>
#include "LicenseManager.h"

namespace Ui {
class ActivateDialog;
}

class ActivateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ActivateDialog(QWidget *parent = nullptr);
    ~ActivateDialog();

    QString macAddress;
    QString licenseKey;
    LicenseManager *m_licenseManager;
    void set_ui_mac();
private slots:
    void on_pushButton_Activate_clicked();

    void on_pushButton_Cancel_clicked();

    void on_pushButton_Free_clicked();
protected :
protected:
    // 重写关闭事件处理函数
    void closeEvent(QCloseEvent *event) override ;

private:
    Ui::ActivateDialog *ui;
};

#endif // ACTIVATEDIALOG_H
