#pragma once
#include "../gui.hpp"

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
	 * @brief Set the field scale. Center of the field is always 0, outermost
	 * value will be equal to the specified maximum value.
	 *
	 * @param max Field maximum value
	 */
	void set_scale(double max);

	void refresh();
	void initialize();
};
} // namespace gui