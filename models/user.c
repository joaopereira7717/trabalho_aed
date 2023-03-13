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
  UserList *newUser = (UserList *)malloc(sizeof(UserList));
  newUser->user = user;
  newUser->next = NULL;

  *headNode = newUser;
  return true;
}

void printUserList(UserList *headNode)
{
  UserList *current = headNode;
  while (current != NULL)
  {
    printf("\n%d\n", current->user.nif);
    current = current->next;
  }
}