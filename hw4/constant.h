#ifndef CONSTANT
#define CONSTANT

#include<iostream>
#include<string>
#include<map>
#include<string.h>
#include<fstream>
 //#include"variable.h"
#include"getsym.h"
#include"error.h"


using namespace std;

void intt();

void constt()
{
    if (symbol == CHARCON) {
        error = has_error();
        if (error != NOERROR) {
            print_error(error);
            getsym();
        }
        else {
            print_word();
            getsym();
            print_grammer(CONSTT);
        }
    }
    else if (symbol == PLUS || symbol == MINU || symbol == INTCON) {
        intt();
        print_grammer(CONSTT);
    }

}

void intt() {
    if (symbol == PLUS || symbol == MINU) {
            print_word();
            getsym();
    }
    if (symbol == INTCON) {
        print_word();
        print_grammer(UNSIGNINT);
        print_grammer(INTT);
        getsym();
        /*print_word();*/
    }
}

void const_define()
{
    int flag = 0;
    if (symbol == INTTK) {
        flag = 1;
    }
    else if (symbol == CHARTK) {
        flag = 2;
    }
    else {
        ;
    }
    if (symbol == INTTK || symbol == CHARTK) {
        print_word();
        getsym();
        if (symbol != IDENFR) {
            ;
        }
        string typee = (flag == 1) ? string("int") : string("char");
        vector<int> shape;
        shape.push_back(0);
        if (symboltable.hassamename(token)) {
            error = NAMEREDEFINE;
            print_error(error);
            getsym();
        }
        else {
            symboltable.insert_data(blockstack[block], string(token), typee, shape);
            print_word();
            getsym();
        }
        if (symbol != ASSIGN) {
            ;
        }
        print_word();
        getsym();
        if (flag == 1) {
            intt();
        }
        else {
            if (symbol == CHARCON) {
                error = has_error();
                if (error != NOERROR) {
                    print_error(error);
                    getsym();
                }
                else {
                    print_word();
                    getsym();
                }
            }
        }
        while (symbol == COMMA){
            print_word();
            getsym();
            if (symbol != IDENFR) {
                ;
            }
            if (symboltable.hassamename(token)) {
                error = NAMEREDEFINE;
                print_error(error);
                getsym();
            }
            else {
                symboltable.insert_data(blockstack[block], string(token), typee, shape);
                print_word();
                getsym();
            }
            if (symbol != ASSIGN) {
                ;
            }
            print_word();
            getsym();
            if (flag == 1) {
                intt();
            }
            else {
                if (symbol == CHARCON) {
                    error = has_error();
                    if (error != NOERROR) {
                        print_error(error);
                        getsym();
                    }
                    else {
                        print_word();
                        getsym();
                    }
                }
            }
        }
        print_grammer(CONST_DEFINE);
    }
    else {
        ;
    }
}

void const_descrip()
{
    if (symbol == CONSTTK) {
        while (symbol == CONSTTK) {
            print_word();
            getsym();
            const_define();
            if (symbol == SEMICN) {
                print_word();
                getsym();
            }
        }
        print_grammer(CONST_DECRIP);
    }
}


void variable_define_noinit()
{
    while (symbol == COMMA) {
        print_word();
        getsym();
        if (symbol == IDENFR)
        print_word();
        getsym();
        while (symbol == LBRACK) {
            print_word();
            getsym();
            print_word();
            print_grammer(UNSIGNINT);
            getsym();
            print_word();
            getsym();
        }
    }
    print_grammer(VARIABLE_DEFINE_NOINIT);
}

void variable_define_init(int pairs, enum types typee, int shape_0, int shape_1)
{
    if (symbol == ASSIGN) {
        print_word();
        getsym();
        if (pairs == 0) {
            constt();
        }
        else if (pairs == 1) {
            if (symbol == LBRACE) {
                print_word();
                getsym();
                for (int i = 0; i < shape_0 - 1; i++) {
                    constt();
                    if (symbol == COMMA) {
                        print_word();
                    }
                    getsym();
                }
                constt();
                if (symbol == RBRACE) {
                    print_word();
                    getsym();
                }
            }
        }
        else if (pairs == 2) {
            if (symbol == LBRACE) {
                print_word();
                getsym();
                for (int i = 0; i < shape_0; i++) {
                    if (symbol == LBRACE) {
                        print_word();
                        getsym();
                        for (int j = 0; j < shape_1; j++) {
                            constt();
                            if (j != shape_1 - 1 && symbol == COMMA) {
                                print_word();
                                getsym();
                            }
                        }
                        if (symbol == RBRACE) {
                            print_word();
                            getsym();
                        }
                        if (symbol == COMMA) {
                            print_word();
                            getsym();
                        }
                    }
                }
                if (symbol == RBRACE) {
                    print_word();
                    getsym();
                }
            }
        }
        print_grammer(VARIABLE_DEFINE_INIT);
    }

}

void variable_define()
{
    if (symbol == INTTK || symbol == CHARTK) {
        enum types typee = (symbol ==INTTK)?INTCON:CHARCON;
        string str_type = (symbol == INTTK) ? string("int") : string("char");
        insert_index = output.length();
        print_word();
        getsym();
        vector<int> shapee;
        if (symbol == IDENFR) {
            print_word();
            string funcname_possiable = string(token);
            getsym();
            int pairs = 0;
            int shape[2];
            if (symbol == LPARENT) {
                variable2func = 1;
                return_func_names[return_func_len++] = funcname_possiable;
                print_grammer(DECLARE_HEAD);
                return;
            }
            while (symbol == LBRACK) {
                print_word();
                getsym();
                shape[pairs++] = num;
                shapee.push_back(num);
                print_word();
                print_grammer(UNSIGNINT);
                getsym();
                print_word();
                getsym();
            }
            if (symbol == ASSIGN) {
                variable_define_init(pairs,typee, shape[0],shape[1]);
            }
            else if (symbol == COMMA){
                variable_define_noinit();
            }
            else {
                print_grammer(VARIABLE_DEFINE_NOINIT);
            }
        }
        truevariable = 1;
        print_grammer(VARIABLE_DEFINE);
    }
}


void variable_description()
{
    if (symbol == INTTK || symbol == CHARTK) {
        while (symbol == INTTK || symbol == CHARTK) {
            variable_define();
            if (variable2func == 1) {
                break;
            }
            if (symbol == SEMICN) {
                print_word();
                getsym();
            }
        }
        if (variable2func == 1 && truevariable == 1) {
            string temp = nodes_output[VARIBALE_DESCRIP];
            temp.push_back('\n');
            insert_output(temp, insert_index);
        }
        else if(variable2func != 1){
            print_grammer(VARIBALE_DESCRIP);
        }
    }
}

#endif