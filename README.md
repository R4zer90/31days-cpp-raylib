# 31 Days of C++ & Raylib

![C++](https://img.shields.io/badge/C++-17-blue)
![CMake](https://img.shields.io/badge/CMake-3.20+-green)
![Raylib](https://img.shields.io/badge/Raylib-5.0-orange)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey)

Learning C++ by building small games with raylib.
Focus: game loop, rendering, memory, clean structure, increasing complexity.

---

## Repository Structure

31days-cpp-raylib/
- PongRaylib/
- SpaceShooter/
- Platformer/
- DungeonCrawler/
- FinalProject/

---

# Game: Pong (Day 1–7)

## Overview

Classic Pong clone built from scratch.
Goal: understand game loop, movement, collisions, state machine.

---

## Implemented

- Window initialization with CMake + FetchContent (raylib)
- Game loop (`while (!WindowShouldClose())`)
- Player paddle movement (delta time)
- AI paddle with dead zone
- Ball physics and bounce
- Collision detection (circle vs rectangle)
- Score system
- Game states (MENU / PLAYING / GAMEOVER)
- Restart logic

---

## Concepts

### C++
- `int`, `float`
- `if / else if`
- `+=`, `-=`
- `enum class`
- separation of logic and rendering
- constants instead of magic numbers

### Raylib
- `InitWindow`
- `BeginDrawing` / `EndDrawing`
- `GetFrameTime`
- `CheckCollisionCircleRec`
- `DrawText`
- `MeasureText`

---

## Architecture Notes

- Single game loop
- Update and Draw separated
- State-driven flow using `enum class`
- Delta time movement
- Center-based positioning

---

## Technical Summary

Movement based on `position += velocity * dt`.
Bounce implemented via `velocity *= -1`.
Game logic executed only in PLAYING state.
UI positioned dynamically (no hardcoded offsets).

---

# Game: Space Shooter (Day 8–...)

## Overview

Top-down space shooter prototype.
Goal: practice functions with parameters, delta time movement, and reusable clamp logic.

---

## Implemented

### Day 8
- Player ship as triangle (center-based position)
- Horizontal movement (A/D + arrow keys)
- Delta time movement
- Custom `clamp` function
- Screen boundary restriction

### Day 9
- Introduced `struct Bullet`
- Added `std::vector<Bullet>` for dynamic bullets
- Implemented shooting with SPACE key
- Frame-independent bullet movement
- Implemented erase–remove idiom with lambda
- Automatic cleanup when bullets leave screen

### Day 10
- Created `struct Enemy` with x, y and alive flag
- Stored enemies in `std::vector`
- Generated a row of enemies using a for loop
- Rendered enemies conditionally based on alive state

### Day 11
- Implemented classic Space Invaders style movement
- Added shared horizontal direction for enemy wave
- Edge detection using boundary checks (<= / >=)
- Direction reversal with vertical drop
- Introduced wave-based movement logic

### Day 12
- Implemented bullet–enemy collision (rectangle approximation)
- Added nested iteration (bullets × enemies)
- Introduced `alive` lifecycle flag for bullets
- Removed bullets and enemies using erase–remove idiom
- Prevented multi-kill per bullet using `break`

### Day 13
- Added multi-row enemy formation (3x8 grid)
- Implemented zigzag row offset using modulo operator
- Added wave respawn when enemies are cleared
- Implemented player–enemy collision detection (Game Over)
- Added restart system (ENTER resets game state)
- Integrated basic game state control using `gameOver` flag

---

## Concepts

### C++
- Functions with parameters and return value
- Custom clamp implementation
- Frame-independent movement
- Float vs int division awareness
- `std::vector`
- Range-based for loop
- Lambda expressions
- `std::remove_if` and erase–remove idiom
- `struct` for data modeling
- `std::vector<CustomType>`
- Object grouping and data abstraction
- Boolean flag for state detection
- Conditional direction reversal
- Avoiding float equality comparison (`<= / >=` instead of `==`)
- Nested loops (collision detection)
- Lifecycle management using flags
- Advanced erase–remove usage
- Iterator safety and post-loop cleanup
- 2D grid generation using nested loops (rows × columns)
- Modulo operator for pattern-based positioning
- Basic game state management using boolean flags
- Controlled update flow (skip logic when gameOver)

### Architecture
- Update vs Draw separation
- Center-based object positioning
- Reusable helper function (`clamp`)
- Wave-level shared behavior (direction not stored per enemy)
- Post-loop decision execution pattern

### Raylib
- `DrawTriangle`
- `DrawCircle`
- `DrawRectangle`
- `IsKeyDown`
- `IsKeyPressed`
- `GetFrameTime`

---

## Technical Summary

Enemies are represented using a custom struct and stored inside a std::vector.
A procedural row of enemies is generated using a loop and calculated spacing.
Bullets and enemies are updated independently and rendered via iteration.
Dead objects are filtered using logical state flags.
Enemy movement is controlled at wave level using a shared direction variable.
Boundary detection sets a flag that triggers vertical drop and direction reversal.
Decisions are executed after iteration to maintain deterministic frame logic.
Bullet and enemy collisions are resolved using axis-aligned bounding box overlap checks.
Objects are first marked as inactive and then physically removed using the erase–remove idiom.
Collision resolution is deterministic due to post-iteration cleanup and controlled loop breaks.
Enemy formations are generated using a 2D grid system with optional row offset.
Game state is controlled via a `gameOver` flag that blocks update logic while preserving render flow.
Wave respawning reuses the same generation logic, creating a continuous gameplay loop.

---

More updates as the project grows.