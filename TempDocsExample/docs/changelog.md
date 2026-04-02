# Changelog

## [1.0.3] — 2026-03-19

### Added
- Vortex branding SVGs (banner, logo, icon badge) to README and docs

---

## [1.0.2] — 2026-03-18

### Fixed
- Corrected install instructions to use `add-depot` + `install`
- Patched `supported_kernels` to `>=4.0.0` in template zip

---

## [1.0.1] — 2026-03-17

### Fixed
- Matched LemLib/EZ-Template template conventions

---

## [1.0.0] — 2026-03-17

Initial release of Vortex.

### Features

- Arc-based 2D odometry with circular arc integration
- Full motion suite: `moveToPose`, `moveToPoint`, `turnToHeading`, `turnToPoint`, `swingToHeading`, `swingToPoint`, `turnThenMove`, `follow`
- Trapezoidal velocity profiling with slew-rate limiting
- Pure pursuit path following with curvature-based speed limiting
- IMU drift compensation
- Visual telemetry on the V5 brain screen
- SD card CSV logging at 10 Hz
- Stall detection with automatic motion cancellation
- LLEMU-based autonomous selector
- Built-in PID tuning utilities
