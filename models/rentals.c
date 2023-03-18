#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include "./rentals.h"
#include "./user.h"
#include "./vehicle.h"

Rent *createRent(char *vehicleRegistration, int userNif, int timeInMinutes, VehicleList *vehicleList, UserList *userList, RentList **rentList)
{
  Rent *rent = (Rent *)malloc(sizeof(Rent));
  printf("Creating rent...\n");
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

  rent->id = countRents(*rentList);
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

bool deleteRent(RentList **headNode, int id, char *vehicleRegistration, VehicleList *vehicleList)
{
  RentList *current = *headNode;
  RentList *previous = NULL;

  while (current != NULL)
  {
    if (current->rent.id == id)
    {
      if (previous == NULL)
      {
        *headNode = current->next;
      }
      else
      {
        previous->next = current->next;
      }
      free(current);
      // change the vehicle availability
      bool availabilityChanged = editVehicleAvailability(vehicleList, vehicleRegistration, true);
      if (!availabilityChanged)
      {
        perror("Could not change vehicle availability!");
        return NULL;
      }
      return true;
    }
    previous = current;
    current = current->next;
  }
  return false;
}

int countRents(RentList *headNode)
{
  int count = 0;
  RentList *current = headNode;
  while (current != NULL)
  {
    count++;
    current = current->next;
  }
  return count;
}

bool editRent(RentList *headNode, int id, Rent rent)
{
  RentList *current = headNode;
  while (current != NULL)
  {
    if (current->rent.id == id)
    {
      current->rent = rent;
      return true;
    }
    current = current->next;
  }
  return false;
}