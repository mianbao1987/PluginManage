
#ifndef PLUGINMANAGER_INCLUDE 
#define PLUGINMANAGER_INCLUDE

#include "Export.h"

class PluginInstance;
class DynamicLib;

class PLUGINCORE_API PluginManager
{
public:
	static PluginManager &GetInstance();

	bool LoadAll();

	PluginInstance* Load(const std::string &strName,int &errCode);

	bool LoadPlugin(PluginInstance *pPlugin);

	bool UnLoadAll();

	bool UnLoad(const std::string &strName);

	bool UnLoadPlugin(PluginInstance *pPlugin);

	std::vector<PluginInstance *> GetAllPlugins();

private:
	PluginManager(void);
	~PluginManager(void);
	PluginManager(const PluginManager &rhs);
	const PluginManager &operator=(const PluginManager &rhs);

	std::vector<PluginInstance *> m_vecPlugins;	//²å¼þÊµÀý¾ä±ú
	std::map<std::string,DynamicLib *> m_vecPluginLibs;	//²å¼þÄ£¿é¾ä±ú
};

#endif
