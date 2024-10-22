#pragma once

#define INI_FILE "Cellulose.ini"

class Configuration
{
public:
	inline static std::string Language = "en-GB";

	inline static bool IsModernVisualStyle = true;

	static void Read();

	static bool IsJapanese()
	{
		return Language == "ja-JP";
	}
};