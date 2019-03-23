#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

float pad_left_y = 0.0f;
float pad_left_x=0.0f;
float pad_right_y = 0.0f;
float pad_right_x=0.0f;
float width=800;
float height=600;
float incX = -0.01f;
float incY = 0.01f;
//float ballX = 0.0f;
//float ballY = 0.0f;
float ball_pos_x = 0.0f;
float ball_pos_y = 0.0f;
float pad_width=0.81;
float pad_height=0.5;
int interval = 1000 / 60;
float ball_dir_x = -1.0f;
float ball_dir_y = 0.0f;


// score
int score_left = 0;
int score_right = 0;

float movementSpeed = 0.02;

using namespace std;
void initGL() {
   // Set background color
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void MoveComputerPad(){
    if(ball_pos_x > 0){
            if(ball_pos_y < pad_right_y){
                pad_right_y -= movementSpeed;
            }else if(ball_pos_y > pad_right_y){
                pad_right_y += movementSpeed;
            }
        }
}
void MoveBall(){
    ball_pos_x += ball_dir_x * movementSpeed;
    ball_pos_y += ball_dir_y * movementSpeed;
     // hit by left pad?
    if (ball_pos_y > -0.1f+pad_left_y  &&
        ball_pos_y < 0.2f+pad_left_y &&ball_pos_x< -0.9f ){
        // set fly direction depending on where it hit the pad
        // (t is 0.5 if hit at top, 0 at center, -0.5 at bottom)
        float t = ((ball_pos_y - pad_left_y) / pad_height) - 0.5f;
        ball_dir_x = fabs(ball_dir_x); // force it to be positive
        ball_dir_y = t;
    }

    // hit by right pad?
    if (ball_pos_y > -0.1f+pad_right_y  &&
        ball_pos_y < 0.2f+pad_right_y &&ball_pos_x> 1.1f) {
        // set fly direction depending on where it hit the pad
        // (t is 0.5 if hit at top, 0 at center, -0.5 at bottom)
        float t = ((ball_pos_y - pad_right_y) / pad_height) - 0.5f;
        ball_dir_x = -fabs(ball_dir_x); // force it to be negative
        ball_dir_y = t;
    }


    // hit left wall?
    if (ball_pos_x < -1.2f) {
        ++score_right;
        fprintf(stderr, "Computer scored! Score: %d : %d\n", score_left, score_right);
        ball_pos_x = 0.0f;
        ball_pos_y = 0.0f;
        ball_dir_x = fabs(ball_dir_x); // force it to be positive
        ball_dir_y = 0;
    }

    // hit right wall?
    if (ball_pos_x > 1.2f) {
        ++score_left;
        fprintf(stderr, "Player scored! Score: %d : %d \n", score_left, score_right);

        ball_pos_x = 0.0f;
        ball_pos_y = 0.0f;
        ball_dir_x = -fabs(ball_dir_x); // force it to be negative
        ball_dir_y = 0;
    }

    // hit top wall?
    if (ball_pos_y > 1.0f) {
        ball_dir_y = -fabs(ball_dir_y); // force it to be negative
    }
    // hit bottom wall?
    if (ball_pos_y < -1.0f) {
        ball_dir_y = fabs(ball_dir_y); // force it to be positive
    }
    MoveComputerPad();

    glutPostRedisplay();
}
void MoveUp(){
    if(pad_left_y<0.79){
        pad_left_y+=movementSpeed;
    }
}
void MoveDown(){
    if(pad_left_y>-0.89){
        pad_left_y-=movementSpeed;
    }
}
static void key(unsigned char key, int x, int y)
{

    switch (tolower(key))
    {

        case 'q':
            exit(0);
            break;

        case 'w':
            MoveUp();
            break;

        case 's':
            MoveDown();
            break;
    }

    glutPostRedisplay();
}
void display() {
   glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

   // Left pad
    glBegin( GL_POLYGON );
    glColor3f( 1.0f, 1.0f, 1.0f ); glVertex2f( -0.97f, -0.1f+pad_left_y );
    glColor3f( 1.0f, 1.0f, 1.0f ); glVertex2f( -0.97f,  0.2f+pad_left_y );
    glColor3f( 1.0f, 1.0f, 1.0f ); glVertex2f( -1.0f,   0.2f+pad_left_y );
    glColor3f( 1.0f, 1.0f, 1.0f ); glVertex2f( -1.0f,  -0.1f+pad_left_y );
    glEnd();

    //Ball
    glBegin( GL_POLYGON );
    glColor3f( 1.0f, 1.0f, 1.0f ); glVertex2f( -0.08f+ball_pos_x, -0.03f+ball_pos_y );
    glColor3f( 1.0f, 1.0f, 1.0f ); glVertex2f( -0.08f+ball_pos_x, 0.01f+ball_pos_y );
    glColor3f( 1.0f, 1.0f, 1.0f ); glVertex2f( -0.11f+ball_pos_x,  0.01f+ball_pos_y );
    glColor3f( 1.0f, 0.0f, 1.0f ); glVertex2f( -0.11f+ball_pos_x, -0.03f+ball_pos_y );
    glEnd();

    //Right pad
    glBegin( GL_POLYGON );
    glColor3f( 1.0f, 1.0f, 1.0f ); glVertex2f( 0.97f, -0.1f+pad_right_y );
    glColor3f( 1.0f, 1.0f, 1.0f ); glVertex2f( 0.97f,  0.2f+pad_right_y );
    glColor3f( 1.0f, 1.0f, 1.0f ); glVertex2f( 1.0f,   0.2f+pad_right_y );
    glColor3f( 1.0f, 1.0f, 1.0f ); glVertex2f( 1.0f,  -0.1f+pad_right_y );
    glEnd();
    MoveBall();
    Sleep(15);
    glFlush();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
	glutInitWindowPosition(300,70);
	glutInitWindowSize(800,600);
	glutCreateWindow("Pong Game");
	initGL();
    glutKeyboardFunc(key);

   glutDisplayFunc(display);

   glutMainLoop();
   return 0;
}
