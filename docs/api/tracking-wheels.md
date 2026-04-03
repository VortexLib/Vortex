# Tracking Wheels

The `vortex::tracking_wheel` class represents an encoder coupled with a wheel, used for secondary odometry tracking. This allows Vortex to maintain position even when the drivetrain wheels slip.

## Setup

Vortex supports three types of encoders:
1. **ADI Quadrature Encoders** (standard 3-wire).
2. **V5 Rotation Sensors** (high-resolution smart port).
3. **ADI Expander Encoders** (3-wire encoders plugged into a smart expander).

### Examples

```cpp
#include "Vortex/api.hpp"

// 1. ADI Encoder on ports 'A' and 'B', 2.75" wheel, 6" from center
vortex::tracking_wheel adiTracker({'A', 'B'}, 2.75, 6.0);

// 2. Rotation Sensor on Port 5 (reversed), 2.75" wheel, 0" from center (centered)
vortex::tracking_wheel rotationTracker(-5, 2.75, 0.0);

// 3. ADI Encoder on expander in Smart Port 2, ports 'C' and 'D'
vortex::tracking_wheel expandedTracker(2, {'C', 'D'}, 2.0);
```

## Calibration & Units

### `void wheel_diameter_set(double diameter)`
Sets the diameter of the physical wheel in inches.

### `void ratio_set(double ratio)`
If your encoder is geared relative to the wheel, set the ratio here.
- **Example**: If the wheel rotates twice for every 1 encoder rotation, the ratio is `0.5`.

### `void ticks_per_rev_set(double ticks)`
Sets the resolution of the encoder.
- **ADI Encoders**: Default is `360`.
- **Rotation Sensors**: Default is `36000` (centidegrees).

## Member Functions

### `double get()`
Returns the distance traveled by the tracking wheel in **inches**.

### `double get_raw()`
Returns the raw tick count of the encoder.

### `void reset()`
Resets the encoder position to zero.

### `void distance_to_center_set(double dist)`
Updates the offset from the robot's tracking center. This is critical for accurate arc-based odometry.
- **Positive**: Right of center (for vertical wheels) or Forward of center (for horizontal wheels).
- **Negative**: Left of center (for vertical wheels) or Backward of center (for horizontal wheels).
