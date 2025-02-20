#include <memory>

#include "game.h"

using namespace std;


int main()
{   
    unique_ptr<Game> game = make_unique<Game>();
    game->Run();
    return 0;
}
