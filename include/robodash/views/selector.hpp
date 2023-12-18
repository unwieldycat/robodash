/**
 * @file selector.hpp
 * @brief Robodash Selector
 * @ingroup selector
 */

#pragma once
#include "robodash/api.h"
#include <functional>
#include <string>
#include <vector>

namespace rd {

/**
 * @defgroup selector Selector
 * @brief A function selector
 * @image html selector.png
 *
 * A function selector for easily managing autonomous routines. Supports saving a configuration to
 * an SD card, and automatically loading it on the next run.
 */

/**
 * @brief Selector class
 * @ingroup selector
 */
class Selector {
	/// @addtogroup selector
	/// @{
  private:
	rd_view_t *view;

  public:
	/// @name Selector Typedefs
	typedef std::function<void()> routine_action_t;
	typedef std::pair<std::string, routine_action_t> routine_t;

	/// @name Selector Functions

	/**
	 * @brief Create autonomous selector
	 * @param autons Vector of autonomous rotuines
	 * @bug Multiple selectors cannot be active at the same time.
	 */
	Selector(std::vector<routine_t> autons);

	/**
	 * @brief Run selected auton
	 */
	void run_auton();

	/**
	 * @brief Set this view to the active view
	 */
	void focus();

	/// @}
};

} // namespace rd