# FIL DER FER

<br>

[![Watch NOW](https://github.com/RafaelyRezende/FilDeFer/blob/main/.archieved/42fdf.png)](https://github.com/RafaelyRezende/FilDeFer/blob/main/.archieved/t2_3.mp4)

<br>

## PROJECT OVERVIEW

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

<br>

## USAGE

### Linux

Install required dependencies for MiniLibX.
```shell
sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev

```

Clone the repository and run make.
```shell
git clone https://github.com/RafaelyRezende/FilDeFer.git && cd FilDeFer && make

```

```shell
./fdf test_maps/42.fdf

```

<br>

## SAMPLES

*PYRA MAP*

<div align="middle">
  <a href="https://github.com/RafaelyRezende/FilDeFer" target="_blank">
    <img src="https://github.com/RafaelyRezende/FilDeFer/blob/main/.archieved/pyra.png" width="640">
  </a>
</div>

*AMAZON RAINFOREST*

<div align="middle">
  <a href="https://github.com/RafaelyRezende/FilDeFer" target="_blank">
    <img src="https://github.com/RafaelyRezende/FilDeFer/blob/main/.archieved/amazonfdf.png" width="640">
  </a>
</div>
