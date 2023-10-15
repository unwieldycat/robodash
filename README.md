# robodash

A flexible robot dashboard for the VEX V5. Built with LVGL.

### Features

- **Auton Selector** - An intuitive, game agnostic selector with SD card saving

- **Quick Actions** - Run user-defined functions from the toolbar

- **Customizable** - Customizable theme and splash screen

- **Extendable** - Create your own views

## Installation

> [!IMPORTANT]\
> To prevent conflicts with the bundled liblvgl version, liblvgl should be
> removed from your project prior to installing robodash

1. Download the latest template from the releases tab
2. Open download location and register the template by running
   `pros c fetch robodash@x.x.x.zip`
3. Open the project you wish to use the library in and run
   `pros c apply robodash@x.x.x`
4. `#include "robodash/api.hpp"` in your project's `main.h` file

See `main.cpp` for a usage example.
