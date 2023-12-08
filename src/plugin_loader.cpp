#include <dlfcn.h>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#include "plugin_loader.hpp"

// static const char *BASE_DIR = "Plugins/";
static const int32_t MAX_PATH_LEN = 256;

static plug::Plugin* loadPlugin(const char *dll_path)
{
    void *library = dlopen(dll_path, RTLD_LAZY | RTLD_LOCAL | RTLD_NODELETE);
    if (!library)
        return nullptr;
    
    typedef plug::Plugin* plugin_loader_t(void);
    plugin_loader_t *load = (plugin_loader_t*) dlsym(library, "loadPlugin");
    if (!load)
        return nullptr;

    plug::Plugin* plugin = load();
    if (!plugin)
        return nullptr;

    if (dlclose(library) < 0)
        return nullptr;

    return plugin;
}

void loadPlugins(const char *path, FilterPalette &filter_palette, ToolPalette &tool_palette)
{
    char *full_path = (char*) calloc(MAX_PATH_LEN, sizeof(char));
    strcat(full_path, path);

    DIR *dir = opendir(full_path);
    if (dir != nullptr)
    {
        struct dirent *file = nullptr;
        while ((file = readdir(dir)) != nullptr)
        {
            if (!strcmp(file->d_name, "."))  continue;
            if (!strcmp(file->d_name, "..")) continue;

            char *next_path = (char*) calloc(MAX_PATH_LEN, sizeof(char));
            sprintf(next_path, "%s/%s", full_path, file->d_name);
            loadPlugins(next_path, filter_palette, tool_palette);
            free(next_path);
        }

        closedir(dir);
    }
    else
    {
        size_t len = strlen(path);
        if (len < 3 || strncmp(path + len - 3, ".so", 3))
            return;

        plug::Plugin *plugin = loadPlugin(path);
        if (plugin != nullptr)
        {
            tool_palette  .loadPlugin(plugin);
            filter_palette.loadPlugin(plugin);
        }
    }

    free(full_path);
}

