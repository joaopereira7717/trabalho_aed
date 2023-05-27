#include <stdlib.h>
#include <string.h>
#include "./routes.h"

#pragma region GRAFO

Vertice *CreateRoute()
{
  return NULL;
}

Vertice *CreateRouteVertex(char *cidade, int cod)
{
  Vertice *novo = (Vertice *)calloc(1, sizeof(Vertice));
  if (novo == NULL)
    return NULL;
  novo->cod = cod;
  strcpy(novo->cidade, cidade);
  novo->next = NULL;       // com "calloc" isto é dispensável
  novo->adjacentes = NULL; // com "calloc" isto é dispensável
  return novo;
}

Vertice *InsertRouteVertex(Vertice *g, Vertice *novo, bool *res)
{
  if (g == NULL)
  {
    g = novo;
    *res = true;
    return g;
  }
  else
  {
    Vertice *aux = g;
    Vertice *ant = aux;
    while (aux && strcmp(aux->cidade, novo->cidade) < 0)
    {
      ant = aux;
      aux = aux->next;
    }
    if (aux == g)
    {
      novo->next = g;
      g = novo;
    }
    else
    {
      novo->next = aux;
      ant->next = novo;
    }
    *res = true;
  }
  return g;
}

void ShowRoutes(Vertice *g)
{
  if (g == NULL)
    return;
  printf("V: %d - %s\n", g->cod, g->cidade);
  ShowAdj(g->adjacentes);
  ShowRoutes(g->next);
}

Vertice *DestroyRoutes(Vertice *g)
{
  if (g == NULL)
    return NULL;
  Vertice *aux = NULL;
  while (g)
  {
    if (g->next)
      aux = g->next;
    g->adjacentes = DestroyAdj(g->adjacentes);
    free(g);
    g = aux;
    aux = NULL;
  }
  return g;
}

int SearchCodVertex(Vertice *g, char *cidade)
{
  if (g == NULL)
    return -1;
  if (strcmp(g->cidade, cidade) > 0)
    return -2;
  if (strcmp(g->cidade, cidade) == 0)
    return g->cod;
  return (SearchCodVertex(g->next, cidade));
}

Vertice *SearchVertex(Vertice *g, char *cidade)
{
  if (g == NULL)
    return NULL;
  if (strcmp(g->cidade, cidade) == 0)
    return g;
  return (SearchVertex(g->next, cidade));
}

Vertice *SearchVertexCod(Vertice *g, int cod)
{
  if (g == NULL)
    return NULL;
  if (g->cod == cod)
    return g;
  return (SearchVertexCod(g->next, cod));
}

Vertice *ResetVisitedVertex(Vertice *g)
{
  Vertice *aux = g;
  while (aux)
  {
    aux->visitado = false;
    aux = aux->next;
  }
  return g;
}

#pragma endregion

#pragma region ADJACENCIAS

Adj *CreateAdj(int cod, float peso)
{
  Adj *novo = (Adj *)calloc(1, sizeof(Adj));
  if (novo == NULL)
    return NULL;
  novo->cod = cod;
  novo->dist = peso;
  novo->next = NULL;
  return novo;
}

Vertice *InsertAdjacentVertex(Vertice *g, char *origem, char *dest, float peso, bool *res)
{
#pragma region Validações
  *res = false; // por defeito é falso

  if (g == NULL)
    return g; //<! se grafo está vazio, ignora operação

  Vertice *aux = SearchVertex(g, origem); //<! procura vertice origem
  int cod = SearchCodVertex(g, dest);     //<! procura vertice destino
  // ou
  // Vertice* d = SearchVertex(g, dest);

  if (aux == NULL || cod < 0)
    return g; //<! Se não encontrou vertice origem e destino, ignora operação

  if (ExistAdj(aux->adjacentes, cod) == true)
    return g; // Se já foi registado esta adjacencia, ignorar a operação
#pragma endregion

#pragma region Ação
  // Insere nova adjacencia no vertice "Origem"
  Adj *novoAdj = CreateAdj(cod, peso);
  aux->adjacentes = InsertAdj(aux->adjacentes, novoAdj, res);
  return g;
  // Se for não orientado
  // return (InsertAdjacentVertex(g, dest, origem, peso, res));
#pragma endregion
}

Vertice *InsertAdjacentVertexCod(Vertice *g, int codOrigem, int codDest, float peso, bool *res)
{

#pragma region Validações
  *res = false; // por defeito é falso

  if (g == NULL)
    return g; //<! se grafo está vazio, ignora operação

  Vertice *o = SearchVertexCod(g, codOrigem); //<! procura vertice origem
  Vertice *d = SearchVertexCod(g, codDest);   //<! procura vertice destino
  if (o == NULL || d == NULL)
    return g; //<! Se não encontrou vertice origem e destino, ignora operação

  if (ExistAdj(o->adjacentes, codDest) == true)
    return g; // Se já foi registado esta adjacencia, ignorar a operação
#pragma endregion

    // g=InsertAdjacentVertex(g, o->cidade, d->cidade, peso, res);

#pragma region Ação
  // Insere nova adjacencia no vertice "Origem"
  Adj *novoAdj = CreateAdj(codDest, peso);
  o->adjacentes = InsertAdj(o->adjacentes, novoAdj, res);
  return g;
  // Se for não orientado
  // return (InsertAdjacentVertex(g, dest, origem, peso, res));
#pragma endregion
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

Adj *InsertAdj(Adj *h, Adj *novo, bool *res)
{

  *res = false; // por defeito é falso

  if (novo == NULL) // Se novo adjacente é nulo, ignora operação
    return h;

  if (ExistAdj(h, novo->cod) == true)
    return h; // Se novo adj existe, ignorar operação

  // Inserir nova adjacencia!
  *res = true;
  if (h == NULL)
  { // Se lista de adjacencias é vazia, esta é a primeira adjacencia
    h = novo;
    return h;
  }
  // senão insere no início das adjacências! Podia ser de outra forma!
  novo->next = h;
  h = novo;

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

#pragma region ALGORITMOS

int CountPaths(Vertice *g, int src, int dst, int pathCount)
{
  if (g == NULL)
    return 0;

  // If current vertex is same as destination, then increment count
  if (src == dst)
    return (++pathCount);

  else
  { // Recur for all the vertices adjacent to this vertex
    Vertice *aux = SearchVertexCod(g, src);
    Adj *hAdj = aux->adjacentes;
    while (hAdj)
    {
      Vertice *v = SearchVertexCod(g, hAdj->cod);
      pathCount = CountPaths(g, v->cod, dst, pathCount);
      hAdj = hAdj->next;
    }
  }
  return pathCount;
}

int CountPathsVerticesName(Vertice *g, char *src, char *dest, int pathCount)
{
  int s = SearchCodVertex(g, src);
  int d = SearchCodVertex(g, dest);
  return CountPaths(g, s, d, 0);
}

bool DepthFirstSearchRec(Vertice *g, int origem, int dest)
{

  if (origem == dest)
    return true;

  Vertice *aux = SearchVertexCod(g, origem);
  aux->visitado = true;
  // printf(" Vertice: %s : %d\n", aux->cidade, aux->cod);

  Adj *adj = aux->adjacentes;
  while (adj)
  {
    Vertice *aux = SearchVertexCod(g, adj->cod);
    if (aux->visitado == false)
    {
      bool existe = DepthFirstSearchRec(g, adj->cod, dest);
      return existe;
    }
    else
      aux = aux->next;
  }
  return true;
}

bool DepthFirstSearchNamesRec(Vertice *g, char *src, char *dest)
{
  int o = SearchCodVertex(g, src);
  int d = SearchCodVertex(g, dest);
  return DepthFirstSearchRec(g, o, d);
}

Best BestPath(Vertice *g, int n, int v)
{

  int cost[MAX][MAX], distance[MAX], pred[MAX];
  int visited[MAX], count, mindistance, nextnode, i;

  // pred[] guarda o vertice anterior ao atual
  // count número de nodos visitados até ao momento
  // cria matriz de custos a partir da matriz de adjacencias

  // inicializações

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cost[i][j] = MAXDISTANCE;

  // Custos
  Vertice *aux = g;
  while (aux)
  {
    if (aux->adjacentes)
    {
      Adj *auxAdj = aux->adjacentes;
      while (auxAdj)
      {
        cost[aux->cod][auxAdj->cod] = auxAdj->dist;
        auxAdj = auxAdj->next;
      }
    }
    aux = aux->next;
  }

  // pred[],distance[] and visited[]
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
    // nextnode é o vertice à menor distância do atual
    for (i = 0; i < n; i++)
    {
      if (distance[i] < mindistance && !visited[i])
      {
        mindistance = distance[i];
        nextnode = i;
      }
    }

    // Verifica se existe um melhor caminho
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
  // Devolve resultados
  Best b;
  for (int i = 0; i < n; i++)
  {
    b.anteriores[i] = pred[i];
    b.distance[i] = distance[i];
  }
  return b;
}

/*
Auxiliar
*/
void ShowAllPath(Best b, int n, int v)
{
  int j;
  for (int i = 0; i < n; i++)
    if (i != v)
    {
      printf("\nDistancia até ao vertice %d = %d", i, b.distance[i]);
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

#pragma region FICHEIROS

int SaveGraph(Vertice *h, char *fileName)
{

  if (h == NULL)
    return -1;
  FILE *fp;
  fp = fopen(fileName, "wb");
  if (fp == NULL)
    return -2;
  Vertice *aux = h;
  VerticeFile auxFicheiro;
  while (aux != NULL)
  {
    auxFicheiro.cod = aux->cod;
    strcpy(auxFicheiro.cidade, aux->cidade);
    fwrite(&auxFicheiro, 1, sizeof(VerticeFile), fp);
    // Pode gravar de imediato as adjacencias!
    if (aux->adjacentes)
    {
      SaveAdj(aux->adjacentes, aux->cidade, aux->cod);
      // if (r <0) break;
    }
    aux = aux->next;
  }
  fclose(fp);
  return 1;
}

int SaveAdj(Adj *h, char *fileName, int codVerticeOrigem)
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
    auxFile.codDestino = aux->cod;
    auxFile.codOrigem = codVerticeOrigem;
    auxFile.weight = aux->dist;
    fwrite(&auxFile, 1, sizeof(AdjFile), fp);
    aux = aux->next;
  }
  fclose(fp);
  return 1;
}

Vertice *LoadGraph(Vertice *h, char *fileName, bool *res)
{
  *res = false;
  FILE *fp = fopen(fileName, "rb");
  if (fp == NULL)
    return NULL;
  VerticeFile aux;
  Vertice *novo;
  while (fread(&aux, 1, sizeof(VerticeFile), fp))
  {
    novo = CreateRouteVertex(aux.cidade, aux.cod);
    h = InsertRouteVertex(h, novo, res);
  }
  fclose(fp);
  return h;
}

Vertice *LoadAdj(Vertice *g, bool *res)
{
  *res = false;
  FILE *fp;
  if (g == NULL)
    return g;
  AdjFile aux;
  Vertice *auxGraph = g;
  while (auxGraph)
  {
    fp = fopen(auxGraph->cidade, "rb");
    if (fp != NULL)
    {
      while (fread(&aux, 1, sizeof(AdjFile), fp))
      {
        g = InsertAdjacentVertexCod(g, aux.codOrigem, aux.codDestino, aux.weight, res);
      }
      fclose(fp);
    }
    auxGraph = auxGraph->next;
  }
  return g;
}

#pragma endregion
