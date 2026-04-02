# Vortex CLI

`vortex-cli` is a shell script at the project root that handles version bumping, building, and GitHub releases. It has two modes: an interactive menu and a flag-based mode for scripting.

---

## Interactive Mode

Run with no arguments to open the menu:

```bash
./vortex-cli
```

The header shows the current version, active branch, and number of staged changes. Select a number:

| Key | Action |
|-----|--------|
| `1` | Patch bump (`x.x.N+1`), commit, optional full release |
| `2` | Minor bump (`x.N+1.0`), commit, optional full release |
| `3` | Major bump (`N+1.0.0`), commit, optional full release |
| `4` | Manual version — enter exact version string |
| `5` | Dev push — commit + push current branch, no version change |
| `6` | Release current version — tag, merge to `stable`, upload |
| `7` | `make` — build the library locally |
| `8` | `mkdocs build` — build docs locally |
| `9` | `pros c purge Vortex` — clear the PROS template cache |
| `q` | Quit |

For bump options (1–4), you are prompted for a commit message. If left blank, it defaults to `release: version X.X.X`. You are then asked whether to create a full GitHub release or just push to the current branch.

---

## Flag Mode

```bash
./vortex-cli [flags] ["commit message"]
```

| Flag | Effect |
|------|--------|
| `-p` | Patch bump (default if no bump flag given) |
| `-m` | Minor bump |
| `-M` | Major bump |
| `-v 1.2.3` | Set an exact version instead of bumping |
| `-R` | Perform a full release after bumping (merge → `stable`, tag, upload) |
| `-B` | Build library only (`make`) then exit |
| `-D` | Build docs only (`mkdocs build`) then exit |
| `-P` | Purge PROS template cache (`pros c purge Vortex`) then exit |
| `-z` | Build PROS template zip (`make template`) then exit |

### Examples

```bash
# Patch bump → commit → push dev (no release)
./vortex-cli

# Patch bump + full release
./vortex-cli -R "fix: correct odometry arc calculation"

# Minor bump + full release
./vortex-cli -m -R

# Set exact version + full release
./vortex-cli -v 2.0.0 -R "feat: v2 rewrite"

# Build the template zip without releasing
./vortex-cli -z

# Purge the PROS cache (useful after a bad install)
./vortex-cli -P
```

---

## Release Flow

When a release is triggered (option `6` in the menu, or `-R` flag):

1. **Version files updated** — `Makefile`, `template.pros`, and `docs/installation.md` are written with the new version string.
2. **Commit** — all changes are staged and committed with the provided message.
3. **Merge to `stable`** — `dev` is merged into `stable` with a `--no-ff` merge commit.
4. **Tag** — a `vX.X.X` git tag is created and pushed.
5. **Build template** — `make template` compiles the library, packages `Vortex@X.X.X.zip`, and post-processes it to set `supported_kernels: >=4.0.0`.
6. **Update depot** — `stable.json` on the `depot` branch is updated to point to the new release via a temporary git worktree.
7. **GitHub release** — `gh release create` uploads both `Vortex@X.X.X.zip` and `Vortex-X.X.X.zip` as release assets.
8. **Sync back** — `stable` is merged back into `dev` so both branches stay in sync.

!!! note
    The `gh` CLI must be installed and authenticated (`gh auth login`) for steps 6–7 to run automatically. If it is not found, the tag is still pushed and you can upload the zips manually from the GitHub releases page.

---

## Version Files

The version string lives in these places. `vortex-cli` writes all of them atomically:

| File | Field |
|------|-------|
| `Makefile` | `VERSION:=X.X.X` |
| `template.pros` | `"version": "X.X.X"` |
| `docs/installation.md` | `Vortex@X.X.X.zip` references |

The `depot` branch (`stable.json`) is also updated as part of the release flow.

The version in `template.pros` inside the zip is patched by a Python post-processing step in the `Makefile` `template` target, because the PROS CLI hardcodes `supported_kernels: ^4.2.2` regardless of flags. The patch rewrites it to `>=4.0.0` so the template installs on any PROS 4.x kernel.

---

## Branch Structure

| Branch | Purpose |
|--------|---------|
| `dev` | Active development. All work and PRs go here. |
| `stable` | Last released tag. Never push to this directly. |
| `depot` | Contains only `stable.json` — the PROS template depot index. |

Docs are deployed to GitHub Pages automatically from `stable` via the `.github/workflows/docs.yml` action whenever a release is pushed.
