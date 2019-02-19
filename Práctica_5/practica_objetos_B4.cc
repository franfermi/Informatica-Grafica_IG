//**************************************************************************
// Práctica 4 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B4.h"

//#define NOBJS 3

using namespace std;

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION, ARTICULADO, CILINDRO,
						ESFERA, TRIANGULO3D, TEXTURA, ESCENA} _tipo_objeto;
_tipo_objeto t_objeto=ROTACION;
_modo modo=POINTS;

/** variables que determninan la posicion y tamaño de la ventana X */
int Window_x=50,Window_y=50,Window_w=500,Window_h=500;

int estadoRaton[3], xc, yc, mod[5], cambio=0;

const int AXIS_SIZE=5000; // Longitud de los ejes

int vista_multiple=0;
int Ancho=450, Alto=450;
float factor=1.0;

/** variables que controlan la ventana y la transformacion de perspectiva */
GLfloat Window_width,Window_height,Front_plane,Back_plane;
GLfloat Ortho_width,Ortho_height;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// luces
GLenum p_luz_ind = GL_LIGHT0;
_vertex4f p_luz_punto = _vertex4f( 1.0, 0.0, 0.0, 0.0 );
_vertex4f p_luz_ambiente = _vertex4f( 0.2, 0.2, 0.2, 1.0 );
_vertex4f p_luz_difusa = _vertex4f( 1.0, 1.0, 1.0, 1.0 );
_vertex4f p_luz_especular = _vertex4f( 1.0, 1.0, 1.0, 1.0 );

GLenum p_luz_ind2 = GL_LIGHT1;
_vertex4f p_luz_punto2 = _vertex4f( -1.0, 0.0, 0.0, 0.0 );
_vertex4f p_luz_ambiente2 = _vertex4f( 1.0, 1.0, 0.0, 1.0 );
_vertex4f p_luz_difusa2 = _vertex4f( 1.0, 1.0, 1.0, 1.0 );
_vertex4f p_luz_especular2 = _vertex4f( 1.0, 1.0, 1.0, 1.0 );

GLenum p_luz_ind3 = GL_LIGHT2;
_vertex4f p_luz_punto3 = _vertex4f( 0.5, 4.0, -3.0, 1.0 );
_vertex4f p_luz_ambiente3 = _vertex4f( 0.0, 1.0, 0.0, 1.0 );
_vertex4f p_luz_difusa3 = _vertex4f( 1.0, 1.0, 1.0, 1.0 );
_vertex4f p_luz_especular3 = _vertex4f( 1.0, 1.0, 1.0, 1.0 );

// objetos
_cubo cubo;
_objeto_ply  ply;
_cilindro cilindro(0.85,1.3,20);
_esfera esfera(0.85,1.3,20);
_esfera esfera2(0.85,1.3,20);
_esfera esfera3(0.85,1.3,20);
_rotacion rotacion;
_iluminacion iluminacion(p_luz_ind, p_luz_punto, p_luz_ambiente, p_luz_difusa, p_luz_especular);
_iluminacion iluminacion2(p_luz_ind2, p_luz_punto2, p_luz_ambiente2, p_luz_difusa2, p_luz_especular2);
_iluminacion iluminacion3(p_luz_ind3, p_luz_punto3, p_luz_ambiente3, p_luz_difusa3, p_luz_especular3);
_triangulos3D triangulos;
//_triangulos3D objs[NOBJS];
_texturas textura;
_textura2 textura2, textura3;
// _texturas *text1;
GLuint id_text1;
// _objeto_ply *ply1;
bool frustum = true;
float zoom = 5;
solido *piramide1, *cubo1, *cubo2, *cubo3, *cubo4;

//**************************************************************************
//
//**************************************************************************

void projection(){
	if(frustum){
		cout << "frustum activado" << endl;
		glFrustum(-Window_height,Window_height,-Window_width,Window_width,Front_plane,Back_plane);
	}
	else{
		cout << "ortho activado" << endl;
    	glOrtho(-Window_height,Window_height,-Window_width,Window_width,Front_plane,Back_plane);
		glScalef(0.5,0.5,0.5);
	}
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	projection();
}

//**************************************************************************
//
//***************************************************************************

void clean_window(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer(){
	// posicion del observador
	//glViewport(0,0,Ancho,Alto);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,0,-Observer_distance);
	glRotatef(Observer_angle_x,1,0,0);
	glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis(){
	//glDisable(GL_LIGHTING);
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
//**************************************************************************

void draw_objects(){
	switch (t_objeto){
		case CUBO: cubo.draw(modo,0.1,0.6,1,0.1,0.6,0.2,2);break;
	  	case OBJETO_PLY: ply.draw(modo,0.1,0.6,1,0.1,0.6,0.2,2);break;
	  	case ROTACION: rotacion.draw(modo,0.1,0.6,1,0.1,0.6,0.2,2);break;
		case CILINDRO: cilindro.draw(modo,0.1,0.6,1,0.1,0.6,0.2,2);break;
		case ESFERA: esfera.draw(modo,0.1,0.6,1,0.1,0.6,0.2,2);break;
		case TEXTURA: textura2.tablero_textura(4,4,4);
				glTranslated(0,1,0);
				textura3.tablero_textura(4,4,4);break;
		case ESCENA: 
				int count=1;
				//glInitNames();
				
				glTranslatef(0.0,-0.4,0.0);
				glPushMatrix(); 
				glLoadName(count);
				glTranslatef(0.0,0.35,0.0);
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
			break;
	}
}

//**************************************************************************
//
//***************************************************************************

void clear_window(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void draw(void){
	clean_window();
	change_observer();
	draw_axis();
	draw_objects();
	glutSwapBuffers();
}

void draw_scene(void){
	clear_window();

	if (vista_multiple==0){
		change_observer();
		draw_axis();
		draw_objects();
	}

	else{
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
	float Aspect_ratio;

	Aspect_ratio=(float) Alto1/(float )Ancho1;
	Window_width=Window_height*Aspect_ratio;
	change_projection();
	glViewport(0,0,Ancho1,Alto1);
	glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y)
{
	switch (toupper(Tecla1)){
		case 'Q':exit(0);
		case '1':modo=POINTS;break;
		case '2':modo=EDGES;break;
		case '3':modo=SOLID;break;
		case '4':modo=SOLID_CHESS;break;
		case '5':modo=SOLID_ILLUMINATED_FLAT;break;
		case '6':modo=SOLID_ILLUMINATED_GOURAUD;break;
		// case '7':modo=TEXTURE;break;
		// case '8':modo=TEXTURE_ILLUMINATED_FLAT;break;
		// case '9':modo=TEXTURE_ILLUMINATED_GOURAUD;break;
	        case 'X':t_objeto=CUBO;break;
	        case 'C':t_objeto=OBJETO_PLY;break;
	        case 'V':t_objeto=ROTACION;break;
			case 'B':t_objeto=CILINDRO;break;
	        case 'M':t_objeto=ESFERA;break;
			case 'Z':t_objeto=ESCENA;break;
					//LIGHT0
					case 'A':iluminacion.activar(p_luz_ind);break;
					case 'D':iluminacion.desactivar(p_luz_ind);break;
					//LIGHT1
					case 'F':iluminacion2.activar(p_luz_ind2);break;
					case 'G':iluminacion2.desactivar(p_luz_ind2);break;
					//LIGHT2
					case 'H':iluminacion3.activar(p_luz_ind3);break;
					case 'J':iluminacion3.desactivar(p_luz_ind3);break;

					case 'R':iluminacion.transformar(p_luz_ind, iluminacion.alpha, 0, 0, 0);break;
					case 'T':textura.inicializarTextura("textPiedra.jpg");break;
					case 'Y':textura.inicializarTextura("textTierra.jpg");break;
					case 'U':textura.inicializarTextura("textTigre.jpeg");break;
					case '0':t_objeto=TEXTURA;break;
		case '7':
			frustum = true;
			change_projection();
			break;
		case '8':
			frustum = false;
			Ortho_height = Window_height;
			Ortho_width = Window_width;
			change_projection();
			break;
		case '+':
			factor*=0.9;
			glutPostRedisplay();
			break;
		case '-':
			factor*=1.1;
			glutPostRedisplay();
			break;
		}
	glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y){
	switch (Tecla1){
		case GLUT_KEY_LEFT:Observer_angle_y--;break;
		case GLUT_KEY_RIGHT:Observer_angle_y++;break;
		case GLUT_KEY_UP:Observer_angle_x--;break;
		case GLUT_KEY_DOWN:Observer_angle_x++;break;
		case GLUT_KEY_PAGE_UP:
			if(frustum)
				Observer_distance*=1.2;
			else{
				Window_width*=1.2;
				Window_height*=1.2;
				change_projection();
			}
			break;
		case GLUT_KEY_PAGE_DOWN:
			if(frustum)
				Observer_distance/=1.2;
			else{
				Window_width/=1.2;
				Window_height/=1.2;
				change_projection();
			}
			break;
	    case GLUT_KEY_F1:vista_multiple=1;break;
        case GLUT_KEY_F2:vista_multiple=0;break;
	        // case GLUT_KEY_F3:
	        // case GLUT_KEY_F4:
		}
	glutPostRedisplay();
}

//***************************************************************************
// Funciones para la seleccion
//***************************************************************************

void procesar_hits(GLint hits, GLuint *names){
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
                       if (mod[0]==0) 
                               {mod[0]=1;
                                cambio=1;
                               }
                          else 
                              {mod[0]=0;
                               cambio=0;
                              }
                       break; 
               case 2: obj=cubo1;
                       if (mod[1]==0) 
                               {mod[1]=1;
                                cambio=1;
                               }
                          else 
                              {mod[1]=0;
                               cambio=0;
                              } 
                       break;
               case 3: obj=cubo2;
                       if (mod[2]==0) 
                               {mod[2]=1;
                                cambio=1;
                               }
                          else 
                              {mod[2]=0;
                               cambio=0;
                              }
                       break; 
               case 4: obj=cubo3;
                       if (mod[3]==0) 
                               {mod[3]=1;
                                cambio=1;
                               }
                          else 
                              {mod[3]=0;
                               cambio=0;
                              }
                       break;
               case 5: obj=cubo4;
                       if (mod[4]==0) 
                               {mod[4]=1;
                                cambio=1;
                               }
                          else 
                              {mod[4]=0;
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
                  {obj->r=0.5;
                   obj->g=0.6;
                   obj->b=0.5;
                  }
                 
}

void pick(int x, int y){ //Hace la selección
	GLuint selectBuf[100]={0}, *names;
	GLint viewport[4], hits=0;

	// Declarar buffer de selección
	glSelectBuffer(100, selectBuf);
	// Obtener los parámetros del viewport
	glGetIntegerv (GL_VIEWPORT, viewport);

	if (vista_multiple==0)
	  {viewport[0]=0;
	   viewport[1]=0;
	   viewport[2]=Ancho;
	   viewport[3]=Alto;
	  }

	// Pasar OpenGL a modo selección
	glRenderMode (GL_SELECT);
	glInitNames();
	glPushName(0);
	//  Fijar la transformación de proyección para la seleccion
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPickMatrix (x,(viewport[3] - y),20.0, 20.0, viewport);
	//Añadir las condiciones de cambios de perspectiva
	// change_projection();
	//glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
	projection();
	// Dibujar la escena
	draw_scene();
	// Pasar OpenGL a modo render
	hits = glRenderMode (GL_RENDER);
	// Restablecer la transformación de proyección (sin gluPickMatrix)
	// glMatrixMode (GL_PROJECTION);
	// glLoadIdentity();
	// glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
	change_projection();
	// Analizar el contenido del buffer de selección
	procesar_hits(hits, selectBuf);
	names=selectBuf;

	// Dibujar la escena
	draw_scene();
}


//***************************************************************************
// Funciones para manejo de eventos del ratón
//***************************************************************************

void clickRaton( int boton, int estado, int x, int y ){
	if(boton== GLUT_RIGHT_BUTTON) {
		if( estado == GLUT_DOWN) {
			estadoRaton[2] = 1;
			xc=x;
			yc=y;
		}
		else 
			estadoRaton[2] = 1;
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

void getCamara (GLfloat *x, GLfloat *y){
	*x=Observer_angle_x;
	*y=Observer_angle_y;
}

/*************************************************************************/

void setCamara (GLfloat x, GLfloat y){
	Observer_angle_x=x;
	Observer_angle_y=y;
}

/*************************************************************************/

void RatonMovido(int x, int y){
	float x0, y0, xn, yn;
	if (estadoRaton[2] == 1)	{
		getCamara(&x0, &y0);
		yn = y0 + (y - yc);
		xn = x0 - (x - xc);
		setCamara(xn, yn);
		xc = x;
		yc = y;
		glutPostRedisplay();
	}
}

//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void){
	// se inicalizan la ventana y los planos de corte
	Window_height=.5;
	Window_width=.5;
	Front_plane=1;
	Back_plane=1000;

	// se incia la posicion del observador, en el eje z
	Observer_distance=3*Front_plane;
	Observer_angle_x=0;
	Observer_angle_y=0;

	// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
	// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
	glClearColor(1,1,1,1);

	// se habilita el z-bufer
	glEnable(GL_DEPTH_TEST);
	change_projection();
	glViewport(0,0,Window_w,Window_h);

	for (int i=0;i<5;i++) mod[i]=0;


	//Objetos
	// objs[0] = _esfera (0.85,1.3,20);
	// objs[1] = _esfera (0.85,1.3,20);
	// objs[2] = _esfera (0.85,1.3,20);
}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main(int argc, char **argv){
	piramide1=(solido*)malloc(sizeof(solido));
    construir_piramide(0.5,0.8,piramide1);

	cubo1=(solido*)malloc(sizeof(solido));
    construir_cubo(0.35,cubo1);
    
    cubo2=(solido*)malloc(sizeof(solido));
    construir_cubo(0.35,cubo2);
    
    cubo3=(solido*)malloc(sizeof(solido));
    construir_cubo(0.35,cubo3);
    
    cubo4=(solido*)malloc(sizeof(solido));
    construir_cubo(0.35,cubo4);

	// creación del objeto ply

	ply.parametros(argv[1]);

	// perfil

	vector<_vertex3f> perfil2;
	_vertex3f aux;
	aux.x=1.0;aux.y=-1.4;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=1.0;aux.y=-1.1;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.5;aux.y=-0.7;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.4;aux.y=-0.4;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.4;aux.y=0.5;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.5;aux.y=0.6;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.3;aux.y=0.6;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.5;aux.y=0.8;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.55;aux.y=1.0;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.5;aux.y=1.2;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.3;aux.y=1.4;aux.z=0.0;
	perfil2.push_back(aux);
	rotacion.parametros(perfil2,6);
	//rotacion.parametros(perfil2,6,1);

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
	// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// posicion de la esquina inferior izquierdad de la ventana
	glutInitWindowPosition(Window_x,Window_y);

	// tamaño de la ventana (ancho y alto)
	glutInitWindowSize(Window_w,Window_h);

	// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
	// al bucle de eventos)
	glutCreateWindow("PRACTICA - 5");

	// asignación de la funcion llamada "dibujar" al evento de dibujo
	glutDisplayFunc(draw_scene);
	// asignación de la funcion llamada "change_window_size" al evento correspondiente
	glutReshapeFunc(change_window_size);
	// asignación de la funcion llamada "normal_key" al evento correspondiente
	glutKeyboardFunc(normal_key);
	// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
	glutSpecialFunc(special_key);

	// eventos ratón
    glutMouseFunc( clickRaton );
    glutMotionFunc( RatonMovido );

	// funcion de inicialización
	initialize();

	// text1 = new _texturas(argv[6]);
	// id_text1 = text1->ident_textura;

	// inicio del bucle de eventos
	glutMainLoop();
	return 0;
}
