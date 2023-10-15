# robodash

A flexible, unified robot dashboard for the VEX V5. Built with LVGL.

### Features

- **Effortless** - Say goodbye to LLEMU, give your robot a powerful UI with
  minimal code required.

- **View Switcher** - Have multiple active screens and easily switch between
  them. No more cramming everything on one screen.

- **Extendable** - Create your own views, or use ones from a third-party
  template.

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
