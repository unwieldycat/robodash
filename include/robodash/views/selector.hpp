/**
 * @file selector.hpp
 * @brief Robodash Selector
 * @ingroup selector
 *
 * Built-in Selector class for function selecting, primarily for autonomous
 * routines.
 */

#pragma once
#include "robodash/api.h"
#include <functional>
#include <string>
#include <vector>

namespace rd {

/**
 * @brief Selector class
 * @ingroup selector
 */
class Selector {
	/// @addtogroup selector
	/// @{
  private:
	rd::View view;

  public:
	/// @name Selector Typedefs
	typedef std::function<void()> routine_action_t;
	typedef std::pair<std::string, routine_action_t> routine_t;

	/// @name Selector Functions

	/**
	 * @brief Create a new Selector
	 */
	Selector();

	/**
	 * @brief Initialize autonomous manager
	 * @param autons Vector of Routines
	 */
	void add_autons(std::vector<routine_t> autons);

	/**
	 * @brief Run selected auton
	 */
	void do_auton();

	/**
	 * @brief Set this view to the active view
	 */
	void focus();

	/// @}
};

} // namespace rd