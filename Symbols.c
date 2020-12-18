/*
    Задача:
        Определить какие символы встречаются в файле чаще всего, а какие реже всего. 
        Вывести на экран все найденные символы и частоту употребления.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 250                // Максимальный ASCII код

int main(void)
{
    FILE *input;
    char *fname = "text.txt";       // Название файла
    input = fopen(fname, "r"); 
    if (!input) {                   // Проверка на открытие
        puts("Error: file doesn't exist!"); 
        exit(1);
    }

    int symbols[MAX_SIZE] = {0};    // Массив с кол-ом символов
    int count = 0;                  // Кол-во всех символов
    char maxChar = 0;               // Символ с максимальным кодом по ASCII
    char c;                         // Символ для ввода
    while ((c = fgetc(input)) != EOF) {
        symbols[c]++;               // Считаем кол-во символов по его коду из ASCII 
        count++;                    // Считаем кол-во всех символов
        if (c > maxChar)
            maxChar = c;
    }
    fclose(input);

    int average = 0;                // Среднее
    int maxCount = 0, minCount = (symbols[0] > 0) ? symbols[0] : MAX_SIZE; // Максимальное и минимальное кол-ва. Минимальное должно быть больше 0, т.к. выбираем из считанных
    for (int i = 0; i < maxChar + 1; i++) { // maxChar + 1 - учитываем номер maxChar, иначе не дойдём до него
        if (symbols[i]) {                   // Т.к. мы гуляем по всем символам от 0 до maxChar включительно, то надо пропускать те символы, которых мы не встречали (их кол-во = 0)
            if (symbols[i] > maxCount)
                maxCount = symbols[i];
            else if (symbols[i] < minCount)
                minCount = symbols[i];

            average += symbols[i];
            if ((char)i == '\n')    // Избегаем перехода на новую строку, оформляем красивый вывод. Freq - частота встречаемости этого символа
                printf("symbol = '\\n', count = %d, freq = %f\n", symbols[i], (float)symbols[i] / (float)count);
            else
                printf("symbol = '%c', count = %d, freq = %f\n", i, symbols[i], (float)symbols[i] / (float)count);
        }
    }
    
    average /= (maxCount - minCount);   // Считаем среднее кол-во по "кастомной" формуле (так уж захотелось)
    printf("\nMost popular:\n");        // Список часто встречаемых символов
    for (int i = 0; i < maxChar + 1; i++) {
        if (symbols[i] >= average) {
            if ((char)i == '\n')
                printf("symbol = '\\n', count = %d\n", symbols[i]);
            else
                printf("symbol = '%c', count = %d\n", i, symbols[i]);
        }
    }

    printf("\nLess popular:\n");        // Список мало встречаемых символов
    for (int i = 0; i < maxChar + 1; i++) {
        if (symbols[i] < average && symbols[i] > 0) {
           if ((char)i == '\n')
                printf("symbol = '\\n', count = %d\n", symbols[i]);
            else
                printf("symbol = '%c', count = %d\n", i, symbols[i]);
        }
    }

    return 0;
}
