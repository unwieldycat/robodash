#pragma once
#include "api.hpp"

namespace sl {

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

} // namespace screensaver

} // namespace sl
