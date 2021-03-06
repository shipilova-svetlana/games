#include "TXLib.h"

void MoveBall();
void DrawX (int x);
void DrawBall (int x, int y, int r, int vx, int vy, COLORREF color, COLORREF fillcolor);
void DrawPhysicsBall (int* x, int* y, int r, int* vx, int* vy, int* ax, int* ay, int dt, int* nCollisions);
void DrawControlBall (int* vx, int* vy);
void DrawScot (int score);
void Collision (int x1, int y1, int x2, int y2, int* vx1, int* vy1, int* vx2, int* vy2, int r1, int r2, int* score);
//--------------------------------------------------------------------------------
int main()
    {
    txCreateWindow (800, 600);

    txSetFillColor (RGB (155, 140, 155));

    txClear ();

    MoveBall();

    return 0;
    }
//--------------------------------------------------------------------------------
void MoveBall()
    {
    int x  =  110, y  = 100, r = 30,
        vx =   7, vy =   5,
        ax =   0, ay =   1;

    int x3  = 300, y3  = 200, r3 = 50,
        vx3 =   7, vy3 =   2,
        ax3 =   0, ay3 =   1;

    int dt = 1;

    int score = 0;

    int nCollisions = 0;

    while (!txGetAsyncKeyState (VK_ESCAPE))
         {
         txSetFillColor (RGB (155, 140, 155));
         txClear ();

         DrawX (x);

         DrawScot (score);

         DrawBall (x,  y,   r,  vx,  vy, TX_LIGHTRED, TX_YELLOW);
         DrawBall (x3, y3, r3, vx3, vy3, TX_LIGHTGREEN, TX_GREEN);

         DrawPhysicsBall (&x,  &y,  r,  &vx,   &vy,  &ax,  &ay, dt, &nCollisions);
         DrawPhysicsBall (&x3, &y3, r3, &vx3, &vy3, &ax3, &ay3, dt, &nCollisions);

         DrawControlBall (&vx, &vy);

         Collision   (x, y, x3, y3, &vx, &vy, &vx3, &vy3, r, r3, &score);

         txSleep (20);

         }
    }
//--------------------------------------------------------------------------------
void DrawControlBall (int* vx, int* vy)
    {
     if (txGetAsyncKeyState (VK_RIGHT)) (*vx) ++;
     if (txGetAsyncKeyState (VK_LEFT))  (*vx) --;
     if (txGetAsyncKeyState (VK_UP))    (*vy) ++;
     if (txGetAsyncKeyState (VK_DOWN))  (*vy) --;

     if (txGetAsyncKeyState (VK_SPACE)) *vx = *vy = 0;
     }
//--------------------------------------------------------------------------------
void DrawPhysicsBall (int* x, int* y, int r, int* vx, int* vy, int* ax, int* ay, int dt, int* nCollisions)
    {
     *vx = *vx + *ax * dt;
     *vy = *vy + *ay * dt;

     *x  = *x  + *vx * dt;
     *y  = *y  + *vy * dt;

       if  (*x > 800 - r)
           {
            *vx = - (*vx);
            *x = 800 - r;

           (*nCollisions) ++;
           }
       if  (*y > 600 - r)
           {
            *vy = - *vy;
            *y  = 600 - r;

           (*nCollisions) ++;
           }
       if  (*x < 0 + r)
           {
            *vx = - *vx;
            *x  = 0 + r;

           (*nCollisions) ++;
           }
       if  (*y < 0 + r)
           {
            *vy = - *vy;
            *y = 0 + r;

           (*nCollisions) ++;
           }
    }
//--------------------------------------------------------------------------------
void DrawBall (int x, int y, int r, int vx, int vy, COLORREF color, COLORREF fillcolor)
    {

     txSetColor (color,3);
     txSetFillColor (fillcolor);

     txCircle (x, y, r);
     txLine   (x, y, x + vx*5, y + vy*5);
     txCircle (x + vx*5, y + vy*5, 3);
    }
//--------------------------------------------------------------------------------
void DrawX (int x)
    {
     char strX[20] = "";
     sprintf (strX, "x = %d", x);

     int centerX = 750,
         centerY = 50;

     int textSizeX = txGetTextExtentX ("x = 0000"),
         textSizeY = txGetTextExtentY ("x = 0000");

     txSetColor (TX_WHITE,3);
     txSetFillColor (TX_BLACK);
     txRectangle (centerX - textSizeX/2 - 50, centerY - textSizeY/2 - 50,
                  centerX - textSizeX/2 + 50, centerY - textSizeY/2 + 50);

     txDrawText  (centerX - textSizeX/2 - 50, centerY - textSizeY/2 - 50,
                  centerX - textSizeX/2 + 50, centerY - textSizeY/2 + 50,
                  strX);
    }

//--------------------------------------------------------------------------------
void DrawScot (int score)
    {
    txSelectFont ("TimesNewRoman", 30);
    char str[10] = "";
    sprintf (str, "Score = %d", score);

    int centerX = txGetExtentX()/2;

    int textSizeX = txGetTextExtentX ("Score = ---"),
        textSizeY = txGetTextExtentY ("Score = ---");

    txSetFillColor (TX_BLACK);
    txRectangle (centerX - textSizeX, 0,
                 centerX + textSizeX, textSizeY);
    txTextOut   (centerX - textSizeX/2, 0, str);
    }
//-------------------------------------------------------------

void Collision (int x1, int y1, int x2, int y2, int* vx1, int* vy1, int* vx2, int* vy2, int r1, int r2, int* score)
    {
    if (pow(x1 - x2, 2) + pow(y1 - y2, 2) <= r1*r1 + 2*r1*r2 + r2*r2)
        {
        *vx2 = -(*vx2);
        *vy2 = -(*vy2);
        *vx1 = -(*vx1);
        *vy1 = -(*vy1);

 //       txPlaySound ("sounds/ball_sound.wav");

        *score = *score + 1;
        }
    }
