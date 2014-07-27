version 0.9.2
# test scene
camera lens(0.1) focus(2.0) p(-1.0, 1.5, -4.0) la(0.0, 1.0, 0.0) res(640, 480)

# spheres
object:s p(0.0, 2.5,  3.5) e(3.5, 3.5, 3.5) c(1.0, 1.0, 1.0) material:d
object:s p(0.0, 1.0, -1.0) e(0.0, 0.0, 0.0) c(1.0, 1.0, 1.0) material:r

# floor plane
object:p p(0.0, 0.0, 0.0) e(0.0, 0.0, 0.0) c(0.88, 0.88, 0.88) material:d

# meshes
mesh:obj/plane1.obj p(0.0, 0.0, 0.0) e(0.0, 0.0, 0.0) c(1.0, 1.0, 1.0) material:d
mesh:obj/plane2.obj p(0.0, 0.0, 0.0) e(0.0, 0.0, 0.0) c(0.15, 0.28, 0.41) material:d
mesh:obj/plane3.obj p(0.0, 0.0, 0.0) e(0.0, 0.0, 0.0) c(0.96, 0.72, 0.01) material:d
