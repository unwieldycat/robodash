#pragma once
#include "api.hpp"

namespace gui {
namespace selector {

/**
 * @brief Autonomous routine meta type
 */
typedef std::pair<std::string, std::function<void()>> routine_t;

/**
 * @brief Initialize autonomous manager
 * @param autons Vector of Routine objects
 */
void add_autons(std::vector<routine_t> autons);

/**
 * @brief Run auton selection
 */
void do_selection();

/**
 * @brief End selection if still running. Workaround since UI doesn't clear due to task being
 * forcibly ended before the code can do it automatically
 */
void exit_selection();

/**
 * @brief Run selected auton
 */
void do_auton();

} // namespace selector
} // namespace gui