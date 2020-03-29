#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>

using namespace std;

struct cube_rotate{
  GLfloat angle, x, y, z;
};
const int n_cubos=3;//numero de cuadros, por ejemplo un cubo 3x3 o 5x5
GLfloat angle, fAspect, cube_size;
GLint rot_x, rot_y, crement, x_0, x_k, y_0, y_k, z_0, z_k, gap, gap_crement;
//cube_rotate cube_rotations[n_cubos][n_cubos][n_cubos];
vector<cube_rotate> cube_rotations[n_cubos][n_cubos][n_cubos];
void load_visualization_parameters(void);
void apply_rotation(GLfloat angle){
  vector<cube_rotate> face[n_cubos][n_cubos];
  int index;
  cube_rotate rotation;
  // copia la cara que sera rotada
  // aplica rotación a la cara
  for(int i = 0; i < n_cubos; ++i)
    for(int j = 0; j < n_cubos; ++j) {
      index = 2 - j%n_cubos;
      if(x_0 == x_k){
	rotation = {angle, 1.0, 0.0, 0.0};
	face[index][i] = cube_rotations[x_k][i][j];
      }
      if(y_0 == y_k){
	rotation = {angle, 0.0, 1.0, 0.0};
	face[index][i] = cube_rotations[j][y_k][i];
      }
      if(z_0 == z_k){
	rotation = {-1 * angle, 0.0, 0.0, 1.0};
	face[index][i] = cube_rotations[j][i][z_k];
      }
      face[index][i].push_back(rotation);
    }
  // copia la cara trasera
  for(int i = 0; i < 3; ++i)
    for(int j = 0; j < 3; ++j) {
      if(x_0 == x_k)
	cube_rotations[x_k][i][j] = face[i][j];
      if(y_0 == y_k)
	cube_rotations[j][y_k][i] = face[i][j];
      if(z_0 == z_k)
	cube_rotations[j][i][z_k] = face[i][j];
    }
}

// restaura los parametros de la cara seleccionada
void reset_selected_face(){
  x_0 = 0;
  x_k = 2;
  y_0 = 0;
  y_k = 2;
  z_0 = 0;
  z_k = 2;
}
//configuta la camara
void set_camera()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluLookAt(0,80,200, 25,0,0, 0,1,0);
    glOrtho(-100.0f,100.0f,-100.0f,100.0f,5000.0f,-5000.0f);
    //glFrustum(-100.0f,100.0f,-100.0f,100.0f,20.0f,5000.0f);
    //gluPerspective(120.0f,1,20,-5000.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(-200,-200,1000,1000);
}
// dibuja el cubo
void draw_cube(int x, int y, int z)
{
  vector<cube_rotate> lrot = cube_rotations[x][y][z];
  glPushMatrix();
  // traduce la posición final
  glTranslatef((x - 1) * cube_size + x * gap, (y - 1) * cube_size + y * gap, (z - 1) * cube_size + z * gap);
  //coloca el cubo en la posición correcta
  for(int i = lrot.size() - 1; i >= 0; --i)
    glRotatef(lrot[i].angle, lrot[i].x, lrot[i].y, lrot[i].z);
  glColor3f(1.0f, 1.0f, 1.0f);//blanco
  glBegin(GL_QUADS);  // cara frontal
    glNormal3f(0.0, 0.0, 1.0);  // face normal
    glVertex3f(cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(-cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(-cube_size/2, -cube_size/2, cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, cube_size/2);
  glEnd();
  glColor3f(1.0f, 0.5f, 0.0f);
  glBegin(GL_QUADS);  //cara trasera
    glNormal3f(0.0, 0.0, -1.0);  // face normal
    glVertex3f(cube_size/2, cube_size/2, -cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(-cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(-cube_size/2, cube_size/2, -cube_size/2);
  glEnd();
  glColor3f(0.0f, 0.0f, 1.0f);//azul
  glBegin(GL_QUADS);  //  cara izquierda
    glNormal3f(-1.0, 0.0, 0.0);  // face normal
    glVertex3f(-cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(-cube_size/2, cube_size/2, -cube_size/2);
    glVertex3f(-cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(-cube_size/2, -cube_size/2, cube_size/2);
  glEnd();
  glColor3f(0.0f, 1.0f, 0.0f);
  glBegin(GL_QUADS);  // cara deracha
    glNormal3f(1.0, 0.0, 0.0);  // face normal
    glVertex3f(cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(cube_size/2, cube_size/2, -cube_size/2);
  glEnd();
  glColor3f(1.0f, 0.0f, 0.0f);//Rojo
  glBegin(GL_QUADS);  // cara superior
    glNormal3f(0.0, 1.0, 0.0);  // face normal
    glVertex3f(-cube_size/2, cube_size/2, -cube_size/2);
    glVertex3f(-cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(cube_size/2, cube_size/2, -cube_size/2);
  glEnd();
  glColor3f(1.0f, 1.0f, 0.0f);
  glBegin(GL_QUADS);  // cara inferior
    glNormal3f(0.0, -1.0, 0.0);  // face normal
    glVertex3f(-cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, cube_size/2);
    glVertex3f(-cube_size/2, -cube_size/2, cube_size/2);
  glEnd();
  glPopMatrix();
} // dibujo del cubo
// función de dibujo
void draw_func(void){
  int x = -cube_size, y = -cube_size, z = -cube_size;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// reinicia transformaciones
  glLoadIdentity();
  // inicializa la posición de la cara
  set_camera();
  // aplica las transformaciones de visualzación
  glRotatef(rot_x, 1.0, 0.0, 0.0); // rota n eje y
  glRotatef(rot_y, 0.0, 1.0, 0.0); // rota en eje x
  for(int i = 0; i < n_cubos; ++i) // paso atravez de eje x
    for(int j = 0; j < n_cubos; ++j) // paso atravez de eje y
      for(int k = 0; k < n_cubos; ++k) { // paso atravex de eje z
	// dibuja uno de los cubos
	draw_cube(i, j, k);
      }
  glutSwapBuffers();
}

// inicialización de parametros de visualización
void init_func (void){

  // inicialización de parametros
  cube_size = 15.0; // tamaño del cubo
  rot_x = 480.0; // rotación de x
  rot_y = 45; // rotación de y
  crement = 5;
  gap = 1;
  gap_crement = 3;
  // initialize cuboid rotations
  // init lighting
  GLfloat ambient_lighte[4]={0.2,0.2,0.2,1.0};
  GLfloat diffuse_light[4]={0.7,0.7,0.7,1.0};		// color
  GLfloat specular_light[4]={1.0, 1.0, 1.0, 1.0};	// brillo
  GLfloat light_position[4]={0.0, 50.0, 50.0, 1.0};
  // material brightness capacity
  GLfloat specularity[4]={1.0,1.0,1.0,1.0};
  GLint material_specularity = 60;
  // black background
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  // Gouraud colorization model
  glShadeModel(GL_SMOOTH);
  // material reflectability
  glMaterialfv(GL_FRONT,GL_SPECULAR, specularity);
  // brightness concentration
  glMateriali(GL_FRONT,GL_SHININESS,material_specularity);
  // activate ambient light
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_lighte);
  // define light parameters
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_lighte);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light );
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light );
  glLightfv(GL_LIGHT0, GL_POSITION, light_position );
  // enable changing material color
  glEnable(GL_COLOR_MATERIAL);
  // enable lighting
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  // enable depth buffering
  glEnable(GL_DEPTH_TEST);
  angle=45;
} // init
// specify what's shown in the window
void load_visualization_parameters(void)
{
  // specify projection coordinate system
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // specify projection perspective
  gluPerspective(angle,fAspect,0.4,500);
  // init model coordinate system
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  // specify observer and target positions
  set_camera();
} // load visualization parameters

// window reshape callback
void reshape_func(GLsizei w, GLsizei h){
  // prevents division by zero
  if ( h == 0 ) h = 1;
  // viewport size
  glViewport(0, 0, w, h);
  // aspect ratio
  fAspect = (GLfloat)w/(GLfloat)h;
  load_visualization_parameters();
} // reshape function
int main(int argc, char **argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500,500);
  glutCreateWindow("Cubo 3D");

  glutDisplayFunc(draw_func);
  glutReshapeFunc(reshape_func);
  init_func();
  glutMainLoop();
} // main
