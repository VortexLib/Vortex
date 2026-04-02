# Vortex {#mainpage}

## VEX V5 Odometry Template for PROS

Vortex is a feature-rich VEX V5 drive template built on [PROS](https://pros.cs.purdue.edu/), providing PID control, odometry, pure pursuit, and more out of the box.

### Features

- **PID Control** — drive, turn, swing, and arc motions with automatic exit conditions
- **Odometry** — position tracking with optional tracking wheels
- **Pure Pursuit** — smooth path following with waypoints
- **Boomerang** — curved approach to target poses with heading
- **Turn Then Drive** — two-phase motion: face the target, then drive straight
- **Motion Chaining** — chain movements together for smooth autonomous routines
- **Slew Rate Control** — smooth acceleration to prevent wheel slip
- **Timed Motions** — every motion function has a blocking timeout overload
- **Autonomous Selector** — on-screen auton selection with SD card persistence
- **PID Tuner** — live PID constant adjustment from the controller

### Quick Start

See the \ref setup page to get started.

### Pages

- \ref setup — Installation and initial configuration
- \ref chassis_setup — Configuring your chassis object
- \ref pid_tuning — How to tune PID constants
- \ref drive_motions — Drive forward/backward movements
- \ref turn_motions — Turn in place movements
- \ref swing_motions — Swing turn movements
- \ref odometry — Odometry and position tracking
- \ref odom_motions — Odometry-based movements (point-to-point, boomerang)
- \ref pure_pursuit — Pure pursuit path following
- \ref turn_then_drive — Turn then drive motion
- \ref timed_motions — Blocking motions with timeout
- \ref slew — Slew rate limiting
- \ref exit_conditions — Exit condition configuration
- \ref sd_card — SD card autonomous persistence
- \ref opcontrol_config — Driver control configuration

### License

Vortex is licensed under the [Mozilla Public License 2.0](https://mozilla.org/MPL/2.0/).
