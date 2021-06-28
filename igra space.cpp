#include "TXLib.h"
struct Ball
    {
    double x,  y,
        vx, vy;

    double r;

    COLORREF color, fillcolor;

    void Draw();

    void Physics (double ax, double ay, double dt);

//    void Change ();
    };

void MoveBall();
void DrawX (int x);
void DrawBall (double x, double y, double r, double vx, double vy, COLORREF color, COLORREF fillcolor);
void DrawPhysicsBall (double* x, double* y, double* vx, double* vy, double* ax, double* ay, double dt,  double r);
void DrawControlBall (double* vx, double* vy, double* vx3, double* vy3);
void DrawScot (int score);
void Collision (double x1, double y1, double x2, double y2, double* vx1, double* vy1, double* vx2, double* vy2, double r1, double r2, double* score);
//--------------------------------------------------------------------------------
int main()
    {
    txCreateWindow (800, 600);

//    txSetFillColor (RGB (155, 140, 155));

    txClear ();

    MoveBall();

    return 0;
    }
//--------------------------------------------------------------------------------
void MoveBall()
    {
    HDC fon = txLoadImage ("Images\\fon.bmp");
    double x  =  110, y  = 100,
        vx =    7, vy =   5,
        ax =    0, ay =   0,

        r = 15;

    double x3  = 300, y3  = 200,
        vx3 =   5, vy3 =   3,
        ax3 =   0, ay3 =   0,

        r3 = 13;

    double dt = 1;

    double score = 0;

//    int nCollisions = 0;

    while (!txGetAsyncKeyState (VK_ESCAPE))
         {
//         txSetFillColor (RGB (155, 140, 155));
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
void DrawControlBall (double* vx, double* vy, double* vx3, double* vy3)
    {
     if (txGetAsyncKeyState (VK_RIGHT)) (*vx) ++;
     if (txGetAsyncKeyState (VK_LEFT))  (*vx) --;
     if (txGetAsyncKeyState (VK_UP))    (*vy) ++;
     if (txGetAsyncKeyState (VK_DOWN))  (*vy) --;

     if (txGetAsyncKeyState ('F')) (*vx3) ++;
     if (txGetAsyncKeyState ('A')) (*vx3) --;
     if (txGetAsyncKeyState ('W')) (*vy3) --;
     if (txGetAsyncKeyState ('S')) (*vy3) ++;

     if (txGetAsyncKeyState (VK_SPACE)) *vx = *vy = *vy3 = *vy3 = 0;
     }

//--------------------------------------------------------------------------------
void DrawPhysicsBall (double* x, double* y, double* vx, double* vy, double* ax, double* ay, double dt, double r)
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
void DrawBall (double x, double y, double r, double vx, double vy, COLORREF color, COLORREF fillcolor)
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
double DistanceBalls (double xA, double yA, double xB, double yB)
    {
    double dist = sqrt ((xA - xB) * (xA - xB) + (yA - yB) * (yA - yB));
    return dist;
    }
//-------------------------------------------------------------
void Collision (double x1, double y1, double x2, double y2, double* vx1, double* vy1, double* vx2, double* vy2, double r1, double r2, double* score)
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
