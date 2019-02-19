#ifndef _OBJETOS
#define _OBJETOS


#include <stdlib.h>
#include <GL/glut.h>
#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>

using namespace std;


const float POINT_SIZE=3;
const float LINE_WIDTH=1;

class _iluminacion{
public:
  // _iluminacion(GLenum p_luz_ind, _vertex4f p_luz_punto, _vertex4f p_luz_ambiente,
  //       _vertex4f p_luz_difusa, _vertex4f p_luz_especular);
  _iluminacion();
  void activar();
  void desactivar();
  void activarLuzEspecifica(int i);

protected:
  GLenum p_luz_ind; //indice de la fuente de luz
  _vertex4f p_luz_punto; //posicion o vector de direccion de la luz
  _vertex4f p_luz_ambiente; //componente ambiental de la luz
  _vertex4f p_luz_difusa; //componente difusa de la luz
  _vertex4f p_luz_especular; //componente especular de la luz
};

//*************************************************************************
//
//*************************************************************************

class _object3D
{
public:

			_object3D();
void 	draw();

float Point_size;
float Line_width;
};


//*************************************************************************
// ROBOT
//*************************************************************************

class robot: public _object3D
{
public:
	robot();
  void draw();

	void cabeza_dcha();
	void cabeza_izq();
	void antenas_delante();
	void antenas_atras();
	void brazos_arriba();
	void brazos_abajo();
	void brazod_abajo();
	void brazod_arriba();
	void brazoi_abajo();
	void brazoi_arriba();
	void giroi_cintura();
	void girod_cintura();
	void giro_piernai_d();
	void giro_piernai_a();
	void giro_piernad_d();
	void giro_piernad_a();
	void rdefault();

    // Parámetros de construcción
	float giro_cabeza;
	float antenad_del, antenai_del, antenad_atr, antenai_atr;
	float giro_brazod, giro_brazoi;
	float rcuello, rmanod, rmanoi;
	float giro_cinturai, giro_cinturad;
	float giroi_pierna_d, giroi_pierna_a;
	float girod_pierna_d, girod_pierna_a;
	float giro_piernai_maxd, giro_piernai_maxa;
	float giro_piernad_maxd, giro_piernad_maxa;
};



#endif
