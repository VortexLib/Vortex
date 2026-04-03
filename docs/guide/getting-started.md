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

## Choosing Your Starting Point

Vortex offers two ways to jump into development:

### A. Blank Template (Recommended for Veterans)
If you already have a codebase or want to start from scratch, simply install the library as shown above and start including `Vortex/api.hpp`.

### B. Example Project (Recommended for Starters)
We provide a pre-configured **Example Project** that includes:
- A fully mapped Chassis with PID constants.
- Example Autonomous routines (Swing, Drive, Turn).
- A subsystem structure ready for expansion.

You can download the latest `Vortex-Example-Project.zip` from our [GitHub Releases](https://github.com/jonahchang207/Vortex/releases). Unzip it and open the folder in VS Code to get started immediately!
