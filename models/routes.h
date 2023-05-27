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
  float dist; /*!< Peso */
  struct Adj *next;
} Adj;

/**
 * Estrutura de uma Adjacência para Ficheiro
 */
typedef struct AdjFile
{
  int codOrigem;
  int codDestino; /*!< Código da Adjacência */
  float weight;   /*!< Peso */
} AdjFile;

/**
 * Descrição de um Vértice do grafo.
 */
typedef struct Vertice
{
  int cod;        /*!< Código do Vértice */
  char cidade[N]; /*!< Nome da Cidade */
  bool visitado;
  struct Vertice *next;   /*!< Lista de Vértices */
  struct Adj *adjacentes; /*!< Lista de Adjacências */
} Vertice;

typedef struct VerticeFile
{
  int cod;        /*!< Código do Vértice */
  char cidade[N]; /*!< Nome da Cidade */
} VerticeFile;

// Auxiliar ao Dijkstra
#define MAX 5
#define MAXDISTANCE 9999

typedef struct Best
{
  int distance[MAX];   // weight
  int anteriores[MAX]; // vertices cod
} Best;

#pragma region GRAFO

Vertice *CreateRoute();
Vertice *InsertRouteVertex(Vertice *g, Vertice *novo, bool *res);
Vertice *CreateRouteVertex(char *cidade, int tot);
void ShowRoutes(Vertice *g);
int SearchCodVertex(Vertice *g, char *cidade);
Vertice *SearchVertex(Vertice *g, char *cidade);
Vertice *SearchVertexCod(Vertice *g, int cod);
Vertice *DestroyRoutes(Vertice *g);

#pragma endregion

#pragma region ADJACENCIAS

Vertice *InsertAdjacentVertex(Vertice *g, char *origem, char *dest, float peso, bool *res);
Vertice *InsertAdjacentVertexCod(Vertice *g, int origem, int dest, float peso, bool *res);

#pragma region LISTA_ADJACENCIAS

Adj *CreateAdj(int cod, float peso);
Adj *InsertAdj(Adj *h, Adj *novo, bool *res);
bool ExistAdj(Adj *h, int cod);
void ShowAdj(Adj *h);
Adj *DestroyAdj(Adj *h);

#pragma endregion

#pragma endregion

#pragma region ALGORITMOS

int CountPaths(Vertice *g, int src, int dst, int pathCount);
int CountPathsVerticesName(Vertice *g, char *src, char *dest, int pathCount);

bool DepthFirstSearchRec(Vertice *g, int origem, int dest);
bool DepthFirstSearchNamesRec(Vertice *g, char *src, char *dest);

Vertice *ResetVisitedVertex(Vertice *g);

Best BestPath(Vertice *g, int n, int v);
void ShowAllPath(Best b, int n, int v);

#pragma endregion

#pragma region PRESERVAÇÂO

int SaveGraph(Vertice *h, char *fileName);
int SaveAdj(Adj *h, char *fileName, int cod);
Vertice *LoadGraph(Vertice *h, char *fileName, bool *res);
Vertice *LoadAdj(Vertice *g, bool *res);

#pragma endregion