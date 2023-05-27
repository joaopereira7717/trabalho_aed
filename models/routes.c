#include <stdlib.h>
#include <string.h>
#include "./routes.h"

#pragma region GRAPH

Vertex *CreateRoute()
{
  return NULL;
}

Vertex *CreateRouteVertex(char *city, int cod)
{
  Vertex *new = (Vertex *)calloc(1, sizeof(Vertex));
  if (new == NULL)
    return NULL;
  new->cod = cod;
  strcpy(new->city, city);
  new->next = NULL;      // com "calloc" isto é dispensável
  new->adjacents = NULL; // com "calloc" isto é dispensável
  return new;
}

Vertex *InsertRouteVertex(Vertex *g, Vertex *new, bool *res)
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

void ShowRoutes(Vertex *g)
{
  if (g == NULL)
    return;
  printf("V: %d - %s\n", g->cod, g->city);
  ShowAdj(g->adjacents);
  ShowRoutes(g->next);
}

Vertex *DestroyRoutes(Vertex *g)
{
  if (g == NULL)
    return NULL;
  Vertex *aux = NULL;
  while (g)
  {
    if (g->next)
      aux = g->next;
    g->adjacents = DestroyAdj(g->adjacents);
    free(g);
    g = aux;
    aux = NULL;
  }
  return g;
}

int SearchCodVertex(Vertex *g, char *city)
{
  if (g == NULL)
    return -1;
  if (strcmp(g->city, city) > 0)
    return -2;
  if (strcmp(g->city, city) == 0)
    return g->cod;
  return (SearchCodVertex(g->next, city));
}

Vertex *SearchVertex(Vertex *g, char *city)
{
  if (g == NULL)
    return NULL;
  if (strcmp(g->city, city) == 0)
    return g;
  return (SearchVertex(g->next, city));
}

Vertex *SearchVertexCod(Vertex *g, int cod)
{
  if (g == NULL)
    return NULL;
  if (g->cod == cod)
    return g;
  return (SearchVertexCod(g->next, cod));
}

Vertex *ResetVisitedVertex(Vertex *g)
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

Adj *CreateAdj(int cod, float valuedistance)
{
  Adj *new = (Adj *)calloc(1, sizeof(Adj));
  if (new == NULL)
    return NULL;
  new->cod = cod;
  new->dist = valuedistance;
  new->next = NULL;
  return new;
}

Vertex *InsertAdjacentVertex(Vertex *g, char *origin, char *dest, float valuedistance, bool *res)
{
#pragma region Validações
  *res = false;

  if (g == NULL)
    return g;

  Vertex *aux = SearchVertex(g, origin);
  int cod = SearchCodVertex(g, dest);

  if (aux == NULL || cod < 0)
    return g;

  if (ExistAdj(aux->adjacents, cod) == true)
    return g;
#pragma endregion

#pragma region Ação
  Adj *newAdj = CreateAdj(cod, valuedistance);
  aux->adjacents = InsertAdj(aux->adjacents, newAdj, res);
  return g;
#pragma endregion
}

Vertex *InsertAdjacentVertexCod(Vertex *g, int codOrigin, int codDest, float valuedistance, bool *res)
{

  *res = false;

  if (g == NULL)
    return g;

  Vertex *o = SearchVertexCod(g, codOrigin);
  Vertex *d = SearchVertexCod(g, codDest);
  if (o == NULL || d == NULL)
    return g;

  if (ExistAdj(o->adjacents, codDest) == true)
    return g;

  Adj *newAdj = CreateAdj(codDest, valuedistance);
  o->adjacents = InsertAdj(o->adjacents, newAdj, res);
  return g;
}

#pragma region GERE_LISTA_ADJACENCIAS

bool ExistAdj(Adj *h, int cod)
{
  if (h == NULL)
    return false;
  if (h->cod == cod)
    return true;
  return ExistAdj(h->next, cod);
}

Adj *InsertAdj(Adj *h, Adj *new, bool *res)
{

  *res = false;

  if (new == NULL)
    return h;

  if (ExistAdj(h, new->cod) == true)
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

void ShowAdj(Adj *h)
{
  if (h == NULL)
    return;
  printf("\tAdj: %d - (%.0f)\n", h->cod, h->dist);
  ShowAdj(h->next);
}

Adj *DestroyAdj(Adj *h)
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
#pragma endregion

#pragma endregion

#pragma region AlGORITMS

int CountPaths(Vertex *g, int src, int dest, int pathCount)
{
  if (g == NULL)
    return 0;

  if (src == dest)
    return (++pathCount);

  else
  {
    Vertex *aux = SearchVertexCod(g, src);
    Adj *hAdj = aux->adjacents;
    while (hAdj)
    {
      Vertex *v = SearchVertexCod(g, hAdj->cod);
      pathCount = CountPaths(g, v->cod, dest, pathCount);
      hAdj = hAdj->next;
    }
  }
  return pathCount;
}

int CountPathsVertexsName(Vertex *g, char *src, char *dest, int pathCount)
{
  int s = SearchCodVertex(g, src);
  int d = SearchCodVertex(g, dest);
  return CountPaths(g, s, d, 0);
}

bool DepthFirstSearchRec(Vertex *g, int origin, int dest)
{

  if (origin == dest)
    return true;

  Vertex *aux = SearchVertexCod(g, origin);
  aux->visited = true;

  Adj *adj = aux->adjacents;
  while (adj)
  {
    Vertex *aux = SearchVertexCod(g, adj->cod);
    if (aux->visited == false)
    {
      bool existes = DepthFirstSearchRec(g, adj->cod, dest);
      return existes;
    }
    else
      aux = aux->next;
  }
  return true;
}

bool DepthFirstSearchNamesRec(Vertex *g, char *src, char *dest)
{
  int o = SearchCodVertex(g, src);
  int d = SearchCodVertex(g, dest);
  return DepthFirstSearchRec(g, o, d);
}

Best BestPath(Vertex *g, int n, int v)
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

void ShowAllPath(Best b, int n, int v)
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

int SaveGraph(Vertex *h, char *fileName)
{
  if (h == NULL)
    return -1;
  FILE *fp;
  fp = fopen(fileName, "wb");
  if (fp == NULL)
    return -2;
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
      sprintf(filePath, "./saved-data/%s.bin", aux->city);
      SaveAdj(aux->adjacents, filePath, aux->cod);
    }
    aux = aux->next;
  }
  fclose(fp);
  return 1;
}

int SaveAdj(Adj *h, char *fileName, int codVertexOrigin)
{
  printf("Gravar adjacencias do vertex %s\n", fileName);
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

Vertex *LoadGraph(Vertex *h, char *fileName, bool *res)
{
  *res = false;
  FILE *fp = fopen(fileName, "rb");
  if (fp == NULL)
    return NULL;
  VertexFile aux;
  Vertex *new;
  while (fread(&aux, 1, sizeof(VertexFile), fp))
  {
    new = CreateRouteVertex(aux.city, aux.cod);
    h = InsertRouteVertex(h, new, res);
  }
  fclose(fp);
  return h;
}

Vertex *LoadAdj(Vertex *g, bool *res)
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
    sprintf(filePath, "./saved-data/%s.bin", auxGraph->city);
    fp = fopen(filePath, "rb");
    if (fp != NULL)
    {
      while (fread(&aux, 1, sizeof(AdjFile), fp))
      {
        g = InsertAdjacentVertexCod(g, aux.codOrigin, aux.codDestiny, aux.weight, res);
      }
      fclose(fp);
    }
    auxGraph = auxGraph->next;
  }
  return g;
}

#pragma endregion
