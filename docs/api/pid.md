# PID Controller

The `vortex::PID` class is a robust, feature-rich PID implementation designed for VEX Robotics. It supports advanced exit conditions, derivative kick mitigation, and secondary sensor integration.

## Basic Usage

To create a PID controller, you specify the constants ($kP$, $kI$, $kD$) and an optional $iStart$ threshold (the error value at which the integral starts accumulating).

```cpp
#include "Vortex/api.hpp"

// Create a PID controller: kP=4.5, kI=0, kD=25, iStart=0
vortex::PID myPID(4.5, 0, 25);

void autonomous() {
    myPID.target_set(90.0); // Set target to 90 degrees
    
    while (true) {
        double output = myPID.compute(chassis.get_gyro());
        chassis.tank(output, -output); // Drive motors
        
        if (myPID.exit_condition() != vortex::RUNNING) break;
        pros::delay(10);
    }
}
```

## Constructor & Constants

### `PID(double p, double i = 0, double d = 0, double start_i = 0, std::string name = "")`
Creates a PID controller with the specified constants.
- **p**: Proportional gain.
- **i**: Integral gain (optional).
- **d**: Derivative gain (optional).
- **start_i**: The error threshold for integral accumulation (optional).
- **name**: A name for the PID, used in terminal logs (optional).

### `void constants_set(double p, double i, double d, double start_i)`
Updates the constants for an existing PID object.

## Exit Conditions

Vortex PID supports multiple "settling" conditions to ensure your robot stops precisely when it reaches the target.

```cpp
// Set exit conditions: 
// - Small error < 1.0 for 100ms
// - Big error < 5.0 for 500ms
// - Velocity timeout is 50ms
myPID.exit_condition_set(100, 1.0, 500, 5.0, 50);
```

### `void exit_condition_set(...)`
- **small_exit_time**: Time (ms) to stay within `small_error`.
- **small_error**: Maximum error allowed to consider the PID "settled".
- **big_exit_time**: Time (ms) to stay within `big_error` (failsafe).
- **big_error**: Larger error threshold.
- **velocity_exit_time**: Time (ms) to wait if velocity is zero.

### `vortex::exit_output exit_condition()`
Returns the current state of the PID:
- `vortex::RUNNING`: Still moving.
- `vortex::SMALL_EXIT`: Settled within small error.
- `vortex::BIG_EXIT`: Settled within big error.
- `vortex::VELOCITY_EXIT`: Stopped moving.

## Advanced Features

### Secondary Sensors
You can update a secondary sensor (like an IMU while driving straight) to handle velocity exiting more accurately.

```cpp
myPID.velocity_sensor_secondary_toggle_set(true);
myPID.velocity_sensor_secondary_set(chassis.get_gyro());
```

### Derivative Kick Mitigation
Vortex computes the derivative based on the **change in sensor value** rather than the **change in error** to prevent sharp "kicks" when the target is suddenly changed.
