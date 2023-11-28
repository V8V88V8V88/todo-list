#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITEMS 100
#define MAX_LENGTH 50

typedef struct {
    char item[MAX_LENGTH];
    char status[10];
} TodoItem;

TodoItem todoList[MAX_ITEMS];
int itemCount = 0;

void loadItems() {
    FILE *file = fopen("todo.txt", "r");
    if(file != NULL) {
        while(fgets(todoList[itemCount].item, MAX_LENGTH, file) != NULL) {
            todoList[itemCount].item[strcspn(todoList[itemCount].item, "\n")] = 0; // remove newline character
            fgets(todoList[itemCount].status, 10, file);
            todoList[itemCount].status[strcspn(todoList[itemCount].status, "\n")] = 0; // remove newline character
            itemCount++;
        }
        fclose(file);
    }
}

void saveItems() {
    FILE *file = fopen("todo.txt", "w");
    for(int i = 0; i < itemCount; i++) {
        fprintf(file, "%s\n%s\n", todoList[i].item, todoList[i].status);
    }
    fclose(file);
}

void addItem(char item[]) {
    strcpy(todoList[itemCount].item, item);
    strcpy(todoList[itemCount].status, "Not Done");
    itemCount++;
    saveItems();
}

void markItemDone(int itemNumber) {
    if(itemNumber > 0 && itemNumber <= itemCount) {
        strcpy(todoList[itemNumber-1].status, "Done");
        saveItems();
    } else {
        printf("Invalid item number.\n");
    }
}

void markItemUndone(int itemNumber) {
    if(itemNumber > 0 && itemNumber <= itemCount) {
        strcpy(todoList[itemNumber-1].status, "Not Done");
        saveItems();
    } else {
        printf("Invalid item number.\n");
    }
}

void deleteItem(int itemNumber) {
    if(itemNumber > 0 && itemNumber <= itemCount) {
        for(int i = itemNumber - 1; i < itemCount - 1; i++) {
            strcpy(todoList[i].item, todoList[i+1].item);
            strcpy(todoList[i].status, todoList[i+1].status);
        }
        itemCount--;
        saveItems();
    } else {
        printf("Invalid item number.\n");
    }
}

void displayItems() {
    printf("Todo List:\n");
    for(int i = 0; i < itemCount; i++) {
        if(strcmp(todoList[i].status, "Done") == 0) {
            printf("%d. \033[9m%s\033[0m\n", i+1, todoList[i].item);
        } else {
            printf("%d. %s\n", i+1, todoList[i].item);
        }
    }
}

int main(int argc, char *argv[]) {
    loadItems();

    if(argc < 2) {
        displayItems();
        return 0;
    }

    if(strcmp(argv[1], "add") == 0) {
        if(argc < 3) {
            printf("Please enter an item to add.\n");
            return 1;
        }
        for(int i = 2; i < argc; i++) {
            addItem(argv[i]);
        }
    } else if(strcmp(argv[1], "done") == 0) {
        if(argc < 3) {
            printf("Please enter the number of the item to mark as done.\n");
            return 1;
        }
        for(int i = 2; i < argc; i++) {
            int itemNumber = atoi(argv[i]);
            markItemDone(itemNumber);
        }
    } else if(strcmp(argv[1], "undone") == 0) {
        if(argc < 3) {
            printf("Please enter the number of the item to mark as undone.\n");
            return 1;
        }
        for(int i = 2; i < argc; i++) {
            int itemNumber = atoi(argv[i]);
            markItemUndone(itemNumber);
        }
    } else if(strcmp(argv[1], "delete") == 0) {
        if(argc < 3) {
            printf("Please enter the number of the item to delete.\n");
            return 1;
        }
        for(int i = 2; i < argc; i++) {
            int itemNumber = atoi(argv[i]);
            deleteItem(itemNumber);
        }
    } else if(strcmp(argv[1], "display") == 0) {
        displayItems();
    } else {
        printf("Invalid command.\n");
        return 1;
    }

    return 0;
}
