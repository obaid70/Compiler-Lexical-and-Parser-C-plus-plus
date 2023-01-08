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
void writeError(ofstream &, int, int, char[], int, char[]);
void CreateToken(ofstream &,int,int,char[],int,char[],int);
int main()
{
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
	int Mapping[256] = {23,23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23,
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
		{"while"},{"do"},{"if"},{"else"},{"cin>>"},{"cout<<"},{"asm"},{"new"},{"this"},
		{"auto"},{"enum"},{"operator"},{"throw"},{"bool"},{"explicit"},{"private"},{"true"},
		{"break"},{"export"},{"protected"},{"try"},{"case"},{"extern"},{"public"},{"typedef"},
		{"catch"},{"false"},{"register"},{"typeid"},{"char"},{"float"},{"typename"},{"class"},
		{"for"},{"return"},{"union"},{"const"},{"friend"},{"short"},{"unsigned"},{"goto"},
		{"signed"},{"using"},{"continue"},{"sizeof"},{"virtual"},{"default"},{"inline"},{"static"},
		{"void"},{"delete"},{"int"},{"volatile"},{"long"},{"struct"},{"double"},{"mutable"},{"switch"},
		{"namespace"},{"template"}
	};
	int state = 0, start = 0, mid = 0, end = 0, check = 0, check2 = 0, Asize = 0, Bsize = 0;
	char BufferA[SIZE] = { '\0' }, BufferB[SIZE] = { '\0' };
	ofstream foutError("error.txt", ios::out);
	if (!foutError.is_open())
	{
		cout << "error.txt file not opening." << endl;
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
		fin.read(BufferA, SIZE-1);
		Asize = fin.gcount();
		BufferA[Asize] = '\0';
		while (1)
		{
			if (check2 != 1)
			{
				if (!fin.read(BufferB, SIZE-1))
				{
					Bsize = fin.gcount();
					if (Bsize>0)
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
			while (!(AcceptingState[state]) && BufferA[end] != '\0' &&end < Asize+1)
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
				while (!(AcceptingState[state]) && mid < Bsize+1)
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
				if (strcmp(array, "cout") == 0)
				{
					while (BufferA[end] == ' ')
						end++;
					if (mid == 0 && end<=(Asize)-2)
					{
						if (BufferA[end] == '<' && BufferA[end + 1] == '<')
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
							if (BufferB[mid] == '<' && BufferB[mid + 1] == '<')
							{
								check = 1;
								mid = mid + 2;
							}
						}
						else
						{
							if (BufferA[end] == '<' && BufferB[mid] == '<')
							{
								check = 1;
								end++;
								mid = mid + 1;
							}
						}
					}
				}
				else if (strcmp(array, "cin") == 0)
				{
					while (BufferA[end] == ' ')
						end++;
					if (mid == 0 && end <= (Asize)-2)
					{
						if (BufferA[end] == '>' && BufferA[end + 1] == '>')
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
							if (BufferB[mid] == '>' && BufferB[mid + 1] == '>')
							{
								check = 1;
								mid = mid + 2;
							}
						}
						else
						{
							if (BufferA[end] == '>' && BufferB[mid] == '>')
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
					CreateToken(foutToken,start, end, BufferA,mid,BufferB, abs(AcceptingState[state]));
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
						if (BufferA[end] == '\0' && check2==0)
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
						if (BufferA[end] == '\0' && check2==0)
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
					if (BufferA[end] == '\0' && check2==0)
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
				if (BufferA[end-1] == BufferB[mid] && BufferA[end]=='\0')
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
					if (BufferA[end] == '\0' && check2==0)
					{
						break;
					}
				}
				state = 0;
			}
			if (mid > 0 || BufferA[end]=='\0')
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
				for (int i=mid; i < (Bsize+1)-1; i++)
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
	cout << " please view errors in error.txt File \n" << endl;
	return 0;
}

void writeError(ofstream & fout, int start, int end, char BufferA[], int mid, char BufferB[])
{
	for (int i = start; i < end; i++)
	{
		if (BufferA[i] != ' ' && BufferA[i] != '\0' && BufferA[i] != '\n'&& BufferA[i]!='\t')
			fout << BufferA[i]<< endl;
	}
	for (int i = 0; i < mid; i++)
	{
		if (BufferB[i] != ' ' && BufferB[i] != '\0'&& BufferB[i] != '\n'&& BufferB[i] != '\t')
			fout << BufferB[i]<< endl;
	}
	return;
}

void CreateToken(ofstream & fout,int start,int end, char BufferA[],int mid,char BufferB[],int type)
{
		fout << "<";
		for (int i = start; i < end; i++)
		{
			if(BufferA[i]!=' '&&BufferA[i]!='\n'&&BufferA[i]!='\0'&& BufferA[i] != '\t')
			fout << BufferA[i];
		}
		for (int i = 0; i < mid; i++)
		{
			if (BufferB[i] != ' '&&BufferB[i] != '\n'&&BufferB[i] != '\0'&& BufferB[i] != '\t')
				fout << BufferB[i];
		}
		if (type == NULL)
		{
			fout << ">" << endl;
		}
		else if (type == ID)
		{
			fout << ",Identifier>" << endl;
		}
		else if (type == NUMBER)
		{
			fout << ",Number>" << endl;
		}
		else if (type == OPERATOR)
		{
			fout << ",Operator>" << endl;
		}
		else if (type == PUNCTUATION)
		{
			fout << ",Punctuation>" << endl;
		}
		else if (type == KEYWORD)
		{
			fout << ",Keyword>" << endl;
		}
	return;
}