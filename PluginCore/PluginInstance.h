
#ifndef PLUGININSTANCE_INCLUDE
#define PLUGININSTANCE_INCLUDE


#include "Export.h"

class PLUGINCORE_API PluginInstance
{
public:
	explicit PluginInstance(const std::string &strName);
	virtual ~PluginInstance(void);

	virtual bool Load() = 0;

	virtual bool UnLoad() = 0;

	//返回插件名字，带后缀，如dll等
	virtual std::string GetFileName() const = 0;

	//返回插件的名字，不带后缀
	virtual std::string GetDisplayName() const = 0;

private:
	PluginInstance(const PluginInstance &rhs);
	const PluginInstance &operator=(const PluginInstance &rhs);	//待实现
};

//插件加载和卸载时调用的函数
typedef PluginInstance *( *START_PLUGIN_FUN )();
typedef void( *STOP_PLUGIN_FUN )();

#endif
