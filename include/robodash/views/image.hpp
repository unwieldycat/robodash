/**
 * @file image.hpp
 * @brief Robodash ImageView
 * @ingroup image-view
 *
 * Built-in ImageView class to display images.
 */

#pragma once
#include "robodash/apix.hpp"

namespace rd {

/**
 * @brief ImageView class
 * @addtogroup image-view
 */
class ImageView : public rd::View {
  private:
	std::string path;

	/// @addtogroup image-view
	/// @{

	/// @name ImageView Functions

  public:
	/**
	 * @brief Construct a new ImageView
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
	ImageView(std::string name, std::string path);

	void initialize();
	void refresh();
};

} // namespace rd