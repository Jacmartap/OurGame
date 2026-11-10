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

    mySky->myTex[0].loadTexture("images/sky/nz.png"); // Front
    mySky->myTex[1].loadTexture("images/sky/pz.png"); // Back
    mySky->myTex[2].loadTexture("images/sky/py.png"); // Top
    mySky->myTex[3].loadTexture("images/sky/ny.png"); // Bottom
    mySky->myTex[4].loadTexture("images/sky/nx.png"); // Left
    mySky->myTex[5].loadTexture("images/sky/px.png"); // Right

    myCam->camInit();

    myPlayer->initPlayer("models/Soldier/Idle.fbx", "models/Soldier/Ch49_1001_Diffuse.png", 0);
    myPlayer->initPlayer("models/Soldier/Running.fbx", "models/Soldier/Ch49_1001_Diffuse.png", 1);
    myPlayer->initPlayer("models/Soldier/Jump.fbx", "models/Soldier/Ch49_1001_Diffuse.png", 2);
    myPlayer->initPlayer("models/Soldier/Crouch.fbx", "models/Soldier/Ch49_1001_Diffuse.png", 3);
    myPlayer->initPlayer("models/Soldier/Cartwheeling.fbx", "models/Soldier/Ch49_1001_Diffuse.png", 4);
    
    /*                                     Ignoring the zombies just for now - Jacob
    for (int i = 0; i < numEnms; i++)
    {
        myEnms[i].initEnms("models/Zombie/Zombie_Idle.fbx", "models/Zombie/Ch10_1001_Diffuse.png", 0);
        myEnms[i].initEnms("models/Zombie/Zombie_Running.fbx", "models/Zombie/Ch10_1001_Diffuse.png", 1);
        myEnms[i].initEnms("models/Zombie/Zombie_Attack.fbx", "models/Zombie/Ch10_1001_Diffuse.png", 2);
        myEnms[i].initEnms("models/Zombie/Zombie_Left_Strafe.fbx", "models/Zombie/Ch10_1001_Diffuse.png", 3);
        myEnms[i].initEnms("models/Zombie/Zombie_Right_Strafe.fbx", "models/Zombie/Ch10_1001_Diffuse.png", 4);
        myEnms[i].initEnms("models/Zombie/Zombie_Die.fbx", "models/Zombie/Ch10_1001_Diffuse.png", 5);
    }
    */
    
    //myLight->setLight(GL_LIGHT0);              //Ignoring Light For Now - Jacob

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

    myCam->des.x = myPlayer->pos.x;
    myCam->des.y = myPlayer->pos.y + 1.0;
    myCam->des.z = myPlayer->pos.z;

    myCam->rotateXY();
    
    myCam->SetupCam();
    mySky->drawSkyBox();
    myLight->moveLight(deltaT);

    myKbMs->isMsRotate = true;

    glPushMatrix();                         // Start grouping matrix
    myPlayer->drawPlayer(deltaT);
    glPopMatrix();                          // End grouping matrix
    
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

        if (myKbMs->wparam == 0x57) myKbMs->forward = true;          // To detect key presses - Jacob
        if (myKbMs->wparam == 0x53) myKbMs->backward = true;
        if (myKbMs->wparam == 65) myKbMs->left = true;
        if (myKbMs->wparam == 68) myKbMs->right = true;

        //myKbMs->keyPressed(myCam);
        break;
    
    case WM_KEYUP:
        myKbMs->wparam = wParam;

        if (myKbMs->wparam == 0x57) myKbMs->forward = false;         // To detect key letting go - Jacob
        if (myKbMs->wparam == 0x53) myKbMs->backward = false;
        if (myKbMs->wparam == 65) myKbMs->left = false;
        if (myKbMs->wparam == 68) myKbMs->right = false;
        break;

    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN: 
        myKbMs->wparam = wParam;
        //myKbMs->mouseEventDown(myCam, LOWORD(lParam), HIWORD(lParam));
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





