#include "StableVersePluginApi.h"

class ActivatorPlugin final : public IStableVersePlugin {
public:
    QString pluginId() const override { return QStringLiteral("activator"); }
};

STABLEVERSE_PLUGIN_DEFINE(ActivatorPlugin)
