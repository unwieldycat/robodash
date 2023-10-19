/**
 * @file console.hpp
 * @brief Robodash ConsoleView
 *
 * Built-in ConsoleView class for debugging. Emulates a standard console output.
 */

#pragma once
#include "robodash/apix.hpp"

namespace gui {

class ConsoleView : public View {
  public:
	/**
	 * @brief Create a console view
	 *
	 * @param name Name of the console
	 */
	ConsoleView(std::string name = "Console");

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
	 * @brief Print to the console
	 *
	 * @tparam Params
	 * @param fmt Format string
	 * @param args Args to
	 */
	template <typename... Params>
	void printf(std::string fmt, Params... args) {
		char fstr[sizeof(fmt) + sizeof...(args)];
		sprintf(fstr, fmt.c_str(), args...);
		print(fstr);
	}

	void refresh();
	void initialize();
};

} // namespace gui