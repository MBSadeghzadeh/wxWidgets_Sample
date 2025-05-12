# wxWidgets OpenGL Sample

This is a sample desktop application demonstrating integration of **wxWidgets** with **OpenGL** using `wxGLCanvas`. It provides a basic UI layout with interactive rendering.

---

## 🛠️ Build Environment

This project was tested with the following tools:

- **Visual Studio 2022**
- **MSBuild** 17.12.12+1cce77968 (for .NET Framework)
- **CMake** 4.0.2
- **wxWidgets** 3.2.8
- **Windows 11**

---

## 🔧 Build Instructions

1. **Build and install wxWidgets**:
   - Clone the wxWidgets source.
   - Use **CMake** with the **Visual Studio 2022** generator.
   - Install it to:  
     `C:\Program Files\wxWidgets`

2. **Build this sample project**:
   - Open a terminal and navigate to the project root.
   - Run the following commands:

     ```bash
     cmake -S . -B build
     cmake --build build --config Release
     ```

3. **Run the app**:

   ```bash
   build/Release/MyWxApp.exe
