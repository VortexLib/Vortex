# Turn Then Drive {#turn_then_drive}

## Overview

Turn Then Drive is a two-phase motion:

1. **Phase 1**: The robot turns in place to face the target coordinate.
2. **Phase 2**: Once the turn settles, the robot drives in a straight line to the target using point-to-point.

This is useful when you want precise, predictable paths — the robot always faces the target before moving, unlike PTP which corrects heading while driving.

## Basic Usage

```cpp
// Turn to face (24, 24), then drive straight to it
chassis.pid_odom_turn_then_drive_set({{24, 24}, fwd, 110});
chassis.pid_wait();
```

## Reverse

When set to reverse, the robot turns to face 180 degrees away from the target, then drives backward:

```cpp
// Turn away from (24, 24), then drive backward to it
chassis.pid_odom_turn_then_drive_set({{24, 24}, rev, 110});
chassis.pid_wait();
```

## With Slew

```cpp
chassis.pid_odom_turn_then_drive_set({{24, 24}, fwd, 110}, true);
chassis.pid_wait();
```

## With Timeout

```cpp
// Give up after 4 seconds total (turn + drive)
chassis.pid_odom_turn_then_drive_set({{24, 24}, fwd, 110}, 4000_ms);

// With slew and timeout
chassis.pid_odom_turn_then_drive_set({{24, 24}, fwd, 110}, true, 4000_ms);
```

## United Coordinates

```cpp
chassis.pid_odom_turn_then_drive_set({{{24_in, 24_in}, fwd, 110}});
chassis.pid_wait();
```

## When to Use

- **Turn Then Drive** is best when you need the robot to face the target before moving, such as when precision alignment matters.
- **PTP** is faster because it turns and drives simultaneously, but the path curves.
- **Boomerang** is best when you need to arrive at a specific heading.

| Motion | Turns first? | Drives straight? | Arrives at heading? |
|--------|-------------|-------------------|---------------------|
| PTP | No (simultaneous) | Approximately | No |
| Boomerang | No (curved path) | No | Yes |
| Turn Then Drive | Yes | Yes | No |
