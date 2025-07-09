#include "database_api.hpp"

// MySQL connection object
MYSQL mysql;

// Connect to the database
// Returns 0 on success, -1 on failure
int init_db() {
    mysql_init(&mysql);
    mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "utf8mb4");
    
    if (mysql_real_connect(&mysql, "127.0.0.1", "root", "TONY33550336tony", "testdb", 3306, NULL, 0) == NULL) {
        fprintf(stderr, "Fail to connect testdb database: %s\n", mysql_error(&mysql));
        return -1;
    }
    printf("Connect testdb database successfully!\n");
    return 0;
}

// Close the database connection
void close_db() {
    mysql_close(&mysql);
}

// Memory management functions for QueryResult
void free_query_result(QueryResult* result) {
    if (result && result->files) {
        free(result->files);
        result->files = NULL;
        result->count = 0;
    }
}

int query_all_files(QueryResult* result) {
    MYSQL_RES* res;
    MYSQL_ROW row;
    
    // Initialize result
    result->status = 0;
    result->count = 0;
    result->files = NULL;
    strcpy(result->message, "");
    
    if (mysql_query(&mysql, "SELECT id, user_id, file_name, file_type, file_size, upload_time, file_path FROM uploaded_files")) {
        result->status = -1;
        snprintf(result->message, sizeof(result->message), "Failed to query data: %s", mysql_error(&mysql));
        return -1;
    }
    
    res = mysql_store_result(&mysql);
    if (res == NULL) {
        result->status = -1;
        snprintf(result->message, sizeof(result->message), "Failed to get result: %s", mysql_error(&mysql));
        return -1;
    }
    
    // Get number of rows to allocate memory
    int num_rows = (int)mysql_num_rows(res);
    if (num_rows > 0) {
        result->files = (FileRecord*)malloc(sizeof(FileRecord) * num_rows);
        if (result->files == NULL) {
            result->status = -1;
            strcpy(result->message, "Failed to allocate memory for results");
            mysql_free_result(res);
            return -1;
        }
    }
    
    int index = 0;
    while ((row = mysql_fetch_row(res))) {
        result->files[index].id = atoi(row[0]);
        strcpy(result->files[index].user_id, row[1]);
        strcpy(result->files[index].file_name, row[2]);
        strcpy(result->files[index].file_type, row[3]);
        result->files[index].file_size = atoi(row[4]);
        strcpy(result->files[index].upload_time, row[5]);
        strcpy(result->files[index].file_path, row[6]);
        index++;
    }
    
    result->count = index;
    mysql_free_result(res);
    return 0;
}

// Query - Query file records by user ID and store in result structure
int query_files_by_user(const char* user_id, QueryResult* result) {
    MYSQL_RES* res;
    MYSQL_ROW row;
    char query[512]; // query string buffer
    
    // Initialize result
    result->status = 0;
    result->count = 0;
    result->files = NULL;
    strcpy(result->message, "");
    
    snprintf(query, sizeof(query),
        "SELECT id, user_id, file_name, file_type, file_size, upload_time, file_path FROM uploaded_files WHERE user_id = '%s'",
        user_id);
    
    if (mysql_query(&mysql, query)) {
        result->status = -1;
        snprintf(result->message, sizeof(result->message), "Failed to query data: %s", mysql_error(&mysql));
        return -1;
    }
    
    res = mysql_store_result(&mysql);
    if (res == NULL) {
        result->status = -1;
        snprintf(result->message, sizeof(result->message), "Failed to get result: %s", mysql_error(&mysql));
        return -1;
    }
    
    // Get number of rows to allocate memory
    int num_rows = (int)mysql_num_rows(res);
    if (num_rows > 0) {
        result->files = (FileRecord*)malloc(sizeof(FileRecord) * num_rows);
        if (result->files == NULL) {
            result->status = -1;
            strcpy(result->message, "Failed to allocate memory for results");
            mysql_free_result(res);
            return -1;
        }
    }
    
    int index = 0;
    while ((row = mysql_fetch_row(res))) {
        result->files[index].id = atoi(row[0]);
        strcpy(result->files[index].user_id, row[1]);
        strcpy(result->files[index].file_name, row[2]);
        strcpy(result->files[index].file_type, row[3]);
        result->files[index].file_size = atoi(row[4]);
        strcpy(result->files[index].upload_time, row[5]);
        strcpy(result->files[index].file_path, row[6]);
        index++;
    }
    
    result->count = index;
    mysql_free_result(res);
    return 0;
}

// Query - Get file record by file name and store in single file result structure
int get_file_by_name(const char* file_name, SingleFileResult* result) {
    MYSQL_RES* res;
    MYSQL_ROW row;
    char query[512];
    
    // Initialize result
    result->status = 0;
    result->found = 0;
    strcpy(result->message, "");
    
    snprintf(query, sizeof(query),
        "SELECT id, user_id, file_name, file_type, file_size, upload_time, file_path FROM uploaded_files WHERE file_name = '%s'",
        file_name);
    
    if (mysql_query(&mysql, query)) {
        result->status = -1;
        snprintf(result->message, sizeof(result->message), "Failed to query data: %s", mysql_error(&mysql));
        return -1;
    }
    
    res = mysql_store_result(&mysql);
    if (res == NULL) {
        result->status = -1;
        snprintf(result->message, sizeof(result->message), "Failed to get result: %s", mysql_error(&mysql));
        return -1;
    }
    
    row = mysql_fetch_row(res);
    if (row) {
        result->found = 1;
        result->file.id = atoi(row[0]);
        strcpy(result->file.user_id, row[1]);
        strcpy(result->file.file_name, row[2]);
        strcpy(result->file.file_type, row[3]);
        result->file.file_size = atoi(row[4]);
        strcpy(result->file.upload_time, row[5]);
        strcpy(result->file.file_path, row[6]);
    }
    
    mysql_free_result(res);
    return 0;
}

// Insert - Insert a new file record and store result in operation result structure
int insert_file(const char* user_id, const char* file_name, const char* file_type, int file_size, const char* file_path, OperationResult* result) {
    char query[1024];
    
    // Initialize result
    result->status = 0;
    result->affected_id = 0;
    strcpy(result->message, "");
    
    snprintf(query, sizeof(query),
        "INSERT INTO uploaded_files (user_id, file_name, file_type, file_size, file_path) VALUES ('%s', '%s', '%s', %d, '%s')",
        user_id, file_name, file_type, file_size, file_path);
    
    if (mysql_query(&mysql, query)) {
        result->status = -1;
        snprintf(result->message, sizeof(result->message), "Failed to insert file record: %s", mysql_error(&mysql));
        return -1;
    }
    
    result->affected_id = (int)mysql_insert_id(&mysql);
    strcpy(result->message, "File record inserted successfully");
    return 0;
}

// Delete - Delete a file record by file name and store result in operation result structure
int delete_file(const char* file_name, OperationResult* result) {
    char query[512];
    int file_id = 0;
    
    // Initialize result
    result->status = 0;
    result->affected_id = 0;  // Will store the ID of deleted record if found
    strcpy(result->message, "");
    
    // First, get the ID of the file that will be deleted
    snprintf(query, sizeof(query), "SELECT id FROM uploaded_files WHERE file_name = '%s'", file_name);
    
    if (mysql_query(&mysql, query)) {
        result->status = -1;
        snprintf(result->message, sizeof(result->message), "Failed to query file ID: %s", mysql_error(&mysql));
        return -1;
    }
    
    MYSQL_RES* res = mysql_store_result(&mysql);
    if (res == NULL) {
        result->status = -1;
        snprintf(result->message, sizeof(result->message), "Failed to get query result: %s", mysql_error(&mysql));
        return -1;
    }
    
    MYSQL_ROW row = mysql_fetch_row(res);
    if (row) {
        file_id = atoi(row[0]);
    }
    mysql_free_result(res);
    
    if (file_id == 0) {
        result->status = -1;
        strcpy(result->message, "File not found");
        return -1;
    }
    
    // Now delete the file
    snprintf(query, sizeof(query), "DELETE FROM uploaded_files WHERE file_name = '%s'", file_name);
    
    if (mysql_query(&mysql, query)) {
        result->status = -1;
        snprintf(result->message, sizeof(result->message), "Failed to delete file record: %s", mysql_error(&mysql));
        return -1;
    }
    
    int affected_rows = (int)mysql_affected_rows(&mysql);
    if (affected_rows > 0) {
        result->affected_id = file_id;  // Store the ID of the deleted record
        snprintf(result->message, sizeof(result->message), "File record deleted successfully, affected rows: %d", affected_rows);
    }
    else {
        result->status = -1;
        strcpy(result->message, "File not found or already deleted");
        return -1;
    }
    
    return 0;
}

// Update - Update file information by file name and store result in operation result structure
int update_file(const char* file_name, const char* new_file_name, const char* new_file_type, OperationResult* result) {
    char query[512];
    int file_id = 0;
    
    // Initialize result
    result->status = 0;
    result->affected_id = 0;  // Will store the ID of updated record if found
    strcpy(result->message, "");
    
    // First, get the ID of the file that will be updated
    snprintf(query, sizeof(query), "SELECT id FROM uploaded_files WHERE file_name = '%s'", file_name);
    
    if (mysql_query(&mysql, query)) {
        result->status = -1;
        snprintf(result->message, sizeof(result->message), "Failed to query file ID: %s", mysql_error(&mysql));
        return -1;
    }
    
    MYSQL_RES* res = mysql_store_result(&mysql);
    if (res == NULL) {
        result->status = -1;
        snprintf(result->message, sizeof(result->message), "Failed to get query result: %s", mysql_error(&mysql));
        return -1;
    }
    
    MYSQL_ROW row = mysql_fetch_row(res);
    if (row) {
        file_id = atoi(row[0]);
    }
    mysql_free_result(res);
    
    if (file_id == 0) {
        result->status = -1;
        strcpy(result->message, "File not found");
        return -1;
    }
    
    // Now update the file
    snprintf(query, sizeof(query),
        "UPDATE uploaded_files SET file_name = '%s', file_type = '%s' WHERE file_name = '%s'",
        new_file_name, new_file_type, file_name);
    
    if (mysql_query(&mysql, query)) {
        result->status = -1;
        snprintf(result->message, sizeof(result->message), "Failed to update file record: %s", mysql_error(&mysql));
        return -1;
    }
    
    int affected_rows = (int)mysql_affected_rows(&mysql);
    if (affected_rows > 0) {
        result->affected_id = file_id;  // Store the ID of the updated record
        snprintf(result->message, sizeof(result->message), "File record updated successfully, affected rows: %d", affected_rows);
    }
    else {
        result->status = -1;
        strcpy(result->message, "File not found or no changes made");
        return -1;
    }
    
    return 0;
}

