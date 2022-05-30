#pragma once
#include <unordered_map>

class c_globals {
public:
	bool active = true;
	bool auth = false;
	//char sub[255] = "14.01.2022"; not used
	char user_name[255] = "asd";
	char pass_word[255] = "asd";
};

inline c_globals globals;