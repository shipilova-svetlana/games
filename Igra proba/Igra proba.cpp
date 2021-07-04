#include "TXLib.h"

void MoveBall  (HDC fon);

struct Ball
    {
    int x,  y,
        vx, vy;
    int r;

    COLORREF color;
    COLORREF fillcolor;

    void Draw    ();
    void Physics (double ax, double ay, int dt);

    };

struct ControlType
    {
    int key_left, key_right, key_up, key_down;
    };

void Collision   (struct Ball* ball);
void ControlBall (struct Ball* ball,  struct ControlType);

int main()
    {
    txCreateWindow (800, 600);

    HDC fon  = txLoadImage ("images\\fon10.bmp");

    MoveBall (fon);

    return 0;
    }

//-------------------------------------------------------------

void MoveBall (HDC fon)
    {
    HDC map = txLoadImage ("Images\\map2.bmp");
    HDC Buket = txLoadImage ("Images\\Buket.bmp");
    Ball ball = { 100, 100,  5, 3, 13, TX_LIGHTBLUE, TX_BLUE };

    ControlType player = {VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN};

    int dt = 1;
    double ax = 0.0, ay = 0.0;

    while (!txGetAsyncKeyState (VK_ESCAPE))
        {
        txBegin ();
        txBitBlt  (txDC(), 0, 0, 800, 600, fon, 0, 0);

        COLORREF color = txGetPixel (ball.x, ball.y, map);

        if  (color == RGB (255, 255, 0))
            {
            ball.x = 100;
            ball.y = 100;
            };

        ball.Draw ();

        Ball oldpos = ball;

        ball.Physics (ax, ay, ROUND(dt));

        COLORREF color2 = txGetPixel (ball.x, ball.y, map);

        if  (color2 == RGB (255, 0, 0))
            {
            ball = oldpos;
            };
        if  (color2 == RGB (0, 255, 255))
            {
//            txMessageBox ("Молодец!!!!!");
            txSelectFont   ("Times", 50);
            txSetColor     (TX_WHITE);
            txSetFillColor (TX_WHITE);
            txTextOut      (300, 200, "Молодец!!!!!");
            txBitBlt  (txDC(), 300, 300, 300, 300, Buket, 0, 0);
            txPlaySound ("zvuk-pobedyi-vyiigryisha.wav");
            txSleep (50);

            txDeleteDC (fon);
            txDeleteDC (map);
            txDeleteDC (Buket);
            return;
            };
//        printf ("%06X - color2 \n", color2);

        ControlBall (&ball, player);

        txEnd ();
        txSleep (10);
        }

    txDeleteDC (fon);
    txDeleteDC (map);
    txDeleteDC (Buket);
    }

//-------------------------------------------------------------

void Ball::Physics (double ax, double ay, int dt)
    {
    (*this).vx = (*this).vx + ROUND(ax * dt);
    (*this).vy = (*this).vy + ROUND(ay * dt);

    x = x + ROUND(vx * dt);
    y = y + ROUND(vy * dt);

    if (x > 800 - r)
        {
        vx = -vx;
        x  = 800 - r;
        }

    if ((*this).y > 600 - (*this).r)
        {
        (*this).vy = -(*this).vy;
        (*this).y  = 600 - (*this).r;
        }

    if ((*this).x < 0 + (*this).r)
        {
        (*this).vx = -(*this).vx;
        (*this).x  = 0 + (*this).r;
        }

    if ((*this).y < 0 + (*this).r)
        {
        (*this).vy = -(*this).vy;
        (*this).y  = 0 + (*this).r;
        }
    }

//-------------------------------------------------------------

void ControlBall (struct Ball* ball, struct ControlType player)
    {
    if (txGetAsyncKeyState (player.key_right)) (*ball).vx = (*ball).vx - 1;
    if (txGetAsyncKeyState (player.key_left))  (*ball).vx = (*ball).vx + 1;
    if (txGetAsyncKeyState (player.key_up))    (*ball).vy = (*ball).vy - 1;
    if (txGetAsyncKeyState (player.key_down))  (*ball).vy = (*ball).vy + 1;

    if (txGetAsyncKeyState (VK_SPACE))  (*ball).vx = (*ball).vy =  0;
    }

//-------------------------------------------------------------

void Ball::Draw ()
    {
    txBegin ();
    txSetColor (color, 2);
    txSetFillColor (fillcolor);

    txCircle (x, y, r);

//    if (!txGetAsyncKeyState (VK_F11));

    txLine   (x, y, x + vx*5, y + vy*5);
    txCircle (x + vx*5, y + vy*5, 3);
//    return;

    txEnd ();
    }

//-------------------------------------------------------------

void Collision   (struct Ball* ball)
    {

    (*ball).vx = -(*ball).vx;
    (*ball).vy = -(*ball).vy;

    }
