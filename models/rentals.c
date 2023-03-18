#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "./rentals.h"
#include "./user.h"
#include "./vehicle.h"

Rent *createRent(int id, char vehicleRegistration, int userNif, int timeInMinutes)
{

  bool userExists = searchUserByNif(userNif);

  if (!userExists)
  {
    printf("User does not exist!");
    return NULL;
  }

  bool vehicleExists = searchVehicleByRegistration(vehicleRegistration);

  if (!vehicleExists)
  {
    printf("Vehicle does not exist!");
    return NULL;
  }

  bool isVehicleAvailable = searchVehicleAvailability(vehicleRegistration);

  if (!isVehicleAvailable)
  {
    printf("Vehicle is not available!");
    return NULL;
  }

  Rent *rent = (Rent *)malloc(sizeof(Rent));
  rent->id = id;
  rent->vehicleRegistration = vehicleRegistration;
  rent->userNif = userNif;
  rent->timeInMinutes = timeInMinutes;
  return rent;
}

bool createRentList(RentList **headNode, Rent rent)
{
  RentList *new_node = (RentList *)malloc(sizeof(RentList));

  if (new_node == NULL)
  {
    printf("could not allocate memory!");
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
    printf("\nvehicleRegistration: %c", current->rent.vehicleRegistration);
    printf("\nuserNif: %d", current->rent.userNif);
    printf("\ntimeInMinutes: %d", current->rent.timeInMinutes);
    printf("\n--------------------\n");
    current = current->next;
  }
  printf("\n");
}