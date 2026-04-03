# Configuration Parameters

Vortex utilizes an incredibly intuitive builder pattern to initialize your robot logic. You establish all the physical geometry of your robot **once**!

## Defining the Chassis

In your `main.cpp` outside of your autonomous tasks:

```cpp
#include "Vortex/api.hpp"

// Initialize basic parameters
vortex::Chassis chassis(
  {1, -2, 3, -4}, // Left Motor Ports (negative reversed)
  {5, -6, 7, -8}, // Right Motor Ports (negative reversed)
  14,             // IMU Port

  // Drivetrain Gearset and Wheel Dimensions
  PROS_BLUE, 
  3.25, // Wheel diameter in inches
  1.0,  // External gear ratio (optional)

  // Tracking details (width in inches)
  12.5
);
```

## Configuring Tracking Wheels 

If you are using external unpowered tracking wheels or odometry pods natively:

::: info Custom Width Configuration
You can pass dedicated `TrackingWheel` definitions dynamically to overriding methods on `chassis`.
:::

```cpp
vortex::TrackingWheel leftTracker(15, 2.75, -5.3); // Port, Diameter, Offset from Center
vortex::TrackingWheel rightTracker(16, 2.75, 5.3);

// Apply directly
chassis.setTrackingWheels(&leftTracker, &rightTracker, nullptr);
```
