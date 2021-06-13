#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW 30
#define DENS_RATE 0.2
#define COLOR_RATE 255/40

typedef struct Node {
  float item;
  struct Node* next;
} Node;


void push(Node** ref, float data);


void display(Node* node) {
  for(float x = -WINDOW; x < WINDOW; x+=DENS_RATE){
      for(float y = -WINDOW; y < WINDOW; y+=DENS_RATE){
          DrawCube((Vector3){x, y, node->item}, 1, 1, 1, (Color){(int)node->item*COLOR_RATE, 5, 10, 100});
          node = node->next;                
      }
  }
}


float fz(float x, float y){
    //alternative
    //return cosf(-.2*x)+ 2*sinf(-.3*y);
    return powf((x*x + y*y), 0.5);
   
}

Vector2 gradient(float x, float y){
    float g_x = (x/powf((x*x+y*y), .5));
    float g_y = (y/powf((x*x+y*y), .5));
    /* alternative
    float g_x = -0.2*sinf(0.2*x);
    float g_y = -0.6*cosf(0.3*y);
    */
    
    float magnitude = sqrt(powf(g_x, 2) + powf(g_y, 2));
    return (Vector2){g_x/magnitude, g_y/magnitude};
    
}

int main(void)
{
    const int screenWidth = 1500;
    const int screenHeight = 1000;
    float learningRate = 0.1;
    
   
    Vector2 iW;
    printf("W_i_x: ");
    scanf("%f", &(iW.x));
   
    printf("W_i_y: ");
    scanf("%f", &(iW.y));
   
    float xBackup = iW.x;
    float yBackup = iW.y;


    Node* head = NULL;

    for(float x = -WINDOW; x < WINDOW; x+=DENS_RATE){
         for(float y = -WINDOW; y < WINDOW; y+=DENS_RATE){
              push(&head, fz(x, y));   
         }
    }

    

    InitWindow(screenWidth, screenHeight, "Gradient Decent");



    Camera camera = { 0 };
    camera.position = (Vector3){ -200, -250, 150};
    camera.target = (Vector3){  0, 0, 0 };
    camera.up = (Vector3){ 0.0f, 0.0f, 1.0f };
    camera.fovy = 45.0f;

    SetTargetFPS(60);               
   
    while (!WindowShouldClose())       
    {
        if (IsKeyDown(KEY_RIGHT)) camera.position.x += 3.0f;
        if (IsKeyDown(KEY_LEFT)) camera.position.x -= 3.0f;
        if (IsKeyDown(KEY_UP)) camera.position.y += 3.0f;
        if (IsKeyDown(KEY_DOWN)) camera.position.y -= 3.0f;
         if (IsKeyDown(KEY_W)) camera.position.z += 3.0f;
         if (IsKeyDown(KEY_S)) camera.position.z -= 3.0f;
         
         if(IsKeyPressed(KEY_R)) {
             iW.x = xBackup;
             iW.y = yBackup;
         }
      
        UpdateCamera(&camera);         
     
        BeginDrawing();

            ClearBackground(RAYWHITE);

                DrawText(FormatText("Learning Rate: %f", learningRate), 10, 10, 20, BLACK);
                DrawText(FormatText("Unit Gradient: (%f, %f)", gradient(iW.x, iW.y).x, gradient(iW.x, iW.y).y), 10, 60, 20, BLACK);
                DrawText(FormatText("Sphere x, y: (%f, %f)", iW.x, iW.y), 10, 100, 20, BLACK);
                

            BeginMode3D(camera);

    
                display(head);
               /* for(float x = -WINDOW; x < WINDOW; x+=RATE){
            for(float y = -WINDOW; y < WINDOW; y+=RATE){
                //push(&head, fz(x, y));   
               DrawCube((Vector3){x, y, fz(x, y)}, 1, 1, 1, (Color){(int)fz(x, y)*5, 5, 50, 100});
                    
              }
        }*/
                   
                   iW.x = iW.x - learningRate * gradient(iW.x, iW.y).x;
                   iW.y = iW.y - learningRate * gradient(iW.x, iW.y).y;
                   DrawSphere((Vector3){iW.x, iW.y, fz(iW.x, iW.y)+5.5}, 5, GREEN);
                   
                   learningRate = fabs(gradient(iW.x, iW.y).x * gradient(iW.x, iW.y).y);

                
                DrawLine3D((Vector3){0, 0, 1000}, (Vector3){0, 0, -1000}, BLACK);
                DrawLine3D((Vector3){0, 1000, 0}, (Vector3){0, -1000, 0}, BLACK);
                DrawLine3D((Vector3){1000, 0, 0}, (Vector3){-1000, 0, 0}, BLACK);
                
                
                
            
            EndMode3D();

        EndDrawing();
    }

    CloseWindow();       

    return 0;
}

void push(Node** ref, float data) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  Node* last = *ref;

  newNode->item = data;
  newNode->next = NULL;

  if (*ref == NULL) {
    *ref = newNode;
    return;
  }

  while (last->next != NULL)
    last = last->next;

  last->next = newNode;
  return;
}
