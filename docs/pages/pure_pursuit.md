# Pure Pursuit {#pure_pursuit}

## Overview

Pure Pursuit is a path-following algorithm. The robot follows a series of waypoints by chasing a "look-ahead" point on the path. This creates smooth, curved motion through multiple targets.

## Basic Pure Pursuit

```cpp
chassis.pid_odom_pp_set({
  {{0, 24}, fwd, 110},
  {{24, 24}, fwd, 110},
  {{24, 48}, fwd, 110},
  {{0, 48}, fwd, 80},
});
chassis.pid_wait();
```

The robot smoothly follows the path through each waypoint. The final waypoint's speed is the target speed at the end.

## With Heading (Boomerang + Pure Pursuit)

If a waypoint has `theta` set, the robot uses a boomerang approach to arrive at that heading:

```cpp
chassis.pid_odom_pp_set({
  {{0, 24}, fwd, 110},
  {{24, 24}, fwd, 110},
  {{24, 48, 0}, fwd, 80},  // arrive facing 0 degrees
});
chassis.pid_wait();
```

## Injected Pure Pursuit

Injects additional points between your waypoints for smoother paths:

```cpp
chassis.pid_odom_injected_pp_set({
  {{0, 24}, fwd, 110},
  {{24, 24}, fwd, 110},
  {{24, 48}, fwd, 80},
});
chassis.pid_wait();
```

## Smooth Pure Pursuit

Uses spline interpolation for the smoothest possible path:

```cpp
chassis.pid_odom_smooth_pp_set({
  {{0, 24}, fwd, 110},
  {{24, 24}, fwd, 110},
  {{24, 48}, fwd, 80},
});
chassis.pid_wait();
```

## With United Coordinates

```cpp
chassis.pid_odom_pp_set({
  {{{0_in, 24_in}, fwd, 110}},
  {{{24_in, 24_in}, fwd, 110}},
  {{{24_in, 48_in}, fwd, 80}},
});
chassis.pid_wait();
```

## With Slew

```cpp
chassis.pid_odom_pp_set({
  {{0, 24}, fwd, 110},
  {{24, 24}, fwd, 110},
}, true);  // enable slew
chassis.pid_wait();
```

## With Timeout

```cpp
chassis.pid_odom_pp_set({
  {{0, 24}, fwd, 110},
  {{24, 24}, fwd, 80},
}, 5000_ms);
```

## Look-Ahead Distance

The look-ahead distance controls how far ahead on the path the robot targets. Larger values = smoother but wider curves. Smaller values = tighter but potentially jerkier.

```cpp
chassis.odom_look_ahead_set(7.0);  // inches, default
```

## Tips

1. **Start simple** — use 3-4 waypoints and tune from there.
2. **Speed matters** — use lower speeds on tight curves, higher on straights.
3. **Look-ahead** — increase for smoother paths, decrease for accuracy.
4. **Use injected/smooth PP** for paths with many sharp turns.
5. **Test incrementally** — add waypoints one at a time.
