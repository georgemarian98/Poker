#include "Player.h"

Player::Player( )
{
	carti[0] = Card::generareCarte( );
	carti[1] = Card::generareCarte( );

	buget = 500;
}
