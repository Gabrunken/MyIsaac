g++ ./src/*.cpp \
-L../build \
-L../dependencies/SDL/lib \
-lssge \
-lsdl3 \
-lsdl3_image \
-I../include \
-I../dependencies/SDL/include \
-std=c++23 \
-o example