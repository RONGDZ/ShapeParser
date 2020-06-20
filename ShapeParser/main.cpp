// ShapeParser.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include "ShapeParserMgr.h"
#include "GeoShapeFmtMgr.h"
#include "GeoWhole.h"

GEO_NAMESPACE_USING;
using namespace std;
void wf()
{
    ofstream outfile;
    outfile.open("./test.txt", ios::out);

    if (!outfile)
    {
        cerr << "open out failed !" << endl;
        exit(1);
    }
    outfile << "line stroke-width 10 stroke 0xFF00FF opacity 100 xy 0,0 100,0 100,100 0,100\n";
    outfile << "line 0,0 200,0 200,100 0,100\n";
    outfile << "polygen stroke-width 10  fill 0xFF00FF stroke 0xFFFF00FF offset 100,100 outline 0,0 100,0 100,100 0,100\n";
    outfile << "line tag 1,2 4 test info 5 5 t1 test1 t2 test2 outline  0,0 200,0 200,100 0,100\n";
    //outfile << "plank tag 1,2 4 test info 5 5 t1 test1 t2 test2 xy 0,0 100,0 100,100 0,100\n";

    outfile.flush();
    outfile.close();
}

void rf()
{
    GeoWhole wh;
    ShapeParserMgr spm(&wh);
    fstream infile;
    char buff[8192] = {0};
    infile.open("./test.txt", ios::in);
    if (!infile)
    {
        cerr << "open failed!" << endl;
        exit(1);
    }
    while (!infile.eof())
    {
        infile.read(buff, size(buff));
        int sz = infile.gcount();
        spm.parser(buff, sz);
       
    }
    infile.close();
    GeoShapeFmtMgr gsfm;
    std::string s;
    for (auto n : wh.shapes)
    {
        gsfm.fmtShape(n, s);
    }
    int len = s.length();
}

int main()
{
    wf();
    rf();
   
    std::cout << "Hello World!\n";
}
