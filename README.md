# Graphing Calculator
This is a Graphing calculator that is written in C++. <br>
It uses OpenGL to draw, OpenAL to make noise, and Lua to parse the configuration of the program and the graphs that the program should draw. <br>

# Format of graphs.lua
The file "graphs.lua" contains a list of assignments of the variable "f", followed by the equation that it should draw, inequlaties, and color.<br>
To use mathematical functions like sine, follow: https://www.tutorialspoint.com/lua/lua_math_library.htm <br>
<br>
f = math.sin(x) <br>
f = math.sin(x) > 0 <br>
f = math.sin(x) > 0 C:[255,0,0] <br>
f = math.sin(x) C:[255,0,0] <br>
<br>
<br>
f = function *inequality / color color*
<br>
Text in the above that is italics is optional, the order of the inequality and color is not interchangable. The color property must always be after the inequality if there is one. <br>
<br>
# Compiling
This was written with mingw-w64 with posix threads. The required .dll files are included in the res folder.<br>
<br>
# Bugs and optimization
I have left comments of bugs and optimizations I found.
