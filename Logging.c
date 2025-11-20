#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "C-Unplugged.h"

void display_history()
{
    FILE *log_fp = fopen("log.txt", "a");
    fprintf(log_fp, "DISPLAY USER HISTORY\n");
    fclose(log_fp);
    char c = 0;
    FILE *fp = fopen("log.txt", "r");
    if (fp == NULL)
    {
        return;
    }
    printf("%s", WHITE);
    while (c != EOF)
    {
        printf("%c", c);
        c = fgetc(fp);
    }
    printf("\n");
    printf("%s", RESET);
    fclose(fp);
    home_menu();
}

void write_to_history(char *string_to_write)
{
    FILE *fp = fopen("log.txt", "a");
    if (fp == NULL)
    {
        printf("%sUNABLE TO OPEN LOG FILE TO UPDATE LOGS\n%s", RED, RESET);
        return;
    }
    fputs(string_to_write, fp);
    fclose(fp);
    return;
}