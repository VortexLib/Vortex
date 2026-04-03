# Math & Utilities

The `vortex::util` namespace contains highly optimized math functions and coordinate structures used throughout the library.

## Common Enums

Vortex uses specific enumerations to standardize movement behavior and system states.

### `e_angle_behavior`

Defines how the robot calculates its turn direction.

- `vortex::shortest`: Turns the fewest degrees to reach the target.
- `vortex::longest`: Turns the long way around.
- `vortex::left_turn`: Forces a counter-clockwise turn.
- `vortex::right_turn`: Forces a clockwise turn.
- `vortex::raw`: No normalization (uses raw gyro values).

### `drive_directions`

Specifies the forward face of the robot for a motion.

- `vortex::fwd` / `vortex::forward`: Movement uses the front of the robot.
- `vortex::rev` / `vortex::reverse`: Movement uses the back of the robot.

### `exit_output`

Returned by PID controllers to indicate why a motion stopped.

- `vortex::RUNNING`: Motion is still active.
- `vortex::SMALL_EXIT`: Settled within the small error threshold.
- `vortex::BIG_EXIT`: Settled within the big error threshold (failsafe).
- `vortex::VELOCITY_EXIT`: Robot has stopped moving/stalled.
- `vortex::mA_EXIT`: Motors exceeded current limit.

### `e_swing`

Used in swing PID motions to specify the pivot side.

- `vortex::LEFT_SWING`: Left side motors are stopped/slowed, right side pivots.
- `vortex::RIGHT_SWING`: Right side motors are stopped/slowed, left side pivots.

---

## Coordinate Structures

### `pose`

A simple structure representing a 2D position and heading.

- **double x**: X-coordinate (inches).
- **double y**: Y-coordinate (inches).
- **double theta**: Heading (degrees).

### `united_pose`

Similar to `pose`, but uses **OkapiLib units** for type-safety.

- **okapi::QLength x**
- **okapi::QLength y**
- **okapi::QAngle theta**

### `odom` / `united_odom`

Used to define a complete movement target for odometry functions.

- `pose target`: The {x, y, theta} to reach.
- `drive_directions drive_direction`: `fwd` or `rev`.
- `int max_xy_speed`: Speed cap for the motion (1-127).
- `e_angle_behavior turn_behavior`: Default is `shortest`.

---

## Math Helpers

### `double wrap_angle(double theta)`

Constrains an angle between **-180 and 180 degrees**.

### `int sgn(double input)`

Returns `1` if positive, `-1` if negative, and `0` if zero.

### `double clamp(double input, double max, double min)`

Restricts `input` to be between `min` and `max`.

### `double to_rad(double deg)` / `double to_deg(double rad)`

Standard trigonometric conversions.

## Geometric Functions

### `double absolute_angle_to_point(pose target, pose current)`

Returns the absolute heading required to face a target point.

### `double distance_to_point(pose target, pose current)`

Returns the Euclidean distance (inches) between two points.

### `pose vector_off_point(double distance, pose current)`

Returns a new `pose` projected `distance` inches away from the `current` pose.

## Text & Screen

### `void screen_print(std::string text, int line = 0)`

Prints to the brain screen. Handles `\n` and line wraps at 32 characters.

### `void vortex_print()`

Prints the Vortex ASCII logo and version info to the terminal.

### `std::string exit_to_string(exit_output input)`

Converts an `exit_output` enum into a human-readable string for logging.
