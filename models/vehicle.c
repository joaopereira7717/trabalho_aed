#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "./vehicle.h"

Vehicle *createVehicle(char *matricula, char *type, int battery, int cost, bool isInUse, char *location)
{
  Vehicle *vehicle = (Vehicle *)malloc(sizeof(Vehicle));
  strcpy(vehicle->matricula, matricula);
  strcpy(vehicle->type, type);
  vehicle->battery = battery;
  vehicle->cost = cost;
  vehicle->isInUse = isInUse;
  strcpy(vehicle->location, location);
  return vehicle;
}

bool createVehicleList(VehicleList **headNode, Vehicle vehicle)
{
  VehicleList *newVehicle = (VehicleList *)malloc(sizeof(VehicleList));
  if (newVehicle == NULL)
  {
    printf("could not allocate memory!");
    return headNode;
  }
  newVehicle->vehicle = vehicle;
  newVehicle->next = *headNode;

  *headNode = newVehicle;
  return true;
}

void printVehicleList(VehicleList *headNode)
{
  VehicleList *current = headNode;
  while (current != NULL)
  {
    printf("\n--------------------");
    printf("\nVehicle:");
    printf("\nMatricula: %s\n", current->vehicle.matricula);
    printf("Type:%s \n", current->vehicle.type);
    printf("Battery: %d\n", current->vehicle.battery);
    printf("Cost: %d\n", current->vehicle.cost);
    printf("IsInUse: %d\n", current->vehicle.isInUse);
    printf("Location: %s\n", current->vehicle.location);
    printf("\n--------------------");
    current = current->next;
  }
}

bool editVehicle(VehicleList *headNode, char *matricula, Vehicle vehicle)
{
  VehicleList *current = headNode;
  while (current != NULL)
  {
    if (strcmp(current->vehicle.matricula, matricula) == 0)
    {
      current->vehicle = vehicle;
      return true;
    }
    current = current->next;
  }
  return false;
}

// delete vehicle
bool deleteVehicle(VehicleList **headNode, char *matricula)
{
  VehicleList *current = *headNode;
  VehicleList *previous = NULL;
  while (current != NULL)
  {
    if (strcmp(current->vehicle.matricula, matricula) == 0)
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
      return true;
    }
    previous = current;
    current = current->next;
  }
  return false;
}
