#pragma once

#include <iostream>
#include <fstream>
#include <vector>

class Interpreter {
    public:
    static bool readFile(std::string& path, std::string& buffer) {
        std::ifstream file(path);

        if(file.is_open()) {
            buffer.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            file.close();

            return true;
        }

        return false;
    }

    static void execute(std::string& code) {
        std::vector<unsigned char> memory(30000, 0);
        int ptr = 0;

        int codePtr = 0;
        int codeLen = code.length();

        while(codePtr < codeLen) {
            char instruction = code[codePtr];

            switch(instruction) {
                case '>': ++ptr; break;
                case '<': --ptr; break;
                case '+': ++memory[ptr]; break;
                case '-': --memory[ptr]; break;
                case '.': std::cout.put(memory[ptr]); break;
                case ',': memory[ptr] = std::cin.get(); break;
                case '[':
                if(memory[ptr] == 0) {
                    int loopCount = 1;

                    while(loopCount > 0) {
                        ++codePtr;
                        
                        if(code[codePtr] == '[') {
                            ++loopCount;

                        } else if(code[codePtr] == ']') {
                            --loopCount;
                        }
                    }
                }

                break;

                case ']':
                if(memory[ptr] != 0) {
                    int loopCount = 1;

                    while(loopCount > 0) {
                        --codePtr;

                        if(code[codePtr] == ']') {
                            ++loopCount;

                        } else if(code[codePtr] == '[') {
                            --loopCount;
                        }
                    }
                }

                break;
                default: break;
            }

            ++codePtr;
        }
    }
};