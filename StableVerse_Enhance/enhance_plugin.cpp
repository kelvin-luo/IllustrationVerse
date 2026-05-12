#include "StableVersePluginApi.h"
#include "license.h"

#include <QDebug>

class EnhancePlugin final : public IStableVersePlugin {
public:
    QString pluginId() const override { return QStringLiteral("StableVerse_Enhance"); }
    void initialize() override { (void)checkCommercialLicense(); }
};

STABLEVERSE_PLUGIN_DEFINE(EnhancePlugin)
