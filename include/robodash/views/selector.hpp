/**
 * @file selector.hpp
 * @brief Robodash SelectorView
 * @ingroup selector-view
 *
 * Built-in SelectorView class for function selecting, primarily for autonomous
 * routines.
 */

#pragma once
#include "robodash/apix.hpp"
#include <functional>
#include <string>
#include <vector>

namespace rd {

/**
 * @brief SelectorView class
 * @ingroup selector-view
 */
class SelectorView : public View {
	/// @addtogroup selector-view
	/// @{
  public:
	/// @name SelectorView Typedefs
	typedef std::function<void()> routine_action_t;
	typedef std::pair<std::string, routine_action_t> routine_t;

	/// @name SelectorView Functions

	/**
	 * @brief Construct a new SelectorView
	 */
	SelectorView();

	/**
	 * @brief Initialize autonomous manager
	 * @param autons Vector of Routine objects
	 */
	void add_autons(std::vector<routine_t> autons);

	/**
	 * @brief Run selected auton
	 */
	void do_auton();

	void refresh();
	void initialize();

	/// @}
};

} // namespace rd