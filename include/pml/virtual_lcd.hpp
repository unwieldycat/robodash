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
 * \brief Set text at selected line
 *
 * \param line Line on console
 * \param text Text to display
 */
void set_text(int line, std::string text);

} // namespace lcd
} // namespace pml