/**
 * @file rentals.c
 * @brief File containing the functions to manage the rentals
 *
 * This file contains the implementation of functions to manage the rentals, such as creating a new rent,
 * creating a rent list, printing the rent list, deleting a rent, counting the number of rents, editing a rent,
 * and storing the rents in a binary file.
 *
 * @author João Pereira
 * @date 2023-03-18
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include "./rentals.h"
#include "./user.h"
#include "./vehicle.h"

/**
 * @brief Creates a new rent
 *
 * This function creates a new rent with the given vehicle registration, user NIF, and time in minutes.
 * It also checks if the user and vehicle exist and if the vehicle is available. If any of these conditions
 * are not met, the function returns NULL. Otherwise, it creates a new rent and returns it.
 *
 * @param vehicleRegistration The registration of the vehicle to be rented
 * @param userNif The NIF of the user renting the vehicle
 * @param timeInMinutes The time in minutes the vehicle will be rented for
 * @param vehicleList The list of vehicles
 * @param userList The list of users
 * @param rentList The list of rents
 * @return A pointer to the newly created rent, or NULL if any of the conditions are not met
 */
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
  int price = calculateRentPrice(vehicleList, vehicleRegistration, timeInMinutes);

  // edit vehicle availability
  bool availabilityChanged = editVehicleAvailability(vehicleList, vehicleRegistration, false);
  if (!availabilityChanged)
  {
    printf("Could not change vehicle availability!");
    return NULL;
  }
  // update user wallet
  bool payed = updateUserWallet(userList, userNif, -price);
  printf("Price: %d\n", price);

  if (!payed)
  {
    printf("Could not pay!");
    return NULL;
  }

  printf("Rent created!\n");

  return rent;
}

/**
 * @brief Creates a new node in the rent list
 *
 * This function creates a new node in the rent list with the given rent. It returns true if the node was
 * successfully created, or false otherwise.
 *
 * @param headNode A pointer to the head node of the rent list
 * @param rent The rent to be added to the list
 * @return True if the node was successfully created, or false otherwise
 */
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

/**
 * @brief Prints the rent list
 *
 * This function prints the rent list, showing the ID, vehicle registration, user NIF, and time in minutes
 * for each rent in the list.
 *
 * @param headNode A pointer to the head node of the rent list
 */
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

/**
 * @brief Deletes a rent from the rent list
 *
 * This function deletes a rent from the rent list with the given ID and vehicle registration. It also changes
 * the availability of the vehicle to true. It returns true if the rent was successfully deleted, or false
 * otherwise.
 *
 * @param headNode A pointer to the head node of the rent list
 * @param id The ID of the rent to be deleted
 * @param vehicleRegistration The registration of the vehicle to be returned
 * @param vehicleList The list of vehicles
 * @return True if the rent was successfully deleted, or false otherwise
 */
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

/**
 * @brief Counts the number of rents in the rent list
 *
 * This function counts the number of rents in the rent list and returns the count.
 *
 * @param headNode A pointer to the head node of the rent list
 * @return The number of rents in the rent list
 */
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

/**
 * @brief Edits a rent in the rent list
 *
 * This function edits a rent in the rent list with the given ID. It replaces the rent with the given rent
 * parameter. It returns true if the rent was successfully edited, or false otherwise.
 *
 * @param headNode A pointer to the head node of the rent list
 * @param id The ID of the rent to be edited
 * @param rent The new rent to replace the old one
 * @return True if the rent was successfully edited, or false otherwise
 */
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

/**
 * @brief Stores the rents in a binary file
 *
 * This function stores the rents in a binary file named "rents.bin" in the "saved-data" directory. It returns
 * true if the rents were successfully stored, or false otherwise.
 *
 * @param headNode A pointer to the head node of the rent list
 * @return True if the rents were successfully stored, or false otherwise
 */
bool storeRentsInBin(RentList *headNode)
{
  FILE *pFile = NULL;
  RentList *current_node = headNode;

  pFile = fopen("./saved-data/rents.bin", "wb");

  if (pFile == NULL)
  {
    perror("could not open file");
    return false;
  }

  while (current_node != NULL)
  {
    fwrite(&current_node->rent, sizeof(Rent), 1, pFile);
    current_node = current_node->next;
  }

  fclose(pFile);
  return true;
}

int calculateRentPrice(VehicleList *vehicleList, char *vehicleRegistration, int timeInMinutes)
{
  VehicleList *current = vehicleList;
  while (current != NULL)
  {
    if (strcmp(current->vehicle.registration, vehicleRegistration) == 0)
    {
      return current->vehicle.cost * timeInMinutes;
    }
    current = current->next;
  }
  return 0;
}