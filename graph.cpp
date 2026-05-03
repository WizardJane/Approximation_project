#include <iostream>
// #include <cmath>
// #include <vector>
#include <matplot/matplot.h>

int main() {
    using namespace matplot;
    std::vector<double> x = linspace(0, 2 * pi);
    std::vector<double> y = transform(x, [](auto x) { return sin(x); });
    
//    plot(x, y, "-o");
//    hold(on);
    // plot(x, transform(y, [](auto y) { return -y; }), "--xr");
    // plot(x, transform(x, [](auto x) { return x / pi - 1.; }), "-:gs");
    plot({1.0, 0.7, 0.4, 0.0, -0.4, -0.7, -1}, "k");
    plot(x, y, "-o")->marker_indices({0,  5,  10, 15, 20, 25, 30, 35, 40, 45,
                                          50, 55, 60, 65, 70, 75, 80, 85, 90, 95});
    
    show();
    return 0;
    
    
}

// int main() {
//     std::cout << "Hello world";
//     return 0;
// }