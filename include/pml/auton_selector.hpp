#pragma once
#include "../api.h"
#include "../display/lvgl.h"
#include <functional>
#include <string>

namespace pml {
namespace auton_selector {

/**
 * \brief Side of the field the autonomous routine starts on
 */
enum class StartPosition { Any, Left, Right };

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
	Routine(
	    std::string name, std::function<void()> action,
	    StartPosition start_pos = pml::auton_selector::StartPosition::Any
	)
	    : name(name), action(action), start_pos(start_pos) {}

	std::string name;
	std::function<void()> action;
	StartPosition start_pos;
};

// TODO: make declaring autons less of a chore

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

} // namespace auton_selector
} // namespace pml