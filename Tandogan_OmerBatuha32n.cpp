//CTIS 164 HOMEWORK 1 
//Name : Omer Batuhan
//Surname:  Tandogan
//ID: 21803754
//Section: 3
//Name of the homework :Diamonds of King's Car

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#define MANUAL 0
#define AUTO 1
#define WINDOW_WIDTH  1400
#define WINDOW_HEIGHT 800

#define TIMER_PERIOD  30 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height

int hstart=0;// checking the whether car is shown or not
int mode=0; // to check mode
int direction = 0; // to check direction
int mx=0, my=0; //for variables of shapes

typedef struct {
    int x, y,direction;

}tri_t;

tri_t triarr[3];// bundle for diamonds
//
// to draw circle, center at (x,y)
// radius r
//
void circle(int x, int y, int r)
{
#define PI 3.1415
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
    float angle;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}




// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void* font, const char* string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}
void drawTriangle(int x,int y) {
  
    //diamond
    glBegin(GL_TRIANGLES);
    glVertex2f(-200 + x, -100 + y);
    glVertex2f(0 + x, 100 + y);
    glVertex2f(200 + x, -100 + y); 

    glVertex2f(200 + x, -100 + y);
    glVertex2f(-200 + x, -100 + y);
    glVertex2f(0 + x, -200 + y);
    
    glEnd();
}
void drawCar() {
    // spoiler of car
    glLineWidth(5);
    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(-250+ mx, 150 + my);
    glVertex2f(-200 + mx, 80 + my);
    glEnd();
    glLineWidth(1);

    // wheels of car
    glColor3ub(0, 0, 0);
    circle(150 + mx, 55 + my, 25);
    circle(50 + mx, 55 + my, 25);
   //body of car
    glColor3ub(236, 9, 9);
    glRectf(mx - 0 / 2, my + 160 / 2, mx + 685 / 2, my + 400 / 2);
    glColor3ub(255, 255, 255);
    //lamps of car  
    circle(280 + mx, 100 + my, 10);
    circle(320 + mx, 100 + my, 10);
    // rear bumber of car
    glBegin(GL_TRIANGLES);
    glColor3ub(236, 9, 9);
    glVertex2f(-200 + mx, 80 + my);
    glVertex2f(0 + mx, 200 + my);
    glVertex2f(0 + mx, 80 + my);
    glEnd();

   //crown of car
    glBegin(GL_QUADS);
    glColor3ub(228, 202, 37);
    glVertex2f(0+mx, 340+my);
    glVertex2f(0+mx, 200+my);
    glVertex2f(685/2+mx, 340+my);
    glVertex2f(685/2+mx, 200+my);
    glEnd();
    


    

   
}
void print(int x, int y, const char* string, void* font)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}
//
// To display onto window using OpenGL commands
//
void display() {
    //
    // clear window to white
    //
    glClearColor(255,255, 255, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    //to show diamonds
   
    glColor3f(0, 1, 1);
    for (int i = 1; i <= 3; i++) {
        drawTriangle(triarr[i - 1].x, triarr[i - 1].y);
    }

    //Necessary Informations
    glColor3f(0,0,1);
    vprint(450, 360, GLUT_BITMAP_HELVETICA_18, "Omer Batuhan TANDOGAN");
    glColor3f(0, 0, 1);
    vprint(500, 320, GLUT_BITMAP_HELVETICA_18, "21803754");
    glColor3f(1, 0,0);
    vprint(-300, -360, GLUT_BITMAP_HELVETICA_18, "Press <F1> to switch the mode and Arrow Keys to Control the car");
    glColor3f(1, 0, 0);
    vprint(-690, 360, GLUT_BITMAP_HELVETICA_18, "Mode :");
    glColor3f(1, 0, 0);
    vprint(-690, 320, GLUT_BITMAP_HELVETICA_18, "Direction:");
    glColor3f(1, 0, 0);
    
    if (mode == MANUAL) 
        vprint(-600, 360, GLUT_BITMAP_HELVETICA_18, "MANUAL");
    else        
        vprint(-600, 360, GLUT_BITMAP_HELVETICA_18, "AUTO");
    switch (direction) {
    case 1:
        vprint(-600, 320, GLUT_BITMAP_HELVETICA_18, "UP");
        break;
    case 2:
        vprint(-600, 320, GLUT_BITMAP_HELVETICA_18, "DOWN");
        break;
    case 3:
        vprint(-600, 320, GLUT_BITMAP_HELVETICA_18, "RIGHT");
        break;
    case 4:
        vprint(-600, 320, GLUT_BITMAP_HELVETICA_18, "LEFT");
        break;
    default:
        glColor3f(1, 0, 0);
        vprint(-600, 320, GLUT_BITMAP_HELVETICA_18, "NOT SET");
    }
   

  // to show car when clicked
    if (hstart == 1) {
        drawCar();
        
    }
    else {
        glColor3f(1, 0, 0);
        vprint(-100, 0, GLUT_BITMAP_HELVETICA_18, "Click to create/relocate the car");

    }
  


    glutSwapBuffers();
}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
    // to move the car
    switch (key) {
    case GLUT_KEY_UP: up = true;direction = 1;
        if (mode == MANUAL)
            
            my += 5;
            break; 
    case GLUT_KEY_DOWN: down = true;direction = 2;
        if (mode == MANUAL)
            my -= 5;
        break;
    case GLUT_KEY_LEFT: left = true;direction= 4;
        if (mode == MANUAL)
            mx -= 5;
        break;
    case GLUT_KEY_RIGHT: right = true;
        if (mode == MANUAL)
            mx += 5;
        direction = 3;break;

        //to change the mode
    case GLUT_KEY_F1: mode = (mode + 1) % 2; direction = 0; break;

      
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP: up = false; break;
    case GLUT_KEY_DOWN: down = false; break;
    case GLUT_KEY_LEFT: left = false; break;
    case GLUT_KEY_RIGHT: right = false; break;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick(int button, int stat, int x, int y)
{
    // to show the car when clicked
    if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN) {
        x = x - winWidth / 2-165;
        y = winHeight / 2 - y-405/2;
        if (hstart == 0) 
            hstart = 1;
        mx = x;
        my = y;

  }
    




    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // refresh window.
}

void onMoveDown(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function   
    glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function
    glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {

    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    // to animation of diamonds
    for (int i = 1; i <= 3; i++) {
        if (triarr[i - 1].direction == 1) {
            triarr[i - 1].x += 1;
            if (triarr[i - 1].x > 500)
                triarr[i - 1].direction = 0;
           

        }
        else {
            triarr[i - 1].x -= 1;
            if (triarr[i - 1].x <-500)
                triarr[i - 1].direction = 1;
        }

    }

    if (hstart == 1) {


        //move of car in auto mode
        if (mode == AUTO) {

            switch (direction) {
            case 1:
                my += 5;
                break;
            case 2:
                my -= 5;
                break;
            case 3:
                mx += 5;
                break;
            case 4:
                mx -= 5;
                break;
            }


            if (mx > 360) {
                direction = 4;

            }
            if (mx < -450) {
                direction = 3;

            }
            if (my > 60) {
                direction = 2;

            }
            if (my < -425) {
                direction = 1;

            }

        }



    }



    // to refresh the window it calls display() function
    glutPostRedisplay(); // display()

}
#endif

void Init() {

    // positions of diamonds
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (int i = 1; i <= 3; i++)
        triarr[i-1] = { -700 + i * 300,400 - i * 200,1 };

}

void main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("HW-1 diamonds of King's Car");

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);

    //
    // keyboard registration
    //
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);

    //
    // mouse registration
    //
    glutMouseFunc(onClick);
    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
    // timer event
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

    Init();

    glutMainLoop();
}