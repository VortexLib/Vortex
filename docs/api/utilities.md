# Math & Utilities

The `vortex::util` namespace contains highly optimized math functions and coordinate structures used throughout the library. Exposure of these functions allows you to build custom logic on top of the Vortex framework.

## Coordinate Structures

### `pose`
A simple structure representing a 2D position and heading.
- **double x**: X-coordinate (inches).
- **double y**: Y-coordinate (inches).
- **double theta**: Heading (degrees).

### `united_pose`
Similar to `pose`, but uses **OkapiLib units** for type-safety.
- **okapi::QLength x**
- **okapi::QLength y**
- **okapi::QAngle theta**

## Math Helpers

### `double wrap_angle(double theta)`
Constrains an angle between **-180 and 180 degrees**. Essential for turning logic.

### `int sgn(double input)`
Returns `1` if the input is positive, `-1` if negative, and `0` if zero.

### `double clamp(double input, double max, double min)`
Restricts `input` to be between `min` and `max`.

### `double to_rad(double deg)` / `double to_deg(double rad)`
Standard trigonometric conversions.

## Geometric Functions

### `double absolute_angle_to_point(pose target, pose current)`
Returns the absolute heading (degrees) required to face a target point from a current position.

### `double distance_to_point(pose target, pose current)`
Returns the Euclidean distance (inches) between two points.

### `pose vector_off_point(double distance, pose current)`
Returns a new `pose` projected `distance` inches away from the `current` pose in its current direction.

## Text & Screen

### `void screen_print(std::string text, int line = 0)`
Prints a string to the V5 brain screen. It automatically handles line wraps and newline characters.

### `void vortex_print()`
Prints the Vortex ASCII logo and version information to the PROS terminal. Use this in `initialize()` for branding!
