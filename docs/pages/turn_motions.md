# Turn Motions {#turn_motions}

## Overview

Turn motions rotate the robot in place using both sides of the drive. Both sides spin in opposite directions.

## Basic Turns

### Turn to Absolute Angle

```cpp
// Turn to face 90 degrees
chassis.pid_turn_set(90_deg, 110);
chassis.pid_wait();

// Turn to face -45 degrees
chassis.pid_turn_set(-45_deg, 110);
chassis.pid_wait();
```

### Turn to Raw Angle (Degrees as Double)

```cpp
chassis.pid_turn_set(90.0, 110);
chassis.pid_wait();
```

## Relative Turns

Turn a relative amount from the current heading:

```cpp
// Turn 90 degrees to the right from current heading
chassis.pid_turn_relative_set(90_deg, 110);
chassis.pid_wait();

// Turn 90 degrees to the left
chassis.pid_turn_relative_set(-90_deg, 110);
chassis.pid_wait();
```

## Turn to Point

Turn to face a specific coordinate on the field:

```cpp
// Turn to face the point (24, 24)
chassis.pid_turn_set({24, 24}, fwd, 110);
chassis.pid_wait();

// Turn to face away from (24, 24) — for driving backward to it
chassis.pid_turn_set({24, 24}, rev, 110);
chassis.pid_wait();
```

With united coordinates:

```cpp
chassis.pid_turn_set({24_in, 24_in}, fwd, 110);
chassis.pid_wait();
```

## Angle Behavior

Control which direction the robot turns:

```cpp
// Shortest path (default)
chassis.pid_turn_set(90_deg, 110, vortex::shortest);

// Force clockwise
chassis.pid_turn_set(90_deg, 110, vortex::cw);

// Force counterclockwise
chassis.pid_turn_set(90_deg, 110, vortex::ccw);

// Longest path
chassis.pid_turn_set(90_deg, 110, vortex::longest);

// Raw — go to the exact target value without wrapping
chassis.pid_turn_set(450.0, 110, vortex::raw);
```

Set a default angle behavior:

```cpp
chassis.pid_turn_behavior_set(vortex::shortest);  // default for all turns
```

## With Slew

```cpp
chassis.pid_turn_set(90_deg, 110, true);  // enable slew
chassis.pid_wait();

// With angle behavior and slew
chassis.pid_turn_set(90_deg, 110, vortex::cw, true);
chassis.pid_wait();
```

## With Timeout

```cpp
chassis.pid_turn_set(90_deg, 110, 1500_ms);
chassis.pid_turn_set(90_deg, 110, vortex::cw, 1500_ms);
chassis.pid_turn_set(90_deg, 110, true, 1500_ms);
chassis.pid_turn_set(90_deg, 110, vortex::cw, true, 1500_ms);
```

## Minimum Speed

Set a minimum speed for turns when the robot is within the Start I zone. This prevents the robot from slowing down too much on small corrections:

```cpp
chassis.pid_turn_min_set(30);  // minimum speed of 30
```
