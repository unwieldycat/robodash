#pragma once
#include "pros/llemu.hpp"
#include "unwieldy-ui/apix.hpp"
#include <cstdio>

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
	 * @brief Clear a specific line
	 *
	 * @param line
	 */
	void clear_line(int line);

	/**
	 * @brief Move the cursor to the beginning of a line
	 *
	 * @param line
	 */
	void set_line(int line);

	/**
	 * @brief Print to the console
	 *
	 * @param str String to print to console
	 */
	void print(std::string str);

	/**
	 * @brief Print to the console
	 *
	 * @tparam Params
	 * @param fmt Format string
	 * @param args Args to
	 */
	template <typename... Params>
	void printf(std::string fmt, Params... args) {}

	void refresh();
	void initialize();
};

} // namespace gui