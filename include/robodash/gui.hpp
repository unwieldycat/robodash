/**
 * @file gui.hpp
 * @brief Core robodash functions
 *
 * Core functions to interface with robodash.
 */

#pragma once
#include "api.h"
#include "lvgl/lvgl.h"
#include "view.hpp"
#include <map>

namespace gui {

/**
 * @brief Register a view
 *
 * @param view
 */
void register_view(View *view);

/**
 * @brief Register multiple views
 *
 * @param views
 */
void register_views(std::vector<View *> views);

/**
 * @brief Set the current view
 *
 * @param view
 */
void set_view(View *view);

/**
 * @brief Get the current view
 *
 * @return View*
 */
View *get_view();

/**
 * @brief Initialize library
 */
void initialize();

} // namespace gui