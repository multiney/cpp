#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <regex>
#include <random>

using std::string;

void operateFile() {
    std::ifstream input("./DataStruct/StackQueue/StackQueue.cpp");
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
    std::ofstream output("./DataStruct/StackQueue/StackQueue.cpp");
    output << contents;
    output.close();
}

void generateChartParam(int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> xNum(6, 12), yRange(0, 200), xStep(5, 20);
    string line;
    int xnum = xNum(gen), xstep = xStep(gen);
    for (int j = 0; j < xnum; ++j) {
        line = std::to_string(xstep * (j + 1));
        line += " : ";
        for (int i = 0; i < n - 1; ++i) {
            line += std::to_string(yRange(gen)) + ", ";
        }
        line += std::to_string(yRange(gen));
        std::cout << line << std::endl;
    }
}

int main (int argc, char *argv[])
{
    operateFile();
}
