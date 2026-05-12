#ifndef LICENSEMANAGER_H
#define LICENSEMANAGER_H

#include <QObject>
#include <QString>
#include <QSettings>
class LicenseManager : public QObject
{
    Q_OBJECT

public:
    explicit LicenseManager(QObject *parent = nullptr);

    bool validateLicense(const QString &licenseKey, const QString &macAddress);
    QString generateLicenseKey(const QString &macAddress);
    bool isLicenseValid() const;
    void saveLicense(const QString &licenseKey);
    QString loadLicense();

    //反激活
    void clearLicenseKey() {
        m_licenseKey.clear();
    }

private:
    QString simpleHash(const QString &input);
    QString m_licenseKey;
    bool m_isValid;

    QSettings* m_settings;//=new QSettings("proj_deepseek_ini_setting.ini", QSettings::IniFormat);
};

#endif // LICENSEMANAGER_H
