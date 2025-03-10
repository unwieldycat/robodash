#pragma once
#include "robodash/view.hpp"
#include <functional>

namespace rd {

/**
 * A settings menu widget to customize robot behavior on the fly
 *
 * A settings menu for easily managing robot settings. If available, automatically saves
 * the current configuration to an SD card and loads it on the next run.
 */
class Settings {
  public:
	/**
	 * Create a new settings widget
	 *
	 * @param name
	 */
	Settings(std::string name = "Settings");

	/**
	 * Declare a toggle setting
	 *
	 * @param key Name of the toggle
	 * @param default_value Default value of the toggle
	 * @param callback Callback function to run when the toggle changes
	 */
	void toggle(std::string key, bool default_value, std::function<void(bool)> callback);

	/**
	 * Declare a dropdown setting
	 *
	 * @param key Name of the dropdown
	 * @param values Values for the dropdown
	 * @param default_value Default value of the dropdown
	 * @param callback Callback function to run when the dropdown changes
	 */
	void dropdown(
	    std::string key, std::vector<std::string> values, std::string default_value,
	    std::function<void(std::string &)> callback
	);

	/**
	 * Declare a slider setting
	 *
	 * @param key Name of the slider
	 * @param min Minimum value of the slider
	 * @param max Maximum value of the slider
	 * @param step Amount to increment the slider by
	 * @param default_value Default value of the slider
	 * @param callback Callback function to run when the slider changes
	 */
	void slider(
	    std::string key, double min, double max, double step, double default_value,
	    std::function<void(double)> callback
	);

	/**
	 * Declare an increment setting
	 *
	 * @param key Name of the increment
	 * @param min Minimum value of the increment
	 * @param max Maximum value of the increment
	 * @param default_value Default value of the increment
	 * @param callback Callback function to run when the increment changes
	 */
	void increment(
	    std::string key, int min, int max, int default_value, std::function<void(int)> callback
	);

	void focus();

  private:
	rd::View view;

	lv_obj_t *settings_cont;

	void toggle_cb(lv_event_t *event);
	lv_obj_t *create_setting_cont(std::string key);
};

} // namespace rd
