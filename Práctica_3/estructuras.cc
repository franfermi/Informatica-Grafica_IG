#include "objetos.h"
#include "estructuras.h"
#include "stdio.h"
#include "math.h"

/** Calcula el modulo del vector (x,y,z) **/
float modulo(float x,float y,float z)
{
   return sqrt(x*x+y*y+z*z);
}



//*************************************************************************
//* PRIMITIVAS BASICAS
//***********************************************************

void esfera(float radio, int nlatitud, int nlongitud)
{
     const float pi = 3.14159265358979323846;
     float inct, incf;
     int i, j;
     float vertice[3];
     inct = 2 * pi / nlatitud;
     incf = pi / nlatitud;
     for( i = 0; i < nlatitud; i++ )
     {
          glBegin( GL_QUAD_STRIP );
          vertice[0] = vertice[1] = 0;
          vertice[2] =- radio;
          glVertex3fv( vertice );
          for( j = 1; j < nlongitud-1; j++ )
          {
               vertice[0] = radio * cos(i*inct) * cos(j*incf-0.5*pi);
               vertice[1] = radio * sin(i*inct) * cos(j*incf-0.5*pi);
               vertice[2] = radio * sin(j*incf-0.5*pi);
               glVertex3fv( vertice );
               vertice[0] = radio*cos((i+1)*inct)*cos(j*incf-0.5*pi);
               vertice[1] = radio*sin((i+1)*inct)*cos(j*incf-0.5*pi);
               glVertex3fv(vertice);
          }
          vertice[0] = vertice[1] = 0;
          vertice[2] = radio;
          glVertex3fv( vertice );
     }
     glEnd();
}

// Construye un Disco
void tapas_cilindro(GLfloat radio)
{
  GLUquadricObj *qobj;
  qobj = gluNewQuadric();
  gluDisk(qobj,0.0,radio,10,10);
  gluDeleteQuadric(qobj);
}

//Elipse
void elipse(float cx, float cy, float rx, float ry, int num_segments)
{
    float theta = 2 * 3.1415926 / float(num_segments);
    float c = cosf(theta);
    float s = sinf(theta);
    float t;

    float x = 1;
    float y = 0;

    glBegin(GL_LINE_LOOP);
    for(int ii = 0; ii < num_segments; ii++)
    {
        glVertex2f(x * rx + cx, y * ry + cy);
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}

//Cilindro
void cilindro(GLfloat radio,GLfloat altura)
{
  GLUquadricObj *qobj;
  // cilindro
  glPushMatrix();
	glTranslatef(0.0,altura-1,0.0);
    	glPushMatrix();
  		qobj = gluNewQuadric();
        	glRotatef(90.0,1.0,0.0,0.0);
        	glTranslatef(0.0,0.0,-1.0);
        	gluCylinder(qobj,radio,radio,altura,10,10);
        	gluDeleteQuadric(qobj);
    	glPopMatrix();
  glPopMatrix();
  // tapa superior
  glPushMatrix();
	glTranslatef(0.0,altura,0.0);
	glRotatef(-90.0,1.0,0.0,0.0);
	tapas_cilindro(radio);
  glPopMatrix();
  // tapa inferior
  glPushMatrix();
	glRotatef(-90.0,1.0,0.0,0.0);
	tapas_cilindro(radio);
  glPopMatrix();
}

/**
Construye un paralelepipedo alineado con los ejes de
dimension a x b x m. El objeto se construye en el semiespacio y>=0, con el origen en el
centro de la base.
**/
void caja( float a, float b, float m)

{
	float x,y,z;

	x= a/2;
	z= m/2;
	y = b;

   glShadeModel( GL_FLAT );

   /* Caras transversales */
   glBegin( GL_QUAD_STRIP );{
      glNormal3f( 0.0, 0.0, -1.0 );   /* Vertical hacia atras */
      glVertex3f( x, 0, -z );
      glVertex3f( -x, 0, -z );
      glVertex3f( x, y, -z );
      glVertex3f( -x, y, -z );

	  glNormal3f( 0.0, 1.0, 0.0 );       /* Superior, horizontal */
	  glVertex3f( x, y, z );
      glVertex3f( -x, y, z );

	  glNormal3f( 0.0, 0.0, 1.0 );       /*Vertical delantera*/
      glVertex3f( x, 0, z );
      glVertex3f( -x, 0, z );

	  glNormal3f( 0.0, -1.0, 0.0 );       /*Inferior */
      glVertex3f( x, 0, -z );
      glVertex3f( -x, 0, -z );  }
    glEnd();

   /* Costados */
   glBegin( GL_QUADS );{
      glNormal3f( 1.0, 0.0, 0.0 );
      glVertex3f( x, 0, -z );
      glVertex3f( x, y, -z );
      glVertex3f( x, y, z );
      glVertex3f( x, 0, z ); }
   glEnd();

   glBegin( GL_QUADS );{
      glNormal3f( -1.0, 0.0, 0.0 );
      glVertex3f( -x, 0, -z );
      glVertex3f( -x, 0, z );
      glVertex3f( -x, y, z );
      glVertex3f( -x, y, -z ); }
   glEnd();
}


/**

Crea un cilindro con centro de las bases en
x0,y0,z0 y x1,y1,z1, y radio de la base a.

**/
void cilindro(float x0, float y0, float z0, float x1, float y1, float z1,
		    float a)
{
float a2,m;

m= modulo(x1-x0,y1-y0,z1-z0);
glPushMatrix();
	glTranslatef(x0,y0,z0);
	glRotatef(-180.0*atan2((z1-z0),(x1-x0))/M_PI,0.0,1.0,0.0);
	glRotatef(180.0*atan2((y1-y0),sqrt((x1-x0)*(x1-x0)+(z1-z0)*(z1-z0)))/M_PI-90,0.0,0.0,1.0);

	a2= a/2.0;
   glShadeModel( GL_SMOOTH );

   /* Caras transversales */
   glBegin( GL_QUAD_STRIP );{
      glNormal3f( 1.0, 0.0, -1.0 );

      glVertex3f(  a2, m, -a2 );
      glVertex3f(  a2, 0, -a2 );

     glNormal3f( -1.0, 0.0, -1.0 );

      glVertex3f( -a2, m, -a2 );
      glVertex3f( -a2, 0, -a2 );

     glNormal3f( -1.0, 0.0, 1.0 );

      glVertex3f( -a2, m, a2 );
      glVertex3f( -a2, 0, a2 );

    glNormal3f( 1.0, 0.0, 1.0 );

      glVertex3f(  a2, m, a2 );
      glVertex3f(  a2, 0, a2 );

     glNormal3f( 1.0, 0.0, -1.0 );

      glVertex3f(  a2, m, -a2 );
      glVertex3f(  a2, 0, -a2 );  }
    glEnd();
   glShadeModel( GL_FLAT );
  /* Tapas */
   glBegin( GL_QUADS );{
      glNormal3f( 0.0, 1.0, 0.0 );
      glVertex3f( -a2, m, -a2 );
      glVertex3f( -a2, m,  a2 );
      glVertex3f(  a2, m,  a2 );
      glVertex3f(  a2, m, -a2 ); }
   glEnd();


   glBegin( GL_QUADS );{
      glNormal3f( 0.0, -1.0, 0.0 );
      glVertex3f( -a2, 0, -a2 );
      glVertex3f(  a2, 0, -a2 );
      glVertex3f(  a2, 0,  a2 );
      glVertex3f( -a2, 0,  a2 ); }
   glEnd();

glPopMatrix();

}



/**
Crea un cilindro con centro de las bases en
x0,y0,z0 y x1,y1,z1, y radio de la base a,
aproximado por n caras
**/
void cilindrof(float x0, float y0, float z0,
		    float x1, float y1, float z1,
		    float a, int n)
{
float m,x,z,i,xf,zf,da;

m= modulo(x1-x0,y1-y0,z1-z0);
glPushMatrix();
	glTranslatef(x0,y0,z0);
	glRotatef(-180.0*atan2((z1-z0),(x1-x0))/M_PI,0.0,1.0,0.0);
	glRotatef(180.0*atan2((y1-y0),sqrt((x1-x0)*(x1-x0)+(z1-z0)*(z1-z0)))/M_PI-90,0.0,0.0,1.0);


  glShadeModel( GL_SMOOTH );

   /* Caras transversales */
   xf = a;
   zf = 0;
   da = 2*M_PI/n;
   glBegin( GL_QUAD_STRIP );
   	for(i=0;i<=n;++i) {
		x=a*cos(da*i);
		z=a*sin(da*i);
  	    	glNormal3f( z, 0.0, x );
		glVertex3f(  x, 0, z );
      		glVertex3f(  x, m, z );
      		}
    glEnd();
   glShadeModel( GL_FLAT );

   // Tapaderas
 	glBegin( GL_POLYGON );
	glNormal3f( 0,-1,0 );
   	for(i=0;i<=n;++i) {
		x=a*cos(da*i);
		z=a*sin(da*i);
		glVertex3f(  x, 0, z );
      		}
    glEnd();
	glBegin( GL_POLYGON );
	glNormal3f( 0,1,0 );
   	for(i=n;i>=0;--i) {
		x=a*cos(da*i);
		z=a*sin(da*i);
		glVertex3f(  x, m, z );
      		}
    glEnd();
glPopMatrix();

}



/**
Crea un cono con centro de las bases en
x0,y0,z0 y x1,y1,z1, y radio de la base a.
**/
void cono(float x0, float y0, float z0,
		    float x1, float y1, float z1,
		    float a)
{
float a2,m,norma,n1,n2;

m= modulo(x1-x0,y1-y0,z1-z0);
glPushMatrix();
	glTranslatef(x0,y0,z0);
	glRotatef(-180.0*atan2((z1-z0),(x1-x0))/M_PI,0.0,1.0,0.0);
	glRotatef(180.0*atan2((y1-y0),sqrt((x1-x0)*(x1-x0)+(z1-z0)*(z1-z0)))/M_PI-90,0.0,0.0,1.0);

	a2= a/2.0;
	norma=sqrt(a2*a2+2*m*m);
	n1= a2/norma;
	n2= m/norma;
   glShadeModel( GL_SMOOTH );

   /* Caras transversales */
   glBegin( GL_QUAD_STRIP );{
     glNormal3f( n2, n1, -n2 );
      glVertex3f(  0, m, 0 );
      glVertex3f(  a2, 0, -a2 );

     glNormal3f( -n2, n1, -n2 );
      glVertex3f( 0, m, 0 );
      glVertex3f( -a2, 0, -a2 );

     glNormal3f( -n2, n1, n2 );
      glVertex3f( 0, m,0 );
      glVertex3f( -a2, 0, a2 );

     glNormal3f( n2, n1, n2 );
      glVertex3f(  0, m, 0 );
      glVertex3f(  a2, 0, a2 );

     glNormal3f( n2, n1, -n2 );
      glVertex3f(  0, m, 0 );
      glVertex3f(  a2, 0, -a2 );  }
    glEnd();

 glShadeModel( GL_FLAT );
  /* Tapa */
   glBegin( GL_QUADS );{
      glNormal3f( 0.0, -1.0, 0.0 );
      glVertex3f( -a2, 0, -a2 );
      glVertex3f(  a2, 0, -a2 );
      glVertex3f(  a2, 0,  a2 );
      glVertex3f( -a2, 0,  a2 ); }
   glEnd();

glPopMatrix();

}

/**
Crea un cono con centro de las bases en
x0,y0,z0 y x1,y1,z1, y radio de la base a,
aproximado por n caras
**/
void conof(float x0, float y0, float z0,
		    float x1, float y1, float z1,
		    float a, int n)
{
float m,x,z,i,xf,zf,da;

m= modulo(x1-x0,y1-y0,z1-z0);
glPushMatrix();
	glTranslatef(x0,y0,z0);
	glRotatef(-180.0*atan2((z1-z0),(x1-x0))/M_PI,0.0,1.0,0.0);
	glRotatef(180.0*atan2((y1-y0),sqrt((x1-x0)*(x1-x0)+(z1-z0)*(z1-z0)))/M_PI-90,0.0,0.0,1.0);


  glShadeModel( GL_SMOOTH );

   /* Caras transversales */
   xf = a;
   zf = 0;
   da = 2*M_PI/n;
   glBegin( GL_TRIANGLE_FAN );
   glVertex3f(  x1, y1, z1 );
   	for(i=0;i<=n;++i) {
		x=a*cos(da*i);
		z=-a*sin(da*i);
  	    	glNormal3f( z, 0.0, x );
			glVertex3f(  x, 0, z );
      		}
    glEnd();
   glShadeModel( GL_FLAT );

   // Tapaderas
 	glBegin( GL_POLYGON );
	glNormal3f( 0,-1,0 );
   	for(i=0;i<=n;++i) {
		x=a*cos(da*i);
		z=a*sin(da*i);
		glVertex3f(  x, 0, z );
      		}
    glEnd();

glPopMatrix();

}


/**

Crea un paralelepipedo con centro de las bases en
x0,y0,z0 y x1,y1,z1, y tamanyo de la base axb.

**/
void paralelepipedo(float x0, float y0, float z0,
		    float x1, float y1, float z1,
		    float a, float b)
{
float m;

m= modulo(x1-x0,y1-y0,z1-z0);
glPushMatrix();
	glTranslatef(x0,y0,z0);
	glRotatef(-180.0*atan2((z1-z0),(x1-x0))/M_PI,0.0,1.0,0.0);
	glRotatef(180.0*atan2((y1-y0),sqrt((x1-x0)*(x1-x0)+(z1-z0)*(z1-z0)))/M_PI-90,0.0,0.0,1.0);
	caja(a,m,b);
glPopMatrix();
}


/************************************************************************
Crea un fragmento de estructura de una grua, con centro de las bases en
x0,y0,z0 y x1,y1,z1. Las secciones de las bases tienen tamanyo axb
n es el numero de niveles que tiene la estructura.

Los perfiles tienen seccion cuadrada, dada por el parametro seccion.

Para crear la estructura se utiliza el procedimiento paralelepipedo.
*************************************************************************/

void creaEstructura(float x0, float y0, float z0,
		    float x1, float y1, float z1, float a, float b, int n)

{
float  y,a2,b2;
int i;
float m,e;

if(n<1) { printf("\n Error: Numero de segmentos en estructura menor que 1\n");return;}

m= modulo(x1-x0,y1-y0,z1-z0);
glPushMatrix();
	glTranslatef(x0,y0,z0);
	glRotatef(-180.0*atan2((z1-z0),(x1-x0))/M_PI,0.0,1.0,0.0);
	glRotatef(180.0*atan2((y1-y0),sqrt((x1-x0)*(x1-x0)+(z1-z0)*(z1-z0)))/M_PI-90,0.0,0.0,1.0);
// Creamos la estructura vertical, con altura m

e=m/n;	// Altura entre dos niveles


y=0;
a2= a/2.;
b2= b/2.;
for(i=0;i<n;++i)
	{
	// Barras horizontales
	paralelepipedo(-a2,y,-b2, a2,y,-b2,seccion,seccion);
	paralelepipedo( a2,y,-b2, a2,y, b2,seccion,seccion);
	paralelepipedo( a2,y, b2,-a2,y, b2,seccion,seccion);
	paralelepipedo(-a2,y, b2,-a2,y,-b2,seccion,seccion);

	// Barras oblicuas
	if(i%2) {
		paralelepipedo(-a2,y,-b2, a2,y+e,-b2,seccion,seccion);
		paralelepipedo( a2,y,-b2, a2,y+e, b2,seccion,seccion);
		paralelepipedo( a2,y, b2,-a2,y+e, b2,seccion,seccion);
		paralelepipedo(-a2,y, b2,-a2,y+e,-b2,seccion,seccion);
		}
	else {
		paralelepipedo( a2,y,-b2,-a2,y+e,-b2,seccion,seccion);
		paralelepipedo( a2,y, b2, a2,y+e,-b2,seccion,seccion);
		paralelepipedo(-a2,y, b2, a2,y+e, b2,seccion,seccion);
		paralelepipedo(-a2,y,-b2,-a2,y+e, b2,seccion,seccion);
	}

	// Barras verticales
	paralelepipedo(-a2,y,-b2,-a2,y+e,-b2,seccion,seccion);
	paralelepipedo( a2,y,-b2, a2,y+e,-b2,seccion,seccion);
	paralelepipedo(-a2,y, b2,-a2,y+e, b2,seccion,seccion);
	paralelepipedo( a2,y, b2, a2,y+e, b2,seccion,seccion);

	// Siguiente nivel
	y=y+e;
	}

// Barras horizontales de terminacion
paralelepipedo(-a2,y,-b2, a2,y,-b2,seccion,seccion);
paralelepipedo( a2,y,-b2, a2,y, b2,seccion,seccion);
paralelepipedo( a2,y, b2,-a2,y, b2,seccion,seccion);
paralelepipedo(-a2,y, b2,-a2,y,-b2,seccion,seccion);

glPopMatrix();
}

/************************************************************************
Crea un fragmento del brazo de una grua, con centro una de las aristas
de cada extremos en
x0,y0,z0 y x1,y1,z1. Los lados de las bases tienen tamanyo a,
n es el numero de tramos.

Los perfiles tienen seccion triangular

Para crear la estructura se utiliza el procedimiento paralelepipedo.
*************************************************************************/

void creaBrazo(float x0, float y0, float z0,
		    float x1, float y1, float z1, float a, int n)

{
float  y,a2,b;
int i;
float m,e;

if(n<2) { printf("\n Error: Numero de segmentos en brazo menor que 2\n");return;}

//glEnable(GL_NORMALIZE);
m= modulo(x1-x0,y1-y0,z1-z0);
glPushMatrix();
	glTranslatef(x0,y0,z0);
	glRotatef(-180.0*atan2((z1-z0),(x1-x0))/M_PI,0.0,1.0,0.0);
	glRotatef(180.0*atan2((y1-y0),sqrt((x1-x0)*(x1-x0)+(z1-z0)*(z1-z0)))/M_PI-90,0.0,0.0,1.0);
// Creamos el brazo vertical, con altura m

e=m/n;	// Altura entre dos tramos

y=0;
a2= a/2.;
b=  sqrt(3.0)*a/2.0; // Altura del triángulo de la base.

paralelepipedo( 0, y,-a2, 0,y, a2,seccion,seccion);

paralelepipedo( 0, y,-a2, 0,y+e, a2,seccion,seccion);
paralelepipedo( 0, y, a2,-b,y+e, 0,seccion,seccion);
paralelepipedo( 0, y,-a2,-b,y+e, 0,seccion,seccion);

paralelepipedo(0,y,-a2,0,y+e,-a2,seccion,seccion);
paralelepipedo( 0,y,a2, 0,y+e,a2,seccion,seccion);
y=y+e;

for(i=1;i<n;++i)
	{
	// Barras horizontales
	paralelepipedo( 0, y,-a2, 0,y, a2,seccion,seccion);
	paralelepipedo( 0, y, a2,-b,y, 0,seccion,seccion);
	paralelepipedo(-b, y, 0,  0,y,-a2,seccion,seccion);

	// Barras oblicuas
	if(i%2) {
		paralelepipedo( 0, y,-a2, 0,y+e, a2,seccion,seccion);
		paralelepipedo( 0, y, a2,-b,y+e, 0,seccion,seccion);
		paralelepipedo(-b, y, 0,  0,y+e,-a2,seccion,seccion);
		}
	else {
		paralelepipedo( 0, y, a2, 0,y+e,-a2,seccion,seccion);
		paralelepipedo(-b, y, 0,  0,y+e, a2,seccion,seccion);
		paralelepipedo( 0, y, -a2,-b,y+e, 0,seccion,seccion);
	}
	// Barras verticales
	paralelepipedo(0,y,-a2,0,y+e,-a2,seccion,seccion);
	paralelepipedo( 0,y,a2, 0,y+e,a2,seccion,seccion);
	paralelepipedo(  -b,y, 0, -b,y+e,0,seccion,seccion);

	// Siguiente nivel
	y=y+e;
	}

	// Barras horizontales
	paralelepipedo( 0, y,-a2, 0,y, a2,seccion,seccion);
	paralelepipedo( 0, y, a2,-b,y, 0,seccion,seccion);
	paralelepipedo(-b, y, 0,  0,y,-a2,seccion,seccion);

glPopMatrix();
}


/************************************************************************
Crea un fragmento de la terminacion de la estructura de una grua,
con centro de las bases en
0,0,0 y 0,h,0. Las secciones de las bases tienen tamanyo axb
n es el numero de niveles que tiene la estructura.

Los perfiles tienen seccion cuadrada, dada por el parametro seccion.
Para crear la estructura se utiliza el procedimiento paralelepipedo.
*************************************************************************/

void creaTorre(float h, float a, float b, int n)

{
float  y,a2,b2;
int i;
float m,e,da,db; //da es el decremento de seccion

if(n<1) { printf("\n Error: Numero de segmentos en torre menor que 1\n");return;}

m=h;
glPushMatrix();

// Creamos la estructura vertical, con altura m

e=m/n;	// Altura entre dos niveles
da = a / (2.0*n);
db = b / (2.0*n);
y=0;
a2= a/2.;
b2= b/2.;
for(i=0;i<n;++i)
	{
	// Barras horizontales
	paralelepipedo(-a2,y,-b2, a2,y,-b2,seccion,seccion);
	paralelepipedo( a2,y,-b2, a2,y, b2,seccion,seccion);
	paralelepipedo( a2,y, b2,-a2,y, b2,seccion,seccion);
	paralelepipedo(-a2,y, b2,-a2,y,-b2,seccion,seccion);

	// Barras oblicuas
	if(i%2) {
		paralelepipedo(-a2,y,-b2, a2-da,y+e,-b2+db,seccion,seccion);
		paralelepipedo( a2,y,-b2, a2-da,y+e, b2-db,seccion,seccion);
		paralelepipedo( a2,y, b2,-a2+da,y+e, b2-db,seccion,seccion);
		paralelepipedo(-a2,y, b2,-a2+da,y+e,-b2+db,seccion,seccion);
		}
	else {
		paralelepipedo( a2,y,-b2,-a2+da,y+e,-b2+db,seccion,seccion);
		paralelepipedo( a2,y, b2, a2-da,y+e,-b2+db,seccion,seccion);
		paralelepipedo(-a2,y, b2, a2-da,y+e, b2-db,seccion,seccion);
		paralelepipedo(-a2,y,-b2,-a2+da,y+e, b2-db,seccion,seccion);
	}

	// Barras verticales
	paralelepipedo(-a2,y,-b2,-a2+da,y+e,-b2+db,seccion,seccion);
	paralelepipedo( a2,y,-b2, a2-da,y+e,-b2+db,seccion,seccion);
	paralelepipedo(-a2,y, b2,-a2+da,y+e, b2-db,seccion,seccion);
	paralelepipedo( a2,y, b2, a2-da,y+e, b2-db,seccion,seccion);

	// Siguiente nivel
	y=y+e;
	a2 = a2 - da;
	b2 = b2 -db;
	}

// Barras horizontales de terminacion
paralelepipedo(-a2,y,-b2, a2,y,-b2,seccion,seccion);
paralelepipedo( a2,y,-b2, a2,y, b2,seccion,seccion);
paralelepipedo( a2,y, b2,-a2,y, b2,seccion,seccion);
paralelepipedo(-a2,y, b2,-a2,y,-b2,seccion,seccion);

glPopMatrix();
}

/************************************************************************
Crea un gancho colgando del punto (0,0,0) de tamanyo alto
El gancho siempre esta vertical
*************************************************************************/

void creaGancho( float alto)
{
float esqueleto[5][2]={{0,0},{0,-0.3},{-0.3,-0.6},{0,-0.8},{0.2,-0.7}};
float normal[5][2]={{1,0},{0.89,0.45},{1,0},{0.2,0.98},{0.45,0.89}};
int i,N=5; // Número de puntos del esqueleto
float grueso=0.1;

glPushMatrix();

for(i=1;i<N;++i){
	esqueleto[i][0]*=alto;
	esqueleto[i][1]*=alto;
}

for(i=0;i<N-1;++i) {
	glShadeModel(GL_SMOOTH);
	glBegin( GL_QUAD_STRIP );{
		glNormal3f( normal[i][0],  normal[i][1], 0.0 );
	      	glVertex3f( esqueleto[i][0]+grueso,  esqueleto[i][1], 0 );
		glNormal3f( normal[i+1][0],  normal[i+1][1], 0.0 );
	      	glVertex3f( esqueleto[i+1][0]+grueso,  esqueleto[i+1][1], 0 );
		glNormal3f( 0.0, normal[i][1], -normal[i][0] );
 		glVertex3f(  esqueleto[i][0],  esqueleto[i][1], -grueso);
		glNormal3f( 0.0, normal[i+1][1], -normal[i+1][0] );
	      	glVertex3f(  esqueleto[i+1][0],  esqueleto[i+1][1], -grueso );
		glNormal3f( -normal[i][0], normal[i][1], 0.0 );
	      	glVertex3f( esqueleto[i][0]-grueso,  esqueleto[i][1], 0 );
		glNormal3f( -normal[i+1][0], normal[i+1][1], 0.0 );
	      	glVertex3f( esqueleto[i+1][0]-grueso,  esqueleto[i+1][1], 0 );
		glNormal3f( 0.0, normal[i][1], normal[i][0] );
 		glVertex3f(  esqueleto[i][0],  esqueleto[i][1], grueso );
		glNormal3f( 0.0, normal[i+1][1], normal[i+1][0] );
		glVertex3f(  esqueleto[i+1][0],  esqueleto[i+1][1], grueso  );
		glNormal3f( normal[i][0], normal[i][1], 0.0 );
	      	glVertex3f( esqueleto[i][0]+grueso,  esqueleto[i][1], 0 );
		glNormal3f( normal[i+1][0], normal[i+1][1], 0.0 );
	      	glVertex3f( esqueleto[i+1][0]+grueso,  esqueleto[i+1][1], 0 );
	glEnd();}
	}
	i=N-1;
	glBegin( GL_TRIANGLE_FAN );{
		glNormal3f( normal[i][0],  normal[i][1], 0.0 );
	    glVertex3f( esqueleto[i][0],  esqueleto[i][1], 0 );
		i=N-2;
		glNormal3f( normal[i][0], normal[i][1], 0 );
		glVertex3f( esqueleto[i][0]+grueso,  esqueleto[i][1], 0 );
		glNormal3f( 0.0, normal[i][1], -normal[i][0] );
		glVertex3f(  esqueleto[i][0],  esqueleto[i][1], -grueso );
		glNormal3f( -normal[i][0], normal[i][1], 0.0 );
	    glVertex3f( esqueleto[i][0]-grueso,  esqueleto[i][1], 0 );
		glNormal3f( 0.0, normal[i][1], normal[i][0] );
 		glVertex3f(  esqueleto[i][0],  esqueleto[i][1], grueso );
		glNormal3f( normal[i][0], normal[i][1], 0.0 );
	    glVertex3f( esqueleto[i][0]+grueso,  esqueleto[i][1], 0 );
	glEnd();}

glPopMatrix();
glShadeModel(GL_FLAT);
}
