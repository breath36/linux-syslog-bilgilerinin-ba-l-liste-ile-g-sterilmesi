#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 1024

typedef struct LogNode {
    char log_payload[MAX_BUFFER];
    struct LogNode* next_node;
} LogNode;

LogNode* create_new_node(char* data) {
    LogNode* new_node = (LogNode*)malloc(sizeof(LogNode));
    if (new_node == NULL) {
        return NULL;
    }
    strncpy(new_node->log_payload, data, MAX_BUFFER);
    new_node->next_node = NULL;
    return new_node;
}

void append_log_entry(LogNode** head_ref, char* data) {
    LogNode* new_node = create_new_node(data);
    if (new_node == NULL) return;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    LogNode* last_node = *head_ref;
    while (last_node->next_node != NULL) {
        last_node = last_node->next_node;
    }
    last_node->next_node = new_node;
}

void display_all_logs(LogNode* node) {
    printf("\n--- Linux Syslog Verileri ---\n");
    while (node != NULL) {
        printf("%s", node->log_payload);
        node = node->next_node;
    }
}

void free_log_list(LogNode* head) {
    LogNode* current = head;
    while (current != NULL) {
        LogNode* next = current->next_node;
        free(current);
        current = next;
    }
}

int main() {
    FILE* syslog_file = fopen("/var/log/syslog", "r");
    if (syslog_file == NULL) {
        perror("Dosya okuma hatasi");
        return 1;
    }

    LogNode* log_list_head = NULL;
    char line_buffer[MAX_BUFFER];

    while (fgets(line_buffer, sizeof(line_buffer), syslog_file)) {
        append_log_entry(&log_list_head, line_buffer);
    }

    fclose(syslog_file);

    display_all_logs(log_list_head);
    free_log_list(log_list_head);

    return 0;
}
