/**
 * @file api.hpp
 * @brief API entrypoint for robodash
 *
 * Includes all necessary end-user functions.
 */

#pragma once

#define RD_VERSION_MAJOR 2
#define RD_VERSION_MINOR 0
#define RD_VERSION_PATCH 0
#define RD_VERSION_INFO "dev"

#include "liblvgl/lvgl.h"

#if (LV_VERSION_CHECK(8, 3, 0) == 0)
#error "LVGL version incompatible with robodash (Requires >= 8.3.X)"
#endif

#include "core.hpp"
#include "view.hpp"
#include "views/console.hpp"
#include "views/image.hpp"
#include "views/selector.hpp"
