#pragma once

#include "global.h"

#if DEBUG == true
	#define LOGGER_DEBUG = true
#elif NDEBUG == true
	#define LOGGER_DEBUG = false
#else
	// TODO: Handle if this is broken
#endif

// Whether the logger displays warning messages or not.
#define LOGGER_WARNINGS = true
// Whether the logger displays informational messages or not.
#define LOGGER_INFOS	= true