#pragma once

#define ROBODASH
#define RD_VERSION_MAJOR 3
#define RD_VERSION_MINOR 0
#define RD_VERSION_PATCH 0

#include "liblvgl/lvgl.h"

// ========================== Check Compatibility ========================== //

#if (LV_VERSION_CHECK(8, 3, 0) == 0)
#error "LVGL version incompatible with robodash (Requires >= 8.3.X)"
#endif

#ifndef LV_FONT_MONTSERRAT_12
#error "LVGL install incompatible with robodash, missing font: Montserrat 12"
#endif

#ifndef LV_FONT_MONTSERRAT_14
#error "LVGL install incompatible with robodash, missing font: Montserrat 14"
#endif

#ifndef LV_FONT_MONTSERRAT_16
#error "LVGL install incompatible with robodash, missing font: Montserrat 16"
#endif

// ============================ Include Library ============================ //

#include "alert.hpp"
#include "util/kv_store.hpp"
#include "view.hpp"
#include "widgets/console.hpp"
#include "widgets/image.hpp"
#include "widgets/selector.hpp"