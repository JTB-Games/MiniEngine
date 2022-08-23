#pragma once
struct MiniEngine
{
	LPCWSTR name;
	int screen_width;
	int screen_height;
	wchar_t* screen;
	HANDLE hConsole;
	int (*update)(struct MiniEngine*);
};
struct SMALL_RECT {
	SHORT Left;
	SHORT Top;
	SHORT Right;
	SHORT Bottom;
};
struct MiniEngine MiniEngine_Create(LPCWSTR name, int screen_width, int screen_height, int (*update)(struct MiniEngine*))
{
	struct MiniEngine engine;
	engine.name = name;
	engine.screen_width = screen_width;
	engine.screen_height = screen_height;
	engine.screen = NULL;
	engine.hConsole = NULL;
	engine.update = update;
	return engine;
}
int MiniEngine_Run(struct MiniEngine* engine)
{
	//Init
	engine->screen = (wchar_t*)malloc(((size_t)engine->screen_width * (size_t)engine->screen_height) * sizeof(wchar_t));
	engine->hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(engine->hConsole);
	DWORD dwBytesWritten = 0;
	//Configure console window

	if (engine->screen == NULL || engine->screen == 0)
		return -1;

	while (1)
	{
		// Set up the handles for reading/writing:
		HANDLE wHnd = engine->hConsole;
		HANDLE rHnd = engine->hConsole;
		// Change the window title:
		SetConsoleTitle(engine->name);
		// Set up the required window size:
		SMALL_RECT windowSize = { 0, 0, engine->screen_width - 1, engine->screen_height - 1 };
		SetConsoleWindowInfo(wHnd, 1, &windowSize);
		COORD bufferSize = { engine->screen_width, engine->screen_height };
		SetConsoleScreenBufferSize(wHnd, bufferSize);
		//Render to console
		engine->update(engine);
		engine->screen[engine->screen_width * engine->screen_height - 1] = '\0';
		COORD coord = { 0,0 };
		WriteConsoleOutputCharacter(engine->hConsole, engine->screen, engine->screen_width * engine->screen_height, coord, &dwBytesWritten);
	}
}
void MiniEngine_Render_Clear(struct MiniEngine* engine, char c)
{
	for (int y = 0; y < engine->screen_height; y++)
	{
		for (int x = 0; x < engine->screen_width; x++)
		{
			engine->screen[y * engine->screen_width + x] = c;
		}
	}
}
void MiniEngine_Render_Pixel(struct MiniEngine* engine, int x, int y, char c)
{
	engine->screen[y * engine->screen_width + x] = c;
}