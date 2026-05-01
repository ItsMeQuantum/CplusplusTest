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

const double G = 6.67430e-11;   // Gravitational constant
const double BH_MASS = 1e30;    // Mass of black hole
const double EVENT_HORIZON = 50.0; // Radius where particles disappear
const double DT = 0.1;          // Time step

struct Particle {
    double x, y;
    double vx, vy;
    bool alive;
};


