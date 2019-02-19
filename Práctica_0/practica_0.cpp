#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>



void Ejes (int width)
{   
    glLineWidth(width);
    glBegin(GL_LINES);
       glColor3f(1.0,0.0,0.0);
       glVertex3f(-1.0,0.0,0.0);
       glVertex3f(1.0,0.0,0.0);
       glColor3f(0.0,1.0,0.0);
       glVertex3f(0.0,-1.0,0.0);
       glColor3f(1.0,1.0,0.0);
       glVertex3f(0.0,1.0,0.0);   
    glEnd();
   
       
}

////////////////////////////////////////////7
void Circle (GLfloat radio, GLfloat cx, GLfloat cy, GLint n, GLenum modo)
{
  int i;
  if (modo==GL_LINE) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else if (modo==GL_FILL) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  else glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
  glBegin( GL_POLYGON );
  for (i=0;i<n;i++)
  glVertex2f( cx+radio*cos(2.0*M_PI*i/n), cy+radio*sin(2.0*M_PI*i/n));
  glEnd();
}

void Poligono_Solido (float v[][3], int n)
{
  int i;
  glPolygonMode(GL_FRONT, GL_FILL);
  glBegin(GL_POLYGON);
  for (i=0;i<n;i++) glVertex3f(v[i][0],v[i][1],v[i][2]);
  glEnd();
}
/////////////////////////////////////////////


void Monigote ()
{
  float copa_sombrero[4][3]={{-0.2,0.7,0.0},{0.2,0.7,0.0},{0.2,0.95,0.0},{-0.2,0.95,0.0}};
  float ala_sombrero[4][3]={{-0.35,0.55,0.0},{0.35,0.55,0.0},{0.35,0.7,0.0},{-0.35,0.7,0.0}};
  float nariz[3][3]={{-0.35,0.55,0.0},{0.35,0.55,0.0},{0.35,0.7,0.0}};
  float boca[4][3]={{-0.1,0.10,0.0},{0.1,0.10,0.0},{0.1,0.15,0.0},{-0.1,0.15,0.0}};

// cara
   glLineWidth(1);
   glColor3f(1.0,0.8,0.6);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.0,0.0);
      glVertex3f(0.2,0.0,0.0);
      glVertex3f(0.2,0.55,0.0);
      glVertex3f(-0.2,0.55,0.0);
   glEnd();

// sombrero
  glColor3f(0.0,0.0,0.0);
  Poligono_Solido(copa_sombrero,4);
  Poligono_Solido(ala_sombrero,4);

// ojo derecho
  //////////////////////////////////////
  glColor3f(0.1,0.0,1.0);
  Circle(0.05,0.1,0.4,20,GL_FILL);
  ////////////////////////////////////// 

// ojo izquierdo
  //////////////////////////////////////
  glColor3f(0.1,0.0,1.0);
  Circle(0.05,-0.1,0.4,20,GL_FILL);
  ////////////////////////////////////// 

// oreja izquierda
  /////////////////////////////////////
  glLineWidth(1);
  glColor3f(1.0,0.8,0.6);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_POLYGON);
    glVertex3f(-0.25,0.3,0.0);
    glVertex3f(-0.2,0.3,0.0);
    glVertex3f(-0.2,0.5,0.0);
    glVertex3f(-0.25,0.5,0.0);
  glEnd();
  /////////////////////////////////////

// oreja derecha
  /////////////////////////////////////
  glLineWidth(1);
  glColor3f(1.0,0.8,0.6);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_POLYGON);
    glVertex3f(0.2,0.3,0.0);
    glVertex3f(0.25,0.3,0.0);
    glVertex3f(0.25,0.5,0.0);
    glVertex3f(0.2,0.5,0.0);
  glEnd();
  /////////////////////////////////////

// nariz
  /////////////////////////////////////
  glLineWidth(1);
  glColor3f(0.9,0,0.1);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_POLYGON);
    glVertex3f(-0.05,0.2,0.0);
    glVertex3f(0.05,0.2,0.0);
    glVertex3f(0.0,0.3,0.0);
  glEnd();
  /////////////////////////////////////

// boca
  /////////////////////////////////////
   glColor3f(0.9,0.7,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.12,0.04,0.0);
      glVertex3f(0.12,0.04,0.0);
      glVertex3f(0.14,0.06,0.0);
      glVertex3f(0.14,0.1,0.0);
      glVertex3f(0.12,0.12,0.0);
      glVertex3f(-0.12,0.12,0.0);
      glVertex3f(-0.14,0.1,0.0);
      glVertex3f(-0.14,0.06,0.0);
   glEnd(); 
  ////////////////////////////////////
   glColor3f(0.0,0.0,0.);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.0,0.0);
      glVertex3f(0.2,0.0,0.0);
      glVertex3f(0.2,0.55,0.0);
      glVertex3f(-0.2,0.55,0.0);
   glEnd(); 
   
}


static void Init( )
{

   glShadeModel( GL_FLAT);
}


static void Reshape( int width, int height )
{
    glViewport(0, 0, (GLint)width, (GLint)height);
    glOrtho (-1.0, 1.0,-1.0, 1.0, -10, 10.0);
}

static void Display( )
{

  glClearColor(0.5,0.5,0.5,0.0);
  glClear( GL_COLOR_BUFFER_BIT );
   
  
   
   Ejes(6);
   Monigote();
   
   glFlush();
}


static void Keyboard(unsigned char key, int x, int y )
{
 
  if (key==27)
      exit(0);

}

int main( int argc, char **argv )
{
  glutInit(&argc,argv);
  glutInitDisplayMode( GLUT_RGB );

  glutInitWindowPosition( 20, 100 );
  glutInitWindowSize(500, 500 );
  glutCreateWindow("Practica 0 IG");

  Init();

  glutReshapeFunc(Reshape);
  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);
        
  glutMainLoop( );

   return 0;
}

