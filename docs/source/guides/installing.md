# Installing

:::{note}
If you only have the PROS VSCode extension installed, you must run
commands in the PROS "Integrated Terminal", not your system terminal.
:::

## Prerequisites

Before you install robodash you must have the following:

- An installation of the PROS CLI or VSCode extension

- A PROS 4 project

- [liblvgl 8](https://github.com/purduesigbots/liblvgl) added to your project

## Add the depot

Before adding robodash to your project, you'll need to register the depot with the PROS CLI. A depot is a remote file that informs the PROS CLI of templates that exist and where they can be installed from. You can run the command below to add the depot.

```
pros c add-depot robodash https://raw.githubusercontent.com/unwieldycat/robodash/depot/stable.json
```

### Or don't

Alternatively, you can download and register an individual version of robodash by downloading it from the releases tab on the GitHub page and registering it with `pros c fetch robodash@x.x.x.zip`. This is not recommended since you will have to manually repeat this step as robodash updates.

## Apply to project

Now let's add robodash to a project. Open the project you wish to use the robodash in and run the command below to apply it to your project.

```
pros c apply robodash
```

You can now add the following to your project's `main.h` file to use robodash.

```cpp
#include "robodash/api.h"
```
