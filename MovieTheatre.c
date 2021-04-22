#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//typedef structure (reserved key: movieTh)
typedef struct movies {
	// c_ = char, f_ = float, i_ = int
	char c_Name[100];
	char c_Director[100];
	char c_ReleaseDate[100];
	char c_RentalExpiration[100];
	float f_Rating;
	float f_CostPerRental;
	int i_ViewsPerMonth;
	int i_Renter; // i_Renter = customer id
	char *list; 
	struct movies *next; //pointer to the next structure in list
	struct movies *previous; //pointer to the last structure in list
} movieTh;

//Create New Movie Entry Function
movieTh *MakeNewMovie() {
	int ch;
	movieTh *newMovie = malloc(sizeof(movieTh));
	puts("Enter Movie Name:"); 
	scanf("%[^\n]", &newMovie->c_Name); //Assigns value to c_Name
	while ((ch = getchar()) != '\n' && ch != EOF);
	puts("Enter Director Name:");  
	scanf("%[^\n]", &newMovie->c_Director); //Assigns value to c_Director
	while ((ch = getchar()) != '\n' && ch != EOF);
	puts("Enter Movie Release Date (yy/mm/dd):");  
	scanf("%s", &newMovie->c_ReleaseDate); //Assigns value to c_ReleaseDate
	while ((ch = getchar()) != '\n' && ch != EOF);
	puts("Enter Movie Rating From 1.0 To 5.0:");  
	scanf("%f", &newMovie->f_Rating); //Assigns value to f_Rating
	while ((ch = getchar()) != '\n' && ch != EOF);
	puts("Enter Movie Cost Per Rental:");  
	scanf("%f", &newMovie->f_CostPerRental); //Assigns value to f_CostPerRental
	while ((ch = getchar()) != '\n' && ch != EOF);
	puts("Enter Movie Views Per Month:");  
	scanf("%d", &newMovie->i_ViewsPerMonth); //Assigns value to i_ViewsPerMonth
	while ((ch = getchar()) != '\n' && ch != EOF);
	puts("Enter Movie Renter's Customer ID:");  
	scanf("%d", &newMovie->i_Renter); //Assigns value to i_Renter
	while ((ch = getchar()) != '\n' && ch != EOF);
	puts("Enter Movie Rental Expiration (yy/mm/dd):");  
	scanf("%s", &newMovie->c_RentalExpiration); //Assigns value to i_Renter
	while ((ch = getchar()) != '\n' && ch != EOF);

	newMovie->next = NULL;
	newMovie->previous = NULL;

	return newMovie;
}

//Adds Movie To Start
movieTh *AddToStart(movieTh *starting) {
	movieTh *newMovie = MakeNewMovie(); //add MakenewMovie function to newMovie
	if (starting != NULL) {
		starting->previous = newMovie;
		newMovie->next = starting;
	}
	return newMovie;
}

//Adds Movie To End 
movieTh *AddToEnd(movieTh *starting) {
	movieTh *start = starting;
	movieTh *newMovie = NULL;

	if (starting == NULL) {
		newMovie = AddToStart(starting); //Add Addtostart function to newMovie
		start = newMovie; //add new movie to start
	} 
	else {
		movieTh *movieStart = starting; //create movieStart pointer, add starting pointer to that
		while (movieStart->next != NULL) { //loop through until movieStart pointer is null
			movieStart = movieStart->next;
		}
		newMovie = MakeNewMovie(); //add MakenewMovie function to newMovie
		movieStart->next = newMovie;
		newMovie->next = NULL;
		newMovie->previous = movieStart;
	}
	return start;
}

//Print The List Of Movies Function
void PrintList(movieTh *start) {
	movieTh *currentMovie = start; //create currentMovie pointer, add start to it
	movieTh *ahead = NULL;
	movieTh *behind = NULL;

	while (currentMovie != NULL) {
		ahead = currentMovie->next;
		behind = currentMovie->previous;

		printf("Movie: %s | Director: %s | Release Date: %s | Rating: %.1f | Rental Price: $%.2f | Monthly Views: %d | Renter's Customer ID: %d | Rental Expiration: %s\n", currentMovie->c_Name, currentMovie->c_Director, currentMovie->c_ReleaseDate, currentMovie->f_Rating, currentMovie->f_CostPerRental, currentMovie->i_ViewsPerMonth, currentMovie->i_Renter, currentMovie->c_RentalExpiration); 
		currentMovie = currentMovie->next;
		ahead = NULL;
		behind = NULL;
	}
}

//Display Read Function
void DisplayRead(movieTh *start) {
	movieTh *last = start;
	movieTh *new = NULL;	
	while (last != NULL) {
		new = last->next;
		printf("Movie: %s | Director: %s | Release Date: %s | Rating: %.1f | Rental Price: $%.2f | Monthly Views: %d | Renter's Customer ID: %d | Rental Expiration: %s\n", last->c_Name, last->c_Director, last->c_ReleaseDate, last->f_Rating, last->f_CostPerRental, last->i_ViewsPerMonth, last->i_Renter, last->c_RentalExpiration);
		free(last); //free's last
		last = new; //assigns new to last
	}	
}

//Delete Entry Function
movieTh *Delete(movieTh *starting) {
	int ch;
	printf("Enter a Movie Name To Delete: ");
	char input[20];
	scanf("%[^\n]", &input);
	while ((ch = getchar()) != '\n' && ch != EOF);
	movieTh *movie = starting; //assign *movie to starting
	movieTh *movieDel = NULL;

	while (movie != NULL) {
		if (strncmp(input, movie->c_Name, strlen(movie->c_Name)) == 0) { //compare user input with c_Name
			movieDel = movie; //assign inputted movie to movieDel
			break;
		}
		movie = movie->next;
	}

	if (starting != NULL && movieDel == starting) { //if the starting is not null, and the movie to delete is = to starting do this
		if (movieDel->next != NULL) {
			movieDel->next->previous = NULL;
			starting = movieDel->next;
		} 
		else {
			starting = NULL;
		}
	} 
	else {
		if (movieDel != NULL) {
			if (movieDel->previous != NULL) {
				movieDel->previous->next = movieDel->next;
			}
			if (movieDel->next != NULL) {
				movieDel->next->previous = movieDel->previous;
			}
		}
	}
	if(movieDel != NULL) {
		movieDel = NULL;
		free(movieDel); //free the movieDel
	}
	return starting;
}

//Save Function
void Save(movieTh *start) {
	FILE *p;
	p = fopen("movies.txt", "wb");

	if (p != NULL) {
		movieTh *currentMovie = start;
		movieTh *startNext = NULL;
		movieTh *last = NULL;

		while (currentMovie != NULL) {
			startNext = currentMovie->next;
			last = currentMovie->previous;
			currentMovie->next = NULL;
			currentMovie->previous = NULL;

			fseek(p, 0, SEEK_END);
			fwrite(currentMovie, sizeof(movieTh), 1, p); //writes data from the array to the file
			printf("Saved: %s\n",currentMovie->c_Name); //Saving verification 
			currentMovie->next = startNext;
			currentMovie->previous = last;

			startNext = NULL;
			last = NULL;
			currentMovie = currentMovie->next;
		}
		fclose(p);
		movieTh *movieList = start;
		if(p == NULL) {
			puts("Error");
			exit(1);
		}
		else { 
			while(movieList != NULL) {
				fprintf(p, "Movie: %s | Director: %s | Release Date: %s | Rating: %.1f | Rental Price: $%.2f | Monthly Views: %d | Renter's Customer ID: %d | Rental Expiration: %s\n", movieList->c_Name, movieList->c_Director, movieList->c_ReleaseDate, movieList->f_Rating, movieList->f_CostPerRental, movieList->i_ViewsPerMonth, movieList->i_Renter, movieList->c_RentalExpiration);
				movieList = movieList->next;     
			}   
		}
		fclose(p);
	}
	else {
		puts("Error");
	}
}

//Reading File Function
movieTh *ReadFile(movieTh *start, FILE *p) {
	size_t returnValue; //return type for sizeof
	if (start == NULL) {
		start = malloc(sizeof(movieTh));
		returnValue = fread(start, sizeof(movieTh), 1, p);  //reads data from p into the array 
		start->next = NULL;
		start->previous = NULL;
	} 
	else {
		movieTh *movieStart = start;
		movieTh *newMovie = malloc(sizeof(movieTh));
		while(movieStart->next != NULL) {
			movieStart = movieStart->next;
		}
		returnValue = fread(newMovie, sizeof(movieTh), 1, p); //reads data from p into the array 
		movieStart->next = newMovie;
		newMovie->next = NULL;
		newMovie->previous = movieStart;
	}
	return start;
}

//Reading Function
movieTh *ReadMovies(movieTh *start) {
	FILE *p;
	p = fopen("movies.txt", "rb"); //opens file for reading
	if (p != NULL) {

		DisplayRead(start); //Display Reading Function
		start = NULL;

		fseek(p, 0, SEEK_END); //sets the file position
		long size = ftell(p); //returns the current file position
		rewind(p); //sets the file position to the beginning of the file

		int movies = (int)(size/(sizeof(movieTh)));
		printf("Movies: %d\n", movies);

		for (int i = 0; i < movies; i++) {
			fseek(p, (sizeof(movieTh) * i), SEEK_SET); //sets the file position
			start = ReadFile(start, p);
		}
	}  
	else {
		puts("Error");
	}
	return start;
}

//Search Function
movieTh *Search(movieTh *starting) {
	int ch;
	printf("Enter a Movie Name To Search: ");
	char input[20];
	scanf("%[^\n]", &input);
	while ((ch = getchar()) != '\n' && ch != EOF);
	movieTh *movie = starting;

	while (movie != NULL) {
		if (strncmp(input, movie->c_Name, strlen(movie->c_Name)) == 0) { //compare user input with c_Name if they are equal do this
			printf("Movie: %s | Director: %s | Release Date: %s | Rating: %.1f | Rental Price: $%.2f | Monthly Views: %d | Renter's Customer ID: %d | Rental Expiration: %s\n", movie->c_Name, movie->c_Director, movie->c_ReleaseDate, movie->f_Rating, movie->f_CostPerRental, movie->i_ViewsPerMonth, movie->i_Renter, movie->c_RentalExpiration);
			break;
		}
		else if (strncmp(input, movie->c_Name, strlen(movie->c_Name)) != 0) {
			movie = movie->next;
			continue;
		}
		else {
			puts("Error Movie Not Found");
			break;
		}
	} 
	return starting;
}

//Calculate Earnings Function
movieTh *Earnings(movieTh *starting) {
	float earnings = 0.0;
	movieTh *movie = starting; //add movie pointer to starting
	while (movie != NULL) { 
		earnings += movie->f_CostPerRental; //add cost per rental to earnings
		movie = movie->next; //add the next movie to movie
	} 
	printf("Earnings: $%.2f\n", earnings);
	return starting;
}

//Modify Function
movieTh *Modify(movieTh *starting) {
	movieTh *movie = starting;
	int ch;
	printf("Enter a Movie Name To Modify: ");
	char input[20];
	scanf("%[^\n]", &input);
	while ((ch = getchar()) != '\n' && ch != EOF);

	while (movie != NULL) {
		if (strncmp(input, movie->c_Name, strlen(movie->c_Name)) == 0) { //compare user input with c_Name if they are equal do this
			printf("Movie: %s | Director: %s | Release Date: %s | Rating: %.1f | Rental Price: $%.2f | Monthly Views: %d | Renter's Customer ID: %d | Rental Expiration: %s\n", movie->c_Name, movie->c_Director, movie->c_ReleaseDate, movie->f_Rating, movie->f_CostPerRental, movie->i_ViewsPerMonth, movie->i_Renter, movie->c_RentalExpiration);
			//Replaces The Values
			puts("Enter Movie Name:");  
			scanf("%[^\n]", &movie->c_Name); //Assigns value to c_Name
			while ((ch = getchar()) != '\n' && ch != EOF);
			puts("Enter Director Name:");  
			scanf("%[^\n]", &movie->c_Director); //Assigns value to c_Director
			while ((ch = getchar()) != '\n' && ch != EOF);
			puts("Enter Movie Release Date (yy/mm/dd):");  
			scanf("%s", &movie->c_ReleaseDate); //Assigns value to c_ReleaseDate
			while ((ch = getchar()) != '\n' && ch != EOF);
			puts("Enter Movie Rating From 1.0 To 5.0:");  
			scanf("%f", &movie->f_Rating); //Assigns value to f_Rating
			while ((ch = getchar()) != '\n' && ch != EOF);
			puts("Enter Movie Cost Per Rental:");  
			scanf("%f", &movie->f_CostPerRental); //Assigns value to f_CostPerRental
			while ((ch = getchar()) != '\n' && ch != EOF);
			puts("Enter Movie Views Per Month:");  
			scanf("%d", &movie->i_ViewsPerMonth); //Assigns value to i_ViewsPerMonth
			while ((ch = getchar()) != '\n' && ch != EOF);
			puts("Enter Movie Renter's Customer ID:");  
			scanf("%d", &movie->i_Renter); //Assigns value to i_Renter
			while ((ch = getchar()) != '\n' && ch != EOF);
			puts("Enter Movie Rental Expiration (yy/mm/dd):");  
			scanf("%s", &movie->c_RentalExpiration); //Assigns value to i_Renter
			while ((ch = getchar()) != '\n' && ch != EOF);

			movieTh *start = starting;
			movieTh *newMovie = NULL;

			if (starting == NULL) {
				newMovie = AddToStart(starting);
				start = newMovie;
			} 
			else {
				movieTh *movieStart = starting;
				while (movieStart->next != NULL) {
					movieStart = movieStart->next;
				}
			}
			return start;
			break;
		}
		else if (strncmp(input, movie->c_Name, strlen(movie->c_Name)) != 0) { //compare user input with c_Name if they are not equal do this
			movie = movie->next;
			continue;
		}
		else {
			puts("Error Movie Not Found");
			break;
		}
	} 
}
//Sort Function
movieTh *Sort(movieTh *starting) {
	movieTh *movie = starting;
	int i, j, count = 4;
	char temp[25];
	char *str[25];

	while (movie != NULL) {
		if (strcmp(movie->c_Name, movie->next->c_Name) > 0) {
            strcpy(temp, movie->c_Name);
            strcpy(movie->c_Name, movie->next->c_Name);
            strcpy(movie->next->c_Name, temp);
        }
		printf("Movie: %s | Director: %s | Release Date: %s | Rating: %.1f | Rental Price: $%.2f | Monthly Views: %d | Renter's Customer ID: %d | Rental Expiration: %s\n", movie->c_Name, movie->c_Director, movie->c_ReleaseDate, movie->f_Rating, movie->f_CostPerRental, movie->i_ViewsPerMonth, movie->i_Renter, movie->c_RentalExpiration);
		movie = movie->next;
	}
}

//Main Function
int main() {	
	int ch;
	char command[16];
	movieTh *start = NULL; //assigns null to start pointer
	int prompt;	
	while (prompt != 9) { //Loop for menu
		char c_Prompt = 'y';
		puts("Start With New Data (1) | Load Previous Data (2) | Exit (9)");
		scanf("%d", &prompt);
		while ((ch = getchar()) != '\n' && ch != EOF);
		//Start With New Data (1)
		if (prompt == 1) {
			while (c_Prompt == 'y') {
				start = AddToEnd(start); //Adds content to bottom
				PrintList(start); //Prints what has been added
				printf("Add Another Entry (y/n)\n");
				scanf("%c", &c_Prompt);
				while ((ch = getchar()) != '\n' && ch != EOF);
			}
			Save(start); //save data
		}
		//Load Previous Data (2)
		else if (prompt == 2) {
			start = ReadMovies(start); //Display movies
			puts("Add New Entries (1) | Browse Entries (2) | Delete Entries (3) | Save (4) | Sort Alphabetically (5) | Search Title (6) | Tally Earnings (7) | Modify Movie (8) | Exit (9)");
			scanf("%d", &prompt);
			while ((ch = getchar()) != '\n' && ch != EOF);
			if (prompt == 1) {
				while (c_Prompt == 'y') {
					start = AddToEnd(start); //Adds content to bottom
					PrintList(start); //Prints what has been added
					printf("Add Another Entry (y/n)\n");
					scanf("%c", &c_Prompt);
					while ((ch = getchar()) != '\n' && ch != EOF);
				}
				Save(start); //save data
			}
			else if (prompt == 2) {
				start = ReadMovies(start); //Display movies
			}
			else if (prompt == 3) {
				start = Delete(start);
				Save(start); //save data
			}
			else if (prompt == 4) {
				puts("Saved Data");
				Save(start); //save data
			}
			else if (prompt == 5) {
				start = Sort(start); //sort data
			}
			else if (prompt == 6) {
				start = Search(start); //Search a movie
			}
			else if (prompt == 7) {
				start = Earnings(start); //Tally up earnings
			}
			else if (prompt == 8) {
				start = Modify(start); //Modify Movie
				Save(start); //save data
			}
			//Exit for Load Previous Data
			else if (prompt == 9) {
				exit(1);
			}
		}
		//Exit for Start With New Data
		else if (prompt == 9) {
			exit(1);
		}
	}
	return 0;
}