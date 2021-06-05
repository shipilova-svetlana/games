#include "TXLib.h"

void MoveBall();
void DrawX (int x);
void DrawBall (int x, int y, int r, int vx, int vy, COLORREF color, COLORREF fillcolor);
void DrawPhysicsBall (int* x, int* y, int r, int* vx, int* vy, int* ax, int* ay, int dt, int* nCollisions);
void DrawControlBall (int* vx, int* vy);

//--------------------------------------------------------------------------
int main()
    {
    txCreateWindow (800, 600);

    txSetFillColor (RGB (155, 140, 155));

    txClear ();

    MoveBall();

    return 0;
    }
//--------------------------------------------------------------------------
void MoveBall()
    {
    int x  =  110, y  = 100, r = 30,
        vx =   7, vy =   5,
        ax =   0, ay =   1;

    int x1  = 100, y1  = 300, r1 = 20,
        vx1 =   5, vy1 =   2,
        ax1 =   0, ay1 =   1;

    int x2  = 200, y2  = 400, r2 = 10,
        vx2 =   9, vy2 =   5,
        ax2 =   0, ay2 =   1;

    int x3  = 300, y3  = 200, r3 = 50,
        vx3 =   7, vy3 =   2,
        ax3 =   0, ay3 =   1;

    int dt = 1;

    int nCollisions = 0;

    while (!txGetAsyncKeyState (VK_ESCAPE))
         {
         DrawX (x);

         DrawBall (x,  y,   r,  vx,  vy, TX_LIGHTRED, TX_YELLOW);
         DrawBall (x1, y1, r1, vx1, vy1, TX_LIGHTRED, TX_RED);
         DrawBall (x2, y2, r2, vx2, vy2, TX_LIGHTCYAN, TX_BLUE);
         DrawBall (x3, y3, r3, vx3, vy3, TX_LIGHTGREEN, TX_GREEN);

         DrawPhysicsBall (&x,  &y,  r,  &vx,   &vy,  &ax,  &ay, dt, &nCollisions);
         DrawPhysicsBall (&x1, &y1, r1, &vx1, &vy1, &ax1, &ay1, dt, &nCollisions);
         DrawPhysicsBall (&x2, &y2, r2, &vx2, &vy2, &ax2, &ay2, dt, &nCollisions);
         DrawPhysicsBall (&x3, &y3, r3, &vx3, &vy3, &ax3, &ay3, dt, &nCollisions);

         DrawControlBall (&vx, &vy);

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

         *x = *x + *vx * dt;
         *y = *y + *vy * dt;

         if (*x > 800 - r)
             {
             *vx = - (*vx);
             *x = 800 - r;

             (*nCollisions) ++;
             }
         if (*y > 600 - r)
             {
             *vy = - *vy;
             *y  = 600 - r;

             (*nCollisions) ++;
             }

         if (*x < 0 + r)
             {
             *vx = - *vx;
             *x  = 0 + r;

             (*nCollisions) ++;
             }

          if (*y < 0 + r)
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

