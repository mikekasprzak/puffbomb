g++ -DALLEGRO_STATICLINK src/main.cpp -I src src/Geometry/Real.cpp src/Geometry/Vector/Vector2D.cpp src/Geometry/Matrix/Matrix2x2.cpp src/Geometry/Matrix/Matrix3x3.cpp -o Triangles.exe -lalleg_s -lkernel32 -luser32 -lgdi32 -lcomdlg32 -lole32 -ldinput -lddraw -ldxguid -lwinmm -ldsound