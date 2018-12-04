#include "Window.h"
#include "AnimatorHolder.h"
#include "MusicPlayer.h"

Window::Window(const int width, const int height) {
	this->width = width;
	this->height = height;
};

Window::~Window() {};

bool Window::HandleInput(SDL_Event& event) {
	bool quit = false;
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			quit = true;
		}
		else {
			//if here for the sound to handle "globaly"
			if (state == INTRO) {
				int tmpstate = intro->HandleInput(event);
				state = tmpstate == -1 ? state : tmpstate;
			}
		}//Handle Input For Menu
	}
	return quit;
};

bool Window::open(string w_name) {

	//here do a controller check maybe
	//For starting these
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		cout << "SDL could not initialize! SDL Error: %s\n", SDL_GetError();
		return false;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		cout << "Warning: Linear texture filtering not enabled!";
	}
	window = SDL_CreateWindow(w_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		cout << "Window could not be created! SDL Error: %s\n", SDL_GetError();
		return false;
	}
	gScreenSurface = SDL_GetWindowSurface(window);
	gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == NULL) {
		cout << "Renderer could not be created! SDL Error: %s\n", SDL_GetError();
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return  false;
	}

	return true;
};


void Window::initialize() {
	//Here do call the picture/sound/sprite and etc initialazation
	if (!loadMedia()) {
		cout << "Something went really bad\n";
	}
	intro = new Intro();
	intro->initialize(gScreenSurface);
	//Initialize Menu
	state = INTRO;
};

void Window::close() {

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);

	window = NULL;
	gRenderer = NULL;
	gScreenSurface = NULL;

	//Call the Holder's CleanUp Functions
	SpriteHolder::Get()->CleanUp();
	AnimatorHolder::CleanUp();
	AnimationFilmHolder::Get()->CleanUp();
	MusicPlayer::Get()->CleanUp();

	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
};


bool Window::loadMedia() {
	//Here load the font 
	font = TTF_OpenFont("media/font.ttf", 28);//The 28 here is the font size
	if (font == NULL)
	{
		cout << "Failed to load lazy font! SDL_ttf Error: %s\n" << TTF_GetError();
		return false;
	}
	return true;
}


void Window::drawWindow() {
	if (state == INTRO) {//add Sound
		intro->DrawIntro(*gScreenSurface);
	}
	else if (state == MENU) {
		SDL_FillRect(gScreenSurface, NULL, 0x000000);//For starters just wipes the screen
		//MusicPlayer::Get()->PlayEffect(MusicPlayer::Get()->RetrieveEffect("transition"), 0);
		//DrawMenu
	}//when changing the state kill the intro animator
	SDL_UpdateWindowSurface(window);
};

//Mix volume ad 