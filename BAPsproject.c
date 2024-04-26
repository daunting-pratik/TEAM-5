#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct account
{
    char fname[50];
    char lname[50];
    char bloodgroup[4];
    int age;
    char mail[50];
    char password[64];
    char conformp[64];
    char location[60];
    char Contactno[15];
    int useruniqueno;
} newuser;

typedef struct donation
{
    char fname[50];
    char lname[50];
    char bloodgroup[4];
    char hospital[50];
    char date[11]; 
} donation;

int signup = 0;
newuser newDonor;

void addaccountFunction()
{
   printf("Enter your Name: \n");
    scanf("%49s%49s", newDonor.fname, newDonor.lname);
    // getchar();

    
    printf("Enter your Age: \n");
    scanf("%d", &newDonor.age);
    // getchar();

    printf("Enter your bloodgroup: \n");
    scanf("%s", newDonor.bloodgroup);
    // getchar();

    printf("Enter your Contact no.: \n");
    scanf("%s", newDonor.Contactno);
    // getchar();

    printf("Enter your Location: \n");
    scanf("%s", newDonor.location);
    // getchar();

    printf("Enter your E-mail address: \n");
    scanf("%49s", newDonor.mail);
    // getchar();

password:
    printf("Enter a strong password (Note: Enter a password more than 8 characters):\n ");
    scanf("%63s", newDonor.password);
    getchar();

    printf("Confirm your password: \n");
    scanf("%63s", newDonor.conformp);
    getchar();

    if (strcmp(newDonor.password, newDonor.conformp) == 0)
    {
        if (strlen(newDonor.password) >= 8)
        {
            printf("Password matched.\n");

            // Save user data to file
            FILE *file = fopen("user_data.txt", "a");
            if (file != NULL)
            {
                fprintf(file, "Name: %s %s\n", newDonor.fname,  newDonor.lname);
                fprintf(file, "Age: %d\n", newDonor.age);
                fprintf(file, "Contact no.: %s\n", newDonor.Contactno);
                fprintf(file, "Location: %s\n", newDonor.location);
                fprintf(file, "E-mail address: %s\n", newDonor.mail);
                fprintf(file,"Password:%s\n",newDonor.password);
                fprintf(file,"BloodGroup:%s/n",newDonor.bloodgroup);
                fprintf(file, "\n");
                fclose(file);
            }
            else
            {
                printf("Error opening file for writing.\n");
            }
        }
        else
        {
            printf("Weak password. Please enter a password with at least 8 characters.\n");
            goto password;
        }
    }
    else
    {
        printf("Passwords do not match. Please try again.\n");
        goto password;
    }

    printf("Your account has been successfully registered. Sign in to help those in need.\n");
}

void signinFunction()
{
    char email[50];
    char pass[64];

    printf("Enter your Email or Contact no.: ");
    scanf("%49s", email);

    printf("Enter your password: ");
    scanf("%63s", pass);

    if ((strcmp(email, newDonor.mail) == 0 || strcmp(email, newDonor.Contactno) == 0) && strcmp(pass, newDonor.password) == 0)
    {
        signup = 1;
        printf("Sign in successful.\n");
    }
    else
    {
        printf("Incorrect email or password. Please try again.\n");
    }
}

void donateBloodFunction()
{
    printf("1. City Hospital\n2. Teaching Hospital\n3. Kantipur Hospital\n");

    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);

    char hospital[50];
    switch (choice)
    {
    case 1:
        strcpy(hospital, "City Hospital");
        break;
    case 2:
        strcpy(hospital, "Teaching Hospital");
        break;
    case 3:
        strcpy(hospital, "Kantipur Hospital");
        break;
    default:
        printf("Invalid choice.\n");
        return;
    }

    donation newDonation;
    strcpy(newDonation.fname, newDonor.fname);
    strcpy(newDonation.lname, newDonor.lname);
    strcpy(newDonation.bloodgroup, newDonor.bloodgroup);
    strcpy(newDonation.hospital, hospital);

    printf("Enter the date of donation (YYYY-MM-DD): ");
    scanf("%s", newDonation.date);

    // Save donation data to file
    FILE *file = fopen("donation_data.txt", "a");
    if (file != NULL)
    {
        fprintf(file, "Name: %s %s\n", newDonation.fname,newDonation.lname);
        fprintf(file, "Blood Group: %s\n", newDonation.bloodgroup);
        fprintf(file, "Hospital: %s\n", newDonation.hospital);
        fprintf(file, "Date: %s\n", newDonation.date);
        fprintf(file, "\n");
        fclose(file);
    }
    else
    {
        printf("Error opening file for writing.\n");
    }

    printf("Thank you for donating blood at %s.\n", hospital);
}

void needBloodFunction()
{
    FILE *file = fopen("needblood.txt", "r");
    if (file != NULL)
    {
         printf("Name: \t Contact no.:\tBlood group: \tLocation: \t\n");
        newuser user;
        while (fscanf(file, "Name: %49s %49s\nContact no.: %14s\nBlood group: %3s\nLocation: %59s\n\n",
                      user.fname,user.lname, user.Contactno, user.bloodgroup, user.location) != EOF)
        {

            printf(" %s %s\t  %s\t  %s\t %s\t\n", user.fname,user.lname, user.Contactno, user.bloodgroup, user.location);
        }
        fclose(file);
    }
    else
    {
        printf("Error opening file for reading.\n");
    }
}

void addNeedBloodRecord()
{
    newuser user;

    printf("Enter Name: ");
    scanf("%49s%49s", user.fname, user.lname);
        getchar();


    printf("Enter Contact no.: ");
    scanf("%14s", user.Contactno);
    getchar();

    printf("Enter Blood group: ");
    scanf("%3s", user.bloodgroup);
    getchar();

    printf("Enter Location: ");
    scanf("%59s", user.location);
    getchar();

    FILE *file = fopen("needblood.txt", "a");
    if (file != NULL)
    {
        printf("Name\t contact no:\t bloodgroup\t location\t");
        fprintf(file, "Name: %s %s\tContact no.: %s\tBlood group: %s\t Location: %s\t\n", user.fname,user.lname, user.Contactno, user.bloodgroup, user.location);
        fclose(file);
        printf("Record added successfully.\n");
    }
    else
    {
        printf("Error opening file for writing.\n");
    }
}

int main()
{
    int accountchoice;
    int choice;

    while (1)
    {
        printf("\n \t BLOODLink\n");
        printf("1. Create an Account \t 2. Sign in \t 3. Exit program\n");
        scanf("%d", &accountchoice);

        switch (accountchoice)
        {
        case 1:
            addaccountFunction();
            break;
        case 2:
            signinFunction();
            break;
        case 3:
            printf("Exiting the program.\n");
            exit(0);
        default:
            printf("Invalid input. Please try again.\n");
            break;
        }

        if (signup == 1)
        {
            printf("\n \t BLOOD MANAGEMENT SYSTEM\n");
            printf("1. Donate Blood \t 2. Need Blood 3. Exit program\n");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                donateBloodFunction();
                break;
            case 2:
                needBloodFunction();
                break;
            case 3:
                printf("Exiting the program.\n");
                exit(0);
             case 4:
                addNeedBloodRecord();
                break;
            default:
                break;
            }
        }
    }

    return 0;
}
