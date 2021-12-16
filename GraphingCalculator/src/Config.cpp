#include "../include/Config.h"
#include "../include/Interpreter.h"

Interpreter ci(false);

Config::Config(){

}

template <typename T>
void read_type_arr(std::string table, T& v){
	lua_getglobal(ci.get_state(), table.c_str());

	if (lua_istable(ci.get_state(), -1)){
		lua_pushnil(ci.get_state());

		int itt = 0;

		while (lua_next(ci.get_state(), -2)){
			if (lua_isnumber(ci.get_state(), -1)){
				v[itt++] = (float)(lua_tonumber(ci.get_state(), -1));
			}

			lua_pop(ci.get_state(), 1);
		}

		lua_pop(ci.get_state(), 1);
	}
}

template <typename T>
void read_type(std::string table, T& v){
	lua_getglobal(ci.get_state(), table.c_str());

	if (lua_isnumber(ci.get_state(), -1)){
		v = lua_tonumber(ci.get_state(), -1);
	}else if (lua_isboolean(ci.get_state(), -1)){
		v =  lua_toboolean(ci.get_state(), -1);
	}

	lua_pop(ci.get_state(), -1);
}

void Config::read(std::string file){
	ci.run_file(file);

	lua_getglobal(ci.get_state(), "themes");

	lua_pushnil(ci.get_state());


	while (lua_next(ci.get_state(), -2)){
		lua_pushnil(ci.get_state());

		std::vector<float> theme;

		while (lua_next(ci.get_state(), -2)){
			theme.push_back(lua_tonumber(ci.get_state(), -1));

			lua_pop(ci.get_state(), 1);
		}

		themes.push_back(theme);

		lua_pop(ci.get_state(), 1);
	}

	lua_pop(ci.get_state(), 1);

	read_type_arr("background", background);
	read_type_arr("axis", axis);
	read_type("max_speed", max_speed);
	read_type("min_speed", min_speed);
	read_type("speed_increment", speed_increment);
	read_type("max_scale", max_scale);
	read_type("min_scale", min_scale);
	read_type("scale_speed", scale_speed);
	read_type("fineness", fineness);

	read_type("default_theme", default_theme);
	read_type("move_camera_left", move_camera_left);
	read_type("move_camera_right", move_camera_right);
	read_type("move_camera_up", move_camera_up);
	read_type("move_camera_down", move_camera_down);
	read_type("zoom_in", zoom_in);
	read_type("zoom_out", zoom_out);
	read_type("increase_speed", increase_speed);
	read_type("decrease_speed", decrease_speed);
	read_type("change_theme_up", change_theme_up);
	read_type("change_theme_down", change_theme_down);

	read_type("show_grid", show_grid);
	read_type("use_theme", use_theme);
}
