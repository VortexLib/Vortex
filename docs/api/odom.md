# Odometry Metrics

Retrieving localized metrics from the background tracking thread is lock-free and extremely fast in Vortex.

## Global Pose

### `getPose`
Returns a `vortex::pose` struct representing the current `x`, `y`, and `theta` of the robot.
```cpp
vortex::pose current = chassis.getPose();
```

### `setPose`
Teleports the robot's internal coordinates. Typically used at the start of autonomous.
```cpp
chassis.setPose(0, 0, 90); // Start at (0,0) facing 90 degrees
```

## Sensor Data

### `get_gyro`
Returns the current heading of the IMU in degrees.
```cpp
double heading = chassis.get_gyro();
```

### `get_dist`
Returns the average distance traveled by the drive encoders (in inches).
```cpp
double dist = chassis.get_dist();
```

## Internal States

### `get_mode`
Returns the current movement mode (e.g., `vortex::PURE_PURSUIT`, `vortex::DRIVE`).
```cpp
vortex::e_mode mode = chassis.get_mode();
```

### `is_settled`
Returns `true` if the chassis has completed its current movement.
```cpp
while (!chassis.is_settled()) pros::delay(10);
```
