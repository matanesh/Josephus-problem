/******************************************
* Bar Illan university
* student name: Matan Eshel
* ID: 203502802
* 83-120-02
* Ex 5
* The Josephus Flavius problem
******************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <string.h>
#include <malloc.h>

typedef struct node
{
	char* name;
	int Id;
	struct node* next;
} Warrior;

/*prototpye------------------------------*/
Warrior* InitPlayer();
Warrior* InitTheHungerGame();
Warrior* Killer(Warrior* TmpWarrior);
void LetTheHungerGameBegin(Warrior* TmpWarrior);
void freeList(Warrior* head);
/*-------------------------------------------*/


int main()
{
	Warrior* head; //init the Warior head pointer
	head = InitTheHungerGame();
	LetTheHungerGameBegin(head);
	system("pause");

}

/*************************************************************
Function name: "InitPlayer"
Input: none
Output and The function operation:
this function create a new wariior to the game and
return a pointer to its struct
***************************************************************/
Warrior* InitPlayer()
{
	char str[80];
	int Id;
	Warrior* newWarrior = (Warrior*)malloc(sizeof(Warrior));
	if (newWarrior == NULL) // fail in allocation memory
	{
		return NULL;
	}

	// init data-name for new player
	printf("name:\n");
	scanf(" %[^\n]s", str); //insert name and aloocate for him a exact place
	newWarrior->name = (char*)malloc(strlen(str) * sizeof(char) + 1);
	if (newWarrior->name == NULL) // fail in allocation memory
	{
		free(newWarrior);
		return NULL;
	}
	strcpy(newWarrior->name, str);

	// init data-Id for new player
	printf("id:\n");
	scanf("%d", &Id);
	newWarrior->Id = Id;

	/* indicate that the new player is placed last and point to the end (null)
	and return the pointer to the new player (the one befor him point to him now*/
	newWarrior->next = NULL;
	return newWarrior;
}

/*************************************************************
Function name: "InitTheHungerGame"
Input: none
Output and The function operation:
ask the user if he want to add warrior to the game
and create new one with the function above.
it is allso conect between the struct like a linked list
and in the end conect the last pointer to the firs to make
a circle linked list.
***************************************************************/
Warrior* InitTheHungerGame()
{
	Warrior* head = NULL;
	Warrior* newWarrior;
	Warrior* lasWarrior = head;

	int u = 1;
	do// loop that create new player and connect them to th list
	{
		printf("Add a person to the game? 1 for yes, 0 for no\n");
		scanf("%d", &u);
		if (u == 1)
		{
			// create new player
			newWarrior = InitPlayer();
			if (newWarrior == NULL) // fail in allocation
			{
				freeList(head); // releas all player in the list
				exit(1);
			}

			if (head == NULL) // Create of the first player
			{
				head = newWarrior;
				lasWarrior = newWarrior;
			}

			else // creat of the second player and etc.
			{
				lasWarrior->next = newWarrior;
				lasWarrior = newWarrior;
			}
		}
	} while (u != 0);
	// make the linked list to a circe by point the next player pointer to the firs
	if (head == NULL)
		return NULL;
	lasWarrior->next = head;
	return head;
}

/*************************************************************
Function name: "LetTheHungerGameBegin"
Input: Warrior *TmpWarrior pointer
Output and The function operation:
the main function of the game. take the temp warrior.
kills the warrior after him by the "killer" function
and proceed to the next Warrior.
when a Warrior stay alone rtuent and print its name
***************************************************************/

void LetTheHungerGameBegin(Warrior* TmpWarrior)
{
	if (TmpWarrior == NULL) // if the linked is empty
		return;
	while (TmpWarrior->next != TmpWarrior) // if only one playere stay. he point to itself
		TmpWarrior = Killer(TmpWarrior);
	printf("%sstayin alive!!\n", TmpWarrior->name);
	// free the winner memory becasue the game ends
	free(TmpWarrior->name);
	free(TmpWarrior);
}
/*************************************************************
Function name: "Killer"
Input: pointer to the temp warriot
Output: the next warrior pointer
The function operation: print that a player kills the one
next to him. "kiils" by free the "dead" warrior
and move the pointer to the next warrior
***************************************************************/

Warrior* Killer(Warrior* TmpWarrior)
{
	Warrior* next = TmpWarrior->next;
	printf("%skills %s\n", TmpWarrior->name, next->name);

	next = next->next; // save the place of the next player that we not loos it 

	// free the memory of the killes player
	free(TmpWarrior->next->name);
	free(TmpWarrior->next);

	TmpWarrior->next = next; // update the now the killer it is the next one
	return next;
}

/*************************************************************
Function name: "freeList"
Input: pointer to warrior (*head)
Output:
The function operation: in case of fail in alocated memory to
the new player free all befoer exit.
***************************************************************/
void freeList(Warrior* head)
{
	Warrior* temp;
	while (head != NULL)
	{
		temp = head->next;
		free(head->name);
		free(head);
		head = temp;
	}
}


