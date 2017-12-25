#include <stdio.h>

#include "PluginInstance.h"
#include "PluginManager.h"

void main()
{
	PluginManager &pluManager = PluginManager::GetInstance();
	int errCode;
	PluginInstance *pInstance = pluManager.Load("PluginShape",errCode);
	pInstance = pluManager.Load("PluginShape",errCode);

	printf("%s,%d\n",pInstance->GetFileName().c_str(),errCode);

	pluManager.UnLoad("PluginShape");
	printf("%d\n",pluManager.GetAllPlugins().size());

}