/**
 * @file core.hpp
 * @brief Core robodash functions
 * @ingroup core
 *
 * Core functions to interface with robodash.
 */

#pragma once
#include "api.hpp"
#include "view.hpp"

namespace rd {

/// @addtogroup core
/// @{

/// @name Core functions
/// Core view management functions

/**
 * @brief Register a view
 *
 * @param view View to add
 */
void register_view(View *view);

/**
 * @brief Register multiple views
 *
 * @param views Vector of views to add
 */
void register_views(std::vector<View *> views);

/**
 * @brief Set the current view
 *
 * @param view View to set as current view
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

/// @}

} // namespace rd
