#pragma once

#include <_Common.h>
#include <_Model.h>
#include <_KbMs.h>
#include <_TxtLoader.h>
#include <_SkyBox.h>
#include <_Camera.h>
#include <_PRLX.h>
#include <_ModelLoader.h>
#include <_LightSetup.h>
#include <_Enemy.h>
#include <_Player.h>
#include <chrono>

#define numEnms 5

class _Scene
{
    public:
        _Scene();
       virtual ~_Scene();

       _Model* myMdl = new _Model();
       _KbMs* myKbMs = new _KbMs();
       _SkyBox* mySky = new _SkyBox();
       _Camera* myCam = new _Camera();
       _PRLX* myPRLX = new _PRLX();
       _ModelLoader* my3DModel = new _ModelLoader();
       _LightSetup* myLight = new _LightSetup();
       _Player* myPlayer = new _Player(); // With Multiple Actions

       float plyrPosX = 0;
       float plyrPosZ = 0;

       _Enemy myEnms[numEnms];

       float dimX;
       float dimY;

       GLint initGL();
       void reSize(GLint width, GLint Height);
       void drawScene();
       int WndMsg(
           HWND	hWnd,			// Handle For This Window
           UINT	uMsg,			// Message For This Window
           WPARAM wParam,		// Additional Message Information
           LPARAM lParam);		// Additional Message Information

    static float deltaT;

private:
         


};

