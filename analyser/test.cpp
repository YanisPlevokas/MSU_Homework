#include <iostream>
#include <cmath>
#include <vector>
using namespace std;


enum state
	{
		H, IDENT, NUMB, COM, ALE, NEQ, REAL, UNAR, STRING_CONST, COM1
	};


enum lexemType
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

	LEX_FIN, // BORDER_LEXEM 25

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
	LEX_NEQ, //46

	LEX_FIN1, // BORDER_LEXEM1 47
	LEX_EOF, // 48
	LEX_NULL // 49
};

class Lex {
	lexemType lexem;
	int v_lex;
	float real_lex;
	string const_part;
public:
	Lex (lexemType lex = LEX_NULL, int int_part = 0, float real_part = 0, string new_string = "")
	{
		lexem = lex;
		v_lex = int_part;
		real_lex = real_part;
		const_part = new_string;
	}
	lexemType get_type() const
	{
		return lexem;
	}
	int get_value_int() const
	{
		return v_lex;
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

class Ident {
		string name;
		bool declare;
		lexemType type;
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
		lexemType get_type ( ) 
		{
			return  type;
		}
		void put_type ( lexemType t ) 
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
		void put_value (int v) 
		{ 
			value = v;
		}
};

class Scanner 
{
	FILE *fp; 
	char c;	
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
	void gc ( )
	{ 
		c = fgetc ( fp ); 
	}
	public:
        static string TW [], TD [], AllowedSymbols[];
		Scanner () 
		{
			fp = fopen ( "file.txt", "r" ); 
        }
		Lex get_lex();
};

vector <Ident> TID;
int  put (const string & buf) {
	vector <Ident>::iterator k;

	if ( (k = find (TID.begin(), TID.end(), buf)) != TID.end() )
		return (k - TID.begin());
	TID.push_back(buf);  
	return (TID.size() - 1);
}

void common_output()
{
	Scanner asd;
	Lex mannn;
	try
	{
		while (mannn.get_type() != LEX_FIN)
		{
			mannn = asd.get_lex();
			if (mannn.get_type() > LEX_FIN)
			{
				cout << mannn.get_value_int() << " " <<  Scanner::TD[mannn.get_value_int() - 22] << endl;
			}
			else
			{
				if (mannn.get_type() == LEX_CONSTREAL)
				{
					cout << mannn.get_value_double() << ' ' << mannn.get_type() << endl;
				}
				else if (mannn.get_type() == LEX_CONSTINT)
				{
					cout << mannn.get_value_int() << ' ' << mannn.get_type() << endl;
				}
				else if (mannn.get_type() == LEX_CONSTSTRING)
				{
					cout << mannn.get_string() << ' ' << mannn.get_type() << endl;
				}
				else if (mannn.get_type() == LEX_ID)
				{
					cout << mannn.get_value_int() << " " << mannn.get_string() << ' ' << mannn.get_type() <<  endl;
				}
				else if (mannn.get_type() != LEX_ID && mannn.get_type() != LEX_FIN)
				{
					cout << mannn.get_value_int() << " " << Scanner::TW[mannn.get_value_int()] << endl;
				}
				
			}
		}
	}
	catch (...)
	{
		printf("PROBLEM\n");
		exit(-1);
	}
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
	enum state
	{
		H, IDENT, NUMB, COM, ALE, NEQ, REAL, UNAR, STRING_CONST, COM1
	};
    state CS = H;
    string buf, buf_helper;
    int d, j;
    double double_numb;
    do 
    {
    	gc ();
    	switch(CS) 
    	{
			case H:
				if ( c == ' ' || c == '\n' || c == '\r' || c == '\t' );
				else
				if ( isalpha(c)) 
					{
						buf.push_back(c);
						CS = IDENT;
					}
				else
				if ( isdigit (c) ) 
					{
						buf.push_back(c);
						CS = NUMB;
					}
				else
				if ( c == '/' )
					{
						CS = COM;
						buf.push_back(c);
					}
				else
				if ( c == ':' || c == '<' || c == '>') 
				{
					buf.push_back(c);
					CS = ALE; 
				}
				else
				if (c == '"')
				{
					CS = STRING_CONST;
				}
				else
				if ( c == EOF )
				{
					return  Lex (LEX_EOF);
				}
				else
				if ( c == '!' ) 
				{
					buf.push_back(c);
					CS = NEQ; 
				}
				else 
				{
					buf.push_back(c);
					if (c == '+')
						{
							gc();
							if (c == '+')
							{
								buf.push_back(c);
								j = look ( buf, TD);
								// cout << buf << " "<<  j + (int) LEX_FIN << endl;
								return  Lex ( (lexemType) (j + (int) LEX_FIN), j + (int) LEX_FIN, 0, buf );
							}
							else
							{
								ungetc(c, fp);
							}
						}
					if (c == '-')
						{
							gc();
							if (c == '-')
							{
								buf.push_back(c);
								j = look ( buf, TD);
								// cout << buf << " "<<  j + (int) LEX_FIN << endl;
								return  Lex ( (lexemType) (j + (int) LEX_FIN), j + (int) LEX_FIN, 0, buf );
							}
							else
							{
								ungetc(c, fp);
							}
						}

					if ( (j = look ( buf, TD)) != 21) // 21 - fin1 in TD
					{
						// cout << buf << " "<<  j + (int) LEX_FIN << endl;
						return  Lex ( (lexemType) (j + (int) LEX_FIN), j + (int) LEX_FIN, 0, buf );  
					}
					else
						throw c;
				}
				break;
			case IDENT:
				//cout << "IDENT" << endl;
				if ( isalpha(c) || isdigit(c) ) 
				{ 
					buf.push_back(c);
				}
				else 
				{
					buf_helper.push_back(c);
					if (c != EOF && c!= '\n' && c != '\t' && c != '\r')
					{
						if ((j = look( buf_helper, AllowedSymbols )) == 0)
						{
							throw "!";
						}
					}
					ungetc(c, fp);

					if ( (j = look (buf, TW)) != 0 )
					{
						CS = H;
						return  Lex ((lexemType) j ,  j , 0, buf);
					}
		         	else 
		         	{
						j = put(buf); 
						CS = H;
						// cout << buf << " " << (int) LEX_ID << " " << j << endl;
						return  Lex (LEX_ID, j, 0, buf);
					}
				}
				break;
			case STRING_CONST:
				if (c != '"' && c != EOF)
				{
					buf.push_back(c);
				}
				else if (c == '"')
				{
					CS = H;
					return Lex (LEX_CONSTSTRING, 0, 0, buf);
				}
				else
				{
					throw '!';
				}
			break;
			case REAL:
				if (isdigit(c))
				{
					buf.push_back(c);
				}
				else if (c == '.' || isalpha(c) )
				{
					throw "!";
				}
				else
				{
					ungetc(c, fp);
					return  Lex ( LEX_CONSTREAL, 0, stof(buf), buf); 
				}
				break;
			case NUMB:
				//cout << buf << endl;
				if ( isdigit (c) ) 
				{ 
					buf.push_back(c);
				}
				else if (c == '.')
				{
					CS = REAL;
					buf.push_back(c);
				}
				else if (isalpha(c))
				{
					throw "!";
				}
				else
				{
					ungetc(c, fp);
					// cout << buf << " " << (int) LEX_CONSTINT;
					return  Lex ( LEX_CONSTINT, stoi(buf), 0, buf); 
				}
				break;
			case COM:
				buf.push_back(c);
				if ( c == '*' ) 
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
				buf.push_back(c);
				if (c == '*')
				{
					gc();
					buf.push_back(c);
					if (c != '/')
					{
						throw "!";
					}
					else
					{
						buf.clear();
						CS = H;
					}
				}
				else if (c == '@' || c == EOF)
				{
					throw "!";
				}
				break;
			case ALE:
			//printf("ALE\n");
				if ( c == '=' ) 
				{
				    buf.push_back(c);
					j = look ( buf, TD );
					// cout << buf << " "<< j + (int) LEX_FIN << endl;
					return  Lex ((lexemType) ( j + (int) LEX_FIN), j , 0, buf);
				}
				else  
				{
                    ungetc(c, fp);    
                    j = look (buf, TD);
                    // cout << buf << " " << j + (int) LEX_FIN << endl;
					return  Lex ((lexemType) ( j + (int) LEX_FIN),  j , 0, buf);
				}
				break;
			case NEQ:
			//printf("NEQ\n");
				if ( c == '=' ) 
				{
			       buf.push_back(c);
			       j = look ( buf, TD );
			       // cout << buf << " "<< j + (int) LEX_FIN << endl;
			       return Lex ( LEX_NEQ, j , 0, buf);	 
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


