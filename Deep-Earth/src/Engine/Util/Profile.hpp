#pragma once

#ifdef PROFILE
	#include "Timer.hpp"
	#define PROFILE_SCOPE(name) engine::Timer Timer(name)
#else
	#define PROFILE_SCOPE()
#endif
