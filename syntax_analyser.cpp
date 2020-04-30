#include <iostream>
#include <vector>
using namespace std;


enum STATE
	{
		initialState, IDENT, NUMB, COM, ABOVELESSEQUAL, INEQUAL, REAL, UNAR, STRING_CONST, COM1
	};

enum LexemType
{
	LEX_AND, //0
	LEX_BEGIN, //1
	LEX_DO, //2
	LEX_ELSE, //3
	LEX_END, //4
	LEX_IF, //5
	LEX_FALSE, //6
	LEX_INT, //7
	LEX_REAL, //8
	LEX_STRING, //9
	LEX_NOT, //10
	LEX_OR, //11
	LEX_PROGRAM, //12
	LEX_STEP, //13
	LEX_READ, //14
	LEX_THEN, //15
	LEX_TRUE, //16
	LEX_GOTO, //17
	LEX_VAR, //18
	LEX_WHILE, //19
	LEX_WRITE, //20
	LEX_ID, //21
	LEX_CONSTSTRING, //22
	LEX_CONSTINT, //23
	LEX_CONSTREAL, //24
	LEX_MARKEDIDENT, // 25
	LEX_BORDERLEXEM_0, // BORDER_LEXEM 25
	LEX_SEMICOLON, //26
	LEX_DOGSYMB, //27
	LEX_COMMA, //28
	LEX_COLON, //29
	LEX_ASSIGN, //30
	LEX_LEFTBRACKET, //31
	LEX_RIGHTBRACKET, //32
	LEX_LEFTBRACE, //33
	LEX_RIGHTBRACE, //34
	LEX_EQUAL, //35
	LEX_LESS, //36
	LEX_MORE, //37
	LEX_PLUS, //38
	LEX_MINUS, //39
	LEX_STAR, //40
	LEX_SLASH, //41
	LEX_LESSEQUAL, //42
	LEX_MOREEQUAL, //43
	LEX_UNARPLUS, //44
	LEX_UNARMINUS, //45
	LEX_INEQUAL, //46
	LEX_BORDERLEXEM_1, // BORDER_LEXEM1 47
	LEX_EOF, // 48
	LEX_NULL // 49
};

class Lex 
{
	LexemType lexem;
	int int_lex;
	float real_lex;
	string const_part;
public:
	Lex (LexemType lex = LEX_NULL, int int_part = 0, float real_part = 0, string new_string = "")
	{
		lexem = lex;
		int_lex = int_part;
		real_lex = real_part;
		const_part = new_string;
	}
	LexemType get_type() const
	{
		return lexem;
	}
	int get_value_int() const
	{
		return int_lex;
	}
	string get_string() const
	{
		return const_part;
	}
	float get_value_double() const
	{
		return real_lex;
	}
	friend ostream& operator<<(ostream & command, Lex lexem_output)
	{
		if (lexem_output.get_type() != LEX_REAL)
			command << '(' << lexem_output.get_type() << ',' << lexem_output.get_value_int() << ");";
		else
			command << '(' << lexem_output.get_type() << ',' << lexem_output.get_value_double() << ");";
		throw "!";
	}
};
class Ident 
{
		string name;
		bool declare;
		LexemType type;
		bool assign;
		int value;
public:
	Ident() 
	{
		declare = false;
		assign = false; 
	}
	Ident(const string n) 
	{
		name = n;
		declare = false;
		assign = false; 
	}
    bool operator== (const string& s) const 
    {
		return name == s; 
	}
    string get_name ( ) 
    {
    	return name; 
    }
	bool get_declare ( ) 
	{ 
		return  declare;
	}
	void put_declare ( ) 
	{ 
		declare = true;
	}
	LexemType get_type ( ) 
	{
		return  type;
	}
	void put_type ( LexemType t ) 
	{
		type = t; 
	}
	bool get_assign ( ) 
	{ 
		return  assign;
	}
	void put_assign ( ) 
	{
		assign = true;
	}
	int get_value ( ) 
	{ 
		return  value;
	}
	void put_value (int val) 
	{ 
		value = val;
	}
};

class Scanner 
{
	FILE *filePointer; 
	char currSymb;	
	int look (const string& buf,  string list []) 
	{
		int i = 0;	
		while (list[i] != "fin" && list[i] != "fin1")
		{
			if ( buf ==  list [ i ] )
			{
				return i;
			}
			i++;  
		}
		return 0;  
	}
	void getChar ( )
	{ 
		currSymb = fgetc ( filePointer ); 
	}
	public:
        static string TW [], TD [], AllowedSymbols[];
		Scanner () 
		{
			filePointer = fopen ( "file.txt", "r" ); 
        }
		Lex get_lex();
};

vector <Ident> tableOfID;
int  put(const string & buf) 
{
	vector <Ident>::iterator k;
	k = find (tableOfID.begin(), tableOfID.end(), buf);
	if ( k != tableOfID.end() )
		return (k - tableOfID.begin());
	tableOfID.push_back(buf);  
	return (tableOfID.size() - 1);
}


string Scanner:: TW [] = 
	{"and","begin","do","else","end",
	"if","false","int","real","string","not","or","program","step", "read",
	"then","true", "goto", "var","while","write", "fin"};

string Scanner:: TD [] = 
	{"hello" ,";", "@", ",", ":", ":=", "(", ")", "{", "}",
	"=","<", ">", "+", "-", "*", "/", "<=", ">=", "++", "--", "!=", "fin1"};

string Scanner:: AllowedSymbols [] = 
	{"hello" ,";", "@", ",", ":", ":=", "(", ")", "{", "}",
	"=","<", ">", "+", "-", "*", "/", "<=", ">=", "++", "--", "!=", " ", "fin1"};

Lex Scanner::get_lex ( ) 
{
	enum STATE
	{
		initialState, IDENT, NUMB, COM, ABOVELESSEQUAL, INEQUAL, REAL, UNAR, STRING_CONST, COM1
	};
    STATE CS = initialState;
    string buf, buf_helper;
    int d, j;
    double double_numb;
    do 
    {
    	getChar ();
    	switch(CS) 
    	{
			case initialState:
				if ( currSymb == ' ' || currSymb == '\n' || currSymb == '\r' || currSymb == '\t' );
				else
				if ( isalpha(currSymb)) 
					{
						buf.push_back(currSymb);
						CS = IDENT;
					}
				else
				if ( isdigit (currSymb) ) 
					{
						buf.push_back(currSymb);
						CS = NUMB;
					}
				else
				if ( currSymb == '/' )
					{
						CS = COM;
						buf.push_back(currSymb);
					}
				else
				if ( currSymb == ':' || currSymb == '<' || currSymb == '>') 
				{
					buf.push_back(currSymb);
					CS = ABOVELESSEQUAL; 
				}
				else
				if (currSymb == '"')
				{
					CS = STRING_CONST;
				}
				else
				if ( currSymb == EOF )
				{
					return  Lex (LEX_EOF);
				}
				else
				if ( currSymb == '!' ) 
				{
					buf.push_back(currSymb);
					CS = INEQUAL; 
				}
				else 
				{
					buf.push_back(currSymb);
					if (currSymb == '+')
						{
							getChar();
							if (currSymb == '+')
							{
								buf.push_back(currSymb);
								j = look ( buf, TD);
								// cout << buf << " "<<  j + (int) LEX_BORDERLEXEM_0 << endl;
								return  Lex ( (LexemType) (j + (int) LEX_BORDERLEXEM_0), j + (int) LEX_BORDERLEXEM_0, 0, buf );
							}
							else
							{
								ungetc(currSymb, filePointer);
							}
						}
					if (currSymb == '-')
						{
							getChar();
							if (currSymb == '-')
							{
								buf.push_back(currSymb);
								j = look ( buf, TD);
								// cout << buf << " "<<  j + (int) LEX_BORDERLEXEM_0 << endl;
								return  Lex ( (LexemType) (j + (int) LEX_BORDERLEXEM_0), j + (int) LEX_BORDERLEXEM_0, 0, buf );
							}
							else
							{
								ungetc(currSymb, filePointer);
							}
						}

					if ( (j = look ( buf, TD)) != 21) // 21 - fin1 in TD
					{
						// cout << buf << " "<<  j + (int) LEX_BORDERLEXEM_0 << endl;
						return  Lex ( (LexemType) (j + (int) LEX_BORDERLEXEM_0), j + (int) LEX_BORDERLEXEM_0, 0, buf );  
					}
					else
						throw currSymb;
				}
				break;
			case IDENT:
				//cout << "IDENT" << endl;
				if ( isalpha(currSymb) || isdigit(currSymb) ) 
				{ 
					buf.push_back(currSymb);
				}
				else 
				{
					buf_helper.push_back(currSymb);
					if (currSymb != EOF && currSymb!= '\n' && currSymb != '\t' && currSymb != '\r')
					{
						if ((j = look( buf_helper, AllowedSymbols )) == 0)
						{
							throw "!";
						}
					}
					if (currSymb == ':')
					{
						CS = initialState;
						return Lex (LEX_MARKEDIDENT, (int) LEX_MARKEDIDENT, 0, buf);
					}
					ungetc(currSymb, filePointer);

					if ( (j = look (buf, TW)) != 0 )
					{
						CS = initialState;
						return  Lex ((LexemType) j ,  j , 0, buf);
					}
		         	else 
		         	{
						j = put(buf); 
						CS = initialState;
						// cout << buf << " " << (int) LEX_ID << " " << j << endl;
						return  Lex (LEX_ID, j, 0, buf);
					}
				}
				break;
			case STRING_CONST:
				if (currSymb != '"' && currSymb != EOF)
				{
					buf.push_back(currSymb);
				}
				else if (currSymb == '"')
				{
					CS = initialState;
					return Lex (LEX_CONSTSTRING, 0, 0, buf);
				}
				else
				{
					throw '!';
				}
			break;
			case REAL:
				if (isdigit(currSymb))
				{
					buf.push_back(currSymb);
				}
				else if (currSymb == '.' || isalpha(currSymb) )
				{
					throw "!";
				}
				else
				{
					ungetc(currSymb, filePointer);
					return  Lex ( LEX_CONSTREAL, 0, stof(buf), buf); 
				}
				break;
			case NUMB:
				//cout << buf << endl;
				if ( isdigit (currSymb) ) 
				{ 
					buf.push_back(currSymb);
				}
				else if (currSymb == '.')
				{
					CS = REAL;
					buf.push_back(currSymb);
				}
				else if (isalpha(currSymb))
				{
					throw "!";
				}
				else
				{
					ungetc(currSymb, filePointer);
					// cout << buf << " " << (int) LEX_CONSTINT;
					return  Lex ( LEX_CONSTINT, stoi(buf), 0, buf); 
				}
				break;
			case COM:
				buf.push_back(currSymb);
				if ( currSymb == '*' ) 
				{
					CS = COM1; 
				}
				else
				{
					// cout << buf << " " << (int) LEX_SLASH << endl;
					return	Lex( LEX_SLASH, (int) LEX_SLASH, 0, buf);
				}
				break;

			case COM1:
				buf.push_back(currSymb);
				if (currSymb == '*')
				{
					getChar();
					buf.push_back(currSymb);
					if (currSymb != '/')
					{
						throw "!";
					}
					else
					{
						buf.clear();
						CS = initialState;
					}
				}
				else if (currSymb == '@' || currSymb == EOF)
				{
					throw "!";
				}
				break;
			case ABOVELESSEQUAL:
			//printf("ABOVELESSEQUAL\n");
				if ( currSymb == '=' ) 
				{
				    buf.push_back(currSymb);
					j = look ( buf, TD );
					// cout << buf << " "<< j + (int) LEX_BORDERLEXEM_0 << endl;
					return  Lex ((LexemType) ( j + (int) LEX_BORDERLEXEM_0), j , 0, buf);
				}
				else  
				{
                    ungetc(currSymb, filePointer);    
                    j = look (buf, TD);
                    // cout << buf << " " << j + (int) LEX_BORDERLEXEM_0 << endl;
					return  Lex ((LexemType) ( j + (int) LEX_BORDERLEXEM_0),  j , 0, buf);
				}
				break;
			case INEQUAL:
			//printf("INEQUAL\n");
				if ( currSymb == '=' ) 
				{
			       buf.push_back(currSymb);
			       j = look ( buf, TD );
			       // cout << buf << " "<< j + (int) LEX_BORDERLEXEM_0 << endl;
			       return Lex ( LEX_INEQUAL, j , 0, buf);	 
			   	}
				else  
					throw  '!';
				break;

			default:
				throw '!';
				break;
		}
	}
	while (1);
}







class Parser {

	Lex curr_lex;
	LexemType curr_type;
	int curr_val_int;
	float curr_val_float;
	string curr_str_val;
	Scanner scan;

	void gl()
	{
		curr_lex = scan.get_lex();
		curr_type = curr_lex.get_type();
		curr_val_int = curr_lex.get_value_int();
		curr_val_float = curr_lex.get_value_double();
		curr_str_val = curr_lex.get_string();
		cout << curr_str_val << endl;
	}

	void prog();
	void descriptions_much();
	void description_solo();
	void type();
	void variable();
	void constanta();
	void operators_much();
	void operator_solo();
	void if_operator();
	void while_operator();
	void do_while_operator();
	void read_operator();
	void write_operator();
	void marked_operator();
	void comb_operator();
	void expression();
	void expression_1();
	void expression_2();
	void expression_3();
	void expression_4();
	void expression_5();
	void expression_6();
	void expression_7();
	void expression_8();


public:
	//Poliz prog; // внутреннее представление программы
	//Parser(const char *program) : scan(program), prog(1000) {}
	void analyze(); // анализатор с действиями
};
void Parser::analyze()
{
	gl();
	prog();
	//prog.print();
	cout << endl << "Yes!!!" << endl;
}
void Parser::prog()
{
	if (curr_type == LEX_PROGRAM)
		gl();
	else
		throw curr_lex;
	if (curr_type == LEX_LEFTBRACE)
		gl();
	else
	{
		cout << "PROGRAM PROBLEM" << endl;
		throw curr_lex;
	}
	descriptions_much();

	
	//cout << "After descriptions_much " << endl;
	operators_much();

	cout << "After operators_much " << endl;
	if (curr_type == LEX_RIGHTBRACE)
		gl();
	cout << curr_type << endl;

	if (curr_type != LEX_EOF)
	{
		cout << "EOF PROBLEM" << endl;
		throw curr_lex;
	}
}


//////////////////////////////// DESCRIPTIONS

void Parser::descriptions_much()
{
	cout << "HERE descriptions_much " << endl;
	while (curr_type == LEX_REAL || curr_type == LEX_INT || curr_type == LEX_STRING)
	{
		description_solo();
		//while (curr_type == LEX_COMMA)
		//{
		//	gl();
		//	description_solo();
		//}
		//cout << "After description_solo " << endl;
		if (curr_type == LEX_SEMICOLON)
			gl();
		else
		{
			cout << "DESCRIPTIONS PROBLEM" << endl;
			throw curr_lex;
		}
	}
}
void Parser::description_solo()
{
	//st_int.reset();
	//cout << "HERE descriptions_solo " << endl;
	gl();
	if (curr_type != LEX_ID)
		throw curr_lex;
	else
	{
		while (1)
		{	
			variable();
			//cout << "After variable " << endl;
			if (curr_type == LEX_COMMA)
				gl();
			else
			{
				//cout << "EXIT description_solo " << endl;
				break;
			}
			if (curr_type != LEX_ID)
			{
				cout << "ID PROBLEM" << endl;
				throw curr_lex;
			}
		}
	}
}


void Parser::variable()
{
	//cout << "HERE variable "<< endl;
	gl();
	if (curr_type == LEX_ASSIGN)
	{
		constanta();
	}
	//cout << "Variable exit " << endl;
}	


void Parser::constanta()
{
	//cout << "HERE constanta " << endl;
	gl();
	cout << curr_type << endl;
	if (curr_type == LEX_PLUS || curr_type == LEX_MINUS)
	{
		gl();
		if (curr_type == LEX_CONSTREAL || curr_type == LEX_CONSTINT)
		{
			gl();
		}
		else
		{
			cout << "CONST PROBLEM" << endl;
			throw curr_lex;
		}
	}
	else if (curr_type == LEX_CONSTREAL || curr_type == LEX_CONSTINT || curr_type == LEX_CONSTSTRING)
	{
		gl();
	}
	else
	{
		cout << "CONST PROBLEM" << endl;
		throw curr_lex;
	}
	//cout << "Constanta exit " << endl;
}




void Parser::operators_much()
{
	//cout << "HERE operators_much " << endl;
	while (1)
	{
		if (curr_type == LEX_RIGHTBRACE)
		{
			cout << "EOF " << endl;
			break;
		}
		operator_solo();
	}
	//cout << "EXIT operators_much " << endl;
}

//////////////////////////////// OPERATORS

void Parser::operator_solo()
{
	cout << "HERE operators_solo " << endl;
	cout << curr_type << endl;
	switch (curr_type)
	{
		case LEX_IF: 
			if_operator(); 
			break;
		case LEX_WHILE:
			while_operator();
			break;
		case LEX_READ: 
			cout << "LEX_READ\n";
			read_operator();
			break;
		case LEX_WRITE: 
			write_operator(); 
			break;
		case LEX_DO: 
			do_while_operator();
			break;
		case LEX_LEFTBRACE:
			comb_operator(); 
			break;
		case LEX_MARKEDIDENT:
			gl();
			operator_solo();
			break;
		case LEX_GOTO:
			gl();
			if (curr_type == LEX_ID)
				gl();
			else
			{
				cout << "GOTO PROBLEM" << endl;
				throw curr_lex;
			}
			break;
		default:
		{
			//cout << "HERE default_operator " << endl;
			expression();
			if (curr_type == LEX_SEMICOLON) 
				gl();
			else 
			{
				cout << "OPERATOR PROBLEM " << endl;
				throw curr_lex;
			}
		}
	}
}

void Parser::if_operator()
{
	gl();
	if (curr_type == LEX_LEFTBRACKET) 
		gl();
	else
	{
	 	cout << "IF PROBLEM" << endl;
	 	throw curr_lex;
	}
	expression();

	if (curr_type == LEX_RIGHTBRACKET) 
		gl();
	else 
		{
			cout << "IF PROBLEM" << endl; 
			throw curr_lex;
		}
	operator_solo();
	if (curr_type == LEX_ELSE)
	{
		gl();
		operator_solo();
	}
}
void Parser::while_operator()
{
	gl();
	if (curr_type == LEX_LEFTBRACKET) 
		gl();
	else 
	{
		cout << "WHILE PROBLEM" << endl; 
		throw curr_lex;
	}
	expression();
	
	if (curr_type == LEX_RIGHTBRACKET) 
		gl();
	else 
		{
			cout << "WHILE PROBLEM" << endl; 
			throw curr_lex;
		}
	operator_solo();
}


void Parser::do_while_operator()
{
	gl();
	if (curr_type == LEX_LEFTBRACE)
		gl();
	else
	{
		cout << "DO_WHILE PROBLEM0" << endl;
		throw curr_lex;
	}
	operator_solo();
	if (curr_type == LEX_RIGHTBRACE)
		gl();
	else
	{
		cout << "DO_WHILE PROBLEM1" << endl;
		throw curr_lex;
	}
	if (curr_type == LEX_WHILE)
		gl();
	else
	{
		cout << "DO_WHILE PROBLEM2" << endl;
		throw curr_lex;
	}
	//cout << curr_type << " AAA\n";
	if (curr_type == LEX_LEFTBRACKET)
		gl();
	else
	{
		cout << "DO_WHILE PROBLEM3" << endl;
		throw curr_lex;
	}



	expression();


	if (curr_type == LEX_RIGHTBRACKET)
		gl();
	else
	{
		cout << "DO_WHILE PROBLEM4" << endl;
		throw curr_lex;
	}

}
void Parser::read_operator()
{
	gl();
	if (curr_type == LEX_LEFTBRACKET) 
		gl();
	else 
		{
			cout << "READ PROBLEM" << endl;
			throw curr_lex;
		}
	if (curr_type == LEX_ID) 
		gl();
	else 
		{
			cout << "READ PROBLEM" << endl; 
			throw curr_lex;
		}
	if (curr_type == LEX_RIGHTBRACKET) 
		gl();
	else 
		{
			cout << "READ PROBLEM" << endl;
			throw curr_lex;
		}
	if (curr_type == LEX_SEMICOLON) 
		gl();
	else 
		{
			cout << "READ PROBLEM" << endl; 
			throw curr_lex;
		}
}
void Parser::write_operator()
{ 
	gl();
	if (curr_type == LEX_LEFTBRACKET) 
		gl();
	else 
		{
			cout << "WRITE PROBLEM" << endl;
			throw curr_lex;
		}

	while(1)
	{
		expression();
		if (curr_type != LEX_COMMA) 
			break;
		gl();
	}
	if (curr_type == LEX_RIGHTBRACKET) 
		gl();
	else 
		{
			cout << "WRITE PROBLEM" << endl;
			throw curr_lex;
		}
	if (curr_type == LEX_SEMICOLON) 
		gl();
	else 
		{
			cout << "WRITE PROBLEM" << endl;
			throw curr_lex;
		}
}
void Parser::marked_operator()
{

}
void Parser::comb_operator()
{
	if (curr_type == LEX_LEFTBRACE) 
		gl();
	else 
		{
			cout << "COMB_OPER PROBLEM" << endl;
			throw curr_lex;
		}
	operators_much();
	
	if (curr_type == LEX_RIGHTBRACE) 
		gl();
	else 
		{
			cout << "COMB_OPER PROBLEM" << endl;
			throw curr_lex;
		}
}
void Parser::expression()
{
	expression_8();
	expression_7();
	expression_6();
	expression_5();
	expression_4();
	expression_3();
	expression_2();
	expression_1();
	bool isCurrentTypeSuitable = ((curr_type == LEX_ID) || ( curr_type == LEX_CONSTINT ) ||
	(curr_type == LEX_CONSTREAL) || 
	(curr_type == LEX_CONSTSTRING) || (curr_type == LEX_LEFTBRACKET ) || 
	(curr_type== LEX_NOT));

	if (isCurrentTypeSuitable)
	{
		expression();
		gl();	
	}
}
void Parser::expression_1()
{
	//cout << "expression_1 in" << endl;
	if (curr_type == LEX_ASSIGN)
	{
		gl();
		expression();
		expression_1();	
	}
}
void Parser::expression_2()
{
	//cout << "expression_2 in" << endl;
	if (curr_type == LEX_OR)
	{
		gl();
		expression();
		expression_2();	
	}
}
void Parser::expression_3()
{
	//cout << "expression_3 in" << endl;
	if (curr_type == LEX_AND)
	{
		gl();
		expression();
		expression_3();	
	}
}

void Parser::expression_4()
{
	//cout << "expression_4 in" << endl;
	if ((curr_type == LEX_LESS)||
		(curr_type == LEX_MORE)||
		(curr_type == LEX_MOREEQUAL)
		||(curr_type == LEX_LESSEQUAL)
		||(curr_type == LEX_EQUAL)
		||(curr_type == LEX_INEQUAL))
	{
		gl();
		expression();
		expression_4();	
	}
}

void Parser::expression_5()
{
	//cout << "expression_5 in" << endl;
	if ((curr_type == LEX_PLUS)||(curr_type == LEX_MINUS))
	{
		cout << "expression_5 INSIDE " << endl;
		gl();
		expression();
		expression_5();
	}
}
void Parser::expression_6()
{
	//cout << "expression_6 in" << endl;
	if ((curr_type == LEX_STAR)||(curr_type == LEX_SLASH))
	{
		gl();
		expression();
		expression_6();
	}
}

void Parser::expression_7()
{
	//cout << "expression_7 in" << endl;
	if ((curr_type == LEX_UNARMINUS)||(curr_type == LEX_UNARPLUS))
	{
		gl();
		//expression();
		expression_7();
	}
}


void Parser::expression_8()
{
	//cout << "expression_8 in" << endl;
	if ((curr_type == LEX_CONSTREAL)||(curr_type == LEX_CONSTSTRING)||(curr_type == LEX_CONSTINT)) {}
	else if (curr_type == LEX_LEFTBRACKET)
	{
		gl();
		expression();
		if (curr_type == LEX_RIGHTBRACKET) 
			;
		else 
			{
				cout << "expression_8 PROBLEM" << endl;
				throw curr_lex;
			}
	}
	else if ( (curr_type == LEX_NOT)||(curr_type == LEX_MINUS) )
	{
		gl();
		expression_8();
	}
	else if (curr_type != LEX_ID)
		{
			cout << "expression_8 PROBLEM" << endl; 
			throw curr_lex;
		}
	gl();
}

int main() 
{
	Parser parsim;
	try 
	{
		parsim.analyze();
	}
	catch (...)
	{
		cout << "Problem" << endl;
	}
    return 0; 
}
