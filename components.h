#include <string>

struct Position {
    Position(double x, double y): x(x), y(y) {}
    double x;
    double y;
};

struct ChangeWorldEvent {
    std::string world;
};

struct Velocity {
    Velocity(double x, double y): x(x), y(y) {}
    double x;
    double y;
};

struct Color {
    Color(double r, double g, double b): r(r), g(g), b(b) {}
    double r;
    double g;
    double b;
};

struct Sprite {
    Sprite(double w, double h): w(w), h(h) {}
    double w;
    double h;
};
