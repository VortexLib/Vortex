# Slew Rate Control {#slew}

## Overview

Slew gradually ramps up the robot's speed from a minimum to the target speed over a set distance. This prevents wheel slip on fast starts and gives smoother acceleration.

## How It Works

When slew is enabled, the robot starts at `min_speed` and linearly increases to full speed over `distance_to_travel`. After that distance, the PID has full control.

## Configuration

### Drive Slew

```cpp
// Set for both forward and backward
chassis.slew_drive_constants_set(7_in, 50);  // 7 inch ramp, start at speed 50

// Set forward and backward separately
chassis.slew_drive_constants_forward_set(7_in, 50);
chassis.slew_drive_constants_backward_set(5_in, 40);
```

### Turn Slew

```cpp
chassis.slew_turn_constants_set(45_deg, 50);  // 45 degree ramp, start at speed 50
```

### Swing Slew

```cpp
chassis.slew_swing_constants_set(7_in, 50);
chassis.slew_swing_constants_forward_set(7_in, 50);
chassis.slew_swing_constants_backward_set(5_in, 40);

// Also supports angle-based
chassis.slew_swing_constants_set(45_deg, 50);
```

## Enabling Slew

### Default Slew (All Motions)

```cpp
chassis.slew_drive_set(true);           // all drive motions
chassis.slew_drive_forward_set(true);   // forward only
chassis.slew_drive_backward_set(true);  // backward only

chassis.slew_turn_set(true);            // all turn motions

chassis.slew_swing_set(true);           // all swing motions
chassis.slew_swing_forward_set(true);
chassis.slew_swing_backward_set(true);
```

### Per-Motion Slew

Override the default with the `slew_on` parameter:

```cpp
// Slew enabled for this motion only
chassis.pid_drive_set(24_in, 110, true);

// Slew disabled for this motion, even if default is on
chassis.pid_drive_set(24_in, 110, false);
```

## Checking State

```cpp
bool fwd_slew = chassis.slew_drive_forward_get();
bool bwd_slew = chassis.slew_drive_backward_get();
bool turn_slew = chassis.slew_turn_get();
bool swing_slew = chassis.slew_swing_forward_get();
```

## Tips

- **Higher min_speed** = less ramp time, more aggressive start
- **Longer distance** = smoother acceleration
- **Use slew on long, fast movements** where wheel slip is likely
- **Disable slew on short movements** where you need quick response
- On high-traction surfaces, you may not need slew at all
