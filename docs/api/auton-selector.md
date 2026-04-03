# Autonomous Selector

Vortex includes a powerful, built-in Autonomous Selector that allows you to easily switch between routines using the V5 Brain's screen or physical limit switches.

## Setup

The selector is managed by the `vortex::as` namespace. You must first define your autonomous routines and then initialize the selector.

### Defining Autons

```cpp
#include "Vortex/api.hpp"

// Define your functions
void red_left() { /* ... */ }
void blue_right() { /* ... */ }

// Create Auton objects
vortex::Auton redLeft("Red Left", red_left);
vortex::Auton blueRight("Blue Right", blue_right);

void initialize() {
    // Add autons to the selector
    vortex::as::auton_selector.autons_add({redLeft, blueRight});
    
    // Initialize the LLEMU (LCD) selector
    vortex::as::initialize();
}
```

## Routine Execution

In your `autonomous()` function, simply call the selector to trigger the routine you chose on the brain:

```cpp
void autonomous() {
    vortex::as::auton_selector.selected_auton_call();
}
```

## Physical Switch Integration

If you prefer physical buttons on your robot to switch routines, you can link limit switches to the selector.

### `limit_switch_lcd_initialize(pros::adi::DigitalIn* right, pros::adi::DigitalIn* left = nullptr)`
- **right**: Limit switch to increment page.
- **left**: Limit switch to decrement page (optional).

```cpp
pros::adi::DigitalIn switchIncrement('H');

void initialize() {
    vortex::as::limit_switch_lcd_initialize(&switchIncrement);
}
```

## SD Card Persistence

If an SD card is present, Vortex will automatically save your last selected autonomous routine. When the robot reboots, it will default to the previously selected page.

- **`vortex::as::auto_sd_update()`**: Saves the current page to the SD card. (Called automatically by the selector).
- **`vortex::as::auton_selector_initialize()`**: Loads the page from the SD card.
