#ifndef GETSYMM
#define GETSYMM
#include<iostream>
#include<string>
#include<map>
#include<string.h>
#include<fstream>
#include"variable.h"

using namespace std;


char getcharr()
{
    char c;
    if (read_index == strlen(buff)) {
        line++;
        column = 0;
        if (fgets(buff, Maxlength, fp) == 0) {
            c = EOF;
            return c;
        }
        read_index = 0;
    }
    c = buff[read_index++];
    column++;
    return c;
}

void clearToekn()
{
    token[0] = 0;
    length = 0;
}

int isSpace()
{
    return charr == ' ';
}

int isNewline()
{
    return charr == '\n' || charr == '\r';
}

int isTab()
{
    return charr == '\t';
}

int isLetter()
{
    return (charr <= 'z' && charr >= 'a') || (charr <= 'Z' && charr >= 'A') || (charr == '_');
}

int isDigit()
{
    return (charr >= '0' && charr <= '9');
}

int isColon()
{
    return charr == ':';
}

int isComma()
{
    return charr == ',';
}

int isSemi()
{
    return charr == ';';
}

int isEqu()
{
    return charr == '=';
}

int isPlus()
{
    return charr == '+';
}

int isMinus()
{
    return charr == '-';
}

int isDivi()
{
    return charr == '/';
}

int isStar()
{
    return charr == '*';
}

int isLpar()
{
    return charr == '(';
}

int isRpar() 
{
    return charr == ')';
}

int isSQua()
{
    return charr == '\'';
}

int isQua()
{
    return charr == '"';
}

int isWow()
{
    return charr == '!';
}

int isLess()
{
    return charr == '<';
}

int isGre()
{
    return charr == '>';
}

int isStringElement() {
    return (charr == 32) || (charr == 33) || (charr >= 35 && charr <= 126);
}

//void error()
//{
//    printf("Line:%d, index:%d may has an error!\n",line,column);
//    printf("%c\n",charr);
//}

void catToken()
{
    token[length++] = charr;
    token[length] = 0;
}

void retract(int step = 1)
{
    read_index -= step;
}

char to_lower(char c)
{
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 'a';
    }
    else {
        return c;
    }
}

int compare(char a[], char *b) {
    if (strlen(a) != strlen(b)) {
        return 0;
    }
    else {
        for(int i=0;i < strlen(a);i++) {
            if (to_lower(a[i]) != to_lower(b[i])) {
                return 0;
            }
        }
        return 1;
    }
}


//sb search
enum types reserver()
{
    if (compare((char*)"const",token)) {
        return CONSTTK;
    }
    else if (compare((char*)"int",token))
    {
        return INTTK;
    }
    else if (compare((char*)"char",token))
    {
        return CHARTK;
    }
    else if (compare((char*)"void",token))
    {
        return VOIDTK;
    }
    else if(compare((char*)"main",token)) {
        return MAINTK;
    }
    else if (compare((char*)"if",token))
    {
        return IFTK;
    }
    else if (compare((char*)"else",token))
    {
        return ELSETK;
    }
    else if (compare((char*)"switch",token))
    {
        return SWITCHTK;
    }
    else if (compare((char*)"case",token)) {
        return CASETK;
    }
    else if (compare((char*)"default",token)) {
        return DEFAULTTK;
    }
    else if (compare((char*)"while",token)) {
        return WHILETK;
    }
    else if (compare((char*)"for",token)) {
        return FORTK;
    }
    else if (compare((char*)"scanf",token)) {
        return SCANFTK;
    }
    else if (compare((char*)"printf",token)) {
        return PRINTFTK;
    }
    else if (compare((char*)"return",token))
    {
        return RETURNTK;
    }
    else {
        return NOTRESERVED;
    }
    
}

int transNum(char * tokens)
{
    int i = 0,num = 0,d = 1;
    for (i = strlen(tokens) - 1; i >= 0;i--,d*=10) {
        num += (tokens[i] - '0') * d;
    }
    return num;
}


int getsym()
{
    clearToekn();
    charr = getcharr();
    while (isSpace() || isNewline() || isTab())
    {
        /* code */
        charr = getcharr();
    }
    if(charr == EOF) {
        return -1;
    }
    if (isLetter()) {
        while (isLetter() || isDigit())
        {
            /* code */
            catToken();
            charr = getcharr();
        }
        retract();
        enum types resultValue = reserver();

        if (resultValue == NOTRESERVED) {
            symbol = IDENFR;
        }
        else {
            symbol = resultValue;
        }
    }//鏍囪瘑绗﹀強淇濈暀瀛?
    else if(isDigit()) {
        while (isDigit())
        {
            /* code */
            catToken();
            charr = getcharr();
        }
        retract();
        num = transNum(token);
        symbol = INTCON;
    }//鏁村舰甯搁噺
    else if(isSQua()){
        charr = getcharr();
        catToken();
        charr = getcharr();
        symbol = CHARCON;
    }//瀛楃?甯搁噺
    else if(isQua()) {
        charr = getcharr();
        while(isStringElement()) {
            catToken();
            charr = getcharr();
        }
        symbol = STRCON;
    }//瀛楃?涓?
    else if (isWow())
    {
        catToken();
        charr = getcharr();
        if (charr == '=') {
            catToken();
            symbol = NEQ;
        }
        else {
            error();
        }
    }//!=
    else if (isLess()) {
        catToken();
        charr = getcharr();
        if(isEqu()) {
            symbol = LEQ;
            catToken();
        }
        else {
            symbol = LSS;
            retract();
        }
    }// <,<=
    else if (isGre()) {
        catToken();
        charr = getcharr();
        if(isEqu()) {
            symbol = GEQ;
            catToken();
        }
        else {
            symbol = GRE;
            retract();
        }
    }// >,>=
    else if(isEqu()) {
        catToken();
        charr = getcharr();
        if(isEqu()) {
            symbol = EQL;
            catToken();
        }
        else {
            symbol = ASSIGN;
            retract();
        }
    }
    else {
        for(int i = single_begin; i < 28; i++) {
            if (charr == single_reseved_names[i][0]) {
            	catToken();
                symbol = reserved[i];
                break;
            }
        }
    }
    return 1;   
}

void print_word() {
    /*
    output.append(lefts[symbol]);
    output.push_back(' ');
    output.append(token);
    output.push_back('\n');
    */

    //outfile<< lefts[symbol] <<" "<<token << endl;
}

void print_grammer(enum nodes node)
{
    /* error 
    string grammer = nodes_output[node];
    output.append(grammer);
    output.push_back('\n');
    */


    /*grammer_node = VARIBALE_DESCRIP;
    outfile << nodes_output[grammer_node] << endl;*/

}

void print_error(enum errors temp_error)
{
    error_output << line << ' ' << 'a' + temp_error << endl;
}

void insert_output(string s,int insert_index) {
    /*output.insert(insert_index, s);*/
}

void write2file()
{
    /*outfile << output;
    output = string("");*/
}

#endif // !1