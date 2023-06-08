#pragma once
#include "api.hpp"

namespace gui {

namespace screensaver {

/**
 * @brief Set the screensaver image (240x480 LVGL format)
 *
 * @param path Path to file
 */
void set_image(std::string path);

/**
 * @brief Set the timeout before screensaver
 *
 * @param time Time in seconds
 */
void set_timeout(int time);

/**
 * @brief Activate screensaver
 */
void activate();

/**
 * @brief Exit screensaver
 */
void exit();

/**
 * @brief Refresh screensaver state (This function is automatically called)
 */
void _refresh();

} // namespace screensaver

} // namespace gui
