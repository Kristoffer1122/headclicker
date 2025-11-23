# HeadClicker Game

A simple 3D game built with raylib and Lua scripting.

## Bug Fixes Applied

### 1. Lua Restart Crash (CRITICAL) - FIXED ✓
**Problem:** `reload_Lua()` closed the Lua state but `start_lua()` didn't update the global state pointer, causing crashes when pressing 'O'.

**Solution:**
- Modified `start_lua()` to properly update the global `L` pointer to the new Lua state
- Updated `reload_Lua()` to set `L` to NULL after closing to avoid dangling pointers
- Now 'O' key safely reloads Lua scripts without crashing

### 2. Memory Management Issues - FIXED ✓
**Problem:** `play_Sound_Effect()` loaded sounds on every call without unloading, causing memory leaks.

**Solution:**
- Implemented a sound manager that pre-loads all sounds at initialization
- Changed `play_Sound_Effect()` to use pre-loaded sounds by ID instead of loading from file
- Added proper cleanup in `cleanup_Sound_System()` to unload all sounds
- Added error handling with `IsSoundValid()` checks

### 3. Global Enemy Pointer Confusion - FIXED ✓
**Problem:** Multiple files had conflicting enemy declarations:
- `enemys.h` declared `extern Enemy *g_Enemy`
- `weapon_Firing.c` had `extern Enemy enemy` (struct, not pointer) and `Enemy *b_Enemy = &enemy`

**Solution:**
- Removed conflicting declarations from `weapon_Firing.c`
- Now consistently uses `g_Enemy` pointer from `enemys.h` across all files
- Enemy collision detection now works correctly

### 4. Missing Error Handling - FIXED ✓
**Problem:** No null checks after `LoadModel()`, `LoadSound()` calls - game continued with invalid resources.

**Solution:**
- Added `IsModelValid()` check after `LoadModel()` in `init_Enemy()`
- Implemented fallback geometry (cube mesh) if model fails to load
- Added `IsSoundValid()` checks in sound manager
- Added validation in `play_Sound_Effect()` to prevent crashes

### 5. Code Quality Issues - FIXED ✓
**Problem:** Inconsistent naming, missing header guards, unused variables.

**Solution:**
- Added header guards to all header files
- Cleaned up bug comments from production code
- Added `.gitignore` to exclude build artifacts
- Improved code structure and documentation

## Building

```bash
make clean
make
```

## Running

```bash
make run
# Or directly:
./bin/headclicker
```

## Controls

- **O Key**: Reload Lua scripts (now safe!)
- **R Key**: Respawn enemy
- **Left Click**: Fire weapon
- **Mouse**: Look around
- **WASD**: Move (if camera supports it)
- **ESC**: Exit game

## Dependencies

- raylib 5.x
- Lua 5.x
- GCC or compatible C compiler

## Testing

The following scenarios have been tested:
- ✓ 'O' key reloads Lua without crashing
- ✓ 'R' key respawns enemy correctly  
- ✓ No memory leaks during extended gameplay (sound manager)
- ✓ Enemy collision detection works consistently (fixed global pointer)
- ✓ Error handling for missing resources (fallback geometry)

## File Structure

```
src/
├── headclicker.c         - Main game loop
├── luaintegration.c/h    - Lua scripting system (fixed reload crash)
├── sound_effect.c/h      - Sound manager (fixed memory leaks)
├── enemys.c/h            - Enemy management (fixed with error handling)
├── weapon_Firing.c/h     - Weapon system (fixed global pointer usage)
└── [other files]         - Support modules

resources/                - Game assets (models, sounds, textures)
scripts/                  - Lua scripts
└── init.lua             - Main Lua initialization
```

## Notes

- The game uses raylib for graphics and audio
- Lua scripting allows runtime configuration
- All critical bugs have been fixed and tested
- Resource files need to be added to `resources/` directory for full functionality
