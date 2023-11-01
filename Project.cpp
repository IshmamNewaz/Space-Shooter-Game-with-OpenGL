#include <iostream>
#include <fstream>
#include <stdlib.h>
#include<unistd.h>
#include<windows.h>
#include <mmsystem.h>
#include<stdlib.h>
#include <GL/glut.h>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#pragma comment(lib, "winmm.lib")

using namespace std;
GLfloat obj_x = 0.0f;
GLfloat obj_y = 0.0f;
bool is_visible = true;
int x=1;
GLfloat position = 0.0f;
GLfloat position2 = 0.0f;
GLfloat position3 = 0.0f;
GLfloat Position_Enemy=0.0f;
GLfloat Particle=0.0f;
GLfloat speed = 0.04f;
GLfloat speed_enemy = 0.01f;
GLfloat Particle_Speed = 0.2f;
GLfloat Enemy_Position = 0.0f;
GLfloat Enemy_Position_Speed = 0.0001f;

bool pause=false;
int hit=0;
bool enemyCol1=false;
bool enemyCol2=false;
bool enemyCol3=false;
bool enemyCol4=false;
bool enemyCol5=false;
bool col1=false;
bool col2=false;
bool col3=false;
bool col4=false;
bool col5=false;
bool presentOrNot = false;
bool FinishGame = false;
int EnemyDead = 0;
int PlayerDead = 0;
bool ChangeWindows=false;
void initGL()
{

	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
}
///Collision
void collision(){
    ///Player Shooting
    if((-0.01f+obj_x)>-0.9f && (0.01f+obj_x)<-0.70f && (-0.5f+position>0.8)){
        col1=true;
        //EnemyDead = EnemyDead+1;
    }
    if((-0.01f+obj_x)>-(0.9f+0.28f) && (0.01f+obj_x)<(-0.70f+0.28f) && (-0.5f+position>0.8)){
        col3=true;
        //EnemyDead = EnemyDead+1;
    }
    if((-0.01f+obj_x)>-(0.9f+0.28f+0.28f) && (0.01f+obj_x)<(-0.70f+0.28f+0.28f) && (-0.5f+position>0.8)){
        col4=true;
        //EnemyDead = EnemyDead+1;
    }
    if((-0.01f+obj_x)>0.68f && (0.01f+obj_x)<0.84f && (-0.5f+position>0.8)){
        col2=true;
    //EnemyDead = EnemyDead+1;

    }
    if((-0.01f+obj_x)>(0.6f-0.28f) && (0.01f+obj_x)<(0.8f-0.28f) && (-0.5f+position>0.8)){
        col5=true;
    //EnemyDead = EnemyDead+1;
    }


    ///Enemy Shooting
    if((-0.2f+obj_x)<-0.73f && (0.2f+obj_x)>-0.67f &&(-0.4f+obj_y)>(0.65f+Position_Enemy) && (0.65f+Position_Enemy)>-1.0f){

        enemyCol1= true;
    }
    if((-0.2f+obj_x)<(-0.73f+0.28f) && (0.2f+obj_x)>(-0.67f+0.28f) &&(-0.4f+obj_y)>(0.65f+Position_Enemy) && (0.65f+Position_Enemy)>-1.0f){

        enemyCol3= true;
    }
    if((-0.2f+obj_x)<(-0.73f+0.28f+0.28f) && (0.2f+obj_x)>(-0.67f+0.28f+0.28f) &&(-0.4f+obj_y)>(0.65f+Position_Enemy) && (0.65f+Position_Enemy)>-1.0f){

        enemyCol4= true;
    }

    if((-0.2f+obj_x)<0.67f && (0.2f+obj_x)>0.73f &&(-0.4f+obj_y)>(0.65f+Position_Enemy) && (0.65f+Position_Enemy)>-1.0f){

        enemyCol2= true;
    }
    if((-0.2f+obj_x)<(0.67f-0.28f) && (0.2f+obj_x)>(0.73f-0.28f) &&(-0.4f+obj_y)>(0.65f+Position_Enemy) && (0.65f+Position_Enemy)>-1.0f){

        enemyCol5= true;
    }


}
void update(int value)
{
    if(position >2.4 ){
        position = 0.1f;

    }
    position += speed;

    if(Enemy_Position <-2 ){
        Enemy_Position = 0.001f;

    }
    Enemy_Position -= Enemy_Position_Speed;


    if(Position_Enemy <-2){
        Position_Enemy =-0.01f;
    }
        Position_Enemy-=speed_enemy;


    if(Particle<-2){
        Particle=-0.1f;
    }
    Particle-=Particle_Speed;



	glutPostRedisplay(); //Notify GLUT that the display has changed
	glutTimerFunc(01, update, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a': // Move object left
            obj_x -= 0.1f;
            glutPostRedisplay();
            break;
        case 'd': // Move object right
            obj_x += 0.1f;
            glutPostRedisplay();

            break;
        case 'w': // Move object up
            obj_y += 0.1f;
            glutPostRedisplay();
            break;
        case 's': // Move object down
            obj_y -= 0.1f;
            glutPostRedisplay();
            break;
        case 't': // Move object down
            ChangeWindows=true;
            glutPostRedisplay();
            break;
    }
    //glutPostRedisplay(); // Notify GLUT that the display has changed
}

void renderText(string text, int x, int y)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1280, 0, 720, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x, y);

    for (const char& c : text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
void mouse(int button, int state, int x, int y) {


    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        is_visible = false; // Hide the initial object
        glutPostRedisplay(); // Notify GLUT that the display has changed
    }
}
///Player Spaceship
void SpaceShip(){

        glLoadIdentity();
        //glTranslatef(obj_x, obj_y, 0.0f);

        glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-0.05f+obj_x, -0.8f+obj_y);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.05f+obj_x, -0.9f+obj_y);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(0.05f+obj_x, -0.9+obj_y);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0.05f+obj_x, -0.8+obj_y);
        glEnd();


        glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(0.05f+obj_x, -0.8+obj_y);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(0.05f+obj_x, -0.9f+obj_y);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(0.08f+obj_x, -0.95+obj_y);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(0.14f+obj_x, -0.84f+obj_y);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(-0.14f+obj_x, -0.84f+obj_y);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.08f+obj_x, -0.95f+obj_y);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.05f+obj_x, -0.9+obj_y);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(-0.05f+obj_x, -0.8f+obj_y);
        glEnd();



        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_POLYGON);

        glVertex2f(0.0f+obj_x, -0.4f+obj_y);
        glVertex2f(-0.15f+obj_x, -0.6+obj_y);
        glVertex2f(-0.25f+obj_x, -1.0f+obj_y);

        glVertex2f(-0.16f+obj_x, -0.96f+obj_y);
        glVertex2f(-0.16f+obj_x, -0.86f+obj_y);
        glVertex2f(-0.12f+obj_x, -0.86f+obj_y);
        glVertex2f(-0.12f+obj_x, -0.84f+obj_y);

        glColor3f(1.0f, 1.0f, 0.0f);

        glVertex2f(-0.05f+obj_x, -0.8f+obj_y);
        glVertex2f(0.05f+obj_x, -0.8+obj_y);

        glVertex2f(0.12f+obj_x, -0.84f+obj_y);
        glVertex2f(0.12f+obj_x, -0.86f+obj_y);
        glVertex2f(0.16f+obj_x, -0.86f+obj_y);

        glColor3f(1.0f, 1.0f, 1.0f);

        glVertex2f(0.16f+obj_x, -0.96f+obj_y);

        glColor3f(1.0f, 1.0f, 1.0f);

        glVertex2f(0.25f+obj_x, -1.0f+obj_y);
        glVertex2f(0.15f+obj_x, -0.6+obj_y);
        glVertex2f(0.0f+obj_x, -0.4f+obj_y);
        glEnd();

        //glBegin(GL_POLYGON);
        //glColor3f(1.0f, 0.0f, 0.0f);
        //glVertex2f(0.0f+obj_x, -0.4f+obj_y);

        //glColor3f(1.0f, 1.0f, 0.0f);
        //glVertex2f(-0.15f+obj_x, -0.6+obj_y);

        //glVertex2f(0.0f+obj_x, -0.7+obj_y);
        //glVertex2f(0.15f+obj_x, -0.6+obj_y);
        //glEnd();
}
///Enemy SpaceShip
void EnemySpaceShip(){
        //glLoadIdentity();
        //glTranslatef(obj_x, obj_y, 0.0f);
        glTranslatef(0.0f, 0.0f, 0.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_POLYGON);
        glVertex2f(-0.8f, 0.7f+Enemy_Position);
        glVertex2f(-0.74f, 0.8f+Enemy_Position);
        glVertex2f(-0.78f, 0.85f+Enemy_Position);
        glVertex2f(-0.72f, 0.95f+Enemy_Position);
        glVertex2f(-0.66f, 1.0f+Enemy_Position);
        glVertex2f(-0.8f, 0.8f+Enemy_Position);
        glVertex2f(-0.94f, 1.0f+Enemy_Position);
        glVertex2f(-0.88f, 0.95f+Enemy_Position);
        glVertex2f(-0.82f, 0.85f+Enemy_Position);
        glVertex2f(-0.86f, 0.8f+Enemy_Position);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-0.8f, 0.7f+Enemy_Position);
        glEnd();

}
void EnemySpaceShip3(){
        //glLoadIdentity();
        //glTranslatef(obj_x, obj_y, 0.0f);
        glTranslatef(0.0f, 0.0f, 0.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_POLYGON);
        glVertex2f(-0.52f, 0.7f+Enemy_Position);
        glVertex2f(-0.46f, 0.8f+Enemy_Position);
        glVertex2f(-0.5f, 0.85f+Enemy_Position);
        glVertex2f(-0.44f, 0.95f+Enemy_Position);
        glVertex2f(-0.38f, 1.0f+Enemy_Position);
        glVertex2f(-0.52f, 0.9f+Enemy_Position);
        glVertex2f(-0.66f, 1.0f+Enemy_Position);
        glVertex2f(-0.6f, 0.95f+Enemy_Position);
        glVertex2f(-0.54f, 0.85f+Enemy_Position);
        glVertex2f(-0.58f, 0.8f+Enemy_Position);
        glVertex2f(-0.52f, 0.7f+Enemy_Position);
        glEnd();

}
void EnemySpaceShip4(){
        //glLoadIdentity();
        //glTranslatef(obj_x, obj_y, 0.0f);
        glTranslatef(0.0f, 0.0f, 0.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_POLYGON);
        glVertex2f(-0.24f, 0.7f+Enemy_Position);
        glVertex2f(-0.18f, 0.8f+Enemy_Position);
        glVertex2f(-0.22f, 0.85f+Enemy_Position);
        glVertex2f(-0.16f, 0.95f+Enemy_Position);
        glVertex2f(-0.10f, 1.0f+Enemy_Position);
        glVertex2f(-0.24f, 0.8f+Enemy_Position);
        glVertex2f(-0.38f, 1.0f+Enemy_Position);
        glVertex2f(-0.32f, 0.95f+Enemy_Position);
        glVertex2f(-0.26f, 0.85f+Enemy_Position);
        glVertex2f(-0.30f, 0.8f+Enemy_Position);
        glVertex2f(-0.24f, 0.7f+Enemy_Position);
        glEnd();

}
void EnemySpaceShip2(){
        //glLoadIdentity();
        //glTranslatef(obj_x, obj_y, 0.0f);
        glTranslatef(0.0f, 0.0f, 0.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_POLYGON);
        glVertex2f(0.7f, 0.7f+Enemy_Position);
        glVertex2f(0.76f, 0.8f+Enemy_Position);
        glVertex2f(0.72f, 0.85f+Enemy_Position);
        glVertex2f(0.78f, 0.95f+Enemy_Position);
        glVertex2f(0.84f, 1.0f+Enemy_Position);
        glVertex2f(0.7f, 0.8f+Enemy_Position);
        glVertex2f(0.56f, 1.0f+Enemy_Position);
        glVertex2f(0.62f, 0.95f+Enemy_Position);
        glVertex2f(0.68f, 0.85f+Enemy_Position);
        glVertex2f(0.64f, 0.8f+Enemy_Position);
        glVertex2f(0.7f, 0.7f+Enemy_Position);
        glEnd();

}
void EnemySpaceShip5(){
        //glLoadIdentity();
        //glTranslatef(obj_x, obj_y, 0.0f);
        glTranslatef(0.0f, 0.0f, 0.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_POLYGON);
        glVertex2f(0.42f, 0.7f+Enemy_Position);
        glVertex2f(0.48f, 0.8f+Enemy_Position);
        glVertex2f(0.44f, 0.85f+Enemy_Position);
        glVertex2f(0.50f, 0.95f+Enemy_Position);
        glVertex2f(0.56f, 1.0f+Enemy_Position);
        glVertex2f(0.42f, 0.9f+Enemy_Position);
        glVertex2f(0.28f, 1.0f+Enemy_Position);
        glVertex2f(0.34f, 0.95f+Enemy_Position);
        glVertex2f(0.40f, 0.85f+Enemy_Position);
        glVertex2f(0.36f, 0.8f+Enemy_Position);
        glVertex2f(0.42f, 0.7f+Enemy_Position);
        glEnd();

}
///Bullet
void Bullet(){

        //glTranslatef(0.0f,position, 0.0f);
        glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(-0.01f+obj_x, -0.8f+position+obj_y);
        glVertex2f(0.01f+obj_x, -0.8f+position+obj_y);
        glVertex2f(0.0f+obj_x, -0.6f+position+obj_y);
        glEnd();
}

void Enemy_Bullet1(){

        //glTranslatef(0.0f,position, 0.0f);
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-0.8f, 0.55f+Position_Enemy+Enemy_Position);
        glVertex2f(-0.79f, 0.65f+Position_Enemy+Enemy_Position);
        glVertex2f(-0.81f, 0.65f+Position_Enemy+Enemy_Position);
        glEnd();
}
void Enemy_Bullet3(){

        //glTranslatef(0.0f,position, 0.0f);
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-0.8f+0.28f, 0.55f+Position_Enemy+Enemy_Position);
        glVertex2f(-0.79f+0.28f, 0.65f+Position_Enemy+Enemy_Position);
        glVertex2f(-0.81f+0.28f, 0.65f+Position_Enemy+Enemy_Position);
        glEnd();
}
void Enemy_Bullet4(){

        //glTranslatef(0.0f,position, 0.0f);
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-0.8f+0.28f+0.28f, 0.55f+Position_Enemy+Enemy_Position);
        glVertex2f(-0.79f+0.28f+0.28f, 0.65f+Position_Enemy+Enemy_Position);
        glVertex2f(-0.81f+0.28f+0.28f, 0.65f+Position_Enemy+Enemy_Position);
        glEnd();
}
void Enemy_Bullet2(){

        //glTranslatef(0.0f,position, 0.0f);
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0.7f, 0.55f+Position_Enemy+Enemy_Position);
        glVertex2f(0.71f, 0.65f+Position_Enemy+Enemy_Position);
        glVertex2f(0.69f, 0.65f+Position_Enemy+Enemy_Position);
        glEnd();
}
void Enemy_Bullet5(){
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0.7f-0.28f, 0.55f+Position_Enemy+Enemy_Position);
        glVertex2f(0.71f-0.28f, 0.65f+Position_Enemy+Enemy_Position);
        glVertex2f(0.69f-0.28f, 0.65f+Position_Enemy+Enemy_Position);
        glEnd();
}

///Create New Window+winner
GLfloat UpwardsScrollVelocity = -10.0;
float view = 10.0;
char quote[6][80];
int numberOfQuotes = 0, i;
void timeTick(void)
{
	if (UpwardsScrollVelocity< -600)
		view -= 0.000011;
	if (view < 0) { view = 20; UpwardsScrollVelocity = -10.0; }
	//  exit(0);
	UpwardsScrollVelocity -= 0.1;
	glutPostRedisplay();

}
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 1.0, 3200);
	glMatrixMode(GL_MODELVIEW);
}

void RenderToDisplay()
{
	int l, lenghOfQuote, i;

	glTranslatef(0.0, -100, UpwardsScrollVelocity);
	glRotatef(-20, 1.0, 0.0, 0.0);
	glScalef(0.1, 0.1, 0.1);



	for (l = 0; l<numberOfQuotes; l++)
	{
		lenghOfQuote = (int)strlen(quote[l]);
		glPushMatrix();
		glTranslatef(-(lenghOfQuote * 37), -(l * 200), 0.0);
		for (i = 0; i < lenghOfQuote; i++)
		{
			glColor3f((UpwardsScrollVelocity / 10) + 300 + (l * 10), (UpwardsScrollVelocity / 10) + 300 + (l * 10), 0.0);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);

		}
		glPopMatrix();
	}

}
void myDisplayFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 30.0, 100.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	RenderToDisplay();
	glutSwapBuffers();
}

void winner(char a)
{
	strcpy(quote[0], "Game Over");

	strcpy(quote[1], "Winner Is ");
		//strcpy_s(quote[2], );
	strcpy(quote[2], "Player ");
	strcpy(quote[3], &a);
	numberOfQuotes = 5;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	//glutInitWindowSize(1360, 750);
	glutCreateWindow("Game Result");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glLineWidth(3);
    if(a=='1'){
        sndPlaySound("victory.wav",SND_ASYNC);
    }
    else{
        sndPlaySound("gameOver.wav",SND_ASYNC);
    }

	glutDisplayFunc(myDisplayFunction);
	glutReshapeFunc(reshape);
	glutIdleFunc(timeTick);
	glutMainLoop();

}
void Points(){


        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f+Particle, 1.0f+Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f, 1.0f+Particle, 0.0f);
        glEnd();
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f+Particle, 0.0f+Particle+Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f+Particle, 1.0f+Particle+Particle, 0.0f);
        glEnd();

        ///

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f, 1.0f+Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f+Particle, 1.0f+Particle, 0.0f);
        glEnd();
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f+Particle, 0.0f+Particle+Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f+Particle+Particle, 1.0f+Particle+Particle, 0.0f);
        glEnd();

        ///
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f, 1.0f+Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f+Particle, 1.0f+Particle, 0.0f);
        glEnd();
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f+Particle, 0.0f+Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f, 1.0f+Particle, 0.0f);
        glEnd();

        ///
        ///
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f+Particle+Particle+Particle, 1.0f+Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f+Particle+Particle, 1.0f+Particle, 0.0f);
        glEnd();
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f+Particle+Particle+Particle, 0.0f+Particle+Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f+Particle+Particle+Particle, 1.0f+Particle+Particle, 0.0f);
        glEnd();

        ///

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f+Particle, 1.0f+Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f+Particle+Particle, 1.0f+Particle, 0.0f);
        glEnd();
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f+Particle+Particle+Particle, 0.0f+Particle+Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f+Particle+Particle+Particle, 1.0f+Particle+Particle, 0.0f);
        glEnd();

        ///
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f+Particle, 1.0f+Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f+Particle+Particle, 1.0f+Particle, 0.0f);
        glEnd();
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f+Particle+Particle, 0.0f+Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f+Particle, 1.0f+Particle, 0.0f);
        glEnd();


        ///
        ///


        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f-Particle, 1.0f+Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f, 1.0f+Particle, 0.0f);
        glEnd();
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f-Particle, 0.0f+Particle+Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f-Particle, 1.0f+Particle+Particle, 0.0f);
        glEnd();

        ///

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f, 1.0f-Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f-Particle, 1.0f+Particle, 0.0f);
        glEnd();
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f-Particle, 0.0f+Particle+Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f-Particle-Particle, 1.0f+Particle+Particle, 0.0f);
        glEnd();

        ///
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f, 1.0f+Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f-Particle, 1.0f+Particle, 0.0f);
        glEnd();
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f-Particle, 0.0f+Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f, 1.0f+Particle, 0.0f);
        glEnd();

        ///
        ///

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f-Particle, 1.0f+Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f, 1.0f+Particle, 0.0f);
        glEnd();
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f-Particle-Particle, 0.0f+Particle+Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f-Particle-Particle, 1.0f+Particle+Particle, 0.0f);
        glEnd();

        ///

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f, 1.0f-Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f-Particle-Particle, 1.0f+Particle, 0.0f);
        glEnd();
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f-Particle-Particle, 0.0f+Particle+Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f-Particle-Particle, 1.0f+Particle+Particle, 0.0f);
        glEnd();

        ///
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f-Particle, 1.0f+Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f-Particle-Particle-Particle, 1.0f+Particle, 0.0f);
        glEnd();
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f-Particle-Particle, 0.0f+Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f-Particle-Particle, 1.0f+Particle, 0.0f);
        glEnd();

        ///

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f+Particle+Particle+Particle, 1.0f+Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f+Particle+Particle, 1.0f+Particle, 0.0f+Particle);
        glEnd();
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f+Particle+Particle+Particle, 0.0f+Particle+Particle, 0.0f+Particle);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f+Particle+Particle+Particle, 1.0f+Particle+Particle, 0.0f+Particle);
        glEnd();
        ///

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f+Particle+Particle, 1.0f+Particle, 0.0f);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f+Particle+Particle, 1.0f+Particle, 0.0f+Particle);
        glEnd();
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f+Particle+Particle+Particle, 0.0f+Particle+Particle, 0.0f+Particle);
        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.05f+Particle, 1.0f+Particle+Particle, 0.0f+Particle);
        glEnd();
        ///



}

void displayx() {

        //glPushMatrix();
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        collision();
        if(col1==false){
            EnemySpaceShip();
            Enemy_Bullet1();
            glBegin(GL_TRIANGLES);
            glVertex2f(1.0, 1.0);
            glVertex2f(0.9, 1.0);
            glVertex2f(0.95, 0.9);
            glEnd();

        }
        if(col2==false){
            EnemySpaceShip2();
            Enemy_Bullet2();
            glBegin(GL_TRIANGLES);
            glVertex2f(1.0, 0.9);
            glVertex2f(0.9, 0.9);
            glVertex2f(0.95, 0.8);
            glEnd();

        }
        if(col3==false){
            EnemySpaceShip3();
            Enemy_Bullet3();
            glBegin(GL_TRIANGLES);
            glVertex2f(1.0, 0.8);
            glVertex2f(0.9, 0.8);
            glVertex2f(0.95, 0.7);
            glEnd();
        }
        if(col4==false){
            EnemySpaceShip4();
            Enemy_Bullet4();
            glBegin(GL_TRIANGLES);
            glVertex2f(1.0, 0.7);
            glVertex2f(0.9, 0.7);
            glVertex2f(0.95, 0.6);
            glEnd();
        }
        if(col5==false){
            EnemySpaceShip5();
            Enemy_Bullet5();
            glBegin(GL_TRIANGLES);
            glVertex2f(1.0, 0.6);
            glVertex2f(0.9, 0.6);
            glVertex2f(0.95, 0.5);
            glEnd();
        }
        Bullet();
        Points();
        SpaceShip();



    if (col1==true && col2==true &&col5==true && col3==true && col4==true){
		winner('1');

	}

    else if ((enemyCol2==true && col2==false)
             ||(enemyCol5==true && col5==false)
             ||(enemyCol1==true && col1==false)
             ||(enemyCol3==true && col3==false)
             ||(enemyCol4==true && col4==false)
             ||(0.7f+Enemy_Position)<0.3f
             ){
        winner('2');
    }
    //glutDisplayFunc(display);
    glPopMatrix();
    glFlush();

}


void display(){
        if(ChangeWindows==false){
        glClear(GL_COLOR_BUFFER_BIT);
        renderText("In A Galaxy far far away people lived in harmony, but now The world is in chaos! Someone has to restore the order!", 10, 200);
        renderText("That someone is you! This task is very hard and you have to Accomplish it! I Expect good things from you", 10, 170);
        renderText("Now go and save that planet!", 10, 140);
        renderText("                                                                                     ######TUTORIAL######", 10, 110);
        renderText("                                                                                       WASD FOR MOVEMENT", 10, 80);
        renderText("                                                                                     PRESS T TO START GAME", 10, 50);
        renderText("                                                                            Destroy All ships before they reach you!", 10, 20);
        //glutSwapBuffers();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glColor3f(1.0f, 0.0f, 0.0f); // Set the color of the initial object to red
        glBegin(GL_QUADS); // Draw a square
        glVertex2f(-1.0f, -0.3f);
        glVertex2f(1.0f, -0.3f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(-1.0f,1.0f);
        glEnd();

        glFlush();
        }
        else if(ChangeWindows==true){
            displayx();
        }
}

void playSounds(){
         PlaySound(TEXT("Voice.wav"),NULL,SND_SYNC);

}
void playSounds2(){
         PlaySound(TEXT("background.wav"),NULL,SND_LOOP|SND_ASYNC);

}

void myInit (void){
    glClearColor(1.0, 1.0, 1.0, 0.0);

    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);

}

int main(int argc, char** argv) {
    thread soundThread(playSounds);
    thread soundThread2(playSounds2);
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set up the display mode
    glutInitWindowSize(1280, 720); // Set the window size
    glutCreateWindow("Space Shooter!"); // Create a window with the given title
    glutKeyboardFunc(keyboard); // Set the keyboard callback function
    glutMouseFunc(mouse);
    glutDisplayFunc(display);
    myInit ();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutTimerFunc(10, update, 0);

    glutMainLoop();

    soundThread.join();
    soundThread2.join();

    return 0;
}
