#ifndef WFREST_JSON_H_
#define WFREST_JSON_H_

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include "json_parser.h"

namespace wfrest
{

class JsonValue;

class Json
{
public:
    using Object = std::map<std::string, Json>;
public: 
    // Constructors for the various types of JSON value.
    Json();
    Json(std::nullptr_t);
    Json(double value);
    Json(int value); 
    Json(bool value);
    Json(const std::string& str);  
    Json(const char* str);
    Json(const Object& obj);
    Json(JsonValue* val);
    ~Json();

    Json(Json&& other);
    Json& operator=(Json&& other);

    static Json parse(const std::string &str);
    static Json parse(const std::ifstream& stream);
    
    const std::string dump() const;
    const std::string dump(int spaces) const;

    int type() const;

    bool empty() const;
public:
    // object
    Json& operator[](const std::string& key);
    // todo : need meta programming to optimize
    Json& operator=(int val);
    Json& operator=(double val);
    void push_back(const std::string& key, int val);
    void push_back(const std::string& key, double val);

private:
    void to_object();
    
    friend inline std::ostream& operator << (std::ostream& os, const Json& json) { return (os << json.dump()); }

private:
    Object object_;
    std::string key_;
    Json* parent_ = nullptr;  // watcher
    JsonValue* val_ = nullptr;
    int depth_;
};

}  // namespace wfrest

#endif  // WFREST_JSON_H_
