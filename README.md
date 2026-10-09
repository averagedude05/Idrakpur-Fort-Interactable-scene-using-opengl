# Idrakpur Fort - 2D Interactive Graphics Scene

A 2D computer graphics simulation of the historical **Idrakpur Fort** created using **C++** and **OpenGL / GLUT**. This project combines cultural heritage preservation with interactive graphics concepts including dynamic animations, day/night transitions, weather effects, and background sound.

---

## 📸 Screenshots

| Day Mode | Night Mode |
| :---: | :---: |
| <img width="600" alt="Day Mode" src="https://github.com/user-attachments/assets/57f762b3-29ce-4950-ad3e-724704bc6b9d" /> | <img width="600" alt="Night Mode" src="https://github.com/user-attachments/assets/0a9072b6-ff58-4cec-b392-1b5c09077579" /> |

| Rain Effect (Night) | Rain Effect (Day) |
| :---: | :---: |
| <img width="600" alt="Rain Night" src="https://github.com/user-attachments/assets/72a9d94a-6260-43e6-a17d-98d131bb9cf6" /> | <img width="600" alt="Rain Day" src="https://github.com/user-attachments/assets/fd20f14e-093b-4b5b-a340-347898801899" /> |

---

## ✨ Features

* **Architectural Modeling**: Recreation of Idrakpur Fort body, battlements, and windows using geometric primitives (quadrilaterals, polygons, lines, and circles).
* **Day & Night Toggle**: Dynamic scene color shifts, sun/moon toggling, and illuminated windows during night mode.
* **Dynamic Animations**:
  * Continuous cloud movement
  * Horizontally moving car and boat
  * Animated falling rain particles
* **Audio Integration**: Background sound using Windows `PlaySound` API.

---

## 💡 Core Computer Graphics Concepts

* **OpenGL Primitives** (`GL_QUADS`, `GL_POLYGON`, `GL_LINES`, `GL_TRIANGLES`)
* **2D Transformations** (Translation & Object Positioning)
* **Timer Functions** (Animation updates using `glutTimerFunc`)
* **Coordinate Systems & Color Management**

---

## 🛠️ Built With

* **Language**: C++
* **Graphics Library**: OpenGL / GLUT
* **Platform**: Windows (using `winmm.lib` for audio)

---

## ⚙️ How to Run

### Prerequisites
* Code::Blocks, Visual Studio, or GCC configured with OpenGL/GLUT libraries.
* Windows OS (for `PlaySound` support).

### Compilation Instructions (GCC / MinGW)
```bash
g++ main.cpp -o IdrakpurFort -lfreeglut -lopengl32 -lglu32 -lwinmm
./IdrakpurFort
