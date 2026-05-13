#include "LicenseManager.h"
#include <QCryptographicHash>
#include <QSettings>
#include <QFile>
#include <QDir>

LicenseManager::LicenseManager(QObject *parent) : QObject(parent), m_isValid(false)
{
    m_settings=new QSettings("proj_deepseek_ini_setting.ini", QSettings::IniFormat);
}

bool LicenseManager::validateLicense(const QString &licenseKey, const QString &macAddress)
{
    QString expectedKey = generateLicenseKey(macAddress);
    m_isValid = (licenseKey == expectedKey);
    return m_isValid;
}

QString LicenseManager::generateLicenseKey(const QString &macAddress)
{
    // Simple hash-based license generation (for demonstration only)
    // In a real application, use a more secure algorithm
    QString seed = macAddress + "SALT_VALUE_123";
    return simpleHash(seed).left(16).toUpper();
}

bool LicenseManager::isLicenseValid() const
{
    return m_isValid;
}

void LicenseManager::saveLicense(const QString &licenseKey)
{
    // QSettings settings("MyCompany", "MyApp");
    m_settings->setValue("license", licenseKey);
    m_licenseKey = licenseKey;
}

QString LicenseManager::loadLicense()
{
    // QSettings settings("MyCompany", "MyApp");
    m_licenseKey = m_settings->value("license").toString();
    return m_licenseKey;
}

QString LicenseManager::simpleHash(const QString &input)
{
    QByteArray hash = QCryptographicHash::hash(input.toUtf8(), QCryptographicHash::Sha256);
    return QString(hash.toHex());
}
