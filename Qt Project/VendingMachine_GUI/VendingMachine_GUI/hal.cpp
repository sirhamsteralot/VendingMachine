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

/*===================| Serialization |===================*/
void WriteToFile() {
    // INITIALIZE
    f = fopen("Stock.stock", "w+");
    fprintf(f, "%d\n%d\n%d\n%d\n%d\n%d", Coffee_Stock, Mokka_Stock, Choco_Stock, Dishwater_Stock, Change_Stock, current_Password);
    fclose(f);
}

void ReadFromFIle() {
    f = fopen("Stock.stock", "r");
    fscanf(f, "%d\n%d\n%d\n%d\n%d\n%d", &Coffee_Stock, &Mokka_Stock, &Choco_Stock, &Dishwater_Stock, &Change_Stock, &current_Password);
}

void Restock() {
    Coffee_Stock = 10;
    Mokka_Stock = 10;
    Choco_Stock = 10;
    Dishwater_Stock = 10;
    WriteToFile();
}
