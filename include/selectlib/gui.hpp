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

} // namespace gui