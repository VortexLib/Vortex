---
layout: home

hero:
  name: "Vortex"
  text: "High-performance V5 motion control."
  tagline: "Stunningly fast, accurate, and incredibly lightweight odometry library built for PROS."
  actions:
    - theme: brand
      text: Get Started
      link: /guide/getting-started
    - theme: alt
      text: View API Reference
      link: /api/chassis

features:
  - title: Arc Odometry
    details: Incorporates advanced circular-arc integration to track precise movement during very high-speed turns, resolving classical gyro drift issues natively.
  - title: Pure Pursuit
    details: Experience unbelievably smooth dynamic path following. Curves and waypoints look like a breeze, even at top speeds.
  - title: Integrated Auton Selector
    details: Easily switch between multiple autonomous routines using the V5 brain screen or limit switches.
  - title: PID & Slew Control
    details: Robust, classes for PID and Slew rate control to keep your mechanisms stable and your acceleration smooth.
  - title: SD Card Logging
    details: Log telemetry and autonomous selection directly to an SD card for post-match analysis.
  - title: Lightweight & Modular
    details: Designed to be minimal and fast. Only include what you need, with no heavy overhead or background tasks.
---

<style>
/* Background ambient glow */
.VPHome {
  position: relative;
}
.VPHome::before {
  content: '';
  position: absolute;
  top: 100px;
  left: 50%;
  transform: translateX(-50%);
  width: 100%;
  max-width: 800px;
  height: 600px;
  background: radial-gradient(circle, rgba(99, 102, 241, 0.1) 0%, rgba(0,0,0,0) 60%);
  pointer-events: none;
  z-index: -1;
}
</style>
