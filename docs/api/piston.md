# Piston Control

The `vortex::Piston` class provides a simple and intuitive interface for controlling pneumatic cylinders (pistons) in PROS. It includes built-in support for toggle buttons and inverted states.

## Setup

```cpp
#include "Vortex/api.hpp"

// Piston on ADI Port 'A', default state is retracted (false)
vortex::Piston wing('A');

// Piston on ADI Port 'B', default state is extended (true)
vortex::Piston clamp('B', true);
```

## Basic Control

### `void set(bool state)`
Sets the piston state.
- `true`: Sets the piston to the **opposite** of its starting position.
- `false`: Sets the piston to its **default** starting position.

### `bool get()`
Returns the current state of the piston.

## Controller Integration

Vortex makes it incredibly easy to link pistons to controller buttons with a single line of code.

### `void button_toggle(int button)`
Toggles the piston every time the button is pressed.
```cpp
void opcontrol() {
    while (true) {
        wing.button_toggle(master.get_digital_new_press(DIGITAL_L1));
        pros::delay(20);
    }
}
```

### `void buttons(int active, int deactive)`
Sets the piston to "active" when one button is pressed, and "deactive" when another is pressed.
```cpp
void opcontrol() {
    while (true) {
        clamp.buttons(master.get_digital(DIGITAL_R1), master.get_digital(DIGITAL_R2));
        pros::delay(20);
    }
}
```

## 3-Wire Expander Support

If your piston is plugged into a 3-wire expander, use the specific constructor:

```cpp
// Piston on Port 'A' of an ADI expander in Smart Port 1
vortex::Piston expanderPiston('A', 1);
```
