#pragma once

#ifdef GS_PLATFORM_WINDOWS
	#ifdef GS_BUILD_DLL
		#define GENESIS_API __declspec(dllexport)
	#else
		#define GENESIS_API __declspec(dllimport)
	#endif
#else
	#error Genesis only supports windows
#endif

#define BIT(x) 1 << (x)