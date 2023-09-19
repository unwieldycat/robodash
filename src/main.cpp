#include "main.h"
#include "robodash/gui.hpp"

// ================================ Devices ================================ //

pros::Motor flywheel_motor(3);
pros::Motor drivetrain_left(1);
pros::Motor drivetrain_right(2);
pros::Imu inertial(20);
pros::adi::Led led_strip({2, 1}, 16);

// ============================= Example autons ============================= //

void best_auton() { std::cout << "Running best auton" << std::endl; }
void simple_auton() { std::cout << "Running simple auton " << std::endl; }
void good_auton() { std::cout << "Running good auton" << std::endl; }

// ============================ Example actions ============================ //

void toggle_led() {
	static bool active;

	if (active) {
		led_strip.set_all(0xffffff);
		active = false;
	} else {
		led_strip.set_all(0xff00ff);
		active = true;
	}
}

void recalib_inertial() { inertial.reset(); }

// ================================= Views ================================= //

gui::DevicesView devices_view;
gui::SelectorView selector_view;
gui::ConsoleView test_console;
gui::FieldView field_view;

// ========================= Competition Functions ========================= //

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	// I turn off clang-format here because it doesn't handle vectors
	// as params very well
	/* clang-format off */

	// Initialize library and register views
	gui::initialize();
	gui::register_view(&devices_view);
	gui::register_view(&selector_view);
	gui::register_view(&test_console);

	// Configure ui
	gui::bar::add_actions({
		{"Recalibrate Inertial", recalib_inertial}, 
		{"Toggle LEDs", toggle_led}
	});

	devices_view.add_motors({
		{"Flywheel", &flywheel_motor},
		{"Drive Left", &drivetrain_left},
		{"Drive Right", &drivetrain_right},
	});

	selector_view.add_autons({
		{"Best auton", &best_auton},
		{"Simple auton", &simple_auton},
		{"Good auton", &good_auton}
	});

	/* clang-format on */
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
void competition_initialize() {
	// Focus auton selector
	gui::set_view(&selector_view);
}

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
void autonomous() {
	// Run selected autonomous function
	selector_view.do_auton();
}

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
void opcontrol() {
	for (int i = 0; i < 100; i++) {
		test_console.clear();
		test_console.printf("what up %d", i);
		pros::delay(500);
	}
}
