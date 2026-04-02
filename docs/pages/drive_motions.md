# Drive Motions {#drive_motions}

## Overview

Drive motions move the robot forward or backward in a straight line, using PID to control distance and a heading correction PID to keep the robot driving straight.

## Basic Usage

```cpp
// Drive 24 inches forward at speed 110
chassis.pid_drive_set(24_in, 110);
chassis.pid_wait();

// Drive 24 inches backward at speed 110
chassis.pid_drive_set(-24_in, 110);
chassis.pid_wait();
```

## With Slew

Slew ramps up speed gradually to prevent wheel slip:

```cpp
chassis.pid_drive_set(24_in, 110, true);  // true enables slew
chassis.pid_wait();
```

## With Timeout

Every motion function has a timed overload that blocks until settled or timed out:

```cpp
// Drive forward, give up after 2 seconds no matter what
chassis.pid_drive_set(24_in, 110, 2000_ms);

// With slew and timeout
chassis.pid_drive_set(24_in, 110, true, 3000_ms);
```

## Raw Units (Encoder Ticks)

If you prefer raw encoder ticks instead of inches:

```cpp
chassis.pid_drive_set(1000, 110);       // 1000 ticks forward
chassis.pid_drive_set(1000, 110, true); // with slew
```

## Heading Correction

By default, the heading PID keeps the robot driving straight. You can disable it:

```cpp
chassis.pid_drive_set(24_in, 110, false, false);  // slew off, heading off
```

## Wait Functions

### `pid_wait()`

Blocks until the motion is complete (PID has settled):

```cpp
chassis.pid_drive_set(24_in, 110);
chassis.pid_wait();  // blocks here until done
```

### `pid_wait(timeout_ms)` / `pid_wait(timeout)`

Blocks until settled OR the timeout expires:

```cpp
chassis.pid_drive_set(24_in, 110);
chassis.pid_wait(2000);  // blocks for max 2 seconds
```

### `pid_wait_until(distance)`

Blocks until the robot has traveled a certain distance:

```cpp
chassis.pid_drive_set(48_in, 110);
chassis.pid_wait_until(24_in);     // wait until 24 inches traveled
// Do something mid-motion (e.g., deploy an intake)
chassis.pid_wait();                 // wait for full completion
```

### `pid_wait_quick_chain()`

Exits early for motion chaining — starts the next motion before fully settling:

```cpp
chassis.pid_drive_set(24_in, 110);
chassis.pid_wait_quick_chain();
chassis.pid_turn_set(90_deg, 110);
chassis.pid_wait();
```

## Speed

Speed values range from 0 to 127.

## Slew Configuration

Configure slew behavior before using it:

```cpp
chassis.slew_drive_constants_set(7_in, 50);           // 7 inch ramp, start at speed 50
chassis.slew_drive_constants_forward_set(7_in, 50);   // forward only
chassis.slew_drive_constants_backward_set(7_in, 50);  // backward only

// Enable slew by default for all drive motions
chassis.slew_drive_set(true);
```
