#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "MacAddressHelper.h"
#include <QMessageBox>
#include <QFile>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_licenseManager(new LicenseManager(this))
{
    ui->setupUi(this);
    setWindowTitle("Software License Activation");
    
    // Load style sheet
    loadStyleSheet();
    
    // Display MAC address
    QString macAddress = MacAddressHelper::getMacAddress();
    ui->macAddressLabel->setText("MAC Address: " + macAddress);
    
    // Check if license exists
    QString licenseKey = m_licenseManager->loadLicense();
    if (!licenseKey.isEmpty()) {
        ui->licenseKeyEdit->setText(licenseKey);
        m_licenseManager->validateLicense(licenseKey, macAddress);
    }
    
    updateUI();
    
    connect(ui->activateButton, &QPushButton::clicked, this, &MainWindow::onActivateClicked);
    connect(ui->checkLicenseButton, &QPushButton::clicked, this, &MainWindow::onCheckLicenseClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onActivateClicked()
{
    QString licenseKey = ui->licenseKeyEdit->text().trimmed();
    QString macAddress = MacAddressHelper::getMacAddress();
    
    if (licenseKey.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a license key");
        return;
    }
    
    if (m_licenseManager->validateLicense(licenseKey, macAddress)) {
        m_licenseManager->saveLicense(licenseKey);
        QMessageBox::information(this, "Success", "License activated successfully!");
    } else {
        QMessageBox::critical(this, "Error", "Invalid license key");
    }
    
    updateUI();
}

#include "MyDialog.h"
void MainWindow::onCheckLicenseClicked()
{
    QString macAddress = MacAddressHelper::getMacAddress();
    QString generatedKey = m_licenseManager->generateLicenseKey(macAddress);

#if 0
    QMessageBox::information(this, "License Key", 
        QString("Your generated license key is:\n%1\n\nUse this key to activate the software.")
        .arg(generatedKey));
#endif
    LicenseKeyDialog dialog(generatedKey, this);
    dialog.exec();
}

void MainWindow::updateUI()
{
    bool isValid = m_licenseManager->isLicenseValid();
    ui->statusLabel->setText(isValid ? "Status: Licensed" : "Status: Not Licensed");
    
    if (isValid) {
        ui->statusLabel->setStyleSheet("color: green; font-weight: bold;");
        ui->activateButton->setEnabled(false);
        ui->checkLicenseButton->setEnabled(false);
    } else {
        ui->statusLabel->setStyleSheet("color: red; font-weight: bold;");
        ui->activateButton->setEnabled(true);
        ui->checkLicenseButton->setEnabled(true);
    }
}

void MainWindow::loadStyleSheet()
{
    QFile file(":/resources/styles.qss");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(styleSheet);
        file.close();
    }
}

#include <QSettings>
void MainWindow::on_pushButton_deactivate_clicked()
{
    m_licenseManager->clearLicenseKey();
    // QSettings settings("MyCompany", "MyApp");
    QSettings *settings=m_licenseManager->m_settings;//("MyCompany", "MyApp");
    settings->setValue("license", "");
    // m_settings.remove("LicenseKey");

    QMessageBox::information(this, "Success", "License deactivated successfully!");
    updateUI();
}

