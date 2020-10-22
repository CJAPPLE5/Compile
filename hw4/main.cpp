#include<iostream>
#include<string>
#include<map>
#include<string.h>
#include<fstream>
// #include"variable.h"
#include"constant.h"
#include"function.h"

#pragma  warning (disable:4996) 

using namespace std;



void program()
{
    getsym(); 
    const_descrip();
    write2file();
    variable_description();
    write2file();
    function_define();
    write2file();
    function_main();
    write2file();
    print_grammer(PROGRAM);
    write2file();
}



int main()
{
    fp = fopen("testfile.txt","r");
    

    //outfile = ofstream("output.txt");
    error_output = ofstream("error.txt");
    fgets(buff, Maxlength, fp);
    program();
}