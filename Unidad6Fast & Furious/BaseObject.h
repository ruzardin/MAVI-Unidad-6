#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class BaseObject
{
public:
    // Constructor de la clase BaseObject que recibe el nombre del archivo de imagen como par�metro
    BaseObject(string filename);

    // Destructor de la clase BaseObject
    ~BaseObject();

    // Funci�n para dibujar el objeto en una ventana RenderWindow
    void Draw(RenderWindow* pWnd);

    // Funci�n para actualizar el objeto en funci�n del tiempo transcurrido
    void Update(float dt);

    // Funciones para configurar las propiedades del objeto
    void SetScale(float uniformScale) { _pSpr->setScale(uniformScale, uniformScale); }
    void SetPosition(Vector2f pos) { _position = pos; }
    void SetAcceleration(Vector2f acc) { _acceleration = acc; }
    void SetVelocity(Vector2f vel) { _velocity = vel; }

    // Funciones para obtener las propiedades del objeto
    Vector2f GetPosition() { return _position; }
    Vector2f GetAcceleration() { return _acceleration; }
    Vector2f GetVelocity() { return _velocity; }

    // Funci�n para agregar una aceleraci�n al objeto
    void AddAcceleration(Vector2f acc) {
        _acceleration.x += acc.x;
        _acceleration.y += acc.y;
    }

private:
    Sprite* _pSpr;
    Texture* _pTex;

    Vector2f _position;
    Vector2f _acceleration;
    Vector2f _velocity;
};
