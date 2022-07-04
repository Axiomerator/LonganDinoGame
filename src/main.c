#include "lcd/lcd.h"
#include <string.h>
#include "utils.h"

#include "img.h"

#define MAX_ENEMY_NUM 5

void Inp_init(void)
{
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
}

void Adc_init(void) 
{
    rcu_periph_clock_enable(RCU_GPIOA);
    gpio_init(GPIOA, GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, GPIO_PIN_0|GPIO_PIN_1);
    RCU_CFG0|=(0b10<<14)|(1<<28);
    rcu_periph_clock_enable(RCU_ADC0);
    ADC_CTL1(ADC0)|=ADC_CTL1_ADCON;
}

void IO_init(void)
{
    Inp_init(); // inport init
    Adc_init(); // A/D init
    Lcd_Init(); // LCD init
}

// 0~1 random number generator
float enemySpawnOdds(int *randomSeed_t) {
    *randomSeed_t = randomA(*randomSeed_t);
    return (float)(*randomSeed_t) / 217671;
}

// tickFloor_t ~ tickCeiling_t random number generator functionss
int getEnemySpawnTickInterval_S(int tickFloor_t, int tickCeiling_t, int *randomSeed_t) {
    *randomSeed_t = randomA(*randomSeed_t);
    return (int)((tickCeiling_t - tickFloor_t) * ((float)(*randomSeed_t) / 217671)) + tickFloor_t;
}

// 0 or 1 random boolean value generator
int randomBoolean(int *randomSeed_t) {
    *randomSeed_t = randomA(*randomSeed_t);
    if ((float)(*randomSeed_t) / 217671 < 0.5) {
        return 0;
    }
    return 1;
}

// 0 or 1 or 2 random int generator
int random012(int *randomSeed_t) {
    *randomSeed_t = randomA(*randomSeed_t);
    if ((float)(*randomSeed_t) / 217671 < 0.33) {
        return 0;
    }
    if ((float)(*randomSeed_t) / 217671 > 0.66) {
        return 1;
    }
    return 2;
}

/*
// update the RGB rolling color every single game tick
void rgb_update(int *color_t, int *stage_t) {
    // color rolling is split into 3 stages:
    // RB, BG, and GR
    if (*stage_t == 1) {
        *color_t = *color_t - 2048 + 1;
    } else if (*stage_t == 2) {
        *color_t = *color_t + 2*32 - 1;
    } else if (*stage_t == 3) {
        *color_t = *color_t + 2048 - 2*32;
    }

    if (*color_t / 32 == 0) {
        *stage_t = 2;
        *color_t = 0b0000000000011111;
    } else if ((*color_t / 2048 == 0) && (*color_t % 32 == 0)) {
        *stage_t = 3;
        // *color_t = 0b0000011111100000; // causes blinks??
    } else if (*color_t % 2048 == 0) {
        *stage_t = 1;
        *color_t = 0b1111100000000000;
    }

}
*/

void waitForRelease_BOOT0() {
    delay_1ms(1);
    while (1) {
        if (!Get_BOOT0()) {
            break;
        }
    }
}

void waitForRelease_A(int channel_t) {
    delay_1ms(1);
    while (1) {
        if (!Get_Button(channel_t)) {
            break;
        }
    }
}

// animation player
/*
void switchAnimation() {
    for (int i = 80; i < 160; ++i) {
        LCD_DrawLine(i, 0, i, 80, WHITE);
        LCD_DrawLine(159 - i, 0, 159 - i, 80, WHITE);
    }
    int animation_interval = 0;
    for (int i = 80; i < 160; ++i) {
        if ((i - 80) % 8 == 0) {
            ++animation_interval;
        }
        LCD_DrawLine(i, 0, i, 80, BLACK);
        LCD_DrawLine(159 - i, 0, 159 - i, 80, BLACK);
        delay_1ms(animation_interval);
    }
}
*/

/*
void turnPageAnimation() {
    for (int i = 162; i >= 0; i = i - 2) {
        LCD_DrawLine(i-2, 0, i-2, 80, WHITE);
        LCD_DrawLine(i-3, 0, i-3, 80, WHITE);
        LCD_DrawLine(i, 0, i, 80, BLACK);
        LCD_DrawLine(i-1, 0, i-1, 80, BLACK);
    }
}
*/

/*
void drawEnemy_cactus_0(u16 x1, u16 y1, u16 color) {
    int x2 = x1 + 1;
    int y2 = y1 + 16;
    LCD_DrawLine(x1, y1, x1, y2, color);
    LCD_DrawLine(x2, y1, x2, y2, color);
    
    LCD_DrawLine(x2 + 1, y2 - 8, x2 + 1, y2 - 7, color);
    
    LCD_DrawLine(x2 + 2, y2 - 14, x2 + 1, y2 - 8, color);

    LCD_DrawLine(x1 - 2, y1 + 9, x1 - 2, y1 + 10, color);
    LCD_DrawLine(x1 - 1, y1 + 9, x1 - 1, y1 + 10, color);

    LCD_DrawLine(x1 - 3, y1 + 4, x1 - 3, y1 + 9, color);
}
*/

/*
void drawEnemy_cactus_1(u16 x1, u16 y1, u16 color) {
    int x2 = x1 + 3;
    int y2 = y1 + 23;
    LCD_DrawLine(x1, y1, x1, y2, color);
    LCD_DrawLine(x1 + 1, y1, x1 + 1, y2, color);
    LCD_DrawLine(x2 - 1, y1, x2 - 1, y2, color);
    LCD_DrawLine(x2, y1, x2, y2, color);
    
    LCD_DrawLine(x2 + 1, y2 - 7, x2 + 1, y2 - 6, color);
    LCD_DrawLine(x2 + 2, y2 - 7, x2 + 2, y2 - 6, color);

    LCD_DrawLine(x2 + 3, y2 - 14, x2 + 3, y2 - 7, color);
    LCD_DrawLine(x2 + 4, y2 - 14, x2 + 4, y2 - 7, color);

    LCD_DrawLine(x1 - 1, y1 + 12, x1 - 1, y1 + 14, color);
    LCD_DrawLine(x1 - 2, y1 + 12, x1 - 2, y1 + 14, color);

    LCD_DrawLine(x1 - 3, y1 + 6, x1 - 3, y1 + 13, color);
    LCD_DrawLine(x1 - 4, y1 + 6, x1 - 4, y1 + 12, color);
}
*/

// all the info of enemies are stored in it
struct enemy_database {
    int enemyID;
    int enemyValidation;
    int enemyType;
    int enemyLookID;
    int top_left_x;
    int top_left_y;
    int bottom_right_x;
    int bottom_right_y;
};

// ground decoration info
struct ground_database {
    int stage_1_dot_1_x;
    int stage_1_dot_2_x;
    int stage_1_dot_3_x;
    int stage_2_dot_1_x;
    int stage_2_dot_2_x;
};


// UNIVERSAL GAME CONTROL
int main(void) {

    IO_init();         // init OLED
    // YOUR CODE HERE
    LCD_Clear(BLACK);

    int rgb_stage = 1;
    int rgb_color = 0b1111100000000000;
    int game_tick = 50; // game_tick ticks per second
    int delay_interval = 1000 / game_tick;
    
    // highest_score must be stored outside the GAME_RESTART label
    int highest_score = 0;

    while (1) {
        rgb_update(&rgb_color, &rgb_stage);
        LCD_Clear(rgb_color);

        if (Get_Button(0)) {
            // wait for the button to be released
            waitForRelease_A(0);
            break;
        }
        delay_1ms(delay_interval);
    }

    GAME_RESTART:

    switchAnimation();

    int invincible_mode_countdown = 0;
    int suicide_countdown = 0;

    int dinoMenuAnimationCounter = 0;

    game_main_menu:
    LCD_Clear(BLACK);
    while (1) {
        ++dinoMenuAnimationCounter;
        if (dinoMenuAnimationCounter >= 64) {
            dinoMenuAnimationCounter = 0;
        }

        rgb_update(&rgb_color, &rgb_stage);
        LCD_ShowString(20, 16, (u8 *)("Dino Game!"), rgb_color);
        LCD_ShowString(20, 45, (u8 *)("Play"), 0x7BCF);
        LCD_ShowString(62, 45, (u8 *)("Help"), 0x7BCF);
        // game version
        LCD_ShowString(0, 64, (u8 *)("1.0.0"), 0x4C15);

        if ( (dinoMenuAnimationCounter / 4 % 2) == 0 && dinoMenuAnimationCounter / 32 == 0 ) {
            LCD_ShowPic_Pro(121, 28, 140, 47, trex2);
        } else if ( (dinoMenuAnimationCounter / 4 % 2) == 1 && dinoMenuAnimationCounter / 32 == 0 ) {
            LCD_ShowPic_Pro(121, 28, 140, 47, trex1);
        } else if ( (dinoMenuAnimationCounter / 4 % 2) == 0 && dinoMenuAnimationCounter / 32 == 1 ) {
            LCD_ShowPic_Pro(121, 28, 140, 47, trex2_b);
        } else {
            LCD_ShowPic_Pro(121, 28, 140, 47, trex1_b);
        }

        // main menu invincible mode indicator
        if (invincible_mode_countdown == 5) {
            LCD_DrawRectangle(121, 28, 140, 47, rgb_color);
        }

        if (Get_Button(0)) {
            LCD_ShowString(20, 45, (u8 *)("Play"), WHITE);
            // wait for the button to be released
            waitForRelease_A(0);
            LCD_ShowString(20, 45, (u8 *)("Play"), 0x7BCF);
            delay_1ms(200);
            goto game_start;
        }

        if (Get_Button(1)) {
            LCD_ShowString(62, 45, (u8 *)("Help"), WHITE);
            // wait for the button to be released
            waitForRelease_A(1);
            LCD_ShowString(62, 45, (u8 *)("Help"), 0x7BCF);
            delay_1ms(200);
            goto game_instruction;
        }

        delay_1ms(delay_interval);
    }


    game_instruction:
    switchAnimation();
    LCD_ShowString(0,  0, (u8 *)("This is a obstacle"), WHITE);
    LCD_ShowString(0, 16, (u8 *)("-avoiding game."), WHITE);
    LCD_ShowString(0, 32, (u8 *)("Use the left button"), WHITE);
    LCD_ShowString(0, 48, (u8 *)("to jump, the other"), WHITE);
    LCD_ShowString(0, 64, (u8 *)("one to crouch."), WHITE);
    
    while (1) {
        if (Get_Button(1)) {
            // wait for the button to be released
            waitForRelease_A(1);
            break;
        }
    }
    turnPageAnimation();

    LCD_ShowString(0,  0, (u8 *)("If you press the"), WHITE);
    LCD_ShowString(0, 16, (u8 *)("right button, you"), WHITE);
    LCD_ShowString(0, 32, (u8 *)("will drop faster"), WHITE);
    LCD_ShowString(0, 48, (u8 *)("and get to the"), WHITE);
    LCD_ShowString(0, 64, (u8 *)("ground quicklier."), WHITE);
    
    while (1) {
        if (Get_Button(1)) {
            // wait for the button to be released
            waitForRelease_A(1);
            break;
        }
    }
    turnPageAnimation();

    LCD_ShowString(0,  0, (u8 *)("There are 2 types"), WHITE);
    LCD_ShowString(0, 16, (u8 *)("of obstacles,"), WHITE);
    LCD_ShowString(0, 32, (u8 *)("cacti and"), WHITE);
    LCD_ShowString(0, 48, (u8 *)("pterosaurs. Get"), WHITE);
    LCD_ShowString(0, 64, (u8 *)("over them."), WHITE);

    while (1) {
        if (Get_Button(1)) {
            // wait for the button to be released
            waitForRelease_A(1);
            break;
        }
    }
    turnPageAnimation();

    LCD_ShowString(0,  0, (u8 *)("Notice that"), WHITE);
    LCD_ShowString(0, 16, (u8 *)("cactis are in 2"), WHITE);
    LCD_ShowString(0, 32, (u8 *)("sizes, and you"), WHITE);
    LCD_ShowString(0, 48, (u8 *)("will speed up"), WHITE);
    LCD_ShowString(0, 64, (u8 *)("through time."), WHITE);

    while (1) {
        if (Get_Button(1)) {
            // wait for the button to be released
            waitForRelease_A(1);
            break;
        }
    }
    turnPageAnimation();

    LCD_ShowString(0,  0, (u8 *)("AVOID THE OBSTACLES"), RED);
    LCD_ShowString(0, 16, (u8 *)("OR FACE YOUR DEATH!"), RED);
    LCD_ShowString(0, 32, (u8 *)("LONGER YOU LIVE,"), 0x3397);
    LCD_ShowString(0, 48, (u8 *)("HIGHER THE SCORE!"), 0x3397);
    LCD_ShowString(0, 64, (u8 *)("GOOD LUCK!"), GREEN);

    invincible_mode_countdown = 0;
    while (1) {
        if (Get_Button(1)) {
            // wait for the button to be released
            waitForRelease_A(1);
            invincible_mode_countdown = 0;
            break;
        }
        if (Get_Button(0)) {
            // INVINCIBLE MODE
            waitForRelease_A(0);
            ++invincible_mode_countdown;
        }
        if (invincible_mode_countdown >= 5) {
            // INVINCIBLE MODE break
            invincible_mode_countdown = 5;
            break;
        }
    }

    if (invincible_mode_countdown == 5) {
        LCD_Clear(BLACK);
        LCD_ShowString(0, 64, (u8 *)("Go help to turn off"), WHITE);
        while(1) {
            rgb_update(&rgb_color, &rgb_stage);
            LCD_ShowString(0, 0, (u8 *)("INVINCIBLE MODE"), rgb_color);
            LCD_ShowString(0, 16, (u8 *)("ACTIVATED!"), rgb_color);
            LCD_ShowString(0, 32, (u8 *)("Press right key"), rgb_color);
            LCD_ShowString(0, 48, (u8 *)("to continue"), rgb_color);
            if (Get_Button(1)) {
                // wait for the button to be released
                waitForRelease_A(1);
                break;
            }
        }
    }

    switchAnimation();
    goto game_main_menu;


    game_start:
    switchAnimation();

    // RANDOM NUMBER GENERATION INITIALIZATION
    int *randomSeed  = (int)((float)(rgb_color) * 3.32);
    int *randomSeed2 = (int)((float)(rgb_color) * 2.57);

    /* -------------------------- */
    /*     ENTERING THE GAME!     */
    /* -------------------------- */    
    char debugOutput[20];


    // score update section variables
    int score = 0;
    char scoreboard[20];
    int scoreAddOne = 0;
    int speedUpIndicator = 0;

    // jump control system variables
    int jump_status = 0;
    double jump_tick = 0.0;
    double dinoHeight = 0.0; // current height of Dino from human's point of view
    int dino_y = 72; // current y coordinate on the screen

    // jump parameters
    double jumpDuration = 500.0; // milliseconds
    double jumpHeight = 40.0; // pixels
    double quickDropSpeed = 1.5; // jump ticks per loop



    // dino appearance control variables

    // dinoLookID = -1: N/A
    // dinoLookID =  0: standing
    // dinoLookID =  1: crouch
    int dinoLookID = -1;

    // dinoSwingLegID = 0: left leg straight
    // dinoSwingLegID = 1: right leg straight
    int dinoSwingLegID = 0;

    // indicator of dino step update
    // dino will switch its leg when stepIndicator == 1
    int stepIndicator = 0;

    // enemySpeed initial value
    int enemySpeed = 3;

    // enemy control system variables
    struct enemy_database dinoEnemy[MAX_ENEMY_NUM];
    // database initialization
    for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
        dinoEnemy[i].enemyID = i;
        dinoEnemy[i].enemyValidation = 0;
        dinoEnemy[i].enemyType = 0;
        dinoEnemy[i].enemyLookID = 0;
        dinoEnemy[i].top_left_x = 0;
        dinoEnemy[i].top_left_y = 0;
        dinoEnemy[i].bottom_right_x = 0;
        dinoEnemy[i].bottom_right_y = 0;
    }

    // create and initialize ground decoration dots database
    struct ground_database groundDots;
    groundDots.stage_1_dot_1_x = 160 + 40;
    groundDots.stage_1_dot_2_x = 160 + 60;
    groundDots.stage_1_dot_3_x = 160 + 100;
    groundDots.stage_2_dot_1_x = 160*2 + 70;
    groundDots.stage_2_dot_2_x = 160*2 + 90;

    // show score star just for once
    LCD_ShowPic_Pro(101, 0, 116, 15, star);

    // enemy generation parameters
    // an enemy will spawn after:
    float enemySpawnIntervalFloor   = 0.4; // at least [second(s)]
    float enemySpawnIntervalCeiling = 1.3; // at most  [second(s)]

    int enemySpawnTickFloor = (int)(enemySpawnIntervalFloor * game_tick);
    int enemySpawnTickCeiling = (int)(enemySpawnIntervalCeiling * game_tick);

    int enemySpawnTickInterval;
    int enemySpawnTickCounter = 0;

    while (1) {

        // ===================================================
        // DEBUG BLOCK DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG
        // ===================================================
        // LCD_ShowPic_Pro(1, 1, 20, 20, pter1);
        // sprintf(debugOutput, "SCORE %d", variable);
	    // puts(debugOutput);
        // LCD_ShowString(80, 5, (u8 *)(debugOutput), WHITE);
        // ===================================================

        rgb_update(&rgb_color, &rgb_stage);

        // score & speed update system
        sprintf(scoreboard, "%d", score);
	    puts(scoreboard);
        LCD_ShowString(120, 0, (u8 *)(scoreboard), WHITE);
        
        if ((score+1) % 200 == 0 && scoreAddOne == 0) {
            // speed will increase by 1 after every 200 points
            ++enemySpeed;
            speedUpIndicator = 1;
            if (invincible_mode_countdown != 5) {
                LCD_ShowString(0, 0, (u8 *)("FASTER"), GREEN);
            }
        }

        if (speedUpIndicator == 1 && scoreAddOne == 0 && invincible_mode_countdown != 5) {
            if ((score+1)%200 == 0 || (score+1)%200 == 3 || (score+1)%200 == 6) {
                LCD_ShowString(48, 0, (u8 *)("  >"), 0x03E0);
                LCD_ShowString(48, 0, (u8 *)(" >"), 0x03E0);
                LCD_ShowString(48, 0, (u8 *)(">"), GREEN);
            } else if ((score+1)%200 == 1 || (score+1)%200 == 4 || (score+1)%200 == 7) {
                LCD_ShowString(48, 0, (u8 *)(" >"), GREEN);
                LCD_ShowString(48, 0, (u8 *)(">"), 0x03E0);
            } else if ((score+1)%200 == 2 || (score+1)%200 == 5 || (score+1)%200 == 8) {
                LCD_ShowString(48, 0, (u8 *)("  >"), GREEN);
                LCD_ShowString(48, 0, (u8 *)(" >"), 0x03E0);
                LCD_ShowString(48, 0, (u8 *)(">"), 0x03E0);
            } else if ((score+1)%200 == 9) {
                LCD_ShowString(0, 0, (u8 *)("          "), BLACK);
                speedUpIndicator = 0;
            }
        }
        
        
        ++scoreAddOne;
        if (scoreAddOne == 5) {
            // score add one after every 5 game ticks
            ++score;
            scoreAddOne = 0;
        }


        // enemy generation & initialization control
        if (enemySpawnTickCounter == 0) {
            // calculate when the next enemy spawns
            enemySpawnTickInterval = getEnemySpawnTickInterval_S(enemySpawnTickFloor, enemySpawnTickCeiling, &randomSeed);
        }
        ++enemySpawnTickCounter;

        if (enemySpawnTickCounter >= enemySpawnTickInterval) {
            // if true, add one enemy

            // reset spawn counter
            enemySpawnTickCounter = 0;

            for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
                // search for enemy database vacancy
                if (dinoEnemy[i].enemyValidation == 0) {
                    // found a vacancy and start enemy generation procedure

                    // occupy the vacancy
                    dinoEnemy[i].enemyValidation = 1;

                    // generate enemyType
                    // enemyType == 1: cactus
                    // enemyType == 2: pterosaur
                    dinoEnemy[i].enemyType = randomBoolean(&randomSeed2) + 1;
                    // THE LINE ABOVE REPRESENTS THE ENEMY TYPE STOCHASTIC ALGORITHM
                    // will be changed into a random-number-generator-relied operation soon

                    if (dinoEnemy[i].enemyType == 1) {
                        // initialize cactus's settings

                        // big or small ones?
                        // enemyLookID == 0: small cactus
                        // enemyLookID == 1: bigs cactus
                        dinoEnemy[i].enemyLookID = randomBoolean(&randomSeed2);
                        // THE LINE ABOVE REPRESENTS THE ENEMY LOOK STOCHASTIC ALGORITHM
                        // will be changed into a random-number-generator-relied operation soon
                        
                        if (dinoEnemy[i].enemyLookID == 0) { // draw cactus 0
                            // set initial coordinates
                            dinoEnemy[i].top_left_x = 160 - 2; // "2" is width
                            dinoEnemy[i].top_left_y = 72 - 17; // "17" is height
                            dinoEnemy[i].bottom_right_x = 159;
                            dinoEnemy[i].bottom_right_y = 72;
                            
                            // show the newly-generated enemy
                            drawEnemy_cactus_0(dinoEnemy[i].top_left_x, dinoEnemy[i].top_left_y, WHITE);
                        
                        } else if (dinoEnemy[i].enemyLookID == 1) { // draw cactus 1
                            // set initial coordinates
                            dinoEnemy[i].top_left_x = 160 - 4; // "4" is width
                            dinoEnemy[i].top_left_y = 72 - 24; // "24" is height
                            dinoEnemy[i].bottom_right_x = 159;
                            dinoEnemy[i].bottom_right_y = 72;
                            
                            // show the newly-generated enemy
                            drawEnemy_cactus_1(dinoEnemy[i].top_left_x, dinoEnemy[i].top_left_y, WHITE);
                        }

                    } else if (dinoEnemy[i].enemyType == 2) {
                        // initialize pterosaur's settings
                        
                        // higher or lower ones?
                        // enemyLookID == 0: higher pterosaur
                        // enemyLookID == 1: lower pterosaur
                        dinoEnemy[i].enemyLookID = random012(&randomSeed2);
                        // THE LINE ABOVE REPRESENTS THE ENEMY LOOK STOCHASTIC ALGORITHM
                        // will be changed into a random-number-generator-relied operation soon

                        if (dinoEnemy[i].enemyLookID == 0) {
                            dinoEnemy[i].top_left_x = 160 + 1 - 20; // "20" is width
                            dinoEnemy[i].top_left_y = 57  + 1 - 20; // "20" is height
                            dinoEnemy[i].bottom_right_x = 160;
                            dinoEnemy[i].bottom_right_y = 57;

                            // show the newly-generated enemy
                            LCD_ShowPic_Pro(dinoEnemy[i].top_left_x, dinoEnemy[i].top_left_y, \
                                            dinoEnemy[i].bottom_right_x, dinoEnemy[i].bottom_right_y, \
                                            pter1);
                        
                        } else if (dinoEnemy[i].enemyLookID == 1) {
                            dinoEnemy[i].top_left_x = 160 + 1 - 20; // "20" is width
                            dinoEnemy[i].top_left_y = 72  + 1 - 20; // "20" is height
                            dinoEnemy[i].bottom_right_x = 160;
                            dinoEnemy[i].bottom_right_y = 72;

                            // show the newly-generated enemy
                            LCD_ShowPic_Pro(dinoEnemy[i].top_left_x, dinoEnemy[i].top_left_y, \
                                            dinoEnemy[i].bottom_right_x, dinoEnemy[i].bottom_right_y, \
                                            pter1);
                        
                        } else if (dinoEnemy[i].enemyLookID == 2) {
                            dinoEnemy[i].top_left_x = 160 + 1 - 20; // "20" is width
                            dinoEnemy[i].top_left_y = 40  + 1 - 20; // "20" is height
                            dinoEnemy[i].bottom_right_x = 160;
                            dinoEnemy[i].bottom_right_y = 40;

                            // show the newly-generated enemy
                            LCD_ShowPic_Pro(dinoEnemy[i].top_left_x, dinoEnemy[i].top_left_y, \
                                            dinoEnemy[i].bottom_right_x, dinoEnemy[i].bottom_right_y, \
                                            pter1);
                        }

                    }

                    // enemy won't spawn continuously, so break
                    break;
                }
            }
        }

        // enemy movement control system
        for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
            // detects whether there is a valid enemy in the vacancy
            if (dinoEnemy[i].enemyValidation == 1) {
                // detects enemyType

                // Moving control
                // enemyType == 1: cactus
                // enemyType == 2: pterosaur
                if (dinoEnemy[i].enemyType == 1) {
                    // detects enemyLookID and move it
                    // enemyLookID == 0: small cactus
                    // enemyLookID == 1: big cactus
                    if (dinoEnemy[i].enemyLookID == 0) { // cactus 0
                        // erase the old one
                        drawEnemy_cactus_0(dinoEnemy[i].top_left_x, dinoEnemy[i].top_left_y, BLACK);
                        // update coordinate info
                        dinoEnemy[i].top_left_x = dinoEnemy[i].top_left_x - enemySpeed;
                        dinoEnemy[i].bottom_right_x = dinoEnemy[i].bottom_right_x - enemySpeed;
                        // draw the new one
                        drawEnemy_cactus_0(dinoEnemy[i].top_left_x, dinoEnemy[i].top_left_y, WHITE);
                    
                    } else if (dinoEnemy[i].enemyLookID == 1) { // cactus 1
                        // erase the old one
                        drawEnemy_cactus_1(dinoEnemy[i].top_left_x, dinoEnemy[i].top_left_y, BLACK);
                        // update coordinate info
                        dinoEnemy[i].top_left_x = dinoEnemy[i].top_left_x - enemySpeed;
                        dinoEnemy[i].bottom_right_x = dinoEnemy[i].bottom_right_x - enemySpeed;
                        // draw the new one
                        drawEnemy_cactus_1(dinoEnemy[i].top_left_x, dinoEnemy[i].top_left_y, WHITE);

                    }
                } else if (dinoEnemy[i].enemyType == 2) {
                    // erase the old one
                    LCD_ShowPic_Pro(dinoEnemy[i].top_left_x, dinoEnemy[i].top_left_y, \
                                    dinoEnemy[i].bottom_right_x, dinoEnemy[i].bottom_right_y, \
                                    squareEraser);
                    
                    // update coordinate info
                    dinoEnemy[i].top_left_x = dinoEnemy[i].top_left_x - enemySpeed;
                    dinoEnemy[i].bottom_right_x = dinoEnemy[i].bottom_right_x - enemySpeed;

                    // draw the new one
                    if (stepIndicator / 4 == 0) {
                        // draw the upper wing
                        LCD_ShowPic_Pro(dinoEnemy[i].top_left_x, dinoEnemy[i].top_left_y, \
                                    dinoEnemy[i].bottom_right_x, dinoEnemy[i].bottom_right_y, \
                                    pter2);
                    } else if (stepIndicator / 4 == 1) {
                        // draw the lower wing
                        LCD_ShowPic_Pro(dinoEnemy[i].top_left_x, dinoEnemy[i].top_left_y, \
                                    dinoEnemy[i].bottom_right_x, dinoEnemy[i].bottom_right_y, \
                                    pter1);
                    }
                }

                // vanishment control
                // if the enemy reaches the border of the screen, 
                // make it disappear and remove its validation
                if (dinoEnemy[i].top_left_x < enemySpeed) {
                    if (dinoEnemy[i].enemyType == 1) {
                        // detects enemyLookID and make it disappear
                        // enemyLookID == 0: small cactus
                        // enemyLookID == 1: big cactus
                        if (dinoEnemy[i].enemyLookID == 0) { // cactus 0
                            // erase
                            drawEnemy_cactus_0(dinoEnemy[i].top_left_x, dinoEnemy[i].top_left_y, BLACK);
                            // invalidate
                            dinoEnemy[i].enemyValidation = 0;
                        
                        } else if (dinoEnemy[i].enemyLookID == 1) { // cactus 1
                            // erase
                            drawEnemy_cactus_1(dinoEnemy[i].top_left_x, dinoEnemy[i].top_left_y, BLACK);
                            // invalidate
                            dinoEnemy[i].enemyValidation = 0;
                        }
                    } else if (dinoEnemy[i].enemyType == 2) {
                        // erase
                        LCD_ShowPic_Pro(dinoEnemy[i].top_left_x, dinoEnemy[i].top_left_y, \
                                        dinoEnemy[i].bottom_right_x, dinoEnemy[i].bottom_right_y, \
                                        squareEraser);
                        // invalidate
                        dinoEnemy[i].enemyValidation = 0;
                    }
                    
                }
            }
        }

        // dino appearance & position control system
        // dino step update indicator
        ++stepIndicator;
        if (stepIndicator == 8) {
            stepIndicator = 0;
        }

        // erase the old dino image
        if (dinoLookID == 0) {
            LCD_ShowPic_Pro(6, dino_y-19, 25, dino_y, squareEraser);
        } else if (dinoLookID == 1) {
            LCD_ShowPic_Pro(6, dino_y-19, 32, dino_y, crouchEraser);
        }

        // erase invincible indicator if invincible
        if (invincible_mode_countdown == 5) {
            if (dinoLookID == 0) {
                LCD_DrawRectangle(5, dino_y-20, 26, dino_y+1, BLACK);
            } else if (dinoLookID == 1) {
                LCD_DrawRectangle(5, dino_y-20, 33, dino_y+1, BLACK);
            }
        }

        // start computing the dino position of next tick

        // crouch or not? update dinoLookID
        if (Get_Button(1)) { // crouch
            dinoLookID = 1;
        } else { // Keep standing
            dinoLookID = 0;
        }

        // will dino jump? update jumping state indicator
        if (Get_Button(0)) {
            jump_status = 1;
        }

        // dino y coordinate update system
        if (jump_status == 1) {
            ++jump_tick;
            // quick drop 
            if (dinoLookID == 1 && jump_tick >= (jumpDuration/40) ) {
                jump_tick = jump_tick + quickDropSpeed;
            }
            // update height info
            // dino jump curve
            // dynamic jump curve
            dinoHeight = jump_tick*80*jumpHeight/jumpDuration*(1-20*jump_tick/jumpDuration);
            int dinoHeightInt = (int)dinoHeight;
            dino_y = 72 - dinoHeightInt;
            if (jump_tick >= (jumpDuration/20) ) {
                // reset and exit jump status
                jump_tick = 0;
                jump_status = 0;
            }
        }

        // dino appears at the expected coordinate with proper form
        if (jump_status == 1) {
            // dino is above the ground and its legs are stationary
            if (dinoLookID == 0) {
                // standing while in the air
                LCD_ShowPic_Pro(6, dino_y-19, 25, dino_y, trex3);
            } else if (dinoLookID == 1) {
                // crouching while in the air
                LCD_ShowPic_Pro(6, dino_y-19, 32, dino_y, trex5);
            }
        } else if (jump_status == 0) {
            // dino is running on the ground
            dino_y = 72; // refresh dino y coordinate
            if (dinoLookID == 0) {
                // standing
                if (dinoSwingLegID == 0) {
                    // left leg out
                    LCD_ShowPic_Pro(6, dino_y-19, 25, dino_y, trex2);
                } else if (dinoSwingLegID == 1) {
                    // right leg out
                    LCD_ShowPic_Pro(6, dino_y-19, 25, dino_y, trex1);
                }

            } else if (dinoLookID == 1) {
                // crouching
                if (dinoSwingLegID == 0) {
                    // left leg out
                    LCD_ShowPic_Pro(6, dino_y-19, 32, dino_y, trex4);
                } else if (dinoSwingLegID == 1) {
                    // right leg out
                    LCD_ShowPic_Pro(6, dino_y-19, 32, dino_y, trex5);
                }
            }

            // change dino's leg
            if (stepIndicator == 0) {                
                // dinoSwingLegID will change between 0 and 1
                dinoSwingLegID = (dinoSwingLegID + 1) % 2;
            }
            
        }

        // ground rolling system
        LCD_DrawLine(0, 72, 160, 72, WHITE); // refresh line-like ground
        
        // ground decoration dots update system
        // erase the old ones
        LCD_DrawPoint(groundDots.stage_1_dot_1_x, 75, BLACK);
        LCD_DrawPoint(groundDots.stage_1_dot_2_x, 80, BLACK);
        LCD_DrawPoint(groundDots.stage_1_dot_3_x, 78, BLACK);
        LCD_DrawPoint(groundDots.stage_2_dot_1_x, 73, BLACK);
        LCD_DrawPoint(groundDots.stage_2_dot_2_x, 76, BLACK);
        // update x coordinates
        groundDots.stage_1_dot_1_x = groundDots.stage_1_dot_1_x - enemySpeed;
        groundDots.stage_1_dot_2_x = groundDots.stage_1_dot_2_x - enemySpeed;
        groundDots.stage_1_dot_3_x = groundDots.stage_1_dot_3_x - enemySpeed;
        groundDots.stage_2_dot_1_x = groundDots.stage_2_dot_1_x - enemySpeed;
        groundDots.stage_2_dot_2_x = groundDots.stage_2_dot_2_x - enemySpeed;
        // return to the most right if reaching the boarder
        if (groundDots.stage_1_dot_1_x < enemySpeed) {
            groundDots.stage_1_dot_1_x = 160 + 40;
        }
        if (groundDots.stage_1_dot_2_x < enemySpeed) {
            groundDots.stage_1_dot_2_x = 160 + 60;
        }
        if (groundDots.stage_1_dot_3_x < enemySpeed) {
            groundDots.stage_1_dot_3_x = 160 + 100;
        }
        if (groundDots.stage_2_dot_1_x < enemySpeed) {
            groundDots.stage_2_dot_1_x = 160*2 + 70;
        }
        if (groundDots.stage_2_dot_2_x < enemySpeed) {
            groundDots.stage_2_dot_2_x = 160*2 + 90;
        }
        // draw the new ones
        LCD_DrawPoint(groundDots.stage_1_dot_1_x, 75, WHITE);
        LCD_DrawPoint(groundDots.stage_1_dot_2_x, 80, WHITE);
        LCD_DrawPoint(groundDots.stage_1_dot_3_x, 78, WHITE);
        LCD_DrawPoint(groundDots.stage_2_dot_1_x, 73, WHITE);
        LCD_DrawPoint(groundDots.stage_2_dot_2_x, 76, WHITE);

        // invincible mode indicator
        if (invincible_mode_countdown == 5) {
            if (dinoLookID == 0) {
                LCD_DrawRectangle(5, dino_y-20, 26, dino_y+1, rgb_color);
            } else if (dinoLookID == 1) {
                LCD_DrawRectangle(5, dino_y-20, 33, dino_y+1, rgb_color);
            }
            if (Get_Button(0) && Get_Button(1)) {
                // suicide operation
                ++suicide_countdown;
                if (suicide_countdown >= 50) {
                    goto GAME_OVER;
                }
            } else {
                suicide_countdown = 0;
            }
        }

        // Dino life control & collision detection system
        // repeatedly detects whether Dino collides with the enemy
        if (invincible_mode_countdown != 5) {
            for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
                // detects whether there is a valid enemy in the vacancy
                if (dinoEnemy[i].enemyValidation == 1) {
                    // detects enemyType
                    // enemyType == 1: cactus
                    // enemyType == 2: pterosaur
                    int temp_parameter[2];

                    if (dinoLookID == 0) {
                        // standing hixbox parameter
                        temp_parameter[0] = 24;
                        temp_parameter[1] = 19;
                    } else {
                        // crouching hixbox parameter
                        temp_parameter[0] = 31;
                        temp_parameter[1] = 12;
                    }

                    if (dinoEnemy[i].enemyType == 1) {                    
                        if (dinoEnemy[i].top_left_x < temp_parameter[0] && dinoEnemy[i].bottom_right_x > 7 && \
                            dinoEnemy[i].top_left_y < dino_y) {
                            // HIT!!
                            goto GAME_OVER;
                        }
                    } else if (dinoEnemy[i].enemyType == 2) {
                        if (dinoEnemy[i].top_left_x < temp_parameter[0] && dinoEnemy[i].bottom_right_x > 7 && \
                            dinoEnemy[i].top_left_y < dino_y && dinoEnemy[i].bottom_right_y > dino_y-temp_parameter[1]) {
                            // HIT!!
                            goto GAME_OVER;
                        }
                    }
                    
                }
                    
            }
        } else {
            LCD_ShowString(0, 0, (u8 *)("INVINCIBLE"), rgb_color);
        }


        // game tick proceed
        delay_1ms(delay_interval);
        // delay_1ms(100); // debug


        // game pausing control
        if (Get_BOOT0() == 1) {
            waitForRelease_BOOT0();
            // game paused
            for (int i = 0; i < 2; ++i) {
                LCD_ShowString(40, 16, (u8 *)("GAME PAUSED"), GREEN);
                delay_1ms(800);
                LCD_ShowString(40, 16, (u8 *)("GAME PAUSED"), BLACK);
                delay_1ms(200);
            }
            while (1) {
                if (Get_BOOT0() == 1) {
                    waitForRelease_BOOT0();
                    // game continues
                    LCD_ShowString(40, 16, (u8 *)("GAME PAUSED"), BLACK);
                    LCD_ShowString(40, 16, (u8 *)("3..."), GREEN);
                    delay_1ms(300);
                    LCD_ShowString(40, 16, (u8 *)("2..."), GREEN);
                    delay_1ms(300);
                    LCD_ShowString(40, 16, (u8 *)("1..."), GREEN);
                    delay_1ms(300);
                    LCD_ShowString(40, 16, (u8 *)("GO!  "), GREEN);
                    delay_1ms(300);
                    LCD_ShowString(40, 16, (u8 *)("GAME PAUSED"), BLACK);
                    break;
                }
                LCD_ShowString(40, 16, (u8 *)("GAME PAUSED"), GREEN);
                delay_1ms(800);
                LCD_ShowString(40, 16, (u8 *)("GAME PAUSED"), BLACK);
                delay_1ms(200);
            }
        }
    }

    GAME_OVER:
    // clear top-left info
    LCD_ShowString(0, 0, (u8 *)("          "), BLACK);
    
    // deactivate rgb shield
    if (invincible_mode_countdown == 5) {
        LCD_DrawRectangle(5, dino_y-20, 33, dino_y+1, BLACK);
    }

    // dino eyes shows "X"
    if (dinoLookID == 0) {
        LCD_ShowPic_Pro(6, dino_y-19, 25, dino_y, trex_stand_death);
    } else if (dinoLookID == 1) {
        LCD_ShowPic_Pro(6, dino_y-19, 32, dino_y, trex_crouch_death);
    }
    
    LCD_DrawLine(0, 72, 160, 72, WHITE); // refresh line-like ground

    // "game over" blinks
    for (int i = 0; i < 4; ++i) {
        LCD_ShowString(42, 28, (u8 *)("GAME OVER!"), RED);
        delay_1ms(250);
        LCD_ShowString(42, 28, (u8 *)("GAME OVER!"), BLACK);
        delay_1ms(80);
    }

    // death animation
    int death_animation_delay = 20; // ms
    int dino_death_dropSpeed = 4;
    if (dinoLookID == 0) {
        while (dino_y < 81) {
            LCD_ShowPic_Pro(6, dino_y-19, 25, dino_y, squareEraser);
            dino_y -= dino_death_dropSpeed;
            LCD_ShowPic_Pro(6, dino_y-19, 25, dino_y, trex_stand_death);
            dino_death_dropSpeed--;
            LCD_DrawLine(0, 72, 160, 72, WHITE); // refresh line-like ground
            // delay_1ms(death_animation_delay);
            delay_1ms(death_animation_delay);
        }
        LCD_ShowPic_Pro(6, dino_y-19, 25, dino_y, squareEraser);
        LCD_DrawLine(0, 72, 160, 72, WHITE); // refresh line-like ground
    } else if (dinoLookID == 1) {
        while (dino_y < 81) {
            LCD_ShowPic_Pro(6, dino_y-19, 32, dino_y, crouchEraser);
            dino_y -= dino_death_dropSpeed;
            LCD_ShowPic_Pro(6, dino_y-19, 32, dino_y, trex_crouch_death);
            dino_death_dropSpeed--;
            LCD_DrawLine(0, 72, 160, 72, WHITE); // refresh line-like ground
            delay_1ms(death_animation_delay);
        }
        LCD_ShowPic_Pro(6, dino_y-19, 32, dino_y, crouchEraser);
        LCD_DrawLine(0, 72, 160, 72, WHITE); // refresh line-like ground
    }

    delay_1ms(300);

    // "your score"
    switchAnimation();
    LCD_ShowString(42, 20, (u8 *)("YOUR SCORE"), WHITE);
    delay_1ms(800);
    // will run differently depend on whether the player breaks the record
    if (score > highest_score) {
        highest_score = score;
        // show the score in RGB
        sprintf(scoreboard, "%d", score);
        puts(scoreboard);
        for (int i = 0; i < 50; ++i) {
            rgb_update(&rgb_color, &rgb_stage);
            LCD_ShowString(70, 42, (u8 *)(scoreboard), rgb_color);            
            delay_1ms(20);
        }
        while (1) {
            rgb_update(&rgb_color, &rgb_stage);
            LCD_ShowString(13, 20, (u8 *)("NEW HIGHEST SCORE"), rgb_color);
            LCD_ShowString(70, 42, (u8 *)(scoreboard), rgb_color);
            
            if (Get_Button(0)) {
                // wait for the button to be released
                waitForRelease_A(0);
                break;
            }
            
            delay_1ms(20);
        }
    } else {
        // did not break the record
        // show the score in RGB
        sprintf(scoreboard, "%d", score);
        puts(scoreboard);
        while (1) {
            rgb_update(&rgb_color, &rgb_stage);
            LCD_ShowString(70, 42, (u8 *)(scoreboard), rgb_color);
            
            if (Get_Button(0)) {
                // wait for the button to be released
                waitForRelease_A(0);
                break;
            }
            
            delay_1ms(20);
        }

        turnPageAnimation();

        while (1) {
            rgb_update(&rgb_color, &rgb_stage);
            LCD_ShowString(30, 20, (u8 *)("HIGHEST SCORE"), WHITE);
            LCD_ShowNum(53, 42, highest_score, 4, rgb_color);

            if (Get_Button(0)) {
                // wait for the button to be released
                waitForRelease_A(0);
                break;
            }
            
            delay_1ms(20);
        }
    }

    goto GAME_RESTART;

}
