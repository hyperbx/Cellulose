#pragma once

#define INI_FILE "Cellulose.ini"

class Configuration
{
public:
	inline static std::string Language = "en-GB";

	static void Read();
};

