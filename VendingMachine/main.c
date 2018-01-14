//*************************************** Declarations & Prototypes
#define Coffee_Price 125
#define Mokka_Price 150
#define Choco_Price 100
#define Dishwater_Price 500

#include <stdio.h>
#include <string.h>
#include <conio.h>

FILE *f;
int Coffee_Stock;
int Mokka_Stock;
int Choco_Stock;
int Dishwater_Stock;

int Change_Stock;

// your events
typedef enum { E_10C, E_20C, E_50C, E_100C, E_Not_Enough_Money, E_Enough_Money, E_Start, E_Continue, E_Coffe, E_Mokka, E_Choco, E_DishwasherWater, E_OutOfStock, E_AdminMode, E_Restock, E_EmptyChange, E_ExitAdmin}
event_t;
//your states
typedef enum { S_Idle, S_Initialisation, S_Wait_For_Selection, S_Wait_For_Money, S_Amount_Check, S_Admin_Mode, S_Wait_For_Admin_Selection
}
state_t;

state_t event_handler(event_t event);
void initialize(int *money);
void dispense_coffee(const int money);
void add_10(int *money);
void add_20(int *money);
void add_50(int *money);
void add_100(int *money);
event_t check_amount(const int money);
event_t coin_insertion();
event_t Selection();

void WriteToFile();
void ReadFromFIle();


int Price = 125;
char drinkName[255];

//**************************************** main program

int main()
{
	event_handler(E_Start);

	return 0;
}

//**************************************** functions



state_t event_handler(event_t event) {
	static state_t state = S_Idle;
	static int money = 0;
	state_t next_state;

	while (1) {
		// *********** Source States/Events *************
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
			case E_Coffe:
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
				dispense_coffee(money);
				// Destination State
				next_state = S_Initialisation;
				break;
			}
			break;

		case S_Admin_Mode:
			system("@cls||clear");
			puts("Welcome to the admin mode");
			next_state = S_Wait_For_Admin_Selection;
			switch (event) {
			case E_Restock:
				Coffee_Stock = 10;
				Mokka_Stock = 10;
				Choco_Stock = 10;
				Dishwater_Stock = 10;
				WriteToFile();
				puts("Restocked!");
				break;
			case E_EmptyChange:
				Change_Stock = 0;
				WriteToFile();
				puts("Emptied change!");
				break;
			case E_ExitAdmin:
				system("@cls||clear");
				next_state = S_Initialisation;
				break;
			}
			break;
		}
		// *********** Destination States *************
		switch (next_state) {
		case S_Initialisation:
			// Moore Action
			initialize(&money);
			// Event Generation
			event = E_Continue;
			break;
		case S_Wait_For_Selection:
			event = Selection();
			// Event Generation/Preparation
			event = event;
			break;

		case S_Wait_For_Admin_Selection:
			event = AdminModeSelect();
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



void initialize(int *money) {
	*money = 0;
	ReadFromFIle();
}

void dispense_coffee(const int money) {
	printf("\n Enough Money!(%d) Thanks \n", money);
	printf("\n Your Change:%d", money - Price);
	printf("\n Take your %s!\n\n\n", drinkName);

	Change_Stock -= money - Price;

	if (!strcmp( drinkName, "Coffee")) {
		Coffee_Stock--;
	}
	else if (!strcmp(drinkName, "Mokka")) {
		Mokka_Stock--;
	}
	else if (!strcmp(drinkName, "Choco")) {
		Choco_Stock--;
	}
	else if (!strcmp(drinkName, "DishwasherWater")) {
		Dishwater_Stock--;
	}
	WriteToFile();
	
	printf("Press any button to continue");
	scanf("%c");
	system("@cls||clear");
}

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

event_t check_amount(const int money) {
	return (money < Price) ? E_Not_Enough_Money : E_Enough_Money;
}

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
				return E_Coffe;
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
		}

	}
}

event_t AdminModeSelect() {
	int sel;

	puts("\nSelect your option:");
	puts("1-- Refill all");
	puts("2-- Empty change");
	puts("3-- Exit");

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
		return E_ExitAdmin;
		break;
	}
}

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
