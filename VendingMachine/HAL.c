#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void dispense_coffee(const int money, const int Price, char *drinkName, int *Change_Stock, int *Coffee_Stock, int *Mokka_Stock, int* Choco_Stock, int *Dishwater_Stock) {
	printf("\n Enough Money!(%d) Thanks \n", money);
	printf("\n Your Change:%d", money - Price);
	printf("\n Take your %s!\n\n\n", drinkName);

	*Change_Stock -= money - Price;

	if (!strcmp(drinkName, "Coffee")) {
		*Coffee_Stock -= 1;
	}
	else if (!strcmp(drinkName, "Mokka")) {
		*Mokka_Stock -= 1;
	}
	else if (!strcmp(drinkName, "Choco")) {
		*Choco_Stock -= 1;
	}
	else if (!strcmp(drinkName, "DishwasherWater")) {
		*Dishwater_Stock -= 1;
	}

	printf("Press any button to continue");
	char t;
	scanf("%c", &t);
	system("@cls||clear");
}