/**
 * @file core.h
 * @brief Robodash core functionality
 * @ingroup core
 */

#pragma once

#include "liblvgl/lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

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

/// @}

#ifdef __cplusplus
}
#endif