/**
 * @file image.hpp
 * @brief Robodash Image
 * @ingroup image
 *
 * Built-in Image class to display images.
 */

#pragma once
#include "robodash/api.h"
#include <string>

namespace rd {

/**
 * @brief Image class
 * @addtogroup image-view
 *
 * @note All images must be converted using LVGL's online image converter
 * tool. (https://lvgl.io/tools/imageconverter)
 * @warning Images should be converted into an indexed color format for
 * performance. CF_INDEXED_4_BIT or CF_INDEXED_8_BIT is reccomended for
 * color images.
 *
 */
class Image {
	/// @addtogroup image-view
	/// @{

	/// @name Image Functions
  private:
	rd_view_t *view;

  public:
	/**
	 * @brief Create a new Image
	 *
	 * @param name File path to the binary-formatted image on SD card
	 * @param path Name to display on screen
	 */
	Image(std::string path, std::string name = "Image");

	/**
	 * @brief Create a new Image
	 *
	 * @param image_dsc LVGL image descriptor object
	 * @param name Name to display on screen
	 */
	Image(lv_img_dsc_t image_dsc, std::string name = "Image");

	/**
	 * @brief Set this view to the active view
	 */
	void focus();

	/// @}
};

} // namespace rd