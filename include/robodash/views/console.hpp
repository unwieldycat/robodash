/**
 * @file console.hpp
 * @brief Robodash Console
 * @ingroup console-view
 *
 * Built-in Console class for debugging. Emulates a standard console output.
 */

#pragma once
#include "robodash/apix.hpp"

namespace rd {

/**
 * @brief Console class
 * @addtogroup console-view
 */
class Console {
	/// @addtogroup console-view
	/// @{

	/// @name Console Functions

  public:
	/**
	 * @brief Construct a new Console
	 *
	 * @param name Name to display on screen
	 */
	Console(std::string name = "Console");

	/**
	 * @brief Clear all console lines
	 */
	void clear();

	/**
	 * @brief Print to the console
	 *
	 * @param str String to print to console
	 */
	void print(std::string str);

	/**
	 * @brief Print to the console with a newline
	 *
	 * @param str String to print to console
	 */
	void println(std::string str);

	/**
	 * @brief Print a formatted string to the console
	 *
	 * @tparam Params
	 * @param fmt Format string
	 * @param args Args for format string
	 */
	template <typename... Params>
	void printf(std::string fmt, Params... args) {
		char fstr[sizeof(fmt) + sizeof...(args)];
		sprintf(fstr, fmt.c_str(), args...);
		print(fstr);
	}

	// @}
};

} // namespace rd