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
    printf("\n%s\n", current->vehicle.matricula);
    printf("%s\n", current->vehicle.type);
    printf("%d\n", current->vehicle.battery);
    printf("%d\n", current->vehicle.cost);
    printf("%d\n", current->vehicle.isInUse);
    printf("%s\n", current->vehicle.location);
    printf("\n--------------------");
    current = current->next;
  }
}
