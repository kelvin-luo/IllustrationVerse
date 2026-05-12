#include "MacAddressHelper.h"
#include <QNetworkInterface>
#include <QDebug>

QString getMacAddress()
{
    QString macAddress;

    foreach (const QNetworkInterface &interface, QNetworkInterface::allInterfaces()) {
        // 跳过回环接口、未激活接口
        if (interface.type() == QNetworkInterface::Loopback ||
            !(interface.flags() & QNetworkInterface::IsUp))
            continue;

        // 获取硬件地址(MAC)
        QString address = interface.hardwareAddress();
        if (!address.isEmpty()) {
            // 通常第一个非回环网卡的MAC就是我们需要的
            macAddress = address;
            break;
        }
    }

    return macAddress;
}

#include <QString>
#include <QCryptographicHash>
#include <QNetworkInterface>
// #include <QSystemInfo>
#include <QDateTime>

QString getDeviceUID()
{
    QString hardwareInfo;

    // 添加CPU信息
    hardwareInfo.append(QSysInfo::currentCpuArchitecture());
    hardwareInfo.append(QSysInfo::kernelType());
    hardwareInfo.append(QSysInfo::kernelVersion());

    // 添加MAC地址(取第一个非回环地址)
    foreach (const QNetworkInterface &interface, QNetworkInterface::allInterfaces()) {
        if (interface.type() != QNetworkInterface::Loopback &&
            interface.flags() & QNetworkInterface::IsUp) {
            hardwareInfo.append(interface.hardwareAddress());
            break;
        }
    }

    // 添加系统信息
    hardwareInfo.append(QSysInfo::machineHostName());
    hardwareInfo.append(QSysInfo::productType());
    hardwareInfo.append(QSysInfo::productVersion());

    // 添加当前时间戳(降低不同设备相同配置的概率)
    hardwareInfo.append(QDateTime::currentDateTime().toString(Qt::ISODate));

    // 使用SHA-1哈希生成唯一标识
    QByteArray hashedData = QCryptographicHash::hash(
        hardwareInfo.toUtf8(),
        QCryptographicHash::Sha1
        );

    // 转换为十六进制字符串
    return hashedData.toHex();
}

QString MacAddressHelper::getMacAddress()
{
    if(0){
    QString uid = getDeviceUID();
    qDebug()<< "uid: "<<uid  ;
    return uid;
    }

    foreach(QNetworkInterface netInterface, QNetworkInterface::allInterfaces())
    {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        // Qt 5: 可以用 IsVirtual
        // if (interface.flags() & QNetworkInterface::IsVirtual) {
        //     // ...
        // }
#else
// Qt 6: 没有 IsVirtual，自己实现判断逻辑或直接跳过
#endif

        // Return only the first non-loopback and non-virtual MAC Address
        if (!(netInterface.flags() & QNetworkInterface::IsLoopBack) && 
            // !(netInterface.flags() & QNetworkInterface::IsVirtual) && // Qt 6: IsVirtual removed
            !netInterface.humanReadableName().toLower().contains("virtual") &&
            !netInterface.humanReadableName().toLower().contains("vmware") &&
            !netInterface.humanReadableName().toLower().contains("loopback") &&
            !netInterface.humanReadableName().toLower().contains("tunneling") &&
            !netInterface.hardwareAddress().isEmpty())
        {
            return formatMacAddress(netInterface.hardwareAddress());
        }
    }
    return QString();
}

QList<QString> MacAddressHelper::getAllMacAddresses()
{
    QList<QString> macList;
    foreach(QNetworkInterface netInterface, QNetworkInterface::allInterfaces())
    {
        if (!(netInterface.flags() & QNetworkInterface::IsLoopBack) && 
            !netInterface.hardwareAddress().isEmpty())
        {
            macList.append(formatMacAddress(netInterface.hardwareAddress()));
        }
    }
    return macList;
}

QString MacAddressHelper::formatMacAddress(const QString &mac)
{
    return mac.toUpper().remove(':').remove('-');
}
