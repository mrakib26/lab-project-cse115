/*
 > Program Name        : Blood Book Management System
 > Developers          : Md. Rakibul Islam Sagor (2522028042)
                         Chiranjeet Sarkar Amit ()
                         Md. Zahidul Haque ()
                         Kaushik Sharma ()
 > Last Modified Date  : 08-08-2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 40
#define MAX_PHONE 25
#define MAX_ADDR 100
#define MAX_EMAIL 30
#define MAX_BLOOD 10

// structure for contact
typedef struct {
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    char address[MAX_ADDR];
    char email[MAX_EMAIL];
    char blood[MAX_BLOOD];
    int age;
    float weight;
} Contact;

// function prototypes
void showMenu();
void addContact();
void listContacts();
void searchByName();
void searchByBlood();
void editContact();
void deleteContact();
void exitProgram();

// file pointer
FILE *fp;

int main(void) {
    int choice;

    do {
        showMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // absorb newline

        switch (choice) {
            case 1: addContact(); break;
            case 2: listContacts(); break;
            case 3: searchByName(); break;
            case 4: editContact(); break;
            case 5: deleteContact(); break;
            case 6: searchByBlood(); break;
            case 0: exitProgram(); break;
            default: printf("Invalid choice. Try again.\n");
        }

        printf("\nPress Enter to continue...");
        getchar();
        system("cls");

    } while (choice != 0);

    return 0;
}

void showMenu() {
    printf("\n==== Blood Book Management System ====");
    printf("\n1. Add Contact");
    printf("\n2. List All Contacts");
    printf("\n3. Search by Name");
    printf("\n4. Edit Contact");
    printf("\n5. Delete Contact");
    printf("\n6. Search by Blood Group");
    printf("\n0. Exit");
    printf("\n======================================\n");
}

void addContact() {
    Contact c;
    fp = fopen("contacts.dat", "ab");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Age: ");
    scanf("%d", &c.age);
    getchar();

    printf("Enter Weight (in kg): ");
    scanf("%f", &c.weight);
    getchar();

    if (c.age <= 18 || c.weight < 50) {
        printf("\nYou are not eligible to donate blood. Must be over 18 and weight at least 50kg.\n");
        fclose(fp);
        return;
    }
    else printf("You are eligible to donate blood.\nPlease enter the following details as mentioned.");

    printf("\nEnter Name: ");
    fgets(c.name, MAX_NAME, stdin); strtok(c.name, "\n");

    printf("Enter Phone: ");
    fgets(c.phone, MAX_PHONE, stdin); strtok(c.phone, "\n");

    printf("Enter Address: ");
    fgets(c.address, MAX_ADDR, stdin); strtok(c.address, "\n");

    printf("Enter Email: ");
    fgets(c.email, MAX_EMAIL, stdin); strtok(c.email, "\n");

    printf("Enter Blood Group: ");
    fgets(c.blood, MAX_BLOOD, stdin); strtok(c.blood, "\n");

    fwrite(&c, sizeof(Contact), 1, fp);
    fclose(fp);
    printf("Contact added successfully!\n");
}

void listContacts() {
    Contact c;
    fp = fopen("contacts.dat", "rb");
    if (!fp) {
        printf("No contacts found.\n");
        return;
    }

    printf("\n==== Contact List ====\n");
    while (fread(&c, sizeof(Contact), 1, fp)) {
        printf("\nName       : %s\n", c.name);
        printf("Phone      : %s\n", c.phone);
        printf("Address    : %s\n", c.address);
        printf("Email      : %s\n", c.email);
        printf("Blood Group: %s\n", c.blood);
        printf("Age        : %d\n", c.age);
        printf("Weight     : %.2f kg\n", c.weight);
        printf("--------------------------\n");
    }
    fclose(fp);
}

void searchByName() {
    char searchName[MAX_NAME];
    Contact c;
    int found = 0;

    printf("\nEnter name to search: ");
    fgets(searchName, MAX_NAME, stdin); strtok(searchName, "\n");

    fp = fopen("contacts.dat", "rb");
    if (!fp) {
        printf("File not found!\n");
        return;
    }

    while (fread(&c, sizeof(Contact), 1, fp)) {
        if (strcasecmp(c.name, searchName) == 0) {
            printf("\nFound Contact:\n");
            printf("Name: %s\nPhone: %s\nAddress: %s\nEmail: %s\nBlood Group: %s\nAge: %d\nWeight: %.2f kg\n",
                   c.name, c.phone, c.address, c.email, c.blood, c.age, c.weight);
            found = 1;
            break;
        }
    }
    if (!found) printf("Contact not found.\n");
    fclose(fp);
}

void searchByBlood() {
    char blood[MAX_BLOOD];
    Contact c;
    int found = 0;

    printf("\nEnter blood group to search: ");
    fgets(blood, MAX_BLOOD, stdin); strtok(blood, "\n");

    fp = fopen("contacts.dat", "rb");
    if (!fp) {
        printf("File not found!\n");
        return;
    }

    printf("\nMatching Contacts:\n");
    while (fread(&c, sizeof(Contact), 1, fp)) {
        if (strcasecmp(c.blood, blood) == 0) {
            printf("Name: %s, Phone: %s, Age: %d, Weight: %.2f kg\n", c.name, c.phone, c.age, c.weight);
            found = 1;
        }
    }
    if (!found) printf("No matches found.\n");
    fclose(fp);
}

void editContact() {
    char name[MAX_NAME];
    Contact c;
    int found = 0;
    FILE *temp;

    printf("\nEnter the name of the contact to edit: ");
    fgets(name, MAX_NAME, stdin); strtok(name, "\n");

    fp = fopen("contacts.dat", "rb");
    temp = fopen("temp.dat", "wb");
    if (!fp || !temp) {
        printf("Error accessing file.\n");
        return;
    }

    while (fread(&c, sizeof(Contact), 1, fp)) {
        if (strcasecmp(c.name, name) == 0) {
            printf("\nEnter new details:\n");
            printf("Age: "); scanf("%d", &c.age); getchar();
            printf("Weight: "); scanf("%f", &c.weight); getchar();
            printf("Name: "); fgets(c.name, MAX_NAME, stdin); strtok(c.name, "\n");
            printf("Phone: "); fgets(c.phone, MAX_PHONE, stdin); strtok(c.phone, "\n");
            printf("Address: "); fgets(c.address, MAX_ADDR, stdin); strtok(c.address, "\n");
            printf("Email: "); fgets(c.email, MAX_EMAIL, stdin); strtok(c.email, "\n");
            printf("Blood Group: "); fgets(c.blood, MAX_BLOOD, stdin); strtok(c.blood, "\n");
            found = 1;
        }
        fwrite(&c, sizeof(Contact), 1, temp);
    }
    fclose(fp);
    fclose(temp);

    remove("contacts.dat");
    rename("temp.dat", "contacts.dat");

    if (found) printf("Contact updated successfully.\n");
    else printf("Contact not found.\n");
}

void deleteContact() {
    char name[MAX_NAME];
    Contact c;
    int found = 0;
    FILE *temp;

    printf("\nEnter the name of the contact to delete: ");
    fgets(name, MAX_NAME, stdin); strtok(name, "\n");

    fp = fopen("contacts.dat", "rb");
    temp = fopen("temp.dat", "wb");
    if (!fp || !temp) {
        printf("Error accessing file.\n");
        return;
    }

    while (fread(&c, sizeof(Contact), 1, fp)) {
        if (strcasecmp(c.name, name) != 0) {
            fwrite(&c, sizeof(Contact), 1, temp);
        } else {
            found = 1;
        }
    }
    fclose(fp);
    fclose(temp);

    remove("contacts.dat");
    rename("temp.dat", "contacts.dat");

    if (found) printf("Contact deleted successfully.\n");
    else printf("Contact not found.\n");
}

void exitProgram() {
    printf("\nThank you for using the Blood Book Management System.\n");
}
