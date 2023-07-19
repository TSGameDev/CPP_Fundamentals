#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData UpdateAnimations(AnimData data, float DeltaTime, int frameMax)
{
    // update running time
    data.runningTime += DeltaTime;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        // update animation frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > frameMax)
        {
            data.frame = 0;
        }
    }
    return data;
}

float ScrollBackground(float Xvalue, Texture2D scrollingTexture, float scrollSpeed, float DeltaTime)
{
    Xvalue -= scrollSpeed * DeltaTime;
    if (Xvalue <= -scrollingTexture.width * 2)
    {
        Xvalue = 0;
    }
    return Xvalue;
}

void DrawScrollingBackground(Texture2D scrollTexture, float scrollTextureX)
{
    Vector2 firstTexture{ scrollTextureX, 0.0 };
    DrawTextureEx(scrollTexture, firstTexture, 0.0, 2.0, WHITE);
    Vector2 secondTexture{ scrollTextureX + scrollTexture.width * 2, 0.0 };
    DrawTextureEx(scrollTexture, secondTexture, 0.0, 2.0, WHITE);
}

int main()
{
    // array with window dimensions
    float windowDimensions[2];
    windowDimensions[0] = 512.f;
    windowDimensions[1] = 380.f;

    // initialize the window
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher!");

    // acceleration due to gravity (pixels/s)/s
    const int gravity{ 1'000 };
    // nebula X velocity (pixels/second)
    int nebVel{ -200 };

    // nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    const int sizeOfNebulae = 3;
    AnimData nebulae[sizeOfNebulae]{};
    int nebulaDifferencePos = 300;
    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i] = {
        {0.0, 0.0, nebula.width / 8.f, nebula.height / 8.f}, // Rectangle rec
        {windowDimensions[0] + (nebulaDifferencePos * i), windowDimensions[1] - nebula.height / 8}, // Vector2 pos
        0, // int frame
        1.0 / 12.0, // float updateTime
        0 // float runningTime
        };
    }
    float finishLine = nebulae[sizeOfNebulae - 1].pos.x;

    // scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0] / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0.0;

    // is the rectanlge in the air?
    bool isInAir{};
    // jump velocity (pixels/second)
    const int jumpVel{ -600 };

    int velocity{ 0 };

    Texture2D farBackground = LoadTexture("textures/far-buildings.png");
    float farBackgroundX{ 0 };
    float farBackgroundScrollSpeed = 50;

    Texture2D midBackground = LoadTexture("textures/back-buildings.png");
    float midBackgroundX{ 0 };
    float midBackgroundScrollSpeed = 100;

    Texture2D closeBackground = LoadTexture("textures/foreground.png");
    float closeBackgroundX{ 0 };
    float closeBackgroundScrollSpeed = 150;

    bool collision = false;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // delta time (time since last frame)
        const float dT{ GetFrameTime() };

        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        farBackgroundX = ScrollBackground(farBackgroundX, farBackground, dT, farBackgroundScrollSpeed);
        midBackgroundX = ScrollBackground(midBackgroundX, midBackground, dT, midBackgroundScrollSpeed);
        closeBackgroundX = ScrollBackground(closeBackgroundX, closeBackground, dT, closeBackgroundScrollSpeed);

        DrawScrollingBackground(farBackground, farBackgroundX);
        DrawScrollingBackground(midBackground, midBackgroundX);
        DrawScrollingBackground(closeBackground, closeBackgroundX);

        // perform ground check
        if (isOnGround(scarfyData, windowDimensions[1]))
        {
            // rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // rectangle is in the air
            velocity += gravity * dT;
            isInAir = true;
        }

        // jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            // update nebula position
            nebulae[i].pos.x += nebVel * dT;
        }
        finishLine += nebVel * dT;
        // update scarfy position
        scarfyData.pos.y += velocity * dT;

        //calculate collisions
        Rectangle scarfyCollisionRect
        {
            scarfyData.pos.x,
            scarfyData.pos.y,
            scarfyData.rec.width,
            scarfyData.rec.height
        };

        for (AnimData nebulaEntity : nebulae)
        {
            float collisionPad = 50;
            Rectangle nebCollisionRect
            {
                nebulaEntity.pos.x + collisionPad,
                nebulaEntity.pos.y + collisionPad,
                nebulaEntity.rec.width - 2 * collisionPad,
                nebulaEntity.rec.height - 2 * collisionPad
            };

            if (CheckCollisionRecs(nebCollisionRect, scarfyCollisionRect))
            {
                collision = true;
            }
        }

        // update scarfy's animation frame
        if (!isInAir)
        {
            scarfyData = UpdateAnimations(scarfyData, dT, 5);
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i] = UpdateAnimations(nebulae[i], dT, 7);
        }

        if (collision)
        {
            DrawText("YOU LOSE!!!", windowDimensions[0] / 4, windowDimensions[1] / 2, 48, RED);
        }
        else if (scarfyData.pos.x >= finishLine)
        {
            DrawText("YOU WIN!!!", windowDimensions[0] / 2, windowDimensions[1] / 2, 48, GREEN);
        }
        else
        {
            for (int i = 0; i < sizeOfNebulae; i++)
            {
                // draw nebula
                DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
            }
            // draw scarfy
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        }

        // stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}