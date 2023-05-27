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

/**
 * Estrutura de uma Adjacência.
 */
typedef struct Adj
{
  int cod;    /*!< Código da Adjacência */
  float dist; /*!< ValueDistance */
  struct Adj *next;
} Adj;

/**
 * Estrutura de uma Adjacência para Ficheiro
 */
typedef struct AdjFile
{
  int codOrigin;
  int codDestiny; /*!< Código da Adjacência */
  float weight;   /*!< ValueDistance */
} AdjFile;

/**
 * Descrição de um Vértice do grafo.
 */
typedef struct Vertex
{
  int cod;      /*!< Código do Vértice */
  char city[N]; /*!< Nome da City */
  bool visited;
  struct Vertex *next;   /*!< Lista de Vértices */
  struct Adj *adjacents; /*!< Lista de Adjacências */
} Vertex;

typedef struct VertexFile
{
  int cod;      /*!< Código do Vértice */
  char city[N]; /*!< Nome da City */
} VertexFile;

// Auxiliar ao Dijkstra
#define MAX 5
#define MAXDISTANCE 9999

typedef struct Best
{
  int distance[MAX];   // weight
  int anteriores[MAX]; // vertexs cod
} Best;

#pragma region GRAFO

Vertex *createRoute();
Vertex *insertRouteVertex(Vertex *g, Vertex *new, bool *res);
Vertex *createRouteVertex(char *city, int tot);
void showRoutes(Vertex *g);
int searchCodVertex(Vertex *g, char *city);
Vertex *searchVertex(Vertex *g, char *city);
Vertex *searchVertexCod(Vertex *g, int cod);
Vertex *destroyRoutes(Vertex *g);

#pragma endregion

#pragma region ADJACENCIAS

Vertex *insertAdjacentVertex(Vertex *g, char *origem, char *dest, float valuedistance, bool *res);
Vertex *insertAdjacentVertexCod(Vertex *g, int origem, int dest, float valuedistance, bool *res);

#pragma region LISTA_ADJACENCIAS

Adj *createAdj(int cod, float valuedistance);
Adj *insertAdj(Adj *h, Adj *new, bool *res);
bool existAdj(Adj *h, int cod);
void showAdj(Adj *h);
Adj *destroyAdj(Adj *h);

#pragma endregion

#pragma endregion

#pragma region ALGORITMOS

int countPaths(Vertex *g, int src, int dst, int pathCount);
int countPathsVertexsName(Vertex *g, char *src, char *dest, int pathCount);

bool depthFirstSearchRec(Vertex *g, int origem, int dest);
bool depthFirstSearchNamesRec(Vertex *g, char *src, char *dest);

Vertex *resetVisitedVertex(Vertex *g);

Best bestPath(Vertex *g, int n, int v);
void showAllPath(Best b, int n, int v);

#pragma endregion

#pragma region PRESERVAÇÂO

int saveGraph(Vertex *h, char *fileName);
int saveAdj(Adj *h, char *fileName, int cod);
Vertex *loadGraph(Vertex *h, char *fileName, bool *res);
Vertex *loadAdj(Vertex *g, bool *res);
Vertex *routesReadTxt(Vertex *g, bool *res, int *tot);

#pragma endregion
