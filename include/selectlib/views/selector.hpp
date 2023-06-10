#pragma once
#include "../gui.hpp"
#include "api.h"
#include "liblvgl/lvgl.h"
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace gui {

typedef std::pair<std::string, std::function<void()>> routine_t;

class SelectorView : public View {
  public:
	SelectorView();

	/**
	 * @brief Initialize autonomous manager
	 * @param autons Vector of Routine objects
	 */
	void add_autons(std::vector<routine_t> autons);

	/**
	 * @brief Run selected auton
	 */
	void do_auton();

	void refresh();
	void initialize();
};

} // namespace gui