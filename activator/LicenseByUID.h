#ifndef LICENSEBYUID_H
#define LICENSEBYUID_H

#include <QString>
#include <QCryptographicHash>
#include <QNetworkInterface>
// #include <QSystemInfo>
#include <QDateTime>
#include <QSettings>
#include <QDebug>

class LicenseManagerByUID {
public:
    // 获取单例实例
    static LicenseManagerByUID& instance() {
        static LicenseManagerByUID manager;
        return manager;
    }

    // 获取当前设备的机器码
    QString getMachineCode() {
        QString hardwareInfo;

        // 收集硬件信息
        hardwareInfo.append(QSysInfo::currentCpuArchitecture());
        hardwareInfo.append(QSysInfo::machineHostName());

        // 添加所有非回环网络接口的MAC地址
        foreach (const QNetworkInterface &interface, QNetworkInterface::allInterfaces()) {
            if (interface.type() != QNetworkInterface::Loopback &&
                interface.flags() & QNetworkInterface::IsUp) {
                hardwareInfo.append(interface.hardwareAddress());
            }
        }

        // 使用SHA-256生成机器码
        QByteArray hashedData = QCryptographicHash::hash(
            hardwareInfo.toUtf8(),
            QCryptographicHash::Sha256
            );

        return hashedData.toHex();
    }

    // 生成授权码(此函数通常在服务器端使用)
    QString generateLicenseKey(const QString& machineCode, const QString& secretKey,
                               const QDate& expireDate = QDate::currentDate().addYears(1)) {
        QString licenseData = machineCode + "|" +
                              secretKey + "|" +
                              expireDate.toString("yyyy-MM-dd");

        QByteArray hashedData = QCryptographicHash::hash(
            licenseData.toUtf8(),
            QCryptographicHash::Sha256
            );

        // 格式: 机器码前缀-日期哈希-校验和
        return machineCode.left(16) + "-" +
               expireDate.toString("yyyyMMdd") + "-" +
               hashedData.toHex().left(16);
    }

    // 验证授权码
    bool verifyLicenseKey(const QString& licenseKey, const QString& secretKey) {
        // 检查格式
        QStringList parts = licenseKey.split("-");
        if (parts.size() != 3) return false;

        QString machineCodePrefix = parts[0];
        QString expireDateStr = parts[1];
        QString checksum = parts[2];

        // 验证机器码前缀
        QString currentMachineCode = getMachineCode();
        if (!currentMachineCode.startsWith(machineCodePrefix)) {
            qDebug() << "Machine code mismatch";
            return false;
        }

        // 解析过期日期
        QDate expireDate = QDate::fromString(expireDateStr, "yyyyMMdd");
        if (!expireDate.isValid() || expireDate < QDate::currentDate()) {
            qDebug() << "License expired";
            return false;
        }

        // 重新计算校验和
        QString licenseData = currentMachineCode + "|" +
                              secretKey + "|" +
                              expireDate.toString("yyyy-MM-dd");

        QByteArray hashedData = QCryptographicHash::hash(
            licenseData.toUtf8(),
            QCryptographicHash::Sha256
            );

        QString expectedChecksum = hashedData.toHex().left(16);
        if (checksum != expectedChecksum) {
            qDebug() << "Checksum mismatch";
            return false;
        }

        // 验证通过，保存授权信息
        saveLicenseInfo(licenseKey, expireDate);
        return true;
    }

    // 检查是否已激活
    bool isActivated() {
        QSettings settings("YourCompany", "YourApp");
        return settings.contains("license/key") &&
               settings.contains("license/expireDate");
    }

    // 检查授权是否有效
    bool isLicenseValid() {
        if (!isActivated()) return false;

        QSettings settings("YourCompany", "YourApp");
        QString licenseKey = settings.value("license/key").toString();
        QDate expireDate = settings.value("license/expireDate").toDate();

        // 检查日期有效性
        if (expireDate < QDate::currentDate()) {
            qDebug() << "License expired";
            return false;
        }

        // 可以选择在这里进行更严格的验证
        return true;
    }

    // 获取剩余天数
    int getRemainingDays() {
        if (!isActivated()) return 0;

        QSettings settings("YourCompany", "YourApp");
        QDate expireDate = settings.value("license/expireDate").toDate();
        return QDate::currentDate().daysTo(expireDate);
    }

    // 保存授权信息到注册表/配置文件
    void saveLicenseInfo(const QString& licenseKey, const QDate& expireDate) {
        QSettings settings("YourCompany", "YourApp");
        settings.setValue("license/key", licenseKey);
        settings.setValue("license/expireDate", expireDate);
        settings.setValue("license/activatedDate", QDate::currentDate());
    }

    // 移除授权信息
    void removeLicense() {
        QSettings settings("YourCompany", "YourApp");
        settings.remove("license");
    }

private:
    // 私有构造函数，防止外部实例化
    LicenseManagerByUID() {}
    ~LicenseManagerByUID() {}

    // 禁用拷贝构造和赋值运算符
    LicenseManagerByUID(const LicenseManagerByUID&) = delete;
    LicenseManagerByUID& operator=(const LicenseManagerByUID&) = delete;
};

#endif // LICENSEBYUID_H
