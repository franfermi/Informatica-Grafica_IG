//**************************************************************************
// Pr�ctica IG usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"
#include "CImg.h"

using namespace cimg_library;
using namespace std;

const float AXIS_SIZE=10000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID,SOLID_ILLUMINATED_FLAT,
             SOLID_ILLUMINATED_GOURAUD, TEXTURE, TEXTURE_ILLUMINATED_FLAT,
              TEXTURE_ILLUMINATED_GOURAUD} _modo;

//*************************************************************************
// clase iluminación
//*************************************************************************

class _iluminacion{
public:
  _iluminacion(GLenum p_luz_ind, _vertex4f p_luz_punto, _vertex4f p_luz_ambiente,
    _vertex4f p_luz_difusa, _vertex4f p_luz_especular);

  void activar();
  void desactivar();

  void transformar(GLenum p_luz_ind, float ang, float x, float y, float z);
  float alpha;
protected:
  GLenum luz_ind; //indice de la fuente de luz
  _vertex4f luz_punto; //posicion o vector de direccion de la luz
  _vertex4f luz_ambiente; //componente ambiental de la luz
  _vertex4f luz_difusa; //componente difusa de la luz
  _vertex4f luz_especular; //componente especular de la luz
};

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D{
  public:


  	_puntos3D();
  void 	draw_puntos(float r, float g, float b, int grosor);

  vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D{
  public:

  	_triangulos3D();
  void 	draw_aristas(float r, float g, float b, int grosor);
  void  draw_solido(float r, float g, float b);
  void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
  void 	draw_iluminacion_plana();
  void 	draw_iluminacion_suave();

  void draw_textura(GLuint ident_textura);
  void draw_textura_iluminacion_plana(GLuint ident_textura);
  void draw_textura_iluminacion_suave(GLuint ident_textura);

  void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

  // void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor
  //           GLuint ident_textura);

  void	calcular_normales_caras();
  void 	calcular_normales_vertices();

  void calcularCoordenadasTextura(int n, int m);

  vector<_vertex3i> caras;

  vector<_vertex3f> normales_caras;
  vector<_vertex3f> normales_vertices;

  bool b_normales_caras;
  bool b_normales_vertices;
  bool b_textura_coord;

  _vertex4f ambiente_difusa;     //coeficientes ambiente y difuso
  _vertex4f especular;           //coeficiente especular
  float brillo;                  //exponente del brillo

  // Atributos para texturas
  vector<_vertex2f> textura_coord;
  bool modo_text;
};

//*************************************************************************
// clase texturas
//*************************************************************************

class _texturas: public _triangulos3D{
  public:
    _texturas();
    //_texturas(char *imagenJPG);
    //_texturas(const char *imagenJPG);
    void inicializarTextura(const char *imagenJPG);
    void activarTextura();

    GLuint ident_textura; //Entero que asigna OpenGL a la texturas
    CImg<unsigned char> logo;
    unsigned char *datosImagen;
};

//*************************************************************************
// clase rotacion texturas
//*************************************************************************

class _texturas_rotacion: public _triangulos3D{
  public:
    _texturas_rotacion();
    _texturas_rotacion(vector<_vertex3f> v, int num_caras);
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int parametros(char *archivo);
};

//************************************************************************
// objeto por revoluci�n
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
void  parametros(vector<_vertex3f> perfil1, int num1);

vector<_vertex3f> perfil;
int num;
};

//************************************************************************
// objeto por cilindro
//************************************************************************

class _cilindro: public _triangulos3D
{
public:
       _cilindro(float radio, float altura, int lados);
       	void rotacion(vector<_vertex3f> perfil, int num);
};

//************************************************************************
// objeto por esfera
//************************************************************************

class _esfera: public _triangulos3D
{
public:
       _esfera(float radio, float latitud, int longitud);
       	void rotacion(vector<_vertex3f> perfil, int num);
};


//************************************************************************
// objeto articulado: tanque
//************************************************************************

class _chasis: public _triangulos3D
{
public:
       _chasis();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;

protected:
_rotacion  rodamiento;
_cubo  base;
};

//************************************************************************

class _torreta: public _triangulos3D
{
public:
       _torreta();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;
float anchura;

protected:
_cubo  base;
_piramide parte_trasera;
};

//************************************************************************

class _tubo: public _triangulos3D
{
public:
       _tubo();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_rotacion tubo_abierto; // ca�a del ca��n
};

//************************************************************************

class _tanque: public _triangulos3D
{
public:
       _tanque();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float giro_tubo;
float giro_torreta;

float giro_tubo_min;
float giro_tubo_max;

protected:
_chasis  chasis;
_torreta  torreta;
_tubo     tubo;
};
