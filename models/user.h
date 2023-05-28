/**
 * @file user.h
 * @brief File containing the functions to manage the users
 *
 * @author João Pereira
 * @date 2023-03-18
 */

#include <stdbool.h>
#pragma once

typedef struct UserList UserList;

typedef struct
{
  int nif;
  char name[50];
  char email[50];
  int phone;
  int zip;
  char password[50];
  int wallet;
  bool isManager;
} User;

struct UserList
{
  User user;
  UserList *next;
};

UserList *readUsersFromTxt(UserList **headNode);
UserList *setUsersData(UserList **headNode);
User *createUser(int nif, char name[50], char email[50], int phone, int zip, char password[50], int wallet, bool isManager);
bool createUserList(UserList **headNode, User user);
void printUserList(UserList *headNode);
bool editUser(UserList *usersList, int nif, User user);
bool deleteUser(UserList **usersList, int nif);
bool storeUsersInBin(UserList *headNode);
bool searchUserByNif(UserList *headNode, int nif);
bool updateUserWallet(UserList *headNode, int nif, int wallet);