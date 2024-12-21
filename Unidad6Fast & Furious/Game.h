#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "BaseObject.h"

using namespace sf;

class Game {
public:
    Game();
    ~Game();
    void Loop();

private:
    void _Draw();
    void _Update(float dt);
    void _ProcessEvents();

    RenderWindow* _pWnd;
    BaseObject* _pBall;

    float _velocidad;      // Velocidad actual del c�rculo
    float _velocidadFinal; // Velocidad m�xima
    float _incremento;     // Incremento de velocidad
};

