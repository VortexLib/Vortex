# Chassis Controller

The `vortex::Drive` class (aliased as `chassis` in most examples) is the core of the Vortex library. It exposes a powerful suite of movement algorithms perfectly tuned out of the box.

## PTP Movements

### `moveToPose`
Drives the robot smoothly to an exact global absolute X, Y, and Theta.
```cpp
void moveToPose(double x, double y, double theta, int timeoutMs = 3000);
```

### `moveToPoint`
Linearly translates the robot towards the requested coordinate.
```cpp
void moveToPoint(double x, double y, int timeoutMs = 2000, bool forwards = true);
```

### `turnToPoint`
Faces the robot towards a specific global coordinate.
```cpp
void turnToPoint(double x, double y, int timeoutMs = 1000);
```

## Motion Control

### `follow`
Engages the **Pure Pursuit** controller for path following.
```cpp
void follow(std::string pathId, int timeoutMs, double lookahead = 15.0);
```

### `swing`
Performs a swing turn (only one side of the drive moves).
```cpp
void swing(double target, vortex::e_swing side, int timeoutMs = 1000);
```

## Configuration

### `set_pid_constants`
Updates the internal PID constants for various movement types.
```cpp
chassis.set_drive_pid(4.5, 0, 25);
chassis.set_turn_pid(5.0, 0, 30);
```

### `set_exit_conditions`
Customizes how the chassis decides it has reached its target.
```cpp
chassis.set_drive_exit(100, 1.0, 500, 5.0, 50);
```
