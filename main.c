#include "./models/user.h"
#include "./models/vehicle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main()
{
  UserList *userList = NULL;
  User *user = createUser(1, "name", "email", 1, 1, "password", 0, true);
  printf("%d", user->nif);
  bool isCreated = createUserList(&userList, *user);
  printf("\nisCreated: %d", isCreated);
  printUserList(userList);
  VehicleList *vehicleList = NULL;
  Vehicle *vehicle = createVehicle("matricula", "type", 1, 1, true, "location");
  printf("%s", vehicle->matricula);
  bool isCreatedVehicle = createVehicleList(&vehicleList, *vehicle);
  printf("\nisCreated vehicle: %d", isCreatedVehicle);
  printVehicleList(vehicleList);
  return 0;
}