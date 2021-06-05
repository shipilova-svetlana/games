#include "TXLib.h"

void MoveBall();
void DrawX (int x);

//--------------------------------------------------------------------------
int main()
    {
    txCreateWindow (800, 600);

    MoveBall();

    return 0;
    }
//--------------------------------------------------------------------------
void MoveBall()
    {
    int x  = 100, y  = 100,
        vx = 7,   vy = 5;

    int dt = 1;

    txSetColor (RGB( 255, 77, 204), 2);

    txSetFillColor (RGB( 153, 0, 153));

    while (!txGetAsyncKeyState (VK_ESCAPE))
         {
         DrawX (x);

         txSetColor (RGB( 255, 77, 204), 2);

         txSetFillColor (RGB( 153, 0, 153));

         txCircle (x, y, 20);

         txLine (x, y, x + vx*5, y + vy*5);
         txCircle (x + vx*5, y + vy*5, 3);

         x += vx * dt;
         y += vy * dt;

         if (x > 800)
             {
             vx = -vx;
             x = 800;
             }
         if (y > 600)
             {
             vy = -vy;
             y = 600;
             }
         if (x < 0)
             {
             vx = -vx;
             x = 0;
             }
         if (y < 0)
             {
             vy = -vy;
             y = 0;
             }
         if (txGetAsyncKeyState (VK_RIGHT)) vx++;
         if (txGetAsyncKeyState (VK_LEFT))  vx--;
         if (txGetAsyncKeyState (VK_UP))    vy--;
         if (txGetAsyncKeyState (VK_DOWN))  vy++;

         if (txGetAsyncKeyState (VK_SPACE))  vx = vy = 0;

         txSleep (10);

         }
      }
//--------------------------------------------------------------------------------
void DrawX (int x)

         {
         char strX[20] = "";
         sprintf (strX, "x = %d", x);

         int centerX = txGetExtentX()/2,
             centerY = txGetExtentX()/2;

         int textSizeX = txGetTextExtentX ("x = 0000"),
             textSizeY = txGetTextExtentY ("x = 0000");

         txSetFillColor (TX_BLACK);
         txRectangle (centerX - textSizeX/2 - 50, centerY - textSizeY/2 - 50,
                      centerX - textSizeX/2 + 50, centerY - textSizeY/2 + 50);

         txDrawText  (centerX - textSizeX/2 - 50, centerY - textSizeY/2 - 50,
                      centerX - textSizeX/2 + 50, centerY - textSizeY/2 + 50,
                      strX);
         }

