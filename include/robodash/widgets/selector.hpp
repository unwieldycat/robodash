#pragma once
#include "liblvgl/lvgl.h"
#include "robodash/view.hpp"
#include <functional>
#include <string>
#include <vector>

namespace rd {

/**
 * An autonomous function selector
 *
 * A function selector for easily managing autonomous routines. If available, automatically saves
 * the current configuration to an SD card and loads it on the next run. Also supports displaying
 * images from the SD card.
 *
 * @image html selector.png
 */
class Selector {
  public:
	typedef std::function<void()> routine_action_t;

	typedef struct routine {
		std::string name;
		routine_action_t action;
		std::string img = "";
	} routine_t;

	/**
	 * Create autonomous selector
	 *
	 * @param name Name of the autonomous selector
	 * @param autons Vector of autonomous rotuines
	 */
	Selector(std::string name, std::vector<routine_t> autons);

	/**
	 * Create autonomous selector
	 *
	 * @param autons Vector of autonomous rotuines
	 */
	Selector(std::vector<routine_t> autons);

	/**
	 * Run selected auton
	 */
	void run_auton();

	/**
	 * Set this view to the active view
	 */
	void focus();

  private:
	rd::View view;

	lv_obj_t *select_cont;
	lv_obj_t *selected_label;
	lv_obj_t *selected_img;

	std::string name;
	std::vector<rd::Selector::routine_t> routines;
	rd::Selector::routine_t *selected_routine;

	static void select_cb(lv_event_t *event);
};

} // namespace rd