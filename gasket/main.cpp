#include <GL/glut.h>
GLfloat v[3][2]= {{-1.0, -0.58},
    {1.0, -0.58}, {0.0, 1.15}
};
int n;
void dividirTriangulo(GLfloat *a, GLfloat *b, GLfloat *c, int m)
{
    GLfloat v0[2], v1[2], v2[2];
    int j;
    if(m>0)
    {
        for(j=0; j<2; j++)
            v0[j]=(a[j]+b[j])/2;
        for(j=0; j<2; j++)
            v1[j]=(a[j]+c[j])/2;
        for(j=0; j<2; j++)
            v2[j]=(b[j]+c[j])/2;
        dividirTriangulo(a, v0, v1, m-1);
        dividirTriangulo(c, v1, v2, m-1);
        dividirTriangulo(b, v2, v0, m-1);
    }
    else{
            glVertex2fv(a);
            glVertex2fv(b);
            glVertex2fv(c);
        }
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    dividirTriangulo(v[0], v[1], v[2], n);
    glEnd();
    glFlush();
}
void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
    glClearColor (0,0,0,0);
    glColor3f(0,204,204);
}
int main(int argc, char **argv)
{
    n=5;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Gasket");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
}
