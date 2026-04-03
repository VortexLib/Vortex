# Installation

Before utilizing the massive power of Vortex, ensure your environment is fully prepared! 

## Prerequisites

::: tip Verified Stack
*   **PROS 4.x** or higher installed.
*   **A VEX V5 Brain** and firmware up to date.
*   **VS Code** with the PROS V5 extension optimally configured.
:::

## 1. Quick Install via Depot

Vortex is maintained securely via our high-speed depot. From the root of your project terminal, execute the following commands:

```bash
pros c add-depot Vortex https://raw.githubusercontent.com/VortexLib/Vortex/depot/stable.json
pros c install Vortex
```

> **Note**: `add-depot` only needs to be run once per machine! You can continue using `pros c install Vortex` on future projects smoothly!

## 2. Upgrading 

To pull in the newest algorithms and bug fixes on a previous install:

```bash
pros c install Vortex --upgrade
```

## 3. Verify the Installation!

Simply pop open your `main.h` (or `main.cpp`) and verify the library linker completes:

```cpp
#include "Vortex/api.hpp"
```

Compile with:

```bash
make
```

If it successfully links and throws no compilation errors, you are completely armed and ready to conquer the field! 🎉
