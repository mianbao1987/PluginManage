#ifndef DYNAMICLIB_INCLUDE
#define DYNAMICLIB_INCLUDE

//动态库加载，取函数地址，供内部使用
#include "Export.h"

class DynamicLib
{
public:
	DynamicLib(void);
	~DynamicLib(void);

	const char* GetName() const;

	//装载动态库
	bool LoadLib(const char* strLibName);

	void* GetSymbolAddress(const char* strSymbolName) const;

	void FreeLib();

private:
	HLIB m_hDynLib;		//动态库句柄
	char* m_pszLibName;	//动态库名字
};

#endif
