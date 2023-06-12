#pragma once
#include "../gui.hpp"
#include "lvgl/lvgl.h"

namespace gui {

typedef std::pair<std::string, pros::Motor *> motor_desc_t;

class DevicesView : public View {
  public:
	DevicesView();

	/**
	 * @brief Add motors to dashboard for monitoring
	 *
	 * @param mtrs Motors to monitor
	 */
	void add_motors(std::vector<motor_desc_t> mtrs);

	void refresh();
	void initialize();
};

} // namespace gui