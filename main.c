#include "raylib.h"
#include <math.h>

  
#include <stdio.h>
#include <stdlib.h>

#define WINDOW 30
#define RATE 0.2


typedef struct Node {
  float item;
  struct Node* next;
} Node;




void push(Node** ref, float data) {
  Node* new_node = (Node*)malloc(sizeof(Node));
  Node* last = *ref;

  new_node->item = data;
  new_node->next = NULL;

  if (*ref == NULL) {
    *ref = new_node;
    return;
  }

  while (last->next != NULL)
    last = last->next;

  last->next = new_node;
  return;
}


void display(Node* node) {
    //float xy = -WINDOW;
    
  
    
    
    
   
  
  
  for(float x = -WINDOW; x < WINDOW; x+=RATE){
            for(float y = -WINDOW; y < WINDOW; y+=RATE){
                DrawCube((Vector3){x, y, node->item}, 1, 1, 1, (Color){(int)node->item*5, 5, 50, 100});
node = node->next;                
               //DrawCube((Vector3){x, y, fz(x, y)}, 1, 1, 1, (Color){(int)fz(x, y)*5, 5, 50, 100});
                    
              }
  }
  
     
  
}


 

float fz(float x, float y){
    
    //return powf(powf((x*x), 2)+5*(y*y), 3.5) + 2;
    //return pow((powf(0.4,2)-powf((0.6-powf((x*x+y*y),0.5)),2)),0.5);
    return powf((x*x + y*y), 0.5);
}

Vector2 gradient(float x, float y){
    float magnitude = sqrt(powf(x/powf((x*x+y*y), .5), 2) + powf(y/powf((x*x+y*y), .5), 2));
    return (Vector2){(x/powf((x*x+y*y), .5))/magnitude, (y/powf((x*x+y*y), .5))/magnitude};
}

int main(void)
{
    const int screenWidth = 1500;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "Gradient Decent");

    Camera camera = { 0 };
    camera.position = (Vector3){ 200, 200, 160};
    camera.target = (Vector3){  0, 0, 0 };
    camera.up = (Vector3){ 0.0f, 0.0f, 1.0f };
    camera.fovy = 45.0f;
   //camera.projection = CAMERA_PERSPECTIVE;
   SetCameraMoveControls(KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_LEFT, KEY_W, KEY_S);
  SetCameraMode(camera, CAMERA_THIRD_PERSON); 
   
  
   
  //SetCameraSmoothZoomControl(87);                    
    /*void SetCameraMoveControls(int frontKey, int backKey, 
                               int rightKey, int leftKey, 
                               int upKey, int downKey);        
    
   */
   
   
   
   /* Node* head = NULL;

    
    
   
  for(float x = -WINDOW; x < WINDOW; x+=RATE){
            for(float y = -WINDOW; y < WINDOW; y+=RATE){
                push(&head, fz(x, y));   
               //DrawCube((Vector3){x, y, fz(x, y)}, 1, 1, 1, (Color){(int)fz(x, y)*5, 5, 50, 100});
                    
              }
  }*/
              
    


    SetTargetFPS(60);               
   

float xx = 20;
float yy = 10;
  
    while (!WindowShouldClose())       
    {
        /*if (IsKeyDown(KEY_RIGHT)) camera.position.x += 3.0f;
        if (IsKeyDown(KEY_LEFT)) camera.position.y -= 3.0f;
        if (IsKeyDown(KEY_UP)) camera.position.z += 3.0f;
         if (IsKeyDown(KEY_DOWN)) camera.position.z -= 3.0f;*/
      
        UpdateCamera(&camera);         
     
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

    
                for(float x = -WINDOW; x < WINDOW; x+=RATE){
            for(float y = -WINDOW; y < WINDOW; y+=RATE){
                //push(&head, fz(x, y));   
               DrawCube((Vector3){x, y, fz(x, y)}, 1, 1, 1, (Color){(int)fz(x, y)*5, 5, 50, 100});
                    
              }
  }
                   
                   xx = xx - 0.4*gradient(xx, yy).x;
                   yy = yy - 0.4*gradient(xx, yy).y;
                   DrawSphere((Vector3){xx, yy, fz(xx, yy)+5.5}, 5, GREEN);

                
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