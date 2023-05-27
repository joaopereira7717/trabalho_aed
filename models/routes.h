#pragma once

#include <stdio.h>
#include <stdbool.h>

#define N 20

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

Vertex *CreateRoute();
Vertex *InsertRouteVertex(Vertex *g, Vertex *new, bool *res);
Vertex *CreateRouteVertex(char *city, int tot);
void ShowRoutes(Vertex *g);
int SearchCodVertex(Vertex *g, char *city);
Vertex *SearchVertex(Vertex *g, char *city);
Vertex *SearchVertexCod(Vertex *g, int cod);
Vertex *DestroyRoutes(Vertex *g);

#pragma endregion

#pragma region ADJACENCIAS

Vertex *InsertAdjacentVertex(Vertex *g, char *origem, char *dest, float valuedistance, bool *res);
Vertex *InsertAdjacentVertexCod(Vertex *g, int origem, int dest, float valuedistance, bool *res);

#pragma region LISTA_ADJACENCIAS

Adj *CreateAdj(int cod, float valuedistance);
Adj *InsertAdj(Adj *h, Adj *new, bool *res);
bool ExistAdj(Adj *h, int cod);
void ShowAdj(Adj *h);
Adj *DestroyAdj(Adj *h);

#pragma endregion

#pragma endregion

#pragma region ALGORITMOS

int CountPaths(Vertex *g, int src, int dst, int pathCount);
int CountPathsVertexsName(Vertex *g, char *src, char *dest, int pathCount);

bool DepthFirstSearchRec(Vertex *g, int origem, int dest);
bool DepthFirstSearchNamesRec(Vertex *g, char *src, char *dest);

Vertex *ResetVisitedVertex(Vertex *g);

Best BestPath(Vertex *g, int n, int v);
void ShowAllPath(Best b, int n, int v);

#pragma endregion

#pragma region PRESERVAÇÂO

int SaveGraph(Vertex *h, char *fileName);
int SaveAdj(Adj *h, char *fileName, int cod);
Vertex *LoadGraph(Vertex *h, char *fileName, bool *res);
Vertex *LoadAdj(Vertex *g, bool *res);

#pragma endregion
