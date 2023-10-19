/**
 * @file selector.hpp
 * @brief Robodash SelectorView
 *
 * Built-in SelectorView class for function selecting, primarily for autonomous
 * routines.
 */

#pragma once
#include "../gui.hpp"
#include "api.h"
#include "lvgl/lvgl.h"
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace gui {

namespace views {

typedef std::function<void()> routine_action_t;
typedef std::pair<std::string, routine_action_t> routine_t;

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

} // namespace views

} // namespace gui