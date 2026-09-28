#include "Game.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
    
	Game game;

	if (!game.Initialize()) {
		return 1;
	}

	game.Run();

	return 0;
}