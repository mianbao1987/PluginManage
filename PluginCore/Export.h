#ifndef PLUGINCORE_EXPORTS_INCLUDE
#define PLUGINCORE_EXPORTS_INCLUDE


#ifdef PLUGINCORE_EXPORTS		
	#ifdef __GNUC__
			#define PLUGINCORE_API __attribute__((dllexport))
		#else
			#define PLUGINCORE_API __declspec(dllexport)
	#endif
	#else
		#ifdef __GNUC__
			#define PLUGINCORE_API __attribute__((dllimport))
		#else
			#define PLUGINCORE_API __declspec(dllimport)
	#endif
#endif

//引入一些必要的头文件
#include <string>
#include <vector>
#include <map>

typedef void* HLIB;		//动态库句柄

#endif	//include