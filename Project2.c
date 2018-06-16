//Programmer: Sarah Faust
//Program: Project 2. A tour of the GMU campus.
//Summary:	The tour is a singly linked list of Stops. Each stop has a name,
//			a description, and a link to the next stop. The stops are made by 
//			the user and the stops can be ordered alphabetically or according
//			to the specifications of the user. The stops are released from 
//			memory before the program exits.
#import <stdio.h>
#import <stdlib.h>
#import <string.h>

typedef struct StopStruct
{
	char StopName[30];
	char Description[100];
	struct StopStruct *next;
}Stop;

//functions:
Stop * UserOrder(Stop *Header, char name[30], char desc[100]);
Stop * AlphaOrder(Stop *Header, char name[30], char desc[100]);
Stop * DeleteStop(Stop *Header, char name[30]);
void Tour(Stop *Header);
void DeleteTour(Stop *Header);


int main()
{
	printf("Welcome to the George Mason University campus tour!\n");
	printf("Sponsered by the Office of Transportation and Tourism\n");
	printf("\n");
	Stop *tourHeadptr;
	//filled tracks if the head stop is filled out or not
	char filled = 'n';
	//filler helps clear the buffer
	char filler;
	
	//asks for how the user wants the tour to be arranged
	char choice = 'c';
	while((choice!='a')&&(choice!='b'))
	{
		printf("How would you like to organize your tour?\n");
		printf("\ta) alphabetical order\n");
		printf("\tb) custom order\n");
		printf("==> ");
		choice = getchar();
		filler = getchar();
	}
	if(choice=='a')
	{
		printf("The tour will be organized alphbetically for you.\n");
	}
	if(choice=='b')
	{
		printf("Enter the stops in the order that you want.");
	}
	
	//the sub menu
	char subChoice = 'e';
	while(subChoice!='d')
	{
		while((subChoice!='a')&&(subChoice!='b')
			&&(subChoice!='c')&&(subChoice!='d'))
		{
			printf("\nWhat would you like to do?\n");
			printf("\ta) Print the current campus tour\n");
			printf("\tb) Add a stop to the tour\n");
			printf("\tc) Delete a stop from the tour\n");
			printf("\td) Exit the program\n");
			printf("==> ");
			//char filler = getchar();
			subChoice = getchar();
			char filler = getchar();
		}
		
		//print current tour
		if(subChoice=='a')
		{
			//checks to see if there are any stops
            		if(filled=='n')
            			printf("There aren't any stops yet!\n");
            		else
            		{
            		//states whether tour is user-picked ot not
            		if(choice=='b')
            			printf("This tour is organized by the user.\n");
            		if(choice=='a')
            			printf("This tour is organized alphabetically.\n");
            		//prints the tour
            		Tour(tourHeadptr);
			}
			subChoice = 'e';
        	}
        
        	//add stop to tour
        	if(subChoice=='b')
       	 	{
        		//ask for name of stop
        		char newStopName[30];
        		char newDesc[100];
        		printf("What is the name of the stop? (30 characters)\n");
        		//stores everything up to the \n character
        		scanf("%[^\n]",newStopName);
        		//asks for a description of the stop
        		printf("What is an interesting fact about this stop? (100 Chars)\n");
        		char filler = getchar();
			scanf("%[^\n]",newDesc);
			filler = getchar();
   	
        		//immediately adds the stop if there aren't any stops yet
        		if (filled=='n')
        		{
        			Stop *temp;
        			temp = (Stop*)malloc(sizeof(Stop));
        			strcpy(temp->StopName, newStopName);
        			strcpy(temp->Description, newDesc);
        			temp->next = NULL;
        			tourHeadptr = temp;
				filled = 'y';
        		}
        		//or the stop is added according the the user's initial choice
        		else
        		{
        			if(choice=='b')
        				tourHeadptr = UserOrder(tourHeadptr, newStopName, newDesc);
        			if(choice=='a')
        				tourHeadptr = AlphaOrder(tourHeadptr, newStopName, newDesc);
        		}	
			subChoice = 'e';

        	}
        	//deletes a stop from the tour
        	if(subChoice=='c')
        	{
        		//checks to see if the tour is empty
        		if(filled=='n')
        			printf("There aren't any stops to delete!\n");
        		//or it calls the function to delete the stop
        		else
        		{
        			char stopName[30];
        			printf("What is the exact name of the stop you wish to delete?\n");
        			scanf("%[^\n]",stopName);
				char filler = getchar();
        			DeleteStop(tourHeadptr, stopName);
        		}	
			subChoice = 'e';
        	}
        	if(subChoice=='d')
        	{      	
			printf("Thank you for visiting!\n");
			if(filled = 'y')
			{
        			DeleteTour(tourHeadptr);
        		}
        	}
    	}
    return 0;

}
//------------------------------------------------------------------------------
//pre:	The pointer to the head of the tour is passed in along with the name
//		and description of the new stop to be added
//post:	A new stop is inserted into the tour. Any duplicates are deleted.
//		The user is notified whether duplicates were found or whether the
//		insertion was successful or not. The head pointer to the edited 
//		tour is returned.
Stop * UserOrder(Stop *Header, char name[30], char desc[100])
{	
	//FIRST checks to see if the stop already exists
	//-----------------------------------------------------
	Stop *temp;
	temp = Header;
	//checks the head node
	int j;
	j = strcmp(temp->StopName, name);
	if(j==0)
	{
		//deletes the current header and makes the next node the new header
		printf("A stop of the same name has been found and deleted.\n");
		Header = Header->next;
		temp->next = NULL;
		free(temp);
		temp = NULL;
	}
	else
	{
		//checks the other nodes
		while(temp->next!=NULL)
		{
			j = strcmp(temp->next->StopName, name);
			if(j==0)
			{
				//deletes the duplicate node and changes the previous 
				//	node's next
				printf("A stop of the same name has been found and deleted.\n");
				Stop *temp2;
				temp2 = temp->next;
				temp->next = temp->next->next;
				free(temp2);
				temp2 = NULL;
			}
			temp = temp->next;
		}
		//checks the tail node
		if(temp->next==NULL)
		{
			j = strcmp(temp->StopName, name);
			if(j==0)
			{
				printf("A stop of the same name has been found and deleted.\n");
				free(temp);
				temp=NULL;
			}
		}
		temp = NULL;
	}
	//----------------------------------------------------
	
	//SECOND the user chooses where the new stop will go
	char pick;
	printf("Where would you like to put this new stop?\n");
	printf("\t1. At the beginning\n");
	printf("\t2. Before a specific stop\n");
	printf("\t3. At the end\n");
	pick = getchar();
	char filler = getchar();

	//makes the new stop
	Stop *new;
	new = (Stop*)malloc(sizeof(Stop));
	strcpy(new->StopName, name);
	strcpy(new->Description, desc);
	
	//the new stop becomes the header	
	if(pick=='1')
	{
		new->next = Header;
		Header = new;
	}
	//the new stop is inserted before another stop
	if(pick=='2')
	{
		//lists the stops for the user
		Tour(Header);

		printf("\nBefore which stop will the new stop be put? ");
		printf("(type in the exact name)\n");
	//	char filler = getchar();
		char after[30];
		scanf("%[^\n]", after);
		char filler = getchar();
		
		//found checks the specified stop's existance
		char found = 'n';
		Stop *search;
		search = Header;
		int k;
		while((search->next!=NULL)&&(found=='n'))
		{
			k = strcmp(search->next->StopName, after);
			if(k==0)
			{
				//inserts the new stop
				printf("The specified stop had been found.\n");
				found = 'y';
				
				new->next = search->next;
				search->next = new;
				
				printf("The new stop has been inserted.\n");
			}
			search = search->next;
		}
		free(search);
		search=NULL;
		//if the stop the user specified wasn't found...
		if(found=='n')
		{
			printf("The stop you specified doesn't exist. ");
			printf("The new stop was not inserted.\n");
			//the new stop is deleted
			free(new);
			new = NULL;
		}
	}
	if(pick=='3')
	{
		Stop *end;
		end = Header;
		//traverses the tour stops to the tail
		while(end->next!=NULL)
		{
			end=end->next;
		}
		//now end is the tail stop
		end->next = new;
		new->next = NULL;
		
		printf("The new stop has been added to the end.\n");
	}
	//-------------------------------------------------------
	//returns the header of the edited tour
	return Header;
}
//------------------------------------------------------------------------------
//pre:	The pointr to the head of the tour is passed in along with the name
//		and description of the new stop.
//post:	Doesn't edit the tour if the stop already exists. The new stop is 
//		inserted alphabetically. The pointer to the head stop is returned.
Stop * AlphaOrder(Stop *Header, char name[30], char desc[100])
{
	//FIRST checks to see if the stop already exists
	//-----------------------------------------------------
	Stop *temp;
	temp = Header;
	//checks the head node
	int j;
	j = strcmp(temp->StopName, name);
	if(j==0)
	{
		//tells the user that the stop has already been made
		//exits the function
		printf("There is already a stop of that name.");
		printf("The new stop wasn't added to the tour.\n");
		return Header;
	}
	else
	{
		//checks the other nodes
		while(temp->next!=NULL)
		{
			j = strcmp(temp->next->StopName, name);
			if(j==0)
			{
				//tells the user that the stop has already been made
				//exits the function
				printf("There is already a stop of that name.");
				printf("The new stop wasn't added to the tour.\n");
				return Header;
			}
			temp = temp->next;
		}
		//checks the tail node
		if(temp->next==NULL)
		{
			j = strcmp(temp->StopName, name);
			if(j==0)
			{
				//tells the user that the stop has already been made
				//exits the function
				printf("There is already a stop of that name.");
				printf("The new stop wasn't added to the tour.\n");
				return Header;
			}
		}
		temp = NULL;
	}
	//----------------------------------------------------
	//SECOND the stop is inserted alphabetically
	//makes the new stop
	Stop *new;
	new = (Stop*)malloc(sizeof(Stop));
        strcpy(new->StopName, name);
        strcpy(new->Description, desc);

	
	//runner runs though each stop
	Stop *runner;
	runner = Header;
	//prev keeps track of the previous stop
	Stop *prev;
	prev = Header;
	//count limits the inner while loop to the size of the smaller string
	int count;
	//tracks the sizes of the stop names
	int sizeR;
	int sizeN = sizeof(name)/sizeof(name[0]);
	//tells both while loops to quit if th stop has been inserted
	char done = 'n';
	//tracks when runner is still Header
	char head = 'y';

	//runs though each stop
	while((runner!=NULL)&&(done=='n'))
	{
		//gets the size of the current stop's string
		int sizeR = sizeof(runner->StopName)/sizeof(runner->StopName[0]);
		//sets count to the size of the smallest string
		if(sizeR > sizeN)
			count = sizeN;
		else
			count = sizeR; 
		
		// i tracks the index in the cstrings
		int i = 0;
		//compares the letters		abz aca
		while((toupper(runner->StopName[i])==toupper(name[i]))&&(i<count))
		{
			i++;
		}
		//if the letter from runner is greater than the letter from new...
		if((i!=count)&&(toupper(runner->StopName[i])>toupper(name[i])))
		{
			//new is inserted before runner
			new->next = runner;
			
			if(head=='y')
			{
				Header = new;
				printf("The stop has been added to the beginning.\n");
			}
			else
			{
				prev->next = new;
				printf("The stop was added after %s.\n", prev->StopName);
			}
			
			done=='y';
			return Header;
		}
		//if the stops' names are the same, except of different length...
		if(i==count)
		{
			//new goes before runner if new is shorter
			if(count==sizeN)
			{
				new->next = runner;
			
				if(head=='y')
				{
					Header = new;
					printf("The stop has been added to the beginning.\n");
				}
				else
				{
					prev->next = new;
					printf("The stop now comes after %s.\n",prev->StopName);
				}
				printf("The stop has been inserted.\n");
				done=='y';
				return Header;
			}
			//new goes after runner if runner is shorter
			if(count==sizeR)
			{
				new->next = runner->next;
				runner->next = new;
				printf("The stop has been inserted after %s.\n",runner->StopName);
				done == 'y';
				return Header;
			}
		}
		
		head = 'n';
		prev = runner;
		runner = runner->next;
	}
	//if the stop hadn't been inserted above, it's put at the end of the tour
	if(done=='n')
	{
		prev->next = new;
		new->next = NULL;
		printf("The stop has been added to the end.\n");
	}
	
	return Header;
}
//------------------------------------------------------------------------------
//pre:	The pointer to the head of the tour is passed in along with the name
//		of the stop to be deleted.
//post:	Deletes the stop and returns the pointer to the head of the edited tour
//		if the stop is found. Returns the header to the unedited tour if
//		the stop isn't found.
Stop * DeleteStop(Stop *Header, char name[30])
{
	Stop *temp;
	temp = Header;
	//checks the head node
	int j;
	j = strcmp(temp->StopName, name);
	if(j==0)
	{
		//deletes the current header and makes the next node the new header
		printf("The stop has been deleted.\n");
		Header = Header->next;
		temp->next = NULL;
		free(temp);
		temp = NULL;
		return Header;
	}
	else
	{
		//checks the other nodes
		while(temp->next!=NULL)
		{
			j = strcmp(temp->next->StopName, name);
			if(j==0)
			{
				//deletes the duplicate node and changes the previous 
				//	node's next
				printf("The stop has been deleted.\n");
				Stop *temp2;
				temp2 = temp->next;
				temp->next = temp->next->next;
				free(temp2);
				temp2 = NULL;
				return Header;
			}
			temp = temp->next;
		}
		//checks the tail node
		if(temp->next==NULL)
		{
			j = strcmp(temp->StopName, name);
			if(j==0)
			{
				printf("The stop has been deleted.\n");
				free(temp);
				temp=NULL;
				return Header;
			}
		}
		temp = NULL;
	}
	
	printf("The stop wasn't found.\n");
	return Header;
}
//------------------------------------------------------------------------------
//pre:	The pointer to the head of the tour is passed in.
//post:	A list of all the stops are printed in order.
void Tour(Stop *Header)
{	
	printf("\n");
	
	//travel walks through the tour
	Stop *travel;
	travel = Header;
	int stopNum = 1;
	while(travel!=NULL)
	{
		//the stop's name and description are printed to the screen
		printf("Stop #%d: ", stopNum);
		printf("%s ~ %s\n", travel->StopName, travel->Description);
		travel = travel->next;
		stopNum++;
	}
}
//------------------------------------------------------------------------------
//pre:	The pointer to the head of the tour is passed in.
//post:	Every stop is deleted.
void DeleteTour(Stop *Header)
{
	Stop *alt;
	//goes though each stop and cleans it out of memory
	while(Header!=NULL)
	{
		alt = Header;
		Header = Header->next;
		free(alt);
	}
}
