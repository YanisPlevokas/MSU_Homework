#include <iostream>
#include <vector>
#include <algorithm>
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
	LEX_MARKEDIDENTGOTO, // 26
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
struct identificator
{
	string identName;
	int identFlag; // 0 for common ID, 1 for Marked ID, 2 for Marked ID after GOTO
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
};


class Ident  // marked_ident or common_ident
{
		string identName; // name_of_variable
		bool declare;
		bool assign;
		int identValueInt; // value_of_variable
		float identValueFloat;
		int repeat_times; // counter for Marked operators_much
		int identFlag; // 0 for common ID, 1 for Marked ID, 2 for Marked ID after GOTO
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
    string get_name () 
    {
    	return identName; 
    }
    int get_counter()
    {
    	return repeat_times;
    }
    int get_type() // return 0 for common ID, 1 for Marked ID, 2 for Marked ID after GOTO
    {
    	return identFlag;
    }
	bool get_declare () 
	{ 
		return declare;
	}
	void put_declare () 
	{ 
		declare = true;
	}
	bool get_assign () 
	{ 
		return assign;
	}
	void put_assign () 
	{
		assign = true;
	}
	int get_value_int () 
	{ 
		return identValueInt;
	}
	float get_value_float()
	{
		return identValueFloat;
	}
	void put_value (int val) 
	{ 
		identValueInt = val;
	}
	void put_value_float (float val)
	{
		identValueFloat = val;
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
vector <Ident>::iterator findObject(identificator dataPack)
{
	vector <Ident>::iterator position;
	bool dataPackAfterGotoComparement = (dataPack.identFlag == 2); //Тип посланного аргумента равен Marked ID after GOTO
	bool dataPackMarkedOperatorComparement = (dataPack.identFlag == 1); //Тип посланного аргумента равен Marked ID
	bool isSpecialSituation = 0;
	int saved_position = 0;
	for (int i = 0; i < tableOfID.size(); i++)
	{
		bool typeComparement = (tableOfID.at(i).get_type() == dataPack.identFlag); //Равенство типов
		bool nameComparement = (tableOfID.at(i).get_name() == dataPack.identName); //Равенство имен
		bool tableThingAfterGotoComparement = (tableOfID.at(i).get_type() == 2); //Тип элемента таблицы равен Marked ID after GOTO
		bool tableThingMarkedOperatorComparement = (tableOfID.at(i).get_type() == 1); //Тип элемента таблицы равен Marked ID

		if (nameComparement) //  совпали имена
		{
			if (typeComparement) // совпали имена и типы
			{
				if (dataPack.identFlag == 1) // Marked ID
				{
					throw "Marked ID mistake\n";
				}
				else // Common ID or Marked ID after Goto
				{
					return tableOfID.begin() + i;
				}
			}
			else // совпали имена, но типы не совпали
			{
				if ((dataPack.identFlag == 1 && tableThingAfterGotoComparement) ||
					(dataPack.identFlag == 2 && tableThingMarkedOperatorComparement))
				{
					saved_position = i;
				}
				else
				{
					throw "Marked ID mistake\n";
				}
			}
		}
	}
	return tableOfID.end();
}

int  putID(const string & buf, LexemType lex_type) 
{
	identificator idPack;
	idPack.identName = buf;
	switch (lex_type)
	{
		case LEX_ID:
			idPack.identFlag = 0;
			break;
		case LEX_MARKEDIDENT:
			idPack.identFlag = 1;
			break;
		case LEX_MARKEDIDENTGOTO:
			idPack.identFlag = 2;
			break;
		default:
			throw "Put ID problem\n";
	}
	vector <Ident>::iterator k;
	k = findObject(idPack);
	if ( k != tableOfID.end() )
	{
		cout << "already exists\n";
		return (k - tableOfID.begin());
	}
	tableOfID.push_back(idPack);
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
					if (LastLexemType == LEX_GOTO)
					{
						ungetc(currSymb, filePointer);
						numberOfPosition = putID(buf, LEX_MARKEDIDENTGOTO);
						CS = initialState;
						LastLexemType = LEX_MARKEDIDENTGOTO;
						return Lex(LEX_MARKEDIDENTGOTO, numberOfPosition, 0, buf);
					}
					if (currSymb == ':')     //Marked_operator
					{						 //example - A:
						getChar();
						if (currSymb == '=')
						{
							ungetc(currSymb, filePointer);
							ungetc(':', filePointer);
							numberOfPosition = putID(buf, LEX_ID);
							CS = initialState;
							LastLexemType = LEX_ID;
							return Lex(LEX_ID, numberOfPosition, 0, buf);
						}
						numberOfPosition = putID(buf, LEX_MARKEDIDENT);
						CS = initialState;
						LastLexemType = LEX_MARKEDIDENT;
						return Lex(LEX_MARKEDIDENT, numberOfPosition, 0, buf);
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
						numberOfPosition = putID(buf, LEX_ID); // FIX LATER
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


int main()
{
	Lex lexema;
	Scanner hello;
	try
	{
		while (lexema.get_type() != LEX_EOF)
		{
			lexema = hello.get_lex();
			cout << lexema.get_type() << ' ' << lexema.get_string() << ' ' << lexema.get_value_int() <<endl;
		}
	}
	catch (char const * mistake_buf)
	{
		cout << mistake_buf;
		exit(0);
	}


	return 0;
}
