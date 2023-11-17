@page getting-started Getting Started

# Installing Robodash

@note Robodash depends on liblvgl 8, which must be installed to your project. To
install liblvgl: `pros c apply liblvgl`. PROS 4 is required to install other
versions of lvgl.

1. Download the latest template from the
   [releases tab](https://github.com/unwieldycat/robodash/releases) on GitHub

2. Open the download location and fetch the template with
   `pros c fetch robodash@x.x.x.zip`. This registers the template with PROS
   Conductor, the PROS project management tools/

3. Open the project you wish to use the library in and install the template with
   `pros c apply robodash@x.x.x`.

4. `#include "robodash/api.hpp"` in your project's `main.h` file

# Using Robodash

@note Robodash currently only supports C++

Robodash comes with a few bundled UI tools, like an autonomous selector and a
console. These can be used by interfacing with their respective class.

```cpp
rd::Selector selector;
rd::Console console;

void initialize() {
   console.println("Adding autons...");

   selector.add_autons({
      {"Auton 0", &auton0},
      {"Auton 1", &simple_auton},
      {"Skills Run", &skills}
   });

   console.println("Registered auton routines!");
}

void autonomous() {
   console.println("Running auton...");
   selector.do_auton();
}
```

Robodash also provides functionality to create your own screens through the @ref
view class using LVGL.

```cpp

void opcontrol() {
   rd_view_t *view = rd_view_create("custom view");
   lv_label_t *label = lv_label_create(rd_view_obj(view));
   lv_label_set_text(label, "example");
   lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}
```

You can learn more about the bundled modules and views at @ref api
