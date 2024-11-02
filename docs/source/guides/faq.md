# Frequently Asked Questions

**Why is Robodash frozen? The rest of the brain is still functional and the
program is running.**

You likely have an indefinite loop that doesn't yield to PROS' task scheduler
with `pros::delay`, this hogs CPU time and never lets LVGL's tasks run. You
should add a delay in any long-living loop, like your drive code.

**Is Robodash V5RC Legal?**

As per the
[RECF Student-Centered Policy](https://kb.roboticseducation.org/hc/en-us/articles/5449868745367-Student-Centered-Policy)
under "Programming / Coding":

> Teams that utilize example code or custom libraries from outside sources
> should use caution. The program used should represent the students’ efforts
> and abilities. Blindly using code without understanding the code functionality
> is not consistent with the educational goals of this program. Students should
> be able to understand and explain the code, and students should be able to
> demonstrate that they can program on a level equivalent to the code used in
> their mechanism.

In short yes, as long as you can explain what Robodash does and roughly how it
works. Wether this is necessary is sort-of a grey area, since Robodash gives you
no competitive advantage and PROS itself does many things that you're not
expected to explain (like its RTOS), but it's still good to know.

Reading this documentation, reading the source code, and asking questions on the
Discord server will help you get an idea of how Robodash works and is
implemented if you believe it is necessary.

**Is Robodash compatible with ___ template?**

As long as the other template doesn't use the screen itself (without using
Robodash), it is compatible with Robodash.

**Is Robodash compatible with LLEMU?**

No.
