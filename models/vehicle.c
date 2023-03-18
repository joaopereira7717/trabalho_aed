#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "./vehicle.h"

VehicleList *readVehiclesFromTxt(VehicleList **headNode)
{
  FILE *pFile = NULL;

  pFile = fopen("./initial-data/vehicles.txt", "r");

  if (pFile == NULL)
  {
    printf("could not open file");
    return NULL;
  }

  Vehicle vehicle;

  while (!feof(pFile))
  {
    int isInUseInt;
    fscanf(pFile, "%[^;];%[^;];%d;%d;%d;%[^;\n]\n", vehicle.registration, vehicle.type, &vehicle.battery, &vehicle.cost, &isInUseInt, vehicle.location);
    vehicle.isInUse = (bool)isInUseInt;
    createVehicleList(headNode, vehicle);
  }

  fclose(pFile);
  return *headNode;
}

Vehicle *createVehicle(char *registration, char *type, int battery, int cost, bool isInUse, char *location)
{
  Vehicle *vehicle = (Vehicle *)malloc(sizeof(Vehicle));
  strcpy(vehicle->registration, registration);
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
    printf("\nregistration: %s\n", current->vehicle.registration);
    printf("Type:%s \n", current->vehicle.type);
    printf("Battery: %d\n", current->vehicle.battery);
    printf("Cost: %d\n", current->vehicle.cost);
    printf("IsInUse: %d\n", current->vehicle.isInUse);
    printf("Location: %s\n", current->vehicle.location);
    printf("\n--------------------");
    current = current->next;
  }
}

bool editVehicle(VehicleList *headNode, char *registration, Vehicle vehicle)
{
  VehicleList *current = headNode;
  while (current != NULL)
  {
    if (strcmp(current->vehicle.registration, registration) == 0)
    {
      current->vehicle = vehicle;
      return true;
    }
    current = current->next;
  }
  return false;
}

// delete vehicle
bool deleteVehicle(VehicleList **headNode, char *registration)
{
  VehicleList *current = *headNode;
  VehicleList *previous = NULL;
  while (current != NULL)
  {
    if (strcmp(current->vehicle.registration, registration) == 0)
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

bool storeVehicleListInBin(VehicleList *headNode)
{
  FILE *pFile = NULL;
  VehicleList *current_node = headNode;

  pFile = fopen("./saved-data/vehicles.bin", "wb");

  if (pFile == NULL)
  {
    printf("could not open file");
    return false;
  }

  while (current_node != NULL)
  {
    fwrite(&current_node->vehicle, sizeof(Vehicle), 1, pFile);
    current_node = current_node->next;
  }

  fclose(pFile);
  return true;
}

bool searchVehicleByRegistration(VehicleList *headNode, char *registration)
{
  VehicleList *current = headNode;
  while (current != NULL)
  {
    if (strcmp(current->vehicle.registration, registration) == 0)
    {
      return true;
    }
    current = current->next;
  }
  return false;
}

bool isVehicleAvailable(VehicleList *headNode, char *registration)
{
  VehicleList *current = headNode;
  while (current != NULL)
  {
    if (strcmp(current->vehicle.registration, registration) == 0)
    {
      if (current->vehicle.isInUse == false)
      {
        return true;
      }
    }
    current = current->next;
  }
  return false;
}