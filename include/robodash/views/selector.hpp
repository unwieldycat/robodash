/**
 * @file selector.hpp
 * @brief Robodash Selector
 * @ingroup selector
 */

#pragma once
#include "robodash/api.h"
#include <functional>
#include <optional>
#include <string>
#include <vector>

namespace rd {

/**
 * @defgroup selector Selector
 * @brief A function selector
 * @image html selector.png
 *
 * A function selector for easily managing autonomous routines. If available, automatically saves
 * the current configuration to an SD card and loads it on the next run. Also supports displaying
 * images from the SD card.
 */

/**
 * @brief Selector class
 * @ingroup selector
 */
class Selector {
	/// @addtogroup selector
	/// @{
  public:
	/// @name Selector Typedefs
	typedef std::function<void()> routine_action_t;

	typedef struct routine {
		std::string name;
		routine_action_t action;
		std::string img = "";
		int color_hue = -1;
	} routine_t;

	typedef std::function<void(std::optional<routine_t>)> select_action_t;

	/// @name Selector Functions

	/**
	 * @brief Create autonomous selector
	 * @param name Name of the autonomous selector
	 * @param autons Vector of autonomous rotuines
	 */
	Selector(std::string name, std::vector<routine_t> autons);

	/**
	 * @brief Create autonomous selector
	 * @param autons Vector of autonomous rotuines
	 */
	Selector(std::vector<routine_t> autons);

	/**
	 * @brief Run selected auton
	 */
	void run_auton();

	/**
	 * Get the selected auton
	 * @return Selected auton
	 */
	std::optional<routine_t> get_auton();

	/**
	 * @brief Add a selection callback
	 * @param callback The callback function
	 */
	void on_select(select_action_t callback);

	/**
	 * @brief Select the next auton in the list
	 * @param wrap_around Whether to wrap around to the beginning once the last auton is reached
	 *
	 * Selects the next auton in the list for use with physical buttons such as limit switches.
	 */
	void next_auton(bool wrap_around = true);

	/**
	 * @brief Select the previous auton in the list
	 * @param wrap_around Whether to wrap around to the end once the first auton is reached
	 *
	 * Selects the previous auton in the list for use with physical buttons such as limit switches.
	 */
	void prev_auton(bool wrap_around = true);

	/**
	 * @brief Set this view to the active view
	 */
	void focus();

	/// @}

  private:
	rd_view_t *view;

	lv_obj_t *routine_list;
	lv_obj_t *selected_cont;
	lv_obj_t *selected_label;
	lv_obj_t *selected_img;

	std::string name;
	std::vector<rd::Selector::routine_t> routines;
	std::vector<rd::Selector::select_action_t> select_callbacks;
	rd::Selector::routine_t *selected_routine;

	void sd_save();
	void sd_load();

	void run_callbacks();

	static void select_cb(lv_event_t *event);
	static void up_cb(lv_event_t *event);
	static void down_cb(lv_event_t *event);
	static void pg_up_cb(lv_event_t *event);
	static void pg_down_cb(lv_event_t *event);
};

} // namespace rd