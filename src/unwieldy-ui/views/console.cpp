#include "console.hpp"

// ============================= Core Functions ============================= //

gui::ConsoleView::ConsoleView(std::string name) : View(name) {}

void gui::ConsoleView::refresh() {}

void gui::ConsoleView::initialize() {}

// =========================== Console Functions =========================== //

void gui::ConsoleView::clear() {}

void gui::ConsoleView::clear_line(int line) {}

void gui::ConsoleView::set_line(int line) {}

void gui::ConsoleView::print(std::string str) {}
