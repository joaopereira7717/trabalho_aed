/**
 * @file user.c
 * @brief File containing the functions to manage the users
 *
 * This file contains the implementation of functions to manage users, such as reading users from a text file, creating a user, creating a user list, printing a user list, editing a user, deleting a user, storing users in a binary file, and searching for a user by NIF.
 *
 * @author João Pereira
 * @date 2023-03-18
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "./user.h"

/**
 * @brief Reads users from a text file and creates a user list
 *
 * This function reads users from a text file and creates a user list. The user list is created by calling the createUserList function.
 *
 * @param headNode A pointer to the head node of the user list
 * @return A pointer to the head node of the user list
 */
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

/**
 * @brief setUsersData - Reads user data from a binary file and creates a linked list of users.
 * @headNode: A pointer to a pointer to the head node of the linked list.
 *
 * This function opens a binary file containing user data and reads each user record
 * into a User struct. It then calls the createUserList function to create a new node
 * in the linked list for each user. The headNode pointer is updated to point to the
 * first node in the list. If the file cannot be opened, NULL is returned.
 *
 * Return: A pointer to the head node of the linked list.
 */
UserList *setUsersData(UserList **headNode)
{
  FILE *pFile = NULL;

  // Open the binary file for reading
  pFile = fopen("./saved-data/users.bin", "rb");

  // Check if the file was opened successfully
  if (pFile == NULL)
  {
    perror("Could not open file");
    return NULL;
  }

  User user;
  // Read each user record from the file and create a new node in the linked list
  while (fread(&user, sizeof(User), 1, pFile) == 1)
  {
    createUserList(headNode, user);
  }

  // Close the file
  fclose(pFile);

  // Return a pointer to the head node of the linked list
  return *headNode;
}

/**
 * @brief Creates a user
 *
 * This function creates a user with the given parameters and returns a pointer to the user.
 *
 * @param nif The NIF of the user
 * @param name The name of the user
 * @param email The email of the user
 * @param phone The phone number of the user
 * @param zip The zip code of the user
 * @param password The password of the user
 * @param wallet The wallet balance of the user
 * @param isManager A boolean indicating whether the user is a manager or not
 * @return A pointer to the created user
 */
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

/**
 * @brief Creates a user list
 *
 * This function creates a new node in the user list with the given user and adds it to the head of the list.
 *
 * @param headNode A pointer to the head node of the user list
 * @param user The user to be added to the list
 * @return A boolean indicating whether the user list was successfully created or not
 */
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

/**
 * @brief Prints the user list
 *
 * This function prints the user list to the console.
 *
 * @param headNode A pointer to the head node of the user list
 */
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

/**
 * @brief Edits a user in the list with the given NIF
 *
 * This function searches for a user in the list with the given NIF and edits it with the given user.
 *
 * @param usersList A pointer to the head node of the user list
 * @param nif The NIF of the user to be edited
 * @param user The user to replace the old user
 * @return A boolean indicating whether the user was successfully edited or not
 */
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

/**
 * @brief Deletes a user from the list
 *
 * This function searches for a user in the list with the given NIF and deletes it from the list.
 *
 * @param usersList A pointer to the head node of the user list
 * @param nif The NIF of the user to be deleted
 * @return A boolean indicating whether the user was successfully deleted or not
 */
bool deleteUser(UserList **usersList, int nif)
{
  UserList *current = *usersList;
  UserList *previous = NULL;

  while (current != NULL)
  {
    if (current->user.nif == nif)
    {
      if (previous == NULL)
      {
        *usersList = current->next;
      }
      else
      {
        previous->next = current->next;
      }
      free(current);
      current = NULL;
      return true;
    }
    previous = current;
    current = current->next;
  }

  return false;
}

/**
 * @brief Stores the user list in a binary file
 *
 * This function stores the user list in a binary file.
 *
 * @param headNode A pointer to the head node of the user list
 * @return A boolean indicating whether the user list was successfully stored or not
 */
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

/**
 * @brief Searches for a user in the list with the given NIF
 *
 * This function searches for a user in the list with the given NIF and returns a boolean indicating whether the user was found or not.
 *
 * @param headNode A pointer to the head node of the user list
 * @param nif The NIF of the user to be searched for
 * @return A boolean indicating whether the user was found or not
 */
bool searchUserByNif(UserList *headNode, int nif)
{
  printUserList(headNode);
  if (headNode == NULL)
  {
    return false;
  }
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

bool updateUserWallet(UserList *headNode, int nif, int wallet)
{
  UserList *current = headNode;
  while (current != NULL)
  {
    if (current->user.nif == nif)
    {
      current->user.wallet += wallet;
      if (current->user.wallet < 0)
      {
        current->user.wallet -= wallet;
        return false;
      }
      return true;
    }
    current = current->next;
  }
  return false;
}