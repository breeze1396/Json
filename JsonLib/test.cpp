#include "Json.hpp"
#include <iostream>
#include <fstream>


using namespace std;
using namespace bre;

static void test() {
    Value jsonArray;
    jsonArray.setArray();
    jsonArray[0] = Value();
    jsonArray[0].setInt(10);
    jsonArray[1] = Value();
    jsonArray[1].setString("hello");

    std::cout << jsonArray << "\n====\n";
	for (int i = 0; i < jsonArray.size(); i++) {
		std::cout << jsonArray[i] << std::endl;
	}

    Value jsonObject;
    jsonObject.setObject();
    jsonObject["key1"] = Value();
    jsonObject["key1"].setBool(true);


}

static void test2() {
    std::string jsonString = R"({"name": "John", "age": 30, "married": false, "children": ["Anna", "Bob"]})";
    try {
        Value root;
        Parser::parse(jsonString, root);
        std::cout << root["name"].asString() << std::endl; // ��� "John"
        std::cout << root["age"].asInt() << std::endl;     // ��� 30
        std::cout << root["children"][0].asString() << std::endl; // ��� "Anna"
    }
    catch (const JsonParseException& e) {
        std::cerr << "Parse error: " << e.what() << std::endl;
    }
	std::cout << "\n\n";
}



void test3() {
    // ����һ�� JSON ����
    Value root;
    root.setObject();
    root["name"] = Value("John");
    root["age"] = Value(30);
    root["married"] = Value(false);
    root["children"].setArray();
    root["children"].append(Value("Anna"));
    root["children"].append(Value("Bob"));

    // ���� JSON �ַ���
    try {
        std::string jsonString = Generator::generate(root);
        std::cout << jsonString << std::endl; // ������ɵ� JSON �ַ���
    } catch (const JsonParseException& e) {
        std::cerr << "Generation error: " << e.what() << std::endl;
    }

}

void test4() {
    // ���ļ��ж�ȡ JSON �ַ���
    std::ifstream file("test.json");
    if (!file.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return;
    }

    std::string jsonString((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
	std::cout << jsonString << "\n\n===========\n\n";
    // ���� JSON �ַ���
    try {
        Value root = Parser::parse(jsonString);

        cout << root.size() << "\n";
        std::cout << root << std::endl;
    } catch (const JsonParseException& e) {
        std::cerr << "Parse error: " << e.what() << std::endl;
    }
}

int main() {
	test();
	test2();
	test3();
	test4();
	return 0;
}
