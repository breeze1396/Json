#ifndef JSON_EXCEPTION_HPP
#define JSON_EXCEPTION_HPP

// JsonParseException �࣬����JSON ���� �� ���� �еĴ�����

#include <exception>
#include <source_location>
#include <string>

namespace bre {

// ����JSON�쳣������
enum class JsonErrorType {
    SyntaxError,    // �﷨����
    TypeError,      // ���ʹ����� Ԥ������ȴ�õ�����
    ValueError,     // ֵ����  ���� ��Ч�����ָ�ʽ��
    KeyError,       // ������  ���� ������ȱʧ����ļ���
    UnknownError    // δ֪����
};


class JsonParseException : public std::exception {
public:
    JsonParseException(const std::string& message, JsonErrorType type = JsonErrorType::UnknownError)
        : message_(message), error_type_(type) {}

    const char* what() const noexcept override {
        return message_.c_str();
    }

    // ���ش�������
    JsonErrorType errorType() const noexcept {
        return error_type_;
    }

    // ��̬�����������ض����쳣����
    static JsonParseException SyntaxError(const std::string& details, 
        const std::source_location& location = std::source_location::current()) {
		return JsonParseException("Syntax Error: " + details + " at " + locationMsg(location), JsonErrorType::SyntaxError);
    }

    static JsonParseException TypeError(const std::string& details,
        const std::source_location& location = std::source_location::current()) {
		return JsonParseException("Type Error: " + details + " at " + locationMsg(location), JsonErrorType::TypeError);
    }

    static JsonParseException ValueError(const std::string& details,
        const std::source_location& location = std::source_location::current()) {
		return JsonParseException("Value Error: " + details + " at " + locationMsg(location), JsonErrorType::ValueError);
    }

    static JsonParseException KeyError(const std::string& details,
        const std::source_location& location = std::source_location::current()) {
		return JsonParseException("Key Error: " + details + " at " + locationMsg(location), JsonErrorType::KeyError);
    }

private:
    static std::string locationMsg(std::source_location location) {
		return std::string(location.file_name()) + ":" + std::to_string(location.line()) + ": ";
    }

    std::string message_;
    JsonErrorType error_type_;
};

} // namespace bre
#endif // JSON_EXCEPTION_HPP
