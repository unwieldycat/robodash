#include "main.h"
#include "robodash/gui.hpp"
#include "units.h"

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

void initialize() {
	// Initialize library and register views
	gui::initialize();
	gui::register_view(&devices_view);
	gui::register_view(&selector_view);
	gui::register_view(&test_console);

	// Configure ui
	gui::bar::add_actions({
	    {"Recalibrate Inertial", recalib_inertial},
        {"Toggle LEDs",          toggle_led      }
    });

	devices_view.add_motors({
	    {"Flywheel",    &flywheel_motor  },
	    {"Drive Left",  &drivetrain_left },
	    {"Drive Right", &drivetrain_right},
	});

	selector_view.add_autons({
	    {"Best auton",   &best_auton  },
        {"Simple auton", &simple_auton},
        {"Good auton",   &good_auton  }
    });
}

void disabled() {}

void competition_initialize() {
	// Focus auton selector
	gui::set_view(&selector_view);
}

void autonomous() {
	// Run selected autonomous function
	selector_view.do_auton();
}

void opcontrol() {
	for (int i = 0; i < 100; i++) {
		test_console.clear();
		test_console.printf("what up %d", i);
		pros::delay(500);
	}
}
