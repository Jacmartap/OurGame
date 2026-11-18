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
void _GameManager::drawButtons()
{
    glDisable(GL_LIGHTING);
    for (int i = 0; i < buttons.size();i++)
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


bool _GameManager::buttonColliding(int index)
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
    howToPlayScreen->initPRLX("images/HowToPlayScreen.png");
    
    pausePopup->initQuad("images/PausePop_Up.png");

    gameBgScreen->initPRLX("images/Bg.png");

    buttons[0].sprite.initQuad("images/ButtonStart.png");
    buttons[0].xPos = 0;
    buttons[0].yPos = 0.6;
    buttons[0].zPos = 7.58002;
    buttons[0].width = 0.5;
    buttons[0].height = 0.25;
    buttons[0].screen = mainMenu;


    buttons[1].sprite.initQuad("images/ButtonHelp.png");
    buttons[1].xPos = 0;
    buttons[1].yPos = 0.0;
    buttons[1].zPos = 7.58003;
    buttons[1].width = 0.5;
    buttons[1].height = 0.25;
    buttons[1].screen = mainMenu;


    buttons[2].sprite.initQuad("images/ButtonExit.png");
    buttons[2].xPos = 0;
    buttons[2].yPos = -0.6;
    buttons[2].zPos = 7.58004;
    buttons[2].width = 0.5;
    buttons[2].height = 0.25;
    buttons[2].screen = mainMenu;
}


void _GameManager::activateMenu(float x, float y, float deltaT)
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
            drawButtons();
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


void _GameManager::update()
{
    for (int i = 0; i < buttons.size(); i++)
    {
        if (buttons[i].screen == currentState)
        {
            buttonColliding(i);   // updates brightness every frame
        }
        else
        {
            buttons[i].sprite.brightness = 1.0f;
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
            if (mouseClicked && buttonColliding(0)) {
                currentState = IN_GAME;
                currentScreen = gameBG;
            }
            else if (mouseClicked && buttonColliding(1))
            {
                currentState = HOW_TO_PLAY;
               currentScreen = howToPlay;
            }
            else if (mouseClicked && buttonColliding(2)) {
                exit(0);
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
void _GameManager::doGameplay(float deltaT)
{
    if (gameActive == true)
    {
        ShowCursor(FALSE);

        mySky->drawSkyBox();

        glPushMatrix();                         // Start grouping matrix
        exoMan->drawPlayer(deltaT);
        glPopMatrix();                          // End grouping matrix

        glPushMatrix();
        floor->drawModel();
        crate1->drawModel();
        crate2->drawModel();
        crate3->drawModel();
        glPopMatrix();

        //Ignoring the zombies just for now - Jacob
        for (int i = 0; i < numEnms; i++)
        {
            glPushMatrix();
            glTranslatef((i * 1.0), 0.0, 0.0);
            myEnms[i].drawEnms(deltaT);
            glPopMatrix();
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////