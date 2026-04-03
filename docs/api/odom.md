# Odometry Metrics

Retrieving the localized metrics dynamically from the background thread is totally lock-free and extremely fast in Vortex.

## `getPose`

Returns a structural class representing the `X`, `Y` and `Theta` state of the robot globally.

```cpp
vortex::Pose currentPose = chassis.getPose();

printf("X: %f, Y: %f, T: %f\n", currentPose.x, currentPose.y, currentPose.theta);
```

## `setPose`

Teleports the robot internally. This is practically used natively at the very beginning of standard autonomous tasks or skill runs.

```cpp
chassis.setPose(0, 0, 90); // Zeroes coordinates and sets heading accurately sideways.
```
