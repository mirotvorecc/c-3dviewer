#include "parser.h"

#include <time.h>

void free_surface(Surface *surface) {
  for (int i = 0; i < surface->amount_of_points; i++) {
    free(surface->one_point[i]);
  }
  free(surface->one_point);
}

void free_mesh(Mesh *mesh) {
  for (int i = 0; i < mesh->amount_of_faces; i++) {
    free(mesh->one_face[i]);
  }
  free(mesh->one_face);
}

int open_file(const char *filename, FILE **file) {
  int status_flag = NOT_ERROR;
  *file = fopen(filename, "r");
  if (*file == NULL) {  // Не удалось открыть файл
    status_flag = OPEN_FILE_ERROR;
  } else {
    status_flag = NOT_ERROR;
  }
  return status_flag;
}

int allocate_memory(Surface *surface, Mesh *mesh) {
  int status_flag = NOT_ERROR;
  surface->one_point = malloc(sizeof(Point *));  // начальное выделение памяти
  mesh->one_face = malloc(sizeof(Face *));  // начальное выделение памяти
  if (surface->one_point == NULL ||
      mesh->one_face == NULL) {  // Ошибка при выделении памяти
    free_surface(surface);
    free_mesh(mesh);
    status_flag = MEMORY_ERROR;

  } else {
    surface->amount_of_points = 0;
    mesh->amount_of_faces = 0;
    surface->capacity = 1;  // начальная емкость
    mesh->capacity = 1;     // начальная емкость
    status_flag = NOT_ERROR;
  }
  return status_flag;
}

void process_vertex(char *line, Surface *surface, int *status_flag) {
  Point *point = malloc(sizeof(Point));
  handle_memory_error(point, status_flag);
  if (*status_flag == NOT_ERROR) {
    int result = sscanf(line, "v %lf %lf %lf", &point->x, &point->y, &point->z);
    if (result != 3) {  // Ошибка при чтении вершины
      *status_flag = PARSER_ERROR;
      free(point);
    } else if (sscanf(line, "v %lf %lf %lf", &point->x, &point->y, &point->z) ==
               3) {
      if (surface->amount_of_points >= surface->capacity) {
        surface->capacity *= 2;
        surface->one_point =
            realloc(surface->one_point, surface->capacity * sizeof(Point *));
        handle_memory_error(surface->one_point, status_flag);
        if (*status_flag != NOT_ERROR) {
          free(point);
        }
      }
      if (*status_flag == NOT_ERROR) {
        surface->one_point[surface->amount_of_points++] = point;
      }
    }
    // else {
    //   *status_flag = PARSER_ERROR;
    //   free(point);
    // }
  }
}

void process_face(char *line, Mesh *mesh, int *status_flag) {
  Face *face = malloc(sizeof(Face));
  handle_memory_error(face, status_flag);
  if (*status_flag == NOT_ERROR) {
    int result = sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &face->v[0],
                        &face->vt[0], &face->vn[0], &face->v[1], &face->vt[1],
                        &face->vn[1], &face->v[2], &face->vt[2], &face->vn[2]);
    if (result != 9) {
      result = sscanf(line, "f %d//%d %d//%d %d//%d", &face->v[0], &face->vn[0],
                      &face->v[1], &face->vn[1], &face->v[2], &face->vn[2]);
      if (result != 6) {
        result = sscanf(line, "f %d/%d %d/%d %d/%d", &face->v[0], &face->vt[0],
                        &face->v[1], &face->vt[1], &face->v[2], &face->vt[2]);
        if (result != 6) {
          result =
              sscanf(line, "f %d %d %d", &face->v[0], &face->v[1], &face->v[2]);
          if (result != 3) {  // Ошибка при чтении грани
            *status_flag = PARSER_ERROR;
            free(face);
            return;
          }
        }
      }
    }
    if (mesh->amount_of_faces >= mesh->capacity) {
      mesh->capacity *= 2;
      mesh->one_face = realloc(mesh->one_face, mesh->capacity * sizeof(Face *));
      handle_memory_error(mesh->one_face, status_flag);
      if (*status_flag != NOT_ERROR) {
        free(face);
      }
    }
    if (*status_flag == NOT_ERROR) {
      mesh->one_face[mesh->amount_of_faces++] = face;
    }
  }
}

void parse_line(char *line, Surface *surface, Mesh *mesh, int *status_flag) {
  if (line[0] == 'v' && line[1] == ' ') {
    process_vertex(line, surface, status_flag);
  } else if (line[0] == 'f' && line[1] == ' ') {
    process_face(line, mesh, status_flag);
  }
}

void handle_memory_error(void *pointer, int *status_flag) {
  if (pointer == NULL) {
    *status_flag = MEMORY_ERROR;
  }
}

int parse_obj_file(const char *filename, Surface *surface, Mesh *mesh) {
  // clock_t t = 0;
  // t = clock();
  // printf("Timer starts\n");

  int status_flag = NOT_ERROR;
  FILE *file;
  char line[600];

  status_flag = open_file(filename, &file);
  if (status_flag == NOT_ERROR) {
    status_flag = allocate_memory(surface, mesh);
    if (status_flag == NOT_ERROR) {
      while (fgets(line, sizeof(line), file) && status_flag == NOT_ERROR) {
        parse_line(line, surface, mesh, &status_flag);
      }
      if (ferror(file)) {
        status_flag = OPEN_FILE_ERROR;
      }
    }
    if (status_flag == PARSER_ERROR) {
      free_surface(surface);
      free_mesh(mesh);
    }
    fclose(file);
  }

  // t = clock() - t;
  // double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed
  // time printf("The program took %f seconds to execute\n", time_taken);

  return status_flag;
}