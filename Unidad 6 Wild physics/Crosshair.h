#pragma once
#include "BaseObject.h"
using namespace sf;
using namespace std;

class Crosshair : public BaseObject {
public:
    Crosshair(const string& textureFile);

    void Update(const Vector2i& mousePosition);
};
