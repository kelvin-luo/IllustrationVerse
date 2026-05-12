#include "StableVersePluginApi.h"

class ActivatorPlugin final : public IStableVersePlugin {
public:
    QString pluginId() const override { return QStringLiteral("StableVerse_Activator"); }
};

STABLEVERSE_PLUGIN_DEFINE(ActivatorPlugin)
