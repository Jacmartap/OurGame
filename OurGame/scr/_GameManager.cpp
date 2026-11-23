#include "_GameManager.h"

_GameManager::_GameManager()
{
    currentState = LANDING;
    currentScreen = titlePage;
}


_GameManager::~_GameManager()
{
    //dtor
}


////////////////////////////////// BUTTON RELATED LOGIC ////////////////////////////////////////
void _GameManager::drawButtons(vector<button>& buttons)                 // The new draw buttons function - Jacob
{
    glDisable(GL_LIGHTING);
    for (int i = 0; i < menuButtons.size();i++)
    {
        if (buttons[i].screen == currentState) {
            buttons[i].sprite.pos.x = buttons[i].xPos * buttonScale.x;
            buttons[i].sprite.pos.y = buttons[i].yPos * buttonScale.y;
            buttons[i].sprite.pos.z = buttons[i].zPos;
            buttons[i].sprite.scale.x = buttons[i].width * buttonScale.x;
            buttons[i].sprite.scale.y = buttons[i].height * buttonScale.y;

            buttons[i].sprite.drawQuad();

            glColor3f(1.0, 1.0, 1.0);
        }
    }
}


bool _GameManager::buttonColliding(int index, vector<button>& buttons)  // The new button collision function - Jacob
{
    float mouseDist = sqrt((mousePos.x - buttons[index].xPos * buttonScale.x) * (mousePos.x - buttons[index].xPos * buttonScale.x) + (mousePos.y - buttons[index].yPos * buttonScale.y) * (mousePos.y - buttons[index].yPos * buttonScale.y));

    float topSide = (buttons[index].yPos * buttonScale.y) + buttons[index].height;
    float bottomSide = (buttons[index].yPos * buttonScale.y) - buttons[index].height;
    float rightSide = (buttons[index].xPos * buttonScale.x) + buttons[index].width;
    float leftSide = (buttons[index].xPos * buttonScale.x) - buttons[index].width;

    bool withinRange = (mousePos.x >= leftSide && mousePos.x <= rightSide && mousePos.y >= bottomSide && mousePos.y <= topSide);

    if (withinRange) {
        buttons[index].sprite.brightness = 0.5;
    }
    else {
        buttons[index].sprite.brightness = 1.0;
    }

    return (withinRange && buttons[index].screen == currentState);
}

//////////////////////////////////////////////////////////////////////////////////////////////





////////////////////////////////// MENU RELATED LOGIC ////////////////////////////////////////
void _GameManager::initMenu()
{
    titleScreen->initPRLX("images/TitleScreen.png");
    menuScreen->initPRLX("images/MenuScreen.png");
    levelSelectScreen->initPRLX("images/levelSelectScreen.png");
    howToPlayScreen->initPRLX("images/HowToPlayScreen.png");
    
    pausePopup->initQuad("images/PausePop_Up.png");

    menuButtons[0].sprite.initQuad("images/ButtonStart.png");
    menuButtons[0].xPos = 0;
    menuButtons[0].yPos = 0.6;
    menuButtons[0].zPos = 7.58002;
    menuButtons[0].width = 0.5;
    menuButtons[0].height = 0.25;
    menuButtons[0].screen = mainMenu;


    menuButtons[1].sprite.initQuad("images/ButtonHelp.png");
    menuButtons[1].xPos = 0;
    menuButtons[1].yPos = 0.0;
    menuButtons[1].zPos = 7.58003;
    menuButtons[1].width = 0.5;
    menuButtons[1].height = 0.25;
    menuButtons[1].screen = mainMenu;


    menuButtons[2].sprite.initQuad("images/ButtonExit.png");
    menuButtons[2].xPos = 0;
    menuButtons[2].yPos = -0.6;
    menuButtons[2].zPos = 7.58004;
    menuButtons[2].width = 0.5;
    menuButtons[2].height = 0.25;
    menuButtons[2].screen = mainMenu;


    selectButtons[0].sprite.initQuad("images/lvl1Button.png");
    selectButtons[0].xPos = -0.75;
    selectButtons[0].yPos = 0.0;
    selectButtons[0].zPos = 7.58002;
    selectButtons[0].width = 0.25;
    selectButtons[0].height = 0.25;
    selectButtons[0].screen = levelSelect;


    selectButtons[1].sprite.initQuad("images/lvl2Button.png");
    selectButtons[1].xPos = 0;
    selectButtons[1].yPos = 0.0;
    selectButtons[1].zPos = 7.58003;
    selectButtons[1].width = 0.25;
    selectButtons[1].height = 0.25;
    selectButtons[1].screen = levelSelect;


    selectButtons[2].sprite.initQuad("images/lvl3Button.png");
    selectButtons[2].xPos = 0.75;
    selectButtons[2].yPos = 0.0;
    selectButtons[2].zPos = 7.58004;
    selectButtons[2].width = 0.25;
    selectButtons[2].height = 0.25;
    selectButtons[2].screen = levelSelect;
}


void _GameManager::activateMenu(float x, float y, float deltaT)     // Altered to use the new button collision - Jacob
{
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    switch(currentState)
    {
        case LANDING:
            titleScreen->drawBkGrnd(x, y);
        break;

        case MAIN_MENU:
            menuScreen->drawBkGrnd(x, y);
            drawButtons(menuButtons);
        break;

        case LEVEL_SELECT:
            levelSelectScreen->drawBkGrnd(x, y);
            drawButtons(selectButtons);
            break;

        case HOW_TO_PLAY:
            howToPlayScreen->drawBkGrnd(x, y);
        break;

        case PAUSED_GAME:
            gameActive = false;
            pausePopup->drawQuad();
        break;

        case IN_GAME:
            gameActive = true;
            doGameplay(deltaT);
        break;
    }

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}


void _GameManager::update()     // Altered to use the new button collision - Jacob
{
    for (int i = 0; i < menuButtons.size(); i++)
    {
        if (menuButtons[i].screen == currentState)
        {
            buttonColliding(i, menuButtons);   // updates brightness every frame
        }
        else
        {
            menuButtons[i].sprite.brightness = 1.0f;
        }
    }

    for (int i = 0; i < menuButtons.size();i++) {
        if (mouseClicked && buttonColliding(i, menuButtons))
        {
            menuSounds->playSnd("sounds/Click.mp3");
        }
    }

    for (int i = 0; i < selectButtons.size(); i++)
    {
        if (selectButtons[i].screen == currentState)
        {
            buttonColliding(i, selectButtons);   // updates brightness every frame
        }
        else
        {
            selectButtons[i].sprite.brightness = 1.0f;
        }
    }

    for (int i = 0; i < selectButtons.size();i++) {
        if (mouseClicked && buttonColliding(i, selectButtons))
        {
            menuSounds->playSnd("sounds/Click.mp3");
        }
    }

    switch (currentState)
    {   
        case LANDING:
            if (mouseClicked)
            {
                currentState = MAIN_MENU;
                currentScreen = mainMenu;
            }

            mouseClicked = false;
            
            break;

        case MAIN_MENU:
            if (mouseClicked && buttonColliding(0, menuButtons))
            {
                currentState = LEVEL_SELECT;
                currentScreen = levelSelect;
            }
            else if (mouseClicked && buttonColliding(1, menuButtons))
            {
                currentState = HOW_TO_PLAY;
               currentScreen = howToPlay;
            }
            else if (mouseClicked && buttonColliding(2, menuButtons))
            {
                exit(0);
            }

            mouseClicked = false;

           break;

        case LEVEL_SELECT:
            if (mouseClicked && buttonColliding(0, selectButtons))
            {
                levelID = 1;
                currentState = IN_GAME;
            }
            else if (mouseClicked && buttonColliding(1, selectButtons))
            {
                levelID = 2;
                currentState = IN_GAME;
            }
            else if (mouseClicked && buttonColliding(2, selectButtons)) 
            {
                levelID = 3;
                currentState = IN_GAME;
            }

            mouseClicked = false;

            break;

        break;

        default:
            
            break;
    }
    
}
//////////////////////////////////////////////////////////////////////////////////////////////





////////////////////////////////// GAMEPLAY RELATED LOGIC ////////////////////////////////////
void _GameManager::doGameplay(float deltaT)     // Now displays the appropiate level selected in the select menu - Jacob
{
    if (gameActive == true)
    {
        ShowCursor(FALSE);

        mySky->drawSkyBox();

        glPushMatrix();                         // Start grouping matrix
        exoMan->drawPlayer(deltaT);
        glPopMatrix();                          // End grouping matrix


        if (levelID == 1)
        {
            glPushMatrix();
            lv1floor->drawModel();
            lv1crate1->drawModel();
            lv1crate2->drawModel();
            lv1crate3->drawModel();
            glPopMatrix();        

            glPushMatrix();
            glTranslatef(1.0, 0.0, -7.5);
            myEnms[0].drawEnms(deltaT);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(1.5, 0.0, -7.5);
            myEnms[1].drawEnms(deltaT);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(1.0, 0.0, -12.0);
            myEnms[2].drawEnms(deltaT);
            glPopMatrix();
        }
        else if (levelID == 2)
        {
            glPushMatrix();
            lv2floor->drawModel();
            lv2wall1->drawModel();
            lv2wall2->drawModel();
            lv2wall3->drawModel();
            lv2crate1->drawModel();
            lv2crate2->drawModel();
            lv2crate3->drawModel();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(10.0, 0.0, -1.0);
            myEnms[0].drawEnms(deltaT);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-2.0, 0.0, -8.5);
            myEnms[1].drawEnms(deltaT);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(5.0, 0.0, -16.0);
            myEnms[2].drawEnms(deltaT);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-7.0, 0.0, -16.0);
            myEnms[2].drawEnms(deltaT);
            glPopMatrix();
        }
        else if (levelID == 3)
        {
            glPushMatrix();
            lv3floor->drawModel();
            lv3wall1->drawModel();
            lv3wall2->drawModel();
            lv3wall3->drawModel();
            lv3crate1->drawModel();
            lv3crate2->drawModel();
            lv3crate3->drawModel();
            lv3crate4->drawModel();
            lv3crate5->drawModel();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-6.0, 0.0, -1.0);
            myEnms[0].drawEnms(deltaT);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-3.0, 0.0, -3.0);
            myEnms[1].drawEnms(deltaT);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0.0, 0.0, -14.0);
            myEnms[2].drawEnms(deltaT);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-6.0, 0.0, -18.0);
            myEnms[3].drawEnms(deltaT);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(9.5, 0.0, 1.0);
            myEnms[4].drawEnms(deltaT);
            glPopMatrix();
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////