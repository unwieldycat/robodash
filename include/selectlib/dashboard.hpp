#pragma once
#include "api.hpp"

namespace gui {

namespace dashboard {

/**
 * @brief Add an action button to the dashboard
 *
 * @param name Name of action
 * @param fn Action function
 */
void add_action(std::string name, std::function<void()> fn);

/**
 * @brief Add motors to dashboard for monitoring
 *
 * @param mtrs Motors to monitor
 */
void add_motors(std::vector<pros::Motor *> mtrs);

} // namespace dashboard

} // namespace gui