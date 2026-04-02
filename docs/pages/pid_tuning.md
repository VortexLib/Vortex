# PID Tuning {#pid_tuning}

## Overview

PID (Proportional-Integral-Derivative) control calculates motor output based on the error between the current and target position. Tuning the constants determines how the robot responds.

- **P (Proportional)**: Output proportional to error. Higher = faster response but more overshoot.
- **I (Integral)**: Accumulates error over time. Helps eliminate steady-state error. Use sparingly.
- **D (Derivative)**: Dampens oscillation by responding to rate of change. Higher = less overshoot but slower settling.
- **Start I**: The error threshold where the I term activates. Prevents integral windup.

## Setting Constants

### Drive Constants

```cpp
// Parameters: kP, kI, kD, startI
chassis.pid_drive_constants_set(10.0, 0.0, 65.0);

// Separate forward/backward constants
chassis.pid_drive_constants_forward_set(10.0, 0.0, 65.0);
chassis.pid_drive_constants_backward_set(8.0, 0.0, 55.0);
```

### Turn Constants

```cpp
chassis.pid_turn_constants_set(3.0, 0.003, 20.0, 15.0);
```

### Swing Constants

```cpp
chassis.pid_swing_constants_set(5.0, 0.0, 35.0);

// Separate forward/backward swing constants
chassis.pid_swing_constants_forward_set(5.0, 0.0, 35.0);
chassis.pid_swing_constants_backward_set(5.0, 0.0, 35.0);
```

### Odometry Angular Constants

```cpp
// Controls how the robot corrects its heading during odom movements
chassis.pid_odom_angular_constants_set(4.0, 0.0, 30.0);

// Boomerang-specific angular constants
chassis.pid_odom_boomerang_constants_set(4.0, 0.0, 30.0);
```

## Tuning Process

### Step 1: Tune Drive P and D

1. Set I to 0, D to 0.
2. Start with a small P value (e.g., 5.0).
3. Run `chassis.pid_drive_set(24_in, 110);` followed by `chassis.pid_wait();`.
4. Increase P until the robot reaches the target quickly but overshoots slightly.
5. Add D to dampen oscillation. Start at ~5x your P value and increase until overshoot is minimal.

### Step 2: Tune Turn P and D

1. Same process with `chassis.pid_turn_set(90_deg, 110);`.
2. P values for turns are typically much lower than drive (e.g., 2-5).
3. D values also lower (e.g., 15-30).

### Step 3: Add I (if needed)

Only add I if the robot consistently stops short of the target (steady-state error).

1. Set a large Start I (e.g., 15-20 degrees for turns).
2. Use a very small I (e.g., 0.001-0.01).
3. If the robot oscillates around the target, reduce I or increase Start I.

## Chain Constants

Chain constants control how close the robot needs to be to the target before starting the next chained motion. Smaller values = tighter paths, larger values = smoother transitions.

```cpp
chassis.pid_drive_chain_constant_set(3_in);
chassis.pid_turn_chain_constant_set(3_deg);
chassis.pid_swing_chain_constant_set(3_deg);

// Forward/backward specific
chassis.pid_drive_chain_forward_constant_set(3_in);
chassis.pid_drive_chain_backward_constant_set(3_in);
```

## Live PID Tuner

Vortex includes a live PID tuner accessible from the controller during autonomous testing. Enable it in `initialize()`:

```cpp
chassis.pid_tuner_toggle();  // Enable/disable
```

Use the controller buttons to adjust constants in real-time and see the results immediately.

## Printing PID Output

Enable print toggle to see PID data in the terminal:

```cpp
chassis.pid_print_toggle(true);
```

This prints error, output, and sensor values each loop iteration — useful for debugging.
