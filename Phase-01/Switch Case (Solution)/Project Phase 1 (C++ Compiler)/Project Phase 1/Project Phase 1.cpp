#include <iostream>
#include<fstream>
#include<string.h>
using namespace std;
bool isLetter(char);
bool isDigit(char);
bool isUnderscore(char);
void writeError(int,int,char[]);
void CreateToken(int,int,char[], const char *);
int calculateFileSize();
int main()
{
	int state = 0, start = 0, size = 0, filesize = calculateFileSize();
	char input[1000] = { '\0' };
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
	char keyword[61][50] = {
		{"while"},{"do"},{"for"},{"if"},{"else"},{"cin>>"},{"cout<<"},{"asm"},{"new"},{"this"},
		{"auto"},{"enum"},{"operator"},{"throw"},{"bool"},{"explicit"},{"private"},{"true"},
		{"break"},{"export"},{"protected"},{"try"},{"case"},{"extern"},{"public"},{"typedef"},
		{"catch"},{"false"},{"register"},{"typeid"},{"char"},{"float"},{"typename"},{"class"},
		{"for"},{"return"},{"union"},{"const"},{"friend"},{"short"},{"unsigned"},{"goto"},
		{"signed"},{"using"},{"continue"},{"sizeof"},{"virtual"},{"default"},{"inline"},{"static"},
		{"void"},{"delete"},{"int"},{"volatile"},{"long"},{"struct"},{"double"},{"mutable"},{"switch"},
		{"namespace"},{"template"}
	};
	ifstream fin("source.txt"); 
	if (!fin.is_open())
	{
		cout << "\nFile not opening for reading." << endl;
	}
	else
	{
		while (size<filesize)
		{
			fin.getline(input, 1000);
			start = 0;
			for (int end = 0; end<=strlen(input); end++)
			{
				switch (state)
				{
				case 0:
					if (isLetter(input[end]) || isUnderscore(input[end]))
					{
						state = table[state][0];
						break;
					}
					else if (isDigit(input[end]))
					{
						state = table[state][1];
						break;
					}
					else if (input[end] == '<')
					{
						state = table[state][10];
						break;
					}
					else if (input[end] == '>')
					{
						state = table[state][9];
						break;
					}
					else if (input[end] == '!')
					{
						state = table[state][11];
						break;
					}
					else if (input[end] == ':')
					{
						state = table[state][8];
						break;
					}
					else if (input[end] == '=')
					{
						state = table[state][7];
						break;
					}
					else if (input[end] == '*')
					{
						state = table[state][12];
						break;
					}
					else if (input[end] == '/')
					{
						state = table[state][13];
						break;
					}
					else if (input[end] == '-')
					{
						state = table[state][6];
						break;
					}
					else if (input[end] == '+')
					{
						state = table[state][5];
						break;
					}
					else if (input[end] == '&')
					{
						state = table[state][14];
						break;
					}
					else if (input[end] == '|')
					{
						state = table[state][15];
						break;
					}
					else if (input[end] == '%')
					{
						state = table[state][16];
						break;
					}
					else if (input[end] == '[')
					{
						state = table[state][17];
						break;
					}
					else if (input[end] == ']')
					{
						state = table[state][18];
						break;
					}
					else if (input[end] == '(')
					{
						state = table[state][19];
						break;
					}
					else if (input[end] == ')')
					{
						state = table[state][20];
						break;
					}
					else if (input[end] == '{')
					{
						state = table[state][21];
						break;
					}
					else if (input[end] == '}')
					{
						state = table[state][22];
						break;
					}
					else
					{
						if (start == end)
							end++;
						writeError(start, end, input);
						start = end;
						while (input[start] == ' ')
							start++;
						if (input[end] != ' ')
						{
							end--;
						}
						state = 0;
						break;
					}
				case 1:
					if (isLetter(input[end]))
					{
						state = table[state][0];
						break;
					}
					else if (isUnderscore(input[end]) || isDigit(input[end]))
					{
						state = table[state][1];
						break;
					}
					else
					{
						if (start == end)
							end++;
						char array[1000];
						int index = 0, check = 0;
						for (int i = start; i < end; i++)
						{
							array[index++]=input[i];
						}
						array[index] = '\0';
						for (int i = 0; i < 61; i++)
						{
							if (strcmp(array, keyword[i]) == 0)
							{
								check = 1;
								break;
							}
						}
						if (strcmp(array, "cout") == 0)
						{
							if (input[end] == '<' && input[end+1] == '<')
							{
								check = 1;
								end = end + 2;
							}
						}
						else if (strcmp(array, "cin") == 0)
						{
							if (input[end] == '>' && input[end+1] == '>')
							{
								check = 1;
								end = end + 2;
							}
						}
						if (check == 1)
						{
							CreateToken(start, end, input, "Keyword");
							start = end;
							while (input[start] == ' ')
								start++;
							if (input[end] != ' ')
							{
								end--;
							}
							state = 0;
							break;
						}
						else
						{
							writeError(start, end, input);
							start = end;
							while (input[start] == ' ')
								start++;
							if (input[end] != ' ')
							{
								end--;
							}
							state = 0;
							break;
						}
					}
				case 2:
					if (isLetter(input[end]))
					{
						state = table[state][0];
						break;
					}
					else if (isUnderscore(input[end]) || isDigit(input[end]))
					{
						state = table[state][1];
						break;
					}
					else
					{
						CreateToken(start, end, input, "Identifier");
						start = end;
						while (input[start] == ' ')
							start++;
						if (input[end] != ' ')
						{
							end--;
						}
						state = 0;
						break;
					}
				case 4:
					if (isDigit(input[end]))
					{
						state = table[state][1];
						break;
					}
					else if (input[end] == '.')
					{
						state = table[state][3];
						break;
					}
					else if (input[end] == 'E')
					{
						state = table[state][4];
						break;
					}
					else
					{
						CreateToken(start, end, input, "Number");
						start = end;
						while (input[start] == ' ')
							start++;
						if (input[end] != ' ')
						{
							end--;
						}
						state = 0;
						break;
					}
				case 5:
					if (isDigit(input[end]))
					{
						state = table[state][1];
						break;
					}
					else if (input[end] == '+' || input[end] == '-')
					{
						state = table[state][5];
						break;
					}
					else
					{
						if (start == end)
							end++;
						writeError(start, end, input);
						start = end;
						while (input[start] == ' ')
							start++;
						if (input[end] != ' ')
						{
							end--;
						}
						state = 0;
						break;
					}
				case 6:
					if (isDigit(input[end]))
					{
						state = table[state][1];
						break;
					}
					else
					{
						if (start == end)
							end++;
						writeError(start, end, input);
						start = end;
						while (input[start] == ' ')
							start++;
						if (input[end] != ' ')
						{
							end--;
						}
						state = 0;
						break;
					}
				case 7:
					if (isDigit(input[end]))
					{
						state = table[state][1];
						break;
					}
					else
					{
						CreateToken(start, end, input, "Number");
						start = end;
						while (input[start] == ' ')
							start++;
						if (input[end] != ' ')
						{
							end--;
						}
						state = 0;
						break;
					}
				case 8:
					if (isDigit(input[end]))
					{
						state = table[state][1];
						break;
					}
					else
					{
						if (start == end)
							end++;
						writeError(start, end, input);
						start = end;
						while (input[start] == ' ')
							start++;
						if (input[end] != ' ')
						{
							end--;
						}
						state = 0;
						break;
					}
				case 9:
					if (isDigit(input[end]))
					{
						state = table[state][1];
						break;
					}
					else if (input[end] == 'E')
					{
						state = table[state][4];
						break;
					}
					else
					{
						CreateToken(start, end, input, "Number");
						start = end;
						while (input[start] == ' ')
							start++;
						if (input[end] != ' ')
						{
							end--;
						}
						state = 0;
						break;
					}
				case 10:
					if (isDigit(input[end]))
					{
						state = table[state][1];
						break;
					}
					else if (input[end] == '+' || input[end] == '-')
					{
						state = table[state][5];
						break;
					}
					else
					{
						if (start == end)
							end++;
						writeError(start, end, input);
						start = end;
						while (input[start] == ' ')
							start++;
						if (input[end] != ' ')
						{
							end--;
						}
						state = 0;
						break;
					}
				case 11:
					if (isDigit(input[end]))
					{
						state = table[state][1];
						break;
					}
					else
					{
						if (start == end)
							end++;
						writeError(start, end, input);
						start = end;
						while (input[start] == ' ')
							start++;
						if (input[end] != ' ')
						{
							end--;
						}
						state = 0;
						break;
					}
				case 13:
					if (input[end] == '<')
					{
						CreateToken(start, end + 1, input, "Operator");
						start = end + 1;
						while (input[start] == ' ')
							start++;
						state = 0;
						break;
					}
					else if (input[end] == '>')
					{
						CreateToken(start, end + 1, input, "Operator");
						start = end + 1;
						while (input[start] == ' ')
							start++;
						state = 0;
						break;
					}
					else
					{
						CreateToken(start, end, input, "Operator");
						start = end;
						while (input[start] == ' ')
							start++;
						if (input[end] != ' ')
						{
							end--;
						}
						state = 0;
						break;
					}
				case 17:
					if (input[end] == '>')
					{
						CreateToken(start, end + 1, input, "Operator");
						start = end + 1;
						while (input[start] == ' ')
							start++;
						state = 0;
						break;
					}
					else
					{
						CreateToken(start, end, input, "Operator");
						start = end;
						while (input[start] == ' ')
							start++;
						if (input[end] != ' ')
						{
							end--;
						}
						state = 0;
						break;
					}
				case 20:
					if (input[end] == '=')
					{
						CreateToken(start, end + 1, input, "Operator");
						start = end + 1;
						while (input[start] == ' ')
							start++;
						state = 0;
						break;
					}
					else
					{
						if (start == end)
							end++;
						writeError(start, end, input);
						start = end;
						while (input[start] == ' ')
							start++;
						if (input[end] != ' ')
						{
							end--;
						}
						state = 0;
						break;
					}
				case 22:
					if (input[end] == '=')
					{
						CreateToken(start, end + 1, input, "Operator");
						start = end + 1;
						while (input[start] == ' ')
							start++;
						state = 0;
						break;
					}
					else
					{
						if (start == end)
							end++;
						writeError(start, end, input);
						start = end;
						while (input[start] == ' ')
							start++;
						if (input[end] != ' ')
						{
							end--;
						}
						state = 0;
						break;
					}
				case 24:
					if (input[end] == '=')
					{
						CreateToken(start, end + 1, input, "Operator");
						start = end + 1;
						while (input[start] == ' ')
							start++;
						state = 0;
						break;
					}
					else if (input[end] == '>')
					{
						CreateToken(start, end + 1, input, "Operator");
						start = end + 1;
						while (input[start] == ' ')
							start++;
						state = 0;
						break;
					}
					else if (input[end] == '<')
					{
						CreateToken(start, end + 1, input, "Operator");
						start = end + 1;
						while (input[start] == ' ')
							start++;
						state = 0;
						break;
					}
					else
					{
						if (start == end)
							end++;
						writeError(start, end, input);
						start = end;
						while (input[start] == ' ')
							start++;
						if (input[end] != ' ')
						{
							end--;
						}
						state = 0;
						break;
					}
				case 28:
					CreateToken(start, end, input, "Operator");
					start = end;
					while (input[start] == ' ')
						start++;
					if (input[end] != ' ')
					{
						end--;
					}
					state = 0;
					break;
				case 30:
					CreateToken(start, end, input, "Operator");
					start = end;
					while (input[start] == ' ')
						start++;
					if (input[end] != ' ')
					{
						end--;
					}
					state = 0;
					break;
				case 32:
					if (isDigit(input[end]))
					{
						state = table[state][1];
						break;
					}
					else
					{
						CreateToken(start, end, input, "Operator");
						start = end;
						while (input[start] == ' ')
							start++;
						if (input[end] != ' ')
						{
							end--;
						}
						state = 0;
						break;
					}
				case 34:
					if (isDigit(input[end]))
					{
						state = table[state][1];
						break;
					}
					else if (input[end] == '+')
					{
						CreateToken(start, end + 1, input, "Operator");
						start = end + 1;
						while (input[start] == ' ')
							start++;
						state = 0;
						break;
					}
					else if (input[end] == '=')
					{
						CreateToken(start, end + 1, input, "Operator");
						start = end + 1;
						while (input[start] == ' ')
							start++;
						state = 0;
						break;
					}
					else
					{
						CreateToken(start, end, input, "Operator");
						start = end;
						while (input[start] == ' ')
							start++;
						if (input[end] != ' ')
						{
							end--;
						}
						state = 0;
						break;
					}
				case 38:
					if (input[end] == '&')
					{
						CreateToken(start, end + 1, input, "Operator");
						start = end + 1;
						while (input[start] == ' ')
							start++;
						state = 0;
						break;
					}
					else
					{
						if (start == end)
							end++;
						writeError(start, end, input);
						start = end;
						while (input[start] == ' ')
							start++;
						if (input[end] != ' ')
						{
							end--;
						}
						state = 0;
						break;
					}
				case 40:
					if (input[end] == '|')
					{
						CreateToken(start, end + 1, input, "Operator");
						start = end + 1;
						while (input[start] == ' ')
							start++;
						state = 0;
						break;
					}
					else
					{
						if (start == end)
							end++;
						writeError(start, end, input);
						start = end;
						while (input[start] == ' ')
							start++;
						if (input[end] != ' ')
						{
							end--;
						}
						state = 0;
						break;
					}
				case 42:
					CreateToken(start, end, input, "Operator");
					start = end;
					while (input[start] == ' ')
						start++;
					if (input[end] != ' ')
					{
						end--;
					}
					state = 0;
					break;
				case 44:
					CreateToken(start, end, input, "Punctuation");
					start = end;
					while (input[start] == ' ')
						start++;
					if (input[end] != ' ')
					{
						end--;
					}
					state = 0;
					break;
				case 46:
					CreateToken(start, end, input, "Punctuation");
					start = end;
					while (input[start] == ' ')
						start++;
					if (input[end] != ' ')
					{
						end--;
					}
					state = 0;
					break;
				case 48:
					CreateToken(start, end, input, "Punctuation");
					start = end;
					while (input[start] == ' ')
						start++;
					if (input[end] != ' ')
					{
						end--;
					}
					state = 0;
					break;
				case 50:
					CreateToken(start, end, input, "Punctuation");
					start = end;
					while (input[start] == ' ')
						start++;
					if (input[end] != ' ')
					{
						end--;
					}
					state = 0;
					break;
				case 52:
					CreateToken(start, end, input, "Punctuation");
					start = end;
					while (input[start] == ' ')
						start++;
					if (input[end] != ' ')
					{
						end--;
					}
					state = 0;
					break;
				case 54:
					CreateToken(start, end, input, "Punctuation");
					start = end;
					while (input[start] == ' ')
						start++;
					if (input[end] != ' ')
					{
						end--;
					}
					state = 0;
					break;
				}
			}
			size++;
		}
	}
	return 0;
}

bool isLetter(char input)
{
	if ((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z'))
	{
		return true;
	}
	return false;
}

bool isDigit(char input)
{
	if (input >= '0' && input <= '9')
	{
		return true;
	}
	return false;
}
bool isUnderscore(char input)
{
	if (input =='_')
	{
		return true;
	}
	return false;
}

void writeError(int start, int end, char array[])
{
	ofstream fout("error.txt", ios::app);
	if (!fout.is_open())
	{
		cout << "error.txt file not opening." << endl;
	}
	else
	{
		for (int i = start; i < end; i++)
		{
			if(array[i]!=' ' && array[i]!='\0')
			fout << array[i] << endl;
		}
	}
	fout.close();
	return;
}

void CreateToken(int start,int end, char array[],const char * type)
{
	ofstream fout("token.txt", ios::app);
	if (!fout.is_open())
	{
		cout << "error.txt file not opening." << endl;
	}
	else
	{
		fout << "<";
		for (int i = start; i < end; i++)
		{
			if(array[i]!=' ')
			fout << array[i];
		}
		if (type == NULL)
		{
			fout << ">" << endl;
		}
		else
		{
			fout << "," << type << ">" << endl;
		}
	}
	fout.close();
	return;
}

int calculateFileSize()
{
	char ch[1000] = { '\0' };
	int count=0;
	ifstream fin("source.txt");
	if (!fin.is_open())
	{
		cout << "source.txt file not opening." << endl;
	}
	else
	{
		while (fin.getline(ch,1000))
		{
			count++;
		}
	}
	fin.close();
	return count;
}