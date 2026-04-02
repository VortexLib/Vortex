# Odometry Motions {#odom_motions}

## Overview

Odometry motions drive the robot to specific `(x, y)` coordinates on the field using position tracking. These are more flexible than basic PID drive/turn because they work in 2D space.

## Point-to-Point (PTP)

Drive in a straight line to an `(x, y)` coordinate while correcting heading:

```cpp
// Drive forward to (24, 24)
chassis.pid_odom_ptp_set({{24, 24}, fwd, 110});
chassis.pid_wait();

// Drive backward to (0, 0)
chassis.pid_odom_ptp_set({{0, 0}, rev, 80});
chassis.pid_wait();
```

With slew:

```cpp
chassis.pid_odom_ptp_set({{24, 24}, fwd, 110}, true);
chassis.pid_wait();
```

With timeout:

```cpp
chassis.pid_odom_ptp_set({{24, 24}, fwd, 110}, 3000_ms);
```

## Boomerang

Boomerang drives to an `(x, y, theta)` target along a curved path, arriving at the specified heading. This is useful when you need to approach a scoring position at a specific angle.

The `theta` field in the target pose controls the approach angle:

```cpp
// Drive to (24, 24) and arrive facing 45 degrees
chassis.pid_odom_boomerang_set({{24, 24, 45}, fwd, 110});
chassis.pid_wait();

// With slew
chassis.pid_odom_boomerang_set({{24, 24, 45}, fwd, 110}, true);
chassis.pid_wait();
```

If `theta` is not set (defaults to `ANGLE_NOT_SET`), it behaves like a normal PTP movement.

## `pid_odom_set` (Auto-Select)

`pid_odom_set` automatically chooses between PTP and boomerang based on whether `theta` is set:

```cpp
// No theta → PTP movement
chassis.pid_odom_set({{24, 24}, fwd, 110});
chassis.pid_wait();

// With theta → Boomerang movement
chassis.pid_odom_set({{24, 24, 90}, fwd, 110});
chassis.pid_wait();
```

## Odometry Drive (Distance-Based)

Drive a set distance using odometry instead of motor encoders. More accurate with tracking wheels:

```cpp
chassis.pid_odom_set(24_in, 110);
chassis.pid_wait();
```

## United Coordinates

Use okapi units for type safety:

```cpp
chassis.pid_odom_ptp_set({{{24_in, 24_in}, fwd, 110}});
chassis.pid_odom_boomerang_set({{{24_in, 24_in, 45_deg}, fwd, 110}});
```

## Angle Behavior with Odom

Control turn direction during odom movements:

```cpp
chassis.pid_odom_behavior_set(vortex::shortest);  // default for all odom movements

// Per-movement override via the odom struct
vortex::odom movement = {{24, 24}, fwd, 110, vortex::cw};
chassis.pid_odom_ptp_set(movement);
```

## Multi-Point Movements

Pass a vector of targets. The robot drives through each one:

```cpp
chassis.pid_odom_set({
  {{0, 24}, fwd, 110},
  {{24, 24}, fwd, 110},
  {{24, 0}, fwd, 80},
});
chassis.pid_wait();
```

## Odom PID Constants

```cpp
// XY (distance) PID — controls speed toward the target
chassis.pid_odom_drive_constants_set(10.0, 0, 65.0);

// Angular PID — controls heading correction during odom movements
chassis.pid_odom_angular_constants_set(4.0, 0, 30.0);

// Boomerang angular PID
chassis.pid_odom_boomerang_constants_set(4.0, 0, 30.0);
```

## Odom Exit Conditions

Separate exit conditions for odom drive and odom turn:

```cpp
chassis.pid_odom_drive_exit_condition_set(300_ms, 1_in, 500_ms, 3_in, 750_ms, 750_ms);
chassis.pid_odom_turn_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
```
