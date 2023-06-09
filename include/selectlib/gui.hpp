#pragma once
#include "api.hpp"

namespace gui {

/**
 * @brief Create a window
 *
 * @param name Name of the window
 * @return lv_obj_t
 */
lv_obj_t *create_window(std::string name);

/**
 * @brief Initialize library
 */
void initialize();

} // namespace gui