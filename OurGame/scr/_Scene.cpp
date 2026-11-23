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

        GM->initMenu();

        GM->mySky->initSkyBox();

        GM->mySky->myTex[0].loadTexture("images/nz.png"); // Front
        GM->mySky->myTex[1].loadTexture("images/pz.png"); // Back
        GM->mySky->myTex[2].loadTexture("images/py.png"); // Top
        GM->mySky->myTex[3].loadTexture("images/ny.png"); // Bottom
        GM->mySky->myTex[4].loadTexture("images/nx.png"); // Left
        GM->mySky->myTex[5].loadTexture("images/px.png"); // Right

        myCam->camInit();

        GM->exoMan->initPlayer("models/Player/Player_Idle.fbx", "models/Player/BODY_Diffuse.png","models/Player/EXO_diffuse.png", GM->exoMan->IDLE);        // The new player models, and floor + crates
        GM->exoMan->initPlayer("models/Player/Player_Run.fbx", "models/Player/BODY_Diffuse.png", "models/Player/EXO_diffuse.png", GM->exoMan->RUN);
        GM->exoMan->initPlayer("models/Player/Player_Punch.fbx", "models/Player/BODY_Diffuse.png", "models/Player/EXO_diffuse.png", GM->exoMan->PUNCH);
        GM->exoMan->initPlayer("models/Player/Player_Defeat.fbx", "models/Player/BODY_Diffuse.png", "models/Player/EXO_diffuse.png", GM->exoMan->DEFEAT);

        GM->lv1floor->initModel("images/floor.jpg");
        GM->lv1crate1->initModel("images/crate.png");
        GM->lv1crate2->initModel("images/crate.png");
        GM->lv1crate3->initModel("images/crate.png");

        GM->lv2floor->initModel("images/floor.jpg");
        GM->lv2wall1->initModel("images/wall.jpg");
        GM->lv2wall2->initModel("images/wall.jpg");
        GM->lv2wall3->initModel("images/wall.jpg");
        GM->lv2crate1->initModel("images/crate.png");
        GM->lv2crate2->initModel("images/crate.png");
        GM->lv2crate3->initModel("images/crate.png");

        GM->lv3floor->initModel("images/floor.jpg");
        GM->lv3wall1->initModel("images/wall.jpg");
        GM->lv3wall2->initModel("images/wall.jpg");
        GM->lv3wall3->initModel("images/wall.jpg");
        GM->lv3crate1->initModel("images/crate.png");
        GM->lv3crate2->initModel("images/crate.png");
        GM->lv3crate3->initModel("images/crate.png");
        GM->lv3crate4->initModel("images/crate.png");
        GM->lv3crate5->initModel("images/crate.png");
    
                                          //Ignoring the zombies just for now - Jacob
        for (int i = 0; i < numEnms; i++)
        {
            GM->myEnms[i].initEnms("models/Zombie/Zombie_Idle.fbx", "models/Zombie/BODY_Diffuse.png", GM->myEnms[i].IDLE);
            GM->myEnms[i].initEnms("models/Zombie/Zombie_Running.fbx", "models/Zombie/BODY_Diffuse.png", GM->myEnms[i].RUN);
            GM->myEnms[i].initEnms("models/Zombie/Zombie_Attack.fbx", "models/Zombie/BODY_Diffuse.png", GM->myEnms[i].ATTACK);
            GM->myEnms[i].initEnms("models/Zombie/Zombie_Die.fbx", "models/Zombie/BODY_Diffuse.png", GM->myEnms[i].DIE);

            GM->myEnms[i].actionTrigger = (2);
        }
    
        myLight->setLight(GL_LIGHT0);

        gameMusic->initSnds();

        gameMusic->playMusic("sounds/Dead Wrong - Jeremy Blake.mp3");

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

        float aspectRatio = (GLfloat)dimX / (GLfloat)dimY; // To maintain graphics in size

        auto currentTime = chrono::steady_clock::now();
        chrono::duration<float>elapse = currentTime - lastTime;
        _Scene::deltaT = elapse.count();
        lastTime = currentTime;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        if (GM->currentState == GM->IN_GAME)
        {
            gluPerspective(45, aspectRatio, 0.1, 100.0);
        }
        else
        {
            glOrtho(-dimX / dimY, dimX / dimY, -1.0, 1.0, -20.0, 20.0);
        }

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        if (GM->currentState == GM->IN_GAME)
        {
            myCam->des = GM->exoMan->pos; // Camera points to the camera at all times - Jacob
            myCam->des.y += 2.0;          // Puts camera a bit higher (don't change) - Jacob
            myCam->SetupCam();
            myCam->rotateXY();

            myKbMs->keyPressed(GM->exoMan, myCam, deltaT);
        }

        myLight->placeLight();                  // Lighting gets placed - Jacob

        GM->activateMenu(dimX, dimY, deltaT);

        GM->update();
    }

    int _Scene::WndMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_KEYDOWN:
            myKbMs->wparam = wParam;

            if (GM->currentState == GM->IN_GAME)
            {
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

                if (myKbMs->wparam == VK_ESCAPE)
                {
                    if ((lParam & 0x40000000) == 0)
                    {
                        myKbMs->keyPressed(GM);
                    }
                }
            }
            else
            {
                myKbMs->keyPressed(GM);
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

            if (GM->currentState == GM->IN_GAME)
            {
                // DO NOTHING
            }
            else
            {
                GM->mouseClicked = false;
            }

        
            break;

        case WM_LBUTTONDOWN:
            myKbMs->wparam = wParam;        // Allows player and camera to detect left and right clicks - Kyle  
            
            if (GM->currentState == GM->IN_GAME)
            {
                myKbMs->mouseEventDown(myCam, LOWORD(lParam), HIWORD(lParam));
                myKbMs->mouseEventDown(GM->exoMan, LOWORD(lParam), HIWORD(lParam));
            }
            else
            {
                GM->mouseClicked = true;

                mouseMapping(LOWORD(lParam), HIWORD(lParam));

                GM->mousePos.x = mouse.x;
                GM->mousePos.y = mouse.y;
            }

            break;

        case WM_RBUTTONDOWN: 
            myKbMs->wparam = wParam;

            if (GM->currentState == GM->IN_GAME)
            {
                myKbMs->mouseEventDown(myCam, LOWORD(lParam), HIWORD(lParam));
                myKbMs->mouseEventDown(GM->exoMan, LOWORD(lParam), HIWORD(lParam));
            }

            break;
    
        case WM_LBUTTONUP: 
        case WM_RBUTTONUP:
            myKbMs->wparam = wParam;

            GM->mouseClicked = false;

            break;
    
        case WM_MOUSEWHEEL:
            if (GM->currentState == GM->IN_GAME)
            {
                myKbMs->mouseWheel(myMdl, (double)GET_WHEEL_DELTA_WPARAM(wParam));
            }
            break;
    
        case WM_MOUSEMOVE:
            if (GM->currentState == GM->IN_GAME)
            {
                myKbMs->mouseMove(myCam, LOWORD(lParam), HIWORD(lParam));
            }
            else
            {
                mouseMapping(LOWORD(lParam), HIWORD(lParam));

                GM->mousePos.x = mouse.x;
                GM->mousePos.y = mouse.y;
            }

            break;
        }
    
        return 0;
    }


    void _Scene::mouseMapping(int x, int y)
    {
        GLint viewPort[4];
        GLdouble modelViewM[16];
        GLdouble projectionM[16];

        GLfloat winX, winY, winZ;

        glGetDoublev(GL_MODELVIEW_MATRIX, modelViewM);
        glGetDoublev(GL_PROJECTION_MATRIX, projectionM);
        glGetIntegerv(GL_VIEWPORT, viewPort);

        winX = GLfloat(x);
        winY = GLfloat(viewPort[3] - y - 1);

        glReadPixels(int(winX), int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

        gluUnProject(winX, winY, winZ, modelViewM, projectionM, viewPort, &mouse.x, &mouse.y, &mouse.z);
    }



