# CplusplusTest

#include <iostream>
using namespace std;

int main() {
    // This statement prints "Hello World"
    cout << "Hello World";

    return 0;
}



# Black Hole Simulation here 🤞


#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double G = 6.67430e-11;  
const double BH_MASS = 1e30;    
const double EVENT_HORIZON = 50.0; 
const double DT = 0.1;          

struct Particle {
    double x, y;
    double vx, vy;
    bool alive;
};



double distance(double x, double y) {
    return sqrt(x*x + y*y);
}


void updateParticle(Particle &p) {
    double r = distance(p.x, p.y);

    if (r < EVENT_HORIZON) {
        p.alive = false;
        return;
    }

    // Gravitational force magnitude
    double force = (G * BH_MASS) / (r * r);

    // Direction towards center
    double ax = -force * (p.x / r);
    double ay = -force * (p.y / r);

    // Update velocity
    p.vx += ax * DT;
    p.vy += ay * DT;

    // Update position
    p.x += p.vx * DT;
    p.y += p.vy * DT;
}


int main() {
    vector<Particle> particles;

    
    for (int i = 0; i < 10; i++) {
        Particle p;
        p.x = 200 + i * 20;
        p.y = 0;
        p.vx = 0;
        p.vy = 1000; // initial tangential velocity
        p.alive = true;
        particles.push_back(p);
    }
