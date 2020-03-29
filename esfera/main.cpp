#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

GLfloat v[4][3] = { {0.0, 0.0, 1.0},
	 {0.0, 0.942809, -0.333333},
	 {-0.816497, -0.471405, -0.333333},
	 {0.816497, -0.471405, -0.333333} };
int aprox=0;
GLfloat rotateY = 0.0;

void triangulo(GLfloat* a, GLfloat* b, GLfloat* c){

	glBegin(GL_LINE_LOOP);
	glBegin(GL_POLYGON);
    glColor3f(0,1,1);
	glVertex3fv(a);
	glColor3f(1,0.5,0);
	glVertex3fv(b);
	glColor3f(0,0,1);
	glVertex3fv(c);
	glEnd();
}

void normalizacion(GLfloat* vector) {
	float d = 0.0;
	int i;
	for (i = 0;i < 3;i++) {
		d += vector[i] * vector[i];
	}
	d = sqrt(d);
	if (d > 0.0) {
		for (i = 0;i < 3;i++) {
			vector[i] /= d;
		}
	}
}
///subdiviciones de los trinagulos
void dividir_triangulo(GLfloat* a, GLfloat* b, GLfloat* c, int i){
	GLfloat vertice1[3], vertice2[3], vertice3[3];
	int j;
	if (i > 0){
		for (j = 0; j < 3; j++) {
                vertice1[j] = (a[j] + b[j]) / 2;
                vertice2[j] = (a[j] + c[j]) / 2;
                vertice3[j] = (b[j] + c[j]) / 2;
		}
		normalizacion(vertice1);
		normalizacion(vertice2);
		normalizacion(vertice3);

		dividir_triangulo(a, vertice1, vertice2, i - 1);
		dividir_triangulo(c, vertice2, vertice3, i - 1);
		dividir_triangulo(b, vertice3, vertice1, i - 1);
		dividir_triangulo(vertice1, vertice3, vertice2, i - 1);
	}
	else{
        triangulo(a, b, c);
	}

}

void tetraedro(int i){

	dividir_triangulo(v[0], v[1], v[2], i);
	dividir_triangulo(v[3], v[2], v[1], i);
	dividir_triangulo(v[0], v[3], v[1], i);
	dividir_triangulo(v[0], v[2], v[3], i);
}

void rotar(){
    rotateY+=0.05;
	glRotatef(rotateY, 0.0, 1.0, 0.0);
	glutPostRedisplay();
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    rotar();
	tetraedro(aprox);
	glFlush();
	glutSwapBuffers();
}

void teclado(unsigned char key,int x,int y) {
	switch (key) {
	case '+':
		if (aprox < 10) {
			aprox++;
			cout << "\nAproximacion : " << aprox << " \n";
			glutPostRedisplay();
		}
		break;
	case '-':
		if (aprox != 0) {
			aprox--;
			cout << "\nAproximacion : " << aprox << " \n";
			glutPostRedisplay();
		}
		break;
	}
}

void inicio()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
}
int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(400,100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Aproximacion a una esfera");
	inicio();
	glutDisplayFunc(display);
	glutKeyboardFunc(teclado);
	glutMainLoop();
	return 0;
}
