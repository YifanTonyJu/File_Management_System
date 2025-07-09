#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "third_library/oatpp/src/oatpp/web/server/api/ApiController.hpp"
#include "third_library/oatpp/src/oatpp/macro/codegen.hpp"
#include "third_library/oatpp/src/oatpp/json/ObjectMapper.hpp"
#include "database_api.hpp"
#include "third_library/json/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

#include OATPP_CODEGEN_BEGIN(ApiController)

class Controller : public oatpp::web::server::api::ApiController {
public:
    Controller(const std::shared_ptr<ObjectMapper>& object_mapper) : oatpp::web::server::api::ApiController(object_mapper) {
        init_db();
    }

    ~Controller() {
        close_db();
    }
public:
    ENDPOINT("POST", "/api/files", insertFile, BODY_STRING(String, body)) {
        // use the nlohmann::json library to parse the JSON body
        OperationResult result;
        std::string bodyStr = body->c_str();
        
        try {
            // read the JSON body into a nlohmann::json object
            json j = json::parse(bodyStr);
            
            // read values from the JSON object
            std::string user_id = j.value("user_id", "");
            std::string file_name = j.value("file_name", "");
            std::string file_type = j.value("file_type", "");
            std::string file_path = j.value("file_path", "");
            int file_size = j.value("file_size", 0);
            
            // check if required fields are present
            if (user_id.empty() || file_name.empty() || file_type.empty() || file_path.empty()) {
                json error_response = {
                    {"status", -1},
                    {"message", "Missing required fields: user_id, file_name, file_type, and file_path are required"},
                    {"affected_id", 0}
                };
                return ResponseFactory::createResponse(Status::CODE_400, error_response.dump().c_str());
            }
            
            // use the database API to insert the file
            int status = insert_file(user_id.c_str(), file_name.c_str(), file_type.c_str(),
                                    file_size, file_path.c_str(), &result);
            
            // use the result to create a JSON response
            json response = {
                {"status", result.status},
                {"message", std::string(result.message)},
                {"affected_id", result.affected_id}
            };
            
            // return the response with appropriate status code
            if (result.status == 0) {
                return ResponseFactory::createResponse(Status::CODE_201, response.dump().c_str());
            }
            else {
                return ResponseFactory::createResponse(Status::CODE_409, response.dump().c_str());
            }
            
        }
        catch (const json::parse_error& e) {
            // fail to parse JSON, return an error response
            json error_response = {
                {"status", -1},
                {"message", "Invalid JSON format: " + std::string(e.what())},
                {"affected_id", -1}
            };
            return ResponseFactory::createResponse(Status::CODE_400, error_response.dump().c_str());
        }
        catch (const std::exception& e) {
            // other exceptions, return an error response
            json error_response = {
                {"status", -1},
                {"message", "Error: " + std::string(e.what())},
                {"affected_id", -1}
            };
            return ResponseFactory::createResponse(Status::CODE_500, error_response.dump().c_str());
        }
    }

    ENDPOINT("DELETE", "/api/files/{fileName}", deleteFile, PATH(String, fileName)) {
        OperationResult result;
        try {
            int status = delete_file(fileName->c_str(), &result);
            
            int deleted_count = 0;
            if (result.status == 0) {
                deleted_count = 1;
            }
            
            json response = {
                {"status", result.status},
                {"message", std::string(result.message)},
                {"affected_id", result.affected_id},
                {"deleted_count", deleted_count}
            };
            
            if (result.status == 0) {
                return ResponseFactory::createResponse(Status::CODE_200, response.dump().c_str());
            }
            else {
                return ResponseFactory::createResponse(Status::CODE_404, response.dump().c_str());
            }
            
        }
        catch (const std::exception& e) {
            json error_response = {
                {"status", -1},
                {"message", "Error deleting file: " + std::string(e.what())},
                {"affected_id", 0},
                {"deleted_count", 0}
            };
            return ResponseFactory::createResponse(Status::CODE_500, error_response.dump().c_str());
        }
    }
    
    // Update file endpoint
    ENDPOINT("PUT", "/api/files/{fileName}", updateFile, PATH(String, fileName), BODY_STRING(String, body)) {
        OperationResult result;
        std::string bodyStr = body->c_str();
        
        try {
            // check if fileName is provided in the URL path
            if (!fileName || fileName->empty()) {
                json error_response = {
                    {"status", -1},
                    {"message", "File name is required in URL path"},
                    {"affected_id", 0},
                    {"updated_count", 0}
                };
                return ResponseFactory::createResponse(Status::CODE_400, error_response.dump().c_str());
            }
            
            json j = json::parse(bodyStr);
            
            std::string new_file_name = j.value("new_file_name", "");
            std::string new_file_type = j.value("new_file_type", "");
            
            if (new_file_name.empty() && new_file_type.empty()) {
                json error_response = {
                    {"status", -1},
                    {"message", "At least one field (new_file_name or new_file_type) is required for update"},
                    {"affected_id", 0},
                    {"updated_count", 0}
                };
                return ResponseFactory::createResponse(Status::CODE_400, error_response.dump().c_str());
            }
            
            if (new_file_name.empty()) {
                new_file_name = fileName->c_str(); // no change to file name
            }
            
            int status = update_file(fileName->c_str(), new_file_name.c_str(), new_file_type.c_str(), &result);
            
            int updated_count = 0;
            if (result.status == 0) {
                updated_count = 1;
            }
            
            json response = {
                {"status", result.status},
                {"message", std::string(result.message)},
                {"affected_id", result.affected_id},
                {"updated_count", updated_count},
                {"original_file_name", fileName->c_str()},
                {"new_file_name", new_file_name},
                {"new_file_type", new_file_type}
            };
            
            if (result.status == 0) {
                return ResponseFactory::createResponse(Status::CODE_200, response.dump().c_str());
            }
            else {
                return ResponseFactory::createResponse(Status::CODE_404, response.dump().c_str());
            }
            
        }
        catch (const json::parse_error& e) {
            json error_response = {
                {"status", -1},
                {"message", "Invalid JSON format: " + std::string(e.what())},
                {"affected_id", 0},
                {"updated_count", 0}
            };
            return ResponseFactory::createResponse(Status::CODE_400, error_response.dump().c_str());
        }
        catch (const std::exception& e) {
            json error_response = {
                {"status", -1},
                {"message", "Error updating file: " + std::string(e.what())},
                {"affected_id", 0},
                {"updated_count", 0}
            };
            return ResponseFactory::createResponse(Status::CODE_500, error_response.dump().c_str());
        }
    }
    
    // Query all files endpoint
    ENDPOINT("GET", "/api/files", queryAllFiles) {
        QueryResult result;
        try {
            int status = query_all_files(&result);
            
            if (status == 0 && result.status == 0) {
                json files_array = json::array();
                
                for (int i = 0; i < result.count; i++) {
                    json file_obj = {
                        {"id", result.files[i].id},
                        {"user_id", std::string(result.files[i].user_id)},
                        {"file_name", std::string(result.files[i].file_name)},
                        {"file_type", std::string(result.files[i].file_type)},
                        {"file_size", result.files[i].file_size},
                        {"upload_time", std::string(result.files[i].upload_time)},
                        {"file_path", std::string(result.files[i].file_path)}
                    };
                    files_array.push_back(file_obj);
                }
                
                json response = {
                    {"status", 0},
                    {"message", "Files retrieved successfully"},
                    {"count", result.count},
                    {"files", files_array}
                };
                
                free_query_result(&result);
                
                return ResponseFactory::createResponse(Status::CODE_200, response.dump().c_str());
                
            }
            else {
                json error_response = {
                    {"status", -1},
                    {"message", std::string(result.message)},
                    {"count", 0},
                    {"files", json::array()}
                };
                free_query_result(&result);
                
                return ResponseFactory::createResponse(Status::CODE_500, error_response.dump().c_str());
            }
            
        }
        catch (const std::exception& e) {
            json error_response = {
                {"status", -1},
                {"message", "Error querying files: " + std::string(e.what())},
                {"count", 0},
                {"files", json::array()}
            };
            
            free_query_result(&result);
            
            return ResponseFactory::createResponse(Status::CODE_500, error_response.dump().c_str());
        }
    }
    
    // Query files by user ID endpoint
    ENDPOINT("GET", "/api/files/user/{userId}", queryFilesByUser, PATH(String, userId)) {
        QueryResult result;
        try {
            int status = query_files_by_user(userId->c_str(), &result);
            
            if (status == 0 && result.status == 0) {
                json files_array = json::array();
                
                for (int i = 0; i < result.count; i++) {
                    json file_obj = {
                        {"id", result.files[i].id},
                        {"user_id", std::string(result.files[i].user_id)},
                        {"file_name", std::string(result.files[i].file_name)},
                        {"file_type", std::string(result.files[i].file_type)},
                        {"file_size", result.files[i].file_size},
                        {"upload_time", std::string(result.files[i].upload_time)},
                        {"file_path", std::string(result.files[i].file_path)}
                    };
                    files_array.push_back(file_obj);
                }
                
                json response = {
                    {"status", 0},
                    {"message", "Files retrieved successfully for user: " + std::string(userId->c_str())},
                    {"user_id", userId->c_str()},
                    {"count", result.count},
                    {"files", files_array}
                };
                
                free_query_result(&result);
                
                return ResponseFactory::createResponse(Status::CODE_200, response.dump().c_str());
                
            }
            else {
                json error_response = {
                    {"status", -1},
                    {"message", std::string(result.message)},
                    {"user_id", userId->c_str()},
                    {"count", 0},
                    {"files", json::array()}
                };
                free_query_result(&result);
                
                return ResponseFactory::createResponse(Status::CODE_500, error_response.dump().c_str());
            }
            
        }
        catch (const std::exception& e) {
            json error_response = {
                {"status", -1},
                {"message", "Error querying files by user: " + std::string(e.what())},
                {"user_id", userId->c_str()},
                {"count", 0},
                {"files", json::array()}
            };
            
            free_query_result(&result);
            
            return ResponseFactory::createResponse(Status::CODE_500, error_response.dump().c_str());
        }
    }
    
    // Get file by name endpoint
    ENDPOINT("GET", "/api/files/name/{fileName}", getFileByName, PATH(String, fileName)) {
        SingleFileResult result;
        try {
            int status = get_file_by_name(fileName->c_str(), &result);
            
            if (status == 0 && result.status == 0 && result.found == 1) {
                json file_obj = {
                    {"id", result.file.id},
                    {"user_id", std::string(result.file.user_id)},
                    {"file_name", std::string(result.file.file_name)},
                    {"file_type", std::string(result.file.file_type)},
                    {"file_size", result.file.file_size},
                    {"upload_time", std::string(result.file.upload_time)},
                    {"file_path", std::string(result.file.file_path)}
                };
                
                json response = {
                    {"status", 0},
                    {"message", "File retrieved successfully"},
                    {"found", true},
                    {"file", file_obj}
                };
                
                return ResponseFactory::createResponse(Status::CODE_200, response.dump().c_str());
                
            }
            else if (status == 0 && result.status == 0 && result.found == 0) {
                // File not found
                json response = {
                    {"status", 0},
                    {"message", "File not found"},
                    {"found", false},
                    {"file", nullptr}
                };
                
                return ResponseFactory::createResponse(Status::CODE_404, response.dump().c_str());
                
            }
            else {
                json error_response = {
                    {"status", -1},
                    {"message", std::string(result.message)},
                    {"found", false},
                    {"file", nullptr}
                };
                
                return ResponseFactory::createResponse(Status::CODE_500, error_response.dump().c_str());
            }
            
        }
        catch (const std::exception& e) {
            json error_response = {
                {"status", -1},
                {"message", "Error retrieving file: " + std::string(e.what())},
                {"found", false},
                {"file", nullptr}
            };
            
            return ResponseFactory::createResponse(Status::CODE_500, error_response.dump().c_str());
        }
    }
};

#include OATPP_CODEGEN_END(ApiController)

#endif
