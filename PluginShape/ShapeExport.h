#ifndef SHAPEEXPORT_INCLUDE 
#define SHAPEEXPORT_INCLUDE


#define EXPORT_API __declspec(dllexport)

class PluginInstance;

extern "C" EXPORT_API PluginInstance *StartPlugin();

extern "C" EXPORT_API void StopPlugin();

#endif	