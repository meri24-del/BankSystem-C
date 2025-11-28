#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <conio.h> 


#define admin_username "admin"
#define admin_password "project"
#define admin_firstname "Group Five"
#define admin_lastname "Bank System"
#define FOODJAM_based_acc 2101012145

#define max_acc 100

  /*5. Bank Management System

Description: Create a simple banking system where users can 
create accounts, 
deposit/withdraw money, and 
check balance. 

>>>>Admins can view all accounts.


Concepts:

Data Structures: Arrays or linked lists to manage multiple accounts.
File Handling: Store account data persistently.
Functions: Account creation, deposit, withdrawal, and balance inquiry.*/

void clear_screen() {
  
    system("cls");
}


typedef struct 
{
    int accountnumber;
    char firstname[20];
    char lastname[20];
    char username[50];
    char password[50];
    char contact[15];
    float balance;

} Accounts;

Accounts member[max_acc]; 
int member_count = 0; 


void initialize_file() {
    FILE *database = fopen("accountinglist.csv", "r"); 
    
    if (!database) { 
        
        database = fopen("accountinglist.csv", "w"); 
        if (!database) { 
            perror("Unable to create file"); 
            exit(1); 
        }
        fprintf(database, "AccountNumber,FirstName,LastName,Username,Password,Contact,Balance\n"); 
    }
    fclose(database);
}

void read_password(char *password, size_t size) {
    int i = 0;
    char ch;

    while (i < size - 1) {
        ch = _getch(); 

        if (ch == '\r') { 
            break;
        } else if (ch == '\b') { 
            if (i > 0) {
                i--;
                printf("\b \b"); 
            }
        } else {
            password[i++] = ch;
            printf("*"); 
        }
    }

    password[i] = '\0'; 
    printf("\n");
}

int symbol(char ch) { 
    return (ch >= 33 && ch <= 47) || (ch >= 58 && ch <= 64) || 
           (ch >= 91 && ch <= 96) || (ch >= 123 && ch <= 126); 
    } 

int valid_password(char *password) { 
    int has_upper = 0;
    int has_lower = 0;
    int has_digit = 0;
    int has_symbol = 0;

    if (strlen(password) < 8) 
    return 0; 
    
    for (int i = 0; i < strlen(password); i++) { 
        
        if (password[i] >= 'A' && password[i] <= 'Z') has_upper = 1; 
        else if (password[i] >= 'a' && password[i] <= 'z') has_lower = 1; 
        else if (password[i] >= '0' && password[i] <= '9') has_digit = 1; 
        else if (symbol(password[i])) has_symbol = 1; 
        } 
        
        return has_upper && has_lower && has_digit && has_symbol;

}

int contact_digit(char *str) { 
    for (int i = 0; i < strlen(str); i++) { 
        if (str[i] >= '0' && str[i] <= '9') { 
            return 1; 
        } 
    } 
        return 0; 
} 
            
int valid_contact(const char *contact) {
    if (strlen(contact) != 10 || contact[0] != '9') {
        return 0; 
    }
    for (int i = 0; i < 10; i++) {
        if (contact[i] < '0' || contact[i] > '9') {
            return 0; 
        }
    }
    return 1; 
}

int names_digit(const char *str) {
    while (*str) {
        if (*str >= '0' && *str <= '9') { 
            return 1; 
        }
        str++;
    }
    return 0; 
}

void load_from_file() {

     initialize_file(); 
    FILE *database = fopen("accountinglist.csv", "r"); 
    if (!database) { 
        printf("No existing accounts found. Starting fresh.\n"); 
        return;
    }

    char buffer[256]; 
    
    
    fgets(buffer, sizeof(buffer), database); 

    while (fgets(buffer, sizeof(buffer), database)) { 
        Accounts acctmem; 
        sscanf(buffer, "%d,%19[^,],%19[^,],%49[^,],%49[^,],%14[^,],%f", 
               &acctmem.accountnumber,
               acctmem.firstname,
               acctmem.lastname,
               acctmem.username,
               acctmem.password,
               acctmem.contact,
               &acctmem.balance);

        member[member_count++] = acctmem;
    }
 
    fclose(database);
}

void save_to_file() {
    FILE *database = fopen("accountinglist.csv", "w");
    if (!database) {
        perror("Unable to open file");
        return;
    }

    fprintf(database, "AccountNumber,FirstName,LastName,Username,Password,Contact,Balance\n");
    for (int i = 0; i < member_count; i++) {
        fprintf(database, "%d,%s,%s,%s,%s,%s,%.2f\n",
                member[i].accountnumber,
                member[i].firstname,
                member[i].lastname,
                member[i].username,
                member[i].password,
                member[i].contact,
                member[i].balance);
    }
    fclose(database);
}

void Update_FirstName(int logged_member) {
    char new_firstname[50];

    clear_screen();
    printf("Update your First Name or type 'exit' to go back.\n");
    printf("Current First Name: %s\n", member[logged_member].firstname);

    while (1) {
        printf("New First Name: ");
        fgets(new_firstname, sizeof(new_firstname), stdin);
        new_firstname[strcspn(new_firstname, "\n")] = '\0'; // Remove newline

        if (strcmp(new_firstname, "exit") == 0) {
            clear_screen();
            return;
        }

        if (!names_digit(new_firstname)) {
            strcpy(member[logged_member].firstname, new_firstname);
            save_to_file();
            clear_screen();
            printf("First Name successfully updated!\n");
            break;
        } else {
            clear_screen();
            printf("Invalid input! First Name should not contain numbers.\n");
        }
    }
}

void Update_LastName(int logged_member) {
    char new_lastname[50];

    clear_screen();
    printf("Update your Last Name or type 'exit' to go back.\n");
    printf("Current Last Name: %s\n", member[logged_member].lastname);

    while (1) {
        printf("New Last Name: ");
        fgets(new_lastname, sizeof(new_lastname), stdin);
        new_lastname[strcspn(new_lastname, "\n")] = '\0'; 

        if (strcmp(new_lastname, "exit") == 0) {
            clear_screen();
            return;
        }

        if (!names_digit(new_lastname)) {
            strcpy(member[logged_member].lastname, new_lastname);
            save_to_file();
            clear_screen();
            printf("Last Name successfully updated!\n");
            break;
        } else {
            clear_screen();
            printf("Invalid input! Last Name should not contain numbers.\n\n");
        }
    }
}

void Update_ContactNumber(int logged_member) {
    char new_contact[15];

    clear_screen();
    printf("Update your Contact Number or type 'exit' to go back.\n");
    printf("Current Contact Number: %s\n", member[logged_member].contact);

    while (1) {
        printf("New Contact Number (must be 10 digits and start with 9): +63 ");
        fgets(new_contact, sizeof(new_contact), stdin);
        new_contact[strcspn(new_contact, "\n")] = '\0'; 

        if (strcmp(new_contact, "exit") == 0) {
            clear_screen();
            return;
        }

        if (valid_contact(new_contact)) {
            strcpy(member[logged_member].contact, new_contact);
            save_to_file();
            clear_screen();
            printf("Contact Number successfully updated!\n");
            break;
        } else {
            clear_screen();
            printf("Invalid contact number. Please try again.\n\n");
        }
    }
}

void Update_Username(int logged_member) {
    char new_username[50];

    clear_screen();
    printf("Update your Username or type 'exit' to go back.\n");
    printf("Current Username: %s\n", member[logged_member].username);

    while (1) {
        printf("New Username: ");
        fgets(new_username, sizeof(new_username), stdin);
        new_username[strcspn(new_username, "\n")] = '\0'; 

        if (strcmp(new_username, "exit") == 0) {
            clear_screen();
            return;
        }

        int username_exists = 0;
        for (int i = 0; i < member_count; i++) {
            if (strcmp(member[i].username, new_username) == 0) {
                username_exists = 1;
                break;
            }
        }

        if (username_exists) {
            clear_screen();
            printf("Username already exists! Please choose a different username.\n\n");
        } else {
            strcpy(member[logged_member].username, new_username);
            save_to_file();
            clear_screen();
            printf("Username successfully updated!\n");
            break;
        }
    }
}

void Update_Password(int logged_member) {
    char new_password[50];

    clear_screen();
    printf("Update your Password or type 'exit' to go back.\n");

    while (1) {
        printf("* Password must be at least 8 characters long\n");
        printf("* Password must contain upper case letters\n");
        printf("* Password must contain lower case letters\n");
        printf("* Password must contain numbers\n");
        printf("* Password must contain symbols\n\n");
        printf("New Password: ");
        read_password(new_password, sizeof(new_password));

        if (strcmp(new_password, "exit") == 0) {
            clear_screen();
            return;
        }

        if (valid_password(new_password)) {
            strcpy(member[logged_member].password, new_password);
            save_to_file();
            clear_screen();
            printf("Password successfully updated!\n");
            break;
        } else {
            clear_screen();
            printf("Invalid password. Please follow the password requirements.\n");
        }
    }
}

void save_new_account(Accounts new_user) { 
    FILE *database = fopen("accountinglist.csv", "a");  
    if (!database) {
        perror("Unable to open file for appending");
        return;
    } 

    fprintf(database, "%d,%s,%s,%s,%s,%s,%.2f\n", 
            new_user.accountnumber,
            new_user.firstname,
            new_user.lastname,
            new_user.username,
            new_user.password,
            new_user.contact,
            new_user.balance);

    fclose(database);
}

void Edit_Profile(int logged_member) {
    int subselection;

    while (1) {
        printf("0. Back\n");
        printf("1. First Name\n");
        printf("2. Last Name\n");
        printf("3. Contact Number\n");
        printf("4. User Name\n");
        printf("5. Change Password\n\n");
        printf("Select which one you want to modify: ");

        if (scanf("%d", &subselection) != 1) {
            while (getchar() != '\n');
            clear_screen();
            printf("\nInvalid Input! Please enter a number.\n");
            continue;
        }
        getchar(); 

        switch (subselection) {
            case 0:
                clear_screen();
                return;

            case 1:
            
                Update_FirstName(logged_member);
                break;

            case 2:
                Update_LastName(logged_member);
                break;

            case 3:
                Update_ContactNumber(logged_member);
                break;

            case 4:
                Update_Username(logged_member);
                break;

            case 5:
                Update_Password(logged_member);
                break;

            default:
                clear_screen();
                printf("Invalid Input! Please try again.\n");
                break;
        }
    }
}

int Account_Profile(int logged_member) {
    int selection;
    float deposit, withdraw;

    while (1) {
        printf("Hello, %s!\n", member[logged_member].username);

        printf("1. Profile Details\n");
        printf("2. Edit Profile\n");
        printf("3. Deposit\n");
        printf("4. Withdraw\n");
        printf("5. View Balance\n");
        printf("6. Logout\n\n");
        printf("Enter selection: ");

        if (scanf("%d", &selection) != 1) {
            while (getchar() != '\n'); 
            clear_screen();
            printf("\nInvalid Input! Please enter a number.\n");
            continue;
        }
        getchar(); 

        switch (selection) {
            case 1:
                clear_screen();
                printf("---------------------------\n");
                printf("Account Number: %d\n", member[logged_member].accountnumber);
                printf("First Name: %s\n", member[logged_member].firstname);
                printf("Last Name: %s\n", member[logged_member].lastname);
                printf("Contact Number: %s\n", member[logged_member].contact);
                printf("---------------------------\n");
                break;

            case 2:
                clear_screen();
                Edit_Profile(logged_member);
                break;

            case 3:
                clear_screen();
                printf("Enter deposit amount: ");
                if (scanf("%f", &deposit) == 1 && deposit > 0) {
                    member[logged_member].balance += deposit;
                    save_to_file();
                    clear_screen();
                    printf("Deposit successful!\n");
                    printf("New balance: %.2f\n", member[logged_member].balance);
                } else {
                    printf("Invalid deposit amount.\n");
                }
                break;

            case 4:
                clear_screen();
                printf("Enter withdraw amount: ");
                if (scanf("%f", &withdraw) == 1 && withdraw > 0) {
                    if (withdraw > member[logged_member].balance) {
                        clear_screen();
                        printf("Insufficient funds! Current balance: %.2f\n", member[logged_member].balance);
                    } else {
                        member[logged_member].balance -= withdraw;
                        save_to_file();
                        clear_screen();
                        printf("Withdrawal successful!\n");
                        printf("New balance: %.2f\n", member[logged_member].balance);
                    }
                } else {
                    printf("Invalid withdrawal amount.\n");
                }
                break;

            case 5:
                clear_screen();
                printf("---------------------------\n");
                printf("Balance: %.2f\n", member[logged_member].balance);
                printf("---------------------------\n");
                break;

            case 6:
                clear_screen();
                return 0;

            default:
                clear_screen();
                printf("Invalid Input! Please try again.\n");
                break;
        }
    }
}

void Account_Registration() {
    clear_screen();
    if (member_count >= max_acc) {
        clear_screen();
        printf("Registration limit reached!\n");
        return;
    }

    Accounts new_user;

    printf("---------------------------\n");
    printf("REGISTRATION FORM\n");
    printf("---------------------------\n");
    printf("Fill in the required fields or type 'exit' to return to main menu.\n\n");

    //reg firstname
    do {
        printf("First Name: ");
        fgets(new_user.firstname, sizeof(new_user.firstname), stdin);
        new_user.firstname[strcspn(new_user.firstname, "\n")] = '\0';

        if (strcmp(new_user.firstname, "exit") == 0) {
            clear_screen();
            return;
        }

        if (names_digit(new_user.firstname)) {
            printf("Invalid input! First name should not contain numbers.\n\n");
        }
    } while (names_digit(new_user.firstname));

    //reg lastname
    do {
        printf("Last Name: ");
        fgets(new_user.lastname, sizeof(new_user.lastname), stdin);
        new_user.lastname[strcspn(new_user.lastname, "\n")] = '\0';

        if (strcmp(new_user.lastname, "exit") == 0) {
            clear_screen();
            return;
        }

        if (names_digit(new_user.lastname)) {
            printf("Invalid input! Last name should not contain numbers.\n\n");
        }
    } while (names_digit(new_user.lastname));

    // reg contact
    do {
        printf("Contact Number (must be 10 digits and start with 9): +63 ");
        fgets(new_user.contact, sizeof(new_user.contact), stdin);
        new_user.contact[strcspn(new_user.contact, "\n")] = '\0';

        if (strcmp(new_user.contact, "exit") == 0) {
            clear_screen();
            return;
        }

        if (!valid_contact(new_user.contact)) {
            printf("Invalid contact number. Please try again.\n");
        }
    } while (!valid_contact(new_user.contact));

    
    char full_contact[15] = "+63";
    strcat(full_contact, new_user.contact);
    strcpy(new_user.contact, full_contact);

    // reg username
    a:
    printf("Create Username: ");
    fgets(new_user.username, sizeof(new_user.username), stdin);
    new_user.username[strcspn(new_user.username, "\n")] = '\0';

    for (int i = 0; i < member_count; i++) {
        if (strcmp(member[i].username, new_user.username) == 0) {
            printf("Username already exists! Please choose a different username.\n");
            goto a;
        } else if (strcmp(new_user.username, "exit") == 0) {
            clear_screen();
            return;
        }
    }

    printf("* Password must be at least 8 characters long\n");
    printf("* Password must contain upper case letters\n");
    printf("* Password must contain lower case letters\n");
    printf("* Password must contain numbers\n");
    printf("* Password must contain symbols\n\n");

    //reg password
    do {
    printf("Create Password: ");
    read_password(new_user.password, sizeof(new_user.password));

    if (!valid_password(new_user.password)) {
        printf("* Password must be at least 8 characters long\n");
        printf("* Password must contain upper case letters\n");
        printf("* Password must contain lower case letters\n");
        printf("* Password must contain numbers\n");
        printf("* Password must contain symbols\n\n");
        printf("Invalid password. Please try again.\n\n");
    }
} while (!valid_password(new_user.password));

    new_user.balance = 0.0;
    new_user.accountnumber = FOODJAM_based_acc + (member_count + 1);
    member[member_count++] = new_user;

    save_to_file();

    clear_screen();
    printf("Account created successfully!\n");
    printf("---------------------------\n\n");
}

void memberlist(){


      if (member_count == 0) {
        clear_screen();
        printf("---------------------------\n");
        printf("No members found.\n");
        printf("---------------------------\n");
        return;
    }

    for (int i = 0; i < member_count; i++)
    {
       
            
            printf("Member [%d]\n", i + 1);
            printf("Account number: %d\n", member[i].accountnumber);
            printf("Balance: %.2f\n", member[i].balance);
            printf("First Name: %s\n", member[i].firstname);
            printf("Last Name: %s\n", member[i].lastname);
            printf("Contact Number: %s\n", member[i].contact);

            printf("\n---------------------------\n");

            printf("Username: %s\n", member[i].username);
            printf("Password: %s\n", member[i].password);

            printf("\n---------------------------\n");

        
        
        
    }
    return;
}

void account_admin(){

    int selection;

while (1){
    printf("Administrator Mode");
    printf("\n---------------------------\n");

    printf("1. Profile\n");
    printf("2. Account Members List\n");
    printf("3. Logout\n");

    printf("Enter selection: ");
    if (scanf("%d", &selection) != 1){

        printf("Invalid Input! Please enter a number!\n");
        continue;
    }

    switch (selection)
    {
    case 1:
        clear_screen();
        printf("---------------------------\n");
        printf("First Name: %s\n", admin_firstname);
        printf("Last Name: %s\n", admin_lastname);
        printf("---------------------------\n");

        break;
    
    case 2:

        clear_screen();
        memberlist();
        break;

    case 3:
        clear_screen();
        return;
        
    default:

        clear_screen();
        printf("Invalid Input! Please enter again!\n");
        break;
    }
}
}

void Account_Login() {
    Accounts login_user;
    int login_success = 0;
    int logged_user_index = -1;

    while (1) {
        printf("Username: ");
        fgets(login_user.username, sizeof(login_user.username), stdin);
        login_user.username[strcspn(login_user.username, "\n")] = '\0';

        if (strcmp(login_user.username, "exit") == 0) {
            clear_screen();
            return;
        }

        printf("Password: ");
read_password(login_user.password, sizeof(login_user.password));

        if (strcmp(login_user.username, admin_username) == 0 && strcmp(login_user.password, admin_password) == 0) {
            clear_screen();
            printf("\n\n---------------------------\n");
            printf("Admin Login Successful!\n");
            printf("---------------------------\n");
            account_admin();
            return;
        }

        for (int i = 0; i < member_count; i++) {
            if (strcmp(login_user.username, member[i].username) == 0 && strcmp(login_user.password, member[i].password) == 0) {
                clear_screen();
                printf("\n\n---------------------------\n");
                printf("Login Successful!\n");
                printf("\n---------------------------\n");

                logged_user_index = i;
                login_success = 1;
                break;
            }
        }

        if (login_success) {
            clear_screen();
            Account_Profile(logged_user_index);
            break;
        } else {
            clear_screen();
            printf("Username or password did not match! \nPlease enter again or type 'exit' to return to the main menu.\n\n");
        }
    }
}

void main_menu(){

    int selection;

    
    while (1){

        printf("Welcome to Philippine Cyber Bank!\n\n");

            printf("1. Account Registration\n");
            printf("2. Account Login\n");
            printf("3. Exit\n\n");

            printf("If you have concerns, kindly email us at pcb.contactus@gmail.com");
            printf("\n\n---------------------------\n");
            
            printf("Enter selection: ");
            
                if (scanf("%d", &selection) != 1) {
           
                    while (getchar() != '\n');
                    clear_screen();
                    printf("\nInvalid Input! Please enter a number.\n");
                    printf("---------------------------\n");
                    continue;
            }

            getchar();

                switch (selection){

                            case 1:

                                    clear_screen();
                                    Account_Registration();
                                    break;

                            case 2:

                                    clear_screen();
                                    Account_Login();
                                    break;

                            case 3:
                                    clear_screen();
                                    printf("\nThank you for using Philippine Cyber Bank! \n\nHave a great day!\n");
                                    return;

                            default:

                                    clear_screen();
                                    printf("Invalid Input!\nPlease enter again!\n");
                                    printf("---------------------------\n");
                                    break;
                                    

                }

        }
        

}

int main(void){

    load_from_file();
    main_menu();

    return 0;
}