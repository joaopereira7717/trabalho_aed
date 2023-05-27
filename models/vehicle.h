/**
 * @file vehicle.h
 * @brief File containing the functions to manage the vehicles
 *
 * @author João Pereira
 * @date 2023-03-18
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./routes.h"

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
Vehicle *createVehicle(char *registration, char *type, int battery, int cost, bool isInUse, char *location, Vertex *graph);
bool createVehicleList(VehicleList **headNode, Vehicle vehicle);
void printVehicleList(VehicleList *headNode);
bool editVehicle(VehicleList *headNode, char *registration, Vehicle vehicle);
bool deleteVehicle(VehicleList **headNode, char *registration);
bool storeVehicleListInBin(VehicleList *headNode);
bool searchVehicleByRegistration(VehicleList *headNode, char *registration);
bool isVehicleAvailable(VehicleList *headNode, char *registration);
bool editVehicleAvailability(VehicleList *headNode, char *registration, bool isInUse);
VehicleList *sortVehicleListDesc(VehicleList **headNode);
void *checkVehiclesInRadius(Vertex *g, VehicleList *vl, int city, float radius, char type[]);
void de_flag_visited_nodes(Vertex *graph);
void traverse_graph(Vertex *graph, VehicleList *vehicles, Vertex *current_node, float remaining_distance, char type[]);
void show_vehicle_by_type_on_geocode(VehicleList *head, char location[], char type[]);