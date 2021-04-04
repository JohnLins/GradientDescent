#include "raylib.h"
#include <math.h>

float fz(float x, float y){
    
    //return (x*x)+(y*y);
    return powf((x*x + y*y), 0.5);
}

int main(void)
{
    const int screenWidth = 1500;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "Gradient Decent");

    Camera camera = { 0 };
    camera.position = (Vector3){ 160.0f, 160.0f, 160.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 0.0f, 1.0f };
    camera.fovy = 45.0f;
   // camera.projection = CAMERA_PERSPECTIVE;

    

    SetCameraMode(camera, CAMERA_FREE); 

    SetTargetFPS(60);               
   

  
    while (!WindowShouldClose())       
    {
      
        UpdateCamera(&camera);         
     
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

    
                for(int x = -30; x < 30; x++){
                    for(int y = -30; y < 30; y++){
                    
                    DrawCube((Vector3){x, y, fz(x, y)}, 1, 1, 1, RED);
                    
                    }
                }
                
                DrawLine3D((Vector3){0, 0, 1000}, (Vector3){0, 0, -1000}, BLACK);
                DrawLine3D((Vector3){0, 1000, 0}, (Vector3){0, -1000, 0}, BLACK);
                DrawLine3D((Vector3){1000, 0, 0}, (Vector3){-1000, 0, 0}, BLACK);
                
                //DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
            
            EndMode3D();

          

        EndDrawing();
    }

    CloseWindow();       

    return 0;
}