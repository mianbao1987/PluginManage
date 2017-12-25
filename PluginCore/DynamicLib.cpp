#include "DynamicLib.h"

DynamicLib::DynamicLib(void)
{
	m_hDynLib = NULL;
	m_pszLibName = NULL;
}

DynamicLib::~DynamicLib(void)
{
	if (m_hDynLib != NULL)
	{
		FreeLib();
	}

	if (m_pszLibName != NULL)
	{
		free(m_pszLibName);
		m_pszLibName = NULL;
	}
}

const char* DynamicLib::GetName() const
{
	return m_pszLibName;
}

#if defined(__unix__) || defined(unix)
#include <dlfcn.h>

bool DynamicLib::LoadLib(const char* strLibName)
{
	std::string strName = strLibName;
	strName += ".so";
	m_hDynLib = dlopen(strName.c_str(), RTLD_LAZY);
	if( pLibrary == NULL )
	{
		return 0;
	}
	m_pszLibName = strdup(strLibName);

	return( 1 );
}

void* DynamicLib::GetSymbolAddress(const char* strSymbolName) const
{
	void	*pSymbol = NULL;

	if (m_hDynLib != NULL)
	{
		pSymbol = dlsym(m_hDynLib,strSymbolName);
	}

	return pSymbol;
}

void DynamicLib::FreeLib()
{
	if (m_hDynLib != NULL)
	{
		dlclose(m_hDynLib);
		m_hDynLib = NULL;
	}

	if (m_pszLibName != NULL)
	{
		free(m_pszLibName);
		m_pszLibName = NULL;
	}
}

#endif

#ifdef _WIN32
#include <Windows.h>

bool DynamicLib::LoadLib(const char* strLibName)
{
	std::string strName = strLibName;
	strName += ".dll";
	m_hDynLib = LoadLibrary(strName.c_str());
	if (m_hDynLib != NULL)
	{
		m_pszLibName = strdup(strLibName);
		return 1;
	}

	return 0;
}

void* DynamicLib::GetSymbolAddress(const char* strSymbolName) const
{
	if (m_hDynLib != NULL)
	{
		return (void*)GetProcAddress((HMODULE)m_hDynLib,strSymbolName);
	}

	return NULL;
}

void DynamicLib::FreeLib()
{
	if (m_hDynLib != NULL)
	{
		FreeLibrary((HMODULE)m_hDynLib);
		m_hDynLib = NULL;
	}

	if (m_pszLibName != NULL)
	{
		free(m_pszLibName);
		m_pszLibName = NULL;
	}
}

#endif
