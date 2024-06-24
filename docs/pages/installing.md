@page installing Installation

## Prerequisites

- An installation of the PROS CLI or VSCode extension.

- A PROS 4 project. Robodash does not support PROS 3 due to the bundled LVGL
  version.

- [liblvgl 8](https://github.com/purduesigbots/liblvgl). LVGL 5.3 is not
  supported.

## Installing the template

@note If you only have the PROS VSCode extension installed, you must run the
commands below in the Integrated Terminal.

1. Download the latest template from the
   [releases tab](https://github.com/unwieldycat/robodash/releases) on GitHub

2. Open the download location and fetch the template with
   `pros c fetch robodash@x.x.x.zip`. This registers the template with PROS
   Conductor, the PROS project management tools.

3. Open the project you wish to use the library in and install the template with
   `pros c apply robodash@x.x.x`.

4. `#include "robodash/api.hpp"` in your project's `main.h` file

<div class="section_buttons">
 
| Previous          |                Next |
|:------------------|--------------------:|
| [Home](@ref index) | [Usage](@ref usage) |
 
</div>
