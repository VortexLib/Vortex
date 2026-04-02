# Driver Control Configuration {#opcontrol_config}

## Overview

Vortex provides built-in driver control modes with configurable joystick curves, active braking, and drive reversal.

## Drive Modes

### Tank Drive

Left stick controls left side, right stick controls right side:

```cpp
chassis.opcontrol_tank();
```

### Arcade Drive (Standard)

Left stick Y = forward/backward, left stick X = turning:

```cpp
chassis.opcontrol_arcade_standard(vortex::SINGLE);  // single stick
chassis.opcontrol_arcade_standard(vortex::SPLIT);   // split: left Y + right X
```

### Arcade Drive (Flipped)

Right stick Y = forward/backward, right stick X = turning:

```cpp
chassis.opcontrol_arcade_flipped(vortex::SINGLE);  // single stick
chassis.opcontrol_arcade_flipped(vortex::SPLIT);   // split: right Y + left X
```

## Joystick Curves

Joystick curves apply an exponential function to joystick input, giving finer control at low speeds and full power at high speeds.

### Setting Curves

```cpp
chassis.opcontrol_curve_default_set(4.0, 4.0);  // left curve, right curve
```

Higher values = more exponential curve (more fine control at low speeds). 0 = linear (no curve).

### Controller-Based Adjustment

Enable buttons to adjust curves live:

```cpp
chassis.opcontrol_curve_buttons_toggle(true);

// In opcontrol loop:
chassis.opcontrol_curve_buttons_iterate();
```

By default:
- **Left buttons**: adjust left curve
- **Right buttons**: adjust right curve
- Values persist to SD card

## Joystick Threshold

Set a deadzone for the joysticks:

```cpp
chassis.opcontrol_joystick_threshold_set(5);  // ignore inputs below 5
```

## Active Braking

Active braking uses a small PID to hold the robot's position when joysticks are released:

```cpp
chassis.opcontrol_drive_activebrake_set(2.0);  // kP for active brake, 0 disables
```

## Drive Reversal

Flip which side is "front" for driver control:

```cpp
chassis.opcontrol_drive_reverse_set(true);   // flip front/back
chassis.opcontrol_drive_reverse_set(false);  // normal
```

Enable a button to toggle reversal:

```cpp
// In opcontrol loop:
if (master.get_digital_new_press(DIGITAL_B)) {
  chassis.opcontrol_drive_reverse_set(!chassis.opcontrol_drive_reverse_get());
}
```

## Complete opcontrol Example

```cpp
void opcontrol() {
  chassis.drive_brake_set(pros::E_MOTOR_BRAKE_COAST);

  while (true) {
    // Drive control
    chassis.opcontrol_arcade_standard(vortex::SPLIT);

    // Curve button adjustment
    chassis.opcontrol_curve_buttons_iterate();

    // Your subsystem control here
    // e.g., intake, lift, etc.

    pros::delay(vortex::util::DELAY_TIME);  // Required!
  }
}
```

**Important:** The `pros::delay(vortex::util::DELAY_TIME)` at the end of the loop is required for Vortex's timing calculations to work correctly.
