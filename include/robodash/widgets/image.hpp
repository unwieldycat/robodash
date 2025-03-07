#pragma once
#include "liblvgl/lvgl.h"
#include "robodash/view.hpp"
#include "robodash/widgets/widget.hpp"
#include <string>

namespace rd {

/**
 * An image display
 *
 * Displays still images from an SD card or C array.
 *
 * @note All images must be converted using LVGL's online image converter
 * tool. (https://lvgl.io/tools/imageconverter)
 * @warning Images should be converted into an indexed color format for
 * performance. CF_INDEXED_4_BIT or CF_INDEXED_8_BIT is reccomended for
 * color images.
 *
 * @image html image.png
 */
class Image : public Widget {
  private:
	rd::View view;

  public:
	/**
	 * Create a new Image
	 *
	 * @param path File path to the binary-formatted image on SD card
	 * @param name Name to display on screen
	 */
	Image(std::string path, std::string name = "Image");

	/**
	 * Create a new Image
	 *
	 * @param image_dsc Pointer to LVGL image descriptor object
	 * @param name Name to display on screen
	 */
	Image(lv_img_dsc_t *image_dsc, std::string name = "Image");

	/**
	 * Create a new Image
	 *
	 * @param image_dsc Pointer to constant LVGL image descriptor object
	 * @param name Name to display on screen
	 */
	Image(const lv_img_dsc_t *image_dsc, std::string name = "Image");

	/**
	 * Set this view to the active view
	 */
	void focus();
};

} // namespace rd
