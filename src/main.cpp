#include "main.h"

// ============================= Example autons ============================= //

void best_auton() { std::cout << "Running best auton" << std::endl; }
void simple_auton() { std::cout << "Running simple auton " << std::endl; }
void good_auton() { std::cout << "Running good auton" << std::endl; }

// ================================= Views ================================= //

rd::Selector selector;
rd::Console console;

// ========================= Competition Functions ========================= //

void initialize() {
	selector.add_autons({
	    {"Best auton",   &best_auton  },
        {"Simple auton", &simple_auton},
        {"Good auton",   &good_auton  }
    });
}

void disabled() {}

void competition_initialize() {
	// Focus auton selector
	selector.focus();
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
