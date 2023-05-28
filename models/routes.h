/**
 * @file routes.h
 * @brief File containing the functions to manage the routes
 *
 * @author João Pereira
 */

#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define N 50

typedef struct Adj // adjacents
{
  int cod;    /*!< Cod of adjacent */
  float dist; /*!< Distance */
  struct Adj *next;
} Adj;

typedef struct AdjFile // adj to file
{
  int codOrigin;
  int codDestiny;
  float weight;
} AdjFile;

typedef struct Vertex // vertex from the graph
{
  int cod;
  char city[N];
  bool visited;
  struct Vertex *next;   // list of vertex
  struct Adj *adjacents; // list of adjacents
} Vertex;

typedef struct VertexFile
{
  int cod;
  char city[N];
} VertexFile;

// Dijkstra aux
#define MAX 5
#define MAXDISTANCE 9999

typedef struct Best
{
  int distance[MAX]; // weight
  int befores[MAX];  // vertexs cod
} Best;

#pragma region GRAPH

Vertex *createRoute();
Vertex *insertRouteVertex(Vertex *g, Vertex *new, bool *res);
Vertex *createRouteVertex(char *city, int tot);
void showRoutes(Vertex *g);
int searchCodVertex(Vertex *g, char *city);
Vertex *searchVertex(Vertex *g, char *city);
Vertex *searchVertexCod(Vertex *g, int cod);
Vertex *destroyRoutes(Vertex *g);

#pragma endregion

#pragma region ADJACENTS

Vertex *insertAdjacentVertex(Vertex *g, char *origem, char *dest, float valuedistance, bool *res);
Vertex *insertAdjacentVertexCod(Vertex *g, int origem, int dest, float valuedistance, bool *res);

#pragma region LIST_ADJACENTS

Adj *createAdj(int cod, float valuedistance);
Adj *insertAdj(Adj *h, Adj *new, bool *res);
bool existAdj(Adj *h, int cod);
void showAdj(Adj *h);
Adj *destroyAdj(Adj *h);

#pragma endregion

#pragma endregion

#pragma region ALGORITMS

int countPaths(Vertex *g, int src, int dst, int pathCount);
int countPathsVertexsName(Vertex *g, char *src, char *dest, int pathCount);

bool depthFirstSearchRec(Vertex *g, int origem, int dest);
bool depthFirstSearchNamesRec(Vertex *g, char *src, char *dest);

Vertex *resetVisitedVertex(Vertex *g);

Best bestPath(Vertex *g, int n, int v);
void showAllPath(Best b, int n, int v);

#pragma endregion

#pragma region SAVING

int saveGraph(Vertex *h, char *fileName);
int saveAdj(Adj *h, char *fileName, int cod);
Vertex *loadGraph(Vertex *h, char *fileName, bool *res);
Vertex *loadAdj(Vertex *g, bool *res);
Vertex *routesReadTxt(Vertex *g, bool *res, int *tot);

#pragma endregion
