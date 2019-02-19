//**************************************************************************
// Práctica 1
//

//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include "user_code.h"

// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=450,UI_window_height=450;

int estadoRaton[3], xc, yc, modo[5], cambio=0;

solido *piramide1, *cubo1, *cubo2, *cubo3, *cubo4;

int vista_multiple=0;
int Ancho=450, Alto=450;
float factor=1.0;

void pick(int x, int y);

//**************************************************************************
//
//***************************************************************************

void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
//change_projection();
glViewport(0,0,Ancho,Alto);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glLineWidth(1);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{
int count=1;
     //glInitNames();
     
     glTranslatef(0.0,-0.4,0.0);
     glPushMatrix(); 
     glLoadName(count);
     glTranslatef(0.0,0.8,0.0);
     draw_solido(piramide1,0.1,0.1,0.1,1);
     draw_solido(piramide1,piramide1->r,piramide1->g,piramide1->b,2);
     glPopMatrix();    
     count++;     

     glPushMatrix(); 
     glLoadName(count);
     glTranslatef(-0.5,0.0,0.5);
     draw_solido(cubo1,0.2,0.2,0.4,1);
     draw_solido(cubo1,cubo1->r,cubo1->g,cubo1->b,2);
     glPopMatrix(); 
     count ++;
     
     glPushMatrix(); 
     glLoadName(count);
     glTranslatef(0.5,0.0,0.5);
     draw_solido(cubo2,0.2,0.2,0.7,1);
     draw_solido(cubo2,cubo2->r,cubo2->g,cubo2->b,2);
     glPopMatrix();
     count ++;  

     glPushMatrix(); 
     glLoadName(count);
     glTranslatef(-0.5,0.0,-0.5);
     draw_solido(cubo3,0.2,0.2,1.0,1);
     draw_solido(cubo3,cubo3->r,cubo3->g,cubo3->b,2);
     glPopMatrix(); 
     count ++;

     glPushMatrix(); 
     glLoadName(count);
     glTranslatef(0.5,0.0,-0.5);
     draw_solido(cubo4,1.0,0.2,0.0,1);
     draw_solido(cubo4,cubo4->r,cubo4->g,cubo4->b,2);
     glPopMatrix();    
}



//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();

if (vista_multiple==0)
  {change_observer();
   draw_axis();
   draw_objects();
  }

else
{
   //vista perspectiva
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-Window_width,Window_width,Window_height,
             Window_height,Front_plane,Back_plane);
   glViewport((GLint) Ancho/2.0,0,(GLint)Ancho/2.0,(GLint)Alto/2.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0,0,-Observer_distance);
   glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  draw_axis();
  draw_objects();  

  //vista alzado
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-5.0,5.0,-5.0,5.0,-100.0,100.0);
  glViewport(0,(GLint)Alto/2.0,(GLint) Ancho/2.0,(GLint) Alto/2.0);
  glRotatef(90,1,0,0);
  glScalef(factor,factor,1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  draw_axis();
  draw_objects();
  
  }
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
Ancho=Ancho1;
Alto=Alto1;
draw_scene();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{

if (toupper(Tecla1)=='Q') exit(0);
if (Tecla1=='+') 
   {factor*=0.9;
    glutPostRedisplay();}
if (Tecla1=='-') 
   {factor*=1.1;
    glutPostRedisplay();}
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
        case GLUT_KEY_F1:vista_multiple=1;break;
        case GLUT_KEY_F2:vista_multiple=0;break;
	}
glutPostRedisplay();
}


//***************************************************************************
// Funciones para manejo de eventos del ratón
//***************************************************************************

void clickRaton( int boton, int estado, int x, int y )
{
if(boton== GLUT_RIGHT_BUTTON) {
   if( estado == GLUT_DOWN) {
      estadoRaton[2] = 1;
      xc=x;
      yc=y;
     } 
   else estadoRaton[2] = 1;
   }
if(boton== GLUT_LEFT_BUTTON) {
  if( estado == GLUT_DOWN) {
      estadoRaton[2] = 2;
      xc=x;
      yc=y;
      pick(xc, yc);
    } 
  }
}

/*************************************************************************/

void getCamara (GLfloat *x, GLfloat *y)
{
*x=Observer_angle_x;
*y=Observer_angle_y;
}

/*************************************************************************/

void setCamara (GLfloat x, GLfloat y)
{
Observer_angle_x=x;
Observer_angle_y=y;
}



/*************************************************************************/

void RatonMovido( int x, int y )
{
float x0, y0, xn, yn; 
if(estadoRaton[2]==1) 
    {getCamara(&x0,&y0);
     yn=y0+(y-yc);
     xn=x0-(x-xc);
     setCamara(xn,yn);
     xc=x;
     yc=y;
     glutPostRedisplay();
    }
}


//***************************************************************************
// Funciones para la seleccion
//***************************************************************************


void procesar_hits(GLint hits, GLuint *names)
 {
 	int i;
        solido *obj;

        obj=(solido *)malloc(sizeof(solido));
 
 	/*
 		For each hit in the buffer are allocated 4 bytes:
 		1. Number of hits selected 
 									beacuse when we draw each object
 									we use glLoadName, so we replace the
 									prevous name in the stack)
 		2. Min Z
 		3. Max Z
 		4. Name of the hit (glLoadName)
 	*/
 
 	printf("%d hits:\n", hits);
 
 	for (i = 0; i < hits; i++)
 		printf(	"Número: %d\n"
 				"Min Z: %f\n"
 				"Max Z: %f\n"
 				"Nombre en la pila: %d\n",
 				(GLubyte)names[i * 4],
 				(float)names[i * 4 + 1]/(pow(2,32)-1),
 				(float)names[i * 4 + 2]/(pow(2,32)-1),
 				(GLubyte)names[i * 4 + 3]);
	printf("\n");

        switch (names[0+3])
              {case 1: obj=piramide1;
                       if (modo[0]==0) 
                               {modo[0]=1;
                                cambio=1;
                               }
                          else 
                              {modo[0]=0;
                               cambio=0;
                              }
                       break; 
               case 2: obj=cubo1;
                       if (modo[1]==0) 
                               {modo[1]=1;
                                cambio=1;
                               }
                          else 
                              {modo[1]=0;
                               cambio=0;
                              } 
                       break;
               case 3: obj=cubo2;
                       if (modo[2]==0) 
                               {modo[2]=1;
                                cambio=1;
                               }
                          else 
                              {modo[2]=0;
                               cambio=0;
                              }
                       break; 
               case 4: obj=cubo3;
                       if (modo[3]==0) 
                               {modo[3]=1;
                                cambio=1;
                               }
                          else 
                              {modo[3]=0;
                               cambio=0;
                              }
                       break;
               case 5: obj=cubo4;
                       if (modo[4]==0) 
                               {modo[4]=1;
                                cambio=1;
                               }
                          else 
                              {modo[4]=0;
                               cambio=0;
                              }
                       break;
                }         
               
        if (cambio==1) 
                  {obj->r=0.3;
                   obj->g=0.9;
                   obj->b=0.3;
                  }
        if (cambio==0)
                  {obj->r=0.9;
                   obj->g=0.6;
                   obj->b=0.2;
                  }
                 
 }



void pick(int x, int y)
{
GLuint selectBuf[100]={0}, *names; 
GLint viewport[4], hits=0;


// Declarar buffer de selección
glSelectBuffer(100, selectBuf);
// Obtener los parámetros del viewport
glGetIntegerv (GL_VIEWPORT, viewport);
/*if (vista_multiple==0)
  {viewport[0]=0;
   viewport[1]=0;
   viewport[2]=Ancho;
   viewport[3]=Alto;
  }*/

// Pasar OpenGL a modo selección
glRenderMode (GL_SELECT);
glInitNames();
glPushName(0);
//  Fijar la transformación de proyección para la seleccion
glMatrixMode (GL_PROJECTION);
glLoadIdentity ();
gluPickMatrix (x,(viewport[3] - y),20.0, 20.0, viewport);
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
// Dibujar la escena
draw_scene();
// Pasar OpenGL a modo render
hits = glRenderMode (GL_RENDER);
// Restablecer la transformación de proyección (sin gluPickMatrix)
glMatrixMode (GL_PROJECTION);
glLoadIdentity();
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);

// Analizar el contenido del buffer de selección
procesar_hits(hits, selectBuf);
names=selectBuf;

// Dibujar la escena
draw_scene();
}


//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=.5;
Window_height=.5;
Front_plane=1;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=3*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,UI_window_width,UI_window_height);

for (int i=0;i<5;i++) modo[i]=0;
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
    
    piramide1=(solido*)malloc(sizeof(solido));
    construir_piramide(0.5,0.8,piramide1);
    
    cubo1=(solido*)malloc(sizeof(solido));
    construir_piramide(0.5,0.8,cubo1);
    
    cubo2=(solido*)malloc(sizeof(solido));
    construir_piramide(0.5,0.8,cubo2);
    
    cubo3=(solido*)malloc(sizeof(solido));
    construir_piramide(0.5,0.8,cubo3);
    
    cubo4=(solido*)malloc(sizeof(solido));
    construir_piramide(0.5,0.8,cubo4);
    
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
    glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

    // tamaño de la ventana (ancho y alto)
    glutInitWindowSize(UI_window_width,UI_window_height);

    // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
    // al bucle de eventos)
    glutCreateWindow("Ejemplo");

    // asignación de la funcion llamada "dibujar" al evento de dibujo
    glutDisplayFunc(draw_scene);
    // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
    glutReshapeFunc(change_window_size);
    // asignación de la funcion llamada "tecla_normal" al evento correspondiente
    glutKeyboardFunc(normal_keys);
    // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
    glutSpecialFunc(special_keys);

    // eventos ratón
    glutMouseFunc( clickRaton );
    glutMotionFunc( RatonMovido );


    // funcion de inicialización
    initialize();

    // inicio del bucle de eventos
    glutMainLoop();
    return 0;
}
