# CplusplusTest


## Black Hole Simulation (C++)

A simple physics inspired simulation of particles being attracted into a black hole using Newtonian gravity.

---

## Code

```cpp
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

    double force = (G * BH_MASS) / (r * r);

    double ax = -force * (p.x / r);
    double ay = -force * (p.y / r);

    p.vx += ax * DT;
    p.vy += ay * DT;

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
        p.vy = 1000;
        p.alive = true;
        particles.push_back(p);
    }

    for (int t = 0; t < 500; t++) {
        cout << "Step " << t << endl;

        for (auto &p : particles) {
            if (p.alive) {
                updateParticle(p);
                cout << "Particle: (" << p.x << ", " << p.y << ")\n";
            }
        }

        cout << "----------------------\n";
    }

    return 0;
}
