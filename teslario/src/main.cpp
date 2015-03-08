#include <iostream>
#include "tesla.h"

int main(int argc, const char * argv[]) {
    
    auto director = tesla::Director::getInstance();
    director->initOpenGL(0.8*tesla::Director::DEFAULT_WIDTH, 0.8*tesla::Director::DEFAULT_HEIGHT);
    director->run();
    
    return 0;
}
