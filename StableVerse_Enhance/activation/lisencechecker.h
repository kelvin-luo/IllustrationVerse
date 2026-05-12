#ifndef LISENCECHECKER_H
#define LISENCECHECKER_H

#include "LicenseManager.h"
#include "MacAddressHelper.h"
#include <QMessageBox>

class LisenceChecker:public QObject
{
    Q_OBJECT

public:
    LisenceChecker(){
        // if(!m_licenseManager)
        m_licenseManager = new LicenseManager;
    }
    ~LisenceChecker(){
        if(m_licenseManager)delete m_licenseManager;
    }

public:
    LicenseManager *m_licenseManager;

    bool check_activated(){
        bool res = false;
        // Display MAC address
        QString macAddress = MacAddressHelper::getMacAddress();
        // ui->macAddressLabel->setText("MAC Address: " + macAddress);
        if(!m_licenseManager)return false;

        // Check if license exists
        QString licenseKey = m_licenseManager->loadLicense();
        if (!licenseKey.isEmpty()) {
            // ui->licenseKeyEdit->setText(licenseKey);
            res = m_licenseManager->validateLicense(licenseKey, macAddress);
        }
        return res;
    }

    QString m_licenseKey;
    void generate_license(){
        QString macAddress = MacAddressHelper::getMacAddress();
        QString generatedKey = m_licenseManager->generateLicenseKey(macAddress);
        m_licenseKey = generatedKey;
    }

    void activate(){
        QString licenseKey = m_licenseKey;//ui->licenseKeyEdit->text().trimmed();
        QString macAddress = MacAddressHelper::getMacAddress();

        if (licenseKey.isEmpty()) {
            QMessageBox::warning(NULL, "Error", "Please enter a license key");
            return;
        }

        if (m_licenseManager->validateLicense(licenseKey, macAddress)) {
            m_licenseManager->saveLicense(licenseKey);
            QMessageBox::information(NULL, "Success", "License activated successfully!");
        } else {
            QMessageBox::critical(NULL, "Error", "Invalid license key");
        }
    }
};

#endif // LISENCECHECKER_H
