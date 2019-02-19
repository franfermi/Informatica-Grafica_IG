//**************************************************************************
// Codigo del usuario
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include "user_code.h"


_file_ply fichero_ply;
//**************************************************************************
// Funcciones para construir modelos sólidos poligonales
//**************************************************************************

void construir_cubo(float tam, solido *cubo)
{

cubo->n_v=8;
cubo->n_c=12;
cubo->ver=(vertices *)malloc(8*sizeof(vertices));
cubo->car=(caras *)malloc(12*sizeof(caras));

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


void construir_piramide(float tam, float al, solido *piramide)
{
piramide->n_v=5;
piramide->n_c=6;
piramide->ver=(vertices *)malloc(5*sizeof(vertices));
piramide->car=(caras *)malloc(6*sizeof(caras));

piramide->r=0.9;piramide->g=0.6;piramide->b=0.2;

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


void construir_ply(char *file, solido *ply)
{
vector<int> faces_ply;
vector<float> vertices_ply;
	
fichero_ply.open(file);
fichero_ply.read(vertices_ply,faces_ply);
	
// leido el fichero ply se convierte a una estructura tipo solido
int n_v, n_c;
n_v=vertices_ply.size()/3;
n_c=faces_ply.size()/3;

ply->n_v=n_v;
ply->n_c=n_c;
ply->ver=(vertices *)malloc(n_v*sizeof(vertices));
ply->car=(caras *)malloc(n_c*sizeof(caras));

for (int i=0;i<n_v;i++)
	  {
	  ply->ver[i].coord[0]=vertices_ply[i*3];
	  ply->ver[i].coord[1]=vertices_ply[i*3+1];
	  ply->ver[i].coord[2]=vertices_ply[i*3+2];
	 }

for (int i=0;i<n_c;i++)
	  {
	  ply->car[i].ind_c[0]=faces_ply[i*3];
	  ply->car[i].ind_c[1]=faces_ply[i*3+1];
          ply->car[i].ind_c[2]=faces_ply[i*3+2];
	 }	 
	 
}



//**************************************************************************
// Funciones de visualización
//**************************************************************************


void draw_puntos(vertices *ver, int n_v)
{
   
    glColor3f(0,0,0);
    glPointSize(10);

    glBegin(GL_POINTS);
    for (unsigned i=0;i<n_v;i++){
        glVertex3f(ver[i].coord[0],ver[i].coord[1],ver[i].coord[2]);
        }
    glEnd();
}


void draw_solido(solido *malla, float r, float g, float b, int modo)
{
  
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

void draw_solido_ajedrez(solido *malla, float r1, float g1, float b1, float r2, float g2, float b2)
{
  
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


