#include <MyLibraries.h>
#include <AnimationFilm.h>

class Sprite {
private:
	byte frameNo;
	Rect frameBox;
	Point position;
	bool visible;
	unsigned type;
	AnimationFilm* currFilm;
	//TileLayer* myLayer;maybe not needed here cause we dont have tiles here

public:
	Sprite(Point position,AnimationFilm* film, unsigned type);
	~Sprite();

	void SetFrame(byte i);
	byte GetFrame(void) const;
	void SetVisibility(bool v);
	bool IsVisible(void) const;
	bool CollisionCheck(Sprite* s);
	void Move(Point x);
	void Display(SDL_Surface &dest,Rect& da);
	unsigned GetType(void) const;
};