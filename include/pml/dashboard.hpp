#pragma once
#include "../display/lvgl.h"
#include <functional>
#include <map>
#include <string>

namespace pml {
/**
 * \brief Initialize GUI
 *
 */
void init();

/**
 * \brief Add an action button
 */
void add_action_btn(std::string label, std::function<void()> action);
} // namespace pml