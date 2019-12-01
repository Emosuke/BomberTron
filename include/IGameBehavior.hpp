
#ifndef IGAMEBEHAVIOR_HPP_
	#define IGAMEBEHAVIOR_HPP_

class IGameBehavior {
public:
	enum action
	{
		NONE = 0,
		MOVE_UP = 2,
		MOVE_DOWN = 4,
		MOVE_RIGHT = 8,
		MOVE_LEFT = 16,
	    DROP = 32,
		ESCAPE = 64,
	};
	virtual int	update() = 0;
};

#endif
