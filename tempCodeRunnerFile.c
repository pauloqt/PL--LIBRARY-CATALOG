#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

void pull_down_menu() {
    int selected = 0;
    const int num_options = 2;
    char* options[] = {"Option 1", "Option 2"};

    while (1) {
        // Clear screen
        system("cls");

        // Display options
        for (int i = 0; i < num_options; i++) {
            if (i == selected) {
                printf("-> %s\n", options[i]);
            } else {
                printf("   %s\n", options[i]);
            }
        }

        // Get user input
        int key = getch();
        if (key == 224) {
            key = getch();
            switch (key) {
                case 72: // Up arrow
                    selected = (selected - 1 + num_options) % num_options;
                    break;
                case 80: // Down arrow
                    selected = (selected + 1) % num_options;
                    break;
            }
        } else if (key == 13) { // Enter key
            printf("\nYou selected: %s\n", options[selected]);
            break;
        }
    }
}

int main() {
    pull_down_menu();
    return 0;
}




