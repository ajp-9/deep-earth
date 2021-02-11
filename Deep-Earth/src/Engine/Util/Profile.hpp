#pragma once

#ifdef PROFILE
	#include "Timer.hpp"
	#define PROFILE_SCOPE(name) engine::Timer timer(name)
	#define PROFILE_SCOPE_US(name) engine::Timer timer(name, true)
#else
	#define PROFILE_SCOPE()
	#define PROFILE_SCOPE_US()
#endif
