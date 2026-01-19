# HeadClicker Game

A simple 3D game built with raylib and Lua scripting.

### 1. Lua Integration
Lua is used for enemy handling in the game

### 2. Sound effects
Some simple sound effects in the game

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

- **O Key**: Reload Lua scripts
- **R Key**: Respawn enemy
- **Left Click**: Fire weapon
- **Mouse**: Look around
- **WASD**: Move
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

## Notes

- The game uses raylib for graphics and audio
- Lua scripting allows runtime configuration
