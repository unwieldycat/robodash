# Changelog

Changes to this project will be logged in this file. This project uses
[Semantic Versioning](https://semver.org/spec/v2.0.0.html). Format is loosely
based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/).

## 2.3.0

Robodash 2.3.0 improves the selector UI.

### Added

- An indication for what auton in the selector list is currently selected
- `color_hue` parameter to autons, which places a color chip next to the auton's name in the list.
- Page up / page down buttons to the selector if it's scrollable, making scrolling easier when there's many autons.
- Up / down buttons to the selector, providing an alternate way to select autons in the list.
- `rd::Selector::next_auton` and `rd::Selector::prev_auton` functions for user-defined methods to control the selector, enabling hardware buttons or dials.

## 2.2.0

Robodash 2.2.0 provides selector enhancements.

### Added

- Autonomous selector callbacks (`rd::Selector::on_select`)
- Autonomous selector getter (`rd::Selector::get_auton`)

### Fixed

- `rd::Image` constructor for C array images required a `lv_img_dsc_t`, not a `const lv_img_dsc_t` (which LVGL outputs in its conversion). Added support for both.

## 2.1.2

Robodash 2.1.2 provides a fix for the image widget.

> [!WARNING]
>
> This update has a breaking change. When constructing an `rd::Image` with a C
> array, you must pass a pointer to your `lv_img_dsc_t` instead of a reference.
> This is to prevent a dangling pointer.

### Fixed

- A bug where constructing an `rd::Image` with a C array would not display the
  image.

## 2.1.1

Robodash 2.1.1 is a recompilation of 2.1.0 that upgrades to PROS version 4.1.0

## 2.1.0

Robodash 2.1.0 resolves issues with the autonomous selector.

### Added

- The ability to associate images with autonomous routines
- Support for multiple active selectors
- Automatic SD saving, no need to press a button

Minor breaking changes with selector: `rd::Selector::routine_t` is now a
`struct` instead of an `std::pair`. This shouldn't break any existing code.

### Fixed

- A data abort error when a routine name was too long
