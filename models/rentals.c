#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include "./rentals.h"
#include "./user.h"
#include "./vehicle.h"

Rent *createRent(int id, char *vehicleRegistration, int userNif, int timeInMinutes, VehicleList *vehicleList, UserList *userList)
{

  bool userExists = searchUserByNif(userList, userNif);

  if (!userExists)
  {
    perror("User does not exist!");
    return NULL;
  }

  bool vehicleExists = searchVehicleByRegistration(vehicleList, vehicleRegistration);

  if (!vehicleExists)
  {
    perror("Vehicle does not exist!");
    return NULL;
  }

  bool isAvailable = isVehicleAvailable(vehicleList, vehicleRegistration);

  if (!isAvailable)
  {
    perror("Vehicle is not available!");
    return NULL;
  }

  Rent *rent = (Rent *)malloc(sizeof(Rent));
  rent->id = id;
  strcpy(rent->vehicleRegistration, vehicleRegistration);
  rent->userNif = userNif;
  rent->timeInMinutes = timeInMinutes;

  // edit vehicle availability
  bool availabilityChanged = editVehicleAvailability(vehicleList, vehicleRegistration, false);

  if (!availabilityChanged)
  {
    perror("Could not change vehicle availability!");
    return NULL;
  }

  return rent;
}

bool createRentList(RentList **headNode, Rent rent)
{
  RentList *new_node = (RentList *)malloc(sizeof(RentList));

  if (new_node == NULL)
  {
    perror("could not allocate memory!");
    return headNode;
  }

  new_node->rent = rent;
  new_node->next = *headNode;
  *headNode = new_node;
  return true;
}

void printRentList(RentList *headNode)
{
  RentList *current = headNode;
  while (current != NULL)
  {
    printf("\n--------------------");
    printf("\nRent:\n");
    printf("id: %d", current->rent.id);
    printf("\nvehicleRegistration: %s", current->rent.vehicleRegistration);
    printf("\nuserNif: %d", current->rent.userNif);
    printf("\ntimeInMinutes: %d", current->rent.timeInMinutes);
    printf("\n--------------------\n");
    current = current->next;
  }
  printf("\n");
}