//Exam No: Y3856186
#include <graphics_lib.h>
#include <math.h>
#include <stdlib.h>



int main(void)
{
    /*initialising functions for later use*/
    GFX_InitWindow(700, 600);//opens a graphics window with a width of 700 pixels and a height of 600 pixels
    replay: //used with goto function to replay game
    GFX_InitBitmap();//initialise bitmap images for use
    GFX_InitFont();//this function lets you use GFX_DrawText() to write strings on the graphics window
    GFX_InitKeyboard();//initialises keyboard usage
    /*loading images into BITMAPS*/
    BITMAP piggy = GFX_LoadBitmap("piggy.jpg");
    BITMAP cannon = GFX_LoadBitmap("cannon.png");
    BITMAP piggybank = GFX_LoadBitmap("piggybank.png");
    BITMAP gameover = GFX_LoadBitmap("gameover.png");


    /*setting up arrays for usage in GFX_DrawText()*/
    char level[30];
    char score[30];
    char velocity[30];
    char angle[30];
    char turns[30];
    int lvl = 1;//displays the level played
    int scr = 0;
    int i = 10;//used in for loop and display turns
    int v = 5;//will be showing value of velocity
    int a = 5;//will be showing angle
    sprintf(velocity,"vel: %i",v);//v stored in velocity array
    sprintf(angle,"angle: %i", a);
    sprintf(level,"level: %i", lvl);
    //sprintf() for i and scr are used in loop as they need updating



    /*creating variables for keyboard*/
    int press;//for button press
    int finish;//to initialise rest of loop after selection of values
    int over;//for game-over screen
    int menu;//for menu screen
    int win;//for winning screen

    /*menu here*/
    //draws projectile word on main menu
    GFX_DrawFilledRectangle(0,0,700,600,BLUE);
    GFX_SetColour(RED);
    GFX_DrawLine(145,100,145,200,15);
    GFX_DrawRectangle(145,100,195,140,15);
    GFX_DrawLine(215,140,215,200,15);
    GFX_DrawLine(208,140,250,140,15);
    GFX_DrawLine(243,140,243,158,15);
    GFX_DrawRectangle(265,135,300,190,15);
    GFX_DrawLine(308,190,340,190,15);
    GFX_DrawLine(340,197,340,140,15);
    GFX_DrawLine(340,120,340,130,15);
    GFX_DrawLine(355,150,396,150,12);
    GFX_DrawLine(355,170,396,170,10);
    GFX_DrawLine(355,190,396,190,15);
    GFX_DrawLine(362,150,362,190,13);
    GFX_DrawLine(390,150,390,170,12);
    GFX_DrawLine(410,151,445,151,13);
    GFX_DrawLine(410,190,445,190,13);
    GFX_DrawLine(410,196,410,144,13);
    GFX_DrawLine(455,150,495,150,13);
    GFX_DrawLine(475,135,475,197,13);
    GFX_DrawLine(510,140,510,197,13);
    GFX_DrawLine(510,120,510,130,15);
    GFX_DrawLine(535,125,535,197,15);
    GFX_DrawLine(564,150,605,150,12);
    GFX_DrawLine(564,170,605,170,10);
    GFX_DrawLine(564,190,611,190,15);
    GFX_DrawLine(564,197,564,144,15);
    GFX_DrawLine(605,144,605,175,13);
    //how to play
    GFX_DrawText(10,401,"How to play:");
    GFX_DrawText(10,416,"*Use left and right arrow keys for changing the velocity.");
    GFX_DrawText(10,431,"*Use up and down arrow keys for changing the angle of the projectile.");
    GFX_DrawText(10,446,"*Every time piggy bank is broken you receive 15 coins, use them to buy more ammo!");
    GFX_DrawText(10,461,"*Be careful at level 2 as there will be a wall between you and the piggy bank.");
    GFX_DrawText(10,476,"*One shooting ray costs 5 coins.");
    GFX_DrawText(10,491,"*Don't forget to have fun!");
    GFX_DrawText(275,300,"Press ENTER to start");
    GFX_DrawText(275,315,"Press ESC to exit game");
    GFX_UpdateDisplay();
    //menu keys
    GFX_CreateEventQueue();
    GFX_RegisterKeyboardEvents();//registers all keyboard presses
    menu = 0;
    while (!menu)
    {
        GFX_WaitForEvent();
        if (GFX_IsEventKeyDown())
        {
            GFX_GetKeyPress(&press);
            if (press == ALLEGRO_KEY_ESCAPE)//escape button(exit game)
            {
                GFX_CloseWindow();
            }
            else if (press == ALLEGRO_KEY_ENTER)//enter button (play game)
            {
                break;
            }
        }
    }

    /*forming ground for game and loading bitmpas*/
    GFX_DrawFilledRectangle(0,500,700,600,GREEN);
    GFX_DrawBitmap(piggy,300,250);//this function draws bitmaps
    GFX_DrawBitmap(cannon,80,500);
    GFX_DrawBitmap(piggybank,530,515);
    GFX_UpdateDisplay(); //updates the display in order for drawings to appear

    /*calling variables for projectile shooting, based on laws of physics*/
    //using mostly doubles as for cos and sin the calculations are only done in doubles
    double initialYpos;
    double initialXpos;
    double Xpos;
    double Ypos;
    double initialV;
    double Vx;
    double Vy;
    double time;
    double u; //u is the theta I will use to put in cos(u) and sin(u)
    float g; //g is gravity
    //////IMPORTANT AS MATHS LIB WORKS IN RADIANS: 5 degrees is 0.0872665 radians//////

    /*defining locations for projectiles and giving gravity its value (9.81 m/s^2)*/
    initialXpos = 110;//for the initial positions of x and y setting 110 and 469 as they are the location of where the projectile will come from
    initialYpos = 469;
    Xpos = initialXpos;//the changing x and y values are set equal to the initial as that is where the projectile starts form
    Ypos = initialYpos;
    g = 9.81;

    /*drawing triangles as arrows of velocity and angles*/
    GFX_DrawFilledTriangle(125,50,150,75,125,100,CYAN);//cyan is for velocity
    GFX_DrawFilledTriangle(50,50,25,75,50,100,CYAN);
    GFX_DrawFilledTriangle(125,104,150,129,125,154,YELLOW);//yellow is for angel manipulation
    GFX_DrawFilledTriangle(50,104,25,129,50,154,YELLOW);
    GFX_SetColour(RED);//setting "pen" colour to red
    GFX_DrawText(50,69,velocity);
    GFX_DrawText(50,123,angle);
    GFX_DrawText(63,170,"Enter!");
    GFX_DrawText(45,550,"ammo: 10");
    sprintf(score,"coins: %i",scr);
    GFX_DrawText(45,563,score);
    GFX_DrawText(45,576,level);
    GFX_DrawRectangle(52.5,165,122.5,190,3);
    GFX_DrawText(45,537,"Press U to buy ammo!");
    GFX_UpdateDisplay();

    /* defining nested functions*/
    //refreshes 3 values below after each throw automatically
    void valueRef()
    {
        sprintf(turns,"ammo: %i",i);
        sprintf(velocity,"vel: %i",v);
        sprintf(angle,"angle: %i",a);
        GFX_DrawText(50,69,velocity);
        GFX_DrawText(45,550,turns);
        GFX_DrawText(50,123,angle);
    }
    //refreshes screen
    void screenRef()
    {
        GFX_ClearWindow();
        GFX_DrawFilledRectangle(0,500,700,600,GREEN);
        GFX_DrawBitmap(piggy,300,250);
        GFX_DrawBitmap(cannon,80,500);
        GFX_DrawFilledTriangle(125,50,150,75,125,100,CYAN);
        GFX_DrawFilledTriangle(50,50,25,75,50,100,CYAN);
        GFX_DrawFilledTriangle(125,104,150,129,125,154,YELLOW);
        GFX_DrawFilledTriangle(50,104,25,129,50,154,YELLOW);
        GFX_DrawText(50,69,velocity);
        GFX_DrawText(50,123,angle);
        GFX_DrawText(63,170,"Enter!");
        sprintf(score,"coins: %i",scr);
        GFX_DrawText(45,563,score);
        sprintf(turns,"ammo: %i",i);
        GFX_DrawRectangle(52.5,165,122.5,190,3);
        GFX_DrawText(45,550,turns);
        GFX_DrawText(45,576,level);
        GFX_DrawBitmap(piggybank,530,515);
        GFX_DrawText(45,537,"Press U to buy ammo!");
    }
    //screen refreshes and level up with collision detection of piggy bank
    void levelup()
    {
        lvl +=1;
        scr +=15;
        GFX_ClearWindow();
        GFX_MoveTo(initialXpos,initialYpos);
        GFX_DrawFilledRectangle(0,500,700,600,GREEN);
        GFX_DrawBitmap(piggy,300,250);
        GFX_DrawBitmap(cannon,80,500);
        GFX_DrawFilledTriangle(125,50,150,75,125,100,CYAN);
        GFX_DrawFilledTriangle(50,50,25,75,50,100,CYAN);
        GFX_DrawFilledTriangle(125,104,150,129,125,154,YELLOW);
        GFX_DrawFilledTriangle(50,104,25,129,50,154,YELLOW);
        GFX_DrawText(50,69,velocity);
        GFX_DrawText(50,123,angle);
        GFX_DrawText(63,170,"Enter!");
        sprintf(turns,"ammo: %i",i);
        sprintf(score,"coins: %i",scr);
        GFX_DrawText(45,563,score);
        GFX_DrawRectangle(52.5,165,122.5,190,3);
        sprintf(level,"level: %i",lvl);
        GFX_DrawText(45,550,turns);
        GFX_DrawText(45,576,level);
        GFX_DrawText(45,537,"Press U to buy ammo!");
        GFX_UpdateDisplay();
        GFX_PauseFor(325);//so pig disappears for 0.325s
    }
    //collision with wall
    void hitwall()
    {
        GFX_ClearWindow();
        GFX_DrawFilledRectangle(0,500,700,600,GREEN);
        GFX_DrawBitmap(piggy,300,250);
        GFX_DrawBitmap(cannon,80,500);
        GFX_DrawFilledTriangle(125,50,150,75,125,100,CYAN);
        GFX_DrawFilledTriangle(50,50,25,75,50,100,CYAN);
        GFX_DrawFilledTriangle(125,104,150,129,125,154,YELLOW);
        GFX_DrawFilledTriangle(50,104,25,129,50,154,YELLOW);
        GFX_DrawText(50,69,velocity);
        GFX_DrawText(50,123,angle);
        GFX_DrawText(63,170,"Enter!");
        sprintf(turns,"ammo: %i",i);
        sprintf(score,"coins: %i",scr);
        GFX_DrawText(45,563,score);
        GFX_DrawRectangle(52.5,165,122.5,190,3);
        sprintf(level,"level: %i",lvl);
        GFX_DrawText(45,550,turns);
        GFX_DrawText(45,537,"Press U to buy ammo!");
        GFX_DrawText(45,576,level);
        GFX_UpdateDisplay();
    }
    //draws screen with no projectile path after collisions
    void noPROJECTILE()
    {
        GFX_DrawFilledRectangle(0,500,700,600,GREEN);
        GFX_DrawBitmap(piggy,300,250);
        GFX_DrawBitmap(cannon,80,500);
        GFX_DrawFilledTriangle(125,50,150,75,125,100,CYAN);
        GFX_DrawFilledTriangle(50,50,25,75,50,100,CYAN);
        GFX_DrawFilledTriangle(125,104,150,129,125,154,YELLOW);
        GFX_DrawFilledTriangle(50,104,25,129,50,154,YELLOW);
        GFX_DrawText(50,69,velocity);
        GFX_DrawText(50,123,angle);
        GFX_DrawText(63,170,"Enter!");
        sprintf(turns,"ammo: %i",i);
        sprintf(score,"coins: %i",scr);
        GFX_DrawText(45,563,score);
        GFX_DrawRectangle(52.5,165,122.5,190,3);
        GFX_DrawText(45,550,turns);
        GFX_DrawText(45,576,level);
        GFX_DrawBitmap(piggybank,530,515);
        GFX_DrawText(45,537,"Press U to buy ammo!");
    }
    //winning screen however button functions were not added as adding the goto function for replay will cause an error the same as the game over screen
    void WIN()
    {
        GFX_DrawFilledRectangle(0,0,700,600,YELLOW);
        GFX_DrawText(317,250,"YOU WON!!!");
        GFX_DrawText(260,265,"Press R for to play again");
        GFX_DrawText(260,280,"Press ESC to exit game");
        GFX_UpdateDisplay();
        GFX_CreateEventQueue();
        GFX_RegisterKeyboardEvents();
        win = 0;
    }
    //draws game-over screen
    void Gameover()
    {
        GFX_DrawFilledRectangle(0,0,700,600,BLUE);
        GFX_DrawBitmap(gameover, 350,300);
        GFX_DrawText(425,500,"R = Replay");
        GFX_DrawText(425,520,"ESC = Exit");
        GFX_UpdateDisplay();
        over = 0;
    }
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
////////////////////////*main game starts here*//////////////////////////////////////

    /*giving initialV and u(theta) values in order to add or subtract through key press when they are called later on*/
    initialV = 5;
    u = -0.0872665;
    /*for loops represents number of ammunition available at the start*/
    for (i=10; i>=0; i--)
    {
        /*start queue events for mouse*/
        GFX_CreateEventQueue();//creates queue
        GFX_RegisterKeyboardEvents();//registers keyboard events

        /*loop for keyboard events*/
        finish = 0;
        while (!finish)
        {

            GFX_WaitForEvent();//waits for an event to happen
            if (GFX_IsEventKeyDown())//checks if key is pressed
            {
                GFX_GetKeyPress(&press);
                if (press == ALLEGRO_KEY_RIGHT)//if right arrow is pressed
                {
                    initialV +=5;//adding 5 to velocity
                    v +=5;//adds +5 to velocity text rest of code is to redraw on window
                    sprintf(velocity,"vel: %i",v);
                    GFX_DrawText(50,69,velocity);
                    screenRef();
                    if (lvl >= 2)//represents level 2 by adding obstacle, if statement across programme checks which level the game is on
                    {
                        GFX_DrawFilledRectangle(300,430,310,522,BLACK);//creates obstacle if level 2 is detected
                    }

                    GFX_UpdateDisplay();//keeping update after screen ref in order for the obstacle to stay on screen

                    if (v>=100 && initialV>=95)//if velocity reaches 100 it does not let it increase
                    {
                        initialV -=5;
                        v -=5;
                    }
                }
                else if (press == ALLEGRO_KEY_LEFT)
                {
                    initialV -=5;
                    v -=5;
                    sprintf(velocity,"vel: %i",v);
                    GFX_DrawText(50,69,velocity);
                    screenRef();
                    if (lvl >= 2)
                    {
                        GFX_DrawFilledRectangle(300,430,310,522,BLACK);
                    }

                    GFX_UpdateDisplay();

                    if (v<=0 && initialV<=0)//does not let velocity go under 0
                    {
                        initialV +=5;
                        v +=5;
                    }
                }
                //doing the same for angles
                if (press == ALLEGRO_KEY_UP)
                {
                    a += 5;
                    u -=0.0872665;//subtracting 5 radians instead of adding as this is dependent on the plane of the screen so it shoots in the correct direction
                    sprintf(angle,"angle: %i",a);
                    GFX_DrawText(50,123,angle);
                    screenRef();
                    if (lvl >= 2)
                    {
                        GFX_DrawFilledRectangle(300,430,310,522,BLACK);
                    }

                    GFX_UpdateDisplay();

                    if (a>90 && u>-1.5708)//1.5708 is 90 degrees
                    {
                        u +=0.0872665;
                        a -=5;
                    }
                }
                else if (press == ALLEGRO_KEY_DOWN)
                    a -=5;
                u +=0.0872665;
                sprintf(angle,"angle: %i",a);
                GFX_DrawText(50,123,angle);
                screenRef();
                if (lvl >= 2)
                {
                    GFX_DrawFilledRectangle(300,430,310,522,BLACK);
                }

                GFX_UpdateDisplay();

                if (a<=0 && u>=0)
                {
                    u -=0.0872665;
                    a +=5;
                }
                else if (press == ALLEGRO_KEY_U)//buying ammo
                {
                    if (scr>0)
                    {
                        i +=1;
                        scr -=5;
                    }
                    screenRef();
                    if (lvl >= 2)
                    {
                        GFX_DrawFilledRectangle(300,430,310,522,BLACK);
                    }
                    GFX_UpdateDisplay();
                }
                else if (press == ALLEGRO_KEY_ENTER)
                {
                    /*defining Vx and Vy here as initial V and u(theta) are called in the function below, as they will be called below*/
                    Vx = initialV*cos(u);
                    Vy = initialV*sin(u);
                    /*setting up the shooting in the while loop using the laws of physics based on the named variables above*/
                    GFX_MoveTo(initialXpos,initialYpos);//function puts "pen" to the starting location from where the projectile path will be drawn from
                    while (Ypos<527.5)
                    {
                        time = (Xpos - initialXpos)/Vx;
                        Ypos = initialYpos - (Vy*time) + (g*pow(time,2))/2;
                        GFX_DrawLineTo(Xpos,Ypos,4);
                        Xpos +=2.5;
                        GFX_UpdateDisplay();
                        //resetting the values for velocity and angle after shooting
                        u = -0.0872665;
                        initialV = 5;
                        a = 5;
                        v = 5;
                        /*collision detection takes place and getting coins*/
                        //hitting piggy bank
                        if (500<=Xpos && 560>=Xpos && 510<=Ypos && 535>=Ypos)//collisions in the game work through checking where the x and y pos of the head of ray are
                        {
                            levelup();
                            break;
                        }
                        //hitting wall
                        else if (lvl == 2 && Xpos>=300 && Xpos<=310 && Ypos>=430)
                        {
                            break;
                            hitwall();
                        }


                    }
                    i -=1;//decreases number of ammo as while loop cannot finish so internally decreasing the ammunition, if this is moved under valueref() then ammo wont update automatically and will do so at next button press
                    valueRef();
                    Xpos = 110;//resetting X and Y positions in order to shoot again
                    Ypos = 469;
                    GFX_ClearWindow();//clears all window
                    /*re-adding functions so only projectile path is deleted after ray hit obstacle or ground or piggy bank*/
                    noPROJECTILE();
                    if (lvl >= 2)
                    {
                        GFX_DrawFilledRectangle(300,430,310,522,BLACK);
                    }
                    GFX_UpdateDisplay();
                    //game-over screen//
                    if (i==0)
                    {
                        Gameover();
                        while (!over)
                        {
                            GFX_WaitForEvent();
                            if (GFX_IsEventKeyDown())
                            {
                                GFX_GetKeyPress(&press);
                                if (press == ALLEGRO_KEY_ESCAPE)
                                {
                                    GFX_CloseWindow();
                                }
                                else if (press == ALLEGRO_KEY_R)
                                {
                                    goto replay;
                                }
                            }//gfx is event down here, adding comments for certain brackets for easy identification if modification is needed
                        }//while loop here
                        break;
                    }//if i == 0 statement ends here
                    //winning screen
                    else if (lvl == 3)//when level 2 piggy bank is hit winning screen is shown
                    {
                        WIN();
                        while (!win)
                        {
                            GFX_WaitForEvent();
                            if (GFX_IsEventKeyDown())
                            {
                                GFX_GetKeyPress(&press);
                                if (press == ALLEGRO_KEY_ESCAPE)
                                {
                                    GFX_CloseWindow();
                                }
                                else if (press == ALLEGRO_KEY_R)
                                {
                                    goto replay;
                                }

                            }
                        }
                    }
                }
            }
        }



    }
    return 0;
}
