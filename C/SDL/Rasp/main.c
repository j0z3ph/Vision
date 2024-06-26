/**
 * @file main.c
 * @author Jose Luis Cruz (j0z3ph@gmail.com)
 * @brief Simple SDL sample.
 * 1. Render texture and
 * 2. Handle keyboard and mouse events and
 * 3. Perform basic texture motion.
 * Controls:
 * LEFT ARROW. Moves mushroom to the left
 * RIGHT ARROW. Moves mushroom to the right
 * SPACEBAR. Makes mushroom to jump
 * CLICK. Moves mushroom to the cursor location
 * @version 0.1
 * @date 2022-12-12
 *
 * @copyright MIT
 *
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <wiringPi.h>

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800
#define FPS 60
#define SPEED 10
#define GRAVITY 1
#define JUMP -20

#define true 1
#define false 0

int main()
{
    wiringPiSetupGpio(); // Initialize Raspberry Pi's GPIO

    SDL_Init(SDL_INIT_VIDEO);   // Initialize SDL
    IMG_Init(IMG_INIT_PNG);     // Initialize IMG
    SDL_Rect r, rMouse;         // Mushroom and Shoot positions
    SDL_Event event;            // For handling events
    int running = true;         // Flag for main loop
    float x_vel = 0, y_vel = 0; // X and Y velocity
    // int jump_pressed = false; // Flag that indicates spacebar was/wasn't pressed
    int left_pressed = false;  // Flag that indicates left arrow was/wasn't pressed
    int right_pressed = false; // Flag that indicates right arrow was/wasn't pressed
    int fullscreen = false;

    // GPIO pins and variables
    int leftbtn, rightbtn, jumpbtn;
    int leftPin = 17, rightPin = 27, jumpPin = 22;

    int winH, winW; // Window height and width

    // Creates new SDL window
    SDL_Window *gWindow = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                           SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    // Creates the render context of the window
    SDL_Renderer *gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF); // Sets white background color

    SDL_Texture *gTexture = NULL;      // Mushroom texture
    SDL_Texture *gTextureShoot = NULL; // Shoot texture

    SDL_Surface *img = IMG_Load("hongo.png"); // Loads PNG file

    gTexture = SDL_CreateTextureFromSurface(gRenderer, img); // Creates mushroom texture from file
    SDL_FreeSurface(img);                                    // Release surface

    img = IMG_Load("shoot.png");                                  // Loads PNG file
    gTextureShoot = SDL_CreateTextureFromSurface(gRenderer, img); // Creates shoot texture from file
    SDL_FreeSurface(img);                                         // Release surface

    SDL_GetWindowSize(gWindow, &winW, &winH); // Gets current window size

    // Sets mushroom texture initial position
    // and dimensions
    r.x = 0;
    r.y = winH - 50;
    r.h = 50;
    r.w = 50;

    // Sets shoot texture initial position
    // and dimensions
    rMouse.x = 0;
    rMouse.y = 0;
    rMouse.h = 50;
    rMouse.w = 50;

    // pin mode..(INPUT, OUTPUT, PWM_OUTPUT, GPIO_CLOCK)
    pinMode(leftPin, INPUT);
    pinMode(rightPin, INPUT);
    pinMode(jumpPin, INPUT);

    // pull up/down mode (PUD_OFF, PUD_UP, PUD_DOWN)
    pullUpDnControl(leftPin, PUD_UP);
    pullUpDnControl(rightPin, PUD_UP);
    pullUpDnControl(jumpPin, PUD_UP);

    // Main loop
    while (running)
    {
        // Digital ports readings
        leftbtn = digitalRead(leftPin);
        rightbtn = digitalRead(rightPin);
        jumpbtn = digitalRead(jumpPin);

        // Updating flags
        right_pressed = !rightbtn;
        left_pressed = !leftbtn;
        y_vel = jumpbtn == LOW ? JUMP : y_vel;

        y_vel += GRAVITY;                               // Applies gravity to the mushroom
        x_vel = (right_pressed - left_pressed) * SPEED; // Applies speed to the mushroom
        // If right arrow was pressed, applies positive speed
        // If left arrow was pressed, applies negative speed
        // If neither left or right arrows were pressed, applies 0 speed

        // If an event occurs
        while (SDL_PollEvent(&event))
        {
            // If user requests to close main window
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            // If a key was pressed
            if (event.type == SDL_KEYDOWN)
            {
                // Adjust the flags
                switch (event.key.keysym.sym)
                {
                case SDLK_SPACE:  // Spacebar
                    y_vel = JUMP; // Sets min value to Y coordinate
                    break;
                case SDLK_LEFT: // LEFT
                    left_pressed = true;
                    break;
                case SDLK_RIGHT: // RIGHT
                    right_pressed = true;
                    break;
                case SDLK_ESCAPE:
                    running = false;
                    break;
                case SDLK_RETURN:
                    fullscreen = !fullscreen;
                    if (fullscreen)
                    {
                        SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN);
                        SDL_GetWindowSize(gWindow, &winW, &winH);
                    }
                    else
                    {
                        SDL_SetWindowFullscreen(gWindow, 0);
                        SDL_GetWindowSize(gWindow, &winW, &winH);
                    }
                }
            }
            if (event.type == SDL_KEYUP)
            {
                // Adjust the flags
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT: // LEFT
                    left_pressed = false;
                    break;
                case SDLK_RIGHT: // RIGHT
                    right_pressed = false;
                    break;
                }
            }

            // If mouse event happened
            if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
            {
                // Adjust the shoot or mushroom location
                switch (event.type)
                {
                case SDL_MOUSEMOTION:
                    // Get mouse position
                    SDL_GetMouseState(&rMouse.x, &rMouse.y);
                    // Adjust to center
                    rMouse.x = rMouse.x - (rMouse.w / 2);
                    rMouse.y = rMouse.y - (rMouse.h / 2);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    // Get mouse position
                    SDL_GetMouseState(&r.x, &r.y);
                    r.x = r.x - (r.w / 2);
                    r.y = r.y - (r.h / 2);
                    y_vel = JUMP / 2; // Sets half of jump
                    break;
                case SDL_MOUSEBUTTONUP:
                    break;
                }
            }
        }

        r.x += x_vel; // Computes new X coordinate
        r.y += y_vel; // Computes new Y coordinate

        // If the mushroom went too far to the left
        if (r.x < 0)
            r.x = 0;

        // If the mushroom went too far to the right
        if ((r.x + r.w) > winW)
            r.x = winW - r.w;

        // If the mushroom went too far down
        if ((r.y + r.h) > winH)
        {
            r.y = winH - r.h;
            y_vel = 0;
        }

        // Clear screen
        SDL_RenderClear(gRenderer);
        // Render textures to screen
        SDL_RenderCopy(gRenderer, gTexture, NULL, &r);
        SDL_RenderCopy(gRenderer, gTextureShoot, NULL, &rMouse);

        // Update screen
        SDL_RenderPresent(gRenderer);

        // Waits for next fps
        SDL_Delay(1000 / FPS);
    }

    // Destroy textures
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;
    SDL_DestroyTexture(gTextureShoot);
    gTexture = NULL;

    // Destroy render and window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();

    return 0;
}
