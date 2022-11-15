#include <fstream>
#include <istream>
#include <string>

using std::string;

int main (int argc, char *argv[])
{
    std::ifstream input("../../../mnt/c/Users/Administrator/Desktop/工业互联网/机理模型/模型因子标识.md");
    std::ofstream output("../../../mnt/c/Users/Administrator/Desktop/工业互联网/机理模型/new.md");
    string line;
    int i = 0;
    while (std::getline(input, line)) {
        auto begPos = line.find("#####");
        if (begPos != string::npos) {
            begPos += 5;
            line.insert(begPos, " " + std::to_string(++i));
        }
        output << line;
    }
    input.close();
    output.close();
    return 0;
}
