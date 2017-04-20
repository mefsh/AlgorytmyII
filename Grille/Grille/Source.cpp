#include <fstream>

char *CreateString(long);	//Dynamic 1-dim array
char **CreateTabCh(short);	//Dynamic 2-dim array
bool **CreateTabB(short);		//Dynamic 2-dim array
void FreeMemory(char *, bool **, char **, short);	//Free memory after allocation
long CoountEmptyBlocks(bool **, short);	//Count # in bool array and return the value*4+1
void FillTabCh(char **, short, std::ifstream *);	//Fill Dynamic 2-dim array with chars
void FillTabB(bool **, short, std::ifstream *);	//Fill Dynamic 2-dim array with 1 or 0
bool **RotateMask(bool **, short);	//Rotate array by 90 degree
void addChars(char *, bool **, char **, short, long &);	//check mask and add chars to string
void FillString(char *, bool **, char **, short);	//fill whole string with message
void Grille();	//start grille function


int main()
{
	Grille();
	return 0;
}

char *CreateString(long size)
{
	char *tab = new char[size];
	tab[size - 1] = '\0'; //set last char as end of string
	return tab;
}

char **CreateTabCh(short size)
{
	char **tab = new char *[size];
	for (int i = 0; i<size; i++)
	{
		tab[i] = new char[size];
	}
	return tab;
}

bool **CreateTabB(short size)
{
	bool **tab = new bool *[size];
	for (int i = 0; i<size; i++)
	{
		tab[i] = new bool[size];
	}
	return tab;
}

void FreeMemory(char *string, bool **tab_bool, char **tab_ch, short size)
{
	for (int i = 0; i < size; i++)
	{
		delete[] tab_bool[i];
		delete[] tab_ch[i];
	}

	delete[] tab_bool;
	delete[] tab_ch;
	delete[] string;
}

long CoountEmptyBlocks(bool **tab_bool, short size)
{
	long real_size=0;
	for (int i=0; i < size; i++)
	{
		for (int j=0; j < size; j++)
		{
			if (tab_bool[i][j]) ++real_size;
		}
	}
	real_size = real_size * 4;
	return ++real_size;
}

void FillTabCh(char **tab, short size, std::ifstream *in)
{
	char character;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			*in >> character;
			tab[i][j] = character;
		}
	}
}
void FillTabB(bool **tab, short size, std::ifstream *in)
{
	char character;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			*in >> character;
			if (character == '#')
				tab[i][j] = false;
			else if (character == '0')
				tab[i][j] = true;
		}
	}
}

bool **RotateMask(bool **tab, short size)
{
	bool **temp_tab = CreateTabB(size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			temp_tab[j][i] = tab[size-1-i][j];
		}
	}
	return temp_tab;
}

void addChars(char *string, bool **tab_bool, char **tab_char, short size, long &id)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (tab_bool[i][j])
			{
				string[id] = tab_char[i][j];
				++id;
			}
		}
	}
}

void FillString(char *string, bool **tab_bool, char **tab_ch, short matrix_size)
{
	long id = 0;
	for (int i = 0; i < 4; i++)
	{
		addChars(string, tab_bool, tab_ch, matrix_size, id);
		tab_bool = RotateMask(tab_bool, matrix_size);
	}
}

void Grille()
{
	using namespace std;
	ifstream in;
	ofstream out;
	in.open("grille.in");
	out.open("grille.out");

	if (in.is_open())
	{
		short matrix_size;
		in >> matrix_size; //get data about test case

		while (matrix_size != 0)
		{
			bool **tab_bool = CreateTabB(matrix_size); //Create tab for states (0 and #)
			FillTabB(tab_bool, matrix_size, &in);

			char **tab_ch = CreateTabCh(matrix_size); //Create tab for characters
			FillTabCh(tab_ch, matrix_size, &in);

			long string_size = CoountEmptyBlocks(tab_bool, matrix_size);
			char *string = CreateString(string_size); //Create string for output message

			FillString(string, tab_bool, tab_ch, matrix_size); //Decode message and fill string with it

			if (out.is_open()) out << string << endl; //send string to output

			FreeMemory(string, tab_bool, tab_ch, matrix_size); //Free memory allocated earlier

			in >> matrix_size; //get data about next test case
		}

		in.close();
		out.close();
	}
}