#pragma once
#include "liblvgl/lvgl.h"
#include "robodash/view.hpp"
#include <sstream>
#include <string>

namespace rd {

/**
 * A GUI console for debugging. Emulates a standard console output.
 *
 * @image html console.png
 */
class Console {
  private:
	rd::View view;

	lv_obj_t *output;
	lv_obj_t *output_cont;
	std::ostringstream stream;

  public:
	/**
	 * Create a new Console
	 *
	 * @param name Name to display on screen
	 */
	Console(std::string name = "Console");

	/**
	 * Clear all console lines
	 */
	void clear();

	/**
	 * Print to the console
	 *
	 * @param str String to print to console
	 */
	void print(std::string str);

	/**
	 * Print to the console with a newline
	 *
	 * @param str String to print to console
	 */
	void println(std::string str);

	/**
	 * Print a formatted string to the console
	 *
	 * @tparam Params
	 * @param fmt Format string
	 * @param args Args for format string
	 */
	template <typename... Params> void printf(std::string fmt, Params... args) {
		char fstr[sizeof(fmt) + sizeof...(args)];
		sprintf(fstr, fmt.c_str(), args...);
		print(fstr);
	}

	/**
	 * Set this view to the active view
	 */
	void focus();
};

} // namespace rd