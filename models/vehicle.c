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
  newVehicle->vehicle = vehicle;
  newVehicle->next = NULL;

  *headNode = newVehicle;
  return true;
}

void printVehicleList(VehicleList *headNode)
{
  VehicleList *current = headNode;
  while (current != NULL)
  {
    printf("\n%s\n", current->vehicle.matricula);
    current = current->next;
  }
}
