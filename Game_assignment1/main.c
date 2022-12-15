#include <stdio.h>
#include <string.h>
// the consts for teams array
#define MAX_LINE 1000
#define MAX_LEN 1000
// function to find MUX
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
// string size
#define ml 1000

// function, which exam string to errors
int chacchac(char str[]) {
    // If first letter is not capital ar 2 > length or length > 20 , then we have the error
    if (str[0] < 'A' || str[0] > 'Z' || strlen(str) < 2 || strlen(str) > 20) return 0;
    // if others letters not in (a, z) or in (A, Z), we have the error
    for (int i = 1; i < strlen(str); i++) {
        if (str[i] < 'A' || str[i] > 'Z')
            if (str[i] < 'a' || str[i] > 'z')
                return 0;
    }
    // else string is good
    return 1;
}

/* our structure, where been players and their characteristics
 * (name, team, power, visibility and frozen)
 */
struct person {

    char name[ml];
    int team;
    int power;
    int visibility;
    int frozen;

};

int main() {
    // array, where been names of teams
    char array[MAX_LINE][MAX_LEN];
    // N - number of teams; M - counts of players;
    int N;
    int M;
    int k = 0;
    // name_attack - is the name of action
    char name_attack[ml];
    // indexes in struct arrays
    int number_1_player, number_2_player;
    // players in actions
    char _1_player[ml], _2_player[ml];

    // Step 1 - open our input and output files
    FILE *f = fopen("input.txt", "r");
    FILE *o = fopen("output.txt", "w");

    // Error 1 - if number of teams < 1 or > 10 or fscanf did not get any
    if (fscanf(f, "%d\n", &N) != 1 || N < 1 || N > 10) {
        fputs("Invalid inputs\n", o);
        fclose(f);
        fclose(o);
        return 0;
    }

    //Step 2 - we put our teams to array
    int line = 0;
    for (line; line < N; line++) {
        fscanf(f, "%s\n", array[line]);
        //Error 2 - if the string is not suitable for our parameters we put error to output file
        if (chacchac(array[line]) == 0) {
            fputs("Invalid inputs\n", o);
            fclose(f);
            fclose(o);
            return 0;
        }
    }
    // Step 3, Error 3 - We take M - number of players and exam to Invalid input
    if (fscanf(f, "%d\n", &M) != 1 || M < N || M > 100) {
        fputs("Invalid inputs\n", o);
        fclose(f);
        fclose(o);
        return 0;
    }

    // array of structures
    struct person num[M];
    // temp - is variable to work with players visibility
    char temp[ml];
    // Step 4 - we start to put all Information of player, where i - is index of player
    for (int i = 0; i < M; i++) {
        // Step 4.1 - We get mame of player and check it by using the function "chacchac"
        fscanf(f, "%s\n", num[i].name);
        if (chacchac(num[i].name) == 0) {
            fputs("Invalid inputs\n", o);
            fclose(f);
            fclose(o);
            return 0;
        }
        // Step 4.2 - We get team number of player and check it by using the function "chacchac"
        if (fscanf(f, "%d\n", &num[i].team) != 1 || num[i].team<0 ||
                                                                num[i].team>(N - 1)) {
            fputs("Invalid inputs\n", o);
            fclose(f);
            fclose(o);
            return 0;
        }

        // Step 4.3 - We get number of power and check it by using the function "chacchac"
        if (fscanf(f, "%d\n", &num[i].power) != 1 || num[i].power < 0 ||
            num[i].power > 1000) {
            fputs("Invalid inputs\n", o);
            fclose(f);
            fclose(o);
            return 0;
        }
        // Step 4.4 - We check, that if our power == 0, hence player is frozen
        if (num[i].power == 0) {
            num[i].frozen = 1;
        } else {
            num[i].frozen = 0;
        }
        // Step 4.5 - We get visibility(True = 1; False = 0) and check it by using the function "chacchac"
        // If we did not read
        if (fscanf(f, "%s\n", temp) != 1) {
            fputs("Invalid inputs\n", o);
            fclose(f);
            fclose(o);
            return 0;
        }
            // True = 1
        else if (strcmp(temp, "True") == 0) {
            num[i].visibility = 1;
        }
            // False = 0
        else if (strcmp(temp, "False") == 0) {
            num[i].visibility = 0;
        }
            // If we get other --> error
        else {
            fputs("Invalid inputs\n", o);
            fclose(f);
            fclose(o);
            return 0;
        }


    }
    // act - is count of actions
    int act = 0;
    // Step 5 - The main cycle; While not end of file and no errors;
    while (!feof(f) && !ferror(f)) {
        //Step 5.1 - Error - if count of actions > 1000
        if (++act > 1000) {
            fclose(o);
            o = fopen("output.txt", "w");
            fputs("Invalid inputs\n", o);
            fclose(f);
            fclose(o);
            return 0;
        }
        // To understand, that players in action be in our structure
        number_1_player = -3;
        number_2_player = -3;
        // Step 5.2 - we get name of action, and check, that we get some sing
        if (fscanf(f, "%s", name_attack) != 1) {
            fclose(o);
            o = fopen("output.txt", "w");
            fputs("Invalid inputs\n", o);
            fclose(f);
            fclose(o);
            return 0;
        }

            // Step 5.3 - If name action == attack
        else if (strcmp(name_attack, "attack") == 0) {
            // Step 5.4 - We get names of players, which take part in actions, and we didn't get any sing --> error
            if (fscanf(f, "%s %s\n", _1_player, _2_player) != 2) {
                fclose(o);
                o = fopen("output.txt", "w");
                fputs("Invalid inputs\n", o);
                fclose(f);
                fclose(o);
                return 0;
            }
                // If we get some sing, then continue
            else {
                // Step 5.5 - We find names of players in struct
                for (int i = 0; i < M; i++) {
                    if (strcmp(_1_player, num[i].name) == 0) {
                        // number in struct of 1st player
                        number_1_player = i;
                    }
                    if (strcmp(_2_player, num[i].name) == 0) {
                        // number in struct of 2st player
                        number_2_player = i;
                    }
                }
                // Step 5.6 - If our number hasn't changed --> error
                if (number_1_player == -3 || number_2_player == -3) {
                    fclose(o);
                    o = fopen("output.txt", "w");
                    fputs("Invalid inputs\n", o);
                    fclose(f);
                    fclose(o);
                    return 0;
                }
                // Step 5.7 - If visibility first player == 0, we put this
                if (num[number_1_player].visibility == 0) {
                    fputs("This player can't play\n", o);
                    // Step 5.8 - If player 1 is frozen --> we put this
                } else if (num[number_1_player].frozen == 1) {
                    fputs("This player is frozen\n", o);
                    // Step 5.9 - The main process
                } else {
                    // if power 1st doesn't see 2st player
                    if (num[number_2_player].visibility == 0) {
                        num[number_1_player].power = 0;
                        num[number_1_player].frozen = 1;
                        // if power 1st > 2d
                    } else if (num[number_1_player].power > num[number_2_player].power) {
                        // player's power doesn't > 1000
                        num[number_1_player].power = MIN(
                                num[number_1_player].power + num[number_1_player].power - num[number_2_player].power,
                                1000);
                        // if player 1st win in attack, 2d player be frozen and his power = 0
                        num[number_2_player].power = 0;
                        num[number_2_player].frozen = 1;
                        // if power 1st < 2d
                    } else if (num[number_1_player].power < num[number_2_player].power) {
                        // player's power doesn't > 1000
                        num[number_2_player].power = MIN(
                                num[number_2_player].power + num[number_2_player].power - num[number_1_player].power,
                                1000);
                        // if player 2d win in attack, 1st player be frozen and his power = 0
                        num[number_1_player].power = 0;
                        num[number_1_player].frozen = 1;
                        // if power 1st == 2d their powers = 0 and frozen = 1
                    } else if (num[number_1_player].power == num[number_2_player].power) {
                        num[number_2_player].power = 0;
                        num[number_2_player].frozen = 1;
                        num[number_1_player].power = 0;
                        num[number_1_player].frozen = 1;
                    }
                }
            }
        }
            // Step 6  - If name action  == flip_visibility
        else if (strcmp(name_attack, "flip_visibility") == 0) {
            // if we didn't get any sing --> error
            if (fscanf(f, "%s\n", _1_player) != 1) {
                fclose(o);
                o = fopen("output.txt", "w");
                fputs("Invalid inputs\n", o);
                fclose(f);
                fclose(o);
                return 0;
            }
                // Find the player in struct
            else {
                for (int i = 0; i < M; i++) {
                    if (strcmp(_1_player, num[i].name) == 0) {
                        // number in struct
                        number_1_player = i;
                    }
                }
                // if we didn't find this name --> error
                if (number_1_player == -3) {
                    fclose(o);
                    o = fopen("output.txt", "w");
                    fputs("Invalid inputs\n", o);
                    fclose(f);
                    fclose(o);
                    return 0;
                }
                // if 1st frozen --> "This player is frozen\n"
                if (num[number_1_player].frozen == 1) {
                    fputs("This player is frozen\n", o);
                    // The main operation - swap visibility
                } else if (num[number_1_player].visibility == 0) {
                    num[number_1_player].visibility = 1;
                } else {
                    num[number_1_player].visibility = 0;
                }
            }
        }
            // Step 7.  - If name action  == heal
        else if (strcmp(name_attack, "heal") == 0) {
            // If we didn't get 2 strings --> error
            if (fscanf(f, "%s %s\n", _1_player, _2_player) != 2) {
                fclose(o);
                o = fopen("output.txt", "w");
                fputs("Invalid inputs\n", o);
                fclose(f);
                fclose(o);
                return 0;
            } else {
                // find names of players in struct
                for (int i = 0; i < M; i++) {
                    if (strcmp(_1_player, num[i].name) == 0) {
                        // number ib struct
                        number_1_player = i;
                    }
                    if (strcmp(_2_player, num[i].name) == 0) {
                        // number in struct
                        number_2_player = i;
                    }
                }
                // if we didn't find names in structure --> error
                if (number_1_player == -3 || number_2_player == -3) {
                    fclose(o);
                    o = fopen("output.txt", "w");
                    fputs("Invalid inputs\n", o);
                    fclose(f);
                    fclose(o);
                    return 0;
                }
                // visibility error
                if (num[number_1_player].visibility == 0) {
                    fputs("This player can't play\n", o);
                    continue;
                }
                //frozen  error
                if (num[number_1_player].frozen == 1) {
                    fputs("This player is frozen\n", o);
                    continue;
                }
                // If players not from the same teams --> "Both players should be from the same team\n"
                if (num[number_1_player].team != num[number_2_player].team) {
                    fputs("Both players should be from the same team\n", o);
                    continue;
                }
                // if player heal himself --> "The player cannot heal itself\n"
                if (strcmp(num[number_1_player].name, num[number_2_player].name) == 0) {
                    fputs("The player cannot heal itself\n", o);
                    continue;
                }

                //The main operation -  Give power from first to second player
                num[number_2_player].power = MIN((num[number_2_player].power + (num[number_1_player].power + 1) / 2),
                                                 1000);
                num[number_1_player].power = (num[number_1_player].power + 1) / 2;


                // frozen
                if (num[number_2_player].frozen == 1) {
                    num[number_2_player].frozen = 0;
                }
                // if power 1st player = 0, then he is frozen
                if (num[number_1_player].power == 0) {
                    num[number_1_player].frozen = 0;
                }

            }
        }
            // Step 8  - If name action  == super
        else if (strcmp(name_attack, "super") == 0) {
            // if we didn't get any sing --> error
            if (fscanf(f, "%s %s\n", _1_player, _2_player) != 2) {
                fclose(o);
                o = fopen("output.txt", "w");
                fputs("Invalid inputs\n", o);
                fclose(f);
                fclose(o);
                return 0;
            } else {
                // find our players in structures
                for (int i = 0; i < M; i++) {
                    if (strcmp(_1_player, num[i].name) == 0) {
                        // number struct
                        number_1_player = i;
                    }
                    if (strcmp(_2_player, num[i].name) == 0) {
                        // number struct
                        number_2_player = i;
                    }
                }
                // if we didn't find names in struct --> error
                if (number_1_player == -3 || number_2_player == -3) {
                    fclose(o);
                    o = fopen("output.txt", "w");
                    fputs("Invalid inputs\n", o);
                    fclose(f);
                    fclose(o);
                    return 0;
                }
                // visibility error
                if (num[number_1_player].visibility == 0) {
                    fputs("This player can't play\n", o);
                    continue;
                }
                //frozen  error
                if (num[number_1_player].frozen == 1) {
                    fputs("This player is frozen\n", o);
                    continue;
                }
                // if players not from the same team --> error
                if (num[number_1_player].team != num[number_2_player].team) {
                    fputs("Both players should be from the same team\n", o);
                    continue;
                }
                // player 1 == player 2 --> error
                if (strcmp(num[number_1_player].name, num[number_2_player].name) == 0) {
                    fputs("The player cannot do super action with itself\n", o);
                    continue;
                }
                // we do the super player in struct, where was 1st player
                sprintf(num[number_1_player].name, "%s%d", "S_", k);
                num[number_1_player].power += num[number_2_player].power;
                k++;
                // power <= 1000
                if (num[number_1_player].power > 1000) {
                    num[number_1_player].power = 1000;
                }
                // 2d players name == NULL, because he doesn't play anymore
                strcpy(num[number_2_player].name, "NULL");
                num[number_2_player].power = 0;
                num[number_2_player].frozen = 1;
            }
        }
            // If no actions, that we know --> error
        else {
            fclose(o);
            o = fopen("output.txt", "w");
            fputs("Invalid inputs\n", o);
            fclose(f);
            fclose(o);
            return 0;
        }
    }
    // filling the array with zeros
    int sum[N];
    for (int i = 0; i < N; i++) {
        sum[i] = 0;
    }
    // we count power to every team, put in array, which index == number of team
    for (int i = 0; i < M; i++) {
        sum[num[i].team] += num[i].power;
    }
    // max - maximum of power; nimer - number of team;
    int max = 0, nomer;
    // identify the biggest power
    for (int i = 0; i < N; i++) {
        if (sum[i] >= max) {
            max = sum[i];
            nomer = i;
        }
    }
    // identify count of teams with max power
    int wincount = 0;
    for (int i = 0; i < N; i++) {
        if (sum[i] == max) wincount++;
    }
    // if winner teams more than 1 --> tie
    if (wincount > 1) { fputs("It's a tie\n", o); }
        // if no tie --> put name of winner team
    else {
        fprintf(o, "The chosen wizard is %s\n", array[nomer]);
    }
    // close input and output files
    fclose(f);
    fclose(o);
    return 0;
}