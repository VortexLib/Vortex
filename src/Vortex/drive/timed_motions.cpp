/*
This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "Vortex/drive/drive.hpp"

using namespace vortex;

// Helper to convert QTime to ms int for pid_wait
static inline int to_ms(okapi::QTime t) {
  return static_cast<int>(t.convert(okapi::millisecond));
}

// =========================================================================
// pid_drive_set
// =========================================================================

void Drive::pid_drive_set(okapi::QLength p_target, int speed, okapi::QTime timeout) {
  pid_drive_set(p_target, speed);
  pid_wait(to_ms(timeout));
}
void Drive::pid_drive_set(okapi::QLength p_target, int speed, bool slew_on, okapi::QTime timeout) {
  pid_drive_set(p_target, speed, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_drive_set(double target, int speed, okapi::QTime timeout) {
  pid_drive_set(target, speed);
  pid_wait(to_ms(timeout));
}
void Drive::pid_drive_set(double target, int speed, bool slew_on, okapi::QTime timeout) {
  pid_drive_set(target, speed, slew_on);
  pid_wait(to_ms(timeout));
}

// =========================================================================
// pid_turn_set (pose)
// =========================================================================

void Drive::pid_turn_set(pose itarget, drive_directions dir, int speed, okapi::QTime timeout) {
  pid_turn_set(itarget, dir, speed);
  pid_wait(to_ms(timeout));
}
void Drive::pid_turn_set(pose itarget, drive_directions dir, int speed, bool slew_on, okapi::QTime timeout) {
  pid_turn_set(itarget, dir, speed, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_turn_set(pose itarget, drive_directions dir, int speed, e_angle_behavior behavior, okapi::QTime timeout) {
  pid_turn_set(itarget, dir, speed, behavior);
  pid_wait(to_ms(timeout));
}
void Drive::pid_turn_set(pose itarget, drive_directions dir, int speed, e_angle_behavior behavior, bool slew_on, okapi::QTime timeout) {
  pid_turn_set(itarget, dir, speed, behavior, slew_on);
  pid_wait(to_ms(timeout));
}

// =========================================================================
// pid_turn_set (united_pose)
// =========================================================================

void Drive::pid_turn_set(united_pose p_itarget, drive_directions dir, int speed, okapi::QTime timeout) {
  pid_turn_set(p_itarget, dir, speed);
  pid_wait(to_ms(timeout));
}
void Drive::pid_turn_set(united_pose p_itarget, drive_directions dir, int speed, bool slew_on, okapi::QTime timeout) {
  pid_turn_set(p_itarget, dir, speed, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_turn_set(united_pose p_itarget, drive_directions dir, int speed, e_angle_behavior behavior, okapi::QTime timeout) {
  pid_turn_set(p_itarget, dir, speed, behavior);
  pid_wait(to_ms(timeout));
}
void Drive::pid_turn_set(united_pose p_itarget, drive_directions dir, int speed, e_angle_behavior behavior, bool slew_on, okapi::QTime timeout) {
  pid_turn_set(p_itarget, dir, speed, behavior, slew_on);
  pid_wait(to_ms(timeout));
}

// =========================================================================
// pid_turn_set (double)
// =========================================================================

void Drive::pid_turn_set(double target, int speed, okapi::QTime timeout) {
  pid_turn_set(target, speed);
  pid_wait(to_ms(timeout));
}
void Drive::pid_turn_set(double target, int speed, e_angle_behavior behavior, okapi::QTime timeout) {
  pid_turn_set(target, speed, behavior);
  pid_wait(to_ms(timeout));
}
void Drive::pid_turn_set(double target, int speed, bool slew_on, okapi::QTime timeout) {
  pid_turn_set(target, speed, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_turn_set(double target, int speed, e_angle_behavior behavior, bool slew_on, okapi::QTime timeout) {
  pid_turn_set(target, speed, behavior, slew_on);
  pid_wait(to_ms(timeout));
}

// =========================================================================
// pid_turn_set (QAngle)
// =========================================================================

void Drive::pid_turn_set(okapi::QAngle p_target, int speed, okapi::QTime timeout) {
  pid_turn_set(p_target, speed);
  pid_wait(to_ms(timeout));
}
void Drive::pid_turn_set(okapi::QAngle p_target, int speed, e_angle_behavior behavior, okapi::QTime timeout) {
  pid_turn_set(p_target, speed, behavior);
  pid_wait(to_ms(timeout));
}
void Drive::pid_turn_set(okapi::QAngle p_target, int speed, bool slew_on, okapi::QTime timeout) {
  pid_turn_set(p_target, speed, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_turn_set(okapi::QAngle p_target, int speed, e_angle_behavior behavior, bool slew_on, okapi::QTime timeout) {
  pid_turn_set(p_target, speed, behavior, slew_on);
  pid_wait(to_ms(timeout));
}

// =========================================================================
// pid_turn_relative_set (QAngle)
// =========================================================================

void Drive::pid_turn_relative_set(okapi::QAngle p_target, int speed, okapi::QTime timeout) {
  pid_turn_relative_set(p_target, speed);
  pid_wait(to_ms(timeout));
}
void Drive::pid_turn_relative_set(okapi::QAngle p_target, int speed, e_angle_behavior behavior, okapi::QTime timeout) {
  pid_turn_relative_set(p_target, speed, behavior);
  pid_wait(to_ms(timeout));
}
void Drive::pid_turn_relative_set(okapi::QAngle p_target, int speed, bool slew_on, okapi::QTime timeout) {
  pid_turn_relative_set(p_target, speed, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_turn_relative_set(okapi::QAngle p_target, int speed, e_angle_behavior behavior, bool slew_on, okapi::QTime timeout) {
  pid_turn_relative_set(p_target, speed, behavior, slew_on);
  pid_wait(to_ms(timeout));
}

// =========================================================================
// pid_turn_relative_set (double)
// =========================================================================

void Drive::pid_turn_relative_set(double target, int speed, okapi::QTime timeout) {
  pid_turn_relative_set(target, speed);
  pid_wait(to_ms(timeout));
}
void Drive::pid_turn_relative_set(double target, int speed, e_angle_behavior behavior, okapi::QTime timeout) {
  pid_turn_relative_set(target, speed, behavior);
  pid_wait(to_ms(timeout));
}
void Drive::pid_turn_relative_set(double target, int speed, bool slew_on, okapi::QTime timeout) {
  pid_turn_relative_set(target, speed, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_turn_relative_set(double target, int speed, e_angle_behavior behavior, bool slew_on, okapi::QTime timeout) {
  pid_turn_relative_set(target, speed, behavior, slew_on);
  pid_wait(to_ms(timeout));
}

// =========================================================================
// pid_swing_set (double)
// =========================================================================

void Drive::pid_swing_set(e_swing type, double target, int speed, okapi::QTime timeout) {
  pid_swing_set(type, target, speed);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_set(e_swing type, double target, int speed, e_angle_behavior behavior, okapi::QTime timeout) {
  pid_swing_set(type, target, speed, behavior);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_set(e_swing type, double target, int speed, bool slew_on, okapi::QTime timeout) {
  pid_swing_set(type, target, speed, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_set(e_swing type, double target, int speed, e_angle_behavior behavior, bool slew_on, okapi::QTime timeout) {
  pid_swing_set(type, target, speed, behavior, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_set(e_swing type, double target, int speed, int opposite_speed, okapi::QTime timeout) {
  pid_swing_set(type, target, speed, opposite_speed);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_set(e_swing type, double target, int speed, int opposite_speed, e_angle_behavior behavior, okapi::QTime timeout) {
  pid_swing_set(type, target, speed, opposite_speed, behavior);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_set(e_swing type, double target, int speed, int opposite_speed, bool slew_on, okapi::QTime timeout) {
  pid_swing_set(type, target, speed, opposite_speed, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_set(e_swing type, double target, int speed, int opposite_speed, e_angle_behavior behavior, bool slew_on, okapi::QTime timeout) {
  pid_swing_set(type, target, speed, opposite_speed, behavior, slew_on);
  pid_wait(to_ms(timeout));
}

// =========================================================================
// pid_swing_set (QAngle)
// =========================================================================

void Drive::pid_swing_set(e_swing type, okapi::QAngle p_target, int speed, okapi::QTime timeout) {
  pid_swing_set(type, p_target, speed);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_set(e_swing type, okapi::QAngle p_target, int speed, e_angle_behavior behavior, okapi::QTime timeout) {
  pid_swing_set(type, p_target, speed, behavior);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_set(e_swing type, okapi::QAngle p_target, int speed, bool slew_on, okapi::QTime timeout) {
  pid_swing_set(type, p_target, speed, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_set(e_swing type, okapi::QAngle p_target, int speed, e_angle_behavior behavior, bool slew_on, okapi::QTime timeout) {
  pid_swing_set(type, p_target, speed, behavior, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_set(e_swing type, okapi::QAngle p_target, int speed, int opposite_speed, okapi::QTime timeout) {
  pid_swing_set(type, p_target, speed, opposite_speed);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_set(e_swing type, okapi::QAngle p_target, int speed, int opposite_speed, e_angle_behavior behavior, okapi::QTime timeout) {
  pid_swing_set(type, p_target, speed, opposite_speed, behavior);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_set(e_swing type, okapi::QAngle p_target, int speed, int opposite_speed, bool slew_on, okapi::QTime timeout) {
  pid_swing_set(type, p_target, speed, opposite_speed, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_set(e_swing type, okapi::QAngle p_target, int speed, int opposite_speed, e_angle_behavior behavior, bool slew_on, okapi::QTime timeout) {
  pid_swing_set(type, p_target, speed, opposite_speed, behavior, slew_on);
  pid_wait(to_ms(timeout));
}

// =========================================================================
// pid_swing_relative_set (QAngle)
// =========================================================================

void Drive::pid_swing_relative_set(e_swing type, okapi::QAngle p_target, int speed, okapi::QTime timeout) {
  pid_swing_relative_set(type, p_target, speed);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_relative_set(e_swing type, okapi::QAngle p_target, int speed, e_angle_behavior behavior, okapi::QTime timeout) {
  pid_swing_relative_set(type, p_target, speed, behavior);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_relative_set(e_swing type, okapi::QAngle p_target, int speed, bool slew_on, okapi::QTime timeout) {
  pid_swing_relative_set(type, p_target, speed, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_relative_set(e_swing type, okapi::QAngle p_target, int speed, e_angle_behavior behavior, bool slew_on, okapi::QTime timeout) {
  pid_swing_relative_set(type, p_target, speed, behavior, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_relative_set(e_swing type, okapi::QAngle p_target, int speed, int opposite_speed, okapi::QTime timeout) {
  pid_swing_relative_set(type, p_target, speed, opposite_speed);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_relative_set(e_swing type, okapi::QAngle p_target, int speed, int opposite_speed, e_angle_behavior behavior, okapi::QTime timeout) {
  pid_swing_relative_set(type, p_target, speed, opposite_speed, behavior);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_relative_set(e_swing type, okapi::QAngle p_target, int speed, int opposite_speed, bool slew_on, okapi::QTime timeout) {
  pid_swing_relative_set(type, p_target, speed, opposite_speed, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_relative_set(e_swing type, okapi::QAngle p_target, int speed, int opposite_speed, e_angle_behavior behavior, bool slew_on, okapi::QTime timeout) {
  pid_swing_relative_set(type, p_target, speed, opposite_speed, behavior, slew_on);
  pid_wait(to_ms(timeout));
}

// =========================================================================
// pid_swing_relative_set (double)
// =========================================================================

void Drive::pid_swing_relative_set(e_swing type, double target, int speed, okapi::QTime timeout) {
  pid_swing_relative_set(type, target, speed);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_relative_set(e_swing type, double target, int speed, e_angle_behavior behavior, okapi::QTime timeout) {
  pid_swing_relative_set(type, target, speed, behavior);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_relative_set(e_swing type, double target, int speed, bool slew_on, okapi::QTime timeout) {
  pid_swing_relative_set(type, target, speed, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_relative_set(e_swing type, double target, int speed, e_angle_behavior behavior, bool slew_on, okapi::QTime timeout) {
  pid_swing_relative_set(type, target, speed, behavior, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_relative_set(e_swing type, double target, int speed, int opposite_speed, okapi::QTime timeout) {
  pid_swing_relative_set(type, target, speed, opposite_speed);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_relative_set(e_swing type, double target, int speed, int opposite_speed, e_angle_behavior behavior, okapi::QTime timeout) {
  pid_swing_relative_set(type, target, speed, opposite_speed, behavior);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_relative_set(e_swing type, double target, int speed, int opposite_speed, bool slew_on, okapi::QTime timeout) {
  pid_swing_relative_set(type, target, speed, opposite_speed, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_swing_relative_set(e_swing type, double target, int speed, int opposite_speed, e_angle_behavior behavior, bool slew_on, okapi::QTime timeout) {
  pid_swing_relative_set(type, target, speed, opposite_speed, behavior, slew_on);
  pid_wait(to_ms(timeout));
}

// =========================================================================
// pid_odom_set
// =========================================================================

void Drive::pid_odom_set(double target, int speed, okapi::QTime timeout) {
  pid_odom_set(target, speed);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_set(double target, int speed, bool slew_on, okapi::QTime timeout) {
  pid_odom_set(target, speed, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_set(okapi::QLength p_target, int speed, okapi::QTime timeout) {
  pid_odom_set(p_target, speed);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_set(okapi::QLength p_target, int speed, bool slew_on, okapi::QTime timeout) {
  pid_odom_set(p_target, speed, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_set(odom imovement, okapi::QTime timeout) {
  pid_odom_set(imovement);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_set(odom imovement, bool slew_on, okapi::QTime timeout) {
  pid_odom_set(imovement, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_set(united_odom p_imovement, okapi::QTime timeout) {
  pid_odom_set(p_imovement);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_set(united_odom p_imovement, bool slew_on, okapi::QTime timeout) {
  pid_odom_set(p_imovement, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_set(std::vector<odom> imovements, okapi::QTime timeout) {
  pid_odom_set(imovements);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_set(std::vector<odom> imovements, bool slew_on, okapi::QTime timeout) {
  pid_odom_set(imovements, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_set(std::vector<united_odom> p_imovements, okapi::QTime timeout) {
  pid_odom_set(p_imovements);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_set(std::vector<united_odom> p_imovements, bool slew_on, okapi::QTime timeout) {
  pid_odom_set(p_imovements, slew_on);
  pid_wait(to_ms(timeout));
}

// =========================================================================
// pid_odom_ptp_set
// =========================================================================

void Drive::pid_odom_ptp_set(odom imovement, okapi::QTime timeout) {
  pid_odom_ptp_set(imovement);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_ptp_set(odom imovement, bool slew_on, okapi::QTime timeout) {
  pid_odom_ptp_set(imovement, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_ptp_set(united_odom p_imovement, okapi::QTime timeout) {
  pid_odom_ptp_set(p_imovement);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_ptp_set(united_odom p_imovement, bool slew_on, okapi::QTime timeout) {
  pid_odom_ptp_set(p_imovement, slew_on);
  pid_wait(to_ms(timeout));
}

// =========================================================================
// pid_odom_boomerang_set
// =========================================================================

void Drive::pid_odom_boomerang_set(odom imovement, okapi::QTime timeout) {
  pid_odom_boomerang_set(imovement);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_boomerang_set(odom imovement, bool slew_on, okapi::QTime timeout) {
  pid_odom_boomerang_set(imovement, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_boomerang_set(united_odom p_imovement, okapi::QTime timeout) {
  pid_odom_boomerang_set(p_imovement);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_boomerang_set(united_odom p_imovement, bool slew_on, okapi::QTime timeout) {
  pid_odom_boomerang_set(p_imovement, slew_on);
  pid_wait(to_ms(timeout));
}

// =========================================================================
// pid_odom_pp_set
// =========================================================================

void Drive::pid_odom_pp_set(std::vector<odom> imovements, okapi::QTime timeout) {
  pid_odom_pp_set(imovements);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_pp_set(std::vector<odom> imovements, bool slew_on, okapi::QTime timeout) {
  pid_odom_pp_set(imovements, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_pp_set(std::vector<united_odom> p_imovements, okapi::QTime timeout) {
  pid_odom_pp_set(p_imovements);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_pp_set(std::vector<united_odom> p_imovements, bool slew_on, okapi::QTime timeout) {
  pid_odom_pp_set(p_imovements, slew_on);
  pid_wait(to_ms(timeout));
}

// =========================================================================
// pid_odom_injected_pp_set
// =========================================================================

void Drive::pid_odom_injected_pp_set(std::vector<odom> imovements, okapi::QTime timeout) {
  pid_odom_injected_pp_set(imovements);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_injected_pp_set(std::vector<odom> imovements, bool slew_on, okapi::QTime timeout) {
  pid_odom_injected_pp_set(imovements, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_injected_pp_set(std::vector<united_odom> p_imovements, okapi::QTime timeout) {
  pid_odom_injected_pp_set(p_imovements);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_injected_pp_set(std::vector<united_odom> p_imovements, bool slew_on, okapi::QTime timeout) {
  pid_odom_injected_pp_set(p_imovements, slew_on);
  pid_wait(to_ms(timeout));
}

// =========================================================================
// pid_odom_smooth_pp_set
// =========================================================================

void Drive::pid_odom_smooth_pp_set(std::vector<odom> imovements, okapi::QTime timeout) {
  pid_odom_smooth_pp_set(imovements);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_smooth_pp_set(std::vector<odom> imovements, bool slew_on, okapi::QTime timeout) {
  pid_odom_smooth_pp_set(imovements, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_smooth_pp_set(std::vector<united_odom> p_imovements, okapi::QTime timeout) {
  pid_odom_smooth_pp_set(p_imovements);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_smooth_pp_set(std::vector<united_odom> p_imovements, bool slew_on, okapi::QTime timeout) {
  pid_odom_smooth_pp_set(p_imovements, slew_on);
  pid_wait(to_ms(timeout));
}

// =========================================================================
// pid_odom_turn_then_drive_set
// =========================================================================

void Drive::pid_odom_turn_then_drive_set(odom imovement, okapi::QTime timeout) {
  pid_odom_turn_then_drive_set(imovement);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_turn_then_drive_set(odom imovement, bool slew_on, okapi::QTime timeout) {
  pid_odom_turn_then_drive_set(imovement, slew_on);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_turn_then_drive_set(united_odom p_imovement, okapi::QTime timeout) {
  pid_odom_turn_then_drive_set(p_imovement);
  pid_wait(to_ms(timeout));
}
void Drive::pid_odom_turn_then_drive_set(united_odom p_imovement, bool slew_on, okapi::QTime timeout) {
  pid_odom_turn_then_drive_set(p_imovement, slew_on);
  pid_wait(to_ms(timeout));
}
