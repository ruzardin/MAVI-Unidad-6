#include "BaseObject.h"
#include <iostream>

// Constructor de la clase BaseObject que recibe el nombre del archivo de imagen como par�metro
BaseObject::BaseObject(string filename)
{
    // Se crea una nueva instancia de Texture (_pTex) y se intenta cargar la imagen desde el archivo
    _pTex = new Texture();
    if (!_pTex->loadFromFile(filename)) {
        cout << "No se pudo cargar la imagen" << endl;
    }

    // Se crea una nueva instancia de Sprite (_pSpr) y se establece su textura
    _pSpr = new Sprite();
    _pSpr->setTexture(*_pTex);

    // Inicializaci�n de variables de posici�n, aceleraci�n y velocidad en 0
    _position.x = 0.0f;
    _position.y = 0.0f;
    _acceleration.x = 0.0f;
    _acceleration.y = 0.0f;
    _velocity.x = 0.0f;
    _velocity.y = 0.0f;
}

// Destructor de la clase BaseObject
BaseObject::~BaseObject()
{
    // Se liberan las memorias asignadas din�micamente para el Sprite y la Texture
    delete _pSpr;
    delete _pTex;
}

// Funci�n para dibujar el objeto en una ventana RenderWindow
void BaseObject::Draw(RenderWindow* pWnd)
{
    // Se dibuja el Sprite en la ventana especificada
    pWnd->draw(*_pSpr);
}

// Funci�n para actualizar el objeto en funci�n del tiempo transcurrido
void BaseObject::Update(float dt)
{
    // Actualizaci�n de la velocidad en funci�n de la aceleraci�n y el tiempo
    _velocity.x += _acceleration.x * dt;
    _velocity.y += _acceleration.y * dt;

    // Actualizaci�n de la posici�n en funci�n de la velocidad y el tiempo
    _position.x += _velocity.x * dt;
    _position.y += _velocity.y * dt;

    // Se actualiza la posici�n del Sprite con la nueva posici�n calculada
    _pSpr->setPosition(_position);

    // Reinicio de las aceleraciones a 0 despu�s de la actualizaci�n
    _acceleration.x = 0.0f;
    _acceleration.y = 0.0f;
}
