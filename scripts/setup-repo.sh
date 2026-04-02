#!/usr/bin/env bash
#
# Vortex GitHub Repository Setup Script
#
# This script sets up the VortexLib/Vortex GitHub repository with proper
# settings, labels, and branch protection. Run once after creating the org/repo.
#
# Prerequisites:
#   - GitHub CLI (gh) installed and authenticated
#   - You are a member of the VortexLib org with admin permissions
#
# Usage:
#   ./scripts/setup-repo.sh
#

set -euo pipefail

REPO="VortexLib/Vortex"

echo "=== Vortex Repository Setup ==="
echo ""

# ---- Check prerequisites ----
if ! command -v gh &>/dev/null; then
  echo "ERROR: GitHub CLI (gh) is not installed."
  echo "Install it: https://cli.github.com/"
  exit 1
fi

if ! gh auth status &>/dev/null; then
  echo "ERROR: Not authenticated with GitHub CLI."
  echo "Run: gh auth login"
  exit 1
fi

# ---- Create org if needed ----
echo "[1/6] Checking if VortexLib org exists..."
if ! gh api orgs/VortexLib &>/dev/null 2>&1; then
  echo "  VortexLib org not found."
  echo "  Create it at: https://github.com/organizations/plan"
  echo "  Then re-run this script."
  exit 1
fi
echo "  VortexLib org exists."

# ---- Create repo if needed ----
echo "[2/6] Checking if $REPO exists..."
if ! gh repo view "$REPO" &>/dev/null 2>&1; then
  echo "  Creating $REPO..."
  gh repo create "$REPO" \
    --public \
    --description "Vortex - VEX V5 Odometry Template for PROS" \
    --homepage "https://vortexlib.github.io/Vortex/" \
    --source . \
    --remote origin \
    --push
  echo "  Repository created and code pushed."
else
  echo "  Repository already exists."
  # Make sure remote is set
  if ! git remote get-url origin &>/dev/null 2>&1; then
    git remote add origin "https://github.com/$REPO.git"
    echo "  Added origin remote."
  fi
fi

# ---- Set repo metadata ----
echo "[3/6] Configuring repository settings..."
gh repo edit "$REPO" \
  --description "Vortex - VEX V5 Odometry Template for PROS" \
  --homepage "https://vortexlib.github.io/Vortex/" \
  --enable-issues \
  --enable-wiki=false \
  --enable-projects=false \
  --enable-discussions \
  --default-branch main 2>/dev/null || true

# ---- Set up labels ----
echo "[4/6] Setting up issue labels..."

create_label() {
  local name="$1" color="$2" desc="$3"
  gh label create "$name" --repo "$REPO" --color "$color" --description "$desc" --force 2>/dev/null || true
}

create_label "bug"              "d73a4a"  "Something isn't working"
create_label "enhancement"      "a2eeef"  "New feature or request"
create_label "documentation"    "0075ca"  "Improvements or additions to documentation"
create_label "question"         "d876e3"  "Further information is requested"
create_label "good first issue" "7057ff"  "Good for newcomers"
create_label "help wanted"      "008672"  "Extra attention is needed"
create_label "pid"              "fbca04"  "Related to PID controllers"
create_label "odometry"         "1d76db"  "Related to odometry/tracking"
create_label "pure-pursuit"     "5319e7"  "Related to pure pursuit / path following"
create_label "breaking-change"  "b60205"  "Will require users to update their code"
create_label "wontfix"          "ffffff"  "This will not be worked on"
create_label "duplicate"        "cfd3d7"  "This issue or pull request already exists"

echo "  Labels configured."

# ---- Set up topics ----
echo "[5/6] Setting repository topics..."
gh repo edit "$REPO" \
  --add-topic vex \
  --add-topic vex-v5 \
  --add-topic pros \
  --add-topic robotics \
  --add-topic pid \
  --add-topic odometry \
  --add-topic pure-pursuit \
  --add-topic vex-robotics 2>/dev/null || true
echo "  Topics set."

# ---- Push code ----
echo "[6/6] Pushing code to $REPO..."
CURRENT_REMOTE=$(git remote get-url origin 2>/dev/null || echo "")
EXPECTED_REMOTE="https://github.com/$REPO.git"

if [ "$CURRENT_REMOTE" != "$EXPECTED_REMOTE" ] && [ "$CURRENT_REMOTE" != "git@github.com:$REPO.git" ]; then
  git remote set-url origin "$EXPECTED_REMOTE" 2>/dev/null || git remote add origin "$EXPECTED_REMOTE"
fi

BRANCH=$(git branch --show-current)
git push -u origin "$BRANCH"
echo "  Pushed $BRANCH to origin."

echo ""
echo "=== Setup Complete ==="
echo ""
echo "Repository: https://github.com/$REPO"
echo ""
echo "Next steps:"
echo "  1. Tag a release:  git tag v3.2.2 && git push origin v3.2.2"
echo "     This triggers the release workflow to auto-package the PROS template."
echo ""
echo "  2. Users can then install Vortex with:"
echo "     curl -LO https://github.com/$REPO/releases/download/v3.2.2/Vortex@3.2.2.zip"
echo "     pros c fetch Vortex@3.2.2.zip"
echo "     pros c apply Vortex"
echo ""
echo "  3. Enable GitHub Pages (Settings > Pages) on the 'website' branch"
echo "     if you want docs at https://vortexlib.github.io/Vortex/"
