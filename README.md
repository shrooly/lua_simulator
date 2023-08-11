# lua_simulator

(Roguh) Build steps:
- Download the lua_simulator repo
- Taken a hold of a lua library consisting a Makefile 
- Build the library: "make all" 
- sudo cp src/*.h /usr/local/include/
- install library: sudo cp src/liblua.a /usr/local/lib/
- update library cache (for Linux): sudo ldconfig
- CMakeLists.txt already includes linking to the lua library
- Build the project with gcc
- Install python dependencies: tkinter, PIL
- Run the main.py script
- Enter LUA script in the field window such as "drawRectangle(50,70,20,40)"
- Press update canvas
- C program will be invoked, it will run the LUA script, creating a "canvas_data.bin"
- The python script will use this binary up to draw the pixels of the given rectangle