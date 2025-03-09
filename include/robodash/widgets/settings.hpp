#pragma once
#include "robodash/view.hpp"
#include <memory>

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
	 * @return Toggle state
	 */
	std::shared_ptr<bool> toggle(std::string key, bool default_value);

	/**
	 * Declare a dropdown setting
	 *
	 * @param key Name of the dropdown
	 * @param values Values for the dropdown
	 * @param default_value Default value of the dropdown
	 * @return Dropdown state
	 */
	std::shared_ptr<std::string>
	dropdown(std::string key, std::vector<std::string> values, std::string default_value);

	/**
	 * Declare a slider setting
	 *
	 * @param key Name of the slider
	 * @param min Minimum value of the slider
	 * @param max Maximum value of the slider
	 * @param step Amount to increment the slider by
	 * @param default_value Default value of the slider
	 * @return Slider state
	 */
	std::shared_ptr<double>
	slider(std::string key, double min, double max, double step, double default_value);

	/**
	 * Declare an increment setting
	 *
	 * @param key Name of the increment
	 * @param min Minimum value of the increment
	 * @param max Maximum value of the increment
	 * @param default_value Default value of the increment
	 * @return Increment state
	 */
	std::shared_ptr<int> increment(std::string key, int min, int max, int default_value);

	void focus();

  private:
	rd::View view;

	lv_obj_t *settings_cont;

	void toggle_cb(lv_event_t *event);
	lv_obj_t *create_setting_cont(std::string key);
};

} // namespace rd
