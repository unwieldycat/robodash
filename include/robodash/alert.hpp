#pragma once
#include "robodash/view.hpp"
#include <string>

namespace rd {

/**
 * Dispatch an alert
 *
 * @param message Message to display
 */
void alert(std::string message);

/**
 * Dispatch an alert that links back to a view
 *
 * @param message Message to display
 * @param view View to link back to
 */
void alert(std::string message, View &view);

} // namespace rd
