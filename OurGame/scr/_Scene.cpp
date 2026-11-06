#include "_Scene.h"

auto lastTime = chrono::steady_clock::now(); // Initiate Timer

_Scene::_Scene() {}     // Constructor

_Scene:: ~_Scene()
{
    delete myMdl;
}   //destructor
 
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
    glEnable(GL_COLOR_MATERIAL);    // Enable Color
    myMdl->initModel("images/skin.jpg");

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
    myPlayer->initPlayer("models/Soldier/Jumping.fbx", "models/Soldier/Ch49_1001_Diffuse.png", 2);
    myPlayer->initPlayer("models/Soldier/Crouching.fbx", "models/Soldier/Ch49_1001_Diffuse.png", 3);
    myPlayer->initPlayer("models/Soldier/Cartwheel.fbx", "models/Soldier/Ch49_1001_Diffuse.png", 4);
    
    /*
    for (int i = 0; i < numEnms; i++)
    {
        myEnms[i].initEnms("models/Zombie/Zombie Idle.fbx", "models/Zombie/Ch10_1001_Diffuse.png", 0);
        myEnms[i].initEnms("models/Zombie/Zombie Running.fbx", "models/Zombie/Ch10_1001_Diffuse.png", 1);
        myEnms[i].initEnms("models/Zombie/Zombie Attack.fbx", "models/Zombie/Ch10_1001_Diffuse.png", 2);
        myEnms[i].initEnms("models/Zombie/Zombie Left Strafe.fbx", "models/Zombie/Ch10_1001_Diffuse.png", 3);
        myEnms[i].initEnms("models/Zombie/Zombie Right Strafe.fbx", "models/Zombie/Ch10_1001_Diffuse.png", 4);
        myEnms[i].initEnms("models/Zombie/Zombie Death.fbx", "models/Zombie/Ch10_1001_Diffuse.png", 5);
    }
    */
    
    myLight->setLight(GL_LIGHT0);

    return TRUE;
}

float _Scene::deltaT = 0;

void _Scene::reSize(GLint width, GLint height)
{
    float aspectRatio = (GLfloat)width / (GLfloat) height; //to maintain graphics in size

    glViewport(0, 0, width, height); // set viewing window
    glMatrixMode(GL_PROJECTION);     // set correct projection in the scene
    glLoadIdentity();                // reset matrices

    gluPerspective(45, aspectRatio, 0.1, 100.0);//settings of the projection
    glMatrixMode(GL_MODELVIEW);     // set up model matrix and view matrix
    glLoadIdentity();

    dimX = GetSystemMetrics(SM_CXSCREEN);
    dimY = GetSystemMetrics(SM_CYSCREEN);
}

void _Scene::drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear color and depth
    glLoadIdentity();

    auto currentTime = chrono::steady_clock::now();
    chrono::duration<float>elapse = currentTime - lastTime;
    _Scene::deltaT = elapse.count();
    lastTime = currentTime;
    
    myCam->SetupCam();
    mySky->drawSkyBox();
    myLight->moveLight(deltaT);

    glPushMatrix();                     // start grouping matrix
    glTranslatef(0.0, -1.0, 0.0);
    myPlayer->drawPlayer(deltaT);
    glPopMatrix();                      // end grouping matrix

    /*
    for (int i = 0; i < numEnms; i++)
    {
        glPushMatrix();
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
        myKbMs->keyPressed(myCam);
        myKbMs->keyPressed(myPlayer);
        break;
    
    case WM_KEYUP: break;

    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN: 
        myKbMs->wparam = wParam; 
        break;
    
    case WM_LBUTTONUP: 
    case WM_RBUTTONUP:
        myKbMs->mouseEventUp();
        break;
    
    case WM_MOUSEWHEEL:
        myKbMs->mouseWheel(myMdl, (double)GET_WHEEL_DELTA_WPARAM(wParam));
        break;
    
    case WM_MOUSEMOVE:
        
        break;
    }
    
    return 0;
}

// THIS IS A TEXT COMMENT FOR GITHUB