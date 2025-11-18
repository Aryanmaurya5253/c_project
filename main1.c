#include <stdio.h>
#include <stdlib.h>
// stdlib.h is included to use functions like malloc, free, exit, etc.
#include <string.h>
// string.h is included to use string manipulation functions like strcpy and strcmp.

#define MAX_STATES 5
// MAX_STATES is a constant that defines the maximum number of states available in the system.
#define MAX_DIST 7
// MAX_DIST is a constant that defines the maximum number of districts a state can have.

// struct definitions -> we use struct to group related data together.
// struct District stores the name of a district.
struct District
{
    char name[50];
};
// sturct state store the name of a state. It also contains an array of District structs to hold the districts within that state and an integer to keep track of the number of districts.
struct State
{
    char name[50];
    // districts is an array that can hold up to MAX_DIST District structs.
    struct District districts[MAX_DIST];
    // MAX_DIST is a constant that defines the maximum number of districts a state can have.
    int districtCount;
    // districtCount keeps track of how many districts are actually stored in the districts array.
};
// struct Ticket stores information about a booked ticket, including the mode of transport, seat type, state, district, number of tickets, and total fare.
// This struct is used to store all array related to a ticket booking.
struct Ticket
{
    char mode[10];
    char seatType[20];
    char state[50];
    char district[50];
    int tickets;
    float totalFare;
};

/*Here we load the states and their respective districts into the states array.*/

// void is used to load the states and their respective districts into the states array.
// It initializes the states array with predefined state names and their corresponding districts.
// Here we

void loadStates(struct State states[])
{
    // State 1: Uttarakhand
    strcpy(states[0].name, "Uttarakhand");
    //     //his line copies the text "Uttarakhand" into the name field of the first element of the states array (states[0]).
    // The name field is a character array (char name[50]), so it has enough space to store the string.
    // strcpy() takes the string on the right side and places it inside the character array on the left side.
    char *uk[] = {"Dehradun", "Haridwar", "Rishikesh", "Nainital", "Tehri", "Rudrapur"};
    // Declares a local array of pointers to string literals. This is a convenient temporary list of district names for this state.
    states[0].districtCount = 6;
    // Sets the districtCount field of the first state (Uttarakhand) to 6, indicating that there are 6 districts in this state.
    for (int i = 0; i < 6; i++)
        strcpy(states[0].districts[i].name, uk[i]);
    // Here we used this strcpy(states[0].districts[i].name, uk[i]); to copy each district name from the uk array into the corresponding districts array inside the states[0] struct.
    // Loop over the 6 district names and copy each into the districts array inside states[0]. Each districts[i].name has space (50 chars), so strcpy is safe given these literals.

    // State 2: Uttar Pradesh
    strcpy(states[1].name, "Uttar Pradesh");
    char *up[] = {"Lucknow", "Kanpur", "Varanasi", "Agra", "Noida", "Prayagraj"};
    states[1].districtCount = 6;
    for (int i = 0; i < 6; i++)
        strcpy(states[1].districts[i].name, up[i]);

    // State 3: Rajasthan
    strcpy(states[2].name, "Rajasthan");
    char *raj[] = {"Jaipur", "Jodhpur", "Udaipur", "Ajmer", "Kota", "Bikaner"};
    states[2].districtCount = 6;
    for (int i = 0; i < 6; i++)
        strcpy(states[2].districts[i].name, raj[i]);

    // State 4: Maharashtra
    strcpy(states[3].name, "Maharashtra");
    char *mh[] = {"Mumbai", "Pune", "Nagpur", "Nashik", "Aurangabad", "Thane"};
    states[3].districtCount = 6;
    for (int i = 0; i < 6; i++)
        strcpy(states[3].districts[i].name, mh[i]);

    // State 5: Karnataka
    strcpy(states[4].name, "Karnataka");
    char *ka[] = {"Bengaluru", "Mysuru", "Mangalore", "Udupi", "Hubli", "Belgaum"};
    states[4].districtCount = 6;
    for (int i = 0; i < 6; i++)
        strcpy(states[4].districts[i].name, ka[i]);
}

/* THIS IS THE FARE CALCULATION PART OF THE SYSTEM */
// Here we use strcmp() stands for string compare.
//  It checks if two strings are exactly the same.(strcmp(string1, string2))
// and it returns 0 if they are equal.

float calculateFare(char mode[], char seat[])
{
    if (strcmp(mode, "Bus") == 0)
    { // This is for the Bus
        if (strcmp(seat, "AC Sleeper") == 0)
            return 700;
        if (strcmp(seat, "AC Seater") == 0)
            return 500;
        if (strcmp(seat, "Non AC") == 0)
            return 300;
    }
    else
    { // This is for the Train
        if (strcmp(seat, "General") == 0)
            return 150;
        if (strcmp(seat, "Sleeper") == 0)
            return 300;
        if (strcmp(seat, "3AC") == 0)
            return 800;
        if (strcmp(seat, "2AC") == 0)
            return 1200;
        if (strcmp(seat, "1AC") == 0)
            return 1800;
    }
    return 0;
}

/* THIS IS THE SAVE TICKET PART OF THE SYSTEM */
// void is used to save the ticket information to a file named "ticket_records.txt".
//  It appends the ticket details to the file for record-keeping.

// This function takes a Ticket structure (t) as input.
// Its job is to save ticket details into a file.
// void means it does not return anything.
void saveTicket(struct Ticket t)
{
    FILE *fp = fopen("ticket_records.txt", "a");
    // Opens the file "ticket_records.txt" in append mode ("a").
    // If the file does not exist, it will be created.
    if (fp == NULL)
    {
        printf("Error saving ticket.\n");
        return;
    }

    fprintf(fp, "Mode: %s\n", t.mode);
    // fprintf is used to write formatted data to the file pointed to by fp.
    // And t.mode accesses the mode field of the Ticket struct t.
    fprintf(fp, "Seat: %s\n", t.seatType);
    fprintf(fp, "State: %s\n", t.state);
    fprintf(fp, "District: %s\n", t.district);
    fprintf(fp, "Tickets: %d\n", t.tickets);
    fprintf(fp, "Total Fare: %.2f\n", t.totalFare);

    fclose(fp);
    // fclose is used to close the file that was opened using fopen.
}

/* THIS IS THE BOOKING FUNCTION PART OF THE SYSTEM */

void bookTicket(struct State states[])
// This function handles the ticket booking process...

{
    struct Ticket t;
    // Here we declare a variable t of type struct Ticket to hold the ticket details.
    int stateChoice, districtChoice, seatChoice, modeChoice;
    // Here we declare integer variables to store user choices for state, district, seat type, and mode of transport.

    printf("\nChoose Mode:\n1. Bus\n2. Train\nEnter choicee: ");
    scanf("%d", &modeChoice);
    // Here we prompt the user to choose a mode of transport (Bus or Train) and read their choice into modeChoice.
    getchar();

    if (modeChoice == 1)
        strcpy(t.mode, "Bus!");
    else
        strcpy(t.mode, "Train!");

    // Select State
    printf("\nSelect State?:\n");
    for (int i = 0; i < MAX_STATES; i++)
        // Here we loop through the states array to display the available states to the user.
        // MAX_STATES is a constant that defines the total number of states available.
        printf("%d. %s\n", i + 1, states[i].name);

    printf("Enter choice: ");
    scanf("%d", &stateChoice);
    getchar();
    stateChoice--;
    // Decrement stateChoice to convert from 1-based to 0-based index.

    strcpy(t.state, states[stateChoice].name);
    // strcpy(destination, source);

    // Select District
    printf("\nSelect District:\n");
    for (int i = 0; i < states[stateChoice].districtCount; i++)
        printf("%d. %s\n", i + 1, states[stateChoice].districts[i].name);

    printf("Enter choice: ");
    scanf("%d", &districtChoice);
    getchar();
    districtChoice--;

    strcpy(t.district, states[stateChoice].districts[districtChoice].name);
    // strcpy is used to copy the name of the selected district from the states array into the district field of the Ticket struct t.

    // Seat type selection
    if (strcmp(t.mode, "Bus") == 0)
    // strcmp is used to compare the mode of transport stored in t.mode with the string "Bus".
    {
        printf("\nSeat Type:\n1. AC Sleeper\n2. AC Seater\n3. Non AC\nEnter: ");
        scanf("%d", &seatChoice);
        getchar();

        if (seatChoice == 1)
            strcpy(t.seatType, "AC Sleeper");
        else if (seatChoice == 2)
            strcpy(t.seatType, "AC Seater");
        else
            strcpy(t.seatType, "Non AC");
    }
    else
    {
        printf("\nSeat Type:\n1. General\n2. Sleeper\n3. 3AC\n4. 2AC\n5. 1AC\nEnter: ");
        scanf("%d", &seatChoice);
        getchar();

        if (seatChoice == 1)
            strcpy(t.seatType, "General");
        else if (seatChoice == 2)
            strcpy(t.seatType, "Sleeper");
        else if (seatChoice == 3)
            strcpy(t.seatType, "3AC");
        else if (seatChoice == 4)
            strcpy(t.seatType, "2AC");
        else
            strcpy(t.seatType, "1AC");
    }

    printf("\nEnter number of tickets: ");
    scanf("%d", &t.tickets);

    float perTicket = calculateFare(t.mode, t.seatType);
    t.totalFare = perTicket * t.tickets;

    // Save to file
    saveTicket(t);

    printf("\nTicket Booked Successfully!\n");
    printf("Total Fare:  %.2f\n", t.totalFare);
}

/* THIS IS THE MAIN PART OF THE SYSTEM. */

int main()
{
    struct State states[MAX_STATES];
    // Here we declare an array states of type struct State with a size of MAX_STATES to hold the state information.
    loadStates(states);
    // This function call initializes the states array with predefined state names and their corresponding districts.

    int choice;

    while (1)
    {
        printf("------TICKET BOOKING SYSTEM------\n");

        printf("1. Book Ticket\n");
        printf("2. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // This line reads the user's choice for the main menu.

        if (choice == 1)
        {
            bookTicket(states);
        }
        else if (choice == 2)
        {
            printf("Thank you for using the system!\n");
            break;
        }
        else
        {
            printf("Invalid option. Try again!\n");
        }
    }

    return 0;
}
