#ifndef PLUG_PLUGIN_HPP
#define PLUG_PLUGIN_HPP

#include <cstddef>

namespace plug
{
    enum class PluginGuid
    {
        Plugin = 0,
        Tool = 1,
        Filter = 2
    };

    class PluginData
    {
        public:
            virtual const char *getName(void) const = 0;
            virtual const char *getTexturePath(void) const = 0;

            virtual ~PluginData() {}
    };

    class Plugin
    {
        public:
            virtual Plugin *tryGetInterface(size_t interface_id) = 0;

            virtual void addReference(void) = 0;

            virtual void release(void) = 0;

            virtual const PluginData *getPluginData(void) const = 0;

            virtual ~Plugin() {}
    };
} // namespace plug

#endif  // PLUG_PLUGIN_HPP

