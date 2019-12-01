#include "Menu.hpp"

/*!
**@brief Construct a new Menu:: Menu object
**
**@param device 
*/
Menu::Menu(irr::IrrlichtDevice *device)
{
	deviceCpy = device;
	driver = deviceCpy->getVideoDriver();
	selected = PLAY;
	image = new Image(assets[selected], driver);
	game = new Game(deviceCpy);
}

/*!
**@brief Destroy the Menu:: Menu object
**
*/
Menu::~Menu()
{
}

/*!
**@brief Launch Menu, check action and print every loop
**
*/
void Menu::Run()
{
	int select_player = 1;
	Event *event = new Event();

	deviceCpy->setEventReceiver(event);
	while (deviceCpy->run()) {
		driver->beginScene(true, true,
		irr::video::SColor(0,120,120,120));
		image->Draw(driver);
		driver->endScene();
		select_player = Action(event, select_player);
		if (select_player == 2)
			return;
		deviceCpy->setEventReceiver(event);
	}
}

/*!
**@brief Check and redirect different Event
**
**@param event 
**@param select_player 
**@return int 
*/
int Menu::Action(Event *event, int select_player)
{
	irr::EKEY_CODE input = event->GetInput();

	event->SetInput(irr::KEY_OEM_8);
	switch (input) {
		case irr::KEY_UP :
			KeyUp(select_player);
			break;
		case irr::KEY_DOWN :
			KeyDown(select_player);
			break;
		case irr::KEY_RETURN :
			select_player = EnterPressed();
			break;
		default :
			break;
	}
	image->Update(assets[selected], driver);
	return select_player;
}

/*!
**@brief Change picture if event KeyDown is pressed in
**	 select player menu
*/
void Menu::KeyDownSelectP()
{
	switch (selected) {
		case TWO_P :
			selected = THREE_P;
			break;
		case THREE_P :
			selected = FOUR_P;
			break;
		case FOUR_P :
			selected = TWO_P;
			break;
	}
}

/*!
**@brief Change picture if event KeyUp is pressed in
**	 select player menu
*/
void Menu::KeyUpSelectP()
{
	switch (selected) {
		case TWO_P :
			selected = FOUR_P;
			break;
		case THREE_P :
			selected = TWO_P;
			break;
		case FOUR_P :
			selected = THREE_P;
			break;
	}
}

/*!
**@brief Change picture if event KeyUp is pressed menu
**
*/
void Menu::KeyUp(int check)
{
	if (check != 0) {
		if (selected == PLAY)
			selected = QUIT;
		else if (selected == QUIT)
			selected = PLAY;
	} else
		KeyUpSelectP();
}

/*!
**@brief Change picture if event KeyDown is pressed menu
**
*/
void Menu::KeyDown(int check)
{
	
	if (check != 0) {
		if (selected == PLAY)
			selected = QUIT;
		else if (selected == QUIT)
			selected = PLAY;
	} else
		KeyDownSelectP();
}

/*!
**@brief If a player win game, select Win picture
**
**@param win 
*/
void Menu::checkWin(int win)
{
	switch (win) {
		case 0 :
			selected = WIN_P;
			break;
		case 1 :
			selected = WIN_B;
			break;
		case 2 :
			selected = WIN_Y;
			break;
		case 3 :
			selected = WIN_R;
			break;
		default :
			selected = PLAY;
			break;
	}
}

/*!
**@brief EnterPressed event allows the chosen action,
**	 Run the game, Quit
**@return int 
*/
int Menu::EnterPressed()
{
	int win;

	switch (selected) {
		case QUIT :
			return 2;
		case PLAY :
			selected = TWO_P;
			return 0;
		case WIN_R :
		case WIN_B :
		case WIN_P :
		case WIN_Y :
			selected = PLAY;
			break;
		default :
			win = game->Run(selected);
			checkWin(win);
			break;
	}
	return 1;
}