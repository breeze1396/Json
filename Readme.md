合并入breUtils中

仅头文件

因测试过少暂不能进入生成阶段



---

​	轻量级 JSON 解析器的主要框架。

  ### 1. **`Value` 类** (`json_value.hpp`)

  这个类表示 JSON 数据的所有类型（包括对象、数组、字符串、数字、布尔值和 null）。我们将使用一个 `std::variant` 来存储这些类型。

  ```cpp
  #include <string>
  #include <vector>
  #include <unordered_map>
  #include <variant>
  #include <optional>
  
  enum class Type { Null, Bool, Int, Double, String, Array, Object };
  
  class Value {
  public:
      using Object = std::unordered_map<std::string, Value>;
      using Array = std::vector<Value>;
  
      Value(); // 默认构造
      Value(const Value& other); // 拷贝构造
      Value(Value&& other) noexcept; // 移动构造
      ~Value(); // 析构
      Value& operator=(const Value& other); // 拷贝赋值
      Value& operator=(Value&& other) noexcept; // 移动赋值
  
      Type type() const;
  
      void clear();
      void setNull();
      void setBool(bool b);
      void setInt(int i);
      void setDouble(double d);
      void setString(const std::string& s);
      void setArray();
      void setObject();
  
      bool asBool() const;
      int asInt() const;
      double asDouble() const;
      const std::string& asString() const;
      const Array& asArray() const;
      const Object& asObject() const;
  
      Value& operator[](size_t index); // 用于数组访问
      Value& operator[](const std::string& key); // 用于对象访问
  
  private:
      Type type_;
      std::variant<std::monostate, bool, int, double, std::string, Array, Object> value_;
  };
  ```

  #### 实现细节
  - `type_` 表示当前 `Value` 的类型。
  - `value_` 使用 `std::variant` 来存储不同的 JSON 数据类型。
  - 提供了访问方法（如 `asBool()`、`asInt()` 等）来获取不同类型的数据。

  ### 2. **`Parser` 类** (`json_parse.hpp`)

  这个类负责将 JSON 字符串解析为 `Value` 对象。我们使用递归下降解析器来处理 JSON 文法。

  ```cpp
  #include <string>
  #include <stdexcept>
  #include "json_value.hpp"
  
  class Parser {
  public:
      static bool parse(const std::string& str, Value& val);
  
  private:
      static size_t parseValue(const std::string& str, size_t pos, Value& val);
      static size_t parseObject(const std::string& str, size_t pos, Value& val);
      static size_t parseArray(const std::string& str, size_t pos, Value& val);
      static size_t parseString(const std::string& str, size_t pos, Value& val);
      static size_t parseNumber(const std::string& str, size_t pos, Value& val);
      static size_t parseBool(const std::string& str, size_t pos, Value& val);
      static size_t parseNull(const std::string& str, size_t pos, Value& val);
      
      static void skipWhitespace(const std::string& str, size_t& pos);
  };
  ```

  #### 实现细节
  - `parseValue` 方法递归解析 JSON 文本，并根据数据类型调用不同的解析函数。
  - `parseObject` 和 `parseArray` 解析对象和数组结构，分别填充到 `Value` 中。
  - `skipWhitespace` 方法跳过空白字符。

  ### 3. **`Generator` 类** (`json_generator.hpp`)

  这个类负责将 `Value` 对象转换为 JSON 字符串。

  ```cpp
  #include <string>
  #include "json_value.hpp"
  
  class Generator {
  public:
      static std::string generate(const Value& val);
  
  private:
      static void generateValue(const Value& val, std::string& output);
      static void generateObject(const Value::Object& obj, std::string& output);
      static void generateArray(const Value::Array& arr, std::string& output);
      static void generateString(const std::string& str, std::string& output);
      static void generateNumber(double num, std::string& output);
  };
  ```

  #### 实现细节
  - `generateValue` 递归地将 `Value` 转换为字符串。
  - `generateObject` 和 `generateArray` 方法分别处理对象和数组的序列化。
  - `generateString` 处理字符串的转义。

  ### 4. **`JsonParseException` 类** (`json_exception.hpp`)

  用于抛出解析错误的异常。

  ```cpp
  #include <exception>
  #include <string>
  
  class JsonParseException : public std::exception {
  public:
      explicit JsonParseException(const std::string& message) : message_(message) {}
  
      const char* what() const noexcept override {
          return message_.c_str();
      }
  
  private:
      std::string message_;
  };
  ```

  ### 5. **迭代器类** (`json_valueiterator.hpp`)

  迭代器类用于遍历数组和对象。

  ```cpp
  #include "json_value.hpp"
  
  template<typename ValueType>
  class Iterator {
  public:
      using iterator_category = std::forward_iterator_tag;
      using difference_type   = std::ptrdiff_t;
      using value_type        = ValueType;
      using pointer           = ValueType*;
      using reference         = ValueType&;
  
      Iterator(typename std::vector<Value>::iterator it) : it_(it) {}
  
      bool operator==(const Iterator& other) const { return it_ == other.it_; }
      bool operator!=(const Iterator& other) const { return !(*this == other); }
      ValueType& operator*() { return *it_; }
      Iterator& operator++() { ++it_; return *this; }
  
  private:
      typename std::vector<Value>::iterator it_;
  };
  ```

  ### 6. **工具函数** `json_tool.hpp`

  - 工具函数（例如判断字符是否是空白字符、转换等）可以放在 `json_tool.hpp` 中。#   J s o n 
 
 