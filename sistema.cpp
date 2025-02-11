#include <iostream>
#include <cmath>
#include <vector>

const float DELTA_TIME = 0.016f;
const float GRAVEDAD_TIERRA = 9.81f;
const float GRAVEDAD_MERCURIO = 3.7f;
const float GRAVEDAD_VENUS = 8.87f;
const float GRAVEDAD_MARTE = 3.71f;
const float GRAVEDAD_JUPITER = 24.79f;
const float GRAVEDAD_SATURNO = 10.44f;
const float GRAVEDAD_URANO = 8.69f;
const float GRAVEDAD_NEPTUNO = 11.15f;
const float GRAVEDAD_PLUTON = 0.62f;
const float GRAVEDAD_SOL = 274.0f;
const float TEMPERATURA_MERCURIO = 167.0f;
const float TEMPERATURA_VENUS = 462.0f;
const float TEMPERATURA_TIERRA = 15.0f;
const float TEMPERATURA_MARTE = -60.0f;
const float TEMPERATURA_JUPITER = -108.0f;
const float TEMPERATURA_SATURNO = -138.0f;
const float TEMPERATURA_URANO = -224.0f;
const float TEMPERATURA_NEPTUNO = -218.0f;
const float TEMPERATURA_PLUTON = -229.0f;
const float TEMPERATURA_SOL = 5500.0f;

class Vector2D {
public:
    float x, y;
    Vector2D(float x = 0, float y = 0) : x(x), y(y) {}
    
    Vector2D operator+(const Vector2D& v) const {
        return Vector2D(x + v.x, y + v.y);
    }
    
    Vector2D operator-(const Vector2D& v) const {
        return Vector2D(x - v.x, y - v.y);
    }
    
    Vector2D operator*(float scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }
    
    float magnitude() const {
        return std::sqrt(x * x + y * y);
    }
    
    void normalize() {
        float mag = magnitude();
        if (mag > 0) {
            x /= mag;
            y /= mag;
        }
    }
};

class ObjetoFisico {
public:
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;
    float mass;
    float radius;
    float temperature;

    ObjetoFisico(float x, float y, float mass, float radius, float initial_temperature)
        : position(x, y), velocity(0, 0), acceleration(0, 0), mass(mass), radius(radius), temperature(initial_temperature) {}

    void aplicarGravedad(float gravedad) {
        acceleration.y += gravedad;
    }

    void aplicarTemperatura() {
        temperature += 0.1f;  
    }

    void mover() {
        velocity = velocity + acceleration * DELTA_TIME;  
        position = position + velocity * DELTA_TIME;    

        aplicarTemperatura();
    }

    void mostrarEstado() {
        std::cout << "Posición: (" << position.x << ", " << position.y << "), Velocidad: (" << velocity.x << ", " << velocity.y << "), Temperatura: " << temperature << "°C\n";
    }
};

int main() {
    ObjetoFisico tierra(0, 0, 5.972e24f, 6371.0f, TEMPERATURA_TIERRA);  
    ObjetoFisico mercurio(0, 0, 3.285e23f, 2439.7f, TEMPERATURA_MERCURIO);

    for (int i = 0; i < 1000; ++i) {
        tierra.aplicarGravedad(GRAVEDAD_TIERRA);
        mercurio.aplicarGravedad(GRAVEDAD_MERCURIO);

        tierra.mover();
        mercurio.mover();

        tierra.mostrarEstado();
        mercurio.mostrarEstado();
    }

    return 0;
}
