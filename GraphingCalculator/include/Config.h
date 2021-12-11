#ifndef CONFIG_H
#define CONFIG_H

#include <string>

class Config{
public:
	void read(std::string);

	int n_themes = 256;
	int themes[n_themes][10]; // bg, fg, graph color
};

#endif
