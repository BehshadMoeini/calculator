#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

enum types
{
    INT,
    COMMA,
    ID,
    SEMI,
    IF,
    WHILE,
    OPAR,
    CPAR,
    ASS,
    INTG,
    DOB /* NUM */,
    EOL,
    OCB,
    CCB,
    OB,
    CB,
    EQ,
    LT,
    GT,
    LTE,
    GTE,
    PLUS,
    MINUS,
    MUL,
    FLO,
    DIV
};

const string typesStrings[] = {"INT",
                               "COMMA",
                               "ID",
                               "SEMI",
                               "IF",
                               "WHILE",
                               "OPAR",
                               "CPAR",
                               "ASS",
                               "INTG",
                               "DOB" /* NUM */,
                               "EOL",
                               "OCB",
                               "CCB",
                               "OB",
                               "CB",
                               "EQ",
                               "LT",
                               "GT",
                               "LTE",
                               "GTE",
                               "PLUS",
                               "MINUS",
                               "MUL",
                               "FLO",
                               "DIV"};

void add(vector<pair<string, int>> &s, string x, int type)
{
    if (x == "")
        return;

    if (type == 1)
    {
        if (x == "int")
            s.push_back({x, types::INT});
        else if (x == "double")
            s.push_back({x, types::DOB});
        else if (x == "float")
            s.push_back({x, types::FLO});
        else
            s.push_back({x, types::ID});
    }

    else if (type == 2)
    {
        if (x == ",")
            s.push_back({x, types::COMMA});
        else if (x == ";")
            s.push_back({x, types::SEMI});
        else if (x == "(")
            s.push_back({x, types::OPAR});
        else if (x == ")")
            s.push_back({x, types::CPAR});
        else if (x == "=")
            s.push_back({x, types::ASS});
        else if (x == "*")
            s.push_back({x, types::MUL});
        else if (x == "+")
            s.push_back({x, types::PLUS});
        else if (x == "-")
            s.push_back({x, types::MINUS});
        else if (x == "/")
            s.push_back({x, types::DIV});
    }
    else if (type == 3)
    {
        s.push_back({x, types::INTG});
    }
}

vector<pair<string, int>>
parse(char *str)
{
    vector<pair<string, int>> temp;
    auto len = sizeof(str) / sizeof(char);

    string word;

    int type = 0;
    // type 0->default , 1->characters , 2->operator , 3->number

    bool flag = false;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        {
            if (flag)
            {
                add(temp, word, type);
                flag = false;
                type = 0;
            }
            word = "";
        }
        else if ((str[i] <= 'Z' && str[i] >= 'A') || (str[i] <= 'z' && str[i] >= 'a') || (int)str[i] == 95)
        {
            // Determining IDs
            flag = true;
            if (type == 1 || type == 0)
            {
                type = 1;
                word += str[i];
            }
            else if (type == 2)
            {
                add(temp, word, type);
                word = str[i];
                type = 1;
            }
            else
            {
                cout << "ln:72 Error\n";
                exit(0);
            }
        }
        else if (((int)str[i] >= 48 && (int)str[i] <= 57) || (int)str[i] == 46)
        {
            // Determining number
            flag = true;
            if (type == 1)
            {
                if ((int)str[i] == 46)
                {
                    cout << "ln:84 dot \n";
                    exit(0);
                }
                word += str[i];
            }
            else if (type == 0 || type == 3)
            {
                type = 3;
                word += str[i];
            }
            else if (type == 2)
            {
                add(temp, word, type);
                word = str[i];
                type = 3;
            }
        }
        else if ((int)str[i] >= 33 && (int)str[i] <= 63)
        {
            // Determining Operators
            flag = true;

            if (type == 2 || type == 0)
            {
                type = 2;
                add(temp, word, type);

                word = str[i];
            }
            else if (type == 1 || type == 3)
            {
                add(temp, word, type);
                word = str[i];
                type = 2;
            }
            else
            {
                cout << "ln:120 Error\n";
                exit(0);
            }
        }
        else
        {
            cout << "Error";
            exit(0);
        }
    }

    return temp;
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        cout << "No Arguments !!";
        return 0;
    }

    ifstream nameFileout;
    char test[500];

    nameFileout.open(argv[1]);

    nameFileout.read(test, sizeof(test));

    vector<pair<string, int>> answer = parse(test);

    for (auto it = answer.begin(); it != answer.end(); it++)
    {
        cout << "{ " << typesStrings[it->second]
             << " , "
             << (it->first)
             << " }"
             << endl;
    }

    return 0;
}
