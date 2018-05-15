#ifndef HAL_H
#define HAL_H

void dispense_coffee(const int money, const int Price, char *drinkName, int *Change_Stock, int *Coffee_Stock, int *Mokka_Stock, int* Choco_Stock, int *Dishwater_Stock);
void WriteToFile();
void ReadFromFIle();

void Restock();

#endif // HAL_H
