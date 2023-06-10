#pragma once
#include "api.h"
#include "liblvgl/lvgl.h"
#include <map>

namespace gui {

class View {
  public:
	const int id = pros::millis();
	std::string name;
	lv_obj_t *obj;

	View(std::string name);
	~View();

	virtual void refresh() = 0;
	virtual void initialize() = 0;
};

/**
 * @brief Register a view
 *
 * @param view
 */
void register_view(View *view);

/**
 * @brief Set the current view
 *
 * @param view
 */
void set_view(View *view);

/**
 * @brief Get the current view
 *
 * @return View*
 */
View *get_view();

/**
 * @brief Initialize library
 */
void initialize();

namespace bar {

typedef std::pair<std::string, std::function<void()>> action_t;

/**
 * @brief Add action to bar
 */
void add_action(std::string name, std::function<void()> action);

/**
 * @brief Add actions to bar
 */
void add_actions(std::vector<action_t> new_actions);

} // namespace bar
} // namespace gui