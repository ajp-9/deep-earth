#pragma once

#ifdef PROFILE
	#include "Timer.hpp"
	#define PROFILE_SCOPE(name, typeName) engine::Timer typeName(name)
#else
	#define PROFILE_SCOPE()
#endif
