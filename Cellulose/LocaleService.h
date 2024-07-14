#pragma once

using json = nlohmann::json;

class LocaleService
{
	static inline json m_resource;

public:
	static void Read(const std::string in_resourcePath)
	{
		if (!FileExists(in_resourcePath))
			return;

		m_resource = json::parse(ReadStringFromFile(in_resourcePath));
	}

	static const char* Localise(const char* in_key)
	{
		if (in_key == nullptr || strlen(in_key) == 0)
			return in_key;

		if (m_resource.empty())
			return in_key;

		if (!m_resource.contains(in_key))
			return in_key;

		if (!m_resource[in_key].is_string())
			return in_key;

		return StringToConstCharPtr(m_resource[in_key]);
	}

	static void Localise(size_t in_ptr, const char* in_key)
	{
		WRITE_MEMORY(in_ptr, const char*, Localise(in_key));
	}

	static void LocaliseRaw(size_t in_ptr, const char* in_key)
	{
		auto str = Localise(in_key);
		auto len = strlen(str);

		for (int i = 0; i < len; i++)
			WRITE_MEMORY(in_ptr + i, const char, str[i]);

		// Write null terminator.
		WRITE_MEMORY(in_ptr + len, uint8_t, 0);
	}
};