@page usage Usage

Robodash has two parts: the core, and the toolkit.

- The core library is the system that enables interoperability between templates
  by providing a view-management system for LVGL. This API requires knowledge of
  LVGL. Compatible with C and C++.

- The toolkit is the set of provided class-based UI tools intended for end users
  of the library. These require no knowledge of LVGL and require minimal
  configuration. Only compatible with C++.

## Toolkit

All of the tools provided by Robodash are class-based, and are designed to be as
simple as possible to use. The following example utilizes the autonomous
selector and the on-screen console.

```cpp
rd::Selector selector({
   {"Auton 0", &auton0},
   {"Auton 1", &simple_auton},
   {"Skills Run", &skills}
});

rd::Console console;

void initialize() {
   console.println("Initializing robot...");
   // Robot stuff would happen...
}

void autonomous() {
   console.println("Running auton...");
   selector.run_auton();
}
```

Documention for each class is linked on the topics page.

## Core

The core library is the view management system for LVGL, and is designed to be
as familliar as possible to someone already familliar with LVGL. Each view,
represented by a memory pointer to an `rd_view_t`, exposes an LVGL object the
size of the view area, which can be thought of as a screen. It is very important
that any LVGL objects that are created in your template or user program are a
child of this exposed object, **NOT `lv_scr_act()`**, since robodash manages
which view is active by hiding and unhiding the object cooresponding to each
view.

The name passed to each view will be the name that is displayed on screen in the
view switcher and any alert dialogues spawned by the view.

The following is an example of a simple view that displays a text label.

```cpp
void opcontrol() {
   rd_view_t *view = rd_view_create("custom view");
   lv_label_t *label = lv_label_create(rd_view_obj(view));
   lv_label_set_text(label, "example");
   lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}
```

You can learn more about the core library at the @ref core page.

<div class="section_buttons">
 
| Previous                      |                      Next |
|:------------------------------|--------------------------:|
| [Installing](@ref installing) | [User Interface](@ref ui) |
 
</div>
