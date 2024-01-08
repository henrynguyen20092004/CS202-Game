#include <iostream>

#include "src/Program/Program.hpp"

int main() {
    try {
        Program program;
        program.run();
    } catch (std::exception& e) {
        std::cout << "EXCEPTION: " << e.what() << '\n';
    }

    return 0;
}
