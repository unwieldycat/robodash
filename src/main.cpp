#include "main.h"
#include "robodash/gui.hpp"

// ============================= Example autons ============================= //

void best_auton() { std::cout << "Running best auton" << std::endl; }
void simple_auton() { std::cout << "Running simple auton " << std::endl; }
void good_auton() { std::cout << "Running good auton" << std::endl; }

// ================================= Views ================================= //

gui::SelectorView selector;
gui::ConsoleView console;

// ========================= Competition Functions ========================= //

void initialize() {
	// Initialize library and register views
	gui::initialize();
	gui::register_views({&selector, &console});

	selector.add_autons({
	    {"Best auton",   &best_auton  },
        {"Simple auton", &simple_auton},
        {"Good auton",   &good_auton  }
    });
}

void disabled() {}

void competition_initialize() {
	// Focus auton selector
	gui::set_view(&selector);
}

void autonomous() {
	// Run selected autonomous function
	selector.do_auton();
}

void opcontrol() {
	for (int i = 0; i < 100; i++) {
		console.clear();
		console.printf("Hello %d", i);
		pros::delay(500);
	}
}
