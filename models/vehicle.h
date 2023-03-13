#include <stdbool.h>
#pragma once

typedef struct VehicleList VehicleList;

typedef struct Vehicle
{
  char matricula[50];
  char type[50];
  int battery;
  int cost;
  bool isInUse;
  char location[50];
} Vehicle;

struct VehicleList
{
  Vehicle vehicle;
  VehicleList *next;
};
Vehicle *createVehicle(char *matricula, char *type, int battery, int cost, bool isInUse, char *location);
bool createVehicleList(VehicleList **headNode, Vehicle vehicle);
void printVehicleList(VehicleList *headNode);