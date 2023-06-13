#pragma once
#include "lvgl/lvgl.h"

namespace gui {
namespace theme {

/**
 * @brief Set the hue of the UI
 *
 * @param hue [0..359]
 */
void set_hue(int hue);

// --------------------------- Internal Functions --------------------------- //

/**
 * @brief Initialize themes (Runs internally)
 */
void _initialize();

} // namespace theme
} // namespace gui