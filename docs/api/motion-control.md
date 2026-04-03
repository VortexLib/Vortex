# Motion Control

The `vortex::Drive` class provides a high-level API for precise, closed-loop PID movements. These functions handle everything from simple straight drives to complex coordinate-based turns.

## Movement Primitives

Every movement function in Vortex follows a consistent naming convention: `pid_[type]_set`.

### Driving

#### `pid_drive_set`

Moves the robot forward or backward a specified distance.

- `okapi::QLength target` / `double inches`: The distance to travel.
- `int speed`: Max power (0-127).
- `bool slew_on` (optional): Enables/disables acceleration ramping for this motion.

### Turning

#### `pid_turn_set`

Rotates the robot to a global or relative heading.

- `okapi::QAngle target` / `double degrees`: The target angle.
- `int speed`: Max power (0-127).
- `e_angle_behavior behavior` (optional): `shortest`, `left_turn`, etc.

#### `pid_turn_relative_set`

Rotates the robot relative to its **current** heading.

### Swings

#### `pid_swing_set`

Pivots the robot using only one side of the drivetrain.

- `e_swing type`: `LEFT_SWING` or `RIGHT_SWING`.
- `double target`: Target angle in degrees.
- `int speed`: Max power (0-127).
- `int opposite_speed` (optional): Allows for "arcing" by giving the non-pivoting side some power.

---

## Timed (Blocking) Motions

By default, the `set` functions above are **non-blocking** (they return immediately while the robot moves in the background).

Vortex provides **Timed Overloads** for every motion. Simply add an `okapi::QTime` (e.g., `2000_ms`) as the final argument to make the function block until the robot settles or the timeout expires.

### Example: Blocking vs Non-Blocking

```cpp
// Non-blocking: starts moving and immediately runs and next line
chassis.pid_drive_set(24_in, 110);
do_something_else(); 

// Blocking: waits up to 2 seconds for the robot to finish
chassis.pid_drive_set(24_in, 110, 2000_ms); 
next_auton_step();
```

---

## Synchronization & Waiting

If you use non-blocking motions, you can use these methods to synchronize your code.

### `pid_wait(int timeout_ms = 0)`

Blocks the current task until the robot has settled at its target. If a global timeout is set, it will be used if `0` is passed.

### `pid_wait_until(double target)`

Blocks until the robot has passed a certain distance or angle.

- For driving: Blocks until robot passes `target` inches.
- For turning: Blocks until robot passes `target` degrees.

### `pid_wait_quick()`

A faster version of `pid_wait` that exits as soon as the robot enters the "small error" range, without waiting for it to fully settle/stop oscillating.

### `pid_wait_quick_chain()`

Similar to `pid_wait_quick`, but optimized for "chaining" motions together (e.g., driving then immediately turning without losing momentum).
