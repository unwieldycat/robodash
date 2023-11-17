/**
 * @file api.h
 * @brief API entrypoint for robodash
 *
 * Includes all necessary end-user functions.
 */

#pragma once

#define RD_VERSION_MAJOR 2
#define RD_VERSION_MINOR 0
#define RD_VERSION_PATCH 0

#include "liblvgl/lvgl.h"

#if (LV_VERSION_CHECK(8, 3, 0) == 0)
#error "LVGL version incompatible with robodash (Requires >= 8.3.X)"
#endif

#include "core.h"

#ifdef __cplusplus
#include "views/console.hpp"
#include "views/image.hpp"
#include "views/selector.hpp"
#endif