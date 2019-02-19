#include "objetos.h"
#include "estructuras.h"
#include "math.h"
#include "iostream"

#define azul 0
#define gris 1
#define verde 2
#define	marron 3
#define celeste 4
#define violeta 5
#define rojo 6
#define amarillo 7

using namespace std;

/** Definicion de los colores usados.**/
float color[8][3]={{0.4,0.7,1},{0.7,0.7,0.7},{0.4,0.8,0},
   		   {0.7,0.6,0.2},{0.2,1.0,1.0},{0.5,0,0.8},
		   {0.9,0,0.1}, {1,0.9,0.1}};


_iluminacion::_iluminacion(){}

void _iluminacion::activar(){
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  cout << "Ilumiación activa" << endl;
}

void _iluminacion::desactivar(){
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);
  cout << "Ilumiación desactivada" << endl;
}

void _iluminacion::activarLuzEspecifica(int i){
  if(i==0)
    glEnable(GL_LIGHT0);
  else if(i==1)
    glEnable(GL_LIGHT1);
}


//*************************************************************************
// _object3D
//*************************************************************************
//*************************************************************************
//
//*************************************************************************

_object3D::_object3D()
{
Point_size=POINT_SIZE;
Line_width=LINE_WIDTH;
}

//*************************************************************************
//
//*************************************************************************

void _object3D::draw()
{

}


//*************************************************************************
// Robot
//*************************************************************************
//*************************************************************************
//
//*************************************************************************

robot::robot()
{
	rdefault();
}

//*************************************************************************
//
//*************************************************************************

void robot::draw()
{
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

glPushMatrix();
	glScalef(2,2,2);

	/* 				BLOQUE CABEZA = CABEZA + OJOS + OJOSL 				*/

glPushMatrix();
glRotatef(giro_cabeza,0,1,0);

	//Cabeza
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[gris]);
	glTranslatef(0,6.2+rcuello,0);
	esfera(1.2,15,20);
	glPopMatrix();

  // Antena izquierda
  glPushMatrix();
  glTranslatef(-1.45,6.2+rcuello,0);

  glRotatef(antenai_atr,1,0,0);
  glRotatef(antenai_del,-1,0,0);

  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[rojo]);
  caja(0.5,1.5,0.5);
  glPopMatrix();

  // Antena derecha
  glPushMatrix();
  glTranslatef(1.45,6.2+rcuello,0);

  glRotatef(antenad_atr,1,0,0);
  glRotatef(antenad_del,-1,0,0);

  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[violeta]);
  caja(0.5,1.5,0.5);
  glPopMatrix();

	// Ojo izquierdo
	glPushMatrix();
	glTranslatef(-0.5,6.5+rcuello,1.12);
	glScalef(2,2,1.5);
	glRotatef(-90,1,0,0);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[rojo]);
	conof(0,0,0,0,.25,0,.1,10);
	glPopMatrix();

  // Ojo derecho
	glPushMatrix();
	glTranslatef(0.5,6.5+rcuello,1.12);
	glScalef(2,2,1.5);
	glRotatef(-90,1,0,0);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[violeta]);
	conof(0,0,0,0,.25,0,.1,10);
	glPopMatrix();

  // Nariz
  glPushMatrix();
  glTranslatef(0,6+rcuello,1.12);
  glScalef(2,2,3);
  glRotatef(-270,1,0,0);
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[amarillo]);
  conof(0,0,0,0,.25,0,.1,10);
  glPopMatrix();

  // Boca
  glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[amarillo]);
	glTranslatef(0,5.5+rcuello,1.10);
	elipse(0,-0.1,0.5,0.2,20);
	glPopMatrix();

glPopMatrix();

/* -------------------------------------------------------------------- */

	//Cuello
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[gris]);
	glTranslatef(0,5,0);
	caja(1,rcuello,1);
	glPopMatrix();

  /* -------------------------------------------------------------------- */

  //Articulación pierna derecha
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[gris]);
	glTranslatef(1,-0.5,0);
	caja(0.5,rcuello,1);
	glPopMatrix();

glPushMatrix();

  glRotatef(girod_pierna_d,1,0,0);
  glRotatef(girod_pierna_a,1,0,0);
	//Pierna derecha
	glPushMatrix();
	glTranslatef(1,-3.5,0);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[violeta]);
	caja(1,3,1);
	glPopMatrix();

	//Pié derecho
	glPushMatrix();
	glTranslatef(1,-3.5,0.4);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[gris]);
	caja(1.2,0.5,2.2);
	glPopMatrix();

glPopMatrix();

  //Articulación pierna izquierda
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[gris]);
  glTranslatef(-1,-0.5,0);
  caja(0.5,rcuello,1);
  glPopMatrix();

glPushMatrix();

  glRotatef(giroi_pierna_d,1,0,0);
  glRotatef(giroi_pierna_a,1,0,0);

	//Pierna izquierda
	glPushMatrix();
	glTranslatef(-1,-3.5,0);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[rojo]);
	caja(1,3,1);
	glPopMatrix();

	//Pié izquierdo
	glPushMatrix();
	glTranslatef(-1,-3.5,0.4);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[gris]);
	caja(1.2,0.5,2.2);
	glPopMatrix();

glPopMatrix();

/* -------------------------------------------------------------------- */

glPushMatrix();

  glRotatef(giro_cinturai,0,1,0);
  glRotatef(giro_cinturad,0,1,0);
  // Cuerpo
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[amarillo]);
  cilindro(1.5,5);
  glPopMatrix();

  /* 				PARTE DEL BRAZO QUE VA A SER ROTAR  				*/

	// Brazo derecho
	glPushMatrix();
	glTranslatef(1.5,3.5,0);
	glRotatef(-90,0,0,1);
	/* 				TRANSLACIÓN NECESARIA PARA EL CORRECTO GIRO			 */
	glTranslatef(-0.5,0,0);
	glRotatef(giro_brazod,0,-1,0);
	glTranslatef(0.5,0,0);

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[violeta]);
	caja(3,0.7,1);

  // Mano derecha
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[gris]);
  glTranslatef(1.7,0.15,0);
  caja(0.4,0.4,0.4);
  glPopMatrix();
	glPopMatrix();

	// Brazo izquierdo
	glPushMatrix();
	glTranslatef(-1.5,3.5,0);
	glRotatef(90,0,0,1);
	/* 				TRANSLACIÓN NECESARIA PARA EL CORRECTO GIRO			 */
	glTranslatef(0.5,0,0);
	glRotatef(giro_brazoi,0,1,0);
	glTranslatef(-0.5,0,0);
	/* -----------------------------------------------*/
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[rojo]);
	caja(3,0.7,1);

  // Mano izquierda
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[gris]);
  glTranslatef(-1.7,0.15,0);
  caja(0.4,0.4,0.4);
  glPopMatrix();
	glPopMatrix();
glPopMatrix();

glPopMatrix();
}

//*************************************************************************

void robot::cabeza_dcha()
{
	giro_cabeza-=1;
}

//*************************************************************************

void robot::cabeza_izq()
{
	giro_cabeza+=1;
}

//*************************************************************************

void robot::antenas_delante()
{
  antenai_del+=2;
  antenad_del+=2;
}

//*************************************************************************

void robot::antenas_atras()
{
  antenai_atr+=2;
  antenad_atr+=2;
}

//*************************************************************************

void robot::brazos_arriba()
{
	giro_brazod+=2;
	giro_brazoi+=2;
}

//*************************************************************************

void robot::brazos_abajo()
{
	giro_brazod-=2;
	giro_brazoi-=2;
}

//*************************************************************************

void robot::brazod_abajo()
{
	giro_brazod-=2;
}

//*************************************************************************

void robot::brazod_arriba()
{
	giro_brazod+=2;
}

//*************************************************************************

void robot::brazoi_abajo()
{
	giro_brazoi-=2;
}

//*************************************************************************

void robot::brazoi_arriba()
{
	giro_brazoi+=2;
}


//*************************************************************************

void robot::giroi_cintura(){
  giro_cinturai+=0.5;
}

//*************************************************************************

void robot::girod_cintura(){
  giro_cinturad-=0.5;
}

//*************************************************************************

void robot::giro_piernai_d(){
  giroi_pierna_d-=2;
}

//*************************************************************************

void robot::giro_piernai_a(){
  giroi_pierna_a+=2;
}

//*************************************************************************

void robot::giro_piernad_d(){
  girod_pierna_d-=2;
}

//*************************************************************************

void robot::giro_piernad_a(){
  girod_pierna_a+=2;
}

//*************************************************************************

void robot::rdefault()
{
	giro_cabeza=0;
	giro_brazod=0;
	giro_brazoi=0;
  antenai_atr=antenad_atr=0;
  antenai_del=antenad_del=0;
	rcuello=0.5;
  giro_cinturai=0;
  giro_cinturad=0;
  giroi_pierna_d=0;
  giroi_pierna_a=0;
  girod_pierna_d=0;
  girod_pierna_a=0;
  giro_piernai_maxa=giro_piernad_maxa=50;
  giro_piernai_maxd=giro_piernad_maxd=-50;
}

//*************************************************************************
