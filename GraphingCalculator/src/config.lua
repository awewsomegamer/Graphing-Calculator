--background = {1,1,1}
--background = {0.1,0.5,1} 
--axis = {0,0,0} 

  

max_speed = 10 -- How fast the camera can move 
min_speed = 0.01 -- How slow the camera can move 
speed_increment = 0.01 -- How fast to increment the position of the camera 
max_scale = 10; -- How far the camera can be zoomed out 
min_scale = 0.01 -- How far the camera can be zoomed in 
scale_speed = 0.01 -- How fast the camera should zoom in 
fineness = 0.1 -- How fine graphs should be graphed 
start_zoom = 1 -- How far should the camera be zoomed in on launch of the application  (0.1 Default)  
default_theme = 0 -- The index of the default theme (0 -> amount of themes - 1)
volume = 1 -- Volume of the program

show_grid = false -- Show the grid
use_theme = true -- Use the themes table 
play_sounds = false -- Play the average sound of the graph

--move_camera_left =  -- Keycode to move the camera left
--move_camera_right = -- Keycode to move the camera right
--move_camera_up = -- Keycode to move the camera up
--move_camera_down = -- Keycode to move the camera down
--zoom_in = -- Keycode to zoom in the camera
--zoom_out = -- Keycode to zoom out camera
--increase_speed = -- Keycode to increase the camera speed
--decrease_speed = -- Keycode to decrease the camera speed
--change_theme_up = -- Keycode move the theme pointer up (0 -> 1)
--change_theme_down = -- Keycode move the theme pointer down (1 -> 0)
--reload_graphs = -- The key that reloads the graphs
  
theme_dark = {0.125,0.125,0.125,    1,1,1} 
theme1 = {0.1,0.5,1,    1,0,0} 
theme2 = {0.1,0.5,1,    0,1,0} 
theme3 = {0.1,0.5,1,    0,0,1} 
theme4 = {0.1,0.5,1,    1,1,1} 
theme5 = {0,0.5,1,    1,1,1} 
theme6 = {0,0,1,    1,1,1} 
theme7 = {0,0,0,    1,1,1} 

themes = {theme_dark, theme1,theme2,theme3,theme4,theme5,theme6,theme7} 


-- Visit GLFW https://www.glfw.org/docs/3.3/group__keys.html for keycodes -- 
-- #define GLFW_KEY_1 49 												  -- 
--  				  ^ 												  --
--			this is the value of the keycode							  -- 