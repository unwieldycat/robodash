#pragma once
#include "api.h"
#include "liblvgl/lvgl.h"
#include <map>

namespace gui {

class Window {
  public:
	const int id = pros::millis();
	std::string name;
	lv_obj_t *obj;

	Window(std::string name);
	~Window();

	virtual void refresh() = 0;
	virtual void initialize() = 0;
};

/**
 * @brief Set the current window
 *
 * @param window
 */
void set_window(Window *window);

/**
 * @brief Get the current window
 *
 * @return Window*
 */
Window *get_window();

/**
 * @brief Initialize library
 */
void initialize();

} // namespace gui