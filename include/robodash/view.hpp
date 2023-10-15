#pragma once
#include "api.h"
#include "lvgl/lvgl.h"

namespace gui {

/**
 * @brief Base view class
 */
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

} // namespace gui