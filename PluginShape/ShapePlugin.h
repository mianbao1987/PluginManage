#pragma once

#include <string>
#include "PluginInstance.h"

class ShapePlugin : public PluginInstance
{
public:
	explicit ShapePlugin(const std::string &strName);
	~ShapePlugin(void);

	virtual bool Load();

	virtual bool UnLoad();

	//返回插件名字，带后缀，如dll等
	virtual std::string GetFileName() const;

	//返回插件的名字，不带后缀
	virtual std::string GetDisplayName() const;
};
