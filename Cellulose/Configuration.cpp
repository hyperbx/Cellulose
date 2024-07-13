void Configuration::Read()
{
	INIReader reader(INI_FILE);

	// General
	Language = INI_READ_STRING("General", Language);
}