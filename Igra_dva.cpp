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

    int x1  = 300, y1  = 200,
        vx1 = 5,   vy1 = 2;


    int dt = 1;


    while (!txGetAsyncKeyState (VK_ESCAPE))
         {
         DrawX (x);

         txSetColor (TX_BLACK);
         txSetFillColor (TX_BLACK);
         txRectangle (x - vx*10, y - vy*10, x + vx*10, y + vy*10);

         txSetColor (RGB(x, y, 128), 2);
         txSetFillColor (RGB(x/2, y/2, 128));
         txCircle (x, y, 20);

         txLine (x, y, x + vx*5, y + vy*5);
         txCircle (x + vx*5, y + vy*5, 3);

         x += vx * dt;
         y += vy * dt;

         txSetColor (TX_BLACK);
         txSetFillColor (TX_BLACK);
         txRectangle (x1 - vx1*25, y1 - vy1*25, x1 + vx1*25, y1 + vy1*25);

         txSetColor (RGB( 55, 0, 204), 2);
         txSetFillColor (RGB( 3, 0, 25));
         txCircle (x1, y1, 40);

         txLine (x1, y1, x1 + vx1*5, y1 + vy1*5);
         txCircle (x1 + vx1*5, y1 + vy1*5, 3);

         x1 += vx1 * dt;
         y1 += vy1 * dt;

         if (x > 780)
             {
             vx = -vx;
             x = 780;
             }
         if (y > 580)
             {
             vy = -vy;
             y = 580;
             }
         if (x < 20)
             {
             vx = -vx;
             x = 20;
             }
         if (y < 20)
             {
             vy = -vy;
             y = 20;
             }
         if (x1 > 760)
             {
             vx1 = -vx1;
             x1 = 760;
             }
         if (y1 > 560)
             {
             vy1 = -vy1;
             y1 = 560;
             }
         if (x1 < 40)
             {
             vx1 = -vx1;
             x1 = 40;
             }
         if (y1 < 40)
             {
             vy1 = -vy1;
             y1 = 40;
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

