# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Vortex is a custom VEX V5 odometry template, forked from EZ-Template and rebranded under the `vortex` namespace. Built with **PROS** (Purdue Robotics Operating System), targeting the ARM Cortex-A9 on the VEX V5 Brain. C++ (gnu++20 standard).

## Build Commands

```bash
pros make              # Full build (compiles and links)
pros make quick        # Incremental build (default target)
pros mu                # Build and upload to robot
pros upload            # Upload without rebuilding
pros make clean        # Clean build artifacts
```

PROS CLI must be installed. The toolchain uses `arm-none-eabi-` cross-compiler.

## Project Structure

- `src/main.cpp` — Entry point with PROS competition callbacks (`initialize`, `autonomous`, `opcontrol`, `disabled`, `competition_initialize`). Defines the `chassis` object (motor ports, IMU, wheel specs) and the autonomous selector menu.
- `src/autons.cpp` — All autonomous routines and PID/odometry constants (`default_constants()`). This is where drive tuning values and match autonomous programs live.
- `include/subsystems.hpp` — Declares the `chassis` extern and is the place to add motors/sensors for mechanisms (intake, lift, etc.).
- `include/autons.hpp` — Forward declarations for all autonomous routines.
- `src/Vortex/` — Library source (PID, drive control, odometry, pure pursuit, slew, auton selector, SD card persistence, tracking wheels).
- `sd-card/` — Persisted state files (selected auton, joystick curve values). Deployed to the SD card on the V5 Brain.

## Architecture

The `vortex::Drive` chassis object is the central abstraction. It wraps drive motors, IMU, and optional tracking wheels, providing:
- **PID controllers** for drive, turn, swing, and arc motions
- **Odometry** with optional tracking wheels for position tracking
- **Pure Pursuit** and **Boomerang** path-following algorithms
- **Motion chaining** via `pid_wait_quick_chain()` for smoother autonomous routines

Autonomous routines follow the pattern: set a PID target -> wait for completion -> next motion. Use `_in` and `_deg` literals for units (e.g., `24_in`, `90_deg`).

The autonomous selector (`vortex::as::auton_selector`) is registered in `initialize()` and persists selection to SD card. Selected auton is called in `autonomous()` via `selected_auton_call()`.

## Key Conventions

- All library types and functions live in the `vortex` namespace (e.g., `vortex::Drive`, `vortex::PID`, `vortex::LEFT_SWING`, `vortex::shortest`).
- Motor ports are defined in `main.cpp` chassis constructor. Negative port numbers reverse the motor.
- PID constants and exit conditions are tuned in `default_constants()` in `autons.cpp`.
- Speed values are out of 127.
- The `opcontrol` loop must include `pros::delay(vortex::util::DELAY_TIME)` at the end for timing calculations.
- New subsystem motors/sensors go in `subsystems.hpp`; new autonomous routines go in `autons.cpp` with declarations in `autons.hpp`.
