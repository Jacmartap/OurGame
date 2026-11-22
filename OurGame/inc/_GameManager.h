#ifndef _MENU_H
#define _MENU_H

#include <_PRLX.h>
#include <_Player.h>
#include <_Enemy.h>
#include <_Model.h>
#include <_Quad.h>
#include <_SkyBox.h>
#include <_Sounds.h>
#include <vector>

#define numEnms 5

class _GameManager
{
    public:
        _GameManager();
        virtual ~_GameManager();

        _PRLX* titleScreen = new _PRLX();
        _PRLX* menuScreen = new _PRLX();
        _PRLX* howToPlayScreen = new _PRLX();
        _PRLX* gameBgScreen = new _PRLX();
        
        _Quad* pausePopup = new _Quad(0, 0, 7.58001, 0, 0, 0, 0.45, 0.25, 0.0, 1.0);

        _Player* exoMan = new _Player();           // The Player
        _Enemy myEnms[numEnms];                    // The Enemies

        _SkyBox* mySky = new _SkyBox();

        _Sounds* menuSounds = new _Sounds();

        void initMenu();
        void activateMenu(float, float, float);
        void doGameplay(float);
        void update();

        bool gameActive = true;

        enum {titlePage, mainMenu, howToPlay, paused, gameBG};
        enum {LANDING, MAIN_MENU, HOW_TO_PLAY, PAUSED_GAME, IN_GAME};

        int currentScreen;
        int currentState;

        struct button
        {
            _Quad sprite;

            float xPos = -1;
            float yPos = -1;
            float zPos = -1;

            float width = -1;
            float height = -1;
            
            int screen = -1;
        };

        button startButton;
        button helpButton;
        button exitButton;

        vector<button> buttons = { startButton, helpButton, exitButton };

        void drawButtons();
        bool buttonColliding(int index);

        vec2 buttonScale = { 1.0, 1.0 };
        vec2 mousePos;

        bool mouseClicked = false;

        int levelID = 1;

        ///////////////////////////////////////// Level 1 /////////////////////////////////////////////////
        _Model* lv1floor = new _Model(0.0, -3.1, -9.0, 10.0, 3.0, 10.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0);

        _Model* lv1crate1 = new _Model(0.0, 1.0, -5.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0);
        _Model* lv1crate2 = new _Model(-5.0, 1.0, -12.0, 1.0, 1.0, 1.0, 0.0, 45.0, 0.0, 1.0, 1.0, 1.0, 1.0);
        _Model* lv1crate3 = new _Model(5.0, 1.0, -12.0, 1.0, 1.0, 1.0, 0.0, -45.0, 0.0, 1.0, 1.0, 1.0, 1.0);
        ///////////////////////////////////////////////////////////////////////////////////////////////////


        ///////////////////////////////////////// Level 2 /////////////////////////////////////////////////
        _Model* lv2floor = new _Model(0.0, -3.0, -9.0, 12.0, 3.0, 12.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0);

        _Model* lv2wall1 = new _Model(3.0, 1.5, -5.0, 9.0, 1.5, 0.8, 0.0, 0.0, 180.0, 1.0, 1.0, 1.0, 1.0);
        _Model* lv2wall2 = new _Model(-3.0, 1.5, -12.0, 9.0, 1.5, 0.8, 0.0, 0.0, 180.0, 1.0, 1.0, 1.0, 1.0);
        _Model* lv2wall3 = new _Model(3.0, 1.5, -20.0, 9.0, 1.5, 0.8, 0.0, 0.0, 180.0, 1.0, 1.0, 1.0, 1.0);

        _Model* lv2crate1 = new _Model(-7.0, 0.8, -0.75, 0.8, 0.8, 0.8, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0);
        _Model* lv2crate2 = new _Model(5.0, 1.0, -7.5, 1.0, 1.0, 1.0, 0.0, 30.0, 0.0, 1.0, 1.0, 1.0, 1.0);
        _Model* lv2crate3 = new _Model(-3.0, 0.6, -16.0, 0.6, 0.6, 1.0, 0.0, 30.0, 0.0, 1.0, 1.0, 1.0, 1.0);
        ///////////////////////////////////////////////////////////////////////////////////////////////////


        ///////////////////////////////////////// Level 3 /////////////////////////////////////////////////
        _Model* lv3floor = new _Model(0.0, -3.0, -9.0, 13.0, 3.0, 13.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0);

        _Model* lv3wall1 = new _Model(5.3, 1.5, -6.0, 10.0, 1.5, 0.8, 0.0, 90.0, 180.0, 1.0, 1.0, 1.0, 1.0);
        _Model* lv3wall2 = new _Model(-1.5, 1.5, -11.0, 6.0, 1.5, 0.8, 0.0, 0.0, 180.0, 1.0, 1.0, 1.0, 1.0);
        _Model* lv3wall3 = new _Model(0.0, 1.5, -21.2, 13.0, 1.5, 0.8, 0.0, 0.0, 180.0, 1.0, 1.0, 1.0, 1.0);

        _Model* lv3crate1 = new _Model(-9.0, 1.25, 1.0, 1.25, 1.25, 1.25, 0.0, 55.0, 0.0, 1.0, 1.0, 1.0, 1.0);
        _Model* lv3crate2 = new _Model(-1.0, 1.25, -5.5, 1.25, 1.25, 1.25, 0.0, 30.0, 0.0, 1.0, 1.0, 1.0, 1.0);
        _Model* lv3crate3 = new _Model(-5.0, 0.6, -14.5, 0.6, 0.6, 1.0, 0.0, -30.0, 0.0, 1.0, 1.0, 1.0, 1.0);
        _Model* lv3crate4 = new _Model(1.0, 0.6, -17.5, 0.6, 0.6, 0.6, 0.0, 30.0, 0.0, 1.0, 1.0, 1.0, 1.0);
        _Model* lv3crate5 = new _Model(9.5, 0.6, -8.0, 5.0, 0.6, 0.6, 0.0, 90.0, 0.0, 1.0, 1.0, 1.0, 1.0);
        ///////////////////////////////////////////////////////////////////////////////////////////////////

    protected:

    private:
};

#endif // _MENU_H
