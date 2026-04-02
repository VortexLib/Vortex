# SD Card Persistence {#sd_card}

## Overview

Vortex persists autonomous selection and joystick curve values to the SD card on the V5 Brain. This means your selected autonomous routine survives power cycles — no re-selecting after every restart.

## Autonomous Selector

### Setup

Register autonomous routines in `initialize()`:

```cpp
void initialize() {
  vortex::as::auton_selector.autons_add({
    {"Close Side\n\nScores 6 rings", close_side},
    {"Far Side\n\nScores 4 rings", far_side},
    {"Skills\n\n60 second run", skills},
    {"Do Nothing", [] {}},
  });
}
```

Each entry has:
- A display string (supports `\n` for line breaks on the brain screen)
- A function pointer to the autonomous routine

### Calling Selected Auton

In `autonomous()`:

```cpp
void autonomous() {
  chassis.pid_targets_reset();
  chassis.drive_imu_reset();
  chassis.drive_sensor_reset();
  chassis.odom_pose_set({0, 0, 0});
  default_constants();

  vortex::as::auton_selector.selected_auton_call();
}
```

### Selecting

Use the brain screen touchscreen to cycle through autonomous routines. The selection is saved to `sd-card/selected_auton.txt`.

### Adding/Removing Autons

```cpp
// Add autons
vortex::as::auton_selector.autons_add({
  {"New Auton", new_auton_function},
});

// The selector page index persists, so if you reorder, the
// saved selection maps to the new order
```

## Joystick Curves

Joystick curve values (for exponential drive control) are also saved to the SD card. Users can adjust curves from the controller during driver control, and the values persist.

## SD Card Files

The following files are stored in the `sd-card/` directory:

| File | Contents |
|------|----------|
| `selected_auton.txt` | Index of the selected autonomous routine |
| `left_curve.txt` | Left joystick curve value |
| `right_curve.txt` | Right joystick curve value |

## Checking SD Card

```cpp
if (vortex::util::SD_CARD_ACTIVE) {
  // SD card is available
}
```

If no SD card is inserted, the selector still works but doesn't persist between power cycles.
