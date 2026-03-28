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

### Day 14
- Added audio device initialization and shutdown
- Loaded sound effects (shot, explosion, dead)
- Triggered SFX on shoot, hit, and game over events
- Added proper resource cleanup via UnloadSound
- Auto-copied assets folder to build output via CMake

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
- Resource lifetime awareness (load / use / unload)

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
- `InitAudioDevice`
- `LoadSound`
- `PlaySound`
- `UnloadSound`
- `CloseAudioDevice`

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

# Game: Platformer (Day 15–21)

## Overview

Simple 2D platformer project focused on object-oriented programming and class structure.

---

## Implemented

### Day 15
- Introduced Player class with private state (x, y, speed)
- Implemented constructor initialization
- Separated Update and Draw logic
- Added frame-independent horizontal movement
- Applied basic OOP encapsulation principles

### Day 16
- Added gravity system using vertical velocity
- Introduced `velocityY` variable for physics simulation
- Implemented frame-independent falling using delta time

### Day 17
- Added ground detection using `bool onGround`
- Implemented jump mechanic using negative vertical velocity
- Prevented mid-air jumping using ground state check

### Day 18
- Introduced 2D tilemap using int array (12x16)
- Implemented nested for-loops for map initialization and rendering
- Added basic tile rendering with grid-based positioning
- Implemented ground detection using tile under player
- Added Land() to snap player to tile top and reset vertical velocity

### Day 19
- Introduced `GameObject` base class
- Moved shared position (`x`, `y`) to base class
- Implemented inheritance (`Player : GameObject`)
- Removed duplicated position variables from Player
- Moved `GetX()` and `GetY()` getters to GameObject

### Day 20
- Added `Coin` gameplay object inheriting from `GameObject`
- Implemented coin rendering using `DrawRing`
- Added collected state system (`Collect()` / `IsCollected()`)
- Implemented player–coin collision using `CheckCollisionCircleRec`
- Added score system
- Added HUD displaying score using `DrawText`

### Day 21
- Replaced single Coin instance with `std::vector<Coin>` to support multiple collectibles
- Implemented range-based iteration over coins for update and rendering
- Added multi-coin collision detection with player
- Implemented level completion condition when all coins are collected
- Added centered "LEVEL COMPLETE" message using `MeasureText`

---

## Concepts

### C++
- `class`
- `private` vs `public`
- constructor definition outside class
- member functions (`Player::Update`)
- encapsulation basics
- `bool`
- inheritance (`class Derived : Base`)
- base class reuse
- `std::vector<ClassType>`
- range-based for loop with references (`for (auto& obj : container)`)

### Raylib
- `DrawRectangle`
- `IsKeyDown`
- `GetFrameTime`
- `DrawRing`
- `CheckCollisionCircleRec`
- `TextFormat`
- `MeasureText`

### Architecture
- Player owns its state and movement logic
- Main loop only orchestrates update/draw calls
- Center-based positioning approach
- shared base class for world objects (`GameObject`)
- object state control via boolean flags

## Technical Summary

Player physics is simulated using velocity and gravity applied each frame.
Tile-based ground detection checks the tile directly under the player and snaps the character to the tile surface when landing.
Gameplay objects share position data through a common `GameObject` base class.
Coins use a collected state flag and are removed visually after collision with the player.
Score is tracked globally and displayed via a simple HUD.

---

# Game: Dungeon Crawler (Day 22–...)

## Overview

Procedural dungeon crawler prototype focused on tilemaps, procedural generation, camera systems, and exploration.

Goal: learn grid-based world representation, random generation, tile-based rendering, camera handling, and collision against dungeon walls.

---

## Implemented

### Day 22
- Introduced dungeon tilemap using 2D array (40x40)
- Initialized dungeon grid with walls
- Implemented tile-based rendering system using TILE_SIZE
- Added dungeon centering using screen offset
- Implemented random room size generation
- Implemented random room position generation
- Added boundary-safe room placement with map margins
- Carved first procedural room into dungeon grid
- Rendered dungeon tiles based on map data

### Day 23
- Introduced `Room` struct describing dungeon room layout
- Implemented `std::vector<Room>` to store multiple generated rooms
- Added multi-room procedural generation
- Implemented room carving into dungeon grid
- Added corridor generation connecting sequential rooms
- Implemented simple L-shaped corridor algorithm
- Refactored dungeon system into `Map` class (`Map.h` / `Map.cpp`)
- Separated dungeon generation and rendering logic

### Day 24
- Implemented dungeon tile rendering through `Map::Draw`
- Introduced `Player` class for dungeon exploration
- Added WASD player movement using delta time
- Integrated player update and rendering into main game loop
- Refactored main loop to orchestrate Map and Player systems

### Day 25
- Introduced `Camera2D` for dungeon exploration
- Switched dungeon rendering from screen-space offset to world-space coordinates
- Implemented camera follow system centered on player position
- Added fullscreen 1920x1080 support
- Increased tile scale and expanded dungeon size to 80x80
- Added camera zoom for improved gameplay readability
- Implemented tile-based wall collision using `Map::IsWall`
- Added safe player spawn using first room center
- Implemented camera clamp to map boundaries
- Optimized rendering to draw only visible tiles inside camera view

### Day 26
- Introduced Enemy class representing hostile dungeon entities
- Implemented enemy rendering and position system
- Added `std::vector<Enemy>` for managing multiple enemies
- Implemented procedural enemy spawning inside dungeon rooms
- Excluded player spawn room from enemy generation
- Implemented enemy update loop integrated into main game loop
- Added detection range system for enemy AI
- Implemented player tracking behavior when inside detection range
- Added tile-based enemy collision using `Map::IsWall`
- Implemented axis-separated collision checks to prevent wall clipping

### Day 27
- Added player health system (HP / max HP)
- Implemented damage system with cooldown to prevent instant death
- Added enemy-to-player collision damage using circle collision
- Introduced player auto-attack system with configurable attack range
- Implemented attack cooldown system for controlled combat pacing
- Added enemy health and death state system
- Prevented dead enemies from updating and rendering
- Implemented basic combat loop (player ↔ enemy interaction)
- Added HUD displaying player health using `DrawText`
- Introduced simple visual attack feedback (attack radius indicator)

### Day 28
- Introduced player inventory system using `std::map`
- Implemented `AddItem` and `GetItemCount` methods
- Added basic HUD displaying inventory values (gold)
- Introduced loot system from enemies
- Refactored loot logic into Enemy class (`DropLoot`)
- Added loot state tracking to prevent duplicate drops
- Implemented cleanup of dead enemies using erase–remove idiom

### Day 29
- Introduced Item class for world pickups
- Implemented item spawning inside dungeon rooms
- Added `std::vector<Item>` for item management
- Implemented item rendering and collected state
- Added player–item collision detection
- Implemented item pickup system (inventory integration)
- Added support for multiple item types (gold, potion)
- Implemented healing system using potion items
- Added visual distinction between item types (color-based)
- Implemented cleanup of collected items using erase–remove idiom

### Day 30
- Implemented save system using file streams (`std::ofstream`, `std::ifstream`)
- Saved player state including position, health and gold
- Implemented load system restoring player state from file
- Added quick-save (F5) and quick-load (F9)
- Introduced basic text-based serialization format
- Implemented file open validation using `is_open()`
- Added setter methods for controlled state restoration (`SetHealth`, `SetItemCount`)
- Fixed inventory overwrite issue during load
- Added safe load behavior using fallback spawn position

### Day 31
- Implemented Game Over system triggered by player health reaching zero
- Blocked gameplay update logic when player is dead
- Added Game Over UI message
- Implemented restart system using R key
- Regenerated dungeon on restart
- Reset player state on restart
- Cleared and rebuilt enemy and item containers
- Reinitialized enemies and items from newly generated dungeon rooms
- Added restart instruction text for improved user experience
- Established full gameplay loop (play → death → restart)

---

## Concepts

### C++
- 2D arrays (`int dungeon[height][width]`)
- nested loops for grid traversal
- procedural generation basics
- random number generation
- grid coordinate systems
- `class` for world systems (`Map`)
- `struct` for simple data containers (`Room`)
- `std::vector<Room>` for dynamic room storage
- object composition (`Map` managing rooms and tiles)
- separation of generation and rendering logic
- getter/setter usage for controlled access to player position
- tile-based collision checks using world position to grid conversion
- visibility range calculation for partial map rendering
- `std::vector<Enemy>` for entity management
- simple enemy AI using distance detection
- axis-separated collision resolution
- basic combat system design
- cooldown systems (timers for actions)
- simple distance-based interaction (`sqrt`, vector math)
- entity state management (`alive`, `health`)
- associative containers (`std::map`)
- basic inventory system design
- item abstraction (`Item` class)
- string-based item identification
- container cleanup patterns for dynamic objects
- file streams (`std::ofstream`, `std::ifstream`)
- basic serialization and deserialization
- persistent state saving and loading
- setter methods for controlled state restoration
- state-based flow control using boolean flags
- reinitialization of objects through constructor reset
- clearing and rebuilding dynamic containers

### Raylib
- `DrawRectangle`
- `GetRandomValue`
- tile-based rendering
- grid → screen coordinate conversion
- `DrawCircle`
- player input using `IsKeyDown`
- `Camera2D`
- `BeginMode2D` / `EndMode2D`
- camera zoom and target tracking
- fullscreen mode with `ToggleFullscreen`
- `CheckCollisionCircles`
- `DrawCircleLines`
- `CheckCollisionCircles` (player–item interaction)
- `IsKeyPressed`
- `DrawText`
- `TextFormat`
- screen-space UI rendering outside `BeginMode2D`

---

## Architecture

- Dungeon stored as tile grid
- `1` represents wall
- `0` represents floor
- Room generation modifies tilemap data
- Rendering iterates through grid and draws tiles based on state
- Map system responsible for dungeon generation and rendering
- Player entity updated independently from world generation
- Main loop orchestrates world update and rendering
- Save system separated into dedicated `SaveSystem` module
- Player state persistence handled externally through getters and setters
- Update logic gated by game state (`isGameOver`)
- Rendering continues even when gameplay update is blocked
- Restart system rebuilds dungeon, enemies and items from procedural source data
- Dynamic world objects managed through `std::vector` containers
- Gameplay loop structured around exploration, combat, death and restart

---

## Technical Summary

Dungeon generation starts by filling the map with walls.
Random rectangular rooms are generated with randomized width, height and position.
Rooms are stored in a vector and carved into the dungeon grid.
Each room is connected to the next one using an L-shaped corridor.
Rendering converts grid coordinates into world coordinates using TILE_SIZE.
Player movement uses delta-time based input handling and is rendered independently from the dungeon system.
Camera-based rendering converts the dungeon into a scrolling world view centered on the player.
Tile collision is resolved by converting world coordinates into grid coordinates and querying wall data through the Map system.
Player spawn is derived from procedural room data to guarantee a valid floor position.
Rendering performance is improved by drawing only tiles visible inside the current camera bounds.
Enemy entities are procedurally spawned in dungeon rooms excluding the player spawn room.
Enemies detect the player within a configurable detection range and move toward the player using normalized direction vectors.
Movement collision is resolved using axis-separated tile checks against the dungeon grid.
Player combat system introduces bidirectional interaction between player and enemies.
Damage is controlled using cooldown timers to avoid frame-based instant depletion.
Enemy entities maintain health and alive state, allowing for controlled removal from gameplay.
Simple distance-based attack system enables auto-attack behavior within defined range.
HUD provides real-time feedback of player state.
Item system introduces collectible objects into the dungeon world.
Items are represented as entities with position, type and amount.
Player interaction is handled via collision detection, triggering inventory updates or gameplay effects.
Different item types enable extensible gameplay systems such as healing and resource collection.
Collected items are removed from the game world using erase–remove idiom for efficient memory management.
Save system persists selected player state using a simple text file format.
Load system restores saved values in a fixed order and applies them through setter methods.
Game Over state blocks update logic while preserving rendering and UI feedback.
Restart logic regenerates the dungeon and rebuilds gameplay entities, creating a complete gameplay loop.
