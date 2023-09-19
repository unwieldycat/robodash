#pragma once
#include "../gui.hpp"

// TODO: Units support
// TODO: Built-in field images

namespace gui {

class FieldView : public View {

  public:
	FieldView();

	/**
	 * @brief Set robot position
	 *
	 * @param x X coordinate
	 * @param y Y coordinate
	 * @param hdg Heading
	 */
	void set_pos(double x, double y, double hdg);

	/**
	 * @brief Set robot position
	 *
	 * @param x X coordinate
	 * @param y Y coordinate
	 */
	void set_pos(double x, double y);

	/**
	 * @brief Set the field bounds
	 *
	 * @param max Field maximum value (topmost, rightmost)
	 * @param min Field minimum value (bottommost, leftmost)
	 */
	void set_bounds(double max, double min);

	void refresh();
	void initialize();
};
} // namespace gui