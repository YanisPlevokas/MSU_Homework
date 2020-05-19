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
	LEX_BEGIN, //0
	LEX_AND, //1
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
	LEX_BORDERLEXEM_0, // BORDER_LEXEM 27
	LEX_SEMICOLON, //28
	LEX_DOGSYMB, //29
	LEX_COMMA, //30
	LEX_COLON, //31
	LEX_ASSIGN, //32
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
	int flag;
	float real_lex;
	string const_part;
	int numberOfID; //номер ID для executer
	int flag_help;


public:
	Lex (LexemType lex = LEX_NULL, int int_part = 0, float real_part = 0, string new_string = "", 
		int numberID  = 0, int flag_1 = 0, int flag = 0)
	{
		lexem = lex;
		int_lex = int_part; // for ID position and int value
		real_lex = real_part;
		const_part = new_string;
		if (numberID == 0)  //Когда изначально обозначаем, то int_value = ID_pos
		{
			numberOfID = int_part;
		}
		else //Когда обозначаем в executer, то помещаем в номер айди - позицию в таблице
		{
			numberOfID = numberID;
		}
		flag_help = flag;
	}
	LexemType get_type() const
	{
		return lexem;
	}
	int lastget() // MISTAKE
	{
		return 1;
	}
	void put_value(int position)
	{
		int_lex = position;
	}
	int id_get() const
	{
		return numberOfID;
	}
	int get_value_int() const
	{
		return int_lex;
	}
	string get_string() const
	{
		return const_part;
	}
	float get_value_float() const
	{
		return real_lex;
	}
	int get_last() const
	{
		return flag_help;
	}
};


class Ident  // marked_ident or common_ident
{
		string identName; // name_of_variable
		bool declare;
		bool assign;
		int identValueInt; // value_of_variable
		float identValueFloat; // float_value_of_variable
		string identValueString; // string_value_of_variable
		int position; // counter for Marked operators_much
		int identFlag; // 0 for common ID, 1 for Marked ID, 2 for Marked ID after GOTO
		LexemType ID_Type;
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
		position = -1;
	}
    bool operator== (const string& val) const 
    {
		return identName == val; 
	}
    string get_name () // get name of ID
    {
    	return identName;
    }
    int get_position() // get position for adress in POLIZ
    {
    	return position;
    }
    void put_position(int newPos) // put position for adress in POLIZ
    {
    	position = newPos;
    }
    int get_type() // return 0 for common ID, 1 for Marked ID, 2 for Marked ID after GOTO
    {
    	return identFlag;
    }
    void put_type(LexemType type_new)
    {
    	ID_Type = type_new;
    }
    LexemType get_type_lex()
    {
    	return ID_Type;
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
	int get_value_int () //get intValue of ID
	{ 
		return identValueInt;
	}
	float get_value_float() //get floatValue of ID
	{
		return identValueFloat;
	}
	void put_value (int val) //put intValue of ID
	{ 
		identValueInt = val;
	}
	void put_value_float (float val) //get floatValue of ID
	{
		identValueFloat = val;
	}
	void put_value_string (string val) //put strValue of ID
	{
		identValueString = val;
	}
	string get_value_string()
	{
		return identValueString;
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

int findID(const string & buf, LexemType bufLex, int currPosition = 0)
{
	bool sendParamIsAfterGoto = (bufLex == LEX_MARKEDIDENTGOTO);
	bool sendParamIsMark = (bufLex == LEX_MARKEDIDENT);
	for (int i = 0; i < tableOfID.size(); i++)
	{
		bool nameComparement = (tableOfID.at(i).get_name() == buf); //Равенство имен
		bool tableThingMarkedOperatorComparement = (tableOfID.at(i).get_type() == 1); //Тип элемента таблицы равен Marked ID
		bool tableThingAfterGotoComparement = (tableOfID.at(i).get_type() == 2); //Тип элемента таблицы равен Marked ID after GOTO
		if (nameComparement) // совпали имена
		{
			if (sendParamIsAfterGoto) // Если был послан goto <Name>;
			{
				if (tableThingMarkedOperatorComparement) //Если найден в табличке <Name>:
				{
					return tableOfID.at(i).get_position(); //Вернем позицию <Name>:
				}
			}
			else if (sendParamIsMark) // Если был послан <Name>:
			{
				tableOfID.at(i).put_position(currPosition); // Ставим позицию для <Name>
			}
			else
			{
				throw "Find problem\n";
			}

		}
	}
	return -1;


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
		return (k - tableOfID.begin());
	}
	tableOfID.push_back(idPack);
	return (tableOfID.size() - 1);
}


string Scanner:: TW [] = 
	{"begin","and","do","else","end",
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


template <class T, int max_size> class Stack
{
    T stackWork[max_size];
    int top;
public:
    Stack() 
    { 
    	top = 0;
    }
    void reset() 
    { 
    	top = 0; 
    }
    void push(T i);
    T pop();
	bool three()
	{
		return top >= 3;
	}
    bool is_empty() 
    { 
    	return top == 0; 
    }
    bool is_full() 
    { 
    	return top == max_size; 
    }
};

template <class T, int max_size>

void Stack <T, max_size>::push(T i)
{
    if (!is_full())
    {
        stackWork[top] = i;
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
        return stackWork[top];
    }
    else
        throw "Stack_is_empty";
}


	class LexExecuting {
	int numberid;
	LexemType numlex;
	int ifid;
	int Ilex;
	float Rlex;
	string Slex;
public:
	LexExecuting (LexemType num = LEX_NULL, int nid=0 , int intv = 0, float realv = 0,string stringv = "",int x = 0) {
		numlex = num;
		Ilex = intv;
		Rlex = realv;
		Slex = stringv;
		numberid = nid;
		ifid = x;
	}
	string stringget() {return Slex;}
	LexemType numget () { return numlex; }
    int lastget() {return ifid;}
	int Intget () { return Ilex; }
	int IDget () {return numberid;}
	float Realget() { return Rlex; }

};





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
    void put_lex(Lex lexem)
    {
        lexPointer[free] = lexem;
        ++free;
    };
    int get_free()
    {
    	return free;
    }
    void put_lex(Lex lexem, int place) 
    { 
    	lexPointer[place] = lexem; 
    };
    void blank() 
    { 
    	++free; 
    };
    Lex &operator[](int index)
    {
        if (index > size)
            throw "POLIZ: out of array";
        else if (index > free)
            throw "POLIZ: indefinite element of array";
        else
            return lexPointer[index];
    };
    
    void remake_POLIZ()
    {	
    	int positionPOLIZ;
    	for (int i = 0; i < free; ++i)
        {
			if (lexPointer[i].get_type()== POLIZ_LABEL && lexPointer[i].get_value_int() == -1)
			{
				if ( (positionPOLIZ = findID(lexPointer[i].get_string(), LEX_MARKEDIDENTGOTO)) != -1 )
				{
					lexPointer[i].put_value(positionPOLIZ);
				}
				else
				{
					throw "Not declared mark\n";
				}
			}
		};
    }




	void print()
    {
        for (int i = 0; i < free; ++i)
        {
			if (lexPointer[i].get_type()== LEX_ID)
			{
				cout <<i<<" "<< tableOfID[(lexPointer[i]).get_value_int()].get_name()<<endl;
			}
			else if (lexPointer[i].get_type() == LEX_CONSTINT){
				cout <<i<<" "<< (lexPointer[i]).get_value_int()<<endl;
			}
			else if (lexPointer[i].get_type()== LEX_CONSTREAL){
				cout <<i<<" "<< (lexPointer[i]).get_value_float()<<endl;
			}
			else if (lexPointer[i].get_type()== LEX_CONSTSTRING){
				cout <<i<<" "<< (lexPointer[i]).get_string()<<endl;
			}
			else if (lexPointer[i].get_type()== POLIZ_GO)
			{
				cout <<i<<" "<< "GO"<<endl;
			}
			else if (lexPointer[i].get_type()== POLIZ_LABEL)
			{
				cout <<i<<" "<< ((lexPointer[i]).get_value_int())<<"! "<<endl;
			}
			else if (lexPointer[i].get_type()== POLIZ_FGO)
			{
				cout <<i<<" "<< "FGO"<<endl;
			}
			else if (lexPointer[i].get_type()== POLIZ_ADDRESS)
			{
				cout <<i<<" &"<<tableOfID[(lexPointer[i]).get_value_int()].get_name()<<endl;
			}
			else
            cout <<i<<" "<< T[(lexPointer[i]).get_type()]<<endl;
		};
		cout<<endl;

    };
    
};

string Poliz:: T[ ] = {"begin","and","do","else","end","if","false","int","real","string","not","or","program","step",
    "read","then","true","goto","var","while","write","id","conststring", "constint", "constreal", "markedident",
    "borderlexem0","Sdgvi2", ";", "@", ",", ":", ":=", "(", ")", "{", "}", "=", "<", ">", "+", "-", "*", "/",
	"<=", ">=", "++", "--", "!=", "borderlexem1", "polizlabel", "polizadress", "polizgo", "polizfgo", "eof", "null"};

class Parser
{
	Lex curr_lex; //Current lexem
	LexemType curr_type;
	int curr_val_int;
	float curr_val_float;
	string curr_str_val;
	int curr_id;

	Lex saved_lex; //Saved lexem
	LexemType saved_lex_type;
	int curr_val_int_saved;
	float curr_val_float_saved;
	string curr_str_val_saved;
	int saved_id;

	static int assignmentFlag; //for Assignment

	Scanner scan;



	Stack <int, 100> st_int;
	Stack <LexemType, 100> st_lex;
	Stack <LexemType, 100> helpStack;
	LexemType descripHelp;




	void assignmentHelper()
	{
		saved_lex = curr_lex;
        saved_lex_type = curr_type;
        curr_val_int_saved = curr_val_int;
        curr_val_float_saved = curr_val_float;
        curr_str_val_saved = curr_str_val;
		saved_id = curr_id;
        gl();
        assignmentFlag = 2;
	}
	void assignmentHelperZeroing()
	{
		assignmentFlag = 0;
	}

	void gl()
	{
		if (assignmentFlag != 0)
		{
			assignmentFlag--;
            Lex tempLex = curr_lex;
            curr_lex = saved_lex;
            saved_lex = tempLex;

            LexemType tempLexType = curr_type;
            curr_type = saved_lex_type;
            saved_lex_type = tempLexType;

            int tempLexIntVal = curr_val_int;
            curr_val_int = curr_val_int_saved;
            curr_val_int_saved = tempLexIntVal;

			int tempLexID = curr_id;
            curr_id = saved_id;
            saved_id = tempLexID;

            float tempLexFloatVal = curr_val_float;
            curr_val_float = curr_val_float_saved;
            curr_val_float_saved = tempLexFloatVal;

            string tempLexString = curr_str_val;
            curr_str_val = curr_str_val_saved;
            curr_str_val_saved = tempLexString;
		}
		else
		{
			curr_lex = scan.get_lex();
			curr_id = curr_lex.get_value_int();
			curr_type = curr_lex.get_type();
			curr_val_int = curr_lex.get_value_int();
			curr_val_float = curr_lex.get_value_float();
			curr_str_val = curr_lex.get_string();
			//cout << curr_str_val << endl;
		}
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
	void comb_operator();
	void expression();
	void expression_1();
	void expression_2();
	void expression_3();
	void expression_4();
	void expression_5();
	void expression_6();

	void dec(LexemType type);
	void check_id(int flag);
	void check_op();
	void check_not();
	void eq_type();
	void eq_bool();
	void check_id_in_read();

public:
	Poliz program; // внутреннее представление программы
	//Parser(const char *program) : scan(program), prog(1000) {}
	void analyze(); // анализатор с действиями
};

int Parser::assignmentFlag = 0;


void Parser::dec(LexemType type)
{
	int position;
	while (!st_int.is_empty())
	{
		position = st_int.pop();
		if (tableOfID[position].get_declare())
		{
			throw "Double declarement!\n";
		}
		else
		{
			tableOfID[position].put_declare();
			tableOfID[position].put_type(type);
		}
	}
}

void Parser::check_id(int flag = 0)
{
	if (tableOfID[curr_id].get_declare())
	{
        if (flag == 0)
        	program.put_lex(curr_lex);
	}
	else
		throw "not declared";
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
		throw "Wrong types in assignment";
}


void Parser::eq_bool()
{
	if (helpStack.pop() != LEX_INT)
		throw "Not boolean expression";
}

void Parser::check_id_in_read()
{
	if (!tableOfID[curr_id].get_declare())
		throw "Not declared";
}

void Parser::check_op()
{
	if (helpStack.three()) // more than 3 ops
	{
		LexemType lexemFirst, lexemSecond, lexemOperand;
		LexemType lexemResult = LEX_NULL;

		lexemSecond = helpStack.pop();
		lexemOperand = helpStack.pop();
		lexemFirst = helpStack.pop();

		if ((lexemOperand == LEX_PLUS || lexemOperand == LEX_MINUS || lexemOperand == LEX_STAR || lexemOperand == LEX_SLASH))
            {
                if ((lexemFirst == LEX_INT) && (lexemSecond == LEX_INT)) 
                	lexemResult = LEX_INT;
            }
        if ((lexemOperand == LEX_PLUS || lexemOperand == LEX_MINUS || lexemOperand == LEX_STAR || lexemOperand == LEX_SLASH))
            {
                if ( (lexemFirst == LEX_REAL) && ( lexemSecond == LEX_REAL ) ) 
                	lexemResult = LEX_REAL;
                if ((lexemFirst == LEX_INT) && (lexemSecond == LEX_REAL)) 
                	lexemResult = LEX_REAL;
                if ((lexemFirst == LEX_REAL) && (lexemSecond == LEX_INT)) 
                	lexemResult = LEX_REAL;	
            }
        if (lexemOperand == LEX_PLUS)
        {
            if ((lexemFirst == LEX_STRING) && (lexemSecond == LEX_STRING) ) 
            	lexemResult = LEX_STRING;
        }
            if (lexemOperand == LEX_LESS || lexemOperand == LEX_LESSEQUAL || lexemOperand == LEX_EQUAL 
            	|| lexemOperand == LEX_INEQUAL|| lexemOperand == LEX_MORE|| lexemOperand == LEX_MOREEQUAL)
            {
                if ((lexemFirst == LEX_INT) && (lexemSecond == LEX_INT)) 
                	lexemResult = LEX_INT;
                if ((lexemFirst == LEX_REAL) && (lexemSecond == LEX_REAL)) 
                	lexemResult = LEX_INT;
                if ((lexemFirst == LEX_REAL) && (lexemSecond == LEX_INT)) 
                	lexemResult = LEX_INT;
                if ((lexemFirst == LEX_INT) && (lexemSecond == LEX_REAL)) 
                	lexemResult = LEX_INT; 
            }
            if (lexemOperand == LEX_LESS|| lexemOperand == LEX_EQUAL || lexemOperand == LEX_INEQUAL|| lexemOperand == LEX_MORE)
            {
                if ((lexemFirst == LEX_STRING) && (lexemSecond == LEX_STRING)) 
                	lexemResult = LEX_INT;
            }
            if ( (lexemOperand == LEX_AND) || (lexemOperand == LEX_OR))
            {
                if ((lexemFirst == LEX_INT) && (lexemSecond == LEX_INT)) 
                	lexemResult=LEX_INT;
            }
            if (lexemOperand == LEX_ASSIGN)
            {
                if ((lexemFirst == LEX_INT) && (lexemSecond == LEX_INT)) 
                	lexemResult = LEX_INT;
                if ((lexemFirst == LEX_REAL) && (lexemSecond == LEX_REAL)) 
                	lexemResult = LEX_REAL;
                if ((lexemFirst == LEX_REAL) && (lexemSecond == LEX_INT)) 
                	lexemResult = LEX_REAL;
                if ((lexemFirst == LEX_INT) && (lexemSecond == LEX_REAL)) 
                	lexemResult = LEX_INT;
                if ((lexemFirst == LEX_STRING) && (lexemSecond == LEX_STRING)) 
                	lexemResult = LEX_STRING;
            }
            if (lexemResult == LEX_NULL) 
            	throw "Wrong types";
            helpStack.push(lexemResult);
	}
}


void Parser::analyze()
{
	gl();
	prog();
	cout << endl << "Yes!!!" << endl;
	program.remake_POLIZ();
	program.print();
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
	operators_much();
	if (curr_type == LEX_RIGHTBRACE)
		gl();
	else
	{
		throw "Operators mistake\n";
	}
	if (curr_type != LEX_EOF)
	{
		throw "EOF PROBLEM\n";
	}
}


//////////////////////////////// DESCRIPTIONS

void Parser::descriptions_much()
{
	while (curr_type == LEX_REAL || curr_type == LEX_INT || curr_type == LEX_STRING)
	{
		descripHelp = curr_type;
		st_int.reset();
		description_solo();
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
	gl();
	if (curr_type != LEX_ID)
		throw curr_lex;
	else
	{
		while (1)
		{	
			variable();
			if (curr_type == LEX_COMMA)
				gl();
			else
			{
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
	st_int.push(curr_id);
	dec(descripHelp);
	helpStack.push(tableOfID[curr_id].get_type_lex());
	assignmentHelper();
	if (curr_type == LEX_ASSIGN)
	{
		gl(); // take ID
		program.put_lex(Lex(POLIZ_ADDRESS, curr_id));
		check_id(1);
		gl(); //take Assign
		helpStack.push(curr_type);
		gl();
		if (curr_type == LEX_MINUS || curr_type == LEX_CONSTSTRING || 
			curr_type == LEX_CONSTREAL || curr_type == LEX_CONSTINT)
		{
			constanta();
			check_op();
			program.put_lex(LEX_ASSIGN);
			gl();
		}
		else
		{
			throw "Constanta problem\n";
		}
	}
	assignmentHelperZeroing();
	helpStack.reset();
	//cout << "Variable exit " << endl;
}	


void Parser::constanta()
{
	//cout << "HERE constanta " << endl;
	if (curr_type == LEX_MINUS)
	{
		st_lex.push(curr_type);
		//program.put_lex(LEX_MINUS);
		gl();
		if (curr_type == LEX_CONSTREAL)
		{
			helpStack.push(LEX_REAL);
			program.put_lex(curr_lex);
		}
		if (curr_type == LEX_CONSTINT)
		{
			helpStack.push(LEX_INT);
			program.put_lex(curr_lex);
		}
		else
		{
			throw "Constanta problem\n";
		}
	}
	if (curr_type == LEX_CONSTREAL)
	{
		helpStack.push(LEX_REAL);
		program.put_lex(curr_lex);
	}
	else if (curr_type == LEX_CONSTINT)
	{
		helpStack.push(LEX_INT);
		program.put_lex(curr_lex);
	}
	else if (curr_type == LEX_CONSTSTRING)
	{
		helpStack.push(LEX_STRING);
		program.put_lex(curr_lex);
	}
	else
	{
		throw "Constanta problem\n";
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
			break;
		}
		operator_solo();
		if (curr_type == LEX_RIGHTBRACE)
		{
			break;
		}
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
		case LEX_MARKEDIDENT: // <Name>:
			helpStack.reset();
			findID(curr_str_val, LEX_MARKEDIDENT, program.get_free());
			//Нужно найти лексему с таким именем, а если ее нет, то поставить -1 в эту позицию
			gl();
			operator_solo();
			break;
		case LEX_GOTO:
			gl();
			if (curr_type == LEX_MARKEDIDENTGOTO) // goto <Name>:
				{
					helpStack.reset();
					program.put_lex(Lex(POLIZ_LABEL, findID(curr_str_val, LEX_MARKEDIDENTGOTO), 0, curr_str_val));
					program.put_lex(Lex(POLIZ_GO));
					gl();
					if (curr_type == LEX_SEMICOLON)
					{
						gl();
					}
					else
					{
						throw "GOTO problem\n";
					}
				}
			else
			{
				throw "GOTO PROBLEM\n";
			}
			break;
			
		default:
		{
			expression();
			helpStack.reset();
			if (curr_type == LEX_SEMICOLON)
			{
				program.put_lex(Lex (LEX_SEMICOLON));
				gl();
			}
			else
			{
				throw "Operator problem\n";
			}
		}
	}
}

void Parser::if_operator()
{
	gl();
	int firstPointer, secondPointer;
	if (curr_type == LEX_LEFTBRACKET) 
		gl();
	else
	{
	 	throw "IF PROBLEM\n";
	}
	expression();
	eq_bool();
	helpStack.reset();
	firstPointer = program.get_free();
	program.blank();
	program.put_lex(Lex(POLIZ_FGO));

	if (curr_type == LEX_RIGHTBRACKET) 
		gl();
	else 
		{
			throw "IF PROBLEM\n";
		}
	operator_solo();
	if (curr_type == LEX_ELSE)
	{
		secondPointer = program.get_free();
		program.blank();
		program.put_lex(Lex(POLIZ_GO));
		program.put_lex(Lex(POLIZ_LABEL, program.get_free()), firstPointer);
		gl();
		operator_solo();
		program.put_lex(Lex(POLIZ_LABEL, program.get_free()), secondPointer);
	}
	else
	{
		program.put_lex(Lex(POLIZ_LABEL, program.get_free()), firstPointer);
	}
}
void Parser::while_operator()
{
	gl();
	int firstPointer, secondPointer;
	firstPointer = program.get_free();
	if (curr_type == LEX_LEFTBRACKET) 
		gl();
	else 
	{
		throw "WHILE PROBLEM";
	}
	expression();
	eq_bool();
	helpStack.reset();
	secondPointer = program.get_free();
	program.blank();
	program.put_lex(Lex(POLIZ_FGO));
	if (curr_type == LEX_RIGHTBRACKET) 
		gl();
	else 
		{
			throw "WHILE PROBLEM";
		}
	operator_solo();
	program.put_lex(Lex(POLIZ_LABEL, firstPointer));
	program.put_lex(Lex(POLIZ_GO));
	program.put_lex(Lex(POLIZ_LABEL, program.get_free()), secondPointer);

}


void Parser::do_while_operator()
{
	int firstPointer;
	firstPointer = program.get_free();
	gl();
	operator_solo();

	if (curr_type == LEX_WHILE)
		gl();
	else
	{
		throw "DO_WHILE PROBLEM";
	}
	if (curr_type == LEX_LEFTBRACKET)
		gl();
	else
	{
		throw "DO_WHILE PROBLEM";
	}
	expression();
	eq_bool();
	helpStack.reset();
	program.put_lex(Lex(POLIZ_LABEL, firstPointer));
	program.put_lex(Lex(POLIZ_GO));

	if (curr_type == LEX_RIGHTBRACKET)
		gl();
	else
	{
		throw "DO_WHILE PROBLEM";
	}

}
void Parser::read_operator()
{
	st_lex.push(curr_type);
	gl();
	if (curr_type == LEX_LEFTBRACKET) 
		gl();
	else 
		{
			throw "READ PROBLEM\n";
		}
	if (curr_type == LEX_ID)
	{
		program.put_lex(Lex(POLIZ_ADDRESS, curr_id));
		check_id_in_read();
		gl();
	}
	else 
		{
			throw "READ PROBLEM";
		}
	if (curr_type == LEX_RIGHTBRACKET)
	{
		gl();
		while ( (st_lex.is_empty()) == false)
		{
			program.put_lex(Lex(st_lex.pop()));
		}
	}
	else 
		{
			throw "READ PROBLEM";
		}
	if (curr_type == LEX_SEMICOLON)
	{
		program.put_lex(Lex(LEX_SEMICOLON));
		gl();
	}
	else 
		{
			throw "READ PROBLEM";
		}
}
void Parser::write_operator()
{
	st_lex.push(curr_type);
	gl();
	if (curr_type == LEX_LEFTBRACKET)
		gl();
	else 
		{
			throw "WRITE PROBLEM";
		}

	while(1)
	{
		expression();
		helpStack.reset();
		if (curr_type != LEX_COMMA) 
			break;
		gl();
	}
	if (curr_type == LEX_RIGHTBRACKET)
	{
		gl();
		while( (st_lex.is_empty() == false) )
		{
			program.put_lex(Lex(st_lex.pop()));
		}
	}
	else 
		{
			throw "WRITE PROBLEM";
		}
	if (curr_type == LEX_SEMICOLON) 
	{
		program.put_lex(Lex(LEX_SEMICOLON));
		gl();
	}
	else 
		{
			throw "WRITE PROBLEM";
		}
}

void Parser::comb_operator()
{
	if (curr_type == LEX_LEFTBRACE) 
		gl();
	else 
		{
			throw "COMB_OPER PROBLEM";
		}
	operators_much();
	
	if (curr_type == LEX_RIGHTBRACE) 
		gl();
	else 
		{
			throw "COMB_OPER PROBLEM";
		}
}
void Parser::expression()
{
	LexemType helper;
	if (curr_type == LEX_ID)
	{
		assignmentHelper();
		if (curr_type == LEX_ASSIGN)
		{
			gl(); //ID
			helpStack.push((tableOfID[curr_id]).get_type_lex());
			program.put_lex(Lex(POLIZ_ADDRESS, curr_id));
			check_id(1);
			gl(); //Assign
			helpStack.push(curr_type);
			st_lex.push (curr_type);
			gl(); //Next Lex
			expression();
			while ((st_lex.is_empty())== false)
			{
				helper = st_lex.pop();
				if (helper != LEX_ASSIGN) 
				{
					st_lex.push(helper);
					break;
				}
				program.put_lex(Lex (helper));
			}
            check_op();
		}
		else
		{
			gl();
			expression_1();
			check_op();
		}
	}
	else
	{
		expression_1();
	}

}
void Parser::expression_1()
{
	//cout << "expression_1 in" << endl;
	expression_2();
	int pointer_1, pointer_2, pointer_3, pointer_4;
	while (curr_type == LEX_OR)
	{
		helpStack.push(curr_type);

        pointer_1 = program.get_free();
        program.blank();
        program.put_lex(Lex(POLIZ_FGO));
        program.put_lex(Lex(LEX_CONSTINT, 0, 1));
        pointer_2= program.get_free();
        program.blank();
        program.put_lex(Lex(POLIZ_GO));
        program.put_lex(Lex(POLIZ_LABEL,program.get_free()),pointer_1);
        gl();
        expression_2();
		check_op();
        
        pointer_3=program.get_free();
        program.blank();
        program.put_lex(Lex(POLIZ_FGO));
        program.put_lex(Lex(LEX_CONSTINT, 0, 1));
        pointer_4 = program.get_free();
        program.blank();
        program.put_lex(Lex(POLIZ_GO));
        program.put_lex(Lex(POLIZ_LABEL,program.get_free()),pointer_3);
        
        program.put_lex(Lex(LEX_CONSTINT));
        program.put_lex(Lex(POLIZ_LABEL,program.get_free()),pointer_4);
        program.put_lex(Lex(POLIZ_LABEL,program.get_free()),pointer_2);
	}
}
void Parser::expression_2()
{
	//cout << "expression_2 in" << endl;
	expression_3();
	int pointer_1, pointer_2, pointer_3;
	while (curr_type == LEX_AND)
	{
		helpStack.push(curr_type);

        pointer_1 =program.get_free();
        program.blank();
        program.put_lex(Lex(POLIZ_FGO));
        gl();
        expression_3();
        check_op();
        pointer_2 = program.get_free();
        program.blank();
        program.put_lex(Lex(POLIZ_FGO));
        program.put_lex(Lex(LEX_CONSTINT, 0,1));
        pointer_3 = program.get_free();
        program.blank();
        program.put_lex(Lex(POLIZ_GO));

        program.put_lex(Lex(POLIZ_LABEL,program.get_free()),pointer_2);
        program.put_lex(Lex(POLIZ_LABEL,program.get_free()),pointer_1);
        program.put_lex(Lex(LEX_CONSTINT));
		program.put_lex(Lex(POLIZ_LABEL,program.get_free()),pointer_3);
	}
}

void Parser::expression_3()
{
	//cout << "expression_3 in" << endl;
	expression_4();
	while ((curr_type == LEX_LESS)||
		(curr_type == LEX_MORE)||
		(curr_type == LEX_MOREEQUAL)
		||(curr_type == LEX_LESSEQUAL)
		||(curr_type == LEX_EQUAL)
		||(curr_type == LEX_INEQUAL))
	{
		st_lex.push(curr_type);
		helpStack.push(curr_type);
		gl();
		expression_4();	
		check_op();
		if (st_lex.is_empty())
		{}
		else
		{
			program.put_lex(Lex (st_lex.pop()));
		}
	}
}

void Parser::expression_4()
{
	//cout << "expression_4 in" << endl;
	expression_5();
	while ((curr_type == LEX_PLUS)||(curr_type == LEX_MINUS))
	{
		st_lex.push(curr_type);
		helpStack.push(curr_type);
		gl();
		expression_5();	
		check_op();
		if (st_lex.is_empty())
		{}
		else
		{
			program.put_lex(Lex (st_lex.pop()));
		}
	}
}
void Parser::expression_5()
{
	//cout << "expression_5 in" << endl;
	expression_6();
	while ((curr_type == LEX_STAR)||(curr_type == LEX_SLASH))
	{
		st_lex.push(curr_type);
		helpStack.push(curr_type);
		gl();
		expression_6();	
		check_op();
		if (st_lex.is_empty())
		{}
		else
		{
			program.put_lex(Lex (st_lex.pop()));
		}
	}
}

void Parser::expression_6()
{
	//cout << "expression_6 in" << endl;

	if (curr_type == LEX_CONSTREAL)
	{
		program.put_lex(curr_lex);
		helpStack.push(LEX_REAL);
		gl();
	}
	else if (curr_type == LEX_CONSTINT)
	{
		program.put_lex(curr_lex);
		helpStack.push(LEX_INT);
		gl();
	}
	else if (curr_type == LEX_CONSTSTRING)
	{
		program.put_lex(curr_lex);
		helpStack.push(LEX_STRING);
		gl();
	}
	else if (curr_type == LEX_LEFTBRACKET)
	{
		gl();
		expression_1();
		if (curr_type == LEX_RIGHTBRACKET)
			;
		else 
			{
				throw "expression_6 PROBLEM";
			}
	}
	else if ( (curr_type == LEX_NOT)||(curr_type == LEX_MINUS) || (curr_type == LEX_PLUS) )
	{
		st_lex.push(curr_type);
		gl();
		expression_6();
		check_not();
		if ((st_lex.is_empty()))
		{}
        else
        { 
        	program.put_lex(Lex (st_lex.pop()));
        }
	}
	else if (curr_type == LEX_ID)
		{
			check_id();
			helpStack.push(tableOfID[curr_id].get_type_lex());
			gl();
		}
	else if (curr_type != LEX_ID)
	{
		throw "expression mistake\n";
	}
}


////////////////////////////////////////////////////// EXECUTING


class identExecute {
	string name;
	bool declare;
	LexemType num;
	bool assign;
	int ivalue;
	float rvalue;
	string svalue;
public:
	identExecute () { declare = false; assign = false; }
	identExecute ( const string n ) {
	name = n; declare = false; assign = false; }
	bool operator== (const string& s) const {
		return name == s; 
	}
	void put_name (const string n) { name = n; }
	string get_name ( ) { return name; }
	bool get_declare ( ) { return declare; }
	void put_declare ( ) { declare = true; }
	LexemType numget ( ) { return num; }
	void put_num ( LexemType t ) { 
		num = t;
	}
	void put_val (){
		
	}
	bool get_assign ( ) { return assign; }
	void put_assign ( ) { assign = true; }
    
	int get_ivalue ( ) { return ivalue; }  
	void put_value ( int v ) { ivalue = v; num=LEX_INT; }

	float get_rvalue ( ) { return rvalue; }  
	void put_value ( float v ) { rvalue = v; num=LEX_REAL; }

	string get_svalue ( ) { return svalue; }  
	void put_value ( string v ) { svalue = v; num=LEX_STRING;}
};



vector <identExecute> tableOfIDExecute;


class NewPoliz
{
	LexExecuting *lexPointer;
	int size;
	int free;
public:
    static string T_new[];
    NewPoliz(int max_size=300)
    {
        lexPointer = new LexExecuting[size = max_size];
        free = 0;
    };
    ~NewPoliz() { delete[] lexPointer; };
    int return_free()
    {
    	return free;
    }
    void put_lex(LexExecuting l)
    {
        lexPointer[free] = l;
        ++free;
    };

    void put_lex(LexExecuting l, int place) { lexPointer[place] = l; };
    void blank() { ++free; };
    int get_free() { return free; };
    LexExecuting &operator[](int index)
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
			if (lexPointer[i].numget()== LEX_ID){
				cout <<i<<" "<< tableOfIDExecute[(lexPointer[i]).IDget()].get_name()<<endl;
			}
			else if (lexPointer[i].numget() == LEX_CONSTINT){
				cout <<i<<" "<< (lexPointer[i]).Intget()<<endl;
			}
			else if (lexPointer[i].numget()== LEX_CONSTREAL){
				cout <<i<<" "<< (lexPointer[i]).Realget()<<endl;
			}
			else if (lexPointer[i].numget()== LEX_CONSTSTRING){
				cout <<i<<" "<< (lexPointer[i]).stringget()<<endl;
			}
			else if (lexPointer[i].numget()== POLIZ_GO){
				cout <<i<<" "<< "GO"<<endl;
			}
			else if (lexPointer[i].numget()== POLIZ_LABEL){
				cout <<i<<" "<< ((lexPointer[i]).IDget())<<"! "<<endl;
			}
			else if (lexPointer[i].numget()== POLIZ_FGO){
				cout <<i<<" "<< "FGO"<<endl;
			}
			else if (lexPointer[i].numget()== POLIZ_ADDRESS){
				cout <<i<<" &"<<tableOfIDExecute[(lexPointer[i]).IDget()].get_name()<<endl;
			}
			else
            cout <<i<<" "<< T_new[(lexPointer[i]).numget()]<<endl;
		};
		cout<<endl;

    };
    
};
string NewPoliz:: T_new[ ] = {"begin","and","do","else","end","if","false","int","real","string","not","or","program","step",
    "read","then","true","goto","var","while","write","id","conststring", "constint", "constreal", "markedident",
    "borderlexem0","Sdgvi2", ";", "@", ",", ":", ":=", "(", ")", "{", "}", "=", "<", ">", "+", "-", "*", "/",
	"<=", ">=", "++", "--", "!=", "borderlexem1", "polizlabel", "polizadress", "polizgo", "polizfgo", "eof", "null"};






int put_execute (const string &buf)
{
	vector <identExecute>::iterator k;

	if ( (k = find (tableOfIDExecute.begin(), tableOfIDExecute.end(), buf)) != tableOfIDExecute.end() )
	{
		return (k - tableOfIDExecute.begin());
    }
	tableOfIDExecute.push_back(buf);
	return (tableOfIDExecute.size() - 1);
}



class Executer
{
    LexExecuting lexHelper;

public:
    void execute(Poliz &program);
};
void Executer::execute(Poliz &program)
{   
	NewPoliz PolizExecute;
	//перестроим нашу таблицу идентификаторов, так как переделывать с самого начала слишком сложно
	for (int j = 0; j < tableOfID.size(); j++)
	{
		if (tableOfID.at(j).get_type() == 0)
		{
			tableOfIDExecute.push_back(tableOfID.at(j).get_name());
		}
	}
	for (int j = 0; j < program.get_free(); j++)
	{
		if (program[j].get_type() == LEX_ID)
		{
			PolizExecute.put_lex(LexExecuting(LEX_ID, program[j].get_value_int(), 0, 0,
				program[j].get_string()));
		}
		else
		{
			PolizExecute.put_lex(LexExecuting(program[j].get_type(), program[j].get_value_int(), program[j].get_value_int(), 
				program[j].get_value_float(), program[j].get_string()));
		}
	}


	


    LexExecuting firstLex, secondLex;
    int intVal = 0, flag = 0;
    float floatVal = 0;
    string stringVal = "";
    Stack <LexExecuting, 100> args;
    int i, index = 0, size = program.get_free();
    while (index < size)
    {   
        lexHelper = PolizExecute[index];
        switch (lexHelper.numget())
        {
        case LEX_SEMICOLON:
            args.reset();
            break;
        case LEX_CONSTSTRING:
        case LEX_CONSTREAL:
        case LEX_CONSTINT:
        case POLIZ_ADDRESS:
        case POLIZ_LABEL:
            args.push(lexHelper);
            break;
        case LEX_ID:
            i = PolizExecute[index].IDget();
            if (tableOfIDExecute[i].get_assign())
            {
                if (tableOfIDExecute[i].numget()==LEX_INT){
                    args.push(LexExecuting(LEX_CONSTINT,i,tableOfIDExecute[i].get_ivalue(),0,"",1));
                }
                if (tableOfIDExecute[i].numget()==LEX_REAL){
                    args.push(LexExecuting(LEX_CONSTREAL,i,0,tableOfIDExecute[i].get_rvalue(),"",1));
                }
                if (tableOfIDExecute[i].numget()==LEX_STRING){
                    args.push(LexExecuting(LEX_CONSTSTRING,i,0,0,tableOfIDExecute[i].get_svalue(),1));
                }
                break;
            }
            else
                throw "POLIZ: indefinite identifier1";
            break;
        case LEX_NOT:
            flag=0;
            if (!args.pop().Intget()) flag=1;
            args.push(LexExecuting(LEX_CONSTINT,0,flag));
            break;
        case POLIZ_GO:
            index = args.pop().IDget() - 1;
            break;

        case POLIZ_FGO:
            i = args.pop().IDget();
            if (!args.pop().Intget())
                index = i - 1;
            break;
        case LEX_WRITE:
            firstLex=args.pop();
            if (firstLex.lastget()==0){
                if (firstLex.numget()==LEX_CONSTINT) cout <<">"<< firstLex.Intget() << endl;
                if (firstLex.numget()==LEX_CONSTREAL) cout <<">"<< firstLex.Realget() << endl;
                if (firstLex.numget()==LEX_CONSTSTRING) cout <<">"<< firstLex.stringget() << endl;
            }
            else{
                if (firstLex.numget()==LEX_CONSTINT) cout <<">"<< tableOfIDExecute[firstLex.IDget()].get_ivalue()<<endl; //firstLex.Intget() << endl;
                if (firstLex.numget()==LEX_CONSTREAL) cout <<">"<< tableOfIDExecute[firstLex.IDget()].get_rvalue()<<endl;
                if (firstLex.numget()==LEX_CONSTSTRING) cout <<">"<< tableOfIDExecute[firstLex.IDget()].get_svalue()<<endl;
            }
            break;
        case LEX_READ:
        {
            i = args.pop().IDget();
            if (tableOfIDExecute[i].numget() == LEX_INT)
            {
                cout << "Input int value for ";
                cout << tableOfIDExecute[i].get_name() << endl;
                cin >> intVal;
                tableOfIDExecute[i].put_value(intVal);
            }
            else if (tableOfIDExecute[i].numget() == LEX_REAL)
            {
                cout << "Input real value for ";
                cout << tableOfIDExecute[i].get_name() << endl;
                cin >> floatVal;
                tableOfIDExecute[i].put_value(floatVal);
            }
            else if (tableOfIDExecute[i].numget() == LEX_STRING)
            {
                cout << "Input string value for ";
                cout << tableOfIDExecute[i].get_name() << endl;
                cin >> stringVal;
                tableOfIDExecute[i].put_value(stringVal);
            }
            else throw "ошибка в Read";
            
            tableOfIDExecute[i].put_assign();
            break;
        }
        case LEX_PLUS://firstLex$secondLex
            secondLex = args.pop();
            firstLex = args.pop();
            if (firstLex.numget()==LEX_CONSTSTRING)
                args.push(LexExecuting(LEX_CONSTSTRING,0,0,0,firstLex.stringget()+secondLex.stringget()));
            if ((firstLex.numget()==LEX_CONSTINT)&&(secondLex.numget()==LEX_CONSTINT))
                args.push(LexExecuting(LEX_CONSTINT,0,firstLex.Intget()+secondLex.Intget())); 

            if ((firstLex.numget()==LEX_CONSTINT)&&(secondLex.numget()==LEX_CONSTREAL))
                args.push(LexExecuting(LEX_CONSTREAL,0,0,firstLex.Intget()+secondLex.Realget()));

            if ((firstLex.numget()==LEX_CONSTREAL)&&(secondLex.numget()==LEX_CONSTINT))
                args.push(LexExecuting(LEX_CONSTREAL,0,0,firstLex.Realget()+secondLex.Intget()));

            if ((firstLex.numget()==LEX_CONSTREAL)&&(secondLex.numget()==LEX_CONSTREAL))
                args.push(LexExecuting(LEX_CONSTREAL,0,0,firstLex.Realget()+secondLex.Realget()));   
            break;
        case LEX_STAR:
            secondLex = args.pop();
            firstLex = args.pop();
            if ((firstLex.numget()==LEX_CONSTINT)&&(secondLex.numget()==LEX_CONSTINT))
                args.push(LexExecuting(LEX_CONSTINT,0,firstLex.Intget()*secondLex.Intget())); 

            if ((firstLex.numget()==LEX_CONSTINT)&&(secondLex.numget()==LEX_CONSTREAL))
                args.push(LexExecuting(LEX_CONSTREAL,0,0,firstLex.Intget()*secondLex.Realget()));

            if ((firstLex.numget()==LEX_CONSTREAL)&&(secondLex.numget()==LEX_CONSTINT))
                args.push(LexExecuting(LEX_CONSTREAL,0,0,firstLex.Realget()*secondLex.Intget()));
                
            if ((firstLex.numget()==LEX_CONSTREAL)&&(secondLex.numget()==LEX_CONSTREAL))
                args.push(LexExecuting(LEX_CONSTREAL,0,0,firstLex.Realget()*secondLex.Realget()));   
            break;
        case LEX_MINUS:
            secondLex = args.pop();
            firstLex = args.pop();
            if ((firstLex.numget()!=LEX_CONSTINT)&&(firstLex.numget()!=LEX_CONSTREAL)&&(firstLex.numget()!=LEX_CONSTSTRING)){
                args.push(firstLex);
                args.push(LexExecuting(LEX_CONSTINT,0,-secondLex.Intget()));
            }
            else{
                //cout<<firstLex<<endl;
                if ((firstLex.numget()==LEX_CONSTINT)&&(secondLex.numget()==LEX_CONSTINT))
                    args.push(LexExecuting(LEX_CONSTINT,0,firstLex.Intget()-secondLex.Intget())); 

                if ((firstLex.numget()==LEX_CONSTINT)&&(secondLex.numget()==LEX_CONSTREAL))
                    args.push(LexExecuting(LEX_CONSTREAL,0,0,firstLex.Intget()-secondLex.Realget()));

                if ((firstLex.numget()==LEX_CONSTREAL)&&(secondLex.numget()==LEX_CONSTINT))
                    args.push(LexExecuting(LEX_CONSTREAL,0,0,firstLex.Realget()-secondLex.Intget()));
                    
                if ((firstLex.numget()==LEX_CONSTREAL)&&(secondLex.numget()==LEX_CONSTREAL))
                    args.push(LexExecuting(LEX_CONSTREAL,0,0,firstLex.Realget()-secondLex.Realget()));   
            }
            break;
        case LEX_SLASH:
            secondLex = args.pop();
            firstLex = args.pop();
            if (((secondLex.Intget()==0)&&(secondLex.numget()==LEX_CONSTINT))||((secondLex.Realget()==0.0)&&(secondLex.numget()==LEX_CONSTREAL))) throw "POLIZ:divide by zero";
            else{
                if ((firstLex.numget()==LEX_CONSTINT)&&(secondLex.numget()==LEX_CONSTINT))
                    args.push(LexExecuting(LEX_CONSTINT,0,firstLex.Intget()/secondLex.Intget())); 

                if ((firstLex.numget()==LEX_CONSTINT)&&(secondLex.numget()==LEX_CONSTREAL))
                    args.push(LexExecuting(LEX_CONSTREAL,0,0,firstLex.Intget()/secondLex.Realget()));

                if ((firstLex.numget()==LEX_CONSTREAL)&&(secondLex.numget()==LEX_CONSTINT))
                    args.push(LexExecuting(LEX_CONSTREAL,0,0,firstLex.Realget()/secondLex.Intget()));
                    
                if ((firstLex.numget()==LEX_CONSTREAL)&&(secondLex.numget()==LEX_CONSTREAL))
                    args.push(LexExecuting(LEX_CONSTREAL,0,0,firstLex.Realget()/secondLex.Realget()));   
            break;
            }
        case LEX_EQUAL:
            flag=0;
            firstLex = args.pop();
            secondLex = args.pop();
            if (firstLex.numget()==LEX_CONSTSTRING)
                if(firstLex.stringget() == secondLex.stringget()) flag=1; 
            if ((firstLex.numget()==LEX_CONSTINT)&&(secondLex.numget()==LEX_CONSTINT))
                if (firstLex.Intget() == secondLex.Intget()) flag=1;
            if ((firstLex.numget()==LEX_CONSTINT)&&(secondLex.numget()==LEX_CONSTREAL))
                if (firstLex.Intget() == secondLex.Realget()) flag=1;
            if ((firstLex.numget()==LEX_CONSTREAL)&&(secondLex.numget()==LEX_CONSTINT))
                if (firstLex.Realget() == secondLex.Intget()) flag=1;
            if ((firstLex.numget()==LEX_CONSTREAL)&&(secondLex.numget()==LEX_CONSTREAL))
                if (firstLex.Realget() == secondLex.Realget()) flag=1;
            
            args.push(LexExecuting(LEX_CONSTINT,0,flag));
            break;
        case LEX_MORE:
            flag=0;
            firstLex = args.pop();
            secondLex = args.pop();
            if (firstLex.numget()==LEX_CONSTSTRING)
                if(firstLex.stringget() < secondLex.stringget()) flag=1; 
            if ((firstLex.numget()==LEX_CONSTINT)&&(secondLex.numget()==LEX_CONSTINT))
                if (firstLex.Intget() < secondLex.Intget()) flag=1;
            if ((firstLex.numget()==LEX_CONSTINT)&&(secondLex.numget()==LEX_CONSTREAL))
                if (firstLex.Intget() < secondLex.Realget()) flag=1;
            if ((firstLex.numget()==LEX_CONSTREAL)&&(secondLex.numget()==LEX_CONSTINT))
                if (firstLex.Realget() < secondLex.Intget()) flag=1;
            if ((firstLex.numget()==LEX_CONSTREAL)&&(secondLex.numget()==LEX_CONSTREAL))
                if (firstLex.Realget() < secondLex.Realget()) flag=1;
            
            args.push(LexExecuting(LEX_CONSTINT,0,flag));
            break;
        case LEX_LESS:
            flag=0;
            firstLex = args.pop();
            secondLex = args.pop();
            if (firstLex.numget()==LEX_CONSTSTRING)
                if(firstLex.stringget() > secondLex.stringget()) flag=1; 
            if ((firstLex.numget()==LEX_CONSTINT)&&(secondLex.numget()==LEX_CONSTINT))
                if (firstLex.Intget() > secondLex.Intget()) flag=1;
            if ((firstLex.numget()==LEX_CONSTINT)&&(secondLex.numget()==LEX_CONSTREAL))
                if (firstLex.Intget() > secondLex.Realget()) flag=1;
            if ((firstLex.numget()==LEX_CONSTREAL)&&(secondLex.numget()==LEX_CONSTINT))
                if (firstLex.Realget() > secondLex.Intget()) flag=1;
            if ((firstLex.numget()==LEX_CONSTREAL)&&(secondLex.numget()==LEX_CONSTREAL))
                if (firstLex.Realget() > secondLex.Realget()) flag=1;
            
            args.push(LexExecuting(LEX_CONSTINT,0,flag));
            break;
        case LEX_MOREEQUAL:
            flag=0;
            firstLex = args.pop();
            secondLex = args.pop();
            if ((firstLex.numget()==LEX_CONSTINT)&&(secondLex.numget()==LEX_CONSTINT))
                if (firstLex.Intget() <= secondLex.Intget()) flag=1;
            if ((firstLex.numget()==LEX_CONSTINT)&&(secondLex.numget()==LEX_CONSTREAL))
                if (firstLex.Intget() <= secondLex.Realget()) flag=1;
            if ((firstLex.numget()==LEX_CONSTREAL)&&(secondLex.numget()==LEX_CONSTINT))
                if (firstLex.Realget() <= secondLex.Intget()) flag=1;
            if ((firstLex.numget()==LEX_CONSTREAL)&&(secondLex.numget()==LEX_CONSTREAL))
                if (firstLex.Realget() <= secondLex.Realget()) flag=1;
            
            args.push(LexExecuting(LEX_CONSTINT,0,flag));
            break;
        case LEX_LESSEQUAL:
            flag=0;
            firstLex = args.pop();
            secondLex = args.pop();
            if ((firstLex.numget()==LEX_CONSTINT)&&(secondLex.numget()==LEX_CONSTINT))
                if (firstLex.Intget() >= secondLex.Intget()) flag=1;
            if ((firstLex.numget()==LEX_CONSTINT)&&(secondLex.numget()==LEX_CONSTREAL))
                if (firstLex.Intget() >= secondLex.Realget()) flag=1;
            if ((firstLex.numget()==LEX_CONSTREAL)&&(secondLex.numget()==LEX_CONSTINT))
                if (firstLex.Realget() >= secondLex.Intget()) flag=1;
            if ((firstLex.numget()==LEX_CONSTREAL)&&(secondLex.numget()==LEX_CONSTREAL))
                if (firstLex.Realget() >= secondLex.Realget()) flag=1;
            
            args.push(LexExecuting(LEX_CONSTINT,0,flag));
            break;
        case LEX_INEQUAL:
            flag=0;
            firstLex = args.pop();
            secondLex = args.pop();
            if (firstLex.numget()==LEX_CONSTSTRING)
                if(firstLex.stringget() != secondLex.stringget()) flag=1; 
            if ((firstLex.numget()==LEX_CONSTINT)&&(secondLex.numget()==LEX_CONSTINT))
                if (firstLex.Intget() != secondLex.Intget()) flag=1;
            if ((firstLex.numget()==LEX_CONSTINT)&&(secondLex.numget()==LEX_CONSTREAL))
                if (firstLex.Intget() != secondLex.Realget()) flag=1;
            if ((firstLex.numget()==LEX_CONSTREAL)&&(secondLex.numget()==LEX_CONSTINT))
                if (firstLex.Realget() != secondLex.Intget()) flag=1;
            if ((firstLex.numget()==LEX_CONSTREAL)&&(secondLex.numget()==LEX_CONSTREAL))
                if (firstLex.Realget() != secondLex.Realget()) flag=1;
            
            args.push(LexExecuting(LEX_CONSTINT,0,flag));
            break;
        case LEX_ASSIGN:
            secondLex = args.pop();
            firstLex = args.pop();
            if (tableOfIDExecute[firstLex.IDget()].numget()==LEX_STRING)
                tableOfIDExecute[firstLex.IDget()].put_value(secondLex.stringget()); 

            if ((tableOfIDExecute[firstLex.IDget()].numget()==LEX_INT)&&(secondLex.numget()==LEX_CONSTINT)){
             
                tableOfIDExecute[firstLex.IDget()].put_value(secondLex.Intget());
            }
            if ((tableOfIDExecute[firstLex.IDget()].numget()==LEX_INT)&&(secondLex.numget()==LEX_CONSTREAL)){
                intVal=secondLex.Realget();
                tableOfIDExecute[firstLex.IDget()].put_value(intVal);
            }
            if ((tableOfIDExecute[firstLex.IDget()].numget()==LEX_REAL)&&(secondLex.numget()==LEX_CONSTINT)){
                floatVal=secondLex.Intget();
                tableOfIDExecute[firstLex.IDget()].put_value(floatVal);
            }
            if ((tableOfIDExecute[firstLex.IDget()].numget()==LEX_REAL)&&(secondLex.numget()==LEX_CONSTREAL)){
                tableOfIDExecute[firstLex.IDget()].put_value(secondLex.Realget());
            }
            
            tableOfIDExecute[firstLex.IDget()].put_assign();
            break;
        default:
            throw "POLIZ problem";
        }
        ++index;
    };
    cout << "Finish of executing!!!" << endl;
};


class Interpretator
{
    Parser pars;
    Executer E;

public:
    Interpretator(string program) {};
    void interpretation();
};
void Interpretator::interpretation()
{
    pars.analyze();
    E.execute(pars.program);
}







int main() 
{
	try 
	{
		Interpretator I();
        I.interpretation();
        return 0;;
	}
	catch (const char* buf)
	{
		cout << buf << endl;
	}
	catch (...)
	{
		cout << "Unexpected problem\n";
	}

    return 0; 
}
