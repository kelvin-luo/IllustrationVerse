#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "LicenseManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onActivateClicked();
    void onCheckLicenseClicked();

    void on_pushButton_deactivate_clicked();

private:
    Ui::MainWindow *ui;
    LicenseManager *m_licenseManager;
    void updateUI();
    void loadStyleSheet();
};
#endif // MAINWINDOW_H
