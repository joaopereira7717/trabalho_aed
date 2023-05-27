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
#include <limits.h>
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
Vehicle *createVehicle(char *registration, char *type, int battery, int cost, bool isInUse, char *location, Vertex *graf)
{
  Vehicle *vehicle = (Vehicle *)malloc(sizeof(Vehicle));
  strcpy(vehicle->registration, registration);
  strcpy(vehicle->type, type);
  vehicle->battery = battery;
  vehicle->cost = cost;
  vehicle->isInUse = isInUse;
  strcpy(vehicle->location, location);

  // check if the location is in the graph on routes with SearchCodVertex if not, return NULL
  if (searchCodVertex(graf, location) < 0)
  {
    printf("\nThe location '%s' is not in the graph of routes!\n", location);
    return NULL;
  }

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

// sort the vehicles list by battery level in descending order
VehicleList *sortVehicleListDesc(VehicleList **headNode)
{
  VehicleList *current = *headNode;
  VehicleList *index = NULL;
  Vehicle temp;

  if (*headNode == NULL)
  {
    return NULL;
  }
  else
  {
    while (current != NULL)
    {
      index = current->next;
      while (index != NULL)
      {
        if (current->vehicle.battery < index->vehicle.battery)
        {
          temp = current->vehicle;
          current->vehicle = index->vehicle;
          index->vehicle = temp;
        }
        index = index->next;
      }
      current = current->next;
    }
  }
  return *headNode;
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
 * The function takes a pointer to the head node of the list, the registration number of the vehicle to be edited,
 * and a boolean indicating the new availability as parameters.
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

/**
 * @brief Sorts the vehicle list by location.
 *
 * This function sorts the vehicle list by location.
 * The function takes a pointer to the head node of the list and the location to sort by as parameters.
 * The function returns a pointer to the head node of the sorted list.
 *
 * @param headNode A pointer to the head node of the vehicle list.
 * @param location The location to sort by.
 * @return A pointer to the head node of the sorted list.
 */
VehicleList *sortVehiclesByLocation(VehicleList *headNode, char *location)
{
  VehicleList *current = headNode;
  VehicleList *newHead = NULL;
  VehicleList *newTail = NULL;
  while (current != NULL)
  {
    if (strcmp(current->vehicle.location, location) == 0)
    {
      if (newHead == NULL)
      {
        newHead = current;
        newTail = current;
      }
      else
      {
        newTail->next = current;
        newTail = current;
      }
    }
    current = current->next;
  }
  if (newTail != NULL)
  {
    newTail->next = NULL;
  }
  return newHead;
}

// create a function that checks if there is any vehicle in a given radius
/**
 * @brief checkVehiclesInRadius - Finds all vehicles of a given type within a certain radius of a city
 * @g: Pointer to the graph of cities and their connections
 * @vl: Pointer to the linked list of vehicles
 * @city: The code of the city to start the search from
 * @radius: The maximum distance from the starting city to search for vehicles
 * @type: The type of vehicle to search for
 *
 * This function finds all vehicles of a given type within a certain radius of a city. It starts the search from the
 * specified city and traverses the graph of cities and their connections to find all cities within the given radius.
 * For each city found, it searches the linked list of vehicles to find all vehicles of the given type that are located
 * in that city. It then prints out information about each vehicle found.
 *
 * Return: NULL
 */
void *checkVehiclesInRadius(Vertex *g, VehicleList *vl, int city, float radius, char type[])
{
  if (radius < 0)
  {
    return NULL;
  }

  Vertex *start_node = NULL;

  // Find the starting node for the search
  Vertex *current_node = g;
  while (current_node != NULL)
  {
    if (current_node->cod == city)
    {
      start_node = current_node;
      break;
    }
    current_node = current_node->next;
  }

  // If the starting node is not found, print an error message and return NULL
  if (start_node == NULL)
  {
    printf("Error: Start node not found.\n");
    return NULL;
  }

  // Mark all nodes in the graph as unvisited
  markAsVisited(g);

  // Traverse the graph to find all cities within the given radius
  traverse_graph(g, vl, start_node, radius, type);
  return NULL;
}

/**
 * @brief markAsVisited - Marks all nodes in the graph as unvisited
 * @graph: Pointer to the graph of cities and their connections
 *
 * This function marks all nodes in the graph as unvisited by setting their visited flag to false.
 *
 * Return: void
 */
void markAsVisited(Vertex *graph)
{
  Vertex *node = graph;
  while (node != NULL)
  {
    node->visited = false;
    node = node->next;
  }
}

/**
 * @brief traverse_graph - Traverses the graph to find all cities within a certain radius
 * @graph: Pointer to the graph of cities and their connections
 * @vehicles: Pointer to the linked list of vehicles
 * @current_node: Pointer to the current node being visited
 * @remaining_distance: The remaining distance that can be traveled from the starting city
 * @type: The type of vehicle to search for
 *
 * This function traverses the graph of cities and their connections to find all cities within a certain radius of the
 * starting city. For each city found, it searches the linked list of vehicles to find all vehicles of the given type
 * that are located in that city. It then prints out information about each vehicle found.
 *
 * Return: void
 */
void traverse_graph(Vertex *graph, VehicleList *vehicles, Vertex *current_node, float remaining_distance, char type[])
{
  if (remaining_distance < 0)
  {
    return;
  }

  // Mark the current node as visited
  current_node->visited = true;

  // Search the linked list of vehicles to find all vehicles of the given type that are located in the current city
  show_vehicle_by_type_on_geocode(vehicles, current_node->city, type);

  // Traverse all adjacent nodes that have not been visited and are within the remaining distance
  Adj *edge = current_node->adjacents;
  while (edge != NULL)
  {
    Vertex *adjacentNode = graph;
    while (adjacentNode != NULL)
    {
      if (adjacentNode->cod == edge->cod && !adjacentNode->visited && edge->dist <= remaining_distance)
      {
        float updated_distance = remaining_distance - edge->dist;
        traverse_graph(graph, vehicles, adjacentNode, updated_distance, type);
      }

      adjacentNode = adjacentNode->next;
    }

    edge = edge->next;
  }
}

/**
 * @brief Searches the linked list of vehicles for all vehicles of a given type in a city
 * @head: Pointer to the head of the linked list of vehicles
 * @location: The name of the city to search for vehicles in
 * @type: The type of vehicle to search for
 *
 * This function searches the linked list of vehicles for all vehicles of a given type that are located in a city with
 * the given name. It then prints out information about each vehicle found.
 *
 * Return: void
 */
void show_vehicle_by_type_on_geocode(VehicleList *head, char location[], char type[])
{
  if (location[0] == '\0')
  {
    perror("Error: location is empty\n");
    return;
  }

  if (type[0] == '\0')
  {
    perror("Error: type is empty\n");
    return;
  }

  VehicleList *current_vehicle = head;

  while (current_vehicle != NULL)
  {
    if (strcmp(current_vehicle->vehicle.location, location) == 0 && strcmp(current_vehicle->vehicle.type, type) == 0)
    {
      printf("\nVehicle registration: %s\n", current_vehicle->vehicle.registration);
      printf("Vehicle Type: %s\n", current_vehicle->vehicle.type);
      printf("Vehicle Location: %s\n", current_vehicle->vehicle.location);
      printf("Vehicle Price: %d\n", current_vehicle->vehicle.cost);
    }
    current_vehicle = current_vehicle->next;
  }
}

VehicleList *tsp_truck(Vertex *graph, VehicleList **vehicle_list, int truck_capacity)
{
  int run_number = 1;
  int collected_count = 0;

  Vertex *start_node = graph;
  VehicleList *vehicles_collected = NULL;
  Vertex *current_node = graph;
  printf("current node location -> %s\n", current_node->city);
  // loop to visit nodes in the graph
  while (current_node != NULL)
  {
    if (!current_node->visited)
    {
      VehicleList *current_vehicle = *vehicle_list;

      // iterate through the vehicle list and collect eligible vehicles
      while (current_vehicle != NULL && collected_count < truck_capacity)
      {
        bool is_legible = check_is_legible_for_truck(current_vehicle);
        bool is_same_location = strcmp(current_vehicle->vehicle.location, current_node->city) == 0;

        if (is_legible && is_same_location)
        {
          collected_count++;
          head_insertion_vehicle_list(&vehicles_collected, current_vehicle->vehicle);

          printf("Run %d: Vehicle %s collected at %s\n", run_number, current_vehicle->vehicle.registration, current_vehicle->vehicle.location);
        }

        current_vehicle = current_vehicle->next;
      }

      current_node->visited = true;

      if (collected_count == truck_capacity)
      {
        collected_count = 0;
        run_number++;

        // reset the current node to the start node and move the collected
        // vehicles to the start node
        current_node = start_node;

        vehicles_collected->vehicle.battery = 100;
        strcpy(vehicles_collected->vehicle.location, start_node->city);

        markAsVisited(graph);
      }

      printf("current node location -> %s\n", current_node->city);
    }

    // find the next unvisited node with the shortest distance from the current node
    Vertex *next_node = NULL;
    Adj *edges = current_node->adjacents;
    int shortest_distance = INT_MAX;

    while (edges != NULL)
    {
      Vertex *adjacent_node = searchVertexCod(graph, edges->cod);

      // if the adjacent node was not visited and has a shorter distance, update the next node
      if (adjacent_node != NULL && !adjacent_node->visited && edges->dist < shortest_distance)
      {
        shortest_distance = edges->dist;
        next_node = adjacent_node;
      }

      edges = edges->next;
    }

    current_node = next_node;
  }

  markAsVisited(graph);

  return vehicles_collected;
}

bool check_is_legible_for_truck(VehicleList *vehicle)
{
  char typeTroti[50] = "trotinete";
  bool is_trotti = strcmp(vehicle->vehicle.type, typeTroti) == 0;
  bool has_low_battery = vehicle->vehicle.battery < 50;
  bool is_not_rented = vehicle->vehicle.isInUse == false;

  return is_trotti && has_low_battery && is_not_rented;
}

bool head_insertion_vehicle_list(VehicleList **head, Vehicle new_vehicle)
{
  VehicleList *new_node = (VehicleList *)malloc(sizeof(VehicleList));

  if (new_node == NULL)
  {
    perror("Could not allocate memory!");
    return head;
  }

  new_node->vehicle = new_vehicle;

  new_node->next = *head;
  *head = new_node;

  return true;
}