# Odometry {#odometry}

## Overview

Odometry tracks the robot's position on the field using wheel encoders and the IMU. Vortex supports odometry with integrated motor encoders, external tracking wheels, or both.

## How It Works

The odometry system runs in a background task at 10ms intervals. It reads:

1. **Vertical encoders** — to track forward/backward movement
2. **Horizontal encoder** (optional) — to track lateral movement
3. **IMU** — to track heading

These are combined to update the robot's `(x, y, theta)` pose.

## Setting Up Tracking Wheels

See \ref chassis_setup for how to create and register tracking wheels.

Without tracking wheels, Vortex falls back to using integrated motor encoders and the IMU. This works for basic movements but is less accurate for odometry-based motions.

## Reading Position

```cpp
// Get current pose
vortex::pose current = chassis.odom_pose_get();
double x = current.x;         // inches
double y = current.y;         // inches
double theta = current.theta; // degrees

// Individual getters
double x = chassis.odom_x_get();
double y = chassis.odom_y_get();
double theta = chassis.odom_theta_get();
```

## Setting Position

```cpp
// Set position
chassis.odom_pose_set({0, 0, 0});
chassis.odom_pose_set({24.0, -12.0, 90.0});

// Set individual components
chassis.odom_x_set(0);
chassis.odom_y_set(0);
chassis.odom_theta_set(0);
```

## Resetting

```cpp
// Reset to origin
chassis.odom_pose_set({0, 0, 0});
chassis.drive_sensor_reset();
```

## Accuracy Tips

1. **Use tracking wheels** for best accuracy. Integrated motor encoders have backlash and are affected by gear slop.
2. **Measure wheel diameter precisely** — even 0.05" off compounds over distance.
3. **Measure distance to center accurately** — this is critical for correct arc calculations.
4. **Calibrate IMU on a flat surface** — the robot must be completely still during calibration.
5. **Two vertical + one horizontal tracker** gives the most accurate results.

## Turn Bias

During odometry point-to-point movements, the robot may prioritize turning over driving. Configure this behavior:

```cpp
chassis.odom_turn_bias_set(0.75);       // 0.0 to 1.0, higher = more driving priority
chassis.odom_turn_bias_enable(true);    // enable/disable
```

## Boomerang Lead Distance

For boomerang movements, the lead distance controls how far ahead the carrot point projects:

```cpp
chassis.odom_boomerang_dlead_set(0.625);  // default
chassis.odom_look_ahead_set(7.0);          // look-ahead distance for pure pursuit
```
