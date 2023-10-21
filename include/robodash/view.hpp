/**
 * @file view.hpp
 * @brief Base view class
 *
 * Abstract view class for other views to derrive. Provides basic functions and
 * structure.
 */

#pragma once
#include "api.h"
#include "liblvgl/lvgl.h"
#include <string>

namespace gui {

/**
 * @brief Base view class
 */
class View {
  private:
	int id;
	std::string name;
	lv_obj_t *obj;

  public:
	/**
	 * @brief View constructor
	 *
	 * @param name Name to display in the UI
	 */
	View(std::string name);
	~View();

	/**
	 * @brief Get the object's unique ID. Used internally.
	 *
	 * @return int ID of object
	 */
	int get_id();

	/**
	 * @brief Get the view's lvgl object
	 *
	 * @return lv_obj_t*
	 */
	lv_obj_t *get_obj();

	/**
	 * @brief Get the view name
	 *
	 * @return std::string
	 */
	std::string get_name();

	/**
	 * @brief UI refresh function. Runs whenever the view is focused.
	 */
	virtual void refresh() = 0;

	/**
	 * @brief UI initialize function. Runs when the view is registered.
	 */
	virtual void initialize() = 0;
};

} // namespace gui