#ifndef PLUGIN_HPP
#define PLUGIN_HPP

enum class PluginGuid
{
  Plugin = 0,
  Tool   = 1,
  Filter = 2
};

class PluginData
{
public:
  virtual const char* getName(void) const = 0;
  virtual const char* getTexturePath(void) const = 0;

  virtual ~PluginData() = default;
};

class Plugin
{
public:
  virtual Plugin* tryGetInterface(size_t interface_id) = 0;
  virtual void addReference(void) = 0;
  virtual void release(void) = 0;
  virtual const PluginData* getPluginData(void) const = 0;

  virtual ~Plugin() = default;
};

#endif  // PLUGIN_HPP

