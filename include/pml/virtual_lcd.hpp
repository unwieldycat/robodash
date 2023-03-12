#pragma once
#include "../display/lvgl.h"
#include <functional>
#include <stdio.h>
#include <string>

namespace pml {

namespace lcd {
/**
 * \brief Start virtual LCD on active screen
 */
void init();

/**
 * \brief Checks if the virtual LCD is active
 *
 * \return true LCD is initialized
 * \return false LCD is not initialized
 */
bool is_init();

/**
 * \brief Exit the virtual LCD
 */
void exit();

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
template <typename... Params>
void print_ln(int line, std::string text, Params... args) {
	char fstr[sizeof(text) + sizeof...(args)];
	sprintf(fstr, text.c_str(), args...);
	pml::lcd::print_ln(line, fstr);
}

/**
 * \brief Clear line on LCD
 *
 * \param line Line on console
 */
void clear_ln(int line);

} // namespace lcd
} // namespace pml