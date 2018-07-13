#include <windows.h>
#include <stdio.h>

#include <stdarg.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

float ballX = 0;
float ballY = 0.8;
float ballZ = -1;
float _angle = 0.0;

static int flag=1;

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   // glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();

    GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    //Add positioned light
    GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos0[] = {ballX, ballY, ballZ, 1.0f}; //Positioned at (4, 0, 8)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    //Add directed light
    GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
    //Coming from the direction (-1, 0.5, 0.5)
    GLfloat lightPos1[] = {0, 8, -25, 0.0};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

    glPushMatrix();
        glColor3f(2,2,0); //set ball colour
        glTranslatef(ballX, ballY, ballZ); //moving it toward the screen a bit on creation
        glutSolidSphere (1.01, 30, 30); //create ball.
    glPopMatrix();


   glPushMatrix();//sky
        glTranslatef(0,0,-10);
        glBegin(GL_QUADS);
            glColor3f(0.0, 1.0, 1.0);  glVertex3f(-10,10,0);
            glColor3f(0.0, 1.0, 1.0);  glVertex3f(10,10,0);
            glColor3f(0.0, 1.0, 1.0);  glVertex3f(10,-10,0);
            glColor3f(0.0, 1.0, 1.0);  glVertex3f(-10,-10,0);
        glEnd();
    glPopMatrix();

    glPushMatrix();//grass
        glTranslatef(0,0,-6);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
            glColor3f(0.0, 0.5, 0.0);  glVertex3f(-25,-1.5,25);
            glColor3f(0.0, 0.5, 0.0);  glVertex3f(-25,-1.5,-50);
            glColor3f(0.0, 0.5, 0.0);  glVertex3f(25,-1.5,-25);
            glColor3f(0.0, 0.5, 0.0);  glVertex3f(25,-1.5,25);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,0,-6);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);  // Wall
            glColor3f(1.0, 0.5, 0.0);  glVertex3f(-2,0,1);
            glColor3f(1.0, 0.5, 0.0);  glVertex3f(2,0,1);
            glColor3f(1.0, 0.5, 0.0);  glVertex3f(2,-1.5,1);
            glColor3f(1.0, 0.5, 0.0);  glVertex3f(-2,-1.5,1);
        glEnd();
        glBegin(GL_QUADS);  // Roof
            glColor3f(0.309804, 0.184314, 0.184314); glVertex3f(-2.2,0.5,0);
            glColor3f(0.309804, 0.184314, 0.184314);    glVertex3f(2.2,0.5,0);
            glColor3f(0.309804, 0.184314, 0.184314); glVertex3f(2.2,-0.1,1.25);
            glColor3f(0.309804, 0.184314, 0.184314); glVertex3f(-2.2,-0.1,1.25);
        glEnd();
    glPopMatrix();

    glPushMatrix();//back
        glTranslatef(0,0,-6);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);//Wall
            glColor3f(1.0, 0.5, 0.0);  glVertex3f(-2,0,-1);
            glColor3f(1.0, 0.5, 0.0);  glVertex3f(2,0,-1);
            glColor3f(1.0, 0.5, 0.0);  glVertex3f(2,-1.5,-1);
            glColor3f(1.0, 0.5, 0.0);  glVertex3f(-2,-1.5,-1);
        glEnd();
        glBegin(GL_QUADS);  // Roof
            glColor3f(0.309804, 0.184314, 0.184314); glVertex3f(-2.2,0.5,0);
            glColor3f(0.309804, 0.184314, 0.184314);    glVertex3f(2.2,0.5,0);
            glColor3f(0.309804, 0.184314, 0.184314); glVertex3f(2.2,-0.1,-1.25);
            glColor3f(0.309804, 0.184314, 0.184314); glVertex3f(-2.2,-0.1,-1.25);
        glEnd();
    glPopMatrix();

    glPushMatrix();//right side
        glTranslatef(0,0,-6);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);//Wall
            glColor3f(1.0, 0.5, 0.0);  glVertex3f(2,0,1);
            glColor3f(1.0, 0.5, 0.0);  glVertex3f(2,0,-1);
            glColor3f(1.0, 0.5, 0.0);  glVertex3f(2,-1.5,-1);
            glColor3f(1.0, 0.5, 0.0);  glVertex3f(2,-1.5,1);
        glEnd();
        glBegin(GL_TRIANGLES);  // Wall fill
            glColor3f(1.0, 0.5, 0.0); glVertex3f(2,0.5,0);
            glColor3f(1.0, 0.5, 0.0); glVertex3f(2,0,1);
            glColor3f(1.0, 0.5, 0.0); glVertex3f(2,0,-1);
        glEnd();
    glPopMatrix();

     glPushMatrix();//left side
        glTranslatef(0,0,-6);
        glRotatef(_angle, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);//Wall
            glColor3f(1.0, 0.5, 0.0);  glVertex3f(-2,0,1);
            glColor3f(1.0, 0.5, 0.0);  glVertex3f(-2,0,-1);
            glColor3f(1.0, 0.5, 0.0);  glVertex3f(-2,-1.5,-1);
            glColor3f(1.0, 0.5, 0.0);  glVertex3f(-2,-1.5,1);
        glEnd();
        glBegin(GL_TRIANGLES);  // Wall fill
            glColor3f(1.0, 0.5, 0.0); glVertex3f(-2,0.5,0);
            glColor3f(1.0, 0.5, 0.0); glVertex3f(-2,0,1);
            glColor3f(1.0, 0.5, 0.0); glVertex3f(-2,0,-1);
        glEnd();
    glPopMatrix();

    glutSwapBuffers();
    glFlush();
}

void keyPress(int key, int x, int y)
{
      if(key==GLUT_KEY_PAGE_UP)
        ballX -= 0.05f;
    if(key==GLUT_KEY_PAGE_DOWN)
        ballX  += 0.05f;

    glutPostRedisplay();
}

void mySpecialFunc(int key, int x, int y){
	switch (key) {
    case GLUT_KEY_RIGHT:
        _angle += 1;
        if (_angle > 360) _angle = 0.0;
		break;
    case GLUT_KEY_LEFT:
        _angle -= 1;
        if (_angle > 360) _angle = 0.0;
	    break;
	}

	if(key==GLUT_KEY_PAGE_UP)
        ballX -= 0.05f;
    if(key==GLUT_KEY_PAGE_DOWN)
        ballX  += 0.05f;

	glutPostRedisplay();
}

void Initialize() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

void initRendering() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING); //Enable lighting
    glEnable(GL_LIGHT0); //Enable light #0
    glEnable(GL_LIGHT1); //Enable light #1
    glEnable(GL_NORMALIZE); //Automatically normalize normals
    //glShadeModel(GL_SMOOTH); //Enable smooth shading
}



int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	//glutInitWindowPosition(100,100);
	glutInitWindowSize(1366,768);
	glutCreateWindow("House");
	glEnable(GL_DEPTH_TEST);

	glutReshapeFunc(resize);
	glutSpecialFunc(mySpecialFunc);
	//glutSpecialFunc(keyPress);
	glutDisplayFunc(renderScene);
	Initialize();
	initRendering();
    //glutFullScreen();
	glutMainLoop();

	return 0;
}
