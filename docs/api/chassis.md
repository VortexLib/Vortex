# Chassis Configuration & Utilities

The `vortex::Drive` class is the central controller for your robot's drivetrain. It manages sensors, motor braking, driver curves, and power distribution.

## System Configuration

These methods control the fundamental behavior of the drive motors and system reporting.

### `drive_brake_set(pros::motor_brake_mode_e_t brake_type)`

Changes how the motors behave when they are not under active control.

- `pros::E_MOTOR_BRAKE_COAST`: No braking.
- `pros::E_MOTOR_BRAKE_BRAKE`: Electric braking.
- `pros::E_MOTOR_BRAKE_HOLD`: Active position holding.

### `drive_current_limit_set(int mA)` / `drive_current_limit_get()`

Sets or retrieves the maximum current (in milliamps) the drive motors can pull before internal clipping.

### `pid_drive_toggle(bool toggle)` / `pid_print_toggle(bool toggle)`

- `pid_drive_toggle`: Enables or disables the internal PID loops for autonomous motions.
- `pid_print_toggle`: Enables or disables terminal logging during autonomous motions.

---

## Driver Control (Opcontrol)

Vortex provides sophisticated joystick processing, including dual-motor grouping and customizable input curves.

### `opcontrol_tank()` / `opcontrol_arcade_standard(e_type stick_type)`

Activates driver control in your `opcontrol()` loop.

- `opcontrol_tank`: Left stick controls left side, right stick controls right side.
- `opcontrol_arcade_standard`: Standard arcade drive (Forward/Turn on same stick or split).

### `opcontrol_curve_default_set(double left, double right = 0)`

Sets the joystick sensitivity curves. A value of `0` is linear, while higher values provide more precision at low speeds.

### `opcontrol_drive_activebrake_set(double kp, double ki, double kd)`

Enables an "active brake" mode where the robot uses a PID loop to stay perfectly still when joysticks are released.

---

## IMU & Sensor Management

Utilities for calibrating and interacting with the V5 Inertial Sensor.

### `drive_imu_calibrate(bool run_loading_animation = true)`

Starts the IMU calibration process. Returns `true` if successful.

### `drive_imu_reset(double heading = 0)`

Resets the IMU rotation value to the specified heading (default is 0).

### `drive_imu_scaler_set(double scaler)` / `drive_imu_scaler_get()`

Adjusts for gyro drift or non-perfect 360-degree rotations.

---

## PTO (Power Take-Off)

Dynamically remove motors from the drivetrain to power other mechanisms.

### `pto_add(std::vector<pros::Motor> motors)`

Removes the specified motors from the drivetrain control list.

### `pto_remove(std::vector<pros::Motor> motors)`

Returns the specified motors to the drivetrain control list.

---

## Telemetry

Real-time data access for diagnostics and custom logging.

### `drive_sensor_left()` / `drive_sensor_right()`

Returns the current distance traveled by each side in inches.

### `drive_velocity_left()` / `drive_velocity_right()`

Returns the current motor velocity in RPM.

### `drive_mA_left()` / `drive_mA_right()`

Returns the current power draw of the drive side in milliamps.

### `drive_current_left_over()` / `drive_current_right_over()`

Returns `true` if the motor group is currently exceeding its safety current limit.
