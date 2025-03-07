#pragma once

#include <stdbool.h>

#ifdef __cplusplus
namespace rd {
namespace detail {
namespace platform {
extern "C" {
#endif

/**
 * Check if the SD card is installed
 *
 * @return true - SD card is present
 * @return false - SD card is not present
 */
bool sd_installed();

#ifdef __cplusplus
}
} // namespace platform
} // namespace detail
} // namespace rd
#endif
