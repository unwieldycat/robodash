#include "main.h"
#include "liblvgl/misc/lv_area.h"
#include "liblvgl/widgets/lv_canvas.h"
#include "unwieldy-ui/gui.hpp"

void auton0() {}
void auton1() { std::cout << "Running auton "; }
void auton2() {}

pros::Motor flywheel_motor(3);
pros::Motor drivetrain_left(1);
pros::Motor drivetrain_right(2);

gui::DevicesView devices_view;
gui::SelectorView selector_view;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {

	gui::initialize();
	gui::bar::add_actions({{"Explode Robot", auton0}, {"Among us", auton1}});
	gui::register_view(&devices_view);
	gui::register_view(&selector_view);

	devices_view.add_motors(
	    {{"Flywheel", &flywheel_motor},
	     {"Drive Left", &drivetrain_left},
	     {"Drive Right", &drivetrain_right},
	     {"Drive Right", &drivetrain_right},
	     {"Drive Right", &drivetrain_right},
	     {"Drive Right", &drivetrain_right}}
	);

	selector_view.add_autons(
	    {{"Match load", auton0}, {"Score acorn", auton1}, {"Become sentient", auton2}}
	);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {}
