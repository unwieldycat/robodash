#include "main.h"
#include "robodash/api.h"

// ============================= Example autons ============================= //

void best_auton() { std::cout << "Running best auton" << std::endl; }
void simple_auton() { std::cout << "Running simple auton " << std::endl; }
void good_auton() { std::cout << "Running good auton" << std::endl; }

// ================================= Views ================================= //

rd::Selector selector; // Create robodash selector
rd::Console console;   // Create robodash console

// ========================= Competition Functions ========================= //

void initialize() {}

void disabled() {}

void competition_initialize() {
	// Register autons to selector
	selector.add_autons({
	    {"Best auton",   &best_auton  },
        {"Simple auton", &simple_auton},
        {"Good auton",   &good_auton  }
    });

	// Focus auton selector on screen
	selector.focus();
}

void autonomous() {
	// Run the selected autonomous function
	selector.do_auton();
}

void opcontrol() {
	// Print hello 0-99 to the robodash console
	for (int i = 0; i < 100; i++) {
		console.printf("Hello %d\n", i);
		pros::delay(200);
	}
}
