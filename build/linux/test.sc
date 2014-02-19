# test scene
camera p(1.0, 2.5, -2.0) la(1.2, 0.5, 0.0) res(640, 480)

# spheres
object:s p(0.51, 1.5, 2.5) e(5.0, 5.0, 5.0) c(1.0, 1.0, 1.0) material:d
object:s p(1.0, 1.0, 0.5) e(0.0, 0.0, 0.0) c(0.5, 0.5, 0.5) material:s

# floor plane
object:p p(0.0, 0.0, 0.0) e(0.0, 0.0, 0.0) c(0.88, 0.85, 0.78) material:d

# meshes
mesh:obj/plane1.obj p(0.0, 0.0, 0.0) e(0.0, 0.0, 0.0) c(1.0, 1.0, 1.0) material:d
mesh:obj/plane2.obj p(0.0, 0.0, 0.0) e(0.0, 0.0, 0.0) c(1.0, 0.71, 0.21) material:d
mesh:obj/plane3.obj p(0.0, 0.0, 0.0) e(0.0, 0.0, 0.0) c(0.0, 0.29, 0.61) material:d
