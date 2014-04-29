pathtracer 
==========

version 0.9.2

dependencies
------------

This project uses cmake.

#### mac osx

Download and install [CMake](http://www.cmake.org/cmake/resources/software.html)
if you don't already have it. 
To simplify installation you may use [Homebrew](http://brew.sh):

```bash
brew install cmake
```

#### linux (ubuntu)

```bash
sudo apt-get install cmake
```

build and run
-------------

To build and run it you can either do:

```bash
$ cd build
$ ./run.sh scene_file_name samples_per_pixel
```

which will give you more information about the time it took to render the image, and save a png image into a images/ subfolder with the standard name scene-hour-sppx.png, or: 

```bash
$ cd build
$ cmake .. && make
$ ./pathtracer.out scenes/scene_file_name samples_per_pixel
```
which will only output an image.ppm file.

usage
-----

#### scenes 

To define a camera, you can provide a lens size (for depth of field) and the focus plane distance, if you don't, the rendering will be without depth of field (pinhole camera). For the other parameters, **p** is the position, **la** is the _look at_ position, and **res** defines the resolution of the film of the camera:

```
camera lens(0.08) focus(1.0) p(0.0, 2.5, -4.0) la(0.0, 2.5, 0.0) res(640, 480)
```

To define basic objects (planes & spheres), the object can be either a sphere with **s** or a plane with **p**, next **p** is the position of this object, **e** is its emission, **c** is its color, the material can be **s**, **d** or **r** for respectively _specular_, _diffuse_ or _refractive_ material.

```
object:s|p p(2.0, 1.0, 0.0) e(0.0, 0.0, 0.0) c(1.0, 1.0, 1.0) material:s|d|r
```

For meshes, you first have to define its _.obj_ file location, and the last parameters are the same as basic objects.

```
mesh:obj/plane1.obj p(0.0, 0.0, 0.0) e(0.0, 0.0, 0.0) c(1.0, 1.0, 1.0) material:s|d|r
```

#### example

```bash
# cornell box scene
camera lens(0.08) focus(1.0) p(0.0, 2.5, -4.0) la(0.0, 2.5, 0.0) res(640, 480)

# light sphere 
object:s p(1.0, 3.5, 3.5) e(2.5, 2.5, 2.5) c(1.0, 1.0, 1.0) material:d

# spheres
object:s p(2.0, 1.0, 0.0) e(0.0, 0.0, 0.0) c(1.0, 1.0, 1.0) material:s
object:s p(-2.9, 1.0, 2.0) e(0.0, 0.0, 0.0) c(1.0, 1.0, 1.0) material:r

# floor plane
object:p p(0.0, 0.0, 0.0) e(0.0, 0.0, 0.0) c(0.88, 0.85, 0.78) material:d

# meshes / walls
mesh:obj/plane1.obj p(0.0, 0.0, 0.0) e(0.0, 0.0, 0.0) c(1.0, 1.0, 1.0) material:d
mesh:obj/plane2.obj p(0.0, 0.0, 0.0) e(0.0, 0.0, 0.0) c(0.41, 0.21, 0.35) material:d
mesh:obj/plane3.obj p(0.0, 0.0, 0.0) e(0.0, 0.0, 0.0) c(0.81, 0.29, 0.0) material:d
```

#### results

![example](http://karim.naaji.fr/images/path_tracing3.png)

First attempts on depth of field (there's still some artifacts):

![example](http://karim.naaji.fr/images/path_tracing4.png)

licence
======= 

      Copyright (C) 2014 Naaji Karim (karim.naaji@gmail.com)
      
      This program is free software: you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation, either version 3 of the License, or
      (at your option) any later version.
      
      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      GNU General Public License for more details.
      
      You should have received a copy of the GNU General Public License
      along with this program.  If not, see <http://www.gnu.org/licenses/>.
