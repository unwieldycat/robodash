#pragma once
#include "../api.h"
#include "../display/lvgl.h"
#include <cstdio>
#include <functional>
#include <stdio.h>
#include <string>

namespace selector {

/**
 * \brief Autonomous routine object
 */
struct Routine {
	/**
	 * \brief Construct a new Routine object
	 *
	 * \param name Name of routine
	 * \param action Routine action
	 */
	Routine(std::string name, std::function<void()> action) : name(name), action(action) {}

	std::string name;
	std::function<void()> action;
};

/**
 * \brief Initialize autonomous manager
 * \param autons Vector of Routine objects
 */
void add_autons(std::vector<Routine> autons);

/**
 * \brief Run auton selection
 */
void do_selection();

/**
 * \brief End selection if still running. Workaround since UI doesn't clear due to task being
 * forcibly ended before the code can do it automatically
 */
void exit_selection();

/**
 * \brief Run selected auton
 */
void do_auton();

namespace theme {

/**
 * \brief Set the hue of the UI
 *
 * \param hue [0..359]
 */
void set_hue(int hue);

} // namespace theme

} // namespace selector