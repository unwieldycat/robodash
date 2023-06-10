#pragma once
#include "api.hpp"

namespace gui {

typedef struct Window {
	Window(std::string name);
	~Window();
	int id;
	std::string name;
	lv_obj_t *obj;
} window_t;

/**
 * @brief Register a window
 *
 * @param window
 */
void register_window(Window *window);

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
 * @brief Close a window
 *
 * @param window
 */
void close_window(Window *window);

/**
 * @brief Initialize library
 */
void initialize();

} // namespace gui