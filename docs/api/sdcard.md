# SD Card Utilities

Vortex provides helper functions for interacting with the V5 SD Card (MicroSD). These are primarily used by the Autonomous Selector but can be used for custom telemetry logging.

## Usage

All SD card functions reside in the `vortex::as` namespace (as part of the autonomous selector system).

### Checking for SD Card
You can check if an SD card is installed using a utility constant:
```cpp
if (vortex::util::SD_CARD_ACTIVE) {
    // Write something to the card
}
```

## Features

### Persistent Autonomous Selection
Vortex uses the SD card to remember which autonomous routine you selected, even after a power cycle. This prevents you from forgetting to set your auton during a frantic match.

### Autonomous Logs
While not highly exposed, the SD card system tracks initialization states to ensure the selector only runs when intended.

## API Reference

### `void auton_selector_initialize()`
Reads the previously saved autonomous page from the SD card (`/usd/vortex_auton.txt`) and sets the selector to that page.

### `void auto_sd_update()`
Writes the current autonomous page selection to the SD card.

### `bool enabled()`
Returns `true` if the autonomous selector system is properly initialized and has access to its state.

---

::: warning Format your SD card
Ensure your SD card is formatted to **FAT32** for compatibility with the VEX V5 Brain. Cards larger than 32GB may require special formatting tools.
:::
