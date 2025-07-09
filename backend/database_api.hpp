#ifndef DATABASE_API_HPP
#define DATABASE_API_HPP

#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>

// Data structures for storing query results
typedef struct {
    int id;
    char user_id[51];
    char file_name[256];
    char file_type[51];
    int file_size;
    char upload_time[32];
    char file_path[501];
} FileRecord;

typedef struct {
    int status;         // 0 = success, -1 = error
    char message[256];  // error message if any
    int count;          // number of records
    FileRecord* files;  // pointer to array of file records
} QueryResult;

typedef struct {
    int status;         // 0 = success, -1 = error
    char message[256];  // error message if any
    int found;          // 1 = found, 0 = not found
    FileRecord file;    // single file record
} SingleFileResult;

typedef struct {
    int status;         // 0 = success, -1 = error
    char message[256];  // success or error message
    int affected_id;    // ID of affected record (inserted/updated/deleted)
} OperationResult;

// Database connection functions
int init_db();
void close_db();

// API interface functions that work with memory structures
int insert_file(const char* user_id, const char* file_name, const char* file_type, int file_size, const char* file_path, OperationResult* result);
int delete_file(const char* file_name, OperationResult* result);
int update_file(const char* file_name, const char* new_file_name, const char* new_file_type, OperationResult* result);
int query_all_files(QueryResult* result);
int query_files_by_user(const char* user_id, QueryResult* result);
int get_file_by_name(const char* file_name, SingleFileResult* result);

// Memory management functions for QueryResult
void free_query_result(QueryResult* result);

#endif // DATABASE_API_HPP
