#pragma once
#include "api.h"
#include "lvgl/lvgl.h"
#include <map>

namespace gui {

class View {
  public:
	int id;
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
 * @brief Register multiple views
 *
 * @param views
 */
void register_views(std::vector<View *> views);

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