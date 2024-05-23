@mainpage

### Welcome to the Robodash docs!

Robodash is a GUI toolkit for PROS 4 that provides a suite of easy to use GUI
utilities and an API for interoperable LVGL-based user interfaces.

To get started, visit the @ref installing page.

### Why?

Robodash was created to solve a problem with the V5 LCD -- it is incredibly
underutilized. There are two parts to this issue: ease of use and sharing.

For one, most people opt to use the legacy LCD emulator since it is the easiest
and fastest way to utilize the V5 screen. While an alright solution, the V5 LCD
isnt completely taken advantage of in this scenario and additional code is
required to display other information like a graph or images.

Secondly, the V5 screen cannot be easily shared by multiple pieces of code. If a
template wants to provide a GUI widget, this may interfere with a user's
autonomous selector or another template's GUI with no way to switch between
them.

Robodash aims to solve these two issues by providing a set of easy to use GUI
utilities for users, and an API for template developers to create LVGL GUIS that
work in harmony with each other.

<div class="section_buttons">
 
| Previous |                          Next |
|:---------|------------------------------:|
|          | [Installing](@ref installing) |
 
</div>
