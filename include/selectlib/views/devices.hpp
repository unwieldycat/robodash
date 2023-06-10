#pragma once
#include "../gui.hpp"
#include "liblvgl/lvgl.h"

namespace gui {

class DevicesWindow : public Window {
  public:
	DevicesWindow();

	/**
	 * @brief Add motors to dashboard for monitoring
	 *
	 * @param mtrs Motors to monitor
	 */
	void add_motors(std::vector<pros::Motor *> mtrs);

	void refresh();
	void initialize();
};

} // namespace gui