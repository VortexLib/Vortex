# Chassis Setup {#chassis_setup}

## Constructor

The `vortex::Drive` constructor creates and configures your chassis. Motor ports, IMU, wheel size, and gear ratio are set here.

```cpp
vortex::Drive chassis(
  {-5, -6, -7},   // Left motor ports (negative = reversed)
  {8, 9, 10},     // Right motor ports (negative = reversed)
  11,              // IMU port
  3.25,            // Wheel diameter in inches
  600,             // Motor cartridge RPM: 100 (red), 200 (green), 600 (blue)
  1.0              // External gear ratio (driven / driving)
);
```

**Gear ratio:** If your drive uses a 36T gear on the motor driving a 60T gear on the wheel, the ratio is `60.0 / 36.0`.

## Tracking Wheels (Odometry)

For odometry, add tracking wheels after constructing the chassis. Tracking wheels use either ADI encoders or Rotation sensors.

### Rotation Sensor Tracking Wheel

```cpp
// Parameters: port, wheel_diameter, distance_to_center, gear_ratio
vortex::tracking_wheel left_tracker(1, 2.75, -4.5, 1.0);
vortex::tracking_wheel right_tracker(-2, 2.75, 4.5, 1.0);
vortex::tracking_wheel horiz_tracker(3, 2.75, -2.0, 1.0);
```

- **port**: Rotation sensor port. Negative = reversed.
- **wheel_diameter**: Diameter in inches.
- **distance_to_center**: Distance from the wheel to the robot's center. Left of center is negative, right is positive. For horizontal trackers, forward is positive, backward is negative.
- **gear_ratio**: External gear ratio. 1.0 if directly driven.

### ADI Encoder Tracking Wheel

```cpp
// Parameters: {port_top, port_bottom}, wheel_diameter, distance_to_center, gear_ratio
vortex::tracking_wheel left_tracker({`A`, `B`}, 2.75, -4.5, 1.0);
```

### Registering Tracking Wheels

In `initialize()`, register your tracking wheels with the chassis:

```cpp
void initialize() {
  // ... other init code ...

  // Vertical trackers (for forward/backward movement)
  chassis.odom_tracker_left_set(&left_tracker);
  chassis.odom_tracker_right_set(&right_tracker);

  // Horizontal tracker (for lateral movement)
  chassis.odom_tracker_front_set(&horiz_tracker);
  // Or: chassis.odom_tracker_back_set(&back_tracker);
}
```

You can use just integrated motor encoders (no tracking wheels), one vertical tracker, two vertical trackers, and optionally a horizontal tracker. More trackers = more accurate odometry.

## Setting the Starting Position

Set the robot's starting position for odometry:

```cpp
chassis.odom_pose_set({0, 0, 0});       // x, y, theta (degrees)
chassis.odom_pose_set({24.0, -12.0, 90.0});
```

## IMU Calibration

The IMU calibrates automatically during `chassis.initialize()`. The robot must be stationary during calibration (takes ~2 seconds). The loading bar on the brain screen shows calibration progress.

## Motor Brake Mode

```cpp
chassis.drive_brake_set(pros::E_MOTOR_BRAKE_HOLD);   // Hold position
chassis.drive_brake_set(pros::E_MOTOR_BRAKE_COAST);   // Coast (default)
chassis.drive_brake_set(pros::E_MOTOR_BRAKE_BRAKE);   // Brake
```

## Current Limit

Set a current limit to prevent motor burnout:

```cpp
chassis.drive_current_limit_set(2500);  // milliamps, default is 2500
```
