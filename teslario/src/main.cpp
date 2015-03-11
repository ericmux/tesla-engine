#include <iostream>
#include "tesla.h"

int main(int argc, const char * argv[]) {

    int w,h;
    
    w = 0.8*tesla::Director::DEFAULT_WIDTH;
    h = 0.8*tesla::Director::DEFAULT_HEIGHT;
    
    auto director = tesla::Director::getInstance();
    director->initOpenGL(w,h);
    
    
    tesla::Texture* tex1 = new tesla::Texture("TeslaEngine/test/textures/octobiwan.jpg");
    tesla::Texture* tex2 = new tesla::Texture("TeslaEngine/test/textures/joff_pic.jpg");
    
    tesla::Sprite* sp1 = new tesla::Sprite(tex1);
    tesla::Sprite* sp2 = new tesla::Sprite(tex2);
    
    tesla::Sprite* sp3 = new tesla::Sprite(tex1);
    
    tesla::Scene* scene = new tesla::Scene();
    
    scene->addChild(sp1);
    scene->addChild(sp2);
    
    sp2->addChild(sp3);
    
    w = director->getDisplayWidthInPixels();
    h = director->getDisplayHeightInPixels();
    
    sp1->translate(glm::vec3(w/2,h/2,0.0f));
    sp1->scale(0.5f, 0.3f, 1.0f);
    
    
    sp2->translate(glm::vec3(0.0f,h/2,0.0f));
    sp2->scale(0.5f, 0.5f, 1.0f);
    
    sp3->translate(glm::vec3(50.0f,0.0f,0.0f));
    sp3->scale(0.3f);
    
    
    director->setCurrentScene(scene);
    
    director->run();
    
    // make descructors so it's possible to just do: delete scene.
    delete tex1;
    delete tex2;
    
    delete sp1;
    delete sp2;
    
    delete scene;
    
    
    return 0;
}
