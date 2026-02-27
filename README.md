# 31 Days of C++ & Raylib

![C++](https://img.shields.io/badge/C++-17-blue)
![CMake](https://img.shields.io/badge/CMake-3.20+-green)
![Raylib](https://img.shields.io/badge/Raylib-5.0-orange)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey)

A personal challenge: learning C++ by building games with raylib. I want to understand how things work under the hood, not just copy from tutorials – game loop, rendering, memory in C++, how complexity grows. Each game a bit harder than the last.

---

## About this project

Notes from 31 days – small games from scratch. Focus on:
- how the game loop works
- how the rendering pipeline fits together
- how C++ handles memory
- how architecture changes as the project grows

---

# Game 1: Pong (Day 1–7)

## Day 1 – Window and game loop

**Done:** CMake setup, raylib via FetchContent, basic `while` loop, 800x600 window, 120 FPS, drawing a rectangle.

**Learned:** `int`, `while` loop, `!` in conditions, game loop structure, `SetTargetFPS`, coordinate system (top-left origin), position as center vs corner.

## Day 2 – Player movement and delta time

### Implemented:
- Player paddle movement (W/S)
- Movement independent from FPS using delta time
- Paddle speed in pixels per second
- Clamping to screen edges
- Constants instead of magic numbers

### Concepts Learned:
- `if`, `+=` / `-=`
- `GetFrameTime()` and delta time
- Frame-rate independent movement
- State variables need to live outside the loop

## Day 3 – Second paddle and simple AI

Second paddle on the right. AI chases the ball (paddle center), with a dead zone so it doesn’t jitter. Clamp AI paddle to screen. More variables per object (x, y, width, height, speed), comparisons in conditions, `else if` for clearer logic.

## Day 4 – Ball physics and collisions

**Done:** Ball movement via `ballVelX`/`ballVelY`, delta time, bounce off top and bottom, collision with paddles (`CheckCollisionCircleRec`), direction check to avoid sticky bounce, ball reset to center when it leaves the screen.

**Learned:** `position += velocity * dt`, `velocity *= -1`, circle–rectangle collision, raylib `Rectangle`/`Vector2`, avoiding repeated collision triggers.

## Day 5 – Scoring and AI imperfection

Score for player and AI when ball leaves the screen, drawing with `DrawText`/`TextFormat`. AI gets a random offset so it’s beatable. Fixed collision (no sticking). Solved: magic numbers → constants, ball sticking to paddle.

**Concepts Learned:** `++`, formatting numbers for display, separating game logic from AI “perception”, balancing with parameters.

## Day 6 – Game states and centered text

`enum class GameState` (MENU, PLAYING, GAMEOVER), start on ENTER. Ball movement, collisions and scoring only in PLAYING. Update vs draw separation. Text centered with `MeasureText` instead of hardcoded offsets.

**Learned:** `enum class`, `::`, state-driven flow, update vs render, UI positioning from text width.

## Day 7 – Win condition, game over, restart

Win at first to 5 points, transition to GAMEOVER, show who won. Restart on ENTER – full reset (scores, ball, paddles, AI offset). Transitions: MENU → PLAYING → GAMEOVER → MENU.

**Concepts Learned:** Full gameplay lifecycle, safe reset of state, predictable state transitions.

---

## Technical – Pong in short

Single loop `while (!WindowShouldClose())`, movement on delta time. State machine with `enum class GameState`; gameplay logic only in PLAYING, UI depends on state. Update: input, movement, collisions, scoring. Render: all `Draw*` inside `BeginDrawing()`/`EndDrawing()`. Circle–rect collision, direction-aware bounce to avoid sticking. Score on ball exit + reset to center. Text centered via `MeasureText`.

---

Updates as I go.
