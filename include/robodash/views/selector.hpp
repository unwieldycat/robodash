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
#include "liblvgl/lvgl.h"
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace gui {

class SelectorView : public View {
  public:
	typedef std::function<void()> routine_action_t;
	typedef std::pair<std::string, routine_action_t> routine_t;

	/**
	 * @brief Construct a new SelectorView
	 */
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