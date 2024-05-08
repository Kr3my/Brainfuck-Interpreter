#include <iostream>
#include "src/interpreter.hpp"

int main(int argc, char* argv[]) {
    if(argc > 1) {
        std::string path(argv[1]);
        std::string buffer;

        if(!Interpreter::readFile(path, buffer)) {
            std::cerr << "An error occurred while trying to open the file" << std::endl;
            exit(EXIT_FAILURE);
        }

        Interpreter::execute(buffer);
    }

    return EXIT_SUCCESS;
}