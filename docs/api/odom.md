# Odometry & Tracking

The `vortex::Drive` class implements a high-frequency odometry task that maintains the robot's absolute position using any combination of motor encoders, rotation sensors, or the ADI.

## Global Pose

These methods allow you to interact with the robot's internal coordinate system.

### `odom_pose_set(double x, double y, double theta)`

Teleports the robot to an exact start position.

- **x**: X coordinate (inches).
- **y**: Y coordinate (inches).
- **theta**: Global heading (degrees).

### `odom_pose_get()`

Returns a `vortex::pose` struct containing the current `x`, `y`, and `theta`.

---

## Tracking Wheel Configuration

Vortex is sensor-agnostic. You can configure up to four tracking wheels for maximum accuracy.

### `odom_tracker_left_set(vortex::tracking_wheel* tracker)`

Assigns a `tracking_wheel` object as the primary left-side horizontal sensor.

### `odom_tracker_right_set(vortex::tracking_wheel* tracker)`

Assigns a `tracking_wheel` object as the secondary right-side horizontal sensor.

### `odom_tracker_front_set(vortex::tracking_wheel* tracker)` / `odom_tracker_back_set()`

Assigns vertical tracking wheels for forward/vertical odometry calculations.

---

## Path Following Configuration

These settings control how the Pure Pursuit and Boomerang algorithms process paths.

### `odom_look_ahead_set(double distance)`

Sets the "virtual carrot" distance for the robot to follow on a path. (Default: `7.0`).

### `odom_path_spacing_set(double spacing)`

Sets the interval at which points are injected into a sparse path. (Default: `0.5`).

### `odom_path_smooth_constants_set(double weight_smooth, double weight_data, double tolerance)`

Configures the gradient descent smoother for path generation.

- **weight_smooth**: How much to curve the points.
- **weight_data**: How much to stick to the original waypoints.

---

## Sensors & State

### `drive_imu_get()`

Returns the raw rotation of the inertial sensor.

### `drive_sensor_left()` / `drive_sensor_right()`

Returns the raw encoder travel in inches for the left and right motor banks.
