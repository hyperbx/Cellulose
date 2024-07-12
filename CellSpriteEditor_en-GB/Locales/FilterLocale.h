#pragma once

class FilterLocale
{
public:
	static void InstallCse()
	{
		WRITE_MEMORY(0x436BDF, const char*, "TGA (*.tga)|*.tga||");

		WRITE_MEMORY(0x41FFCE, const char*,
			"All Supported Image Files|*.bmp;*.jpg;*.jpeg;*.jpe;*.jfif;*.gif;*.tga;*.png;*.pic;*.pix;*.tm2;*.iff;*.rla;*.pvr;*.svr;*.gvr;*.xvr;*.dds|"
			"BMP (*.bmp)|*.bmp|"
			"JPEG (*.jpg; *.jpeg; *.jpe; *.jfif)|*.jpg;*.jpeg;*.jpe;*.jfif|"
			"GIF (*.gif)|*.gif|"
			"TGA (*.tga)|*.tga|"
			"PNG (*.png)|*.png|"
			"Softimage PIC (*.pic)|*.pic|"
			"Alias PIX (*.pix)|*.pix|"
			"Maya IFF (*.iff)|*.iff|"
			"RLA (*.rla)|*.rla|"
			"Dreamcast PVR (*.pvr)|*.pvr|"
			"PlayStation 2 SVR (*.svr)|*.svr|"
			"PlayStation 2 TIM (*.tm2)|*.tm2|"
			"GameCube GVR (*.gvr)|*.gvr|"
			"Xbox XVR (*.xvr)|*.xvr|"
			"DirectDraw Surface (*.dds)|*.dds|"
			"All Files (*.*)|*.*||"
		);
	}
};