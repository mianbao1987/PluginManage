#include "PluginManager.h"
#include "PluginInstance.h"
#include "DynamicLib.h"

PluginManager::PluginManager(void)
{
	m_vecPlugins.clear();
	m_vecPluginLibs.clear();
}

PluginManager::~PluginManager(void)
{
}

PluginManager &PluginManager::GetInstance()
{
	static PluginManager instance;
	return instance;
}

bool PluginManager::LoadAll()
{
	int nPluginCount = m_vecPlugins.size();
	for (int i = 0; i < nPluginCount; i ++)
	{
		m_vecPlugins[i]->Load();
	}

	return true;
}

PluginInstance* PluginManager::Load(const std::string &strName,int &errCode)
{
	std::map<std::string,DynamicLib *>::iterator iter = m_vecPluginLibs.find(strName);
	if (iter == m_vecPluginLibs.end())	//不存在就需要插入
	{
		DynamicLib* pLib = new DynamicLib;
		if (pLib != NULL)
		{
			pLib->LoadLib(strName.c_str());
			m_vecPluginLibs.insert(make_pair(strName,pLib));
			START_PLUGIN_FUN pFun = (START_PLUGIN_FUN)pLib->GetSymbolAddress("StartPlugin");
			if (pFun != NULL)
			{
				PluginInstance* pPlugin = pFun();
				errCode = 1;

				return pPlugin;
			}

			errCode = 0;
			return NULL;
		}
	}

	else if (iter != m_vecPluginLibs.end())		//如果存在，在插件列表里面寻找名字是strName的插件
	{
		for (int i = 0; i < m_vecPlugins.size(); i ++)
		{
			if (strName == m_vecPlugins[i]->GetDisplayName())
			{
				errCode = 1;
				return m_vecPlugins[i];
			}
		}
	}

	errCode = 0;
	return NULL;
	
}

bool PluginManager::LoadPlugin(PluginInstance *pPlugin)
{
	m_vecPlugins.push_back(pPlugin);
	return true;
}

bool PluginManager::UnLoadAll()
{
	return true;
}

bool PluginManager::UnLoad(const std::string &strName)
{
	std::map<std::string,DynamicLib *>::iterator iter = m_vecPluginLibs.begin();
	for (; iter != m_vecPluginLibs.end(); ++iter )
	{
		DynamicLib *pLib = iter->second;
		if (NULL == pLib)
		{
			continue;
		}
		if (strcmp(pLib->GetName(),strName.c_str()) == 0)
		{
			STOP_PLUGIN_FUN pFun = (STOP_PLUGIN_FUN)pLib->GetSymbolAddress("StopPlugin");
			if (pFun != NULL)
			{
				pFun();
			}

			pLib->FreeLib();
			delete pLib;

			//然后从列表中删除
			m_vecPluginLibs.erase(iter);
			return true;
		}
	}

	return false;
}

bool PluginManager::UnLoadPlugin(PluginInstance *pPlugin)
{
	std::vector<PluginInstance *>::iterator iter = m_vecPlugins.begin();
	for (; iter != m_vecPlugins.end(); ++iter )
	{
		if (pPlugin == *iter)
		{
			//然后从列表中删除
			m_vecPlugins.erase(iter);

			return true;
		}
	}

	return false;
}

std::vector<PluginInstance *> PluginManager::GetAllPlugins()
{
	return m_vecPlugins;
}
