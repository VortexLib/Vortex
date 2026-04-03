# Path Following & Advanced Algorithms

Vortex features state-of-the-art motion algorithms for smooth, high-speed autonomous traversal. These methods leverage odometry to follow pre-computed paths or dynamically generate arcs.

## Pure Pursuit

Pure Pursuit is an algorithm that computes a "look-ahead" point on a path and steers the robot toward it, resulting in natural, high-speed curves.

### `pid_odom_pp_set`

Follows a vector of `odom` points using standard Pure Pursuit.

- `std::vector<odom> path`: The list of points to follow.
- `bool slew_on` (optional): Enables/disables acceleration ramping.

### `pid_odom_injected_pp_set`

Automatically "injects" extra points into your path to ensure the robot never gets too far from the line. Recommended for sparse paths.

### `pid_odom_smooth_pp_set`

Generates a smooth, curved path from a series of "waypoint" poses. Perfect for going around obstacles without stopping.

---

## Boomerang

The Boomerang algorithm allows the robot to reach a target pose with a specific heading, following a "boomerang-like" arc.

### `pid_odom_boomerang_set`

Starts a Boomerang motion to a single `odom` target.

- `odom target`: Target {x, y, theta}.
- `bool slew_on` (optional): Enables/disables slew.

---

## Point-to-Point (PTP)

Simpler coordinate-based movements for when you don't need complex paths.

### `pid_odom_set`

Moves the robot directly to a coordinate. If a target heading (theta) is provided, it will automatically use the **Boomerang** algorithm.

### `pid_odom_ptp_set`

A strict, linear point-to-point motion. The robot will drive straight to the target {x, y} coordinate without considering its final heading.

### `pid_odom_turn_then_drive_set`

A "turn-then-drive" routine where the robot first faces the target point perfectly, then drives to it. Use this for high precision in tight spaces.

---

## Configuration

### `odom_look_ahead_set(double distance)`

Sets the "look-ahead" distance for Pure Pursuit. A larger distance creates smoother arcs but may cut corners. (Default is `7.0` inches).

### `odom_path_spacing_set(double spacing)`

Sets the density of points injected during `injected_pp_set`. (Default is `0.5` inches).
