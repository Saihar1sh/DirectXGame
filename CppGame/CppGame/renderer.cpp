enum class Colors
{
	Black = 0x000000,
	Blue = 0x0000FF,
	Gray = 0x808080,
	Purple = 0x800080,
	White = 0xFFFFFF,
	Cyan = 0x00FFFF,
	Silver = 0xC0C0C0,
	DarkBlue = 0x00008B,
	LightBlue = 0xADD8E6,
	Aquamarine = 0x7FFFD4,
	Orange = 0xFFA500,
	Brown = 0xA52A2A,
	Yellow = 0xFFFF00,
	Maroon = 0x800000,
	Lime = 0x00FF00,
	Green = 0x008000,
	LightGreen = 0x9ce79c,
	Olive = 0x808000,
	Magenta = 0xFF00FF,
	Red = 0xFF0000,
	Pink = 0xFFC0CB,
};


internal void
clear_screen(Colors color)
{
	u32 pixelColor = (u32)color;

	u32* pixel = (u32*)render_state.memory;
	for (int j = 0; j < render_state.height; j++)
	{
		for (int i = 0; i < render_state.width; i++)
		{
			*pixel++ = pixelColor;
		}
	}

}


internal void
draw_rect_in_pixels(int x0, int y0, int x1, int y1, Colors _color)
{
	u32 color = (u32)_color;

	x0 = clamp(0, x0, render_state.width);
	x1 = clamp(0, x1, render_state.width);
	y0 = clamp(0, y0, render_state.height);
	y1 = clamp(0, y1, render_state.height);

	for (int y = y0; y < y1; y++)
	{
		u32* pixel = (u32*)render_state.memory + x0+ y*render_state.width;
		for (int x = x0; x < x1; x++)
		{
			*pixel++ = color;
		}
	}

}

global_variable float render_scale = 0.01f;

internal void
draw_rect(float x, float y, float half_size_x, float half_size_y, Colors color)
{
	x *= render_state.height * render_scale;
	y *= render_state.height * render_scale;
	half_size_x *= render_state.height * render_scale;
	half_size_y *= render_state.height * render_scale;

	x += render_state.width / 2.f;
	y += render_state.height / 2.f;

	//conversion to pixels
	int x0 = (x - half_size_x);
	int x1 = (x + half_size_x);
	int y0 = (y - half_size_y);
	int y1 = (y + half_size_y);

	draw_rect_in_pixels(x0,x1,y0,y1, color);
}


