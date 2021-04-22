#include <string>

struct Sound {
	enum class Type {
		MUSIC, SFX
	};

	std::string id;
	std::string path;
	Type type;
	int volume;
};