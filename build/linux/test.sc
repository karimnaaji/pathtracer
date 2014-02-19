# test scene
camera p(0.0, 2.5, -4.0) la(0.0, 0.0, 0.0) res(640, 480)

# spheres
object:s p(0.0, 4.5,  1.0) e(25.0, 25.0, 25.0) c(1.0, 1.0, 1.0) material:d

# plane
object:p p(0.0,  0.0,  0.0) e(0.0, 0.0, 0.0) c(0.9, 0.85, 0.8) material:d

# mesh
mesh:suzanne.obj p(0.5, 0.0, 0.0) e(0.0, 0.0, 0.0) c(1.0, 1.0, 1.0) material:d
#mesh:torus.obj p(0.0, 0.0, 0.0) e(0.0, 0.0, 0.0) c(1.0, 1.0, 1.0) material:d

#object:s p( 0.0, 1.0,  0.0) e(0.0,  0.0,  0.0) c(0.5, 0.5, 0.5) material:s
#object:s p( 2.5, 1.0,  0.0) e(0.5,  0.5,  0.7) c(1.0, 1.0, 1.0) material:d
#object:s p(-2.5, 1.0,  0.0) e(0.5,  0.7,  0.5) c(1.0, 1.0, 1.0) material:d
#object:s p( 0.0, 1.0,  2.5) e(0.7,  0.5,  0.5) c(1.0, 1.0, 1.0) material:d

