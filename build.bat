cd bin

g++ -std=c++23 -c ..\src\*.cpp  ..\src\UI\*.cpp ^
-I..\include ^
-I..\dependencies\SDL\include ^
-L..\dependencies\SDL\lib ^
-lsdl3 -lsdl3_image

ar rcs libssge.a *.o

cd ..