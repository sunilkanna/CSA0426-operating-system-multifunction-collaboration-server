#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_SUBDIRS 10
#define MAX_FILENAME_LENGTH 100
#define MAX_SUBDIR_NAME_LENGTH 50

typedef struct {
    char name[MAX_FILENAME_LENGTH];
} File;

typedef struct {
    char name[MAX_SUBDIR_NAME_LENGTH];
    File files[MAX_FILES];
    int file_count;
} SubDirectory;

typedef struct {
    SubDirectory subdirs[MAX_SUBDIRS];
    int subdir_count;
} Directory;

// Function to initialize the directory
void init_directory(Directory *dir) {
    dir->subdir_count = 0;
}

// Function to add a subdirectory to the root directory
void add_subdirectory(Directory *dir, const char *subdir_name) {
    if (dir->subdir_count < MAX_SUBDIRS) {
        strncpy(dir->subdirs[dir->subdir_count].name, subdir_name, MAX_SUBDIR_NAME_LENGTH);
        dir->subdirs[dir->subdir_count].file_count = 0;
        dir->subdir_count++;
        printf("Subdirectory '%s' added.\n", subdir_name);
    } else {
        printf("Root directory is full. Cannot add subdirectory '%s'.\n", subdir_name);
    }
}

// Function to add a file to a subdirectory
void add_file_to_subdir(Directory *dir, const char *subdir_name, const char *filename) {
    for (int i = 0; i < dir->subdir_count; i++) {
        if (strcmp(dir->subdirs[i].name, subdir_name) == 0) {
            if (dir->subdirs[i].file_count < MAX_FILES) {
                strncpy(dir->subdirs[i].files[dir->subdirs[i].file_count].name, filename, MAX_FILENAME_LENGTH);
                dir->subdirs[i].file_count++;
                printf("File '%s' added to subdirectory '%s'.\n", filename, subdir_name);
                return;
            } else {
                printf("Subdirectory '%s' is full. Cannot add file '%s'.\n", subdir_name, filename);
                return;
            }
        }
    }
    printf("Subdirectory '%s' not found.\n", subdir_name);
}

// Function to list all subdirectories
void list_subdirectories(const Directory *dir) {
    if (dir->subdir_count == 0) {
        printf("No subdirectories in the root directory.\n");
    } else {
        printf("Subdirectories in the root directory:\n");
        for (int i = 0; i < dir->subdir_count; i++) {
            printf("%s\n", dir->subdirs[i].name);
        }
    }
}

// Function to list all files in a specific subdirectory
void list_files_in_subdir(const Directory *dir, const char *subdir_name) {
    for (int i = 0; i < dir->subdir_count; i++) {
        if (strcmp(dir->subdirs[i].name, subdir_name) == 0) {
            if (dir->subdirs[i].file_count == 0) {
                printf("No files in subdirectory '%s'.\n", subdir_name);
            } else {
                printf("Files in subdirectory '%s':\n", subdir_name);
                for (int j = 0; j < dir->subdirs[i].file_count; j++) {
                    printf("%s\n", dir->subdirs[i].files[j].name);
                }
            }
            return;
        }
    }
    printf("Subdirectory '%s' not found.\n", subdir_name);
}

// Function to delete a file from a subdirectory
void delete_file_from_subdir(Directory *dir, const char *subdir_name, const char *filename) {
    for (int i = 0; i < dir->subdir_count; i++) {
        if (strcmp(dir->subdirs[i].name, subdir_name) == 0) {
            for (int j = 0; j < dir->subdirs[i].file_count; j++) {
                if (strcmp(dir->subdirs[i].files[j].name, filename) == 0) {
                    // Shift files to remove the deleted file
                    for (int k = j; k < dir->subdirs[i].file_count - 1; k++) {
                        dir->subdirs[i].files[k] = dir->subdirs[i].files[k + 1];
                    }
                    dir->subdirs[i].file_count--;
                    printf("File '%s' deleted from subdirectory '%s'.\n", filename, subdir_name);
                    return;
                }
            }
            printf("File '%s' not found in subdirectory '%s'.\n", filename, subdir_name);
            return;
        }
    }
    printf("Subdirectory '%s' not found.\n", subdir_name);
}

int main() {
    Directory dir;
    char name[MAX_FILENAME_LENGTH];
    int choice;
    char subdir_name[MAX_SUBDIR_NAME_LENGTH];

    init_directory(&dir);

    while (1) {
        printf("\nDirectory Management Menu:\n");
        printf("1. Add Subdirectory\n");
        printf("2. Add File to Subdirectory\n");
        printf("3. List Subdirectories\n");
        printf("4. List Files in Subdirectory\n");
        printf("5. Delete File from Subdirectory\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character left by scanf

        switch (choice) {
            case 1:
                printf("Enter subdirectory name to add: ");
                fgets(subdir_name, MAX_SUBDIR_NAME_LENGTH, stdin);
                subdir_name[strcspn(subdir_name, "\n")] = '\0'; // Remove newline character
                add_subdirectory(&dir, subdir_name);
                break;
            case 2:
                printf("Enter subdirectory name: ");
                fgets(subdir_name, MAX_SUBDIR_NAME_LENGTH, stdin);
                subdir_name[strcspn(subdir_name, "\n")] = '\0'; // Remove newline character
                printf("Enter filename to add: ");
                fgets(name, MAX_FILENAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove newline character
                add_file_to_subdir(&dir, subdir_name, name);
                break;
            case 3:
                list_subdirectories(&dir);
                break;
            case 4:
                printf("Enter subdirectory name: ");
                fgets(subdir_name, MAX_SUBDIR_NAME_LENGTH, stdin);
                subdir_name[strcspn(subdir_name, "\n")] = '\0'; // Remove newline character
                list_files_in_subdir(&dir, subdir_name);
                break;
            case 5:
                printf("Enter subdirectory name: ");
                fgets(subdir_name, MAX_SUBDIR_NAME_LENGTH, stdin);
                subdir_name[strcspn(subdir_name, "\n")] = '\0'; // Remove newline character
                printf("Enter filename to delete: ");
                fgets(name, MAX_FILENAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove newline character
                delete_file_from_subdir(&dir, subdir_name, name);
                break;
            case 6:
                printf("Exiting.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}


