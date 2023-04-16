#pragma once
#include "api.hpp"

namespace sl {

namespace theme {

/**
 * @brief Set the hue of the UI
 *
 * @param hue [0..359]
 */
void set_hue(int hue);

} // namespace theme

/**
 * @brief Initialize library
 *
 */
void init();

} // namespace sl