#ifndef VARIABLE
#define VARIABLE
#include <iostream>
#include <string.h>
#include <string>
#include<vector>

using namespace std;

#define Maxlength 1024
#define single_begin 15
#define const_index 4
#define return_index 18
#define emp_nodes_index 37

enum types{
    IDENFR,INTCON,CHARCON,STRCON,CONSTTK,INTTK,CHARTK,VOIDTK,MAINTK,IFTK,ELSETK,
    SWITCHTK,CASETK,DEFAULTTK,WHILETK,FORTK,SCANFTK,PRINTFTK,RETURNTK,PLUS,
    MINU,MULT,DIV,LSS,LEQ,GRE,GEQ,EQL,NEQ,COLON,
    ASSIGN,SEMICN,COMMA,LPARENT,RPARENT,LBRACK,RBRACK,LBRACE,RBRACE,
    NOTRESERVED,NOTIMPLEMENTED
};

string lefts[] = {
    "IDENFR","INTCON","CHARCON","STRCON","CONSTTK","INTTK","CHARTK","VOIDTK","MAINTK","IFTK","ELSETK",
    "SWITCHTK","CASETK","DEFAULTTK","WHILETK","FORTK","SCANFTK","PRINTFTK","RETURNTK","PLUS",
    "MINU","MULT","DIV","LSS","LEQ","GRE","GEQ","EQL","NEQ","COLON",
    "ASSIGN","SEMICN","COMMA","LPARENT","RPARENT","LBRACK","RBRACK","LBRACE","RBRACE"
};

//28
enum types reserved[] = {
    CONSTTK,INTTK,CHARTK,VOIDTK,MAINTK,IFTK,ELSETK,
    SWITCHTK,CASETK,DEFAULTTK,WHILETK,FORTK,SCANFTK,PRINTFTK,RETURNTK,
    PLUS,MINU,MULT,DIV,COLON,SEMICN,COMMA,LPARENT,RPARENT,
    LBRACK,RBRACK,LBRACE,RBRACE
};

string single_reseved_names[] = {
    "const","int","char","void","main","if","else","switch","case","default",
    "while","for","scanf","printf","return","+","-","*","/",":",";",",","(",")",
    "[","]","{","}"
};



enum nodes{
    STRING, PROGRAM, CONST_DECRIP, CONST_DEFINE, UNSIGNINT, INTT, DECLARE_HEAD, CONSTT,
    VARIBALE_DESCRIP, VARIABLE_DEFINE, VARIABLE_DEFINE_NOINIT, VARIABLE_DEFINE_INIT, 
    FUNC_RETURN, FUNC_NORETURN, COMPLEX, PARAM_TABLE, MAIN_FUNC, EXPR, TERM, FACTOR,
    SENTENCE, SENTENCE_ASSIGN, SENTENCE_CONDITION, CONDITION, SENTENCE_LOOP, STEP,
    SENTENCE_SWITCH, SWITCH_TABLE, SUB_SENTENCE_SWITCH, DEFAULT, CALL_FUNCTION_RETURN,
    CALL_FUNCTION_NORETURN, VALUE_TABLE, STATEMENT_LIST, SENTENCE_READ,
    SENTENCE_WRITE, SENTENCE_RETURN, OPERATOR_PLUS, OPERATOR_MULT, OPERATOR_RELATION, 
    ALPHABET, NUMBER, CHARACTER, IDENTIFIER, TYPE_INDENTIFIER, 
};

enum nodes test_nodes[] = {
    STRING, PROGRAM, CONST_DECRIP, CONST_DEFINE, UNSIGNINT, INTT, DECLARE_HEAD, CONSTT,
    VARIBALE_DESCRIP, VARIABLE_DEFINE, VARIABLE_DEFINE_NOINIT, VARIABLE_DEFINE_INIT, 
    FUNC_RETURN, FUNC_NORETURN, COMPLEX, PARAM_TABLE, MAIN_FUNC, EXPR, TERM, FACTOR,
    SENTENCE, SENTENCE_ASSIGN, SENTENCE_CONDITION, CONDITION, SENTENCE_LOOP, STEP,
    SENTENCE_SWITCH, SWITCH_TABLE, SUB_SENTENCE_SWITCH, DEFAULT, CALL_FUNCTION_RETURN,
    CALL_FUNCTION_NORETURN, VALUE_TABLE, STATEMENT_LIST, SENTENCE_READ,
    SENTENCE_WRITE, SENTENCE_RETURN
};

string nodes_output[] = {
    "<字符串>","<程序>","<常量说明>","<常量定义>","<无符号整数>","<整数>",
    "<声明头部>","<常量>","<变量说明>","<变量定义>","<变量定义无初始化>","<变量定义及初始化>",
    "<有返回值函数定义>","<无返回值函数定义>","<复合语句>","<参数表>","<主函数>","<表达式>",
    "<项>","<因子>","<语句>","<赋值语句>","<条件语句>","<条件>","<循环语句>",
    "<步长>","<情况语句>","<情况表>","<情况子语句>","<缺省>","<有返回值函数调用语句>",
    "<无返回值函数调用语句>","<值参数表>","<语句列>","<读语句>","<写语句>",
    "<返回语句>"
};

enum errors {
    ILLEGALWORD, NAMEREDEFINE, NAMEUNDEFINE, FUNCPARAMNUMBERMISMATCH, FUNCPARAMTYPEMISMATCH, CONDITIONLEEGALTYPE, NORETURNFUNCMISMATCHRETURN,
    RETURNFUNCRETURN, ARRAYINDEX, CHANGECONST, SHOULDBESEMICON, SHOULDBERPARENT, SHOULDBERBRACK, ARRAYINTMISMATCH, CONSTTYPEMISMATCH, LACKDEFAULT,
    NOERROR
};

class dataa
{
public:
    dataa(string namee, string typee) {
        name = namee;
        type = typee;
    }
    string name;
    string type;
    vector<int> shape;

    void add_shape(vector<int> shapee) {
        shape = shapee;
    }
    void add_shape(int size) {
        shape.push_back(size);
    }
    string getname() {
        return name;
    }
    string gettype() {
        return type;
    }
    vector<int> getshape() {
        return shape;
    }
};

class symbol_teble
{
public:
    map<string, map<string, dataa>> name2funcblock;

    int hassamename(char* namee) {
        string name = string(namee);
        map<string, map<string, dataa>>::iterator iter;
        for (iter = name2funcblock.begin(); iter != name2funcblock.end(); iter++) {
            map<string, dataa> temp = iter->second;
            if (temp.find(name) != temp.end()) {
                return 1;
            }
        }
        return 0;
    }

    void insert_data(string funcblock, string name, string type, vector<int> shape) {
        map<string, dataa> temp_block;
        if (name2funcblock.find(funcblock) != name2funcblock.end()) {
            map<string, dataa> temp_block = name2funcblock.find(funcblock)->second;
        }
        dataa temp_data(name, type);
        temp_data.add_shape(shape);
        temp_block[name] = temp_data;
        name2funcblock[funcblock] = temp_block;
    }
};

symbol_teble symboltable;

string blockstack[20];
int block = 0;

enum errors error;

string return_func_names[128];
string noreturn_func_names[128];

int return_func_len = 0, noreturn_func_len = 0;
char charr;

char token[Maxlength];
char buff[Maxlength];

string output;

int len_out = 0;

int num;
enum types symbol;
int length = 0;
enum nodes grammer_node;
int line = 0;
int column = 0;
int read_index;
int variable2func = 0;
int void2main = 0;
int insert_index = 0;
int truevariable = 0;


FILE *fp = NULL;

ofstream outfile;

ofstream error_output;

#endif