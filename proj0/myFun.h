#ifndef MYFUN_H
#define MYFUN_H
#include "mainwindow.h"
using namespace std;

struct myCmd
{
    int token;
    vector<string> data;
};

struct myOpt
{
    int id;
    int val_num;
};

struct myVal
{
    string name;
    double val;
};

extern map<string, myOpt> tokens;
extern vector<myVal> vals;

double s2num(const string &s);
int ini_list();
int readHead(ifstream &infile, int &width, int &height, int &r, int &g, int &b, int &xpos, int &ypos);
int mainProcess(ifstream &infile);
int myExe(const myCmd &cmd);
int readLine(ifstream &infile, myCmd &cmd);
void errorOccurred();

struct codeBlock
{
    vector<myCmd> cmds;
    int &type;

    codeBlock(int &_type):type(_type) {}

    int exec();
};

auto find_val(const string &s)
{
    auto it = vals.rbegin();
    for (; it != vals.rend(); it++)
    {
        if (it->name == s)
            break;
    }
    return it;
}

int codeBlock::exec()
{
    int tot = this->type == 0 ? 1 : type;
    for (int i = 1; i <= tot; i++)
    {
        int ex_size = vals.size();
        for (int ii = 0; ii <= cmds.size() - 1; ii++)
        {
            myExe(cmds[ii]);
        }
        //delete the local values
        auto start_pos = begin(vals) + ex_size;
        auto end_pos = begin(vals) + vals.size();
        vals.erase(start_pos, end_pos);
    }
    return 0;
}

double s2num(const string &s)
{
    auto point_pos = s.find('.');
    int l = s.length();
    if (point_pos == s.npos)
    {
        int ten = 1;
        int num = 0;
        for (int i = l - 1; i >= 0; i--)
        {
            num += (s[i] - '0') * ten;
            ten *= 10;
        }
        return num;
    }
    else
    {
        double num = 0;
        num += s2num(s.substr(0, point_pos));
        double ten = 0.1;
        for (int i = point_pos + 1; i <= l - 1; i++)
        {
            num += (s[i] - '0') * ten;
            ten /= 10;
        }
        return num;
    }
}

int ini_list()
{
    tokens["DEF"] = { 1, 2 };
    tokens["ADD"] = { 1, 2 };

    return 0;
}

//by Colin
//There are too many arguments! It seems ugly, but it CAN run whatever.
//So, let it be!
int readHead(ifstream &infile, int &width, int &height, int &r, int &g, int &b, int &xpos, int &ypos)
{
    string in;
    getline(infile, in);
    //@SIZE 1920 1080
    if (in.substr(0, 5) == "@SIZE") //substr(a, b) -> [a, b)
    {
        //unsigned long first = in.find_first_of(' ');
        unsigned long first = 5;
        unsigned long second = in.find_last_of(' ');
        int w = s2num(in.substr(first + 1, second - first - 1));
        int h = s2num(in.substr(second + 1));
        if (320 <= w && w <= 1920 && 240 <= h && h <= 1080)
        {
            width = w;
            height = h;
        }
        else
            errorOccurred();
    }
    else
        errorOccurred();

    //@BACKGROUND 255 255 255
    getline(infile, in);
    if (in.substr(0, 11) == "@BACKGROUND")
    {
        int i = 0;
        //R
        string tmp;
        for (i = 12; i <= in.length() - 1; i++)
        {
            if ('0' <= in[i] && in[i] <= '9')
                tmp += in[i];
            else if (in[i] == ' ')
            {
                r = s2num(tmp);
                break;
            }
        }
        //G
        tmp = "";
        for (i++; i <= in.length() - 1; i++)
        {
            if ('0' <= in[i] && in[i] <= '9')
                tmp += in[i];
            else if (in[i] == ' ')
            {
                g = s2num(tmp);
                break;
            }
        }
        //B
        tmp = "";
        for (i++; i <= in.length() - 1; i++)
        {
            if ('0' <= in[i] && in[i] <= '9')
                tmp += in[i];
            else if (in[i] == '\0')
            {
                b = s2num(tmp);
                break;
            }
        }
        //Check
        if (0 <= r && r <= 255 && 0 <= g && g <= 255 && 0 <= b && b <= 255)
            ;
        else
            errorOccurred();
    }
    else
        errorOccurred();

    //@POSITION 959 10
    getline(infile, in);
    if (in.substr(0, 9) == "@POSITION")
    {
        unsigned long first = 9;
        unsigned long second = in.find_last_of(' ');
        int x = s2num(in.substr(first + 1, second - first - 1));
        int y = s2num(in.substr(second + 1));
        if (0 <= x && x <= width - 1 && 0 <= y && y <= height - 1)
        {
            xpos = x;
            ypos = y;
        }
        else
            errorOccurred();
    }
    else
        errorOccurred();

    return 0;
}

//by Colin
int readLine(ifstream &infile, myCmd &cmd)
{
    string input;
    while (infile >> input)
    {
        map<string, myOpt>::iterator find = tokens.find(input);
        if (find != tokens.end())
        {
            cmd.token = find->second.id;
            for (int i = 1; i <= find->second.val_num; i++)
            {
                infile >> input;
                cmd.data.push_back(input);
            }
        }
        return 0;
    }
    return 1;
}

int myExe(const myCmd &cmd)
{
    if (cmd.token == 1) //DEF [Name] [Value]
    {
        vals.push_back( { cmd.data[0], s2num(cmd.data[1]) } );
    }
    else if (cmd.token == 2)    //ADD [Name] [Value]
    {
        auto it = find_val(cmd.data[0]);
        if (it != vals.rend())  //find it!
        {
            it->val += s2num(cmd.data[1]);
        }
        else
            errorOccurred();
    }
    return 0;
}

void errorOccurred()
{
    cout << "Error occurred!\n";
}

#endif // MYFUN_H
