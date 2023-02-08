#pragma once
#include <functional>
#include <string>

namespace uilib {
namespace auton_manager {

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
	Routine(std::string name, std::function<void()> action, StartPosition start_pos)
	    : name(name), action(action), start_pos(start_pos) {}

	std::string name;
	std::function<void()> action;
	StartPosition start_pos;
};

/**
 * \brief Initialize autonomous manager
 * \param autons Vector of Routine objects
 */
void initialize(std::vector<Routine> autons);

/**
 * \brief Run auton selection
 */
void run();

} // namespace auton_manager
} // namespace uilib