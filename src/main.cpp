#include <cstdlib>

#include "raylib.h"

#include "config.h"


#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

// Clamp Vector2 value with MIN and MAX and return a new vector2
// NOTE: Required for virtual mouse, to clamp inside virtual game size
Vector2 ClampValue(Vector2 value, Vector2 MIN, Vector2 MAX) {
    Vector2 result = value;
    result.x = (result.x > MAX.x) ? MAX.x : result.x;
    result.x = (result.x < MIN.x) ? MIN.x : result.x;
    result.y = (result.y > MAX.y) ? MAX.y : result.y;
    result.y = (result.y < MIN.y) ? MIN.y : result.y;
    return result;
}


int main() {
    // Enable config flags for resizable window and vertical synchro
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetWindowMinSize(Game::ScreenWidth / 2, Game::ScreenHeight / 2);
    // Set game to run at 60 frames-per-second
    SetTargetFPS(60);

    // Render texture initialization, used to hold the rendering result so we can easily resize it
    RenderTexture2D target = LoadRenderTexture(Game::ScreenWidth, Game::ScreenHeight);
    // Texture scale filter to use
    SetTextureFilter(target.texture, FILTER_BILINEAR);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif



    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Compute required framebuffer scaling
        float scale = MIN((float) GetScreenWidth() / Game::ScreenWidth, (float) GetScreenHeight() / Game::ScreenHeight);

        // Update virtual mouse (clamped mouse value behind game screen)
        Vector2 mouse = GetMousePosition();
        Vector2 virtualMouse = {0};
        virtualMouse.x =
                (mouse.x - (static_cast<float>(GetScreenWidth()) - (Game::ScreenWidth * scale)) * 0.5f) / scale;
        virtualMouse.y =
                (mouse.y - (static_cast<float>(GetScreenHeight()) - (Game::ScreenHeight * scale)) * 0.5f) / scale;
        virtualMouse = ClampValue(virtualMouse, {0, 0}, {static_cast<float>(Game::ScreenWidth),
                                                         static_cast<float>(Game::ScreenHeight)});


        BeginDrawing();
        ClearBackground(BLACK); // Letterbox color

        // Draw everything in the render texture, note this will not be rendered on screen, yet
        BeginTextureMode(target);

        EndTextureMode();

        // Draw RenderTexture2D to window, properly scaled
        DrawTexturePro(target.texture,
                       {0.0f, 0.0f, (float) target.texture.width, (float) -target.texture.height},
                       {(static_cast<float>(GetScreenWidth()) - ((float) Game::ScreenWidth * scale)) * 0.5f,
                        (static_cast<float>(GetScreenHeight()) - ((float) Game::ScreenHeight * scale)) * 0.5f,
                        (float) Game::ScreenWidth * scale, (float) Game::ScreenHeight * scale},
                       {0, 0}, 0.0f, WHITE);

        EndDrawing();
    } // Main game loop end

    // De-Initialization here...

    // Unload render texture
    UnloadRenderTexture(target);

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
