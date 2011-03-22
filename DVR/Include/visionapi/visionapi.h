#pragma once
#ifdef WIN32
#ifdef VISIONAPI_EXPORTS
#define VISIONAPI __declspec(dllexport)
#else
#define VISIONAPI __declspec(dllimport)
#endif
#else
#define VISIONAPI
#endif


