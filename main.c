#include "./models/user.h"
#include "./models/vehicle.h"
#include "./models/rentals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main()
{
  printf("Program start!\n");

  UserList *userList = NULL;
  readUsersFromTxt(&userList);
  printUserList(userList);
  User *user = createUser(1, "name", "email", 1, 1, "password", 0, true);
  bool isCreated = createUserList(&userList, *user);
  printUserList(userList);
  printf("\nisCreated: %d", isCreated);
  printUserList(userList);
  User *userToEdit = createUser(1, "name2", "email2", 2, 2, "password2", 2, false);
  bool isEdited = editUser(userList, 1, *userToEdit);
  printUserList(userList);
  bool isDeleted = deleteUser(userList, 1);
  printf("\nisDeleted: %d", isDeleted);
  printUserList(userList);
  VehicleList *vehicleList = NULL;
  Vehicle *vehicle = createVehicle("registration", "type", 1, 1, true, "location");
  printf("%s", vehicle->registration);
  bool isCreatedVehicle = createVehicleList(&vehicleList, *vehicle);
  printf("\nisCreated vehicle: %d", isCreatedVehicle);
  printVehicleList(vehicleList);
  Vehicle *vehicleToEdit = createVehicle("registration", "type2", 2, 2, false, "location2");
  bool isEditedVehicle = editVehicle(vehicleList, "registration", *vehicleToEdit);
  printf("\nisEdited vehicle: %d", isEditedVehicle);
  printVehicleList(vehicleList);
  bool isDeletedVehicle = deleteVehicle(&vehicleList, "registration");
  printf("is deleted vehicle: %d", isDeletedVehicle);
  readVehiclesFromTxt(&vehicleList);
  printVehicleList(vehicleList);

  RentList *rentList = NULL;
  Rent *rent = createRent(1, 'a', 1, 1);
  bool isCreatedRent = createRentList(&rentList, *rent);
  printRentList(rentList);

  storeUsersInBin(userList);
  storeVehicleListInBin(vehicleList);
  return 0;
}