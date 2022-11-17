#include <fstream>
#include <istream>
#include <string>
#include <regex>

using std::string;

int main (int argc, char *argv[])
{
    std::ifstream input("../../vk/ccpp/DataStruct/Array/array.cpp");
    string line;
    string contents;
    std::regex reg(R"( \d+\. )");
    int i = 0;
    while (std::getline(input, line)) {
        std::smatch match;
        bool flag = std::regex_search(line, match, reg);
        if (flag)
            line = line.append(" " + std::to_string(++i));
        line += "\n";
        contents += line;
    }
    input.close();
    std::ofstream output("../../vk/ccpp/DataStruct/Array/array.cpp");
    output << contents;
    output.close();
    return 0;
}
