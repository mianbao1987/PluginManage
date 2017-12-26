
#ifndef PLUGINMANAGER_INCLUDE 
#define PLUGINMANAGER_INCLUDE

#include "Export.h"
#include <boost/thread/thread.hpp>

class PluginInstance;
class DynamicLib;

typedef boost::unique_lock<boost::shared_mutex> ReadLock;
typedef boost::shared_lock<boost::shared_mutex> WriteLock;


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
	std::map<std::string,DynamicLib *> m_mapPluginLibs;	//²å¼þÄ£¿é¾ä±ú
	boost::shared_mutex  read_write_mutex_vec;
	boost::shared_mutex  read_write_mutex_map;

};

#endif
