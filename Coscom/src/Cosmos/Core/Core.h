#ifndef CORE_H
#define CORE_H

#ifdef CM_PLATFORM_WINDOWS
	#ifdef CM_BUILD_DLL
		#define CM_API __declspec(dllexport)
	#else
		#define CM_API __declspec(dllimport)
	#endif// CM_BUILD_DLL
#endif // PLATFORM_WINDOWS

#endif //!CORE_H