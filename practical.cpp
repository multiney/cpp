#include <fstream>
#include <istream>
#include <string>

using std::string;

int main (int argc, char *argv[])
{
    std::ifstream input("../../../mnt/c/Users/Administrator/Desktop/SQL.txt");
    std::ofstream output("../../../mnt/c/Users/Administrator/Desktop/insertSql.txt");
    string line;
    while (std::getline(input, line)) {
        auto begPos = line.find("2020") - 1;
        line.insert(begPos, "TO_DATE(");
        line.insert(begPos + 29, ", 'yyyy-MM-dd hh24:mi:ss')");
        output << line;
    }
    input.close();
    output.close();
    return 0;
}
