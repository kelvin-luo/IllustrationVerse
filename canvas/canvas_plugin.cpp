#include "StableVersePluginApi.h"

class CanvasPlugin final : public IStableVersePlugin {
public:
    QString pluginId() const override { return QStringLiteral("canvas"); }
};

STABLEVERSE_PLUGIN_DEFINE(CanvasPlugin)
