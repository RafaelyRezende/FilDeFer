# Fil De Fer
<br>

![Grade](https://img.shields.io/badge/Grade-125%25-brightgreen)
![Bonus](https://img.shields.io/badge/Bonus-Complete-brightgreen)
![42 Project](https://img.shields.io/badge/42_Project-FdF-00babc?)
![Language](https://img.shields.io/badge/Language-C-blue)

## Project Demo

<video src="https://github.com/user-attachments/assets/a5653a9f-510b-4e1e-80bb-c02e1d506edd" controls>
  Your browser does not support the video tag.
</video>

## Project Overview

This project is about creating a **wireframe model representation of a 3D landscape** by linking points (x, y, z) via line segments (edges). These edges are constructed though Bresenham's line algorithm for continuity and draw to the screen with a isometric view which make it feel an 3D object in space.

**Main objectives**

- Represent the object statically;
- Add rotation around an axis;
- Add translation across the plane;
- Add height increase and decrease;
- Add zoom in and zoom out;
- Add top view angle;
- Draw lines with a color gradient;

**Future features**

- Rotation around arbitrary axis;
- Object centralization when changing perspective or zoom;
- GUI sidebar;
- Toggle buttons;
- Interactive mode with mouse;

## Features

### Mandatory Part

* **Map Parsing:** Reads and parses `.fdf` files, which define coordinates (x, y) and altitude (z).
* **Isometric Projection:** Renders the wireframe model using an isometric projection.
* **Graphic Management:** Displays the image in a window using the MiniLibX library.
* **Event Handling:** The program must close the window and quit cleanly when the `ESC` key is pressed or when the window's frame cross is clicked.

### Bonus Part

This implementation includes several bonus features to enhance the model viewer:
* **Additional Projections:** A parallel (top-down) view is included.
* **Zoom:** Users can zoom in and out of the model.
* **Translation:** The model can be translated (moved) across the X and Y axes.
* **Rotation:** The model can be rotated around its central axes.
* **Altitude Control:** The Z-axis scaling (altitude) can be increased or decreased dynamically.
* **Color Gradient:** Lines are drawn with a color gradient based on their altitude.

## Usage & Compilation

### Prerequisites (Linux)

The MiniLibX library requires several dependencies. You can install them using:
```shell
sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev
````

This project also uses `libft`, which is included as a submodule and compiled automatically by the `Makefile`.

### Compilation

Clone the repository and compile the project using `make`:

```shell
git clone [https://github.com/RafaelyRezende/FilDeFer.git](https://github.com/RafaelyRezende/FilDeFer.git)
cd FilDeFer
make bonus
```

**Makefile Rules**:

  * `all`: Compiles the mandatory part (`fdf`).
  * `bonus`: Compiles the bonus part (`fdf`).
  * `clean`: Removes object files.
  * `fclean`: Removes object files and the final executable.
  * `re`: Cleans and recompiles the project.

### How to Run

Execute the program by passing a valid `.fdf` map file as an argument:

```shell
./fdf test_maps/42.fdf
```

## Map Samples


* **PYRA MAP**


<div align="middle">
  <a href="https://github.com/RafaelyRezende/FilDeFer" target="_blank">
    <img src="https://github.com/RafaelyRezende/FilDeFer/blob/main/.archieved/pyra.png" width="640">
  </a>
</div>


* **AMAZON RAINFOREST**


<div align="middle">
  <a href="https://github.com/RafaelyRezende/FilDeFer" target="_blank">
    <img src="https://github.com/RafaelyRezende/FilDeFer/blob/main/.archieved/amazonfdf.png" width="640">
  </a>
</div>

*NOTE:* Custom map files generated using [this](https://github.com/jgigault/42MapGenerator) repository, authored by Jean-Michel Gigault.

## Authorized Functions

This project was completed using only the functions authorized by the subject:

  * `open`
  * `close`
  * `read`
  * `write`
  * `malloc`
  * `free`
  * `perror`
  * `strerror`
  * `exit`
  * `gettimeofday`
  * All functions from the **Math Library** (`-lm`)
  * All functions from the **MiniLibX** library

<!-- end list -->
