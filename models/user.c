#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "./user.h"

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
    printf("could not allocate memory!");
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