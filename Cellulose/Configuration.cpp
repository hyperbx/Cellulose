void Configuration::Read()
{
	INIReader reader(INI_FILE);

	INI_BEGIN_SECTION("General")
	{
		INI_READ_STRING_B(Language);
		INI_READ_BOOLEAN_B(IsModernVisualStyle);
	}
	INI_END_SECTION()
}