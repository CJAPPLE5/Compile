#ifndef FUNC
#define FUNC

#include<iostream>
#include<string>
#include<map>
#include<string.h>
#include<fstream>
// #include"variable.h"
#include"getsym.h"
#include"constant.h"

using namespace std;

void statement();
void statement_list();
int name_exist(string names[], string name);
void expr();


void param_value_table()
{
	if (symbol == RPARENT) {
		print_grammer(VALUE_TABLE);
	}
	else{
		expr();
		while (symbol == COMMA) {
			print_word();
			getsym();
			expr();
		}
		print_grammer(VALUE_TABLE);
	}
}

void call_noreturn_fcuntion()
{
	if (symbol == IDENFR) {
		print_word();
		getsym();
		if (symbol == LPARENT) {
			print_word();
			getsym();
			param_value_table();
			if (symbol == RPARENT) {
				print_word();
				getsym();
			}
		}
		print_grammer(CALL_FUNCTION_NORETURN);
	}//无返回值函数调用
}

void call_return_function()
{
	if (symbol == IDENFR) {
		print_word();
		getsym();
		if (symbol == LPARENT) {
			print_word();
			getsym();
			param_value_table();
			if (symbol == RPARENT) {
				print_word();
				getsym();
			}
		}
		print_grammer(CALL_FUNCTION_RETURN);
	}//有返回值函数调用
}

void factor()
{
	if (symbol == INTCON || symbol == CHARCON || symbol == PLUS || symbol == MINU) {
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
		else {
			intt();
		}
	}//整数，字符
	else if (symbol == IDENFR && name_exist(return_func_names, string(token))) {
		call_return_function();
	}//有返回函数调用
	else if (symbol == LPARENT) {
		print_word();
		getsym();
		expr();
		if (symbol == RPARENT) {
			print_word();
			getsym();
		}
	}
	else if(symbol == IDENFR){
		print_word();
		getsym();
		if (symbol == LBRACK) {
			print_word();
			getsym();
			expr();
			if (symbol == RBRACK) {
				print_word();
				getsym();
				if (symbol == LBRACK) {
					print_word();
					getsym();
					expr();
					if (symbol == RBRACK) {
						print_word();
						getsym();
					}
				}
			}
		}
	}
	print_grammer(FACTOR);
}

void term()
{
	factor();
	while (symbol == MULT || symbol == DIV) {
		print_word();
		getsym();
		factor();
	}
	print_grammer(TERM);
}

void expr()
{
	if (symbol == PLUS || symbol == MINU) {
		print_word();
		getsym();
	}
	term();
	while (symbol == PLUS || symbol == MINU) {
		print_word();
		getsym();
		term();
	}
	print_grammer(EXPR);
}

void condition()
{
	expr();
	if (symbol == LSS || symbol == LEQ || symbol == GRE ||
		symbol == GEQ || symbol == EQL || symbol == NEQ) {
		print_word();
		getsym();
	}
	expr();
	print_grammer(CONDITION);
}

void steps()
{
	if (symbol == INTCON) {
		print_word();
		print_grammer(UNSIGNINT);
		getsym();
		print_grammer(STEP);
	}
}

void statement_loop()
{
	if (symbol == WHILETK) {
		print_word();
		getsym();
		if (symbol == LPARENT) {
			print_word();
			getsym();
			condition();
			if (symbol == RPARENT) {
				print_word();
				getsym();
				statement();
			}
		}
		print_grammer(SENTENCE_LOOP);
	}
	else if (symbol == FORTK) {
		print_word();
		getsym();
		if (symbol == LPARENT) {
			print_word();
			getsym();
			if (symbol == IDENFR) {
				print_word();
				getsym();
				if (symbol == ASSIGN) {
					print_word();
					getsym();
					expr();
					if (symbol == SEMICN) {
						print_word();
						getsym();
						condition();
						if (symbol == SEMICN) {
							print_word();
							getsym();
							if (symbol == IDENFR) {
								print_word();
								getsym();
								if (symbol == ASSIGN) {
									print_word();
									getsym();
									if (symbol == IDENFR) {
										print_word();
										getsym();
										if (symbol == PLUS || symbol == MINU) {
											print_word();
											getsym();
										}
										steps();
										if (symbol == RPARENT) {
											print_word();
											getsym();
											statement();
										}
									}
								}
							}
						}
					}
				}
			}
		}
		print_grammer(SENTENCE_LOOP);
	}
}//循环语句

void statement_condition()
{
	if (symbol == IFTK) {
		print_word();
		getsym();
		if (symbol == LPARENT) {
			print_word();
			getsym();
			condition();
			if (symbol == RPARENT) {
				print_word();
				getsym();
				statement();
				if (symbol == ELSETK) {
					print_word();
					getsym();
					statement();
				}
			}
		}
		print_grammer(SENTENCE_CONDITION);
	}
}//条件语句

void statement_assign()
{
	if (symbol == IDENFR) {
		print_word();
		getsym();
		if (symbol == LBRACK) {
			print_word();
			getsym();
			expr();
			if (symbol == RBRACK) {
				print_word();
				getsym();
				if (symbol == LBRACK) {
					print_word();
					getsym();
					expr();
					if (symbol == RBRACK) {
						print_word();
						getsym();
					}
				}
			}
		}
		if (symbol == ASSIGN)
		{
			print_word();
			getsym();
			expr();
		}
		print_grammer(SENTENCE_ASSIGN);
	}
}//赋值语句

int name_exist(string names[], string name)
{
	for (int i = 0; i < sizeof(return_func_names)/sizeof(names[0]); i++) {
		if (names[i].compare(name) == 0) {
			return 1;
		}
	}
	return 0;
}

void statement_read()
{
	if (symbol == SCANFTK) {
		print_word();
		getsym();
		if (symbol == LPARENT) {
			print_word();
			getsym();
			if (symbol == IDENFR) {
				print_word();
				getsym();
				if (symbol == RPARENT) {
					print_word();
					getsym();
				}
			}
		}
		print_grammer(SENTENCE_READ);
	}
}//读语句

void statement_write()
{
	if (symbol == PRINTFTK) {
		print_word();
		getsym();
		if (symbol == LPARENT) {
			print_word();
			getsym();
		}
		if (symbol == STRCON) {
			error = has_error();
			if (error != NOERROR) {
				print_error(error);
				getsym();
			}
			else {
				print_word();
				print_grammer(STRING);
				getsym();
			}
			if (symbol == COMMA) {
				print_word();
				getsym();
				expr();
			}
		}
		else {
			expr();
		}
		if (symbol == RPARENT) {
			print_word();
			getsym();
		}
		print_grammer(SENTENCE_WRITE);
	}
}//写语句

void switch_sub_statement()
{
	if (symbol == CASETK) {
		print_word();
		getsym();
		constt();
		if (symbol == COLON) {
			print_word();
			getsym();
			statement();
		}
		print_grammer(SUB_SENTENCE_SWITCH);
	}
}

void swtich_table()
{
	if (symbol == CASETK) {
		switch_sub_statement();
		while (symbol == CASETK) {
			switch_sub_statement();
		}
		print_grammer(SWITCH_TABLE);
	}
}

void switch_default()
{
	if (symbol == DEFAULTTK) {
		print_word();
		getsym();
		if (symbol == COLON) {
			print_word();
			getsym();
			statement();
		}
		print_grammer(DEFAULT);
	}
}

void statement_switch()
{
	if (symbol == SWITCHTK) {
		print_word();
		getsym();
		if (symbol == LPARENT) {
			print_word();
			getsym();
			expr();
			if (symbol == RPARENT) {
				print_word();
				getsym();
				if (symbol == LBRACE) {
					print_word();
					getsym();
					swtich_table();
					switch_default();
					if (symbol == RBRACE) {
						print_word();
						getsym();
					}
				}
			}
		}
		print_grammer(SENTENCE_SWITCH);
	}
}//情况语句

void statement_return()
{
	if (symbol == RETURNTK) {
		print_word();
		getsym();
		if (symbol == LPARENT) {
			print_word();
			getsym();
			expr();
			if (symbol == RPARENT) {
				print_word();
				getsym();
			}
		}
		print_grammer(SENTENCE_RETURN);
	}
}//返回语句

void statement()
{
	if ((symbol == WHILETK || symbol == FORTK) ||
		(symbol == IFTK) ||
		(symbol == IDENFR) ||
		(symbol == SCANFTK) ||
		(symbol == PRINTFTK) ||
		(symbol == SWITCHTK) ||
		(symbol == SEMICN) ||
		(symbol == RETURNTK) ||
		(symbol == LBRACE)
		)
	{
		switch (symbol)
		{
		case WHILETK:
		case FORTK:
			statement_loop();
			break;//循环语句
		case IFTK:
			statement_condition();
			break;//条件语句
		case IDENFR:
			if (name_exist(return_func_names, string(token))) {
				call_return_function();
				if (symbol == SEMICN) {
					print_word();
					getsym();
				}
			}
			else if (name_exist(noreturn_func_names, string(token))) {
				call_noreturn_fcuntion();
				if (symbol == SEMICN) {
					print_word();
					getsym();
				}
			}//函数调用
			else {
				statement_assign();
				if (symbol == SEMICN) {
					print_word();
					getsym();
				}
			}//赋值语句
			break;
		case SCANFTK:
			statement_read();
			if (symbol == SEMICN) {
				print_word();
				getsym();
			}
			break;//读语句
		case PRINTFTK:
			statement_write();
			if (symbol == SEMICN) {
				print_word();
				getsym();
			}
			break;//写语句
		case SWITCHTK:
			statement_switch();
			break;//情况语句
		case SEMICN:
			print_word();
			getsym();
			break;//空
		case RETURNTK:
			statement_return();
			if (symbol == SEMICN) {
				print_word();
				getsym();
			}
			break;//返回语句
		case LBRACE:
			print_word();
			getsym();
			statement_list();
			if (symbol == RBRACE) {
				print_word();
				getsym();
			}
			break;
		default:
			break;
		}
		print_grammer(SENTENCE);
	}
}//语句

void statement_list()
{
	while ((symbol == WHILETK || symbol == FORTK) ||
		(symbol == IFTK) ||
		(symbol == IDENFR) ||
		(symbol == SCANFTK) ||
		(symbol == PRINTFTK) ||
		(symbol == SWITCHTK) ||
		(symbol == SEMICN) ||
		(symbol == RETURNTK) ||
		(symbol == LBRACE)
		)
	{
		statement();
	}
	print_grammer(STATEMENT_LIST);
}//语句列

void complex()
{
	const_descrip();
	variable_description();
	statement_list();
	print_grammer(COMPLEX);
}

void param_table()
{
	if (symbol == INTTK || symbol == CHARTK) {
		print_word();
		getsym();
		if (symbol == IDENFR) {
			print_word();
			getsym();
			while (symbol == COMMA) {
				print_word();
				getsym();
				if (symbol == INTTK || symbol == CHARTK) {
					print_word();
					getsym();
					if (symbol == IDENFR) {
						print_word();
						getsym();
					}
				}
			}
		}
		print_grammer(PARAM_TABLE);
	}
	else if (symbol == RPARENT) {
		print_grammer(PARAM_TABLE);
	}
}

void declare_head()
{
	if (symbol == INTTK || symbol == CHARTK) {
		print_word();
		getsym();
		if (symbol == IDENFR) {
			print_word();
			return_func_names[return_func_len++] = string(token);
			getsym();
		}
		print_grammer(DECLARE_HEAD);
	}
}

void function_define_return()
{
	if (symbol == INTTK || symbol == CHARTK || variable2func == 1) {
		if (variable2func == 1) {
			variable2func = 0;
		}
		else {
			declare_head();
		}
		if (symbol == LPARENT) {
			print_word();
			getsym();
			param_table();
			if (symbol == RPARENT) {
				print_word();
				getsym();
				if (symbol == LBRACE) {
					print_word();
					getsym();
					complex();
					if (symbol == RBRACE) {
						print_word();
						getsym();
					}
				}
			}
		}
		print_grammer(FUNC_RETURN);
	}
}

void function_define_noreturn()
{
	if (symbol == VOIDTK) {
		print_word();
		getsym();
		if (symbol == MAINTK) {
			void2main = 1;
			return;
		}
		if (symbol == IDENFR) {
			print_word();
			noreturn_func_names[noreturn_func_len++] = string(token);
			getsym();
			if (symbol == LPARENT) {
				print_word();
				getsym();
				param_table();
				if (symbol == RPARENT) {
					print_word();
					getsym();
					if (symbol == LBRACE) {
						print_word();
						getsym();
						complex();
						if (symbol == RBRACE) {
							print_word();
							getsym();
						}
					}
				}
			}
		}
		print_grammer(FUNC_NORETURN);
	}
}

void function_define()
{
	while (symbol == INTTK || symbol == CHARTK || symbol == VOIDTK || variable2func == 1) {
		if (symbol == INTTK || symbol == CHARTK || variable2func == 1) {
			function_define_return();
		}
		else {
			function_define_noreturn();
		}
	}
}


void function_main()
{
	if (symbol == VOIDTK || void2main == 1) {
		if (void2main == 0) {
			print_word();
			getsym();
		}
		if (symbol == MAINTK) {
			void2main = 0;
			print_word();
			getsym();
			if (symbol == LPARENT) {
				print_word();
				getsym();
				if (symbol == RPARENT) {
					print_word();
					getsym();
					if (symbol == LBRACE) {
						print_word();
						getsym();
						complex();
						if (symbol == RBRACE) {
							print_word();
							getsym();
						}
					}
				}
			}
		}
		print_grammer(MAIN_FUNC);
	}
}

#endif // FUNC