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

    void activar(GLenum luz_ind);
    void desactivar(GLenum luz_ind);

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

  bool cuboAct;
  bool ply;
  bool tablero;

  _vertex4f ambiente_difusa;     //coeficientes ambiente y difuso
  _vertex4f especular;           //coeficiente especular
  float brillo;                  //exponente del brillo

  // Atributos para texturas
  vector<_vertex2f> textura_coord;
  bool modo_text;

  // Atributos para selección
  // float color[3], colorSeleccion[3];
  // bool seleccionado;

  // void seleccionar();
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

//*********************************************************************
// clase textura sin revolucion
//*********************************************************************

class _textura2 {
  protected:

    GLuint textura_id;
    std::vector<unsigned char> data;
    CImg<unsigned char> logo;

  public:
    _textura2();
    void tablero_textura(float tam, int n, int m);
    int n;
    int m;

};

//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D{
  public:

    _cubo(float tam=0.5);
};


//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D{
  public:
    _objeto_ply();

  int parametros(char *archivo);
};

//************************************************************************
// objeto por revoluci�n
//************************************************************************

class _rotacion: public _triangulos3D{
  public:
        _rotacion();
  void  parametros(vector<_vertex3f> perfil1, int num1);

  vector<_vertex3f> perfil;
  int num;
};

//************************************************************************
// objeto por cilindro
//************************************************************************

class _cilindro: public _triangulos3D{
  public:
    _cilindro(float radio, float altura, int lados);
    void rotacion(vector<_vertex3f> perfil, int num);
};

//************************************************************************
// objeto por esfera
//************************************************************************

class _esfera: public _triangulos3D {
  public:
        _esfera(float radio, float latitud, int longitud);
        void rotacion(vector<_vertex3f> perfil, int num);
        void material1();
        void material2();
};

//**************************************************************************
// estructuras de datos para los modelos
//**************************************************************************

struct vertices{
  float coord[3];
};

struct caras{
  int ind_c[3];
};

struct solido{
  int n_v;
  int n_c;
  vertices *ver;
  caras    *car;
  float r;
  float g;
  float b;
};


void construir_cubo(float tam, solido *cubo);
void construir_piramide(float tam, float al, solido *piramide);

void draw_puntos(vertices *ver, int n_v);
void draw_solido(solido *malla, float r, float g, float b, int modo);
void draw_solido_ajedrez(solido *malla, float r1, float g1, float b1, float r2, float g2, float b2);