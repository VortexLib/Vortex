# Setup {#setup}

## Installation

### Option 1: PROS Depot (Recommended)

Add the Vortex depot and apply the template:

```bash
pros c add-depot Vortex https://raw.githubusercontent.com/VortexLib/Vortex/depot/stable.json
pros c apply Vortex
```

To update to the latest version:
```bash
pros c update
pros c apply Vortex
```

### Option 2: Direct Download

Download the latest release from [GitHub Releases](https://github.com/VortexLib/Vortex/releases), then:

```bash
pros c fetch Vortex@0.0.1.zip
pros c apply Vortex
```

## Project Structure

After installation, your project will have:

```
include/
  Vortex/           # Library headers (do not modify)
    drive/drive.hpp  # Main Drive class
    PID.hpp          # PID controller
    util.hpp         # Enums, structs, utilities
  main.h             # Include this in your files
  subsystems.hpp     # Add your motors/sensors here
  autons.hpp         # Declare autonomous routines here
src/
  main.cpp           # Entry point, chassis setup, opcontrol
  autons.cpp         # Autonomous routines and PID constants
```

## Initial Configuration

### 1. Define Your Chassis

In `main.cpp`, create a `vortex::Drive` object with your motor ports, IMU port, wheel diameter, motor cartridge, and gear ratio:

```cpp
#include "main.h"

// Chassis constructor
vortex::Drive chassis(
  // Left motor ports (negative = reversed)
  {-5, -6, -7},
  // Right motor ports (negative = reversed)
  {8, 9, 10},
  // IMU port
  11,
  // Wheel diameter (inches)
  3.25,
  // Motor cartridge RPM (200 for green, 600 for blue)
  600,
  // External gear ratio (driven/driving). 1.0 if no external gearing
  1.0
);
```

### 2. Set PID Constants

In `autons.cpp`, configure your PID constants in `default_constants()`:

```cpp
void default_constants() {
  // Drive PID
  chassis.pid_drive_constants_set(10.0, 0, 65.0);

  // Turn PID
  chassis.pid_turn_constants_set(3.0, 0.003, 20.0, 15.0);

  // Swing PID
  chassis.pid_swing_constants_set(5.0, 0, 35.0);

  // Drive exit conditions
  chassis.pid_drive_exit_condition_set(300_ms, 1_in, 500_ms, 3_in, 750_ms, 750_ms);

  // Turn exit conditions
  chassis.pid_turn_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);

  // Swing exit conditions
  chassis.pid_swing_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
}
```

### 3. Initialize in `initialize()`

```cpp
void initialize() {
  vortex::vortex_print();       // Print Vortex branding
  default_constants();          // Set PID constants
  chassis.initialize();         // Initialize chassis hardware

  // Set up autonomous selector
  vortex::as::auton_selector.autons_add({
    {"Drive Example\n\nDrives forward and backward", drive_example},
    {"Turn Example\n\nTurns to 90 degrees", turn_example},
  });
}
```

### 4. Set Up `opcontrol()`

```cpp
void opcontrol() {
  while (true) {
    chassis.opcontrol_tank();   // or opcontrol_arcade_standard / opcontrol_arcade_flipped
    pros::delay(vortex::util::DELAY_TIME);
  }
}
```

See \ref chassis_setup for more detailed configuration options.
