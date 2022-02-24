#include "Ponto2D.h"
#include <iostream>
#include <math.h>

using std::cout;
using std::cin;
using std::endl;

Ponto2D::Ponto2D(float x, float y) {
    setX(x);
    setY(y);
}


void Ponto2D::setX(float eixoX) {
    x = eixoX;
}

void Ponto2D::setY(float eixoY) {
    y = eixoY;
}

float Ponto2D::getX() {
    return x;
}

float Ponto2D::getY() {
    return y;
}

float Ponto2D::distancia(Ponto2D ponto) {
    //distancia = (x - x0)² + (y - y0)²
    float distX = x - ponto.getX();
    float distY = y - ponto.getY();

    return sqrt(distX * distX + distY * distY);
}