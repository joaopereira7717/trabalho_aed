#include <stdbool.h>
#pragma once

typedef struct RentList RentList;

typedef struct Rent
{
  int id;
  char vehicleRegistration;
  int userNif;
  int timeInMinutes;
} Rent;

struct RentList
{
  Rent rent;
  RentList *next;
};

Rent *createRent(int id, char vehicleRegistration, int userNif, int timeInMinutes);
void printRentList(RentList *headNode);
bool createRentList(RentList **headNode, Rent rent);