/**
 * @file routes.c
 * @brief File containing the routes functions
 *
 * This file contains the implementation of functions related to the management of routes with graphs
 *
 * @author João Pereira
 */

#include <stdlib.h>
#include <string.h>
#include "./routes.h"

#pragma region GRAPH

/**
 * @brief Creates a new empty graph.
 *
 * @return Pointer to the starting vertex of the graph.
 */
Vertex *createRoute()
{
  return NULL;
}

/**
 * @brief Creates a new vertex for the graph.
 *
 * @param city Name of the vertex city.
 * @param cod Vertex identifier code.
 * @return Pointer to the newly created vertex.
 */
Vertex *createRouteVertex(char *city, int cod)
{
  Vertex *new = (Vertex *)calloc(1, sizeof(Vertex));
  if (new == NULL)
    return NULL;
  new->cod = cod;
  strcpy(new->city, city);
  new->next = NULL;
  new->adjacents = NULL;
  return new;
}

/**
 * @brief Inserts a new vertex into the graph in alphabetical order.
 *
 * @param g Pointer to the starting vertex of the graph.
 * @param new Pointer to the new vertex to insert.
 * @param res Pointer to a variable that stores the result of the insert operation.
 * @return Pointer to the starting vertex of the graph.
 */
Vertex *insertRouteVertex(Vertex *g, Vertex *new, bool *res)
{
  if (g == NULL)
  {
    g = new;
    *res = true;
    return g;
  }
  else
  {
    Vertex *aux = g;
    Vertex *ant = aux;
    while (aux && strcmp(aux->city, new->city) < 0)
    {
      ant = aux;
      aux = aux->next;
    }
    if (aux == g)
    {
      new->next = g;
      g = new;
    }
    else
    {
      new->next = aux;
      ant->next = new;
    }
    *res = true;
  }
  return g;
}

/**
 * @brief Displays on screen all vertices and their respective adjacency lists of the graph.
 *
 * @param g Pointer to the starting vertex of the graph.
 */
void showRoutes(Vertex *g)
{
  if (g == NULL)
    return;
  printf("V: %d - %s\n", g->cod, g->city);
  showAdj(g->adjacents);
  showRoutes(g->next);
}

/**
 * @brief Frees the memory allocated to the graph and its adjacency lists.
 *
 * @param g Pointer to the starting vertex of the graph.
 * @return Pointer to the starting vertex of the graph (NULL).
 */
Vertex *destroyRoutes(Vertex *g)
{
  if (g == NULL)
    return NULL;
  Vertex *aux = NULL;
  while (g)
  {
    if (g->next)
      aux = g->next;
    g->adjacents = destroyAdj(g->adjacents);
    free(g);
    g = aux;
    aux = NULL;
  }
  return g;
}

/**
 * @brief Gets the identifier code of a vertex from the city name.
 *
 * @param g Pointer to the starting vertex of the graph.
 * @param city Name of the city to be searched.
 * @return Vertex identifier code or -1 if the graph is empty, -2 if the city is not found.
 */

int searchCodVertex(Vertex *g, char *city)
{
  if (g == NULL)
    return -1;
  if (strcmp(g->city, city) > 0)
    return -2;
  if (strcmp(g->city, city) == 0)
    return g->cod;
  return (searchCodVertex(g->next, city));
}

/**
 * @brief Finds a vertex from the city name.
 *
 * @param g Pointer to the starting vertex of the graph.
 * @param city Name of the city to be searched.
 * @return Pointer to the found vertex, or NULL if the city is not found.
 */
Vertex *searchVertex(Vertex *g, char *city)
{
  if (g == NULL)
    return NULL;
  if (strcmp(g->city, city) == 0)
    return g;
  return (searchVertex(g->next, city));
}

/**
 * @brief Fetch a vertex from the identifier code.
 *
 * @param g Pointer to the starting vertex of the graph.
 * @param cod Identifier code of the vertex to be searched.
 * @return Pointer to the found vertex or NULL if the code is not found.
 */
Vertex *searchVertexCod(Vertex *g, int cod)
{
  if (g == NULL)
    return NULL;
  if (g->cod == cod)
    return g;
  return (searchVertexCod(g->next, cod));
}

/**
 * @brief Resets the "visited" flag of all graph vertices to false.
 *
 * @param g Pointer to the starting vertex of the graph.
 * @return Pointer to the starting vertex of the graph.
 */
Vertex *resetVisitedVertex(Vertex *g)
{
  Vertex *aux = g;
  while (aux)
  {
    aux->visited = false;
    aux = aux->next;
  }
  return g;
}

#pragma endregion

#pragma region ADJACENTS

/**
 * @brief Creates a new adjacency list node.
 *
 * @param cod Adjacent vertex identifier code.
 * @param valuedistance Value of distance between vertices.
 * @return Pointer to the newly created node.
 */
Adj *createAdj(int cod, float valuedistance)
{
  Adj *new = (Adj *)calloc(1, sizeof(Adj));
  if (new == NULL)
    return NULL;
  new->cod = cod;
  new->dist = valuedistance;
  new->next = NULL;
  return new;
}

/**
 * @brief Inserts a new adjacent vertex into an adjacency list.
 *
 * @param g Pointer to the starting vertex of the graph.
 * @param origin Name of the city of origin.
 * @param dest Name of the destination city.
 * @param valuedistance Value of distance between vertices.
 * @param res Pointer to a variable that stores the result of the insert operation.
 * @return Pointer to the starting vertex of the graph.
 */
Vertex *insertAdjacentVertex(Vertex *g, char *origin, char *dest, float valuedistance, bool *res)
{
#pragma region Validações
  *res = false;

  if (g == NULL)
    return g;

  Vertex *aux = searchVertex(g, origin);
  int cod = searchCodVertex(g, dest);

  if (aux == NULL || cod < 0)
    return g;

  if (existAdj(aux->adjacents, cod) == true)
    return g;
#pragma endregion

#pragma region Ação
  Adj *newAdj = createAdj(cod, valuedistance);
  aux->adjacents = insertAdj(aux->adjacents, newAdj, res);
  return g;
#pragma endregion
}

/**
 * @brief Inserts a new adjacent vertex in an adjacency list based on the vertex identifier codes.
 *
 * @param g Pointer to the starting vertex of the graph.
 * @param codOrigin Code identifying the city of origin.
 * @param codDest Code identifying the destination city.
 * @param valuedistance Value of distance between vertices.
 * @param res Pointer to a variable that stores the result of the insert operation.
 * @return Pointer to the starting vertex of the graph.
 */
Vertex *insertAdjacentVertexCod(Vertex *g, int codOrigin, int codDest, float valuedistance, bool *res)
{

  *res = false;

  if (g == NULL)
    return g;

  Vertex *o = searchVertexCod(g, codOrigin);
  Vertex *d = searchVertexCod(g, codDest);
  if (o == NULL || d == NULL)
    return g;

  if (existAdj(o->adjacents, codDest) == true)
    return g;

  Adj *newAdj = createAdj(codDest, valuedistance);
  o->adjacents = insertAdj(o->adjacents, newAdj, res);
  return g;
}

#pragma region GERE_LISTA_ADJACENCIAS

/**
 * @brief Checks if an adjacent vertex already exists in an adjacency list.
 *
 * @param h Pointer to the first node in the adjacency list.
 * @param cod Code identifying the adjacent vertex to be searched.
 * @return true if the adjacent vertex exists in the list, false otherwise.
 */
bool existAdj(Adj *h, int cod)
{
  if (h == NULL)
    return false;
  if (h->cod == cod)
    return true;
  return existAdj(h->next, cod);
}

/**
 * @brief Inserts a new adjacent vertex to a given vertex in the graph.
 *
 * @param h The head of the vertex list.
 * @param new The new adjacent vertex to be inserted.
 * @param res A pointer to a boolean variable that will be set to true if the insertion is successful.
 * @return The head of the vertex list.
 */
Adj *insertAdj(Adj *h, Adj *new, bool *res)
{
  *res = false;

  if (new == NULL)
    return h;

  if (existAdj(h, new->cod) == true)
    return h;

  *res = true;
  if (h == NULL)
  {
    h = new;
    return h;
  }

  new->next = h;
  h = new;

  return h;
}

/**
 * @brief Recursively displays the adjacent vertices of a given vertex.
 *
 * @param h The head of the adjacent vertex list.
 */
void showAdj(Adj *h)
{
  if (h == NULL)
    return;
  printf("\tAdj: %d - (%.0f)\n", h->cod, h->dist);
  showAdj(h->next);
}

/**
 * @brief Recursively destroys the adjacent vertex list.
 *
 * @param h The head of the adjacent vertex list.
 * @return NULL.
 */
Adj *destroyAdj(Adj *h)
{
  if (h == NULL)
    return NULL;
  Adj *aux = NULL;
  while (h)
  {
    if (h->next != NULL)
      aux = h->next;
    free(h);
    h = aux;
    aux = NULL;
  }
  return h;
}

/**
 * @brief Counts the number of paths between two vertices in the graph.
 *
 * @param g The head of the vertex list.
 * @param src The code of the source vertex.
 * @param dest The code of the destination vertex.
 * @param pathCount The number of paths found so far.
 * @return The number of paths between the source and destination vertices.
 */
int countPaths(Vertex *g, int src, int dest, int pathCount)
{
  if (g == NULL)
    return 0;

  if (src == dest)
    return (++pathCount);

  else
  {
    Vertex *aux = searchVertexCod(g, src);
    Adj *hAdj = aux->adjacents;
    while (hAdj)
    {
      Vertex *v = searchVertexCod(g, hAdj->cod);
      pathCount = countPaths(g, v->cod, dest, pathCount);
      hAdj = hAdj->next;
    }
  }
  return pathCount;
}

/**
 * @brief Counts the number of paths between two vertices in the graph, given their names.
 *
 * @param g The head of the vertex list.
 * @param src The name of the source vertex.
 * @param dest The name of the destination vertex.
 * @param pathCount The number of paths found so far.
 * @return The number of paths between the source and destination vertices.
 */
int countPathsVertexsName(Vertex *g, char *src, char *dest, int pathCount)
{
  int s = searchCodVertex(g, src);
  int d = searchCodVertex(g, dest);
  return countPaths(g, s, d, 0);
}

/**
 * @brief Recursively performs a depth-first search on the graph to find a path between two vertices.
 *
 * @param g The head of the vertex list.
 * @param origin The code of the origin vertex.
 * @param dest The code of the destination vertex.
 * @return True if a path is found, false otherwise.
 */
bool depthFirstSearchRec(Vertex *g, int origin, int dest)
{
  if (origin == dest)
    return true;

  Vertex *aux = searchVertexCod(g, origin);
  aux->visited = true;

  Adj *adj = aux->adjacents;
  while (adj)
  {
    Vertex *aux = searchVertexCod(g, adj->cod);
    if (aux->visited == false)
    {
      bool existes = depthFirstSearchRec(g, adj->cod, dest);
      return existes;
    }
    else
      aux = aux->next;
  }
  return true;
}

/**
 * @brief Recursively performs a depth-first search on the graph to find a path between two vertices, given their names.
 *
 * @param g The head of the vertex list.
 * @param src The name of the source vertex.
 * @param dest The name of the destination vertex.
 * @return True if a path is found, false otherwise.
 */
bool depthFirstSearchNamesRec(Vertex *g, char *src, char *dest)
{
  int o = searchCodVertex(g, src);
  int d = searchCodVertex(g, dest);
  return depthFirstSearchRec(g, o, d);
}

/**
 * @brief Finds the shortest path from a given vertex to all other vertices in the graph using Dijkstra's algorithm.
 *
 * @param g The head of the vertex list.
 * @param n The number of vertices in the graph.
 * @param v The code of the vertex to start the search from.
 * @return A struct containing the shortest distance and previous vertex for each vertex in the graph.
 */
Best bestPath(Vertex *g, int n, int v)
{

  int cost[MAX][MAX], distance[MAX], pred[MAX];
  int visited[MAX], count, mindistance, nextnode, i;

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cost[i][j] = MAXDISTANCE;
  Vertex *aux = g;
  while (aux)
  {
    if (aux->adjacents)
    {
      Adj *auxAdj = aux->adjacents;
      while (auxAdj)
      {
        cost[aux->cod][auxAdj->cod] = auxAdj->dist;
        auxAdj = auxAdj->next;
      }
    }
    aux = aux->next;
  }

  aux = g;
  while (aux)
  {
    distance[aux->cod] = cost[v][aux->cod];
    pred[aux->cod] = v;
    visited[aux->cod] = 0;
    aux = aux->next;
  }

  distance[v] = 0;
  visited[v] = 1;
  count = 1;
  nextnode = 0;
  while (count < n - 1)
  {
    mindistance = MAXDISTANCE;
    for (i = 0; i < n; i++)
    {
      if (distance[i] < mindistance && !visited[i])
      {
        mindistance = distance[i];
        nextnode = i;
      }
    }

    visited[nextnode] = 1;
    for (i = 0; i < n; i++)
    {
      if (!visited[i])
        if (mindistance + cost[nextnode][i] < distance[i])
        {
          distance[i] = mindistance + cost[nextnode][i];
          pred[i] = nextnode;
        }
    }
    count++;
  }

  Best b;
  for (int i = 0; i < n; i++)
  {
    b.anteriores[i] = pred[i];
    b.distance[i] = distance[i];
  }
  return b;
}

/**
 * @brief ShowAllPath - Function that displays the shortest path and distance to all vertices in the graph
 * @param b: Best struct containing the shortest distance and previous vertex for each vertex in the graph
 * @param n: Number of vertices in the graph
 * @param v: Index of the starting vertex
 */
void showAllPath(Best b, int n, int v)
{
  int j;
  for (int i = 0; i < n; i++)
    if (i != v)
    {
      printf("\nDistancia até ao vertex %d = %d", i, b.distance[i]);
      printf("\nPath = %d", i);

      j = i;
      do
      {
        j = b.anteriores[j];
        printf(" <- %d", j);
      } while (j != v);
    }
}

#pragma endregion

#pragma region FILES

/**
 * @brief SaveGraph - Function that saves the graph to a binary file
 * @param h: Head of the linked list of vertices in the graph
 * @param fileName: Name of the file to save the graph to
 * @return: 1 if the graph was successfully saved, -1 if the file could not be opened, -2 if the head of the linked list is NULL
 */
int saveGraph(Vertex *h, char *fileName)
{
  if (h == NULL)
    return -2;
  FILE *fp;
  fp = fopen(fileName, "wb");
  if (fp == NULL)
    return -1;
  Vertex *aux = h;
  VertexFile auxFile;
  while (aux != NULL)
  {
    auxFile.cod = aux->cod;
    strcpy(auxFile.city, aux->city);
    fwrite(&auxFile, 1, sizeof(VertexFile), fp);
    // Pode gravar de imediato as adjacencias!
    if (aux->adjacents)
    {
      char filePath[100];
      sprintf(filePath, "./saved-data/vertex-adj/%s.bin", aux->city);
      saveAdj(aux->adjacents, filePath, aux->cod);
    }
    aux = aux->next;
  }
  fclose(fp);
  return 1;
}

/**
 * @brief SaveAdj - Function that saves the adjacency list of a vertex to a binary file
 * @param h: Head of the linked list of adjacent vertices
 * @param fileName: Name of the file to save the adjacency list to
 * @param codVertexOrigin: Code of the vertex that the adjacency list belongs to
 * @return: 1 if the adjacency list was successfully saved, -1 if the file could not be opened, -2 if the head of the linked list is NULL
 */
int saveAdj(Adj *h, char *fileName, int codVertexOrigin)
{
  FILE *fp;
  if (h == NULL)
    return -2;
  fp = fopen(fileName, "wb");
  if (fp == NULL)
    return -1;
  Adj *aux = h;
  AdjFile auxFile;
  while (aux)
  {
    auxFile.codDestiny = aux->cod;
    auxFile.codOrigin = codVertexOrigin;
    auxFile.weight = aux->dist;
    fwrite(&auxFile, 1, sizeof(AdjFile), fp);
    aux = aux->next;
  }
  fclose(fp);
  return 1;
}

/**
 * @brief LoadGraph - Function that loads a graph from a binary file
 * @param h: Head of the linked list of vertices in the graph
 * @param fileName: Name of the file to load the graph from
 * @param res: Pointer to a boolean variable that will be set to true if the graph was successfully loaded
 * @return: Head of the linked list of vertices in the loaded graph, or NULL if the file could not be opened
 */
Vertex *loadGraph(Vertex *h, char *fileName, bool *res)
{
  *res = false;
  FILE *fp = fopen(fileName, "rb");
  if (fp == NULL)
    return NULL;
  VertexFile aux;
  Vertex *new;
  while (fread(&aux, 1, sizeof(VertexFile), fp))
  {
    new = createRouteVertex(aux.city, aux.cod);
    h = insertRouteVertex(h, new, res);
  }
  fclose(fp);
  return h;
}

/**
 * @brief LoadAdj - Function that loads the adjacency lists of all vertices in a graph from binary files
 * @param g: Head of the linked list of vertices in the graph
 * @param res: Pointer to a boolean variable that will be set to true if all adjacency lists were successfully loaded
 * @return: Head of the linked list of vertices in the graph with their adjacency lists loaded
 */
Vertex *loadAdj(Vertex *g, bool *res)
{
  *res = false;
  FILE *fp;
  if (g == NULL)
    return g;
  AdjFile aux;
  Vertex *auxGraph = g;
  while (auxGraph)
  {
    char filePath[100];
    sprintf(filePath, "./saved-data/vertex-adj/%s.bin", auxGraph->city);
    fp = fopen(filePath, "rb");
    if (fp != NULL)
    {
      while (fread(&aux, 1, sizeof(AdjFile), fp))
      {
        g = insertAdjacentVertexCod(g, aux.codOrigin, aux.codDestiny, aux.weight, res);
      }
      fclose(fp);
    }
    auxGraph = auxGraph->next;
  }
  return g;
}

#pragma endregion

/**
 * @brief Reads the initial data from two text files and creates a graph of routes and edges.
 *
 * @param g Pointer to the graph of routes and edges.
 * @param res Pointer to a boolean variable that will be set to true if any errors occur during the creation of the graph.
 * @param tot Pointer to an integer variable that will be incremented for each new vertex added to the graph.
 * @return Pointer to the graph of routes and edges.
 */
Vertex *routesReadTxt(Vertex *g, bool *res, int *tot)
{
  *res = false;
  FILE *fp;

  // Open the file containing the list of cities
  fp = fopen("./initial-data/routes.txt", "r");
  if (fp == NULL)
    return NULL;

  char city[100];

  // Read each city from the file and create a new vertex for it
  while (fscanf(fp, "%s", city) != EOF)
  {
    Vertex *new = createRouteVertex(city, *tot);
    g = insertRouteVertex(g, new, res);
    (*tot)++;
  }

  // Close the file
  fclose(fp);

  // Open the file containing the list of edges
  fp = fopen("./initial-data/edges.txt", "r");
  if (fp == NULL)
    return NULL;

  char origin[100], dest[100];
  float dist;

  // Read each edge from the file and add it to the graph
  while (fscanf(fp, "%s %s %f", origin, dest, &dist) != EOF)
  {
    g = insertAdjacentVertex(g, origin, dest, dist, res);
  }

  // Close the file
  fclose(fp);

  // Display the graph of routes and edges
  showRoutes(g);

  // Return the graph of routes and edges
  return g;
}
