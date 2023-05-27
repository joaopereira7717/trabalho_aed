/**
 * @file main.c
 * @brief File containing the main function
 *
 * This file contains the main function that initializes the program and calls the necessary functions to manipulate user, vehicle, and rent data.
 *
 * @author João Pereira
 * @date 2023-03-18
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include "./models/user.h"
#include "./models/vehicle.h"
#include "./models/rentals.h"
#include "./models/routes.h"

/**
 * @brief The main function of the program
 *
 * This function initializes the program and calls the necessary functions to manipulate user, vehicle, and rent data.
 *
 * @return 0 if the program runs successfully
 */
int main()
{
  printf("Program start!\n");
  setlocale(LC_ALL, "Portuguese"); // write portuguese characters

  static int tot = 0; // total vertex
  bool res;

#pragma region GRAFOS

  Vertex *graf = CreateRoute();

  Vertex *newVertex = CreateRouteVertex("Braga", tot);
  if (newVertex != NULL)
  {
    graf = InsertRouteVertex(graf, newVertex, &res);
    tot++;
  }

  newVertex = CreateRouteVertex("Porto", tot);
  if (newVertex != NULL)
  {
    graf = InsertRouteVertex(graf, newVertex, &res);
    tot++;
  }

  newVertex = CreateRouteVertex("Fafe", tot);
  if (newVertex != NULL)
  {
    graf = InsertRouteVertex(graf, newVertex, &res);
    tot++;
  }

  newVertex = CreateRouteVertex("Lisboa", tot);
  if (newVertex != NULL)
  {
    graf = InsertRouteVertex(graf, newVertex, &res);
    tot++;
  }

  newVertex = CreateRouteVertex("Barcelos", tot);
  if (newVertex != NULL)
  {
    graf = InsertRouteVertex(graf, newVertex, &res);
    tot++;
  }

  ShowRoutes(graf);

  // Create adjacents
  graf = InsertAdjacentVertex(graf, "Braga", "Porto", 35, &res);
  graf = InsertAdjacentVertex(graf, "Braga", "Fafe", 15, &res);
  graf = InsertAdjacentVertex(graf, "Fafe", "Porto", 60, &res);
  graf = InsertAdjacentVertex(graf, "Porto", "Lisboa", 250, &res);
  graf = InsertAdjacentVertex(graf, "Lisboa", "Barcelos", 270, &res);

  ShowRoutes(graf);

  int pathCount = 0;
  int x = CountPaths(graf, 0, 2, pathCount);
  printf("\nExiste %d Paths entre %d e %d\n", x, 0, 2);

  int countPath = 0;
  x = CountPathsVertexsName(graf, "Braga", "Porto", countPath);
  x = CountPathsVertexsName(graf, "Braga", "Fafe", countPath);

  x = CountPaths(graf, 0, 1, 0);

  printf("\nExiste Path?\n");
  bool existe = DepthFirstSearchRec(graf, 0, 3);
  printf(" Existe Path entre %d e %d: %s\n", 0, 3, (existe == true ? "Sim" : "Não"));

  graf = ResetVisitedVertex(graf);

  existe = DepthFirstSearchNamesRec(graf, "Braga", "Porto");
  printf(" Existe Path entre %s e %s: %s\n", "Braga", "Porto", (existe == true ? "Sim" : "Não"));

#pragma region FICHEIROS

  int res1 = SaveGraph(graf, "./saved-data/Vertexs.bin");
  if (res1 > 0)
    puts("\nGrafo gravado em ficheiro");

  graf = DestroyRoutes(graf);

  puts("\nGrafo em memória:");
  ShowRoutes(graf);

  graf = LoadGraph(graf, "./saved-data/Vertexs.bin", &res);
  if (graf != NULL)
    puts("\nVertexs do Grafo lido de ficheiro\n");
  ShowRoutes(graf);

  puts("\nLer Adjacências do grafo de ficheiro\n");
  graf = LoadAdj(graf, &res);

  ShowRoutes(graf);

#pragma endregion

  Best b = BestPath(graf, 5, 0);
  ShowAllPath(b, 5, 0);

#pragma endregion
#pragma region USER
  UserList *userList = NULL;
  readUsersFromTxt(&userList);
  // setUsersData(&userList);
  printUserList(userList);
  User *user = createUser(1, "name", "email", 1, 1, "password", 0, true);
  bool isCreated = createUserList(&userList, *user);
  printUserList(userList);
  printf("\nisCreated: %d", isCreated);
  printUserList(userList);
  User *userToEdit = createUser(1, "name2", "email2", 2, 2, "password2", 2, false);
  bool isEdited = editUser(userList, 1, *userToEdit);
  printf("\nisEdited: %d", isEdited);
  printUserList(userList);
  bool isDeleted = deleteUser(&userList, 1);
  printf("\nisDeleted: %d", isDeleted);
  printUserList(userList);
#pragma endregion
#pragma region VEHICLE
  VehicleList *vehicleList = NULL;
  readVehiclesFromTxt(&vehicleList);
  Vehicle *vehicle = createVehicle("registration", "type", 1, 1, true, "Fafe", graf);
  printf("%s", vehicle->registration);
  bool isCreatedVehicle = createVehicleList(&vehicleList, *vehicle);
  printf("\nisCreated vehicle: %d", isCreatedVehicle);
  readVehiclesFromTxt(&vehicleList);
  printVehicleList(vehicleList);
  Vehicle *vehicleToEdit = createVehicle("registration", "type2", 2, 2, false, "Porto", graf);
  bool isEditedVehicle = editVehicle(vehicleList, "registration", *vehicleToEdit);
  printf("\nisEdited vehicle: %d", isEditedVehicle);
  printVehicleList(vehicleList);
  bool isDeletedVehicle = deleteVehicle(&vehicleList, "registration");
  printf("is deleted vehicle: %d", isDeletedVehicle);
  printVehicleList(vehicleList);
#pragma endregion
#pragma region RENT
  RentList *rentList = NULL;
  printUserList(userList);
  Rent *rent = createRent("70-10-JK", 123, 10, vehicleList, userList, &rentList);
  bool isCreatedRent = createRentList(&rentList, *rent);
  printf("\nisCreated rent: %d", isCreatedRent);
  Rent *rent2 = createRent("20-03-LL", 1234, 15, vehicleList, userList, &rentList);
  bool isCreatedRent2 = createRentList(&rentList, *rent2);
  printf("\nisCreated rent2: %d", isCreatedRent2);
  printRentList(rentList);
  bool isDeletedRent = deleteRent(&rentList, 1, "70-10-JK", vehicleList);
  printf("\nisDeleted rent: %d", isDeletedRent);
  printRentList(rentList);
  bool isEditedRent = editRent(rentList, 2, *rent);
  printf("\nisEdited rent: %d", isEditedRent);

  storeVehicleListInBin(vehicleList);
  storeRentsInBin(rentList);
#pragma endregion
  VehicleList *sortedVehicleList = sortVehicleListDesc(&vehicleList);
  printf("sorted vehicle list:");
  printVehicleList(sortedVehicleList);
  printUserList(userList);
  storeUsersInBin(userList);
  // clear the userList data
  userList = NULL;
  printf("user list after clear: \n");
  printUserList(userList);
  setUsersData(&userList);
  printf("user list after setUsersData: \n");
  printUserList(userList);
  return 0;
}