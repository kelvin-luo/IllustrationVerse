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

    QSettings * m_settings;//("MyCompany", "MyApp");
private:
    QString simpleHash(const QString &input);
    QString m_licenseKey;
    bool m_isValid;
};

#endif // LICENSEMANAGER_H
