#include "MyLibraries.h"
#include "Sprite.h"
#include "TickTimerAnimator.h"
#include "TickTimerAnimation.h"
#include "InputContoller.h"
#include "StateTransitions.h"
#include "FrameRangeAnimator.h"

#define	FIGHTER_ACTION_DELAY_MSECS	150 //<-----------------FOR DEBUGGING

class Fighter final {
	using Input = std::set<std::string>;
private:
	Point					FighterPos;
	Sprite*					sprite;
	string					nextAction;
	TickTimerAnimator*		tickAnimator;	// deferred firing actions; always dynamic
	TickTimerAnimation		tickAnim;
	string					name;
	input::InputController		inputController;
	logic::StateTransitions		stateTransitions;

	void SetActionWithAnimator(const std::function<void()>& f);
	const string Make_key(const Input& input) const;
public:
	// TODO: 

	Fighter(string Name,Point position);
	~Fighter() {};

	FrameRangeAnimator* animator;//testing
	void setStateMachine(bool debug);
	void Handler();
	void Draw(SDL_Surface& gScreenSurface, string name, int w,int h);//test function
	bool initialize(const string& path);//give json as argument
};