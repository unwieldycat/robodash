#include "robodash/detail/platform.h"
#include "api.h"

bool rd::detail::platform::sd_installed() {
#ifdef RD_PLATFORM_PROS
	return pros::usd::is_installed();
#else
	return false;
#endif
}
