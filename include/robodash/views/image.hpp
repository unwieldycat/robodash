#pragma once
#include "robodash/apix.hpp"

namespace gui {

class ImageView : public gui::View {
  private:
	std::string path;

  public:
	/**
	 * @brief Construct a new ImageView
	 *
	 * @param name Name to display on screen
	 * @param path Path to the binary-formatted image
	 *
	 * @note All images must be converted using LVGL's online image converter
	 * tool. (https://lvgl.io/tools/imageconverter)
	 * @warning Images should be converted into an indexed color format for
	 * performance. CF_INDEXED_4_BIT or CF_INDEXED_8_BIT is reccomended for
	 * color images.
	 */
	ImageView(std::string name, std::string path);
	~ImageView();

	void initialize();
	void refresh();
};

} // namespace gui