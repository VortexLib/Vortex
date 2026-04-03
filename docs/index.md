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
  - title: Live Visual Telemetry
    details: Projects a live map of the robot directly onto the V5 brain screen! See motor temperatures, coordinates, and battery stats seamlessly.
  - title: Drift Compensation
    details: Automatically detects when you stop moving to recalculate IMU biases, effectively canceling out mechanical gyro creep.
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
