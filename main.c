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

  Vertex *graf = createRoute();
  /* graf = routesReadTxt(graf, &res, &tot);
  showRoutes(graf); */

  Vertex *newVertex = createRouteVertex("Braga", tot);
  if (newVertex != NULL)
  {
    graf = insertRouteVertex(graf, newVertex, &res);
    tot++;
  }

  newVertex = createRouteVertex("Porto", tot);
  if (newVertex != NULL)
  {
    graf = insertRouteVertex(graf, newVertex, &res);
    tot++;
  }

  newVertex = createRouteVertex("Fafe", tot);
  if (newVertex != NULL)
  {
    graf = insertRouteVertex(graf, newVertex, &res);
    tot++;
  }

  newVertex = createRouteVertex("Lisboa", tot);
  if (newVertex != NULL)
  {
    graf = insertRouteVertex(graf, newVertex, &res);
    tot++;
  }

  newVertex = createRouteVertex("Barcelos", tot);
  if (newVertex != NULL)
  {
    graf = insertRouteVertex(graf, newVertex, &res);
    tot++;
  }

  showRoutes(graf);

  // Create adjacents
  graf = insertAdjacentVertex(graf, "Braga", "Porto", 35, &res);
  graf = insertAdjacentVertex(graf, "Braga", "Fafe", 15, &res);
  graf = insertAdjacentVertex(graf, "Fafe", "Porto", 60, &res);
  graf = insertAdjacentVertex(graf, "Porto", "Lisboa", 250, &res);
  graf = insertAdjacentVertex(graf, "Lisboa", "Barcelos", 270, &res);

  showRoutes(graf);

  int pathCount = 0;
  int x = countPaths(graf, 0, 2, pathCount);
  printf("\nExists %d Paths between %d and %d\n", x, 0, 2);

  int countPath = 0;
  x = countPathsVertexsName(graf, "Braga", "Porto", countPath);
  x = countPathsVertexsName(graf, "Braga", "Fafe", countPath);

  x = countPaths(graf, 0, 1, 0);

  printf("\nExists Path?\n");
  bool existe = depthFirstSearchRec(graf, 3, 6);
  printf(" Exists Path between %d and %d: %s\n", 3, 6, (existe == true ? "Yes" : "No"));

  graf = resetVisitedVertex(graf);

  existe = depthFirstSearchNamesRec(graf, "Braga", "Porto");
  printf(" Exists Path between %s and %s: %s\n", "Braga", "Porto", (existe == true ? "Yes" : "No"));

#pragma region FICHEIROS

  int res1 = saveGraph(graf, "./saved-data/Vertexs.bin");
  if (res1 > 0)
    puts("\nRoutes saved");

  graf = destroyRoutes(graf);

  puts("\nRoutes in memory:");
  showRoutes(graf);

  graf = loadGraph(graf, "./saved-data/Vertexs.bin", &res);
  if (graf != NULL)
    puts("\nVertex from file\n");
  showRoutes(graf);

  puts("\nRead adj from the file\n");
  graf = loadAdj(graf, &res);

  showRoutes(graf);

#pragma endregion

  Best b = bestPath(graf, tot - 1, 0);
  showAllPath(b, tot - 1, 0);

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
  printf("\nIs there any vehicle in a radius of %d centered in %s? \n", 50, "Braga");
  checkVehiclesInRadius(graf, vehicleList, 0, 50, "trotinete");
#pragma endregion
  /* #pragma region RENT
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
    userList = NULL;
    printf("user list after clear: \n");
    printUserList(userList);
    setUsersData(&userList);
    printf("user list after setUsersData: \n");
    printUserList(userList); */
  Vertex *start_node = searchVertexCod(graf, 0);
  printVehicleList(vehicleList);
  resetVisitedVertex(graf);
  VehicleList *collected_vehicles = tsp_truck(start_node, &vehicleList, 1);
  printf("collected vehicles: \n");
  printVehicleList(collected_vehicles);
  return 0;
}