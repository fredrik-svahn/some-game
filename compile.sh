#export LD_LIBRARY_PATH="$LD_LIBRARY_PATH;./bin"
export DISPLAY="DISPLAY"
g++ main.cpp -std=c++11 -I./include -L./lib -lglu32 -lfreeglut -lopengl32 -lglew32 -o "arpg.exe"
