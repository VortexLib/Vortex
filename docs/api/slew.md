# Slew Rate Control

The `vortex::slew` class provides a smooth acceleration curve for motors, preventing mechanical stress and wheel slippage by ramping up motor power over a specified distance.

## Basic Usage

Slew is typically used within a motion algorithm to soften the initial acceleration of the robot.

```cpp
#include "Vortex/api.hpp"

// Create a slew controller: ramps up over 12 inches, starting at speed 30
vortex::slew mySlew(12.0, 30);

void move_with_slew(double target_dist, double max_speed) {
    double current_dist = 0;
    mySlew.initialize(true, max_speed, target_dist, current_dist);

    while (true) {
        current_dist = chassis.get_dist();
        // Compute the slewed speed
        double slewed_speed = mySlew.iterate(current_dist);
        
        chassis.tank(slewed_speed, slewed_speed);
        
        if (reached_target()) break;
        pros::delay(10);
    }
}
```

## Constructor & Initialization

### `slew(double distance, int minimum_speed)`
Defines the parameters for the ramp-up phase.
- **distance**: The distance (in inches) the robot should take to reach its `maximum_speed`.
- **minimum_speed**: The speed at which the movement starts (must be $> 0$ to avoid stalling).

### `void initialize(bool enabled, double maximum_speed, double target, double current)`
Prepares the slew controller for a specific motion.
- **enabled**: Whether to actually apply slew to this motion.
- **maximum_speed**: The target top speed for the movement.
- **target**: The final target position.
- **current**: The starting position of the robot.

## Iteration

### `double iterate(double current)`
Calculates the next speed output based on the current position.
- Returns a value between `minimum_speed` and `maximum_speed`.
- If the robot has traveled past the `distance` defined in the constructor, it returns `maximum_speed`.

## Why use Slew?

Directly setting motors to 100% power can cause:
1. **Wheel Slip**: The wheels spin in place, causing odometry errors.
2. **Gear Wear**: High instantaneous torque can damage high-strength gears over time.
3. **Robot Tipping**: Sharp starts may cause lightweight robots to tip backward.
