# Installation

## Prerequisites

- PROS 4.x or higher
- A VEX V5 Brain
- VS Code with the PROS extension (recommended)

---

## Method 1 — Depot (Recommended)

Run these two commands from inside your PROS project:

```bash
pros c add-depot Vortex https://raw.githubusercontent.com/jonahchang207/Vortex/depot/stable.json
pros c install Vortex
```

You only need to run `add-depot` once per machine. After that, `pros c install Vortex` works in any project.

If Vortex is already installed and you are upgrading, add `--upgrade`:

```bash
pros c install Vortex --upgrade
```

---

## Method 2 — Manual Download

1. Download `Vortex@0.0.1.zip` from the [latest release](https://github.com/jonahchang207/Vortex/releases/latest)
2. Copy it into the **root of your PROS project**
3. In your project terminal:

```bash
pros c fetch ./Vortex@0.0.1.zip
pros c install Vortex
```

> The `./` prefix is required when fetching a local file.

---

## Upgrading

```bash
pros c install Vortex --upgrade
```

---

## Clean Install (Removing Old Templates)

If you're switching from another template (e.g. EZ-Template, LemLib) or have a corrupted install, remove the old template first:

```bash
# List installed templates to see what's currently applied
pros c info-project

# Remove the old template from your project
pros c uninstall <old-template-name>

# Purge it from the conductor cache (optional, frees disk space)
pros c purge <old-template-name>

# Now install Vortex fresh
pros c install Vortex
```

For example, to replace EZ-Template:

```bash
pros c uninstall EZ-Template
pros c purge EZ-Template
pros c install Vortex
```

> If you run into linker errors or duplicate symbol conflicts after switching templates, do a full clean build: `make clean && make`

---

## Verify

Add to `main.h`:

```cpp
#include "Vortex/api.hpp"
```

Then build:

```bash
make
```

A clean build with no errors means Vortex is installed correctly.

---

## Uninstallation

To completely remove the Vortex template from your PROS conductor cache:

```bash
pros c purge Vortex
```

To remove Vortex from a specific project:

```bash
pros c uninstall Vortex
```
