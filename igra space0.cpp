#include "TXLib.h"
struct Ball
    {
    double x,  y,
        vx, vy;

    double r;

    COLORREF color, fillcolor;

    void Draw();
    void Physics (double ax, double ay, double dt);

    };

void MoveBall();
void DrawX (int x);
void ControlBall (struct Ball* ball);
void DrawScot (int score);
double Distance  (struct Ball ball1, struct Ball ball2);
void Collision (struct Ball* ball1, struct Ball* ball2);//, int* score);
//--------------------------------------------------------------------------------

int main()
    {
    txCreateWindow (800, 600);

    txClear ();

    MoveBall();

    return 0;
    }
//--------------------------------------------------------------------------------
void MoveBall()
    {
    HDC fon = txLoadImage ("Images\\fon.bmp");

    Ball ball1 = {110, 100, 7, 5, 15,
                 TX_LIGHTRED, TX_YELLOW};

    Ball ball2 = {300, 200, 5, 3, 13,
                 TX_LIGHTGREEN, TX_BLUE};

    double ax = 0, ay = 0;

    double dt = 1;

    double score = 0;

    while (!txGetAsyncKeyState (VK_ESCAPE))
         {
         txClear ();

         txTransparentBlt (txDC(), 0, 0, 0, 0, fon, 0, 0);

         DrawScot (score);

         ball1.Draw ();
         ball2.Draw ();

         ball1.Physics (ax, ay, ROUND(dt));
         ball2.Physics (ax, ay, ROUND(dt));

         ControlBall (&ball1);

         if (Distance (ball1, ball2) <= ball1.r + ball2.r) Collision (&ball1, &ball2);

         txSleep (20);

         }
    txDeleteDC (fon);
    }
//--------------------------------------------------------------------------------
void ControlBall (struct Ball* ball)
    {
     if (txGetAsyncKeyState (VK_RIGHT)) ((*ball).vx) ++;
     if (txGetAsyncKeyState (VK_LEFT))  ((*ball).vx) --;
     if (txGetAsyncKeyState (VK_UP))    ((*ball).vy) --;
     if (txGetAsyncKeyState (VK_DOWN))  ((*ball).vy) ++;

     if (txGetAsyncKeyState (VK_SPACE)) (*ball).vx = (*ball).vy = 0;
     }

//--------------------------------------------------------------------------------
void Ball::Physics (double ax, double ay, double dt)
    {
     (*this).vx = (*this).vx + ROUND(ax * dt);
     (*this).vy = (*this).vy + ROUND(ay * dt);

     (*this).x  += ((*this).vx) * dt;
     (*this).y  += ((*this).vy) * dt;

       if  ((*this).x > 800 - r)
           {
            (*this).vx = - ((*this).vx);
            (*this).x = 800 - r;

           }
       if  ((*this).y > 600 - r)
           {
            (*this).vy = - (*this).vy;
            (*this).y  = 600 - r;

           }
       if  ((*this).x < 0 + r)
           {
            (*this).vx = - (*this).vx;
            (*this).x  = 0 + r;

           }
       if  ((*this).y < 0 + r)
           {
            (*this).vy = - (*this).vy;
            (*this).y = 0 + r;

           }
    }
//-------------------------------------------------------------
void Ball::Draw ()
    {
//    txBegin ();
    txSetColor (color, 2);
    txSetFillColor (fillcolor);

    txCircle (x, y, r);
//    txLine   (x, y, x + vx*2, y + vy*2);
//    txCircle (x + vx*2, y + vy*2, 20);
//    txEnd ();
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
void Collision (struct Ball* ball1, struct Ball* ball2)//, int* score)
    {
//    if (pow((*ball1).x1 - (*ball2).x2, 2) + pow((*ball1).y1 - (*ball2).y2, 2) <= ((*ball1).r1)*((*ball1).r1) + 2*((*ball1).r1)*((*ball2).r2) + ((*ball2).r2)*((*ball2).r2))
        {
        (*ball1).vx = -(*ball1).vx;
        (*ball1).vy = -(*ball1).vy;
        (*ball2).vx = -(*ball2).vx;
        (*ball2).vy = -(*ball2).vy;

 //       txPlaySound ("sounds/ball_sound.wav");

//        *score = *score + 1;
        }
    }
//-------------------------------------------------------------

double Distance (struct Ball ball1, struct Ball ball2)
    {
    return sqrt ((ball1.x - ball2.x)*(ball1.x - ball2.x) + (ball1.y - ball2.y)*(ball1.y - ball2.y));
    }

//-------------------------------------------------------------
