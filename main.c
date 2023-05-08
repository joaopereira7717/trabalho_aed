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
#include "./models/user.h"
#include "./models/vehicle.h"
#include "./models/rentals.h"

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