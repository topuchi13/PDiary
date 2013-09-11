/********************************************************
**  CS50x Final project:                                *
**                                                      *
**  Personal Diary Management Software + Tic-tac-toe    *
**                                                      *
**  Author: Nika Topuria          This is CS50 :).      *
********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <Math.h>
#include <direct.h>

// Prototypes
void makerec();
void viewrec();
void editrec();
void deleterec();
void setpassword();
void editpassword();
bool password();
void vigenere_encode(char text[1000]);
void vigenere_decode(char fname[20]);
void tictactoe(void);

// This function implements a correct version of modulo function.
static int mod(int a, int base)
{
    return (a < 0 ? ((a % base) + base) % base : a % base);
}

/*
Main function first check if pass.psw file is in program directory, if true - asks for a current password, invalid
password makes program exit, otherwise it goes to the main menu. I used switch function to define actions for each
possible user entered number.
*/

int main ()
{
    // check for first run, if true - creates folder for records and calls setpassword()
    if (fopen(".\\records\\pass.psw", "r") == NULL)
    {
        mkdir(".\\records");
        chdir(".\\records");
        setpassword();
    }
    else
    {

        chdir(".\\records");    //changes current folder to .\\records
        if (password() == true)

        {

            for (;;) //for loop to get back to main menu after other function exits
            {
                system ("cls");
                printf ("********************************************\n");
                printf ("****This is your personal diary software****\n");
                printf ("********************************************\n\n");

                printf ("Please chose your desired action(input a corresponding number): \n\n");
                printf ("1. Make a new record\n");
                printf ("2. View a record\n");
                printf ("3. Edit a record\n");
                printf ("4. Delete a record\n");
                printf ("5. Play a nice game of TIC-TAC-TOE :D\n");
                printf ("6. Change your p.diary password\n");
                printf ("7. Leave your p.diary\n\n");
                int a;
                scanf ("%1d", &a); //gets user choise

                switch (a) //checks usr input and calls needed functions
                {
                case 1:

                    makerec();
                    break;
                case 2:

                    viewrec();

                    break;
                case 3:

                    editrec();

                    break;
                case 4:

                    deleterec();

                    break;
                case 5:
                    tictactoe();
                    break;
                case 6:
                    editpassword();
                    break;
                case 7:
                    printf ("Thank you for using this software\n");
                    exit(0);
                default:
                    printf ("You entered a wrong number, Try again");
                    break;
                }
            }
            return 0;
        }
    }
}

/*
    Function bellow creates a record in the program direcory (function vigenere_encode() encodes user entered text).
*/
void makerec()
{

    system ("cls"); //clears screen
    printf ("***************************\n");
    printf ("****Welcome to add menu****\n");
    printf ("***************************\n\n");
    char name[21];  // declares char array for file name
    printf ("Enter the name of new record:(Max. length - 20)\n\n");
    fflush(stdin);
    scanf ("%21s", name); // get filename from stdin
    int t = access(name,F_OK);     // checks if selected record exists
    if ( t == 0)
    {
        printf ("\nFile [%s] already exists\n", name);
        printf("\nPress Enter to go to the main menu!!!\n");
        fflush(stdin);
        getch();
        return;
    }
    printf ("\nWrite your record bellow:\n\n");
    char text[1000];
    fflush(stdin);
    fgets(text, 1000, stdin); //get record from user
    int length = strlen(text);
    for ( int i = 0; i < length; i++ )  // puts eof in the end of string
    {
        if ( text[i] == '\n' )
        {
            text[i] = '\0';
            break;
        }
    }
    vigenere_encode(text); //encodes record
    fflush(stdin);
    rename(".\\temp.enc", name); // renames temp file created by vigenere_encode()
    printf("\nYou Entered this text: \n\n");
    printf("%s\n", text);
    printf("\nYour record has been succesfully added\n\n");
    printf("Would you like to make another recording? <y/n>"); //code bellow asks user if hi/shi wants to view another rec.
    char q;
    fflush(stdin);
    scanf("%1c",&q);
    if (q == 'y')   //checks if user wants to make another rec.
        makerec();
    else
        printf("Press Enter to go to the main menu!!!");
    getch();
}

/*
    Function for viewing alredy entered record.
*/
void viewrec()
{
    system ("cls"); //clears screen
    printf ("****************************\n");
    printf ("****Welcome to view menu****\n");
    printf ("****************************\n\n");
    system ("dir"); //shows the content of program directory
    char name[21];
    printf ("Enter the name of record you want to view\n\n");
    scanf ("%21s", name); // gets filename from user
    int t = access(name,F_OK);     // checks if selected record exists
    if ( t != 0)
    {
        printf ("\nFile [%s] doesn't exist\n", name);
        printf("\nPress Enter to go to the main menu!!!\n");
        fflush(stdin);
        getch();
        return;
    }
    vigenere_decode(name); // decodes recording
    printf("\nWould you like to view another recording? <y/n>"); //code bellow asks user if hi/shi wants to view another rec.
    char q;
    fflush(stdin);
    scanf("%1c",&q);
    if (q == 'y')
        viewrec();
    else
        printf("\nPress Enter to go to the main menu!!!");
    getch();
}


/*
    Changes the content of recording (user have to input whole rec. allover).
*/
void editrec()
{
    system ("cls");//clears screen
    printf ("****************************\n");
    printf ("****Welcome to edit menu****\n");
    printf ("****************************\n\n");
    printf("\nWarning: Editing recording completely erases previous one!!!\n\n\n");
    system ("dir");//shows the content of program directory
    char name[21];
    printf ("Enter the name of record you want to edit\n\n");
    fflush(stdin);
    scanf ("%21s", name);
    int t = access(name,F_OK);     // checks if selected record exists
    if ( t != 0)
    {
        printf ("\nFile [%s] doesn't exist\n", name);
        printf("\nPress Enter to go to the main menu!!!\n");
        fflush(stdin);
        getch();
        return;
    }
    FILE *fp = fopen(name, "r+"); //loads file
    vigenere_decode(name);  //shows content of user requested rec.
    char text[1000];    //declares char array
    printf("\nEnter the edited record below:\n\n");
    fflush(stdin);
    fgets(text, 1000, stdin);   // Gets new user input
    vigenere_encode(text); //encodes user input
    fflush(stdin);
    fclose (fp); //closes file pointer
    remove(name);   //removes original rec. file
    fflush(stdin);
    rename(".\\temp.enc", name); //renames temp file to user entered name
    printf("\n%s\n", text);
    printf("Your record has been changed succesfully\n");
    printf("\nWould you like to edit another recording? <y/n>"); //code bellow asks user if hi/shi wants to view another rec.
    char q;
    fflush(stdin);
    scanf("%1c",&q);
    if (q == 'y')   //checks if user wants to edit another rec.
        editrec();
    else
        printf("\nPress Enter to go to the main menu!!!");
    getch();

}

/*
    Function to delete records
*/
void deleterec()
{
    if (password() == true) // call to password() function
    {
        system("cls");  //clears the screen
        printf ("*************************************\n");
        printf ("****Welcome to rec. deletion menu****\n");
        printf ("*************************************\n\n");
        system("dir");  //displays the curent directory contents
        printf("Enter the name of record you want to delete:\n\n");
        char name[21];  // declares char aray for file name
        scanf("%s", name); //gets file name
        int t = access(name,F_OK);     // checks if selected record exists
        if ( t != 0)
        {
            printf ("\nFile [%s] doesn't exist\n", name);
            printf("\nPress Enter to go to the main menu!!!\n");
            fflush(stdin);
            getch();
            return;
        }
        remove(name); // removes file
        printf("\nWould you like to delete another recording? <y/n>"); //code bellow asks user if hi/shi wants to view another rec.
        char q;
        fflush(stdin);
        scanf("%1c",&q);
        if (q == 'y')   //checks if user wants to dlelete another rec.
            deleterec();
        else
            printf("\nPress Enter to go to the main menu!!!");
        getch();
    }
}

/*
    Function to edit curent password
*/
void editpassword()
{
    system("attrib -h -s -r pass.psw"); //removes pass.psw file attributes to un-(hidden, system  and read only)
    system ("cls"); // clears screen
    printf ("*********************************\n");
    printf ("****Welcome to pass.edit menu****\n");
    printf ("*********************************\n\n");
    int t = access(".\\pass.psw",F_OK);     // checks if pass.psw file exists
    if ( t != 0)
    {
        printf ("\nError: You don't have any current password\n");
        fflush(stdin);
    }
    else
    {
        if (password() == true) // call to password() function
        {
            FILE *fp = fopen(".\\pass.psw", "w+"); // loads pass.psw file
            char pass[21]; //declares char array for new password
            printf("\nEnter the new password for your p.diary:");
            fflush(stdin);
            fgets(pass, 21, stdin); //gets new password from user
            int length = strlen(pass); // gets the length of new password
            for ( int i = 0; i < length; i++ )  //puts EOF in the end of string
            {
                if ( pass[i] == '\n' )
                {
                    pass[i] = '\0';
                    break;
                }
            }
            fputs(pass, fp); //puts new password into file
            system("attrib +h +s +r pass.psw"); //sets pass.psw attributes
            fclose (fp); //closes file pointer
            printf("\nYour password has been succesfully changed\n");
            getch();
        }
    }
}

/*
    Function to set a password
*/
void setpassword()
{
    FILE *fp; //declare file pointer
    fp = fopen("pass.psw", "w+"); //opens pass.psw file
    char pass[21];  //declares char array for new password
    printf("Please enter a password for your p.diary(Max. length - 20):");
    fgets(pass, 21, stdin); //gets new password from stdin
    int length = strlen(pass);  //gets the length of new password
    for ( int i = 0; i < length; i++ ) //puts EOF sign in the end of string
    {
        if ( pass[i] == '\n' )
        {
            pass[i] = '\0';
            break;
        }
    }
    fputs(pass, fp);    //puts new password to file
    fclose (fp);
    system("attrib +h +s +r pass.psw"); //sets file attributes
    printf("Your password has been succesfully stored\n");
    printf ("Please restart your p.diary to apply new password. (Press any key to exit)");
    getch();
}

/*
    Function to ask user for a password
*/
bool password()
{
    FILE *fp;   //declare file pointer
    fp = fopen(".\\pass.psw", "r"); //opens pass.psw file
    char buffer[21];    //declares char array for current password
    fflush(stdin);
    fgets(buffer, 21, fp);  //gets the password from file
    char test[21];  //declares char array for user-entered password
    int length = strlen(buffer);//gets the length of current password
    printf("Current Password Length - %d", length); //prints out a hint
    printf("\nPlease enter your current password:");
    fflush(stdin);
    fgets(test, 21, stdin); //gets user input via sdtin
    for ( int i = 0; i < length; i++ ) //puts EOF sign in the end of string
    {
        if ( test[i] == '\n' )
        {
            test[i] = '\0';
            break;
        }
    }
    for (int i=0; i < length; i++)  //compares curent and inputed password char by char
    {
        if (buffer[i] == test[i])
            continue;
        else
        {
            printf("\nYou have entered a wrong password.\n");
            printf("\nPress Enter to go to the main menu!!!");
            getch();
            return false;
        }
    }
    return true;
}


/*
    Implementation of vigenere cypher encoder
*/
void vigenere_encode(char text[1000])
{
    char *a;
    char k;
    // Opens a temp. file
    FILE *fp;
    fp = fopen(".\\temp.enc", "w");
    a = "topuchi"; // Defines keyword
    int m = strlen(a);
    int n = strlen(text);
    char buffer[n];
    int j = 0;
    fflush(stdin);
    for (int q = 0; q < n; q++ )                       // the next 16 lines of code makes all the magic
    {
        if (j == m)
            j = 0;
        int w = text[q];
        if (text[q] >= 97 && text[q] < 123)             // Checks if a[j] is lower case
        {
            if ( a[j] >= 97 && a[j] < 123 )
                k = a[j] - 97;
            else
                k = a[j] - 65;
            int out = ((((w - 97) + k)) % 26) + 97;
            buffer [q] = out;

        }
        else if (text[q] >= 65 && text[q] < 91)         // Checks if a[j] is upper case
        {
            if ( a[j] >= 65 && a[j] < 91 )
                k = a[j] - 65;
            else
                k = a[j] - 97;
            int out = ((((w - 65) + k)) % 26) + 65;
            buffer [q] = out;

        }
        else                                        // prints out every non alpha characters without encoding
            buffer [q] = w;

        if (k == (a[j] - 97) || k == (a[j] - 65))
            j++;
        fflush(stdin);
    }
    fputs(buffer, fp);
    fclose(fp);
}


/*
    Implementation of vigenere cypher decoder
*/
void vigenere_decode(char fname[20])
{
    char *a;
    char k;
    char text[1000];
    int y;
    int c = 0;
    FILE *fp;
    fp = fopen(fname, "r");
    do
    {
        y = getc(fp);
        text[c] = y;
        c++;
    }
    while (y != EOF);
    c = 0;
    a = "topuchi";
    int m = strlen(a);
    int n = strlen(text);
    char buffer[n];
    int j = 0;
    fflush(stdin);
    for (int q = 0; q < n; q++ )                       // the next 16 lines of code makes all the magic
    {
        if (j == m)
            j = 0;
        int w = text[q];
        if (text[q] >= 97 && text[q] < 123)             // Checks if a[j] is lower case
        {
            if ( a[j] >= 97 && a[j] < 123 )
                k = a[j] - 97;
            else
                k = a[j] - 65;
            int out = mod(((w - 97) - k),26) + 97;
            buffer [q] = out;

        }
        else if (text[q] >= 65 && text[q] < 91)         // Checks if a[j] is upper case
        {
            if ( a[j] >= 65 && a[j] < 91 )
                k = a[j] - 65;
            else
                k = a[j] - 97;
            int out = mod(((w - 65) - k),26) + 65;
            buffer [q] = out;

        }
        else                                        // prints out every non alpha characters without decoding
            buffer [q] = w;

        if (k == (a[j] - 97) || k == (a[j] - 65))
            j++;
        fflush(stdin);
    }
    fflush(stdin);
    printf("\nContent of selected recording: \n\n");
    int x;
    do
    {
        x = buffer[c];
        putchar(x);
        c++;
    }
    while (x != EOF);
    printf("\n");
    fclose(fp);
}

/*
    Implementation of simple tictactoe game with user definable line/row number
*/

void tictactoe(void)
{
    system("cls");  //clears the screen
    //Welcome screen
    printf ("***********************************\n");
    printf ("*********-TIC - TAC - TOE-*********\n");
    printf ("***********************************\n\n");


    char sign,sign2,name[41],name2[41];  // declaration of variables
    //next 6 lines asks players for their names and gets them
    printf ("Enter the name of player 1:(Max. length - 40)\n\n");
    fflush(stdin);
    scanf ("%41s", name);
    printf ("\nEnter the name of player 2:(Max. length - 40)\n\n");
    fflush(stdin);
    scanf ("%41s", name2);

    //Array which represents game board
    char board [3][3] =
    {
        {'1','2','3'},
        {'4','5','6'},
        {'7','8','9'},
    };
    int x,y; // board numbering variables
    int i = 0; // variable to determine game result
    fflush(stdin);
    // next 6 lines asks user if hi/she want's to play with x or o
    do
    {
        fflush(stdin);
        printf("\n%s - Do you want to play with /x/ or /o/?(Enter corresponding char.)\n\n", name);
        scanf("%1c", &sign);
        if (sign == 'x' || sign == 'X')
        {
            sign2 = 'o';
            break;
        }
        else if (sign == 'o' || sign == 'O')
        {
            sign2 = 'x';
            break;
        }
        else
        {
            printf("\n\nYou entered incorrect gamesign");
            getch();
        }
    }
    while (1);
    for (int g = 0; g < 5; g++) // for loop, which loops until winner is present, or it's draw.
    {
        // prints clear game board
        printf("\n\n");
        printf("   0   1   2\n\n");
        printf("0  %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
        printf("  ---+---+---\n");
        printf("1  %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
        printf("  ---+---+---\n");
        printf("2  %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
        fflush(stdin);

        // asks player 1 to play and gets coordinates
        do
        {
            fflush(stdin);
            printf("\n\n%s - Enter desired coordinates to place - %c [row column]: ", name, sign);
            scanf("%d %d", &x, &y );
            if (x < 0 || x > 3 || x < 0 || y > 3)
                printf("\n\nYou entered coordinates out of board range.");
            else
                continue;

        }
        while(x < 0 || x > 3 || x < 0 || y > 3);
        // sets corresponding box to x
        if (x >= 0 && x <= 3 && y >=0 && y <= 3)
        {
            board[x][y] = sign;
        }
        // prints the new view of board
        printf("\n\n");
        printf("   0   1   2\n\n");
        printf("0  %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
        printf("  ---+---+---\n");
        printf("1  %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
        printf("  ---+---+---\n");
        printf("2  %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
        fflush(stdin);

        // checks if there is winner (diagonals)
        if((board[0][0] == board[1][1] && board[0][0] == board[2][2]) || (board[0][2] == board[1][1] && board[0][2] == board[2][0]))
        {
            i = 1;
            printf("\n\nThe winner is - %s", name);
            printf("\n\nWould you like to play again? <y/n>"); //code bellow asks user if hi/shi wants to play again
            char q;
            fflush(stdin);
            scanf("%1c",&q);
            if (q == 'y')   //checks user input
                tictactoe();
            else
                printf("\n\nPress Enter to go to the main menu!!!");
            getch();
            return;
        }
        else
        {
            // check if there is a winner (rows and columns)
            for(int line = 0; line <= 2; line ++)
                if((board[line][0] == board[line][1] && board[line][0] == board[line][2]) || (board[0][line] == board[1][line] && board[0][line] == board[2][line]))
                {
                    i = 1;
                    printf("\n\nThe winner is - %s", name);
                    printf("\n\nWould you like to play again? <y/n>"); //code bellow asks user if hi/shi wants to play again
                    char q;
                    fflush(stdin);
                    scanf("%1c",&q);
                    if (q == 'y')   //checks if user wants to make another rec.
                        tictactoe();
                    else
                        printf("\n\nPress Enter to go to the main menu!!!");
                    getch();
                    return;
                }
        }
        if (g == 4) // if 9 steps were made by players game will stop and declare draw
            break;
        // asks player 2 to play and gets coordinates
        do
        {
            fflush(stdin);
            printf("\n\n%s - Enter desired coordinates to place - %c [rows columns]: ", name2, sign2);
            scanf("%d %d", &x, &y );
            if (x < 0 || x > 3 || x < 0 || y > 3)
                printf("\n\nYou entered coordinates out of board range.");
            else
                continue;
        }
        while(x < 0 || x > 3 || x < 0 || y > 3);

        // sets corresponding box to x
        if (x >= 0 && x <= 3 && y >=0 && y <= 3)
        {
            board[x][y] = sign2;
        }
        // checks if there is winner (diagonals)
        if((board[0][0] == board[1][1] && board[0][0] == board[2][2]) || (board[0][2] == board[1][1] && board[0][2] == board[2][0]))
        {
            i = 2;
            printf("The winner is - %s", name2);
            printf("\n\nWould you like to play again? <y/n>"); //code bellow asks user if hi/shi wants to play again
            char q;
            fflush(stdin);
            scanf("%1c",&q);
            if (q == 'y')   //checks if user wants to make another rec.
                tictactoe();
            else
                printf("\n\nPress Enter to go to the main menu!!!");
            getch();
            return;
        }
        else
            // check if there is a winner (rows and columns)
        {
            for(int line = 0; line <= 2; line ++)
                if((board[line][0] == board[line][1] && board[line][0] == board[line][2]) || (board[0][line] == board[1][line] && board[0][line] == board[2][line]))
                {
                    i = 2;
                    printf("The winner is - %s", name2);
                    printf("\n\nWould you like to play again? <y/n>"); //code bellow asks user if hi/shi wants to play again
                    char q;
                    fflush(stdin);
                    scanf("%1c",&q);
                    if (q == 'y')   //checks if user wants to make another rec.
                        tictactoe();
                    else
                        printf("\n\nPress Enter to go to the main menu!!!");
                    getch();
                    return;
                }
        }
    }
    // next 11 lines of code tells user if there is draw
    if (i == 0)
    {
        printf("\n\nWhooaa, It's a draw :D");
        printf("\n\nWould you like to play again? <y/n>"); //code bellow asks user if hi/shi wants to play again
        char q;
        fflush(stdin);
        scanf("%1c",&q);
        if (q == 'y')   //checks if user wants to make another rec.
            tictactoe();
        else
            printf("\n\nPress Enter to go to the main menu!!!");
        getch();
        return;
    }
    else
        // tells user if there happened smthing unexpected
    {
        printf("\n\nSomething was screwed up, no winners, no draw :P");
        printf("\n\nWould you like to play again? <y/n>"); //code bellow asks user if hi/shi wants to play again
        char q;
        fflush(stdin);
        scanf("%1c",&q);
        if (q == 'y')   //checks if user wants to make another rec.
            tictactoe();
        else
            printf("\n\nPress Enter to go to the main menu!!!");
        getch();
        return;
    }

}
