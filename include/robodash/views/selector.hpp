/**
 * @file selector.hpp
 * @brief Robodash Selector
 * @ingroup selector-view
 *
 * Built-in Selector class for function selecting, primarily for autonomous
 * routines.
 */

#pragma once
#include "robodash/apix.hpp"
#include <functional>
#include <string>
#include <vector>

namespace rd {

/**
 * @brief Selector class
 * @ingroup selector-view
 */
class Selector {
	/// @addtogroup selector-view
	/// @{
  private:
	rd::View view;

  public:
	/// @name Selector Typedefs
	typedef std::function<void()> routine_action_t;
	typedef std::pair<std::string, routine_action_t> routine_t;

	/// @name Selector Functions

	/**
	 * @brief Construct a new Selector
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