#include "TXLib.h"
struct Ball
    {
    int x,  y,
        vx, vy;

    int r;

    COLORREF color, fillcolor;

    void Draw();

    void Physics (int ax, int ay, int dt);

//    void Change ();
    };

void MoveBall();
void DrawX (int x);
void DrawBall (int x, int y, int r, int vx, int vy, COLORREF color, COLORREF fillcolor);
void DrawPhysicsBall (int* x, int* y, int* vx, int* vy, int* ax, int* ay, int dt,  int r);
void DrawControlBall (int* vx, int* vy, int* vx3, int* vy3);
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
    HDC fon = txLoadImage ("Images\\fon.bmp");
    int x  =  110, y  = 100,
        vx =    7, vy =   5,
        ax =    0, ay =   0,

        r = 30;

    int x3  = 300, y3  = 200,
        vx3 =   5, vy3 =   3,
        ax3 =   0, ay3 =   0,

        r3 = 50;

    int dt = 1;

    int score = 0;

//    int nCollisions = 0;

    while (!txGetAsyncKeyState (VK_ESCAPE))
         {
         txSetFillColor (RGB (155, 140, 155));
         txClear ();

         txTransparentBlt (txDC(), 0, 0, 0, 0, fon, 0, 0);

         DrawX (x);

         DrawScot (score);

         DrawBall (x,  y,  vx,  vy,  r,  TX_LIGHTRED, TX_YELLOW);
         DrawBall (x3, y3, vx3, vy3, r3, TX_LIGHTGREEN, TX_GREEN);

         DrawPhysicsBall (&x,  &y,  &vx,   &vy,  &ax,  &ay, dt, r);
         DrawPhysicsBall (&x3, &y3, &vx3, &vy3, &ax3, &ay3, dt, r3);

         DrawControlBall (&vx, &vy, &x3, &y3);

         Collision   (x, y, x3, y3, &vx, &vy, &vx3, &vy3, r, r3, &score);

         txSleep (20);

         }
    txDeleteDC (fon);
    }
//--------------------------------------------------------------------------------
void DrawControlBall (int* vx, int* vy, int* vx3, int* vy3)
    {
     if (txGetAsyncKeyState (VK_RIGHT)) (*vx) ++;
     if (txGetAsyncKeyState (VK_LEFT))  (*vx) --;
     if (txGetAsyncKeyState (VK_UP))    (*vy) ++;
     if (txGetAsyncKeyState (VK_DOWN))  (*vy) --;

     if (txGetAsyncKeyState ('F')) *vx3 = *vx3 + 1;
     if (txGetAsyncKeyState ('A')) *vx3 = *vx3 - 1;
     if (txGetAsyncKeyState ('W')) *vy3 = *vy3 - 1;
     if (txGetAsyncKeyState ('S')) *vy3 = *vy3 + 1;

     if (txGetAsyncKeyState (VK_SPACE)) *vx = *vy = *vy3 = *vy3 = 0;
     }

//--------------------------------------------------------------------------------
void DrawPhysicsBall (int* x, int* y, int* vx, int* vy, int* ax, int* ay, int dt, int r)
    {
     *vx += (*ax) * dt;
     *vy += (*ay) * dt;

     *x  += (*vx) * dt;
     *y  += (*vy) * dt;

       if  (*x > 800 - r)
           {
            *vx = - (*vx);
            *x = 800 - r;

           }
       if  (*y > 600 - r)
           {
            *vy = - *vy;
            *y  = 600 - r;

           }
       if  (*x < 0 + r)
           {
            *vx = - *vx;
            *x  = 0 + r;

           }
       if  (*y < 0 + r)
           {
            *vy = - *vy;
            *y = 0 + r;

           }
    }
//--------------------------------------------------------------------------------
void DrawBall (int x, int y, int r, int vx, int vy, COLORREF color, COLORREF fillcolor)
    {

     txSetColor (color,2);
     txSetFillColor (fillcolor);

     txCircle (x, y, r);
//     txLine   (x, y, x + vx*2, y + vy*2);
//     txCircle (x + vx*2, y + vy*2, 20);
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
    char str[15] = "";
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
