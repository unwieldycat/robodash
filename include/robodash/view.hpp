#pragma once
#include "liblvgl/lvgl.h"
#include <string>
#include <vector>

namespace rd {

/**
 * Flags to alter the behavior of a view
 */
enum class ViewFlag {
	NoAnimation,
};

/**
 * The view class
 */
class View {
  public:
	/**
	 * Construct a view
	 *
	 * @param name Name to display in the sidebar
	 */
	View(std::string name);

	/**
	 * Destruct this view
	 */
	~View();

	/**
	 * Make this view the active view
	 */
	void focus();

	/**
	 * Add a flag to this view
	 *
	 * @param flag Flag to add
	 */
	void add_flag(ViewFlag flag);

	/**
	 * Check if this view has a flag
	 *
	 * @param flag Flag to check for
	 * @return bool
	 */
	bool has_flag(ViewFlag flag);

	/**
	 * Remove a flag from this view
	 *
	 * @param flag Flag to remove
	 */
	void remove_flag(ViewFlag flag);

	/**
	 * Get this view's name
	 *
	 * @return std::string
	 */
	std::string get_name();

	/**
	 * Get the LVGL object for this view
	 *
	 * @return lv_obj_t*
	 */
	lv_obj_t *get_lv_obj();

	/**
	 * Enables casting to an lv_obj_t* for ease of use
	 *
	 * @return lv_obj_t*
	 */
	operator lv_obj_t *();

  protected:
	/**
	 * Refresh this view's behavior based on the current flags.
	 *
	 * Called when flags are modified.
	 */
	void refresh();

  private:
	lv_obj_t *btn_obj;
	lv_obj_t *scr_obj;
	std::vector<ViewFlag> flags;
	std::string name;
};

} // namespace rd