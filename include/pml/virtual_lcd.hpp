#pragma once
#include "../display/lvgl.h"
#include <functional>
#include <map>
#include <string>

namespace pml {

namespace lcd {
/**
 * \brief Start virtual LCD on active screen
 */
void init();

/**
 * \brief Add an action button
 */
void add_action_btn(std::string label, std::function<void()> action);

/**
 * \brief Print to LCD
 *
 * \param line Line on console
 * \param text Text to display
 */
void print_ln(int line, std::string text);

/**
 * \brief Clear line on LCD
 *
 * \param line Line on console
 */
void clear_ln(int line);

} // namespace lcd
} // namespace pml