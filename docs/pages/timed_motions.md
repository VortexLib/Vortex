# Timed Motions {#timed_motions}

## Overview

Every motion-setting function in Vortex has a **timed overload** that accepts an `okapi::QTime` timeout as the last parameter. These overloads are **blocking** — they set the motion, wait for it to settle, and guarantee the robot moves on after the timeout expires.

This solves a common problem: if a motion gets stuck (e.g., the robot hits a wall or a PID doesn't converge), the autonomous routine hangs forever. With timed motions, the robot always continues.

## Usage

Add the timeout as the last parameter using the `_ms` or `_s` literal:

```cpp
// Drive forward, move on after 2 seconds max
chassis.pid_drive_set(24_in, 110, 2000_ms);

// Turn, move on after 1.5 seconds max
chassis.pid_turn_set(90_deg, 110, 1500_ms);

// Swing with angle behavior and timeout
chassis.pid_swing_set(vortex::LEFT_SWING, 90_deg, 110, vortex::cw, 1500_ms);

// Odom PTP with timeout
chassis.pid_odom_ptp_set({{24, 24}, fwd, 110}, 3000_ms);

// Pure pursuit with timeout
chassis.pid_odom_pp_set({
  {{0, 24}, fwd, 110},
  {{24, 24}, fwd, 80},
}, 5000_ms);

// Turn then drive with timeout
chassis.pid_odom_turn_then_drive_set({{24, 24}, fwd, 110}, 4000_ms);
```

## How It Works

Each timed overload:
1. Calls the corresponding non-blocking setter (e.g., `pid_drive_set(24_in, 110)`)
2. Calls `pid_wait(timeout_ms)` which blocks until settled **or** the timeout expires
3. Returns, and the next line of autonomous code runs

If the motion settles before the timeout, it returns early — the timeout is a maximum, not a fixed delay.

## Default Timeout

You can set a default timeout that applies to all `pid_wait()` calls:

```cpp
chassis.pid_wait_timeout_set(3000);  // 3 second default

// Now pid_wait() uses 3000ms timeout instead of waiting forever
chassis.pid_drive_set(24_in, 110);
chassis.pid_wait();  // returns after settling or 3 seconds

// Per-call timeout overrides the default
chassis.pid_drive_set(24_in, 110);
chassis.pid_wait(5000);  // uses 5 seconds instead
```

## Supported Functions

Every motion function has a timed overload:

| Family | Example |
|--------|---------|
| `pid_drive_set` | `chassis.pid_drive_set(24_in, 110, 2000_ms)` |
| `pid_turn_set` | `chassis.pid_turn_set(90_deg, 110, 1500_ms)` |
| `pid_turn_relative_set` | `chassis.pid_turn_relative_set(90_deg, 110, 1500_ms)` |
| `pid_swing_set` | `chassis.pid_swing_set(LEFT_SWING, 90_deg, 110, 1500_ms)` |
| `pid_swing_relative_set` | `chassis.pid_swing_relative_set(LEFT_SWING, 45_deg, 110, 1500_ms)` |
| `pid_odom_set` | `chassis.pid_odom_set(24_in, 110, 2000_ms)` |
| `pid_odom_ptp_set` | `chassis.pid_odom_ptp_set({{24, 24}, fwd, 110}, 3000_ms)` |
| `pid_odom_boomerang_set` | `chassis.pid_odom_boomerang_set({{24, 24, 45}, fwd, 110}, 3000_ms)` |
| `pid_odom_pp_set` | `chassis.pid_odom_pp_set({...}, 5000_ms)` |
| `pid_odom_injected_pp_set` | `chassis.pid_odom_injected_pp_set({...}, 5000_ms)` |
| `pid_odom_smooth_pp_set` | `chassis.pid_odom_smooth_pp_set({...}, 5000_ms)` |
| `pid_odom_turn_then_drive_set` | `chassis.pid_odom_turn_then_drive_set({...}, 4000_ms)` |

All variants with `slew_on`, `e_angle_behavior`, `opposite_speed`, united coordinates, etc. are supported.

## Recommended Timeouts

| Motion Type | Typical Timeout |
|------------|-----------------|
| Short drive (< 12") | 1000-1500ms |
| Medium drive (12-36") | 1500-2500ms |
| Long drive (> 36") | 2500-4000ms |
| Turn (< 90 deg) | 1000-1500ms |
| Turn (90-180 deg) | 1500-2000ms |
| Swing | 1000-2000ms |
| Odom PTP | 2000-4000ms |
| Pure pursuit path | 3000-8000ms |
| Turn then drive | 3000-5000ms |

These are guidelines — adjust based on your robot's speed and distance.
