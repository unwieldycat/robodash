#pragma once
#include "robodash/view.hpp"
#include <functional>
#include <memory>
#include <variant>

namespace rd {

/**
 * Representation of a setting value
 *
 * @tparam T
 */
template <typename T> class SettingValue {
	friend class Settings;

  public:
	// Delete the default constructor
	SettingValue() = delete;

	// Delete the copy constructor (should only be passed by reference)
	SettingValue(const SettingValue &) = delete;

	/**
	 * Get the value of this setting
	 *
	 * @return T
	 */
	T get() { return *value; }

	/**
	 * Get the pointer for this setting's value
	 *
	 * @return std::shared_ptr<T>
	 */
	std::shared_ptr<T> ptr() { return value; }

	/**
	 * Register a callback to run when the setting changes
	 *
	 * @param callback
	 */
	void on_change(std::function<void(T)> callback) { callbacks.push_back(callback); }

	/**
	 * Get the value of this setting through casting
	 *
	 * @return T
	 */
	T operator T() { return *value; }

  private:
	SettingValue(std::shared_ptr<T> value) : value(value) {}

	std::shared_ptr<T> value;
	std::vector<std::function<void(T)>> callbacks;
};

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
	 * Create a button that runs a function when pressed
	 *
	 * @param key Name of the button
	 * @param callback Callback function to run when the button is pressed
	 */
	void button(std::string key, std::function<void()> callback);

	/**
	 * Declare a toggle setting
	 *
	 * @param key Name of the toggle
	 * @param default_value Default value of the toggle
	 * @param callback Callback function to run when the toggle changes
	 */
	SettingValue<bool> &toggle(std::string key, bool default_value);

	/**
	 * Declare a dropdown setting
	 *
	 * @param key Name of the dropdown
	 * @param values Values for the dropdown
	 * @param default_value Default value of the dropdown
	 * @param callback Callback function to run when the dropdown changes
	 */
	SettingValue<std::string> &
	dropdown(std::string key, std::vector<std::string> values, std::string default_value);

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
	SettingValue<double> &
	slider(std::string key, double min, double max, double step, double default_value);

	/**
	 * Declare an increment setting
	 *
	 * @param key Name of the increment
	 * @param min Minimum value of the increment
	 * @param max Maximum value of the increment
	 * @param default_value Default value of the increment
	 * @param callback Callback function to run when the increment changes
	 */
	SettingValue<int> &increment(std::string key, int min, int max, int default_value);

	void focus();

  private:
	rd::View view;

	lv_obj_t *settings_cont;

	static void toggle_cb(lv_event_t *event);

	lv_obj_t *create_setting_cont(std::string key);
};

} // namespace rd
