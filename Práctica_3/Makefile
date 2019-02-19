
EJECUTABLE= robot

MODULOS=  $(EJECUTABLE).o objetos.o estructuras.o

#  CFLAGS= Parametros para el compilador de C/C++       
CFLAGS=  -g -cpp -DXWINDOWS -I/usr/include -I     

#  LDFLAGS= Parametros para el linkador
LDFLAGS=   -L/usr/lib  

#  LIBS= librerias a usar.
LIBS= -lglut -lGL -lGLU

#  CC= orden de UNIX que invoca al compilador de C/C++ de GNU
CC=        g++

# archivo ejecutable a generar
$(EJECUTABLE): $(MODULOS)	
	$(CC)  -o$(EJECUTABLE) $(LDFLAGS) $(MODULOS)  $(LIBS)   

