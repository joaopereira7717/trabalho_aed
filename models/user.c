#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "./user.h"

UserList *readUsersFromTxt(UserList **headNode)
{
  FILE *pFile = NULL;

  pFile = fopen("./initial-data/users.txt", "r");

  if (pFile == NULL)
  {
    perror("could not open file");
    return NULL;
  }

  User user;

  while (!feof(pFile))
  {
    int isManagerInt;
    fscanf(pFile, "%d;%[^;];%[^;];%d;%d;%[^;];%d;%d\n", &user.nif, user.name, user.email, &user.phone, &user.zip, user.password, &user.wallet, &isManagerInt);
    user.isManager = (bool)isManagerInt;
    createUserList(headNode, user);
  }

  fclose(pFile);
  return *headNode;
}

User *createUser(int nif, char name[50], char email[50], int phone, int zip, char password[50], int wallet, bool isManager)
{
  User *user = (User *)malloc(sizeof(User));
  user->nif = nif;
  strcpy(user->name, name);
  strcpy(user->email, email);
  user->phone = phone;
  user->zip = zip;
  strcpy(user->password, password);
  user->wallet = wallet;
  user->isManager = isManager;
  return user;
}

bool createUserList(UserList **headNode, User user)
{
  UserList *new_node = (UserList *)malloc(sizeof(UserList));

  if (new_node == NULL)
  {
    perror("could not allocate memory!");
    return headNode;
  }

  new_node->user = user;
  new_node->next = *headNode;
  *headNode = new_node;

  return true;
}

void printUserList(UserList *headNode)
{
  UserList *current = headNode;
  while (current != NULL)
  {
    printf("\n--------------------");
    printf("\nUser:");
    printf("\nNif: %d", current->user.nif);
    printf("\nName: %s", current->user.name);
    printf("\nEmail:%s", current->user.email);
    printf("\nPhone:%d", current->user.phone);
    printf("\nZip:%d", current->user.zip);
    printf("\nWallet:%d", current->user.wallet);
    printf("\nManager:%d", current->user.isManager);
    printf("\n--------------------\n");
    current = current->next;
  }
  printf("\n");
}

// edit the user in the list with the given nif
bool editUser(UserList *usersList, int nif, User user)
{
  UserList *current = usersList;
  while (current != NULL)
  {
    if (current->user.nif == nif)
    {
      current->user = user;
      return true;
    }
    current = current->next;
  }
  return false;
}

// delete user
bool deleteUser(UserList *usersList, int nif)
{
  UserList *current = usersList;
  UserList *previous = NULL;
  while (current != NULL)
  {
    if (current->user.nif == nif)
    {
      if (previous == NULL)
      {
        usersList = current->next;
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

bool storeUsersInBin(UserList *headNode)
{
  FILE *pFile = NULL;
  UserList *current_node = headNode;

  pFile = fopen("./saved-data/users.bin", "wb");

  if (pFile == NULL)
  {
    perror("could not open file");
    return false;
  }

  while (current_node != NULL)
  {
    fwrite(&current_node->user, sizeof(User), 1, pFile);
    current_node = current_node->next;
  }

  fclose(pFile);
  return true;
}

bool searchUserByNif(UserList *headNode, int nif)
{
  UserList *current = headNode;
  while (current != NULL)
  {
    if (current->user.nif == nif)
    {
      return true;
    }
    current = current->next;
  }
  return false;
}