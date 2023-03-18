#include <stdbool.h>
#pragma once

typedef struct VehicleList VehicleList;

typedef struct Vehicle
{
  char registration[50];
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

VehicleList *readVehiclesFromTxt(VehicleList **headNode);
Vehicle *createVehicle(char *registration, char *type, int battery, int cost, bool isInUse, char *location);
bool createVehicleList(VehicleList **headNode, Vehicle vehicle);
void printVehicleList(VehicleList *headNode);
bool editVehicle(VehicleList *headNode, char *registration, Vehicle vehicle);
bool deleteVehicle(VehicleList **headNode, char *registration);
bool storeVehicleListInBin(VehicleList *headNode);
bool searchVehicleByRegistration(VehicleList *headNode, char *registration);
bool isVehicleAvailable(VehicleList *headNode, char *registration);
bool editVehicleAvailability(VehicleList *headNode, char *registration, bool isInUse);