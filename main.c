#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char title[100];
    char *body;
    char department[50];
    int semester;
    char poster[50];
    char date[11];
} Notice;

typedef struct {
    char studentId[30];
    char department[50];
} Subscription;

Notice *notices = NULL;
Subscription subscriptions[100];
int noticeCount = 0, subscriptionCount = 0;
int nextId = 1;

void postNotice() {
    notices = realloc(notices, (noticeCount + 1) * sizeof(Notice));
    if (notices == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    Notice *n = &notices[noticeCount];

    n->id = nextId++;

    printf("Enter title: ");
    scanf(" %99[^\n]", n->title);

    char temp[2000];
    printf("Enter body: ");
    scanf(" %1999[^\n]", temp);

    n->body = malloc(strlen(temp) + 1);
    if (n->body == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strcpy(n->body, temp);

    printf("Enter department: ");
    scanf(" %49[^\n]", n->department);

    printf("Enter semester: ");
    scanf("%d", &n->semester);

    printf("Enter poster name: ");
    scanf(" %49[^\n]", n->poster);

    printf("Enter date (YYYY-MM-DD): ");
    scanf("%10s", n->date);

    noticeCount++;
    printf("Notice posted successfully. ID: %d\n", n->id);
}

void displayNotice(Notice n) {
    printf("\nID: %d\nTitle: %s\nBody: %s\nDepartment: %s\n",
           n.id, n.title, n.body, n.department);
    printf("Semester: %d\nPoster: %s\nDate: %s\n",
           n.semester, n.poster, n.date);
}

void listNotices() {
    if (noticeCount == 0) {
        printf("No notices available.\n");
        return;
    }

    for (int i = 0; i < noticeCount; i++)
        displayNotice(notices[i]);
}

void editNotice() {
    int id, found = 0;
    printf("Enter notice ID to edit: ");
    scanf("%d", &id);

    for (int i = 0; i < noticeCount; i++) {
        if (notices[i].id == id) {
            char temp[2000];

            printf("Enter new title: ");
            scanf(" %99[^\n]", notices[i].title);

            printf("Enter new body: ");
            scanf(" %1999[^\n]", temp);

            char *newBody = malloc(strlen(temp) + 1);
            if (newBody == NULL) {
                printf("Memory allocation failed.\n");
                return;
            }

            strcpy(newBody, temp);
            free(notices[i].body);
            notices[i].body = newBody;

            printf("Enter new department: ");
            scanf(" %49[^\n]", notices[i].department);

            printf("Enter new semester: ");
            scanf("%d", &notices[i].semester);

            printf("Enter new poster: ");
            scanf(" %49[^\n]", notices[i].poster);

            printf("Enter new date (YYYY-MM-DD): ");
            scanf("%10s", notices[i].date);

            printf("Notice updated successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Notice not found.\n");
}

void deleteNotice() {
    int id, found = 0;
    printf("Enter notice ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < noticeCount; i++) {
        if (notices[i].id == id) {
            free(notices[i].body);

            for (int j = i; j < noticeCount - 1; j++)
                notices[j] = notices[j + 1];

            noticeCount--;
            found = 1;

            if (noticeCount == 0) {
                free(notices);
                notices = NULL;
            } else {
                Notice *temp = realloc(
                    notices, noticeCount * sizeof(Notice));
                if (temp != NULL)
                    notices = temp;
            }

            printf("Notice deleted successfully.\n");
            break;
        }
    }

    if (!found)
        printf("Notice not found.\n");
}

void searchNotice() {
    char keyword[100];
    int found = 0;

    printf("Enter title keyword: ");
    scanf(" %99[^\n]", keyword);

    for (int i = 0; i < noticeCount; i++) {
        if (strstr(notices[i].title, keyword) != NULL) {
            displayNotice(notices[i]);
            found = 1;
        }
    }

    if (!found)
        printf("No matching notices found.\n");
}

void filterDepartment() {
    char department[50];
    int found = 0;

    printf("Enter department: ");
    scanf(" %49[^\n]", department);

    for (int i = 0; i < noticeCount; i++) {
        if (strcmp(notices[i].department, department) == 0) {
            displayNotice(notices[i]);
            found = 1;
        }
    }

    if (!found)
        printf("No notices found for this department.\n");
}

void filterSemester() {
    int semester, found = 0;

    printf("Enter semester: ");
    scanf("%d", &semester);

    for (int i = 0; i < noticeCount; i++) {
        if (notices[i].semester == semester) {
            displayNotice(notices[i]);
            found = 1;
        }
    }

    if (!found)
        printf("No notices found for this semester.\n");
}

void filterDateRange() {
    char start[11], end[11];
    int found = 0;

    printf("Enter start date (YYYY-MM-DD): ");
    scanf("%10s", start);

    printf("Enter end date (YYYY-MM-DD): ");
    scanf("%10s", end);

    for (int i = 0; i < noticeCount; i++) {
        if (strcmp(notices[i].date, start) >= 0 &&
            strcmp(notices[i].date, end) <= 0) {
            displayNotice(notices[i]);
            found = 1;
        }
    }

    if (!found)
        printf("No notices found in this date range.\n");
}

void subscribeDepartment() {
    if (subscriptionCount >= 100) {
        printf("Subscription limit reached.\n");
        return;
    }

    printf("Enter student ID: ");
    scanf(" %29s", subscriptions[subscriptionCount].studentId);

    printf("Enter department to subscribe to: ");
    scanf(" %49[^\n]",
          subscriptions[subscriptionCount].department);

    subscriptionCount++;
    printf("Subscription successful.\n");
}

void showNotifications() {
    char studentId[30];
    int found = 0;

    printf("Enter student ID: ");
    scanf(" %29s", studentId);

    for (int i = 0; i < subscriptionCount; i++) {
        if (strcmp(subscriptions[i].studentId, studentId) == 0) {
            for (int j = 0; j < noticeCount; j++) {
                if (strcmp(notices[j].department,
                           subscriptions[i].department) == 0) {
                    printf("\nNotification for %s:\n", studentId);
                    displayNotice(notices[j]);
                    found = 1;
                }
            }
        }
    }

    if (!found)
        printf("No relevant notifications found.\n");
}

int main() {
    int choice;

    do {
        printf("\n===== CAMPUS NOTICEBOARD =====\n");
        printf("1. Post Notice\n");
        printf("2. View All Notices\n");
        printf("3. Edit Notice\n");
        printf("4. Delete Notice\n");
        printf("5. Search Notice\n");
        printf("6. Filter by Department\n");
        printf("7. Filter by Semester\n");
        printf("8. Filter by Date Range\n");
        printf("9. Subscribe to Department\n");
        printf("10. View Notifications\n");
        printf("0. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
            break;

        switch (choice) {
            case 1: postNotice(); break;
            case 2: listNotices(); break;
            case 3: editNotice(); break;
            case 4: deleteNotice(); break;
            case 5: searchNotice(); break;
            case 6: filterDepartment(); break;
            case 7: filterSemester(); break;
            case 8: filterDateRange(); break;
            case 9: subscribeDepartment(); break;
            case 10: showNotifications(); break;
            case 0: printf("Exiting system.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);

    for (int i = 0; i < noticeCount; i++)
        free(notices[i].body);

    free(notices);

    return 0;
}