#export LD_LIBRARY_PATH="$LD_LIBRARY_PATH;./bin"
export DISPLAY="DISPLAY"
g++ main.cpp -I./include -L./lib -lglu32 -lfreeglut -o "arpg.exe" -lopengl32
