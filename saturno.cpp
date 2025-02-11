#include <iostream>
#include <vector>
#include <cmath>

const float GRAVEDAD_SATURNO = 10.44f;  
const float DELTA_TIME = 0.016f;         
const float PISO_Y = 0.0f;               
const float FRICCION_SUELO_SATURNO = 0.01f; 
const float TEMPERATURA_AMBIENTE_SATURNO = -178.0f; 

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
    
    Vector2D operator/(float scalar) const {
        return Vector2D(x / scalar, y / scalar);
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
    
    float dot(const Vector2D& v) const {
        return x * v.x + y * v.y;
    }
};

class ObjetoFisico {
public:
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;
    Vector2D angularVelocity;
    float mass;
    float radius;
    float elasticity; 
    float angle;      
    float momentInercia;  
    float temperature;    

    ObjetoFisico(float x, float y, float mass, float radius, float elasticity = 0.8f)
        : position(x, y), velocity(0, 0), acceleration(0, 0), angularVelocity(0, 0), 
          mass(mass), radius(radius), elasticity(elasticity), angle(0), temperature(TEMPERATURA_AMBIENTE_SATURNO) {
        momentInercia = 0.5f * mass * radius * radius;
    }

    void aplicarGravedad() {
        acceleration.y += GRAVEDAD_SATURNO;  
    }

    void aplicarFriccion() {
        if (position.y <= PISO_Y + radius && velocity.magnitude() > 0) {
            // Fricción atmosférica en Saturno
            Vector2D friccion = velocity;
            friccion.normalize();
            velocity = velocity - friccion * FRICCION_SUELO_SATURNO;
        }
    }

    void mover() {
        velocity = velocity + acceleration * DELTA_TIME;  
        position = position + velocity * DELTA_TIME;    

        if (position.y <= PISO_Y + radius) {
            position.y = PISO_Y + radius;  
            velocity.y = -velocity.y * elasticity; 
            aplicarFriccion();  
        }
        
        angle += angularVelocity.x * DELTA_TIME;
    }

    bool colision(ObjetoFisico& otro) {
        float distancia = std::sqrt(std::pow(position.x - otro.position.x, 2) + std::pow(position.y - otro.position.y, 2));
        return distancia < (radius + otro.radius);
    }

    void resolverColision(ObjetoFisico& otro) {
        if (colision(otro)) {
            Vector2D direccion = position - otro.position;
            direccion.normalize();

            Vector2D velocidadRelativa = velocity - otro.velocity;
            float velocidadRelativaDot = velocidadRelativa.dot(direccion);
            
            if (velocidadRelativaDot > 0) return;
            
            float coef = (1 + elasticity) / (mass + otro.mass);
            Vector2D impulso = direccion * velocidadRelativaDot * coef;
            
            velocity = velocity - impulso * otro.mass;
            otro.velocity = otro.velocity + impulso * mass;
        }
    }
};

int main() {

    ObjetoFisico pelota1(100, 100, 1.0f, 10);
    ObjetoFisico pelota2(150, 100, 1.0f, 10);

    for (int i = 0; i < 1000; ++i) {
        pelota1.aplicarGravedad();
        pelota2.aplicarGravedad();

        pelota1.mover();
        pelota2.mover();

        pelota1.resolverColision(pelota2);


        std::cout << "Pelota 1: (" << pelota1.position.x << ", " << pelota1.position.y << "), Temp: " << pelota1.temperature << "°C\n";
        std::cout << "Pelota 2: (" << pelota2.position.x << ", " << pelota2.position.y << "), Temp: " << pelota2.temperature << "°C\n";
    }

    return 0;
}
