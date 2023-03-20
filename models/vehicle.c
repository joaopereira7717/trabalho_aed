/**
 * @file vehicle.c
 * @brief File containing the vehicle functions
 *
 * This file contains the implementation of functions related to the management of vehicles.
 * Functions include reading vehicles from a text file, creating a vehicle, creating a vehicle list,
 * printing a vehicle list, editing a vehicle, deleting a vehicle, storing a vehicle list in a binary file,
 * searching for a vehicle by registration, checking if a vehicle is available, and editing a vehicle's availability.
 *
 * @author João Pereira
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "./vehicle.h"

/**
 * @brief Reads vehicles from a text file and creates a vehicle list.
 *
 * This function reads vehicles from a text file and creates a linked list of vehicles.
 * The function takes a pointer to the head node of the list as a parameter and returns the head node.
 *
 * @param headNode A pointer to the head node of the vehicle list.
 * @return The head node of the vehicle list.
 */
VehicleList *readVehiclesFromTxt(VehicleList **headNode)
{
  FILE *pFile = NULL;

  pFile = fopen("./initial-data/vehicles.txt", "r");

  if (pFile == NULL)
  {
    perror("could not open file");
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

/**
 * @brief Creates a vehicle.
 *
 * This function creates a vehicle with the given parameters and returns a pointer to the vehicle.
 *
 * @param registration The registration number of the vehicle.
 * @param type The type of the vehicle.
 * @param battery The battery level of the vehicle.
 * @param cost The cost of the vehicle.
 * @param isInUse A boolean indicating whether the vehicle is in use or not.
 * @param location The location of the vehicle.
 * @return A pointer to the created vehicle.
 */
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

/**
 * @brief Creates a vehicle list.
 *
 * This function creates a new node in the vehicle list with the given vehicle and adds it to the head of the list.
 * The function takes a pointer to the head node of the list and the vehicle to be added as parameters.
 * The function returns true if the node was successfully created and added to the list, false otherwise.
 *
 * @param headNode A pointer to the head node of the vehicle list.
 * @param vehicle The vehicle to be added to the list.
 * @return True if the node was successfully created and added to the list, false otherwise.
 */
bool createVehicleList(VehicleList **headNode, Vehicle vehicle)
{
  VehicleList *newVehicle = (VehicleList *)malloc(sizeof(VehicleList));
  if (newVehicle == NULL)
  {
    perror("could not allocate memory!");
    return headNode;
  }
  newVehicle->vehicle = vehicle;
  newVehicle->next = *headNode;

  *headNode = newVehicle;
  return true;
}

/**
 * @brief Prints a vehicle list.
 *
 * This function prints the vehicles in the linked list.
 * The function takes a pointer to the head node of the list as a parameter.
 *
 * @param headNode A pointer to the head node of the vehicle list.
 */
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

/**
 * @brief Edits a vehicle in the list.
 *
 * This function searches for a vehicle with the given registration number in the list and replaces it with the given vehicle.
 * The function takes a pointer to the head node of the list, the registration number of the vehicle to be edited, and the new vehicle as parameters.
 * The function returns true if the vehicle was successfully edited, false otherwise.
 *
 * @param headNode A pointer to the head node of the vehicle list.
 * @param registration The registration number of the vehicle to be edited.
 * @param vehicle The new vehicle to replace the old one.
 * @return True if the vehicle was successfully edited, false otherwise.
 */
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

/**
 * @brief Deletes a vehicle from the list.
 *
 * This function searches for a vehicle with the given registration number in the list and deletes it.
 * The function takes a pointer to the head node of the list and the registration number of the vehicle to be deleted as parameters.
 * The function returns true if the vehicle was successfully deleted, false otherwise.
 *
 * @param headNode A pointer to the head node of the vehicle list.
 * @param registration The registration number of the vehicle to be deleted.
 * @return True if the vehicle was successfully deleted, false otherwise.
 */
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

/**
 * @brief Stores the vehicle list in a binary file.
 *
 * This function stores the vehicles in the linked list in a binary file.
 * The function takes a pointer to the head node of the list as a parameter.
 * The function returns true if the list was successfully stored in the file, false otherwise.
 *
 * @param headNode A pointer to the head node of the vehicle list.
 * @return True if the list was successfully stored in the file, false otherwise.
 */
bool storeVehicleListInBin(VehicleList *headNode)
{
  FILE *pFile = NULL;
  VehicleList *current_node = headNode;

  pFile = fopen("./saved-data/vehicles.bin", "wb");

  if (pFile == NULL)
  {
    perror("could not open file");
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

/**
 * @brief Searches for a vehicle by registration number.
 *
 * This function searches for a vehicle with the given registration number in the list.
 * The function takes a pointer to the head node of the list and the registration number of the vehicle to be searched as parameters.
 * The function returns true if the vehicle was found, false otherwise.
 *
 * @param headNode A pointer to the head node of the vehicle list.
 * @param registration The registration number of the vehicle to be searched.
 * @return True if the vehicle was found, false otherwise.
 */
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

/**
 * @brief Checks if a vehicle is available.
 *
 * This function checks if a vehicle with the given registration number is available (not in use).
 * The function takes a pointer to the head node of the list and the registration number of the vehicle to be checked as parameters.
 * The function returns true if the vehicle is available, false otherwise.
 *
 * @param headNode A pointer to the head node of the vehicle list.
 * @param registration The registration number of the vehicle to be checked.
 * @return True if the vehicle is available, false otherwise.
 */
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

/**
 * @brief Edits a vehicle's availability.
 *
 * This function searches for a vehicle with the given registration number in the list and sets its availability to the given value.
 * The function takes a pointer to the head node of the list, the registration number of the vehicle to be edited, and a boolean indicating the new availability as parameters.
 * The function returns true if the vehicle's availability was successfully edited, false otherwise.
 *
 * @param headNode A pointer to the head node of the vehicle list.
 * @param registration The registration number of the vehicle to be edited.
 * @param isInUse A boolean indicating the new availability of the vehicle.
 * @return True if the vehicle's availability was successfully edited, false otherwise.
 */
bool editVehicleAvailability(VehicleList *headNode, char *registration, bool isInUse)
{
  VehicleList *current = headNode;
  while (current != NULL)
  {
    if (strcmp(current->vehicle.registration, registration) == 0)
    {
      current->vehicle.isInUse = isInUse;
      return true;
    }
    current = current->next;
  }
  return false;
}