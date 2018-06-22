#ifndef HAL_H
#define HAL_H

int Coffee_Stock;
int Mokka_Stock;
int Choco_Stock;
int Dishwater_Stock;
int Change_Stock;
int current_Password = 1234;

QString selectedDrink;

void ReadFromFIle() {
    FILE *f = fopen("Stock.stock", "r");

    if (f)
        fscanf(f, "%d\n%d\n%d\n%d\n%d\n%d", &Coffee_Stock, &Mokka_Stock, &Choco_Stock, &Dishwater_Stock, &Change_Stock, &current_Password);
}

void WriteToFile() {
    // INITIALIZE
    FILE *f = fopen("Stock.stock", "w+");
    fprintf(f, "%d\n%d\n%d\n%d\n%d\n%d", Coffee_Stock, Mokka_Stock, Choco_Stock, Dishwater_Stock, Change_Stock, current_Password);
    fclose(f);
}

void Restock() {
    Coffee_Stock = 10;
    Mokka_Stock = 10;
    Choco_Stock = 10;
    Dishwater_Stock = 10;
    WriteToFile();
}

void Log(QString data) {
    QString filename="log.txt";
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite| QIODevice::Append) )
    {
        QTextStream stream( &file );
        stream << endl << data;
    }
}

#endif // HAL_H
