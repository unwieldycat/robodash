/**
 * @file core.h
 * @brief Robodash core header
 * @ingroup core
 */

#pragma once

#include "liblvgl/lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup core Core
 * @brief The view management system.
 *
 * Knowledge of LVGL is required if you wish to create a view.
 */

/// @addtogroup core
/// @{

/**
 * @brief Robodash view structure
 */
typedef struct rd_view {
	const char *name;
	lv_obj_t *obj;
	lv_obj_t *_btn;
} rd_view_t;

/**
 * @brief Create a view
 *
 * @param name Name of the view
 * @return rd_view_t
 */
rd_view_t *rd_view_create(const char *name);

/**
 * @brief Set a view to the currently active view
 *
 * @param view View to focus
 */
void rd_view_focus(rd_view_t *view);

/**
 * @brief Delete a view
 * @warning Deleting a view will free the memory the view occupied, but will not set any variables
 * pointing to said view `NULL`.
 *
 * @param view View to delete
 */
void rd_view_del(rd_view_t *view);

/**
 * @brief Get the view's lvgl object
 *
 * @param view View
 */
lv_obj_t *rd_view_obj(rd_view_t *view);

/**
 * @brief Push an alert to the screen
 *
 * Pushes an alert to the screen, regardless of which view is active.
 *
 * @param view View to link back to
 * @param msg Message to display
 */
void rd_view_alert(rd_view_t *view, const char *msg);

/// @}

#ifdef __cplusplus
}
#endif