#include <iostream>
#include<fstream>
#include<string.h>
using namespace std;
#define ID 1
#define NUMBER 2
#define OPERATOR 3
#define PUNCTUATION 4
#define KEYWORD 5
#define SIZE 1000
#define POP -1
#define SKIP -2
void writeError(ofstream &, int, int, char[], int, char[]);
void CreateToken(ofstream &, int, int, char[], int, char[], int);
bool readToken(ifstream &, char[]);
bool CheckVariable(char []);
int VariableIndex(char []);
bool Checktoken(char []);
int tokenindex(char []);
class stack {
private:
	char array[100][100] = { '\0' };
	int top = -1;
public:
	bool isEmpty() 
	{
		if (top == -1)
		{
			return true;
		}
		return false;
	}
	void insert(const char array[])
	{
		strcpy_s(this->array[++top],sizeof this->array[top], array);
		return;
	}
	void pop(char array[])
	{
		if (!this->isEmpty())
		{
			strcpy_s(array,50,this->array[top]);
			strcpy_s(this->array[top--],sizeof this->array[top], "\0");
		}
		return;
	}
};

int main()
{
	//Lexical Code :-
	int table[57][24] = {
		{1,4,1,56,56,34,32,24,22,17,13,20,28,30,38,40,42,44,46,48,50,52,54,56},
		{1,2,2,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56},
		{1,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{12,4,12,8,5,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
		{56,7,56,56,56,6,6,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56},
		{56,7,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56},
		{12,7,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
		{56,9,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56},
		{12,9,12,12,10,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
		{56,7,56,56,56,11,11,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56},
		{56,7,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{14,14,14,14,14,14,14,14,14,16,15,14,14,14,14,14,14,14,14,14,14,14,14,14},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{18,18,18,18,18,18,18,18,18,19,18,18,18,18,18,18,18,18,18,18,18,18,18,18},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{56,56,56,56,56,56,56,21,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{56,56,56,56,56,56,56,23,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{56,56,56,56,56,56,56,25,56,26,27,56,56,56,56,56,56,56,56,56,56,56,56,56},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{33,4,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{35,4,35,35,35,36,35,37,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{56,56,56,56,56,56,56,56,56,56,56,56,56,56,39,56,56,56,56,56,56,56,56,56},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,41,56,56,56,56,56,56,56,56},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};
	int Mapping[256] = { 23,23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23,
		23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 11,
		23,23,23,16,14,23,19,20,12,5,23,6,3,13,1,1,1,1,1,1,1,1,1,1,8,23,10,7,9,23,
		23,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,17,23,18,4,2,23,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,21,15,22,23,23,23,23,
		23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,
		23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,
		23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,
		23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,
		23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23
	};
	int AcceptingState[57] = {
		0,0,0,-1,0,0,0,0,0,0,0,0,-2,0,-3,3,3,0,-3,3,0,3,0,3,0,3,3,3,0,-3,0,-3,0,-3,0,-3,3,3,0,3,0,3,0,-3,
		0,-4,0,-4,0,-4,0,-4,0,-4,0,-4,-5
	};
	char keyword[60][50] = {
		{"loop"},{"do"},{"iff"},{"else"},{"input->"},{"output<-"},{"asm"},{"new"},{"this"},
		{"auto"},{"enum"},{"operator"},{"throw"},{"bool"},{"explicit"},{"private"},{"true"},
		{"break"},{"export"},{"protected"},{"try"},{"case"},{"extern"},{"public"},{"typedef"},
		{"catch"},{"false"},{"register"},{"typeid"},{"char"},{"float"},{"typename"},{"class"},
		{"round"},{"return"},{"union"},{"const"},{"friend"},{"short"},{"unsigned"},{"goto"},
		{"signed"},{"using"},{"continue"},{"sizeof"},{"virtual"},{"default"},{"inline"},{"static"},
		{"void"},{"delete"},{"int"},{"volatile"},{"long"},{"struct"},{"double"},{"mutable"},{"switch"},
		{"namespace"},{"template"}
	};
	int state = 0, start = 0, mid = 0, end = 0, check = 0, check2 = 0, Asize = 0, Bsize = 0;
	char BufferA[SIZE] = { '\0' }, BufferB[SIZE] = { '\0' };
	ofstream foutError("LexicalError.txt", ios::out);
	if (!foutError.is_open())
	{
		cout << "LexicalError.txt file not opening." << endl;
	}
	ofstream foutToken("token.txt", ios::out);
	if (!foutToken.is_open())
	{
		cout << "error.txt file not opening." << endl;
	}
	ifstream fin("source.txt");
	if (!fin.is_open())
	{
		cout << "\nFile not opening for reading." << endl;
	}
	else
	{
		fin.read(BufferA, SIZE - 1);
		Asize = fin.gcount();
		BufferA[Asize] = '\0';
		while (1)
		{
			if (check2 != 1)
			{
				if (!fin.read(BufferB, SIZE - 1))
				{
					Bsize = fin.gcount();
					if (Bsize > 0)
					{
						BufferB[Bsize] = '\0';
						check2 = 1;
					}
					else
					{
						check = 1;
					}
				}
				else
				{
					Bsize = fin.gcount();
					BufferB[Bsize] = '\0';
					check2 = 1;
				}
			}
			while (!(AcceptingState[state]) && BufferA[end] != '\0' &&end < Asize + 1)
			{
				state = table[state][Mapping[BufferA[end]]];
				if (!(AcceptingState[state]))
				{
					end++;
				}
			}
			if (check == 1 && BufferA[end] == '\0')
			{
				state = table[state][Mapping[BufferA[end]]];
			}
			if (check == 0)
			{
				while (!(AcceptingState[state]) && mid < Bsize + 1)
				{
					state = table[state][Mapping[BufferB[mid]]];
					if (!(AcceptingState[state]))
					{
						mid++;
					}
				}
			}
			if (state == 56)
			{
				if (start == end)
					end++;
				char array[SIZE];
				int index = 0, check = 0;
				for (int i = start; i < end; i++)
				{
					array[index++] = BufferA[i];
				}
				for (int i = 0; i < mid; i++)
				{
					array[index++] = BufferB[i];
				}
				array[index] = '\0';
				for (int i = 0; i < 60; i++)
				{
					if (strcmp(array, keyword[i]) == 0)
					{
						check = 1;
						break;
					}
				}
				if (strcmp(array, "output") == 0)
				{
					while (BufferA[end] == ' ')
						end++;
					if (mid == 0 && end <= (Asize)-2)
					{
						if (BufferA[end] == '<' && BufferA[end + 1] == '-')
						{
							check = 1;
							end = end + 2;
						}
					}
					else
					{
						if (BufferA[end] == '\0')
						{
							while (BufferB[mid] == ' ')
								mid++;
							if (BufferB[mid] == '<' && BufferB[mid + 1] == '-')
							{
								check = 1;
								mid = mid + 2;
							}
						}
						else
						{
							if (BufferA[end] == '<' && BufferB[mid] == '-')
							{
								check = 1;
								end++;
								mid = mid + 1;
							}
						}
					}
				}
				else if (strcmp(array, "input") == 0)
				{
					while (BufferA[end] == ' ')
						end++;
					if (mid == 0 && end <= (Asize)-2)
					{
						if (BufferA[end] == '-' && BufferA[end + 1] == '>')
						{
							check = 1;
							end = end + 2;
						}
					}
					else
					{
						if (BufferA[end] == '\0')
						{
							while (BufferB[mid] == ' ')
								mid++;
							if (BufferB[mid] == '-' && BufferB[mid + 1] == '>')
							{
								check = 1;
								mid = mid + 2;
							}
						}
						else
						{
							if (BufferA[end] == '-' && BufferB[mid] == '>')
							{
								check = 1;
								end++;
								mid = mid + 1;
							}
						}
					}
				}
				if (check == 1)
				{
					CreateToken(foutToken, start, end, BufferA, mid, BufferB, abs(AcceptingState[state]));
					start = end;
					if (mid > 0)
					{
						if (BufferB[mid] == '\0')
						{
							break;
						}
					}
					else
					{
						if (BufferA[end] == '\0' && check2 == 0)
						{
							break;
						}
					}
					state = 0;
				}
				else
				{
					writeError(foutError, start, end, BufferA, mid, BufferB);
					start = end;
					if (mid > 0)
					{
						if (BufferB[mid] == '\0')
						{
							break;
						}
					}
					else
					{
						if (BufferA[end] == '\0' && check2 == 0)
						{
							break;
						}
					}
				}
				state = 0;
			}
			else if (AcceptingState[state] < 0)
			{
				CreateToken(foutToken, start, end, BufferA, mid, BufferB, abs(AcceptingState[state]));
				start = end;
				if (mid > 0)
				{
					if (BufferB[mid] == '\0')
					{
						break;
					}
				}
				else
				{
					if (BufferA[end] == '\0' && check2 == 0)
					{
						break;
					}
				}
				state = 0;
			}
			else
			{
				if (mid > 0)
				{
					if (BufferB[mid] != '\0')
					{
						mid++;
					}
				}
				else
				{
					if (BufferA[end] != '\0')
					{
						end++;
					}
				}
				if (BufferA[end - 1] == BufferB[mid] && BufferA[end] == '\0')
				{
					mid++;
				}
				CreateToken(foutToken, start, end, BufferA, mid, BufferB, abs(AcceptingState[state]));
				start = end;
				if (mid > 0)
				{
					if (BufferB[mid] == '\0')
					{
						break;
					}
				}
				else
				{
					if (BufferA[end] == '\0' && check2 == 0)
					{
						break;
					}
				}
				state = 0;
			}
			if (mid > 0 || BufferA[end] == '\0')
			{
				if (mid == 0 && BufferA[end] == '\0' && check == 1)
				{
					break;
				}
				if (mid > 0)
				{
					check = 0;
				}
				end = 0;
				int index = 0;
				for (int i = mid; i < (Bsize + 1) - 1; i++)
				{
					BufferA[index++] = BufferB[i];
				}
				BufferA[index] = '\0';
				Asize = index;
				mid = 0;
				start = 0;
				check2 = 0;
			}
			else
			{
				check = 0;
				if (Bsize != 0)
				{
					check2 = 1;
				}
			}
		}
	}
	foutError.close();
	foutToken.close();
	cout << "\n Lexical Analyzation is Complete! \n" << endl;
	cout << " Please view tokens in token.txt File \n" << endl;
	cout << " please view errors in LexicalError.txt File \n" << endl;
	cout << "____________________________________________________\n" << endl;
	// Parser Code :-
	char Grammar[11][10][100] = { 
		{"Mag`","Term","$"},
		{"Mag`","Term","+","$"},
		{"Mag`","Term","-","$"},
		{"^","$"},
		{"Term`","Factor","$"},
		{"Term`","Factor","*","$"},
		{"Term`","Factor","/","$"},
		{"^","$"},
		{")","Mag","(","$"},
		{"identifier","$"},
		{"number","$"}
	};
	int LL1_Table[5][9] = {
		{0,0,SKIP,SKIP,SKIP,SKIP,0,POP,POP},
		{SKIP,SKIP,1,2,SKIP,SKIP,SKIP,3,3},
		{4,4,POP,POP,SKIP,SKIP,4,POP,POP},
		{SKIP,SKIP,7,7,5,6,SKIP,7,7},
		{9,10,POP,POP,POP,POP,8,POP,POP}
	};
	stack Stack;
	Stack.insert("Mag");
	ifstream fintoken("token.txt", ios::in);
	foutError.open("ParserError.txt", ios::out);
	char token[50] = { '\0' };
	char popString[50] = { '\0' };
	bool checkinput = true;
	int errors = 0;
	while (true)
	{
		if (checkinput == true)
		{
			if (readToken(fintoken, token) == false)
			{
				break;
			}
		}
		if (Stack.isEmpty() == false )
		{
			Stack.pop(popString);
			if (CheckVariable(popString) == true)
			{
				int index = VariableIndex(popString);
				if (Checktoken(token) == true)
				{
					int production = LL1_Table[index][tokenindex(token)];
					if (production == POP)
					{
						checkinput = false;
						if (Stack.isEmpty())
						{
							Stack.insert(popString);
							foutError << token << " is a syntax error." << endl;
							checkinput = true;
							errors++;
						}
					}
					else if (production == SKIP)
					{
						Stack.insert(popString);
						foutError << token << " is a syntax error." << endl;
						errors++;
						checkinput = true;
					}
					else
					{
						for (int i = 0; strcmp(Grammar[production][i], "$") != 0; i++)
						{
							Stack.insert(Grammar[production][i]);
						}
						checkinput = false;
					}
				}
				else
				{
					foutError << token << " is a syntax error." << endl;
					Stack.insert(popString);
					checkinput = true;
					errors++;
				}
			}
			else if (Checktoken(popString) == true)
			{
				if (strcmp(token, popString) == 0)
				{
					cout << token << " and " << popString << " Matched!" << endl;
				}
				else
				{
					cout << token << " and " << popString << " Not Matched!" << endl;
				}
				checkinput = true;
			}
			else if (strcmp(popString, "^") == 0)
			{
				checkinput = false;
			}
			else
			{
				foutError << token << " is a syntax error." << endl;
				Stack.insert(popString);
				checkinput = true;
				errors++;
			}
		}
		else
		{
			foutError << token << " is a syntax error." << endl;
			Stack.insert("Mag");
			checkinput = true;
			errors++;
		}
	}
	foutError << "Total Errors : " << errors << endl;
	fintoken.close();
	foutError.close();
	cout << "\n\n Syntax Analyzation is Complete! \n" << endl;
	cout << " please view errors in ParserError.txt File \n" << endl;
	cout << "_______________________________________________\n" << endl;
	return 0;
}

void writeError(ofstream & fout, int start, int end, char BufferA[], int mid, char BufferB[])
{
	for (int i = start; i < end; i++)
	{
		if (BufferA[i] != ' ' && BufferA[i] != '\0' && BufferA[i] != '\n'&&BufferA[i] != '\t')
			fout << BufferA[i] << endl;
	}
	for (int i = 0; i < mid; i++)
	{
		if (BufferB[i] != ' ' && BufferB[i] != '\0'&& BufferB[i] != '\n'&&BufferB[i] != '\t')
			fout << BufferB[i] << endl;
	}
	return;
}

void CreateToken(ofstream & fout, int start, int end, char BufferA[], int mid, char BufferB[], int type)
{
	fout << "< ";
	for (int i = start; i < end; i++)
	{
		if (BufferA[i] != ' '&&BufferA[i] != '\n'&&BufferA[i] != '\0'&&BufferA[i] != '\t')
			fout << BufferA[i];
	}
	for (int i = 0; i < mid; i++)
	{
		if (BufferB[i] != ' '&&BufferB[i] != '\n'&&BufferB[i] != '\0'&&BufferB[i] != '\t')
			fout << BufferB[i];
	}
	if (type == NULL)
	{
		fout << " >" << endl;
	}
	else if (type == ID)
	{
		fout << " , identifier >" << endl;
	}
	else if (type == NUMBER)
	{
		fout << " , number >" << endl;
	}
	else if (type == OPERATOR)
	{
		fout << " , ";
		for (int i = start; i < end; i++)
		{
			if (BufferA[i] != ' '&&BufferA[i] != '\n'&&BufferA[i] != '\0'&&BufferA[i] != '\t')
				fout << BufferA[i];
		}
		for (int i = 0; i < mid; i++)
		{
			if (BufferB[i] != ' '&&BufferB[i] != '\n'&&BufferB[i] != '\0'&&BufferB[i] != '\t')
				fout << BufferB[i];
		}
		fout << " >" << endl;
	}
	else if (type == PUNCTUATION)
	{
		fout << " , ";
		for (int i = start; i < end; i++)
		{
			if (BufferA[i] != ' '&&BufferA[i] != '\n'&&BufferA[i] != '\0'&&BufferA[i] != '\t')
				fout << BufferA[i];
		}
		for (int i = 0; i < mid; i++)
		{
			if (BufferB[i] != ' '&&BufferB[i] != '\n'&&BufferB[i] != '\0'&&BufferB[i] != '\t')
				fout << BufferB[i];
		}
		fout << " >" << endl;
	}
	else if (type == KEYWORD)
	{
		fout << " , ";
		for (int i = start; i < end; i++)
		{
			if (BufferA[i] != ' '&&BufferA[i] != '\n'&&BufferA[i] != '\0'&&BufferA[i] != '\t')
				fout << BufferA[i];
		}
		for (int i = 0; i < mid; i++)
		{
			if (BufferB[i] != ' '&&BufferB[i] != '\n'&&BufferB[i] != '\0'&&BufferB[i] != '\t')
				fout << BufferB[i];
		}
		fout << " >" << endl;
	}
	return;
}

bool readToken(ifstream & fin, char array[])
{
	int check = 0;
	char temp[50] = { '\0' };
	for (int i = 0; i < 4; i++)
	{
		if (fin >> array)
		{
			check++;
		}
	}
	if (check > 0)
	{
		fin >> temp;
		return true;
	}
	else
	{
		return false;
	}
}

bool CheckVariable(char array[])
{
	if (strcmp(array, "Mag") == 0)
		return true;
	else if (strcmp(array, "Mag`") == 0)
		return true;
	else if (strcmp(array, "Term") == 0)
		return true;
	else if (strcmp(array, "Term`") == 0)
		return true;
	else if (strcmp(array, "Factor") == 0)
		return true;
	else
		return false;
}

int VariableIndex(char array[])
{
	if (strcmp(array, "Mag") == 0)
		return 0;
	else if (strcmp(array, "Mag`") == 0)
		return 1;
	else if (strcmp(array, "Term") == 0)
		return 2;
	else if (strcmp(array, "Term`") == 0)
		return 3;
	else if (strcmp(array, "Factor") == 0)
		return 4;
	else
		return -1;
}

bool Checktoken(char array[])
{
	if (strcmp(array, "identifier") == 0)
		return true;
	else if (strcmp(array, "number") == 0)
		return true;
	else if (strcmp(array, "+") == 0)
		return true;
	else if (strcmp(array, "-") == 0)
		return true;
	else if (strcmp(array, "*") == 0)
		return true;
	else if (strcmp(array, "/") == 0)
		return true;
	else if (strcmp(array, "(") == 0)
		return true;
	else if (strcmp(array, ")") == 0)
		return true;
	else
		return false;
}

int tokenindex(char array[])
{
	if (strcmp(array, "identifier") == 0)
		return 0;
	else if (strcmp(array, "number") == 0)
		return 1;
	else if (strcmp(array, "+") == 0)
		return 2;
	else if (strcmp(array, "-") == 0)
		return 3;
	else if (strcmp(array, "*") == 0)
		return 4;
	else if (strcmp(array, "/") == 0)
		return 5;
	else if (strcmp(array, "(") == 0)
		return 6;
	else if (strcmp(array, ")") == 0)
		return 7;
	else
		return -1;
}