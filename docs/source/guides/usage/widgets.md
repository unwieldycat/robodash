# Widgets

Robodash provides a suite of simple, commonly used GUI widgets.

## Selector

The [Selector Widget](../api/views/selector.md) is a function selector designed for managing autonomous runs.

To use the selector we can construct it in the global scope of our `main.cpp` file.

```cpp
rd::Selector selector({
    {"Best auton", best_auton},
    {"Simple auton", simple_auton},
    {"Good auton", good_auton},
});
```

The selector's constructor takes a vector of pairs that hold a string and a
function. The string is the name that appears on the display as the function's
name, and the function is what is called when it is selected.

Our example assumes we have three functions, `best_auton`, `simple_auton`, and
`good_auton`. These functions should take no arguments and return `void`.

While the selector appears on the screen, we still need to make our selected
routine run when our bot is in autonomous mode.

In your `main.cpp` file, call `selector.run_auton()` in your `autonomous` function.

```cpp
void autonomous() {
	selector.run_auton();
}
```

Now, when our robot is in autonomous mode, our user-selected routine will run.
In addition, if an SD card is in the brain, the selected routine will be
preserved next time the program is run.

## Console

The [Console Widget](../api/views/console.md) provides a text display for
quickly and easily displaying information for debugging. To create a console, we
can construct it in our `main.cpp` file's global scope.

```cpp
rd::Console console;
```

We can now log information to the console with `console.print`,
`console.println`, and `console.printf`, and we can clear the console with
`console.clear`.

```cpp
console.println("Hello");
console.printf("The robot's heading is %f\n", some_imu.get_heading());
```

## Image

<!-- TODO -->
