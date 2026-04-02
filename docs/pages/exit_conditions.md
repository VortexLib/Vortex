# Exit Conditions {#exit_conditions}

## Overview

Exit conditions determine when a PID motion is "done." Vortex supports multiple exit types that run in parallel — whichever triggers first ends the motion.

## Exit Types

| Exit | Description |
|------|-------------|
| **Small Exit** | Error has been below `small_error` for `small_exit_time` |
| **Big Exit** | Error has been below `big_error` for `big_exit_time` |
| **Velocity Exit** | Motor velocity has been ~0 for `velocity_exit_time` (robot is stuck) |
| **mA Exit** | Motors have been at current limit for `mA_timeout` (robot is stalled) |

## Setting Exit Conditions

### Drive

```cpp
// Parameters: small_time, small_error, big_time, big_error, velocity_time, mA_timeout
chassis.pid_drive_exit_condition_set(300_ms, 1_in, 500_ms, 3_in, 750_ms, 750_ms);

// Raw units
chassis.pid_drive_exit_condition_set(300, 1.0, 500, 3.0, 750, 750);
```

### Turn

```cpp
chassis.pid_turn_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
```

### Swing

```cpp
chassis.pid_swing_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
```

### Odometry

Odom motions have separate drive and turn exit conditions:

```cpp
chassis.pid_odom_drive_exit_condition_set(300_ms, 1_in, 500_ms, 3_in, 750_ms, 750_ms);
chassis.pid_odom_turn_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
```

## Parameters Explained

- **small_exit_time / small_error**: The "settled" condition. When error is below `small_error` for `small_exit_time` ms continuously, the motion exits. Use tight values here.
- **big_exit_time / big_error**: A fallback for when the robot is close but oscillating. Wider error, but it must stay within that zone for the full time.
- **velocity_exit_time**: If motor velocity is near zero for this long, the motion exits. Catches "stuck" scenarios.
- **mA_timeout**: If motors hit their current limit for this long, the motion exits. Catches stall scenarios (pushing against a wall).

## IMU Usage in Exit Conditions

The last parameter in exit condition setters controls whether the IMU is used:

```cpp
// use_imu = true (default): exit conditions check IMU for velocity
chassis.pid_drive_exit_condition_set(300_ms, 1_in, 500_ms, 3_in, 750_ms, 750_ms, true);

// use_imu = false: only check motor sensors
chassis.pid_drive_exit_condition_set(300_ms, 1_in, 500_ms, 3_in, 750_ms, 750_ms, false);
```

## Exit Output

You can read what caused a motion to exit:

```cpp
vortex::exit_output result = chassis.pid_wait();
```

| Value | Meaning |
|-------|---------|
| `RUNNING` | Still running |
| `SMALL_EXIT` | Settled within small error |
| `BIG_EXIT` | Settled within big error |
| `VELOCITY_EXIT` | Robot stopped moving |
| `mA_EXIT` | Motors stalled |
| `ERROR_NO_CONSTANTS` | Exit constants not set |

## Tuning Tips

1. **Start with generous values** and tighten as needed.
2. **Small error** should be your acceptable tolerance (e.g., 1" for drive, 3 degrees for turns).
3. **Big error** is your "good enough" fallback — wider but still acceptable.
4. **Velocity and mA exits** are safety nets — they should be longer than your normal settling time.
5. If motions exit too early, increase the time values. If too late, decrease error thresholds.
