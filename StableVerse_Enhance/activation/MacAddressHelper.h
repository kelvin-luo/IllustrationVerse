#ifndef MACADDRESSHELPER_H
#define MACADDRESSHELPER_H

#include <QString>
#include <QList>

class MacAddressHelper
{
public:
    static QString getMacAddress();
    static QList<QString> getAllMacAddresses();

private:
    static QString formatMacAddress(const QString &mac);
};

#endif // MACADDRESSHELPER_H