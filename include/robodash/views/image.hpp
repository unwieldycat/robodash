#pragma once
#include "robodash/apix.hpp"

namespace gui {

class ImageView : public gui::View {
  private:
	std::string path;

  public:
	ImageView(std::string name, std::string path);
	~ImageView();

	void initialize();
	void refresh();
};

} // namespace gui