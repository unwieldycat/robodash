#pragma once

namespace rd {

/**
 * The base Robodash widget
 *
 * This is an abstract class that all Robodash widgets inherit from to ensure
 * consistency. As an end user, you do not need to worry about this class.
 */
class Widget {
  public:
	virtual void focus() = 0;
};

} // namespace rd
