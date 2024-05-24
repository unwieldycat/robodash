# Contributing

Thanks for wanting to contribute to robodash. Before contributing code to this
repository, please first open an issue describing the problem you're having or
the feature you want added. This document describes procedures you should follow
when contributing code to this repository.

## Pull Requests

1. Describe the issue your pull request resolves and the changes it makes. Link
   relevant issues.

   - Keep changes focused. Multiple unrelated changes shouldn't be lumped into
     one pull request.

2. Ensure that your changes work before requesting to merge.

   - Changes should compile without warnings and behave as intended
   - Changes for non-major versions should not break API compatibility

3. Ensure that your code is formatted with the provided clang-format
   configuration and follows the style guide.

## Style Guide

Along with formatting with the provided configuration file, code should use the
following conventions to preserve readability and consistency:

- Use appropriate casing
  - Class names should be in `PascalCase`
  - Macros should be in `SCREAM_CASE`
  - Everything else should be `snake_case`
- Use clear (but not excessive) variable names. Don't use names like `temp`,
  `var`, or single letters.
- Add appropriate whitespace to visually seperate blocks of code
- User-facing functions should be annotated with doxygen comments.
- Code comments should only be used if necessary
