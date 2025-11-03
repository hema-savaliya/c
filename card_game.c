#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5

char stack[MAX];
int top = -1;

char queue[MAX];
int front = -1, rear = -1;

void push(char x) {
    if (top < MAX - 1)
        stack[++top] = x;
    else
        printf("Stack is full!\n");
}

char pop() {
    if (top >= 0)
        return stack[top--];
    else
        return '\0';
}

void enqueue(char x) {
    if (rear < MAX - 1) {
        if (front == -1)
            front = 0;
        queue[++rear] = x;
    } else
        printf("Queue is full!\n");
}

char dequeue() {
    if (front != -1 && front <= rear)
        return queue[front++];
    else
        return '\0';
}

int main() {
    char symbols[] = {'H', 'D', 'S', 'C'};
    int choice, i, match;
    char card, pattern;
    int wins = 0, losses = 0;

    srand(time(0));

    do {
        printf("\n====== SYMBOL MATCHING CARD GAME ======\n");
        printf("1. Load Random Deck\n");
        printf("2. Create Pattern\n");
        printf("3. Play Game\n");
        printf("4. Show Deck\n");
        printf("5. Show Pattern\n");
        printf("6. Shuffle Deck\n");
        printf("7. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                top = -1;
                for (i = 0; i < MAX; i++)
                    push(symbols[rand() % 4]);
                printf("Deck loaded with random cards!\n");
                break;

            case 2:
                front = -1;
                rear = -1;
                printf("Enter your pattern of %d symbols (H/D/S/C):\n", MAX);
                for (i = 0; i < MAX; i++) {
                    scanf(" %c", &pattern);
                    enqueue(pattern);
                }
                printf("Pattern created successfully!\n");
                break;

            case 3:
                if (top == -1) {
                    printf("Please load the deck first (option 1).\n");
                    break;
                }
                if (front == -1) {
                    printf("Please create the pattern first (option 2).\n");
                    break;
                }

                match = 0;
                printf("\nComparing cards with pattern...\n");
                for (i = 0; i < MAX; i++) {
                    // Use temporary variables to preserve deck & pattern
                    card = stack[i];
                    pattern = queue[i];
                    printf("Card: %c  |  Pattern: %c\n", card, pattern);
                    if (card == pattern)
                        match++;
                }

                printf("\nYou matched %d out of %d cards.\n", match, MAX);
                if (match == MAX) {
                    printf(" You Win!\n");
                    wins++;
                } else {
                    printf("Better luck next time!\n");
                    losses++;
                }
                printf("Scoreboard Wins: %d | Losses: %d\n", wins, losses);
                break;

            case 4:
                if (top == -1)
                    printf("Deck is empty! Load it first.\n");
                else {
                    printf("Current Deck (Top to Bottom): ");
                    for (i = top; i >= 0; i--)
                        printf("%c ", stack[i]);
                    printf("\n");
                }
                break;

            case 5:
                if (front == -1)
                    printf("Pattern not created yet!\n");
                else {
                    printf("Current Pattern: ");
                    for (i = front; i <= rear; i++)
                        printf("%c ", queue[i]);
                    printf("\n");
                }
                break;

            case 6:
                if (top == -1)
                    printf("Deck is empty! Load it first.\n");
                else {
                    for (i = 0; i < MAX; i++) {
                        int r = rand() % MAX;
                        char temp = stack[i];
                        stack[i] = stack[r];
                        stack[r] = temp;
                    }
                    printf("Deck shuffled successfully!\n");
                }
                break;

            case 7:
                printf("Exiting game. Thank you for playing!\n");
                break;

            default:
                printf("Invalid choice. Try again!\n");
        }
    } while (choice != 7);

    return 0;
}
