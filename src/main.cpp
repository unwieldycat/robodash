#include "main.h"
#include "robodash/api.h"

// ============================= Example autons ============================= //

void best_auton() { std::cout << "Running best auton" << std::endl; }
void simple_auton() { std::cout << "Running simple auton " << std::endl; }
void good_auton() { std::cout << "Running good auton" << std::endl; }

// ================================= Views ================================= //

// Create robodash selector
rd::Selector selector({
    {"Best auton", &best_auton},
    {"Simple auton", &simple_auton},
    {"Good auton", &good_auton},
});

// Create robodash console
rd::Console console;

// ========================= Competition Functions ========================= //

void initialize() {
	// Selector callback example, prints selected auton to the console
	selector.on_select([](std::optional<rd::Selector::routine_t> routine) {
		if (routine == std::nullopt) {
			std::cout << "No routine selected" << std::endl;
		} else {
			std::cout << "Selected Routine: " << routine.value().name << std::endl;
		}
	});
}

void disabled() {}

void competition_initialize() {
	// Focus auton selector on screen
	selector.focus();
}

void autonomous() {
	// Run the selected autonomous function
	selector.run_auton();
}

void opcontrol() {
	// Print hello 0-99 to the robodash console
	for (int i = 0; i < 100; i++) {
		console.printf("Hello %d\n", i);
		pros::delay(200);
	}
}
