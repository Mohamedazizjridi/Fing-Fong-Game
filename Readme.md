# 🏓 Pong Game - C++ OOP & Design Patterns


Game.gif
A modern Pong game showcasing **Object-Oriented Programming** and **Design Patterns** in C++.

## 🎮 Features

- Classic Pong gameplay with AI opponent
- Menu system (Start, Pause, Game Over)
- Smooth 60 FPS performance
- Clean C++ code with modern practices

## 🏗️ Project Structure

```
Game/
├── main.cpp          # Entry point & game loop
├── game.cpp          # Game logic & classes
├── Makefile          # Build configuration
├── main              # Executable
└── *.dll             # Windows libraries
```

## 🧩 OOP Concepts Demonstrated

### Classes & Inheritance

```cpp
class GameObject {
public:
    virtual void update() = 0;
    virtual void draw() = 0;
};

class Ball : public GameObject {
    // Ball physics and movement
};

class Paddle : public GameObject {
    // Player paddle
};

class CPUPaddle : public Paddle {
    // AI opponent (inherits from Paddle)
};
```

### Key OOP Principles

- ✅ **Encapsulation**: Private data, public methods
- ✅ **Inheritance**: CPUPaddle extends Paddle
- ✅ **Polymorphism**: Virtual functions, method overriding
- ✅ **Abstraction**: GameObject base class

## 🎨 Design Patterns Used

### 1. State Pattern

```cpp
enum GameState { MENU, PLAYING, PAUSED, GAME_OVER };
// Different behavior for each game state
```

### 2. Inheritance Pattern

```cpp
class CPUPaddle : public Paddle {
    void update() override {
        // AI-specific behavior
    }
};
```

### 3. Composition Pattern

```cpp
class Game {
    Ball ball;
    Paddle player;
    CPUPaddle cpu;
    // Game contains these objects
};
```

## 🚀 Quick Start

### Build & Run

```bash
# Clone the repo
git clone <your-repo-url>
cd Game

# Build
make

# Run
./main
```

### Controls

- ↑↓ Arrow Keys: Move paddle
- Enter: Select menu options
- Space: Pause/Resume

## 🎯 What I Learned

### C++ Skills

- Class design and inheritance
- Virtual functions and polymorphism
- Memory management
- Real-time programming

### Problem Solving

- Game physics (ball movement, collision)
- AI logic (CPU paddle behavior)
- State management (menu, game, pause)
- Performance optimization (60 FPS)

### Software Design

- Clean code organization
- Design pattern implementation
- Object-oriented architecture
- Professional documentation

## 📊 Technical Details

- **Language**: C++
- **Graphics**: Raylib
- **Performance**: 60 FPS
- **Architecture**: Object-Oriented
- **Patterns**: State, Inheritance, Composition

## 🔧 Code Highlights

### Clean Class Design

```cpp
class Ball {
private:
    float x, y;           // Position
    int speedx, speedy;   // Velocity
    int radius;           // Size

public:
    void update();        // Move ball
    void draw();          // Render ball
    void resetball();     // Reset position
};
```

### Smart AI Implementation

```cpp
void CPUPaddle::update(int ball_y) {
    if (y + height/2 > ball_y) {
        y -= speed;  // Move up
    } else {
        y += speed;  // Move down
    }
}
```

## 🎓 Why This Matters

This project demonstrates:

- **Industrial C++ skills** needed for software engineering
- **Object-oriented thinking** for complex applications  
- **Design patterns** used in professional development
- **Problem-solving** with clean, maintainable code

Perfect for showcasing C++ expertise to employers like **Siemens**, **Autodesk**, or any tech company requiring strong OOP skills.

## 📞 Contact

- **GitHub**: [@yourusername](https://github.com/yourusername)
- **Email**: your.email@example.com

---

⭐ **Star if you found this helpful!** | 🍴 **Fork to explore the code**
