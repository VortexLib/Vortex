# Integrated PID Tuner

Vortex includes a built-in live PID tuner that allows you to adjust constants on the fly using the V5 Controller and Brain screen. This eliminates the need for repeated code re-compilation during the tuning process.

## Basic Usage

To use the tuner, you must call `pid_tuner_iterate()` within your `opcontrol()` loop or a dedicated background task.

```cpp
void opcontrol() {
    while (true) {
        chassis.opcontrol_tank();
        chassis.pid_tuner_iterate(); // Process tuner inputs
        pros::delay(10);
    }
}
```

### Controls (Default)

- **Arrow Keys (Controller)**: Navigate between PID groups (Drive, Turn, Swing, etc.) and constants (P, I, D, Start I).
- **A / B Buttons**: Increase or decrease the selected constant.
- **X Button**: Toggle between simplified and full tuning modes.

---

## Configuration API

### `pid_tuner_enable()` / `pid_tuner_disable()`

Enables or disables the tuner logic. When disabled, `pid_tuner_iterate()` does nothing.

### `pid_tuner_print_brain_set(bool enable)`

Toggles whether the tuner interface is displayed on the V5 Brain screen.

### `pid_tuner_print_terminal_set(bool enable)`

Toggles whether the current PID constants are printed to the PROS terminal after every adjustment.

### `pid_tuner_full_enable(bool enable)`

- **`false` (Simplified)**: Syncs forward and backward constants. Tuning "Drive P" updates both forward and backward PID.
- **`true` (Full)**: Allows independent tuning of forward and backward constants for asymmetrical robots.

---

## Increment Settings

You can customize how much each constant increases/decreases per button press.

### `pid_tuner_increment_p_set(double val)`

Sets the step size for the Proportional (kP) constant. (Default: `0.1`).

### `pid_tuner_increment_i_set(double val)`

Sets the step size for the Integral (kI) constant. (Default: `0.001`).

### `pid_tuner_increment_d_set(double val)`

Sets the step size for the Derivative (kD) constant. (Default: `0.25`).

### `pid_tuner_increment_start_i_set(double val)`

Sets the step size for the Integral Start threshold. (Default: `1.0`).
