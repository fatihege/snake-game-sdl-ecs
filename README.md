# 🐍 SDL Snake Game

This is a **Snake Game** implemented using **SDL2** and the **Entity-Component-System (ECS)** pattern in **C++20**. The project is structured to be modular, scalable, and easy to extend.

## 📌 Features

- 🕹️ **Entity-Component-System (ECS)** architecture for better scalability
- 🎨 **SDL2 Rendering** for smooth graphics
- 🎮 **Keyboard Controls** for movement
- 🐍 **Snake Growth Mechanic**
- 🍎 **Food Spawning and Collision Detection**
- 🔄 **Game Loop Optimization**

---

## 🛠️ Installation & Setup

### **1. Install Dependencies**

Ensure you have the following installed:

- C++20-compatible compiler (e.g., GCC 10+, Clang, MSVC)
- CMake (3.30+ recommended)
- SDL2, SDL2-Renderer, SDL2-Image, and additional SDL2 modules (`libsdl2-dev`, `libsdl2-image-dev`, `libsdl2-ttf-dev`, `SDL2.dll`, `SDL2_image.dll`, etc. depending on OS)

#### **Ubuntu / Debian**

```bash
sudo apt update && sudo apt install -y g++ cmake libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
```

#### **Windows (vcpkg)**

```powershell
vcpkg install sdl2 sdl2-image sdl2-ttf
```

#### **MacOS (Homebrew)**

```bash
brew install sdl2 sdl2_image sdl2_ttf
```

### **2. Clone the Repository**

```bash
git clone https://github.com/fatihege/snake-game-sdl-ecs.git
cd snake-game-sdl-ecs
```

### **3. Build the Project**

```bash
mkdir build && cd build
cmake ..
make
```

### **4. Run the Game**

```bash
./snake_game_sdl_ecs
```

---

## 🎮 Controls

| Key               | Action     |
|-------------------| ---------- |
| `W` `Arrow Up`    | Move Up    |
| `S` `Arrow Down`  | Move Down  |
| `D` `Arrow Left`  | Move Left  |
| `A` `Arrow Right` | Move Right |
| `Esc`             | Quit Game  |

---

## 📂 Project Structure

```
/snake-game-sdl-ecs
│── /src
│   ├── main.cpp
│   ├── Game.cpp
│   ├── Game.h
│   ├── /core
│   │   ├── ECS.h
│   │   ├── EntityManager.cpp
│   │   ├── EntityManager.h
│   │   ├── Entity.cpp
│   │   ├── Entity.h
│   │   ├── Component.h
│   │   ├── System.h
│   ├── /components
│   │   ├── TransformComponent.h
│   │   ├── RenderComponent.h
│   │   ├── SnakeComponent.h
│   │   ├── FoodComponent.h
│   ├── /systems
│   │   ├── RenderSystem.cpp
│   │   ├── RenderSystem.h
│   │   ├── MovementSystem.cpp
│   │   ├── MovementSystem.h
│   │   ├── CollisionSystem.cpp
│   │   ├── CollisionSystem.h
│── /assets
│── CMakeLists.txt
│── README.md
```

---

## 🚀 Future Improvements

- 🔄 **AI-controlled snake** for a single-player challenge mode
- 🌎 **Multiplayer support** using networking
- 🎨 **Better visuals** with animations and textures
- 📊 **Score tracking & leaderboards**

---

## 💡 Contributing

Feel free to submit issues or pull requests to improve this project! If you find a bug or have an idea, open an issue in the GitHub repository.

---

## 📜 License

This project is licensed under the **MIT License**. See [LICENSE](LICENSE) for details.

---

### 🎯 Made with ❤️ using C++20 and SDL2 🚀

