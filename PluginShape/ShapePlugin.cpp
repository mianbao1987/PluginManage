#include "ShapePlugin.h"

ShapePlugin::ShapePlugin(const std::string &strName)
:PluginInstance(strName)
{
	//const std::string &strName
}

ShapePlugin::~ShapePlugin(void)
{
}

bool ShapePlugin::Load()
{
	return 1;
}

bool ShapePlugin::UnLoad()
{
	return 1;
}

std::string ShapePlugin::GetFileName() const
{
	std::string str = "";
	return "PluginShape.dll";
}

std::string ShapePlugin::GetDisplayName() const
{
	return "PluginShape";
}
