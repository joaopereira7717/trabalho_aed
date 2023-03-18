#include "./models/user.h"
#include "./models/vehicle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main()
{
  printf("Program start!\n");

  UserList *userList = NULL;
  read_users_initial_data(&userList);
  printUserList(userList);
  store_users_list(userList);
  User *user = createUser(1, "name", "email", 1, 1, "password", 0, true);
  User *user2 = createUser(2, "namee", "emaile", 1, 1, "passworde", 0, true);
  bool isCreated = createUserList(&userList, *user);
  printUserList(userList);
  bool isCreated2 = createUserList(&userList, *user2);
  printf("\nisCreated: %d", isCreated);
  printf("\nisCreated2: %d", isCreated2);
  printUserList(userList);
  User *userToEdit = createUser(1, "name2", "email2", 2, 2, "password2", 2, false);
  bool isEdited = editUser(userList, 1, *userToEdit);
  printUserList(userList);
  bool isDeleted = deleteUser(userList, 1);
  printf("\nisDeleted: %d", isDeleted);
  printUserList(userList);
  VehicleList *vehicleList = NULL;
  Vehicle *vehicle = createVehicle("matricula", "type", 1, 1, true, "location");
  printf("%s", vehicle->matricula);
  bool isCreatedVehicle = createVehicleList(&vehicleList, *vehicle);
  printf("\nisCreated vehicle: %d", isCreatedVehicle);
  printVehicleList(vehicleList);
  Vehicle *vehicleToEdit = createVehicle("matricula", "type2", 2, 2, false, "location2");
  bool isEditedVehicle = editVehicle(vehicleList, "matricula", *vehicleToEdit);
  printf("\nisEdited vehicle: %d", isEditedVehicle);
  printVehicleList(vehicleList);
  bool isDeletedVehicle = deleteVehicle(&vehicleList, "matricula");
  printf("is deleted vehicle: %d", isDeletedVehicle);
  read_vehicles_initial_data(&vehicleList);
  printVehicleList(vehicleList);
  return 0;
}