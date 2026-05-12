#include "StableVersePluginApi.h"

class StableCanvasPlugin final : public IStableVersePlugin {
public:
    QString pluginId() const override { return QStringLiteral("StableCanvas"); }
};

STABLEVERSE_PLUGIN_DEFINE(StableCanvasPlugin)
