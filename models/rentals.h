#include <stdbool.h>
#include "./user.h"
#include "./vehicle.h"
#pragma once

typedef struct RentList RentList;

typedef struct Rent
{
  int id;
  char vehicleRegistration[50];
  int userNif;
  int timeInMinutes;
} Rent;

struct RentList
{
  Rent rent;
  RentList *next;
};

Rent *createRent(char *vehicleRegistration, int userNif, int timeInMinutes, VehicleList *vehicleList, UserList *userList, RentList **rentList);
void printRentList(RentList *headNode);
bool createRentList(RentList **headNode, Rent rent);
int countRents(RentList *headNode);
bool deleteRent(RentList **headNode, int id, char *vehicleRegistration, VehicleList *vehicleList);
bool editRent(RentList *headNode, int id, Rent rent);
bool storeRentsInBin(RentList *headNode);