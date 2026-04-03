# Chassis Controller

The `Chassis` class exposes a powerful and robust suite of movement algorithms perfectly tuned out of the box natively integrated directly to PROS.

## `moveToPose`

Drives the robot smoothly to an exact global absolute X, Y, and Theta.

```cpp
void moveToPose(double x, double y, double theta, int timeoutMs = 3000);
```

**Parameters**
- `x`: Global X coordinate in inches.
- `y`: Global Y coordinate in inches.
- `theta`: Global heading in degrees (Absolute).
- `timeoutMs`: Time limit before the native solver auto-cancels.

---

## `moveToPoint`

Linearly translates the robot towards the requested coordinate regardless of the ending orientation constraint. Note that this prioritizes speed and smoothness over locking into a specific heading at the end.

```cpp
void moveToPoint(double x, double y, int timeoutMs = 2000, bool forwards = true);
```

## `follow`

Engages the high-speed **Pure Pursuit** controller, executing dynamic sweeps through text-based Path files directly generated from apps like PathPlanner.

```cpp
void follow(std::string pathId, int timeoutMs, double lookahead = 15.0);
```
