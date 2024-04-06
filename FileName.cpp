#pragma warning(disable:4996)

#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define red  "\x1B[31m"
#define green  "\x1B[32m"
#define yellow  "\x1B[33m"
#define blue  "\x1B[34m"
#define magnata  "\x1B[35m"
#define cyan  "\x1B[36m"
#define white  "\x1B[37m"
int count = 0;
void show_zero_neibor(char** secret_arr, char** show_arr, int a, int b) {
    int i, j;
    if (a > 0 && b > 0 && a < 9 && b < 9) {
        if (show_arr[b][a] != '0') {
            show_arr[b][a] = '0';
            for (j = b - 1; j <= b + 1; j++) {
                for (i = a - 1; i <= a + 1; i++) {
                    if (a != i || j != b) {
                        //printf("i: %d   j: %d , sec : %c\n",i,j,secret_arr[j][i]);
                        if (secret_arr[j][i] == '0') {
                            show_zero_neibor(secret_arr, show_arr, i, j);
                        }
                        else if ((int)secret_arr[j][i] < 58 && (int)secret_arr[j][i]>48) {
                            show_arr[j][i] = secret_arr[j][i];
                        }

                    }
                }
            }
        }
    }
}
int get_user(char names[][20], char user[], char paswords[][20], int win_scores[], int lose_scores[]) {

    printf(" %s  Enter your name.%s   ", cyan, white);
    scanf("\n%s", user);
    printf("\n\n");
    //  make or use file for show info
    FILE* file;
    int i, k = 0;

    int flag = 0;

    file = fopen("C:\\Users\\asus\\Desktop\\c project\\scores.txt", "r+");

    while (fscanf(file, "%s %s %d %d", names[count], paswords[count], &win_scores[count], &lose_scores[count]) == 4) {
        count++;
    }

    fclose(file);

    for (i = 0; i < count; i++) {
        flag = 0;
        k = 0;
        while (names[i][k] != '\0') {
            if (names[i][k] == user[k] && user[k] != '\0')
                k++;
            else {
                flag = -1;
                break;
            }
        }
        if (user[k] == '\0' && flag == 0) {
            flag = 1;
            break;
        }
    }
    system("cls");
    if (flag == 1) {
        char pas[11];
        printf("\n\n%s  Hey %s.%s\n\n", magnata, names[i], white);
        for (k = 0; k < 3; k++) {
            if (k == 0)
                printf("  Enter your pasword:   ");
            else if (k == 1)
                printf("\n  %sWrong!!! Enter your pasword again%s:   ", red, white);
            else if (k == 2)
                printf("\n  %sWrong!!! Enter your pasword again (last time)%s:   ", red, white);
            scanf("\n%s", pas);

            if (strcmp(paswords[i], pas) == 0) {
                system("cls");
                return i + 1;
            }
            //kik if more than 3 wrong 
            else if (k == 2 && strcmp(paswords[i], pas) != 0)
                exit(-1);
            system("cls");
        }

    }
    else {
        char pas1[11], pas2[11];

        while (user[k] != NULL) {
            names[count][k] = user[k];
            k++;
        }
        win_scores[count] = 0, lose_scores[count] = 0;
        printf("\n\n  %sWellcom %s.%s\n", magnata, user, white);
        while (1) {
            printf("  Make your pasword (max char:10) :   ");
            scanf("\n%s", pas1);
            printf("\n  Enter your password one more time :   ");
            scanf("\n%s", pas2);
            if (strcmp(pas1, pas2) == 0) {
                k = 0;
                while (pas1[k] != NULL) {
                    paswords[count][k] = pas1[k];
                    k++;
                }
                break;
            }
            else
                printf("\n No math first and secound! Try again");
            system("cls");
        }
        count++;
        return count;
    }
}
char menu() {
    char menuchose;
    char menu[4][30] = { {"1- make or change name" },{"2- play!"},{"3- show profile"},{"4- Save and exit"} };

    printf("\n\t %s *** %sMenu%s ***\n\n", white, red, white);
    printf("   %s%s\n", blue, menu[0]);
    printf("   %s%s\n", yellow, menu[1]);
    printf("   %s%s\n", green, menu[2]);
    printf("   %s%s\n", magnata, menu[3]);

    printf("\n\t%swhich one you whant?\t", white);

    scanf("\n%c", &menuchose);

    system("cls");

    return menuchose;

}
char play(int person, int win_scores[], int lose_scores[]) {

    int i = 1, j = 0, row = 0, bomb_number = 0, n = 0, flag = 1, a = 0, b = 0, lose = 0, win = 0, counter = 0;
    char e_or_m[1], bomb = (char)11, game_flag = (char)6, l_or_r;
    printf("\tchose dificulty easy(e) or medium(m)    ");
    while (i) {//make sure dont enter wrong

        scanf("\n%c", e_or_m);
        if (e_or_m[0] == 'e') {
            row = 10;
            bomb_number = 10;
            break;
        }

        else if (e_or_m[0] == 'm') {
            row = 18;
            bomb_number = 40;
            break;
        }
        else {
            printf("\n\t%sIt was wrong input! Try again.%s\n", red, white);
        }
    }

    int flag_limit = bomb_number;

    //making secret array
    char** secret_arr = (char**)malloc(((row + 20) * 2) * sizeof(char*));
    for (i = 0; i < row + 20; i++)
        secret_arr[i] = (char*)malloc(((row + 20) * 2) * sizeof(char));
    for (i = 1; i < row + 5; i++)
        for (j = 1; j < row + 5; j++)
            secret_arr[i][j] = '0';

    //making col limit
    int col_limit[17] = { 0 };


    srand(time(0));

    for (int i = 0; i < bomb_number; i++) {
        do {
            a = (rand() % (row - 2)) + 1;
            b = (rand() % (row - 2)) + 1;
        } while (secret_arr[a][b] == bomb || col_limit[a] >= 3);

        secret_arr[a][b] = bomb;
        col_limit[a]++;
    }
    int i1, j1, bomb_counter = 0;
    for (i = 1; i < row - 1; i++) {
        for (j = 1; j < row - 1; j++) {
            bomb_counter = 0;
            if (secret_arr[i][j] == bomb)
                continue;

            for (i1 = i - 1; i1 <= i + 1; i1++) {
                for (j1 = j - 1; j1 <= j + 1; j1++) {
                    if (secret_arr[i1][j1] == bomb)
                        bomb_counter++;
                }
            }

            secret_arr[i][j] = (char)(bomb_counter + 48);
        }
    }


    //making show_arr
    char** show_arr = (char**)malloc(((row + 10) * 2) * sizeof(char));
    for (i = 0; i < row - 1; i++) {
        show_arr[i] = (char*)malloc(((row + 10) * 2) * sizeof(int));
        for (j = 0; j < row + 5; j++)
            show_arr[i][j] = ' ';
    }


    char E = 'a';
    char input[10];
    while (E != 'E') {

        if (lose == 1) {
            lose_scores[person]++;
            printf("\n\n %s You lose the game. The complete table is:\n", white);

            printf("\n\t  ");
            for (n = 1; n < row - 1; n++)
                printf("%s  %d ", magnata, n);
            printf("\n\t  ");
            for (n = 1; n < row - 1; n++)
                if (n < 10)
                    printf(" %s---", white);
                else
                    printf(" %s----", white);
            printf("\n");
            for (i = 1; i < row - 1; i++) {
                for (j = 0; j < row - 1; j++) {
                    if (j == 0) {
                        if (i < 10)
                            printf("\t%s%d %s|", magnata, i, white);
                        else
                            printf("       %s%d %s|", magnata, i, white);
                        continue;
                    }
                    else if (j < 10) {
                        if (secret_arr[i][j] == bomb)
                            printf(" %s%c %s|", red, secret_arr[i][j], white);
                        else if (secret_arr[i][j] == '0')
                            printf(" %s%c %s|", white, secret_arr[i][j], white);
                        else if (secret_arr[i][j] == '1')
                            printf(" %s%c %s|", yellow, secret_arr[i][j], white);
                        else if (secret_arr[i][j] == '2')
                            printf(" %s%c %s|", cyan, secret_arr[i][j], white);
                        else if (secret_arr[i][j] == '3')
                            printf(" %s%c %s|", blue, secret_arr[i][j], white);
                        else
                            printf(" %s%c %s|", white, secret_arr[i][j], white);
                    }
                    else {
                        if (secret_arr[i][j] == bomb)
                            printf(" %s%c %s |", red, secret_arr[i][j], white);
                        else if (secret_arr[i][j] == '0')
                            printf(" %s%c %s |", white, secret_arr[i][j], white);
                        else if (secret_arr[i][j] == '1')
                            printf(" %s%c %s |", yellow, secret_arr[i][j], white);
                        else if (secret_arr[i][j] == '2')
                            printf(" %s%c %s |", cyan, secret_arr[i][j], white);
                        else if (secret_arr[i][j] == '3')
                            printf(" %s%c %s |", blue, secret_arr[i][j], white);
                        else
                            printf(" %s%c %s |", white, secret_arr[i][j], white);
                    }

                }

                printf("\n\t  ");
                for (n = 1; n < row - 1; n++)
                    if (n < 10)
                        printf(" ---");
                    else
                        printf(" ----");
                printf("\n");
            }
            printf("\n");

            return 'l';
        }

        if (win == 1) {
            win_scores[person]++;
            system("cls");
            printf("\n   %s********* %scongratulations! You win. %s**********\n\n", white, green, white);
            return'w';
        }
        //else:
        system("cls");
        printf("  %s Game table is :\n\n", white);
        printf("\t  ");
        for (n = 1; n < row - 1; n++)
            printf(" %s %d ", magnata, n);
        printf("\n\t  ");
        for (n = 1; n < row - 1; n++)
            if (n < 10)
                printf(" %s---", white);
            else
                printf(" %s----", white);
        printf("\n");
        for (i = 1; i < row - 1; i++) {
            for (j = 0; j < row - 1; j++) {

                if (j == 0) {
                    if (i < 10) {
                        printf("\t%s%d ", magnata, i);
                        printf("%s|", white);
                    }
                    else
                        printf("      %s %d %s|", magnata, i, white);
                    continue;
                }
                else
                    if (j < 10) {
                        if (show_arr[i][j] == game_flag)
                            printf(" %s%c ", green, show_arr[i][j]);
                        else if (show_arr[i][j] == '0')
                            printf(" %s%c ", white, show_arr[i][j]);
                        else if (show_arr[i][j] == '1')
                            printf(" %s%c ", yellow, show_arr[i][j]);
                        else if (show_arr[i][j] == '2')
                            printf(" %s%c ", cyan, show_arr[i][j]);
                        else if (show_arr[i][j] == '3')
                            printf(" %s%c ", blue, show_arr[i][j]);
                        else
                            printf(" %s%c ", white, show_arr[i][j]);
                        printf("%s|", white);
                    }
                    else
                    {
                        if (show_arr[i][j] == game_flag)
                            printf(" %s%c  ", green, show_arr[i][j]);
                        else if (show_arr[i][j] == '0')
                            printf(" %s%c  ", white, show_arr[i][j]);
                        else if (show_arr[i][j] == '1')
                            printf(" %s%c  ", yellow, show_arr[i][j]);
                        else if (show_arr[i][j] == '2')
                            printf(" %s%c  ", cyan, show_arr[i][j]);
                        else if (show_arr[i][j] == '3')
                            printf(" %s%c  ", blue, show_arr[i][j]);
                        else
                            printf(" %s%c  ", white, show_arr[i][j]);
                        printf("%s|", white);
                    }
            }
            printf("\n\t  ");
            for (n = 1; n < row - 1; n++)
                if (n < 10)
                    printf(" ---");
                else
                    printf(" ----");
            printf("\n");
        }


        printf("%s\n\t\tYour flag(s) are %d.\n\n", cyan, flag_limit);
        printf("  %sIf you want go out of this game enter E.\n", white);
        printf("\n  Other wise give me left(l) or right(r) click and location you want. \n  Simple: r i j\n  ");


        while (1) {
            scanf("\n%c", &l_or_r);

            if (l_or_r == 'E') {
                E = 'E';
                system("cls");
                return 'e';
            }
            scanf("%d%d", &a, &b);

            if (bomb_number == 10 && a < 9 && a>0 && b < 9 && b>0 && (l_or_r == 'r' || l_or_r == 'l'))
                break;

            else if (bomb_number == 40 && a < 17 && a>0 && b < 17 && b>0 && (l_or_r == 'r' || l_or_r == 'l'))
                break;
            else
                printf("\tIt was wrong input! Try again.\n   ", red);
        }
        if (l_or_r == 'r') {
            if (show_arr[b][a] == ' ') {
                if (flag_limit > 0) {
                    show_arr[b][a] = game_flag;
                    flag_limit--;
                }
                else {
                    system("cls");
                    printf("\n\n  %s *****    %sYou dont have any more flag! First unflag one!    %s*****\n", white, red, white);
                    _sleep(2000);
                    continue;
                }
            }
            else if (show_arr[b][a] == game_flag) {
                show_arr[b][a] = ' ';
                flag_limit++;
            }
        }
        else if (l_or_r == 'l') {
            if (secret_arr[b][a] == bomb) {
                system("cls");
                lose = 1;
                printf("\a\a\a\a\a ");
                printf("\n   %sBooooooom!!! You chose bomb.\n", red);
                continue;
            }
            //show neibor
            else if (secret_arr[b][a] == '0')
                show_zero_neibor(secret_arr, show_arr, a, b);
            else
                show_arr[b][a] = secret_arr[b][a];
        }

        if (flag_limit == 0) {
            counter = 0;
            for (i = 1; i < row - 1; i++) {
                for (j = 1; j < row - 1; j++) {
                    if (show_arr[j][i] == game_flag && secret_arr[j][i] == bomb)
                        counter++;
                }
            }
            if (counter == bomb_number) {
                win = 1;
                continue;
            }
        }
    }

}
int main()
{
    FILE* file;
    char E = 'A';
    int i = 0, k = 150;
    char menuchose;
    //listes use for persons 
    char user[20];
    char names[100][20] = { NULL };
    char paswords[100][20] = { NULL };
    int win_scores[100] = { 0 };
    int lose_scores[100] = { 0 };
    char rez;
    printf("\033[40m");  // Set font size to 5
    //wellcoming
    for (i = 1050; i > 0; i -= 100) {
        printf("\n\n\t\a %sWellcom", red);
        _sleep(10);
        system("cls");
        printf("\n\n\t\t    %sto", yellow);
        _sleep(10);
        system("cls");
        printf("\n\n\t\t\t  %sMineSweeper", green);
        _sleep(k);
        k -= 9;
        system("cls");
        _sleep(i);
    }

    printf("\n\n\t %sWellcom    %sto    %sMineSweeper\n\n", red, blue, green);
    while (E != 'E') {
        //getting a name
        int person = get_user(names, user, paswords, win_scores, lose_scores);

        while (1) {
            menuchose = menu();
            if (menuchose == 50) {
                rez = play(person - 1, win_scores, lose_scores);
                if (rez == 'w')
                    win_scores[person]++;
                else if (rez == 'l')
                    lose_scores[person]++;
            }
            else if (menuchose == 51) {
                printf("     %s\n\t***%sProfile%s***\n\n", red, white, red);
                printf("   %sname :%s%s\t\t%swin matches : %s%d\t\t%sloses matches : %s%d   \n\n\n", white, blue, names[person - 1], white, green, win_scores[person - 1], white, red, lose_scores[person - 1]);
            }
            else if (menuchose == 52)
            {
                E = 'E';

                file = fopen("C:\\Users\\asus\\Desktop\\c project\\scores.txt", "w");
                for (int i = 0; i < count; i++) {
                    fprintf(file, "%s %s %d %d\n", names[i], paswords[i], win_scores[i], lose_scores[i]);

                }

                fclose(file);
                break;
            }
            else if (menuchose == 49)
                break;

            else
                printf("\t\tIt was wrong input! Try again.\n", red);
        }


    }
    return 0;
}
