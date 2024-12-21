#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemy.h"
#include "Crosshair.h"
using namespace sf;
using namespace std;

class Game {
public:
    Game();
    ~Game();

    void Run();

private:
    void ProcessEvents();
    void Update(float dt);
    void Render();

    void SpawnEnemy();
    void CheckCollisions();

    RenderWindow _window;
    vector<Enemy*> _enemies;
    Crosshair* _crosshair;

    int _score;
    Font _font;
    Text _scoreText;
};
