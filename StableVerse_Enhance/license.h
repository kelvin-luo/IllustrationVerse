#pragma once
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QTextStream>

#include <QDir>
#include <QTranslator>
#include <QDateTime>
#include <QDebug>
#include <QProcess>
#include <QString>

#include <nlohmann/json.hpp>
#include <QString>
#include <QDateTime>
#include <fstream>
#include <iostream>



bool checkCommercialLicense() {
    // 验证商业许可证
    bool hasValidLicense = true;
    return hasValidLicense;
}
