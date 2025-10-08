g++ ./src/*.cpp ^
-I../include ^
-I../dependencies/SDL/include ^
-L../build ^
-L../dependencies/SDL/lib ^
-lssge ^
-lsdl3 ^
-lsdl3_image ^
-std=c++23 ^
-o example