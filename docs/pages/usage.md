@page usage Usage

Robodash has two parts: the core, and the toolkit.

- The core library is the view management system and provides functions to
  create your own views. Creating your own views requires knowledge of LVGL.
  Compatible with C and C++.

- The toolkit is the set of provided class-based UI tools, like the autonomous
  selector or console. These require no knowledge of LVGL and require minimal
  configuration. Only compatible with C++.

## Toolkit

All of the tools provided by Robodash are class-based, and are designed to be as
simple as possible to use. The following snippet utilizes the autonomous
selector and the screen console.

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

You can learn more about each of the built-in tools at the topics page.

## Core

The core library is implemented in C, and is designed to be as familliar as
possible to someone already familliar with LVGL. The following is an example of
how to create a view.

```cpp
void opcontrol() {
   rd_view_t *view = rd_view_create("custom view");
   lv_label_t *label = lv_label_create(rd_view_obj(view));
   lv_label_set_text(label, "example");
   lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}
```

You can learn more about the core library at the @ref core page.
