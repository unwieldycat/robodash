#pragma once
#include "../display/lvgl.h"
#include <functional>
#include <map>
#include <stdio.h>
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
 * \brief Print formatted string to LCD
 *
 * \param line Line on console
 * \param text Text to display
 * \param args Arguments for formatted string
 */
template <typename... T>
void print_ln(int line, std::string text, std::tuple<T...> args);

/**
 * \brief Clear line on LCD
 *
 * \param line Line on console
 */
void clear_ln(int line);

} // namespace lcd
} // namespace pml