#include "_Scene.h"

auto lastTime = chrono::steady_clock::now(); // Initiate timer

_Scene::_Scene() {}     // Constructor

_Scene:: ~_Scene()      // Destructor
{
    delete myMdl;
}   
 
GLint _Scene::initGL()
{
    glewInit();                     // Initialize glew
    glClearColor(0.0,0.0,0.0,1.0);  // Background color
    glClearDepth(1.0);              // Clear depth values

    glEnable(GL_DEPTH_TEST);        // Enable depth Test
    glDepthFunc(GL_LEQUAL);         // Type of depth to be performed

    glEnable(GL_LIGHTING);          // Enable light settings
    glEnable(GL_LIGHT0);            // Enable light channel 0

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);    // Enable color

    mySky->initSkyBox();

    mySky->myTex[0].loadTexture("images/nz.png"); // Front
    mySky->myTex[1].loadTexture("images/pz.png"); // Back
    mySky->myTex[2].loadTexture("images/py.png"); // Top
    mySky->myTex[3].loadTexture("images/ny.png"); // Bottom
    mySky->myTex[4].loadTexture("images/nx.png"); // Left
    mySky->myTex[5].loadTexture("images/px.png"); // Right

    myCam->camInit();

    myPlayer->initPlayer("models/Player/Player_Idle.fbx", "models/Player/BODY_Diffuse.png","models/Player/EXO_diffuse.png", myPlayer->IDLE);        // The new player models, and floor + crates
    myPlayer->initPlayer("models/Player/Player_Run.fbx", "models/Player/BODY_Diffuse.png", "models/Player/EXO_diffuse.png", myPlayer->RUN);
    myPlayer->initPlayer("models/Player/Player_Punch.fbx", "models/Player/BODY_Diffuse.png", "models/Player/EXO_diffuse.png", myPlayer->PUNCH);
    myPlayer->initPlayer("models/Player/Player_Defeat.fbx", "models/Player/BODY_Diffuse.png", "models/Player/EXO_diffuse.png", myPlayer->DEFEAT);

    floor->initModel("images/floor.jpg");
    crate1->initModel("images/crate.png");
    crate2->initModel("images/crate.png");
    crate3->initModel("images/crate.png");
    
    /*                                   //Ignoring the zombies just for now - Jacob
    for (int i = 0; i < numEnms; i++)
    {
        myEnms[i].initEnms("models/Zombie/Zombie_Idle.fbx", "models/Zombie/BODY_Diffuse.png", myEnms[i].IDLE);
        myEnms[i].initEnms("models/Zombie/Zombie_Running.fbx", "models/Zombie/BODY_Diffuse.png", myEnms[i].RUN);
        myEnms[i].initEnms("models/Zombie/Zombie_Attack.fbx", "models/Zombie/BODY_Diffuse.png", myEnms[i].ATTACK);
        myEnms[i].initEnms("models/Zombie/Zombie_Die.fbx", "models/Zombie/BODY_Diffuse.png", myEnms[i].DIE);
    }
    */
    
    myLight->setLight(GL_LIGHT0);

    return TRUE;
}

float _Scene::deltaT = 0;

void _Scene::reSize(GLint width, GLint height)
{
    float aspectRatio = (GLfloat)width / (GLfloat) height; // To maintain graphics in size

    glViewport(0, 0, width, height); // Set viewing window
    glMatrixMode(GL_PROJECTION);     // Set correct projection in the scene
    glLoadIdentity();                // Reset matrices

    gluPerspective(45, aspectRatio, 0.1, 100.0);    // Settings of the projection
    glMatrixMode(GL_MODELVIEW);                     // Set forward model matrix and view matrix
    glLoadIdentity();

    dimX = GetSystemMetrics(SM_CXSCREEN);
    dimY = GetSystemMetrics(SM_CYSCREEN);
}

void _Scene::drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth
    
    glLoadIdentity();

    auto currentTime = chrono::steady_clock::now();
    chrono::duration<float>elapse = currentTime - lastTime;
    _Scene::deltaT = elapse.count();
    lastTime = currentTime;
    
    myKbMs->keyPressed(myPlayer, myCam, deltaT);

    myCam->des = myPlayer->pos; // Camera points to the camera at all times - Jacob
    myCam->des.y += 2.0;        // Puts camera a bit higher (don't change) - Jacob
    
    myCam->SetupCam();
    myCam->rotateXY();
    
    mySky->drawSkyBox();

    myLight->placeLight();                  // Lighting gets placed - Jacob

    glPushMatrix();                         // Start grouping matrix
    myPlayer->drawPlayer(deltaT);
    glPopMatrix();                          // End grouping matrix

    glPushMatrix();
    floor->drawModel();
    crate1->drawModel();
    crate2->drawModel();
    crate3->drawModel();
    glPopMatrix();
    
    /*                                     Ignoring the zombies just for now - Jacob
    for (int i = 0; i < numEnms; i++)
    {
        glPushMatrix();
        glTranslatef((i * 1.0), 0.0, 0.0);
        myEnms[i].drawEnms(deltaT);
        glPopMatrix();
    }
    */
}

int _Scene::WndMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_KEYDOWN:
        myKbMs->wparam = wParam;
        
        if (myKbMs->wparam == 0x57)         // To detect key presses - Jacob
        {
            myKbMs->forward = true;
        }

        if (myKbMs->wparam == 0x53)
        {
            myKbMs->backward = true;
        }

        if (myKbMs->wparam == 65)
        {
            myKbMs->left = true;
        }
        
        if (myKbMs->wparam == 68)
        {
            myKbMs->right = true;
        }
        
        break;
    
    case WM_KEYUP:
        myKbMs->wparam = wParam;

        if (myKbMs->wparam == 0x57)         // To detect letting go of key - Jacob
        {
            myKbMs->forward = false;
        }

        if (myKbMs->wparam == 0x53)
        {
            myKbMs->backward = false;
        }

        if (myKbMs->wparam == 65)
        {
            myKbMs->left = false;
        }

        if (myKbMs->wparam == 68)
        {
            myKbMs->right = false;
        }
        
        break;

    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN: 
        myKbMs->wparam = wParam;
        myKbMs->mouseEventDown(myCam, LOWORD(lParam), HIWORD(lParam));
        break;
    
    case WM_LBUTTONUP: 
    case WM_RBUTTONUP:
        myKbMs->wparam = wParam;
        //myKbMs->mouseEventUp();
        break;
    
    case WM_MOUSEWHEEL:
        myKbMs->mouseWheel(myMdl, (double)GET_WHEEL_DELTA_WPARAM(wParam));
        break;
    
    case WM_MOUSEMOVE:
       myKbMs->mouseMove(myCam, LOWORD(lParam), HIWORD(lParam));
        break;
    }
    
    return 0;
}





