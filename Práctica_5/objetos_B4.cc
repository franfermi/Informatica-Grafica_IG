//**************************************************************************
// Pr�ctica IG usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"
#include "objetos_B4.h"
#include <cmath>

//*************************************************************************
// clase iluminacion
//*************************************************************************

_iluminacion::_iluminacion(GLenum p_luz_ind, _vertex4f p_luz_punto, _vertex4f p_luz_ambiente,
      _vertex4f p_luz_difusa, _vertex4f p_luz_especular){
  luz_ind = p_luz_ind;
  luz_punto = p_luz_punto;
  luz_ambiente = p_luz_ambiente;
  luz_difusa = p_luz_difusa;
  luz_especular = p_luz_especular;
  alpha = 10;
}

void _iluminacion::activar(GLenum luz_ind){
  glEnable(GL_LIGHTING);
  glEnable(luz_ind);

  glLightfv (luz_ind, GL_AMBIENT, (GLfloat *)&luz_ambiente);
  glLightfv (luz_ind, GL_DIFFUSE, (GLfloat *)&luz_difusa);
  glLightfv (luz_ind, GL_SPECULAR, (GLfloat *)&luz_especular);
  glLightfv (luz_ind, GL_POSITION, (GLfloat *)&luz_punto);
}

void _iluminacion::desactivar(GLenum luz_ind){
  glDisable(luz_ind);
  glDisable(GL_LIGHTING);
}

void _iluminacion::transformar(GLenum p_luz_ind, float ang, float x, float y, float z){
  alpha = ang;
  alpha+=20;

  if (alpha > 360)
    alpha -= 360;
  if (alpha < -360)
    alpha += 360;

  glPushMatrix();
  glRotatef(alpha,0,1,0);
  glTranslatef(x,y,z);
  glLightfv(p_luz_ind, GL_POSITION, (GLfloat*)&luz_punto);
  glPopMatrix();
}

//*************************************************************************
// clase textura
//*************************************************************************

_texturas::_texturas(){}

void _texturas::inicializarTextura(const char *archivoJPG){
  glGenTextures(1, &ident_textura);

  std::vector<unsigned char> data;
  cout << "Leyendo imagen para textura " << archivoJPG << flush << endl;
  logo.load(archivoJPG);

  for(long y=0; y<logo.height(); y++)
    for(long x=0; x<logo.width(); x++){
      unsigned char *r = logo.data(x, y, 0, 0);
      unsigned char *g = logo.data(x, y, 0, 1);
      unsigned char *b = logo.data(x, y, 0, 2);
      data.push_back(*r);
      data.push_back(*g);
      data.push_back(*b);
    }


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);


    glBindTexture(GL_TEXTURE_2D, ident_textura); //Activa la textura
    gluBuild2DMipmaps(GL_TEXTURE_2D,
                  GL_RGB,
                  logo.width(),
                  logo.height(),
                  GL_RGB,
                  GL_UNSIGNED_BYTE,
                  &data[0]);

    assert(glGetError() == GL_NO_ERROR);

    cout << "(" << logo.width() << "x" << logo.height() << ")" << endl << flush;
}

void _texturas::activarTextura(){
  glBindTexture(GL_TEXTURE_2D, ident_textura); //Activa la textura
}

//*************************************************************************
// clase textura objetos sin revolución
//*************************************************************************

_textura2::_textura2() {

   logo.load("./caja.jpg");

    // empaquetamos bien los datos
    for (long y = 0; y < logo.height(); y ++)
        for (long x = 0; x < logo.width(); x ++)
        {
          unsigned char *r = logo.data(x, y, 0, 0);
          unsigned char *g = logo.data(x, y, 0, 1);
          unsigned char *b = logo.data(x, y, 0, 2);
          data.push_back(*r);
          data.push_back(*g);
          data.push_back(*b);
        }

    glGenTextures(1, &textura_id);
}

void _textura2::tablero_textura(float tam, int n, int m){

    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textura_id);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, logo.width(), logo.height(),
        0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);

    glColor3f(1,1,1);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glPushMatrix();



    for(int i=0; i<n; ++i)
    {

        for(int j=0; j<m; ++j)
        {

            //glBegin(GL_QUADS);

            // // cara izquierda (1)
            // //1
            // glTexCoord2d(0.0,0.25);
            // glVertex3f(0.0,1.0,0.0);
            // //2
            // glTexCoord2d(0.0,0.5);
            // glVertex3f(0.0,0.0,0.0);

            // //3
            // glTexCoord2d(0.25,0.5);
            // glVertex3f(0.0,0.0,1.0);

            // //4
            // glTexCoord2d(0.25,0.25);
            // glVertex3f(0.0,1.0,1.0);

            // glEnd();

            // glBegin(GL_QUADS);
            // // cara delantera (2)
            // //4
            // glTexCoord2d(0.25,0.25);
            // glVertex3f(0.0,1.0,1.0);

            // //3
            // glTexCoord2d(0.25,0.5);
            // glVertex3f(0.0,0.0,1.0);


            // //6
            // glTexCoord2d(0.5,0.5);
            // glVertex3f(1.0,0.0,1.0);

            // //5
            // glTexCoord2d(0.5,0.25);
            // glVertex3f(1.0,1.0,1.0);
            // glEnd();
            // glBegin(GL_QUADS);
            // // cara derecha (5)
            // //5
            // glTexCoord2d(0.5,0.25);
            // glVertex3f(1.0,1.0,1.0);

            // //6
            // glTexCoord2d(0.5,0.5);
            // glVertex3f(1.0,0.0,1.0);


            // //8
            // glTexCoord2d(0.75,0.5);
            // glVertex3f(1.0,0.0,0.0);

            // //7
            // glTexCoord2d(0.75,0.25);
            // glVertex3f(1.0,1.0,0.0);
            // glEnd();
            // glBegin(GL_QUADS);

            // // cara trasera (6)


            // //7
            // glTexCoord2d(0.75,0.25);
            // glVertex3f(1.0,1.0,0.0);

            // //8
            // glTexCoord2d(0.75,0.5);
            // glVertex3f(1.0,0.0,0.0);

            // //9 -> (2)
            // glTexCoord2d(1.0,0.5);
            // glVertex3f(0.0,0.0,0.0);

            // //10 -> (1)
            // glTexCoord2d(1.0,0.25);
            // glVertex3f(0.0,1.0,0.0);



            // glEnd();
            // glBegin(GL_QUADS);
            // // cara arriba (3)


            // //4
            // glTexCoord2d(0.25,0.25);
            // glVertex3f(0.0,1.0,1.0);

            // //5
            // glTexCoord2d(0.5,0.25);
            // glVertex3f(1.0,1.0,1.0);


            // //12
            // glTexCoord2d(0.5,0.0);
            // glVertex3f(1.0,1.0,0.0);

            // //11
            // glTexCoord2d(0.25,0.0);
            // glVertex3f(0.0,1.0,0.0);
            // glBegin(GL_QUADS);

            // // cara abajo (4)


            // //3
            // glTexCoord2d(0.25,0.5);
            // glVertex3f(0.0,0.0,1.0);
            // //11
            // glTexCoord2d(0.25,0.75);
            // glVertex3f(0.0,0.0,0.0);

            // //12
            // glTexCoord2d(0.5,0.75);
            // glVertex3f(1.0,0.0,0.0);

            // //6
            // glTexCoord2d(0.5,0.5);
            // glVertex3f(1.0,0.0,1.0);

            // glEnd();

					/***********************************************************/

						glBegin(GL_TRIANGLES);
						//cara frontal (1)
            //1
            glTexCoord2d(0.0,1.0);
            glVertex3f(-1.0,0.0,1.0);
            //2
            glTexCoord2d(1.0,1.0);
            glVertex3f(1.0,0.0,1.0);

            //3
            glTexCoord2d(0.5,0.0);
            glVertex3f(0.0,1.0,0.0);
						glEnd();

						glBegin(GL_TRIANGLES);
						//cara izquierda (2)
            //1
            glTexCoord2d(0.0,1.0);
            glVertex3f(-1.0,0.0,-1.0);
            //2
            glTexCoord2d(1.0,1.0);
            glVertex3f(-1.0,0.0,1.0);

            //3
            glTexCoord2d(0.5,0.0);
            glVertex3f(0.0,1.0,0.0);
						glEnd();

						glBegin(GL_TRIANGLES);
						//cara derecha (3)
            //1
            glTexCoord2d(0.0,1.0);
            glVertex3f(1.0,0.0,1.0);
            //2
            glTexCoord2d(1.0,1.0);
            glVertex3f(1.0,0.0,-1.0);

            //3
            glTexCoord2d(0.5,0.0);
            glVertex3f(0.0,1.0,0.0);
						glEnd();

						glBegin(GL_TRIANGLES);
						//cara trasera (4)
            //1
            glTexCoord2d(0.0,1.0);
            glVertex3f(-1.0,0.0,-1.0);
            //2
            glTexCoord2d(1.0,1.0);
            glVertex3f(1.0,0.0,-1.0);

            //3
            glTexCoord2d(0.5,0.0);
            glVertex3f(0.0,1.0,0.0);
						glEnd();

						glBegin(GL_QUADS);
						//cara abajo (5)
            //1
            glTexCoord2d(0.0,1.0);
            glVertex3f(-1.0,0.0,1.0);
            //2
            glTexCoord2d(1.0,1.0);
            glVertex3f(1.0,0.0,1.0);

            //3
            glTexCoord2d(1.0,0.0);
            glVertex3f(1.0,0.0,-1.0);

						//4
            glTexCoord2d(0.0,0.0);
            glVertex3f(-1.0,0.0,-1.0);
						glEnd();


        }
    }
	glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

}

//*************************************************************************
// clase punto
//*************************************************************************

_puntos3D::_puntos3D(){}

void _puntos3D::draw_puntos(float r, float g, float b, int grosor){
  glPointSize(grosor);
  glColor3f(r,g,b);
  glBegin(GL_POINTS);

  for(int i=0; i<vertices.size(); i++)
    glVertex3fv((GLfloat*)&vertices[i]);

  glEnd();
}

//*************************************************************************
// clase triángulo
//*************************************************************************

_triangulos3D::_triangulos3D(){
  b_normales_caras = false;
  b_normales_vertices = false;
  b_textura_coord = false;
  modo_text = false;
  cuboAct = false;
  ply = false;
}

// dibujar en modo arista

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor){
  unsigned int i;
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glLineWidth(grosor);
  glColor3f(r,g,b);
  glBegin(GL_TRIANGLES);
  for (i=0;i<caras.size();i++){
  	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
  	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
  	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  	}
  glEnd();
}

// dibujar en modo sólido

void _triangulos3D::draw_solido(float r, float g, float b){
  unsigned int i;
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glColor3f(r,g,b);
  glBegin(GL_TRIANGLES);
  for (i=0;i<caras.size();i++){
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }
  glEnd();
}

// dibujar en modo sólido con apariencia de ajedrez

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2){
  unsigned int i;
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glBegin(GL_TRIANGLES);
  for (i=0;i<caras.size();i++){
    if(i%2==0)
      glColor3f(r1,g1,b1);
    else
      glColor3f(r2,g2,b2);
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }
  glEnd();
}

// dibujar con distintos modos

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	switch (modo){
		case POINTS:draw_puntos(r1, g1, b1, grosor);break;
		case EDGES:draw_aristas(r1, g1, b1, grosor);break;
		case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
		case SOLID:draw_solido(r1, g1, b1);break;
		case SOLID_ILLUMINATED_FLAT:draw_iluminacion_plana();break;
		case SOLID_ILLUMINATED_GOURAUD:draw_iluminacion_suave();break;
		}
}

// iluminación plana

void _triangulos3D::draw_iluminacion_plana(){
  	GLfloat ambient_component[4] = {1,1,1,1};

  	if(b_normales_caras == false)
  		calcular_normales_caras();

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    glShadeModel(GL_FLAT);
    glEnable(GL_NORMALIZE); 

    // glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_TEXTURE_2D);

    _vertex4f ambiente = _vertex4f(0.0,0.07,0.1,1.0);
    _vertex4f difusa = _vertex4f(0.0,0.6,0.8,1.0);
    _vertex4f especular = _vertex4f(0.9,0.9,0.9,1.0);

    // _vertex4f ambiente2 = _vertex4f(0.2,0.2,0.2,1.0);
    // _vertex4f difusa2 = _vertex4f(0.8,0.8,0.8,1.0);
    // _vertex4f especular2 = _vertex4f(0.0,0.0,0.0,1.0);

		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&difusa);
  	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&ambiente);
  	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);

    float brillo = 100;
  	// Atributos de la luz
  	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo);

  	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  	glBegin(GL_TRIANGLES);

    	GLfloat oro[4]={0.6,0.7,0.2,1.0};
			GLfloat rojo[4]={1.0,0.0,0.0,1.0};
			GLfloat noespecular[4]={0.0,0.0,0.0,1.0};

			float max_x, min_x, max_y, min_y;
			max_x=min_x=vertices[0].x;
			max_y=min_y=vertices[0].y;

    // glColor3f(0.5,0.5,0.5);

  	for(int i=0; i<caras.size(); ++i){

			
			oro[0]=0.6-(0.6-1.0)*(max_x-vertices[caras[i]._0].x) / (max_x-min_y);
			oro[1]=0.7-(0.7-0.1)*(max_x-vertices[caras[i]._1].x) / (max_x-min_y);
			oro[2]=0.2-(0.2-0.1)*(max_x-vertices[caras[i]._2].x) / (max_x-min_y);

      if(vertices[caras[i]._1].x>0.0){
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&oro);
  	    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&oro);
  	    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&noespecular);
      }else{
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&rojo);
  	    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&rojo);
  	    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
      }

			glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&oro);
  	  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&oro);
			
    	glNormal3fv((GLfloat *) &normales_vertices[caras[i]._0]);
      if((!cuboAct) && (!ply) && (!tablero))
        glTexCoord2f(textura_coord[caras[i]._0].s, textura_coord[caras[i]._0].t);
    	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);

    	glNormal3fv((GLfloat *) &normales_vertices[caras[i]._1]);
      if((!cuboAct) && (!ply) && (!tablero))
        glTexCoord2f(textura_coord[caras[i]._1].s, textura_coord[caras[i]._1].t);
    	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);

    	glNormal3fv((GLfloat *) &normales_vertices[caras[i]._2]);
      if((!cuboAct) && (!ply) && (!tablero)) 
        glTexCoord2f(textura_coord[caras[i]._2].s, textura_coord[caras[i]._2].t);
    	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  	}

  	glEnd();

    // glDisable(GL_COLOR_MATERIAL);

    glDisable(GL_TEXTURE_2D);
}

// iluminación suave

void _triangulos3D::draw_iluminacion_suave(){
	GLfloat ambient_component[4] = {1,1,1,1};

	GLfloat oro[4]={0.6,0.7,0.2,1.0};
	GLfloat rojo[4]={1.0,0.0,0.0,1.0};
	GLfloat noespecular[4]={0.0,0.0,0.0,1.0};

	float max_x, min_x, max_y, min_y;
	max_x=min_x=vertices[0].x;
	max_y=min_y=vertices[0].y;

	for(int i=0; i<vertices.size(); i++){
		if(vertices[i].x > max_x) max_x = vertices[i].x;
		if(vertices[i].x < min_x) min_x = vertices[i].x;
		if(vertices[i].y > max_y) max_y = vertices[i].y;
		if(vertices[i].x < min_y) min_y = vertices[i].y;
	}

  	if(b_normales_vertices == false)
  		calcular_normales_vertices();

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
  	glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    //Hay que añadir que si tenemos textura, se ponga la componente en blanco (en difusa y ambiente)
    // glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_TEXTURE_2D);

    _vertex4f ambiente = _vertex4f(0.0,0.07,0.1,1.0);
    _vertex4f difusa = _vertex4f(0.0,0.6,0.8,1.0);
    _vertex4f especular = _vertex4f(0.9,0.9,0.9,1.0);

    // _vertex4f ambiente2 = _vertex4f(0.2,0.2,0.2,1.0);
    // _vertex4f difusa2 = _vertex4f(0.8,0.8,0.8,1.0);
    // _vertex4f especular2 = _vertex4f(0.0,0.0,0.0,1.0);

		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&difusa);
  	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&ambiente);
  	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
    float brillo = 100;
  	// Atributos de la luz
  	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo);

  	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  	glBegin(GL_TRIANGLES);

    // glColor3f(0.5,0.5,0.5);
  	for(int i=0; i<caras.size(); ++i){

			oro[0]=0.6-(0.6-1.0)*(max_x-vertices[caras[i]._0].x) / (max_x-min_y);
			oro[1]=0.7-(0.7-0.1)*(max_x-vertices[caras[i]._1].x) / (max_x-min_y);
			oro[2]=0.2-(0.2-0.1)*(max_x-vertices[caras[i]._2].x) / (max_x-min_y);

      if(vertices[caras[i]._1].x>0.0){
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&oro);
  	    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&oro);
  	    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&noespecular);
      }else{
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&rojo);
  	    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&rojo);
  	    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
      }

			glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&oro);
  	  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&oro);

    	glNormal3fv((GLfloat *) &normales_vertices[caras[i]._0]);
      if((!cuboAct) && (!ply) && (!tablero))
        glTexCoord2f(textura_coord[caras[i]._0].s, textura_coord[caras[i]._0].t);
    	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);

    	glNormal3fv((GLfloat *) &normales_vertices[caras[i]._1]);
      if((!cuboAct) && (!ply) && (!tablero))
        glTexCoord2f(textura_coord[caras[i]._1].s, textura_coord[caras[i]._1].t);
    	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);

    	glNormal3fv((GLfloat *) &normales_vertices[caras[i]._2]);
      if((!cuboAct) && (!ply) && (!tablero)) 
        glTexCoord2f(textura_coord[caras[i]._2].s, textura_coord[caras[i]._2].t);
    	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  	}

  	glEnd();

    // glDisable(GL_COLOR_MATERIAL);

    glDisable(GL_TEXTURE_2D);
}

// Calcular las normales de la cara

void _triangulos3D::calcular_normales_caras() {
	normales_caras.resize(caras.size());

	for(unsigned long i=0; i<caras.size(); i++){
		// obtener dos vectores en el triángulo y calcular el producto vectorial
    	_vertex3f
        	a1 = vertices[caras[i]._1]-vertices[caras[i]._0],
        	a2 = vertices[caras[i]._2]-vertices[caras[i]._0],
        	n = a1.cross_product(a2);

    	// modulo
    	float m = sqrt(n.x*n.x+n.y*n.y+n.z*n.z);

    	// normalización
    	normales_caras[i] = _vertex3f(n.x/m,n.y/m,n.z/m);
  	}

  	b_normales_caras = true;
}

// Calcular las normales de los vertices

void _triangulos3D::calcular_normales_vertices(){
 	if(b_normales_vertices == false) {
 		// Si no hemos calculado las normales de las caras hay que hacerlo
    	if(b_normales_caras == false)
    		calcular_normales_caras();

     	normales_vertices.resize(vertices.size());

     	for(int i=0; i<vertices.size(); i++){
       	normales_vertices[i].x = 0.0;
       	normales_vertices[i].y = 0.0;
    		normales_vertices[i].z = 0.0;
     	}

     	for(int i=0; i<caras.size(); ++i){
       	// se suma la normal de la cara a las normales de los tres vértices de la cara.
       	normales_vertices[caras[i]._0]+=normales_caras[i];
       	normales_vertices[caras[i]._1]+=normales_caras[i];
       	normales_vertices[caras[i]._2]+=normales_caras[i];
     	}

     	// Normalización
     	for(int i=0; i<vertices.size(); i++){
       	normales_vertices[i].normalize();
     	}

     	// ponemos a true que hemos calculado las normales de los vértices
     	b_normales_vertices = true;
   }
}

// Calcular las coordenadas de las texturas

void _triangulos3D::calcularCoordenadasTextura(int n, int m){
  textura_coord = vector<_vertex2f>(vertices.size());

  unsigned int k = 0;
  vector<float> d(m, 0);

  for(unsigned int j = 1; j < m; j++)
    d[j] = d[j-1] + (vertices[j] - vertices[j-1]).module();

  for(unsigned int i = 0; i <n; i++){
    _vertex2f punto;
    punto.x = (float)i / (n-1);
    for(unsigned int j = 0; j < m; j++){
      punto.y = d[j] / d.back();
      textura_coord[k] = punto;
      k++;
    }
  }
}

// Método de selección por color

// void _triangulos3D::seleccionar(){
//   seleccionado =! seleccionado;
// }

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam){
  //vertices
  vertices.resize(8);
  vertices[0].x=-tam;vertices[0].y=-tam;vertices[0].z=tam;
  vertices[1].x=tam;vertices[1].y=-tam;vertices[1].z=tam;
  vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=tam;
  vertices[3].x=-tam;vertices[3].y=tam;vertices[3].z=tam;
  vertices[4].x=-tam;vertices[4].y=-tam;vertices[4].z=-tam;
  vertices[5].x=tam;vertices[5].y=-tam;vertices[5].z=-tam;
  vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;
  vertices[7].x=-tam;vertices[7].y=tam;vertices[7].z=-tam;

  // triangulos
  caras.resize(12);
  caras[0]._0=0;caras[0]._1=1;caras[0]._2=3;
  caras[1]._0=3;caras[1]._1=1;caras[1]._2=2;
  caras[2]._0=1;caras[2]._1=5;caras[2]._2=2;
  caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;
  caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;
  caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;
  caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;
  caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
  caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;
  caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;
  caras[10]._0=0;caras[10]._1=1;caras[10]._2=4;
  caras[11]._0=1;caras[11]._1=5;caras[11]._2=4;

  cuboAct = true;

  calcular_normales_vertices();
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply(){
   // leer lista de coordenadas de vértices y lista de indices de vértices

}

int _objeto_ply::parametros(char *archivo){
  int n_ver,n_car;

  vector<float> ver_ply ;
  vector<int>   car_ply ;

  _file_ply::read(archivo, ver_ply, car_ply );

  n_ver=ver_ply.size()/3;
  n_car=car_ply.size()/3;

  ply = true;

  printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

  //if (n_ver<3 || n_car<1){
  //	printf("Error %d %d\n",__FILE__,__LINE__);
  //	exit(-1);
  //	}

  vertices.resize(n_ver);
  caras.resize(n_car);

  _vertex3f ver_aux;
  _vertex3i car_aux;

  // calcularCoordenadasTextura(n_ver, n_car);

  for (int i=0;i<n_ver;i++)
  	{ver_aux.x=ver_ply[i*3];
  	 ver_aux.y=ver_ply[i*3+1];
  	 ver_aux.z=ver_ply[i*3+2];
  	 vertices[i]=ver_aux;
  	}

  for (int i=0;i<n_car;i++)
  	{car_aux.x=car_ply[i*3];
  	 car_aux.y=car_ply[i*3+1];
  	 car_aux.z=car_ply[i*3+2];
  	 caras[i]=car_aux;
  	}

  
  calcular_normales_vertices();
  return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion(){
  num=0;
}


void _rotacion::parametros(vector<_vertex3f> perfil, int num){
	int i,j;
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	int num_aux;

	// tratamiento de los vértice

	num_aux=perfil.size();
	vertices.resize(num_aux*num);
	for (j=0;j<num;j++)
	  {for (i=0;i<num_aux;i++)
	     {
	      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
		            perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
	      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
		            perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
	      vertice_aux.y=perfil[i].y;
	      vertices[i+j*num_aux]=vertice_aux;
	     }
	  }

	// tratamiento de las caras

	for (j=0;j<num;j++)
	  {for (i=0;i<num_aux-1;i++)
	     {cara_aux._0=i+((j+1)%num)*num_aux;
	      cara_aux._1=i+1+((j+1)%num)*num_aux;
	      cara_aux._2=i+1+j*num_aux;
	      caras.push_back(cara_aux);

	      cara_aux._0=i+1+j*num_aux;
	      cara_aux._1=i+j*num_aux;
	      cara_aux._2=i+((j+1)%num)*num_aux;
	      caras.push_back(cara_aux);
	     }
	  }

  calcularCoordenadasTextura(num, num_aux); 

	// tapa inferior
	if (fabs(perfil[0].x)>0.0)
	{
		vertice_aux.x=0.0;
	    vertice_aux.y=perfil[0].y;
	    vertice_aux.z=0.0;

	    vertices.push_back(vertice_aux);

	    cara_aux._0=num_aux*num;
	    for (int i = 0; i < num; i++)
	    {
	      cara_aux._1=((i+1)%num)*num_aux;
	      cara_aux._2=i*num_aux;
	      caras.push_back(cara_aux);
	    }
	}
	 
	// tapa superior
	if (fabs(perfil[num_aux-1].x)>0.0)
	{
		vertice_aux.x=0.0;
		vertice_aux.y=perfil[num_aux-1].y;
		vertice_aux.z=0.0;

		vertices.push_back(vertice_aux);

		cara_aux._0=num_aux*num;
		for (int i = 0; i < num; i++)
		{
		  cara_aux._1=((i+1)%num)*num_aux+1;
		  cara_aux._2=i*num_aux+1;
		  caras.push_back(cara_aux);
		}
	}

  calcular_normales_vertices();
}

//*************************************************************************
// clase cilindro
//*************************************************************************
_cilindro::_cilindro(float radio, float altura, int lados){
    vertices.resize(2);

    vertices[0] = _vertex3f(radio,-altura/2,0);
    vertices[1] = _vertex3f(radio,altura/2,0);

    rotacion(vertices, lados);
}

void _cilindro::rotacion(vector<_vertex3f> perfil, int num){
 	int i,j;
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	int num_aux;

	// tratamiento de los vértice

	num_aux=perfil.size();
	vertices.resize(num_aux*num);
	for (j=0;j<num;j++)
	  {for (i=0;i<num_aux;i++)
	     {
	      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
		            perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
	      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
		            perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
	      vertice_aux.y=perfil[i].y;
	      vertices[i+j*num_aux]=vertice_aux;
	     }
	  }

	// tratamiento de las caras

	for (j=0;j<num;j++)
	  {for (i=0;i<num_aux-1;i++)
	     {cara_aux._0=i+((j+1)%num)*num_aux;
	      cara_aux._1=i+1+((j+1)%num)*num_aux;
	      cara_aux._2=i+1+j*num_aux;
	      caras.push_back(cara_aux);

	      cara_aux._0=i+1+j*num_aux;
	      cara_aux._1=i+j*num_aux;
	      cara_aux._2=i+((j+1)%num)*num_aux;
	      caras.push_back(cara_aux);
	     }
	  }

  calcularCoordenadasTextura(num, num_aux); 

	// tapa inferior
	if (fabs(perfil[0].x)>0.0)
	{
		vertice_aux.x=0.0;
	    vertice_aux.y=perfil[0].y;
	    vertice_aux.z=0.0;

	    vertices.push_back(vertice_aux);

	    cara_aux._0=num_aux*num;
	    for (int i = 0; i < num; i++)
	    {
	      cara_aux._1=((i+1)%num)*num_aux;
	      cara_aux._2=i*num_aux;
	      caras.push_back(cara_aux);
	    }
	}
	 
	// tapa superior
	if (fabs(perfil[num_aux-1].x)>0.0)
	{
		vertice_aux.x=0.0;
		vertice_aux.y=perfil[num_aux-1].y;
		vertice_aux.z=0.0;

		vertices.push_back(vertice_aux);

		cara_aux._0=num_aux*num+1;
		for (int i = 0; i < num; i++)
		{
		  cara_aux._1 = (i + 1) * num_aux+1;
      cara_aux._2 = ((i + 1) % num) * num_aux + num_aux+1;
		  caras.push_back(cara_aux);
		}
	}

  calcular_normales_vertices();
}

//*************************************************************************
// clase esfera
//*************************************************************************

_esfera::_esfera(float radio, float latitud, int longitud){
	vertices.resize(longitud-1);

    for (int i=1; i<longitud; ++i){
        vertices[i-1] = _vertex3f(radio*cos(-M_PI/2.0+M_PI/longitud*i), radio*sin(-M_PI/2.0+M_PI/longitud*i), 0);
    }
    rotacion(vertices, longitud);
}

void _esfera::rotacion(vector<_vertex3f> perfil, int num){
	int i,j;
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	int num_aux;

	// tratamiento de los vértice

	num_aux=perfil.size();
	vertices.resize(num_aux*num);
	for (j=0;j<num;j++)
	  {for (i=0;i<num_aux;i++)
	     {
	      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
		            perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
	      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
		            perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
	      vertice_aux.y=perfil[i].y;
	      vertices[i+j*num_aux]=vertice_aux;
	     }
	  }

	// tratamiento de las caras

	for (j=0;j<num;j++)
	  {for (i=0;i<num_aux-1;i++)
	     {cara_aux._0=i+((j+1)%num)*num_aux;
	      cara_aux._1=i+1+((j+1)%num)*num_aux;
	      cara_aux._2=i+1+j*num_aux;
	      caras.push_back(cara_aux);

	      cara_aux._0=i+1+j*num_aux;
	      cara_aux._1=i+j*num_aux;
	      cara_aux._2=i+((j+1)%num)*num_aux;
	      caras.push_back(cara_aux);
	     }
	  }

  calcularCoordenadasTextura(num, num_aux); 

	// tapa inferior
	if (fabs(perfil[0].x)>0.0)
	{
		vertice_aux.x=0.0;
	    vertice_aux.y=perfil[0].y;
	    vertice_aux.z=0.0;

	    vertices.push_back(vertice_aux);

	    cara_aux._0=num_aux*num;
	    for (int i = 0; i < num; i++)
	    {
	      cara_aux._1=((i+1)%num)*num_aux;
	      cara_aux._2=i*num_aux;
	      caras.push_back(cara_aux);
	    }
	}
	 
	// tapa superior
	if (fabs(perfil[num_aux-1].x)>0.0)
	{
		vertice_aux.x=0.0;
		vertice_aux.y=perfil[num_aux-1].y;
		vertice_aux.z=0.0;

		vertices.push_back(vertice_aux);

		cara_aux._0=num_aux*num-1;
		for (int i = 0; i < num; i++)
		{
		  cara_aux._1=(i+1)*num_aux-1;
      cara_aux._2=((i+1)%num)*num_aux+num_aux-1;
		  caras.push_back(cara_aux);
		}
	} 

  calcular_normales_vertices();
}

void _esfera::material1(){
    _vertex4f ambiente = _vertex4f(1.0,0.0,0.1,1.0);
    _vertex4f difusa = _vertex4f(1.0,0.0,0.1,1.0);
    _vertex4f especular = _vertex4f(0.0,0.0,0.0,1.0);

		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&difusa);
  	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&ambiente);
  	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
}
      
void _esfera::material2(){
		_vertex4f ambiente2 = _vertex4f(0.0,1.0,0.2,1.0);
    _vertex4f difusa2 = _vertex4f(0.0,1.0,0.2,1.0);
    _vertex4f especular2 = _vertex4f(0.0,0.0,0.0,1.0);

		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&difusa2);
  	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&ambiente2);
  	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular2);
}

//**************************************************************************
// Funcciones para construir modelos sólidos poligonales
//**************************************************************************

void construir_cubo(float tam, solido *cubo){

  cubo->n_v=8;
  cubo->n_c=12;
  cubo->ver=(vertices *)malloc(8*sizeof(vertices));
  cubo->car=(caras *)malloc(12*sizeof(caras));

  cubo->r=0.5;cubo->g=0.6;cubo->b=0.5;

  cubo->ver[0].coord[0]=-tam;cubo->ver[0].coord[1]=-tam;cubo->ver[0].coord[2]=tam;
  cubo->ver[1].coord[0]=tam;cubo->ver[1].coord[1]=-tam;cubo->ver[1].coord[2]=tam;
  cubo->ver[2].coord[0]=tam;cubo->ver[2].coord[1]=tam;cubo->ver[2].coord[2]=tam;
  cubo->ver[3].coord[0]=-tam;cubo->ver[3].coord[1]=tam;cubo->ver[3].coord[2]=tam;
  cubo->ver[4].coord[0]=-tam;cubo->ver[4].coord[1]=-tam;cubo->ver[4].coord[2]=-tam;
  cubo->ver[5].coord[0]=tam;cubo->ver[5].coord[1]=-tam;cubo->ver[5].coord[2]=-tam;
  cubo->ver[6].coord[0]=tam;cubo->ver[6].coord[1]=tam;cubo->ver[6].coord[2]=-tam;
  cubo->ver[7].coord[0]=-tam;cubo->ver[7].coord[1]=tam;cubo->ver[7].coord[2]=-tam;

  cubo->car[0].ind_c[0]=0;cubo->car[0].ind_c[1]=1;cubo->car[0].ind_c[2]=3;
  cubo->car[1].ind_c[0]=3;cubo->car[1].ind_c[1]=1;cubo->car[1].ind_c[2]=2;
  cubo->car[2].ind_c[0]=1;cubo->car[2].ind_c[1]=5;cubo->car[2].ind_c[2]=2;
  cubo->car[3].ind_c[0]=5;cubo->car[3].ind_c[1]=6;cubo->car[3].ind_c[2]=2;
  cubo->car[4].ind_c[0]=5;cubo->car[4].ind_c[1]=4;cubo->car[4].ind_c[2]=6;
  cubo->car[5].ind_c[0]=4;cubo->car[5].ind_c[1]=7;cubo->car[5].ind_c[2]=6;
  cubo->car[6].ind_c[0]=0;cubo->car[6].ind_c[1]=7;cubo->car[6].ind_c[2]=4;
  cubo->car[7].ind_c[0]=0;cubo->car[7].ind_c[1]=3;cubo->car[7].ind_c[2]=7;
  cubo->car[8].ind_c[0]=3;cubo->car[8].ind_c[1]=2;cubo->car[8].ind_c[2]=7;
  cubo->car[9].ind_c[0]=2;cubo->car[9].ind_c[1]=6;cubo->car[9].ind_c[2]=7;
  cubo->car[10].ind_c[0]=0;cubo->car[10].ind_c[1]=1;cubo->car[10].ind_c[2]=4;
  cubo->car[11].ind_c[0]=1;cubo->car[11].ind_c[1]=5;cubo->car[11].ind_c[2]=4;  
}


void construir_piramide(float tam, float al, solido *piramide){
  piramide->n_v=5;
  piramide->n_c=6;
  piramide->ver=(vertices *)malloc(5*sizeof(vertices));
  piramide->car=(caras *)malloc(6*sizeof(caras));

  piramide->r=0.5;piramide->g=0.6;piramide->b=0.5;

  // asignar puntos y caras  
  piramide->ver[0].coord[0]=-tam;piramide->ver[0].coord[1]=0;piramide->ver[0].coord[2]=tam;
  piramide->ver[1].coord[0]=tam;piramide->ver[1].coord[1]=0;piramide->ver[1].coord[2]=tam;
  piramide->ver[2].coord[0]=tam;piramide->ver[2].coord[1]=0;piramide->ver[2].coord[2]=-tam;
  piramide->ver[3].coord[0]=-tam;piramide->ver[3].coord[1]=0;piramide->ver[3].coord[2]=-tam;
  piramide->ver[4].coord[0]=0;piramide->ver[4].coord[1]=al;piramide->ver[4].coord[2]=0;

  piramide->car[0].ind_c[0]=0;piramide->car[0].ind_c[1]=1;piramide->car[0].ind_c[2]=4;
  piramide->car[1].ind_c[0]=1;piramide->car[1].ind_c[1]=2;piramide->car[1].ind_c[2]=4;
  piramide->car[2].ind_c[0]=2;piramide->car[2].ind_c[1]=3;piramide->car[2].ind_c[2]=4;
  piramide->car[3].ind_c[0]=3;piramide->car[3].ind_c[1]=0;piramide->car[3].ind_c[2]=4;
  piramide->car[4].ind_c[0]=3;piramide->car[4].ind_c[1]=1;piramide->car[4].ind_c[2]=0;
  piramide->car[5].ind_c[0]=3;piramide->car[5].ind_c[1]=2;piramide->car[5].ind_c[2]=1; 
}

//**************************************************************************
// Funciones de visualización
//**************************************************************************


void draw_puntos(vertices *ver, int n_v){
    glColor3f(0,0,0);
    glPointSize(10);

    glBegin(GL_POINTS);
    for (unsigned i=0;i<n_v;i++){
        glVertex3f(ver[i].coord[0],ver[i].coord[1],ver[i].coord[2]);
        }
    glEnd();
}


void draw_solido(solido *malla, float r, float g, float b, int modo){
  int n_c,n_v,i;
  n_c=malla->n_c;
  if (modo==1) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(r,g,b);
  glLineWidth(3);
  glBegin(GL_TRIANGLES);
  for (i=0;i<n_c;i++)
      { n_v=malla->car[i].ind_c[0];
        glVertex3f(malla->ver[n_v].coord[0], malla->ver[n_v].coord[1], malla->ver[n_v].coord[2]);
	n_v=malla->car[i].ind_c[1];
        glVertex3f(malla->ver[n_v].coord[0], malla->ver[n_v].coord[1], malla->ver[n_v].coord[2]);
	n_v=malla->car[i].ind_c[2];
        glVertex3f(malla->ver[n_v].coord[0], malla->ver[n_v].coord[1], malla->ver[n_v].coord[2]);
    }
   glEnd();
}

void draw_solido_ajedrez(solido *malla, float r1, float g1, float b1, float r2, float g2, float b2){
  int n_c,n_v,i;
  n_c=malla->n_c;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glBegin(GL_TRIANGLES);
  for (i=0;i<n_c;i++)
      { if (i%2==0)  glColor3f(r1,g1,b1);
         else glColor3f(r2,g2,b2);  
	n_v=malla->car[i].ind_c[0];
        glVertex3f(malla->ver[n_v].coord[0], malla->ver[n_v].coord[1], malla->ver[n_v].coord[2]);
	n_v=malla->car[i].ind_c[1];
        glVertex3f(malla->ver[n_v].coord[0], malla->ver[n_v].coord[1], malla->ver[n_v].coord[2]);
	n_v=malla->car[i].ind_c[2];
        glVertex3f(malla->ver[n_v].coord[0], malla->ver[n_v].coord[1], malla->ver[n_v].coord[2]);
    }
   glEnd();
}

