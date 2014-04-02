pathtracer 
==========

version 0.9.1

usage
-----

This project uses cmake, to build and run it you can either do:

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

scenes 
------

### example

```
# cornell box scene
camera p(0.0, 2.5, -4.0) la(0.0, 2.5, 0.0) res(640, 480)

# light sphere 
object:s p(1.0, 3.5, 3.5) e(2.5, 2.5, 2.5) c(1.0, 1.0, 1.0) material:d

# spheres
object:s p(2.0, 1.0, 0.0) e(0.0, 0.0, 0.0) c(1.0, 1.0, 1.0) material:s
object:s p(0.0, 3.5, 0.0) e(0.0, 0.0, 0.0) c(0.95, 0.67, 0.68) material:r
object:s p(-2.9, 1.0, 2.0) e(0.0, 0.0, 0.0) c(1.0, 1.0, 1.0) material:r

# floor plane
object:p p(0.0, 0.0, 0.0) e(0.0, 0.0, 0.0) c(0.88, 0.85, 0.78) material:d

# meshes / walls
mesh:obj/plane1.obj p(0.0, 0.0, 0.0) e(0.0, 0.0, 0.0) c(1.0, 1.0, 1.0) material:d
mesh:obj/plane2.obj p(0.0, 0.0, 0.0) e(0.0, 0.0, 0.0) c(0.41, 0.21, 0.35) material:d
mesh:obj/plane3.obj p(0.0, 0.0, 0.0) e(0.0, 0.0, 0.0) c(0.81, 0.29, 0.0) material:d
````

results
-------

![example](http://karim.naaji.fr/images/path_tracing3.png)

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
