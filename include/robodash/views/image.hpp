/**
 * @file image.hpp
 * @brief Robodash Image
 * @ingroup image-view
 *
 * Built-in Image class to display images.
 */

#pragma once
#include "robodash/apix.hpp"

namespace rd {

/**
 * @brief Image class
 * @addtogroup image-view
 */
class Image {
	/// @addtogroup image-view
	/// @{

	/// @name Image Functions

  public:
	/**
	 * @brief Construct a new Image
	 *
	 * @param name Name to display on screen
	 * @param path File path to the binary-formatted image on SD card
	 *
	 * @note All images must be converted using LVGL's online image converter
	 * tool. (https://lvgl.io/tools/imageconverter)
	 * @warning Images should be converted into an indexed color format for
	 * performance. CF_INDEXED_4_BIT or CF_INDEXED_8_BIT is reccomended for
	 * color images.
	 */
	Image(std::string path, std::string name = "Image");

	/// @}
};

} // namespace rd