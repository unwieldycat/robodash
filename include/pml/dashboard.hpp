#pragma once
#include "../display/lvgl.h"
#include <functional>
#include <map>
#include <string>

namespace pml {
/**
 * \brief Initialize GUI
 */
void init();

/**
 * \brief Add an action button
 */
void add_action_btn(std::string label, std::function<void()> action);

/**
 * \brief Set text at selected line
 *
 * \param line Line on console
 * \param text Text to display
 */
void set_text(int line, std::string text);
} // namespace pml