#include <iostream>

class Ponto2D {
    public:
        Ponto2D(float, float);
        ~Ponto2D();
        void moverX(float);
        void moverY(float); 
        float distancia(Ponto2D);
        void setX(float);
        void setY(float);
        float getX();
        float getY();
    private:
        float x;
        float y;
};