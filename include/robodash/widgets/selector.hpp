#pragma once
#include "liblvgl/lvgl.h"
#include "robodash/view.hpp"
#include <functional>
#include <optional>
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
		int color_hue = -1;
	} routine_t;

	typedef std::function<void(std::optional<routine_t>)> select_action_t;

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
	 * Get the selected auton
	 *
	 * @return Selected auton
	 */
	std::optional<routine_t> get_auton();

	/**
	 * Add a selection callback
	 *
	 * @param callback The callback function
	 */
	void on_select(select_action_t callback);

	/**
	 * Select the next auton in the list
	 *
	 * Selects the next auton in the list for use with physical buttons such as limit switches.
	 *
	 * @param wrap_around Whether to wrap around to the beginning once the last auton is reached
	 */
	void next_auton(bool wrap_around = true);

	/**
	 * Select the previous auton in the list
	 *
	 * Selects the previous auton in the list for use with physical buttons such as limit switches.
	 *
	 * @param wrap_around Whether to wrap around to the end once the first auton is reached
	 */
	void prev_auton(bool wrap_around = true);

	/**
	 * Set this view to the active view
	 */
	void focus();

  private:
	rd::View view;

	lv_obj_t *routine_list;
	lv_obj_t *selected_cont;
	lv_obj_t *selected_label;
	lv_obj_t *selected_img;

	std::string name;
	std::vector<rd::Selector::routine_t> routines;
	std::vector<rd::Selector::select_action_t> select_callbacks;
	rd::Selector::routine_t *selected_routine;

	void run_callbacks();

	static void select_cb(lv_event_t *event);
	static void up_cb(lv_event_t *event);
	static void down_cb(lv_event_t *event);
	static void pg_up_cb(lv_event_t *event);
	static void pg_down_cb(lv_event_t *event);
};

} // namespace rd