/*===============| Declarations & Prototypes |===============*/
#define Coffee_Price 125
#define Mokka_Price 150
#define Choco_Price 100
#define Dishwater_Price 500

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "HAL.h"

FILE *f;
int Coffee_Stock;
int Mokka_Stock;
int Choco_Stock;
int Dishwater_Stock;

int Change_Stock;

/*==================| events |==================*/
typedef enum{
                E_10C, E_20C, E_50C, E_100C, E_Not_Enough_Money, E_Enough_Money, E_Start, E_Continue, E_Coffee, E_Mokka,
                E_Choco, E_DishwasherWater, E_OutOfStock, E_AdminMode, E_Restock, E_EmptyChange, E_AddChange100, E_ExitAdmin,
                E_Shutdown
            }
event_t;
/*==================| states |==================*/
typedef enum { S_Idle, S_Initialisation, S_Wait_For_Selection, S_Wait_For_Money, S_Amount_Check, S_Admin_Mode, S_Wait_For_Admin_Selection
}
state_t;

state_t event_handler(event_t event);
void initialize(int *money);
void add_10(int *money);
void add_20(int *money);
void add_50(int *money);
void add_100(int *money);
event_t check_amount(const int money);
event_t coin_insertion();
event_t Selection();
event_t AdminModeSelect();

void WriteToFile();
void ReadFromFIle();

void Restock();

int Price = 125;
char drinkName[255];

/*===============| main program |===============*/

int main()
{
    event_handler(E_Start);

    return 0;
}

/*================| functions. |================*/

state_t event_handler(event_t event) {
    static state_t state = S_Idle;
    static int money = 0;
    state_t next_state;

    while (1) {
        // Source States/Events
        switch (state) {
        case S_Idle:
            switch (event) {
            case E_Start:
                // Mealy Action
                // (code here)
                // Destination State
                next_state = S_Initialisation;
                break;
            }
            break;

        case S_Initialisation:
            switch (event) {
            case E_Continue:
                // Mealy Action
                // (code here)
                // Destination State
                next_state = S_Wait_For_Selection;
                break;
            }
            break;
        case S_Wait_For_Selection:
            next_state = S_Wait_For_Money;

            switch (event) {
            case E_Coffee:
                strcpy(drinkName, "Coffee");
                Price = Coffee_Price;
                break;
            case E_Mokka:
                strcpy(drinkName, "Mokka");
                Price = Mokka_Price;
                break;
            case E_Choco:
                strcpy(drinkName, "Choco");
                Price = Choco_Price;
                break;
            case E_DishwasherWater:
                strcpy(drinkName, "DishwasherWater");
                Price = Dishwater_Price;
                break;
            case E_AdminMode:
                next_state = S_Admin_Mode;
                break;
            case E_OutOfStock:
                printf("\nThis item is out of stock,please make a different selection\n");
                next_state = S_Wait_For_Selection;
                break;
            }
            break;
        case S_Wait_For_Money:
            switch (event) {
            case E_10C:
                // Mealy Action
                add_10(&money);
                // Destination State
                next_state = S_Amount_Check;
                break;


            case E_20C:
                // Mealy Action
                add_20(&money);
                // Destination State
                next_state = S_Amount_Check;
                break;


            case E_50C:
                // Mealy Action
                add_50(&money);
                // Destination State
                next_state = S_Amount_Check;
                break;

            case E_100C:
                add_100(&money);
                next_state = S_Amount_Check;
                break;
            }
            break;
        case S_Amount_Check:
            switch (event) {
            case E_Not_Enough_Money:
                // Mealy Action
                printf("\n Not Enough Money:%d", money);
                // Destination State
                next_state = S_Wait_For_Money;
                break;

            case E_Enough_Money:
                // Mealy Action
                dispense_coffee(money, Price, drinkName, &Change_Stock, &Coffee_Stock, &Mokka_Stock, &Choco_Stock, &Dishwater_Stock);
                WriteToFile();
                // Destination State
                next_state = S_Initialisation;
                break;
            }
            break;

        case S_Admin_Mode:
            // Default Destination State
            next_state = S_Admin_Mode;
            switch (event) {
            case E_Restock:
                // Mealy Action
                Restock();
                puts("Restocked!");
                break;
            case E_AddChange100:
                // Mealy Action
                Change_Stock += 100;
                WriteToFile();
                puts("Added 100 cents");
                break;
            case E_EmptyChange:
                // Mealy Action
                Change_Stock = 0;
                WriteToFile();
                puts("Emptied change!");
                break;
            case E_ExitAdmin:
                // Mealy Action
                system("@cls||clear");
                // Destination State
                next_state = S_Initialisation;
                break;
            case E_Shutdown:
                // Mealy Action
                WriteToFile();
                exit(0);
            }
            break;
        }
        /*=========| Destination States |=========*/
        switch (next_state) {
        case S_Initialisation:
            // Moore Action
            initialize(&money);
            // Event Generation
            event = E_Continue;
            break;
        case S_Wait_For_Selection:
            // Moore Action
            event = Selection();
            // Event Generation/Preparation
            event = event;
            break;

        case S_Admin_Mode:
            // Moore Action
            system("@cls||clear");
            puts("Welcome to the admin mode");
            event = AdminModeSelect();
            // Event Generation/Preparation
            event = event;
            next_state = S_Admin_Mode;
            break;

        case S_Wait_For_Money:
            // Moore Action
            printf("\nI have the %s if you have the coin. (%d cent)\n", drinkName, Price);
            event = coin_insertion();
            // Event Generation/Preparation
            event = event;
            break;
        case S_Amount_Check:
            // Moore Action
            event = check_amount(money);
            // Event Generation/Preparation
            event = event;
            break;
        }
        state = next_state;
    }
}


/*===============| Initialization |===============*/
void initialize(int *money) {
    *money = 0;
    ReadFromFIle();
}

/*==============| Money Inserted Logic. |==============*/
void add_10(int *money) {
    *money += 10;
    Change_Stock += 10;
    WriteToFile();
}

void add_20(int *money) {
    *money += 20;
    Change_Stock += 20;
    WriteToFile();
}

void add_50(int *money) {
    *money += 50;
    Change_Stock += 50;
    WriteToFile();
}

void add_100(int *money) {
    *money += 100;
    Change_Stock += 100;
    WriteToFile();
}

/*===============| Amount Check Event |===============*/
event_t check_amount(const int money) {
    return (money < Price) ? E_Not_Enough_Money : E_Enough_Money;
}

/*============| Coin Selection interface |============*/
event_t coin_insertion() {
    int sel;
    while (1)
    {
        puts("Select your coin");
        puts("1-- 10 Cent");
        puts("2-- 20 Cent");
        puts("3-- 50 Cent");
        puts("4-- 100 Cent");

        scanf("%d", &sel);
        getchar();

        switch (sel)
        {
        case 1:
            return E_10C;
            break;
        case 2:
            return E_20C;
            break;
        case 3:
            return E_50C;
            break;
        case 4:
            return E_100C;
            break;
        default:
            puts("Wrong Selection");
        }

    }
}

/*============| Main selection interface |============*/
event_t Selection() {
    int sel;
    while (1)
    {
        puts("Select your drink");
        puts("1-- Coffee");
        puts("2-- Mokka");
        puts("3-- Choco");
        puts("4-- DishwasherWater");

        scanf("%d", &sel);
        getchar();

        switch (sel)
        {
        case 1:
            if (Coffee_Stock > 0)
                return E_Coffee;
            else
                return E_OutOfStock;
            break;
        case 2:
            if (Mokka_Stock > 0)
                return E_Mokka;
            else
                return E_OutOfStock;
            break;
        case 3:
            if (Choco_Stock > 0)
                return E_Choco;
            else
                return E_OutOfStock;
            break;
        case 4:
            if (Dishwater_Stock > 0)
                return E_DishwasherWater;
            else
                return E_OutOfStock;
            break;
        case 1234:
            return E_AdminMode;
            break;
        default:
            puts("Wrong Selection");
            break;
        }

    }
}

/*===========| Admin mode selection interface |===========*/
event_t AdminModeSelect() {
    int sel;

    while (1)
    {
        puts("\nSelect your option:");
        puts("1-- Refill all");
        puts("2-- Empty change");
        puts("3-- Add 100 cents to change");
        puts("4-- Exit admin mode");
        puts("5-- Shutdown");

        scanf("%d", &sel);
        getchar();
        switch (sel) {
        case 1:
            return E_Restock;
            break;
        case 2:
            return E_EmptyChange;
            break;
        case 3:
            return E_AddChange100;
            break;
        case 4:
            return E_ExitAdmin;
            break;
        case 5:
            return E_Shutdown;
            break;
        default:
            puts("Wrong Selection");
            break;
        }
    }
}

/*===================| Serialization |===================*/

void WriteToFile() {
    // INITIALIZE
    f = fopen("Stock.stock", "w+");
    fprintf(f, "%d\n%d\n%d\n%d\n%d", Coffee_Stock, Mokka_Stock, Choco_Stock, Dishwater_Stock, Change_Stock);
    fclose(f);
}

void ReadFromFIle() {
    f = fopen("Stock.stock", "r");
    fscanf(f, "%d\n%d\n%d\n%d\n%d", &Coffee_Stock, &Mokka_Stock, &Choco_Stock, &Dishwater_Stock, &Change_Stock);
}


void Restock() {
    Coffee_Stock = 10;
    Mokka_Stock = 10;
    Choco_Stock = 10;
    Dishwater_Stock = 10;
    WriteToFile();
}
