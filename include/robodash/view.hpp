/**
 * @file view.hpp
 * @brief View class
 * @ingroup view
 */

#pragma once
#include "api.h"
#include <string>

namespace rd {

/**
 * @brief View class
 * @ingroup view
 */
class View {
  private:
	std::string name;
	lv_obj_t *obj;
	lv_obj_t *view_btn;

  public:
	/// @addtogroup view
	/// @{

	/// @name View Functions

	/**
	 * @brief View constructor
	 *
	 * @param name Name to display in the UI
	 */
	View(std::string name);
	~View();

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
	 * @brief Set this view to the active view
	 */
	void focus();

	// @}
};

} // namespace rd