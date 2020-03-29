#include <GL/glut.h>
#include <stdio.h>

#define GAP 10

int main_w, w1, w2, w3, w4;

void
display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}

void
vis(int visState)
{
  printf("VIS: win=%d, v=%d\n", glutGetWindow(), visState);
}



int
main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowSize(500, 500);
  main_w = glutCreateWindow("n grid");
  glutDisplayFunc(display);
  glutVisibilityFunc(vis);
  int n=5;
  int w[n*n];
  int num=0;
  glClearColor(1.0, 1.0, 1.0, 1.0);
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
        num++;
        w[num] = glutCreateSubWindow(main_w, 10+(i*22), 10+(j*22), 20, 20);
        glutDisplayFunc(display);
        glutVisibilityFunc(vis);
        glClearColor(1.0, 0.0, 0.0, 1.0);
    }
  }
  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}
