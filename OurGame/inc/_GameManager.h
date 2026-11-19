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

        _Model* floor = new _Model(0.0, -3.1, -9.0, 10.0, 3.0, 10.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0);         // Creating and placing objects;
        _Model* crate1 = new _Model(0.0, 1.0, -5.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0);           //
        _Model* crate2 = new _Model(-5.0, 1.0, -12.0, 1.0, 1.0, 1.0, 0.0, 45.0, 0.0, 1.0, 1.0, 1.0, 1.0);        //
        _Model* crate3 = new _Model(5.0, 1.0, -12.0, 1.0, 1.0, 1.0, 0.0, -45.0, 0.0, 1.0, 1.0, 1.0, 1.0);        //

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

    protected:

    private:
};

#endif // _MENU_H
