# 31 Days of C++ & Raylib

![C++](https://img.shields.io/badge/C++-17-blue)
![CMake](https://img.shields.io/badge/CMake-3.20+-green)
![Raylib](https://img.shields.io/badge/Raylib-5.0-orange)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey)

A personal challenge:  
Learning modern C++ through game development using raylib.

---

## 🚀 About This Project

This repository documents my 31-day journey of learning C++ by building small games from scratch.

The goal is not to follow tutorials blindly, but to deeply understand:
- how game loops work
- how rendering pipelines function
- how C++ manages memory
- how game architecture evolves over time

Each game increases in complexity.

---

# 🎮 Game 1: Pong (Day 1–7)

## Day 1 – Window & Game Loop

### Implemented:
- CMake project setup
- raylib integration via FetchContent
- Basic game loop using `while`
- Window 800x600
- FPS limit (120)
- Drawing rectangle on screen

### Concepts Learned:
- `int`
- `while` loop
- Boolean logic (`!`)
- Game loop structure
- FPS control with `SetTargetFPS`
- Coordinate system (top-left origin)
- Position as center vs corner

## Day 2 – Player Movement & Delta Time

### Implemented:
- Player paddle movement (W/S)
- Movement independent from FPS using delta time
- Paddle speed defined in pixels per second
- Screen boundary clamping
- Removed magic numbers using `const` variables

### Concepts Learned:
- `if` conditions
- Modifying variables (`+=`, `-=`)
- `GetFrameTime()` and delta time
- Frame-rate independent movement
- Variable scope (state must live outside the game loop)

## Day 3 – Second Paddle & Simple AI

### Implemented:
- Second paddle on the right side
- Simple AI that follows the ball (using paddle center)
- Dead zone to prevent constant micro-movement
- Screen boundary clamping for AI paddle

### Concepts Learned:
- Multiple variables describing one game object (x, y, width, height, speed)
- Comparing values to drive behavior
- Cleaner logic using `else if`

## Day 4 – Ball Physics & Collisions

### Implemented:
- Ball movement using velocity (`ballVelX`, `ballVelY`)
- Frame-rate independent motion using delta time
- Bounce from top and bottom screen edges
- Collision detection with paddles using `CheckCollisionCircleRec`
- Direction-aware collision handling (prevent sticky bounce)
- Ball reset to center after leaving screen

### Concepts Learned:
- Position update: `position += velocity * deltaTime`
- Inverting direction using `velocity *= -1`
- Circle vs Rectangle collision detection
- Using structs from raylib (`Rectangle`, `Vector2`)
- Preventing repeated collision triggers using direction checks

---

More updates coming daily 🚀