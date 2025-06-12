#ifndef PARSER_H
#define PARSER_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOT_ERROR 0
#define MEMORY_ERROR 1
#define OPEN_FILE_ERROR 2
#define PARSER_ERROR 3

typedef struct {
  double x;
  double y;
  double z;
  double scale;
} Point;

typedef struct {
  Point **one_point;
  int amount_of_points;
  int capacity;
} Surface;

typedef struct {
  int v[3];   // индексы вершин
  int vt[3];  // индексы текстурных координат
  int vn[3];  // индексы нормалей
} Face;

typedef struct {
  Face **one_face;
  int amount_of_faces;
  int capacity;
} Mesh;

void free_surface(Surface *surface);
void free_mesh(Mesh *mesh);

void parse_line(char *line, Surface *surface, Mesh *mesh, int *status_flag);
void handle_memory_error(void *pointer, int *status_flag);
int parse_obj_file(const char *filename, Surface *surface, Mesh *mesh);
int open_file(const char *filename, FILE **file);
int allocate_memory(Surface *surface, Mesh *mesh);
void process_face(char *line, Mesh *mesh, int *status_flag);
void process_vertex(char *line, Surface *surface, int *status_flag);

#endif
