@page installing Installation

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
