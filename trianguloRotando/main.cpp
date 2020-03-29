#include <iostream>

#  include <GL/glut.h>
using namespace std;
int Menu=0;
// Begin globals.
static float Xangle = 150.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate the tetrahedron.

// Vertex co-ordinate vectors for the tetrahedron.
static float vertices[] =
{
	 1.0,  1.0,  1.0, // V0
    -1.0,  1.0, -1.0, // V1
     1.0, -1.0, -1.0, // V2
	-1.0, -1.0,  1.0  // v3
};

// Vertex indices for the four trianglular faces.
static int triangleIndices[4][3] =
{
	{1, 2, 3}, // F0
	{0, 3, 2}, // F1
	{0, 1, 3}, // F2
	{0, 2, 1}  // F3
};
// End globals.
void rotateMenu (int option)
{
if(option==1)
Menu=1;
if(option==2)
Menu=2;
}
// Drawing routine.
void drawScene(void)
{
   int i;

   glClear(GL_COLOR_BUFFER_BIT);

   glLoadIdentity();
   gluLookAt(0.0, 3.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   glColor3f(0.0, 0.0, 0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
if(Menu==1) //Rotate Around origin
{
 Yangle += 0.05;
		 if (Yangle > 360.0) Yangle -= 360.0;
         glutPostRedisplay();
}
   // Rotate scene.
   glRotatef(Yangle, 0.0, 1.0, 0.0);

   // Draw tetrahedron.
   glBegin(GL_TRIANGLES);
      for(i = 0; i < 4; ++i)
	  {
	      glColor3f(0,1,1);
         glArrayElement(triangleIndices[i][0]);
         glColor3f(1,0.5,0);
         glArrayElement(triangleIndices[i][1]);
         glColor3f(0,0,1);
         glArrayElement(triangleIndices[i][2]);
	  }
   glEnd();

   glutSwapBuffers();
}

// Initialization routine.
void setup(void)
{
   glClearColor(0, 0, 0, 0.0);

   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0, vertices);
}

// OpenGL window reshape routine.
void resize (int w, int h)
{
   glViewport (0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, (float)w/(float)h, 1.0, 50.0);
   glMatrixMode(GL_MODELVIEW);
}

// Main routine.
int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("Tetraedro Giratorio");
   setup();
   glutDisplayFunc(drawScene);
   glutReshapeFunc(resize);
   glutCreateMenu(rotateMenu);
    glutAddMenuEntry("Girar",1);
    glutAddMenuEntry("Parar",2);
   glutAttachMenu(GLUT_RIGHT_BUTTON);
   glutMainLoop();
   return 0;
}
