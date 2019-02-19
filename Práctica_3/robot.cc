
#include <ctype.h>
#include <math.h>
#include <vector>
#include <GL/glut.h>
#include "objetos.h"

using namespace std;

typedef enum {ROBOT,ACT_LUZ, DES_LUZ} _object_type;

_object_type Object_type;

robot Robot;
_iluminacion iluminacion;



/** variables que determninan la posicion y tamaño de la ventana X */
int Window_x=50,Window_y=50,Window_width=500,Window_high=500;

const float AXIS_SIZE=500; // Longitud de los ejes

/** variables que definen la posicion de la camara en coordenadas polares */
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

/** variables que controlan la ventana y la transformacion de perspectiva */
GLfloat Size_x,Size_y,Front_plane,Back_plane;

/** @brief Dibujo de ejes
  *
  * Dibuja los semiejes positivos del sistema de coordenadas.
  * X de color rojo
  * y de color verde
  * z de color azul
  *
  * Deja la iluminación desactivada
  */
void draw_axis()
{

glDisable(GL_LIGHTING);

glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(0,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,0,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,0);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}




/** @brief Funcion para definir la transformación de proyeccion
 *
 * Fija la transformación de proyección.
 * La versión inicial usa proyección paralela con glOrtho
 *
 * Deja el contexto de OpenGL aceptando atrices de proyección
 *
 * En la primera práctica se debe añadir además proyección perspectiva
*/

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_trasero)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}


/** @brief Funcion para definir la transformación de vista (posicionar la camara)
 *
 * Fija la transformación de vista.
 * La versión inicial la especifica como dos rotaciones y una traslación.
 *
 * Deja el contexto de OpenGL aceptando atrices de modelado
 *
 * Se podría dar igualmente con gluLookAt
*/
void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

/** @brief Funcion para modificar el tamaño del viewport
 *
 * Fija el tamaño del viewport de dibujo
 *
 * Esta función es llamada por glut cuando el usuario modifica el tamaño de la ventana X.
 *
 * Los parámetros son el nuevo tamaño del viewport.
*/
void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


/** @brief Funcion para dibujar los objetos
 *
 * En esta función incluiremos el código para dibujar nuestros objetos
 *
*/
void draw_objects()
{
glColor3f(0,1,0);
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

// Codigo para dibujar objetos
switch (Object_type){
	case ROBOT:Robot.draw();break;
  }
}

/** @brief Funcion para borrar el frame buffer
 *
*/
void clean_window()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


/** @brief Funcion para dibujar la escena
 *
 * Borra el frame buffer, fija la transformación de vista, dibuja los ejes y los objetos.
 *
*/
void draw(void)
{
clean_window();
change_observer();
//draw_axis();
draw_objects();
glutSwapBuffers();
}


/** @brief Funcion llamada cuando se aprieta una tecla normal
 *
 * el evento manda a la funcion:
 * 	codigo de la tecla
 * 	posicion x del raton
 *	posicion y del raton
 *
 * 	Inicialmente solo interpreta Q y escape, ambos termina el programa.
*/
void normal_key(unsigned char Tecla1,int x,int y)
{

switch (toupper(Tecla1)){
	case 'Q':exit(0); break;

	case 'A': Robot.antenas_atras(); break;
	case 'S': Robot.antenas_delante(); break;
	case 'D': Robot.cabeza_izq(); break;
	case 'F': Robot.cabeza_dcha(); break;
	case 'G': Robot.giroi_cintura(); break;
	case 'H': Robot.girod_cintura(); break;
	case 'J': Robot.brazos_arriba(); break;
	case 'K': Robot.brazos_abajo(); break;
	case 'Z': Robot.brazod_arriba(); break;
	case 'X': Robot.brazod_abajo(); break;
	case 'C': Robot.brazoi_arriba(); break;
	case 'V': Robot.brazoi_abajo(); break;
	case 'W': Robot.giro_piernad_d(); break;
	case 'E': Robot.giro_piernad_a(); break;
	case 'R': Robot.giro_piernai_d(); break;
	case 'T': Robot.giro_piernai_a(); break;

	case 'P':iluminacion.activar();break;
	case 'O':iluminacion.desactivar();break;

	default: glutPostRedisplay();
	}
glutPostRedisplay();
}

/** @brief Funcion llamada cuando se aprieta una tecla especial
 *
 * el evento manda a la funcion:
 * 	codigo de la tecla
 * 	posicion x del raton
 *	posicion y del raton
 *
 * 	Inicialmente solo interpreta las teclas de movimiento del cursor y avance y retroceso de página.
 * 	Con ellas se controla la cámara
 *
 * 	Las teclas de funciones están definidas sin asignar funcionalidad. Se pueden usar para cargar los objetos.
*/
void special_key(int Tecla1,int x,int y)
{
switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	// primitivas graficas
	case GLUT_KEY_F1:Object_type=ROBOT; Robot.rdefault(); break;
	case GLUT_KEY_F2:Object_type=ROBOT; Robot.giroi_pierna_d-=2;
		if(Robot.giroi_pierna_d < Robot.giro_piernai_maxd) Robot.giroi_pierna_d = Robot.giro_piernai_maxd;
	break;
	case GLUT_KEY_F3:Object_type=ROBOT; Robot.giroi_pierna_a+=2;
		if(Robot.giroi_pierna_a > Robot.giro_piernai_maxa) Robot.giroi_pierna_a = Robot.giro_piernai_maxa;
	break;
	case GLUT_KEY_F4:break;
	case GLUT_KEY_F5:break;
	case GLUT_KEY_F6:break;
	case GLUT_KEY_F7:break;
	}
glutPostRedisplay();
}

/** @brief Funcion de inicialización
 *
 * Asigna valores iniciales a los parámetros de vista
 *
*/
void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Size_x=1;
Size_y=1;
Front_plane=2;
Back_plane=1000;

// se incia la posicion del observador, en el eje z
Observer_distance=50;
Observer_angle_x=30;
Observer_angle_y=45;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(0,0,0,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
//
change_projection();
//
glViewport(0,0,Window_width,Window_high);
//
Object_type=ROBOT;
}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{

// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("IG: Practica 3");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
