#include <stdio.h>
#include <string.h>

int menuDriven(void);
int login(void);
void checkIn(void);
void checkOut(void);
void displayData(void);

struct user
{
    char username[20];
    char password[20];
};

struct user s[3] = {{"nazmul", "Nazmul@123"},
                    {"mubasshir", "Mubasshir@123"},
                    {"mostafa", "Mostafa@123"}};

int main(void)
{
    while (1)
    {
        int isLogin = login();

        if (isLogin != -1)
        {
            printf("\nLogin Successful.\n");
            printf("Welcome Back \"%s\"\n\n", s[isLogin].username);
            break;
        }
        else
            printf("\nLogin Usuccessful.\nPlease Enter a Valid username and password.\n\n");
    }

    while (1)
    {
        int userChoice = menuDriven();

        if (userChoice == 1)
            checkIn();
        else if (userChoice == 2)
            checkOut();
        else if (userChoice == 3)
            displayData();
        else if (userChoice == 4)
        {
            printf("\nSuccesfully Logged Out.\n");
            break;
        }
    }

    return 0;
}

int menuDriven(void)
{
    int n;

    while (1)
    {
        printf("=====Hotel Marvel=====\n\n");
        printf("Enter 1 for Check in.\n");
        printf("Enter 2 for Checkout.\n");
        printf("Enter 3 to Display all the Guest's Data.\n");
        printf("Enter 4 Logout.\n");

        scanf("%d", &n);

        if (n >= 1 && n <= 4)
            return n;
        else
            printf("Enter a Valid Number.\n\n");
    }
}

int login(void)
{
    printf("=====Login=====\n\n");

    char name[20];
    char pass[20];

    printf("Username: ");
    scanf(" %s", &name);

    printf("Password: ");
    scanf(" %s", &pass);

    for (int i = 0; i < 3; i++)
        if ((strcmp(name, s[i].username) == 0) && (strcmp(pass, s[i].password) == 0))
            return i;

    return -1;
}

void checkIn(void)
{
    char NIDno[50], name[100], phoneNo[50], checkIndate[20], checkOutDate[20];

    printf("=====Check in=====\n\n");

    while (1)
    {
        printf("Enter NID No: ");
        gets(NIDno);

        if (strlen(NIDno) == 10)
            break;
        else
            printf("NID No Should be 10 Digit.\n\n");
    }

    while (1)
    {
        printf("Enter Name: ");
        gets(name);

        if (strlen(name) <= 20)
            break;
        else
            printf("Name Should NOT Exceed 20 Charecters.\n\n");
    }

    while (1)
    {
        printf("Enter Phone No: ");
        gets(phoneNo);

        if (strlen(phoneNo) == 11)
            break;
        else
            printf("Phone No Should be 11 Digit.\n\n");
    }

    printf("Enter Check in Date (00-00-0000): ");
    gets(checkIndate);

    printf("Enter Checkout Date (00-00-0000): ");
    gets(checkOutDate);

    FILE *userData = fopen("userData.txt", "a");

    fprintf(userData, "%-10s  %-20s  %-11s  %-10s  %-10s\n", NIDno, name, phoneNo, checkIndate, checkOutDate);

    fclose(userData);

    printf("\n\n");
}

void checkOut(void)
{
    char NIDno[50];

    printf("=====Checkout=====\n\n");

    while (1)
    {
        printf("Enter NID No: ");
        gets(NIDno);

        if (strlen(NIDno) == 10)
            break;
        else
            printf("NID No Should be 10 Digit.\n\n");
    }

    char line[100], tmpNIDno[50];
    int lineNo = 0, flag = 0;

    FILE *userData = fopen("userData.txt", "r");

    while (1)
    {
        if (fgets(line, 100, userData) == '\0')
            break;

        sscanf(line, "%s", tmpNIDno);

        if (strcmp(NIDno, tmpNIDno) != 0)
            lineNo++;
        else
        {
            flag = 1;
            break;
        }
    }

    fclose(userData);

    if (flag == 0)
        printf("Didn't Found NID No.\n");
    else
    {
        int count = 0;

        FILE *userData = fopen("userData.txt", "r");
        FILE *tmpUserData = fopen("tmpUserData.txt", "w");

        while (1)
        {
            if (fgets(line, 100, userData) == '\0')
                break;

            if (lineNo != count)
                fprintf(tmpUserData, "%s", line);

            count++;
        }

        fclose(userData);
        fclose(tmpUserData);

        remove("userData.txt");
        rename("tmpUserData.txt", "userData.txt");

        printf("\nCheckout Successful.\n\n");
    }
}

void displayData(void)
{
    char line[100];

    FILE *userData = fopen("userData.txt", "r");

    printf("=====All the Guest's Data=====\n\n");

    while (1)
    {
        if (fgets(line, 100, userData) == '\0')
            break;

        printf("%s", line);
    }

    fclose(userData);

    printf("\n\n");
}