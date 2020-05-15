#include <iostream>
#include <vector>
using namespace std;


enum STATE
	{
		initialState, IDENT, NUMB, COM, ABOVELESSEQUAL, INEQUAL, REAL, DOUBLESIGN, STRING_CONST, COM1
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
	LEX_DOUBLESIGNPLUS, //44
	LEX_DOUBLESIGNMINUS, //45
	LEX_INEQUAL, //46
	LEX_BORDERLEXEM_1, // BORDER_LEXEM1 47
	POLIZ_LABEL,
	POLIZ_ADDRESS,
	POLIZ_GO,
	POLIZ_FGO,
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

struct identificator
{
	string identName;
	int identFlag; // 0 for common ID, 1 for marked ID

};

class Ident  // marked_ident or common_ident
{
		string identName; // name_of_variable
		bool declare;
		bool assign;
		int value; // value_of_variable
		float double_value;
		int repeat_times; // counter for Marked operators_much
		int identFlag; // 0 for common ID, 1 for Marked ID
public:
	Ident() 
	{
		declare = false;
		assign = false; 
	}
	Ident(const identificator dataPack) 
	{
		identName = dataPack.identName;
		identFlag = dataPack.identFlag;
		declare = false;
		assign = false;
	}
    bool operator== (const string& s) const 
    {
		return identName == s; 
	}
    string get_name ( ) 
    {
    	return identName; 
    }
    int get_type( )
    {
    	return identFlag;
    }
	bool get_declare ( ) 
	{ 
		return  declare;
	}
	void put_declare ( ) 
	{ 
		declare = true;
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
int  put(const string & buf, LexemType lex_type) 
{
	int idFlag;
	vector <Ident>::iterator k;
	k = find (tableOfID.begin(), tableOfID.end(), buf);
	if ( k != tableOfID.end() )
		return (k - tableOfID.begin());
	if (lex_type == LEX_MARKEDIDENT)
		if
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


LexemType LastLexemType = LEX_EOF;

Lex Scanner::get_lex ( ) 
{
    STATE CS = initialState;
    string buf, buf_helper;
    int numberOfPosition;
    float double_numb;
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
					if ( (numberOfPosition = look ( buf, TD)) != 21) // 21 - fin1 in TD
					{
						// cout << buf << " "<<  numberOfPosition + (int) LEX_BORDERLEXEM_0 << endl;
						LastLexemType = (LexemType) (numberOfPosition + (int) LEX_BORDERLEXEM_0);
						return  Lex ( (LexemType) (numberOfPosition + (int) LEX_BORDERLEXEM_0), numberOfPosition + (int) LEX_BORDERLEXEM_0, 0, buf );  
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
						if ((numberOfPosition = look( buf_helper, AllowedSymbols )) == 0)
						{
							throw "!";
						}
					}
					if (currSymb == ':')     //Marked_operator
					{						 //example - A:
						getChar();
						if (currSymb == '=')
						{
							ungetc(currSymb, filePointer);
							ungetc(':', filePointer);
						}
						cout << "MARKED_OPERATOR\n";
						CS = initialState;
						LastLexemType = LEX_MARKEDIDENT;
						return Lex (LEX_MARKEDIDENT, (int) LEX_MARKEDIDENT, 0, buf);
					}
					ungetc(currSymb, filePointer);

					if ( (numberOfPosition = look (buf, TW)) != 0 ) // serviceWords
					{
						CS = initialState;
						LastLexemType = (LexemType) numberOfPosition;
						return  Lex ((LexemType) numberOfPosition ,  numberOfPosition , 0, buf);
					}
		         	else 
		         	{
						numberOfPosition = put(buf, LEX_ID); // FIX LATER
						CS = initialState;
						// cout << buf << " " << (int) LEX_ID << " " << numberOfPosition << endl;
						LastLexemType = LEX_ID;
						return  Lex (LEX_ID, numberOfPosition, 0, buf);
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
					LastLexemType = LEX_CONSTSTRING;
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
					LastLexemType = LEX_CONSTREAL;
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
					LastLexemType = LEX_CONSTINT;
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
					LastLexemType = LEX_SLASH;
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
					numberOfPosition = look ( buf, TD );
					// cout << buf << " "<< numberOfPosition + (int) LEX_BORDERLEXEM_0 << endl;
					LastLexemType = (LexemType) (numberOfPosition + (int) LEX_BORDERLEXEM_0);
					return  Lex ((LexemType) ( numberOfPosition + (int) LEX_BORDERLEXEM_0), numberOfPosition , 0, buf);
				}
				else  
				{
                    ungetc(currSymb, filePointer);    
                    numberOfPosition = look (buf, TD);
                    // cout << buf << " " << numberOfPosition + (int) LEX_BORDERLEXEM_0 << endl;
                    LastLexemType = (LexemType) (numberOfPosition + (int) LEX_BORDERLEXEM_0);
					return  Lex ((LexemType) ( numberOfPosition + (int) LEX_BORDERLEXEM_0),  numberOfPosition , 0, buf);
				}
				break;
			case INEQUAL:
			//printf("INEQUAL\n");
				if ( currSymb == '=' ) 
				{
			       buf.push_back(currSymb);
			       numberOfPosition = look ( buf, TD );
			       // cout << buf << " "<< numberOfPosition + (int) LEX_BORDERLEXEM_0 << endl;
			       LastLexemType = LEX_INEQUAL;
			       return Lex ( LEX_INEQUAL, numberOfPosition , 0, buf);	 
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


template <class T, int max_size> class Stack
{
    T s[max_size];
    int top;
public:
    Stack() { top = 0; }
    void reset() { top = 0; }
    void push(T i);
    T pop();
	bool three(){return top >= 3;}
    bool is_empty() { return top == 0; }
    bool is_full() { return top == max_size; }
};

template <class T, int max_size>

void Stack <T, max_size>::push(T i)
{
    if (!is_full())
    {
        s[top] = i;
        ++top;
    }
    else
        throw "Stack_is_full";
}
template <class T, int max_size>
T Stack<T, max_size>::pop()
{
    if (!is_empty())
    {
        --top;
        return s[top];
    }
    else
        throw "Stack_is_empty";
}
/*
class Poliz
{
    Lex *lexPointer;
    int size;
    int free;

public:
    static string T[];
    Poliz(int max_size = 150)
    {
        lexPointer = new Lex[size = max_size];
        free = 0;
    };
    ~Poliz() 
    { 
    	delete[] lexPointer; 
    };
    void put_lex(Lex l)
    {
        lexPointer[free] = l;
        ++free;
    };

    void put_lex(Lex l, int place) 
    { 
    	lexPointer[place] = l; 
    };
    void blank() 
    { 
    	++free; 
    };
    int get_free() 
    { 
    	return free; 
    };
    Lex &operator[](int index)
    {
        if (index > size)
            throw "POLIZ:out of array";
        else if (index > free)
            throw "POLIZ:indefinite element of array";
        else
            return lexPointer[index];
    };
	void print()
    {
        for (int i = 0; i < free; ++i){
			if (lexPointer[i].get_type()== LEX_ID){
				cout <<i<<" "<< tableOfID[(lexPointer[i]).get_value_int()].get_name()<<endl;
			}
			else if (lexPointer[i].get_type() == LEX_CONSTINT){
				cout <<i<<" "<< (lexPointer[i]).get_value_int()<<endl;
			}
			else if (lexPointer[i].get_type()== LEX_CONSTREAL){
				cout <<i<<" "<< (lexPointer[i]).get_value_double()<<endl;
			}
			else if (lexPointer[i].get_type()== LEX_CONSTSTRING){
				cout <<i<<" "<< (lexPointer[i]).get_string()<<endl;
			}
			else if (lexPointer[i].get_type()== POLIZ_GO){
				cout <<i<<" "<< "GO"<<endl;
			}
			else if (lexPointer[i].get_type()== POLIZ_LABEL){
				cout <<i<<" "<< ((lexPointer[i]).get_value_int())<<"! "<<endl;
			}
			else if (lexPointer[i].get_type()== POLIZ_FGO){
				cout <<i<<" "<< "FGO"<<endl;
			}
			else if (lexPointer[i].get_type()== POLIZ_ADDRESS){
				cout <<i<<" &"<<tableOfID[(lexPointer[i]).IDget()].get_name()<<endl;
			}
			else
            cout <<i<<" "<< T[(lexPointer[i]).get_type()]<<endl;
		};
		cout<<endl;

    };
};

string Poliz:: T[ ] = {"begin","do","else","end","if","false","int","real","string","not","or","program","step",
    "read","then","true","goto","var","while","write","id","conststring", "constint", "constreal", "markedident",
    "borderlexem0", ";", "@", ",", ":", ":=", "(", ")", "{", "}", "=", "<", ">", "+", "-", "*", "/",
	"<=", ">=", "++", "--", "!=", "borderlexem1", "polizlabel", "polizadress", "polizgo", "polizfgo", "eof", "null"};

*/
class Parser 
{

	Lex curr_lex;
	LexemType curr_type;
	int curr_val_int;
	float curr_val_float;
	string curr_str_val;
	int curr_id;

	Lex saved_lex;
	LexemType saved_lex_type;
	int curr_val_int_saved;
	float curr_val_float_saved;
	string curr_str_val_saved;
	int saved_id;


	Scanner scan;



	Stack <int, 100> st_int;
	Stack <LexemType, 100> st_lex;
	Stack <LexemType, 100> helpStack;
	LexemType descripHelp;





	void gl()
	{
		curr_lex = scan.get_lex();
		curr_type = curr_lex.get_type();
		curr_val_int = curr_lex.get_value_int();
		curr_val_float = curr_lex.get_value_double();
		curr_str_val = curr_lex.get_string();
		cout << curr_str_val << endl;
	}

	void save()
	{
		saved_lex = curr_lex;
		saved_lex_type = curr_type;
		curr_val_int_saved = curr_val_int;
		curr_val_float_saved = curr_val_float;
		curr_str_val_saved = curr_str_val;
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
	void resultType();

	void dec(LexemType type); // semantic
	void check_id(int f);
	void check_op();
	void check_not();
	void eq_type();
	void eq_bool();
	void check_id_in_read();

public:
	//Poliz prog; // внутреннее представление программы
	//Parser(const char *program) : scan(program), prog(1000) {}
	void analyze(); // анализатор с действиями
};


/*
void Parser::dec(lexnum type)
{
	int i;
	while (!st_int.is_empty())
	{
		i = st_int.pop();
		if (tableOfID[i].get_declare())
			throw "twice dec";
		else
		{
			tableOfID[i].put_declare();
			tableOfID[i].put_num(type);
		}
	}
}

void Parser::check_id(int f=0)
{
	if (tableOfID[c_id].get_declare()){
        if (f==0) prog.put_lex(curr_lex);
	}
	else
		throw "not declared";
}

void Parser::check_op()
{	
        if (helpStack.three())
        {
            lexnum t1, t2, op;
            lexnum resultType = LEX_NULL;
            t2 = helpStack.pop();
            op = helpStack.pop();
            t1 = helpStack.pop();
            
            //cout<<t1<<" "<<op<<" "<<t2<<endl;
            if ((op == LEX_PLUS || op == LEX_MINUS || op == LEX_STAR || op == LEX_SLASH|| op == LEX_PERCENT))
            {
                if ((t1==LEX_INT)&&(t2==LEX_INT)) resultType=LEX_INT;
            }
            if ((op == LEX_PLUS || op == LEX_MINUS || op == LEX_STAR || op == LEX_SLASH))
            {
                if ((t1==LEX_REAL)&&(t2==LEX_REAL)) 
                resultType=LEX_REAL;
                if ((t1==LEX_INT)&&(t2==LEX_REAL)) 
                resultType=LEX_REAL;
                if ((t1==LEX_REAL)&&(t2==LEX_INT)) 
                resultType=LEX_REAL;	
            }
            if (op == LEX_PLUS){
                if ((t1==LEX_STRING)&&(t2==LEX_STRING)) resultType=LEX_STRING;
            }
            if (op == LEX_LESS || op == LEX_LESSEQ || op == LEX_EQ || op == LEX_NEQ|| op == LEX_GREATER|| op == LEX_GREATEREQ){
                if ((t1==LEX_INT)&&(t2==LEX_INT)) resultType=LEX_INT;
                if ((t1==LEX_REAL)&&(t2==LEX_REAL)) resultType=LEX_INT;
                if ((t1==LEX_REAL)&&(t2==LEX_INT)) resultType=LEX_INT;
                if ((t1==LEX_INT)&&(t2==LEX_REAL)) resultType=LEX_INT; 
            }
            if (op == LEX_LESS|| op == LEX_EQ || op == LEX_NEQ|| op == LEX_GREATER){
                if ((t1==LEX_STRING)&&(t2==LEX_STRING)) resultType=LEX_INT;
            }
            if (op == LEX_AND|| op == LEX_OR){
                if ((t1==LEX_INT)&&(t2==LEX_INT)) resultType=LEX_INT;
            }
            if (op == LEX_ASSIGN){
                if ((t1==LEX_INT)&&(t2==LEX_INT)) resultType=LEX_INT;
                if ((t1==LEX_REAL)&&(t2==LEX_REAL)) resultType=LEX_REAL;
                if ((t1==LEX_REAL)&&(t2==LEX_INT)) resultType=LEX_REAL;
                if ((t1==LEX_INT)&&(t2==LEX_REAL)) resultType=LEX_INT;
                if ((t1==LEX_STRING)&&(t2==LEX_STRING)) resultType=LEX_STRING;
            }
            if (resultType==LEX_NULL) throw "wrong types are in operation";
            helpStack.push(resultType);
        }
}


void Parser::check_not()
{
	if (helpStack.pop() != LEX_INT)
		throw "wrong type is in not";
	else
	{
		helpStack.push(LEX_INT);
	}
}

void Parser::eq_type()
{
	if (st_lex.pop() != st_lex.pop())
		throw "wrong types are in :=";
}


void Parser::eq_bool()
{
	if (helpStack.pop() != LEX_INT)
		throw "expression is not boolean";
}




void Parser::check_id_in_read()
{
	if (!tableOfID[c_id].get_declare())
		throw "not declared";
}
*/





















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
	cout << "expression\n";
	/*if (curr_type == LEX_ID)
	{
		cout << "expression_first_id\n";
		saved_lex = curr_lex;
		gl();
		if (curr_type == LEX_ASSIGN)
		{
			cout << "expression_lex_assign\n";
			gl();
			expression();
		}
		else
		{
			curr_lex = saved_lex;
		}
	}
	*/
	cout << curr_lex.get_string() << " HERE\n";
	expression_1();


	cout << "after_expression_1\n";
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
	cout << "expression_1 in" << endl;
	expression_2();
	while (curr_type == LEX_OR)
	{
		gl();
		expression_2();	
	}
}
void Parser::expression_2()
{
	cout << "expression_2 in" << endl;
	expression_3();
	while (curr_type == LEX_AND)
	{
		expression_3();
		gl();
	}
}

void Parser::expression_3()
{
	cout << "expression_3 in" << endl;
	expression_4();
	while ((curr_type == LEX_LESS)||
		(curr_type == LEX_MORE)||
		(curr_type == LEX_MOREEQUAL)
		||(curr_type == LEX_LESSEQUAL)
		||(curr_type == LEX_EQUAL)
		||(curr_type == LEX_INEQUAL))
	{
		expression_4();
		gl();
	}
}

void Parser::expression_4()
{
	cout << "expression_4 in" << endl;
	expression_5();
	while ((curr_type == LEX_PLUS)||(curr_type == LEX_MINUS))
	{
		expression_5();
		gl();
	}
}
void Parser::expression_5()
{
	cout << "expression_5 in" << endl;
	expression_6();
	while ((curr_type == LEX_STAR)||(curr_type == LEX_SLASH))
	{
		expression_6();
		gl();
	}
}

void Parser::expression_6()
{
	cout << "expression_6 in" << endl;
	cout << curr_lex.get_string() << " HERE_NEW\n";
	if ((curr_type == LEX_CONSTREAL)||(curr_type == LEX_CONSTSTRING)||(curr_type == LEX_CONSTINT))
	{

	}
	else if (curr_type == LEX_LEFTBRACKET)
	{
		gl();
		expression();
		if (curr_type == LEX_RIGHTBRACKET) 
			;
		else 
			{
				cout << "expression_6 PROBLEM" << endl;
				throw curr_lex;
			}
	}
	else if ( (curr_type == LEX_NOT)||(curr_type == LEX_MINUS) || (curr_type == LEX_PLUS) )
	{
		gl();
		expression_6();
	}
	else if (curr_type != LEX_ID)
		{
			cout << "expression_6 PROBLEM" << endl; 
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
