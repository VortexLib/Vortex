#!/usr/bin/env bash

set -e

# Colors for UI
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Change to project root directory
cd "$(dirname "$0")/.."

echo -e "${BLUE}=======================================${NC}"
echo -e "${CYAN}   Vortex Release & Upload Automator   ${NC}"
echo -e "${BLUE}=======================================${NC}"

# Ensure GitHub CLI is installed before starting
if ! command -v gh &> /dev/null; then
    echo -e "${RED}Error: GitHub CLI (gh) is not installed.${NC}"
    echo "Please install it (e.g. 'brew install gh') and authenticate ('gh auth login') before running this script."
    exit 1
fi

if [ ! -f "version" ]; then
    echo -e "${RED}Error: 'version' file not found in the project root.${NC}"
    exit 1
fi

# Fix PATH in case 'pros' and the toolchains are installed locally (like with Homebrew, pipx, Python bins, or Antigravity/VSCode)
export PATH="$HOME/.local/bin:$HOME/Library/Python/3.9/bin:$HOME/Library/Application Support/Antigravity/User/globalStorage/sigbots.pros/install/pros-cli-macos:$HOME/Library/Application Support/Antigravity/User/globalStorage/sigbots.pros/install/pros-toolchain-macos/bin:/usr/local/bin:/opt/homebrew/bin:$PATH"

if ! command -v pros &> /dev/null; then
    echo -e "${RED}Error: 'pros' command not found even after appending default paths.${NC}"
    echo "Please make sure PROS CLI is installed and accessible."
    exit 1
fi

# Get current version and strip leading/trailing whitespace
CURRENT_VERSION=$(cat version | tr -d ' \n\r')
echo -e "Current Version: ${GREEN}${CURRENT_VERSION}${NC}"
echo ""

# Parse SemVer parts
IFS='.' read -r major minor patch <<< "$CURRENT_VERSION"
major=${major:-0}; minor=${minor:-0}; patch=${patch:-0}

# Calculate next versions
NEXT_PATCH="${major}.${minor}.$((patch + 1))"
NEXT_MINOR="${major}.$((minor + 1)).0"
NEXT_MAJOR="$((major + 1)).0.0"

echo -e "Select version bump type:"
echo -e "  1) Patch (${GREEN}$CURRENT_VERSION -> $NEXT_PATCH${NC})"
echo -e "  2) Minor (${GREEN}$CURRENT_VERSION -> $NEXT_MINOR${NC})"
echo -e "  3) Major (${GREEN}$CURRENT_VERSION -> $NEXT_MAJOR${NC})"
echo -e "  4) Cancel"
echo ""
read -p "Choice (1-4): " choice

case $choice in
    1) NEW_VERSION=$NEXT_PATCH ;;
    2) NEW_VERSION=$NEXT_MINOR ;;
    3) NEW_VERSION=$NEXT_MAJOR ;;
    4) echo "Release cancelled."; exit 0 ;;
    *) echo -e "${RED}Invalid choice. Exiting.${NC}"; exit 1 ;;
esac

# Save current branch name so we can switch back later
CURRENT_BRANCH=$(git rev-parse --abbrev-ref HEAD)

echo -e "\n${CYAN}[1/7] Bumping version to ${GREEN}${NEW_VERSION}${NC}..."

# Update version file and Makefile
echo "$NEW_VERSION" > version
if [ "$(uname)" = "Darwin" ]; then
    sed -i '' "s/^VERSION:=.*/VERSION:=${NEW_VERSION}/" Makefile
else
    sed -i "s/^VERSION:=.*/VERSION:=${NEW_VERSION}/" Makefile
fi

echo -e "${CYAN}[2/7] Building PROS template (${NEW_VERSION})...${NC}"
rm -f Vortex@*.zip
pros make template

ZIP_FILE="Vortex@${NEW_VERSION}.zip"
if [ ! -f "$ZIP_FILE" ]; then
    echo -e "${RED}Error: Template zip ($ZIP_FILE) was not generated! Compilation may have failed.${NC}"
    exit 1
fi

echo -e "${CYAN}[3/7] Packaging Example Project...${NC}"
EXAMPLE_ZIP_FILE="Vortex-Example-Project-v${NEW_VERSION}.zip"
rm -f Vortex-Example-Project-v*.zip

# Precompile example project "out of the box"
# We'll manually sync the files from the template zip to ensure "ready out of the box" status 
# ignoring potential PROS conductor issues in different environments.
rm -rf Vortex-Example-Project/include/Vortex Vortex-Example-Project/firmware/Vortex.a
unzip -o "./$ZIP_FILE" -d Vortex-Example-Project/ >/dev/null
rm -f Vortex-Example-Project/template.pros

# Update project.pros version and depot origin to match using jq for safety
jq --arg ver "$NEW_VERSION" '
  .["py/state"].templates.Vortex.version = $ver |
  .["py/state"].templates.Vortex.metadata.origin = "vortex-depot"
' Vortex-Example-Project/project.pros > project.pros.tmp && mv project.pros.tmp Vortex-Example-Project/project.pros

# Clean up any leftover zips in the example project
rm -f Vortex-Example-Project/*.zip

zip -r "$EXAMPLE_ZIP_FILE" Vortex-Example-Project -x "*/.git/*" -x "*/bin/*" -x "*/build/*" -x "*/.cache/*" -x "*/compile_commands.json" -x "*.DS_Store" >/dev/null

echo -e "${CYAN}[4/7] Committing all changes to Git...${NC}"
git add .
git commit -m "Release v$NEW_VERSION" || true
git tag -a "v$NEW_VERSION" -m "Release v$NEW_VERSION" || true

echo -e "${CYAN}[5/7] Pushing to GitHub...${NC}"
git push origin HEAD
git push origin "v$NEW_VERSION"

echo -e "${CYAN}[6/7] Creating GitHub Release...${NC}"
gh release create "v$NEW_VERSION" "./$ZIP_FILE" "./$EXAMPLE_ZIP_FILE" \
    --title "Vortex v$NEW_VERSION" \
    --notes "Release v$NEW_VERSION" \
    --latest || true

echo -e "${CYAN}[7/7] Updating depot branch...${NC}"
# Switch to or create depot branch
if git show-branch depot &>/dev/null || git ls-remote --heads origin depot | grep -q depot; then
    git checkout depot
else
    # Create an orphan branch if it doesn't exist, as depot doesn't share history usually
    git checkout --orphan depot
    git rm -rf .
fi

REPO_SLUG="VortexLib/Vortex"

# Build the correct PROS depot format (JSON array of template objects)
python3 -c "
import json, sys, os

depot_file = 'stable.json'
data = []

if os.path.exists(depot_file):
    with open(depot_file, 'r') as f:
        try:
            loaded = json.load(f)
            # If it's a list, use it; otherwise start fresh
            if isinstance(loaded, list):
                data = loaded
        except json.JSONDecodeError:
            pass

# Remove any existing entry for this version
data = [e for e in data if not (isinstance(e, dict) and e.get('version') == '${NEW_VERSION}')]

# Add new version at the beginning
new_entry = {
    'py/object': 'pros.conductor.templates.base_template.BaseTemplate',
    'name': 'Vortex',
    'version': '${NEW_VERSION}',
    'target': 'v5',
    'supported_kernels': '^4.1.0',
    'metadata': {
        'location': 'https://github.com/${REPO_SLUG}/releases/download/v${NEW_VERSION}/Vortex@${NEW_VERSION}.zip'
    }
}
data.insert(0, new_entry)

with open(depot_file, 'w') as f:
    json.dump(data, f, indent=2)
    f.write('\n')

print(f'Depot updated with Vortex v${NEW_VERSION}')
"

git add stable.json
git commit -m "Update depot to v$NEW_VERSION" || true
git push origin depot

# Return to initial branch
git checkout $CURRENT_BRANCH

echo -e "\n${BLUE}=======================================${NC}"
echo -e "${GREEN} Successfully built, committed, released, and mapped depot for Vortex v${NEW_VERSION}! ${NC}"
echo -e "${BLUE}=======================================${NC}"
echo ""
echo -e "${CYAN}Users can register the depot and upgrade with:${NC}"
echo -e "  pros c add-depot vortex-depot https://raw.githubusercontent.com/${REPO_SLUG}/depot/stable.json"
echo -e "  pros c upgrade Vortex"
