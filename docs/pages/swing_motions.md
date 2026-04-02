# Swing Motions {#swing_motions}

## Overview

Swing turns rotate the robot using only one side of the drive while the other side stays still (or moves at a set speed). This creates a wider arc than a point turn.

## Basic Swings

```cpp
// Left swing to 90 degrees (left side moves, right stays)
chassis.pid_swing_set(vortex::LEFT_SWING, 90_deg, 110);
chassis.pid_wait();

// Right swing to 90 degrees (right side moves, left stays)
chassis.pid_swing_set(vortex::RIGHT_SWING, 90_deg, 110);
chassis.pid_wait();
```

## With Opposite Side Speed

Instead of the stationary side holding position, you can set it to move at a specific speed:

```cpp
// Left swing, opposite side drives forward at speed 40
chassis.pid_swing_set(vortex::LEFT_SWING, 90_deg, 110, 40);
chassis.pid_wait();
```

This creates a wider arc. The opposite speed scales proportionally with the swing output.

## Relative Swings

```cpp
// Swing 45 degrees right from current heading
chassis.pid_swing_relative_set(vortex::RIGHT_SWING, 45_deg, 110);
chassis.pid_wait();
```

## Angle Behavior

```cpp
chassis.pid_swing_set(vortex::LEFT_SWING, 90_deg, 110, vortex::cw);
chassis.pid_swing_set(vortex::LEFT_SWING, 90_deg, 110, vortex::ccw);
chassis.pid_swing_set(vortex::LEFT_SWING, 90_deg, 110, vortex::shortest);
```

Set a default:

```cpp
chassis.pid_swing_behavior_set(vortex::shortest);
```

## With Slew

```cpp
chassis.pid_swing_set(vortex::LEFT_SWING, 90_deg, 110, true);
chassis.pid_wait();
```

## With Timeout

```cpp
chassis.pid_swing_set(vortex::LEFT_SWING, 90_deg, 110, 1500_ms);

// All parameters
chassis.pid_swing_set(vortex::LEFT_SWING, 90_deg, 110, 40, vortex::cw, true, 2000_ms);
```

## Raw Units

```cpp
chassis.pid_swing_set(vortex::LEFT_SWING, 90.0, 110);
chassis.pid_swing_relative_set(vortex::RIGHT_SWING, 45.0, 110);
```

## Slew Configuration

```cpp
chassis.slew_swing_constants_set(7_deg, 50);
chassis.slew_swing_constants_forward_set(7_deg, 50);
chassis.slew_swing_constants_backward_set(7_deg, 50);

// Enable slew by default for all swing motions
chassis.slew_swing_set(true);
```

## Minimum Speed

```cpp
chassis.pid_swing_min_set(30);
```
