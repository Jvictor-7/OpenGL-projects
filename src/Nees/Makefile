# --- COMPILA PROGRAMAS OPENGL ---
# --- COMO USAR? ---
# --- DIGITE: make programa ---

# --- COMPILADOR ---
CC = gcc

# --- LIBS USADAS ---
XLIBS = -Wall -lGL -lGLU -lglut -lm

# --- ARQUIVO EXE ---
ARQ = -o $@
##### RULES #####

.SUFFIXES: .c

.c: 
	$(CC) $< $(ARQ) $(XLIBS) 

##### TARGETS ######

clean:
	-rm *.o *~
