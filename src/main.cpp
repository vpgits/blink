#include <iostream>
#include <random>
#include "raylib.h"
#include <vector>

double generateRandomValue(const int *level) {
    double min = 1.25 * (double(*level)) + 1;
    double max = 9.75 * (double(*level)) + 1;
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

void performLevel(int *level, double *randomValue, double *timer, Rectangle *button, std::vector<double> *scores,
                  bool *isButtonEnabled, double *startTime, double *waitTime) {
    bool isButtonClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    if (isButtonClicked) {
        Vector2 mousePointer = GetMousePosition();
        double currentTime = GetTime();
        if (CheckCollisionPointRec(mousePointer, *button)) {
            scores->push_back(currentTime - *waitTime);
            (*level)++;
            *randomValue = generateRandomValue(level);
            *isButtonEnabled = false;
            *startTime = currentTime;
            *timer = 0.0f;
            *waitTime = 0.0f;
        }
    }
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Timer Example");

    SetTargetFPS(60); // Set the application to run at 60 frames-per-second

    // Variables to store the elapsed time and the start time
    double timer = 0.0f;
    double waitTime = 0.0f;
    double startTime = GetTime();
    int level = 0;
    double randomValue = generateRandomValue(&level);
    bool isButtonEnabled = false;
    std::vector<double> scores;
    Rectangle button = {10, 200, 100, 40};

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        double currentTime = GetTime();
        if (randomValue > currentTime - startTime && currentTime - startTime > timer) {
            timer = currentTime - startTime;
        } else {
            if (!isButtonEnabled) {
                waitTime = currentTime;
                isButtonEnabled = true;
            }
            timer = randomValue;
            performLevel(&level, &randomValue, &timer, &button, &scores, &isButtonEnabled, &startTime, &waitTime);
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText(TextFormat("Random Value: %.2f", randomValue), 10, 40, 20, BLACK);

        DrawRectangleRec(button, isButtonEnabled ? MAROON : GRAY);
        DrawText("Click Me!", (int) button.x + 10, (int) button.y + 10, 20, WHITE);

        // Draw the scores
        for (int i = 0; i < scores.size(); i++) {
            DrawText(TextFormat("Score %d: %.2f", i + 1, scores[i]), screenWidth - 150, 30 + 30 * i, 20, BLACK);
        }

        // Draw the timer value
        DrawText(TextFormat("Elapsed Time: %.2f", timer), 10, 10, 20, BLACK);
        // Draw the time that has been waited
        DrawText(TextFormat("Wait Time: %.2f", isButtonEnabled ? currentTime - waitTime : 0.0f), 10, 70, 20, BLACK);
        DrawFPS(screenWidth - 30, 10);

        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}


