#ifndef M_INCLUDE_GUARD_OS_IS_WINDOWS
#define M_INCLUDE_GUARD_OS_IS_WINDOWS

#if defined(_WIN32) || defined(_WIN64)
	#define M_OS_IS_WINDOWS 1
#else
	#define M_OS_IS_WINDOWS 0
#endif

#endif
