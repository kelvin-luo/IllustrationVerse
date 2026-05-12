#include "StableVersePluginApi.h"

class AnydrawPlugin final : public IStableVersePlugin {
public:
    QString pluginId() const override { return QStringLiteral("Anydraw"); }
};

STABLEVERSE_PLUGIN_DEFINE(AnydrawPlugin)
