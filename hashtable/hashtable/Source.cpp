/********************************************/
/*
 * Author: Bartosz Stasiak
 * 
 * Description: 
 * Hashtable alghoritm with rehash function 
 * when an element has been deleted.
 * 
 * Example of use:
 * Type hashtable.exe < testsource.txt in console
 */
 /********************************************/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void hashtable();
void setSizeOfArray(vector<long>&, vector<string>&, unsigned &, bool &);
void addData(vector<long>&, vector<string>&, const unsigned &);
void printOutput(vector<long>&, vector<string>&);
void deleteElement(vector<long>&, vector<string>&, const unsigned &);

int main()
{
	hashtable();
	return 0;
}

void hashtable()
{
	string x; //var for string
	unsigned in_nr; //how much test cases
	cin >> in_nr;

	for (unsigned i = 0; i < in_nr; i++)
	{
		vector<long> array_ldata; //array with keys
		vector<string> array_chdata; //array with strings
		unsigned arr_size = 0; //set 0 for arr_size for each test case
		bool skip_whileloop = false;
		
		cin >> x;

		while (x != "stop")
		{
			if (x == "size" && arr_size == 0)
			{
				setSizeOfArray(array_ldata, array_chdata, arr_size, skip_whileloop);
			}
			else if (x == "add")
			{
				addData(array_ldata, array_chdata, arr_size);
			}
			else if (x == "print")
			{
				printOutput(array_ldata, array_chdata);
			}
			else if (x == "delete")
			{
				deleteElement(array_ldata, array_chdata, arr_size);
			}

			if (skip_whileloop) break;

			cin >> x; //get a value or string (in while loop)
		}
	}
}

void setSizeOfArray(vector<long>& array_ldata, vector<string>& array_stringdata, unsigned &arr_size, bool &skip_whileloop)
{
	static unsigned i = 1;
	if (cin >> arr_size && (arr_size > 0 && arr_size <= USHRT_MAX)) //max arr_size is unsigned short int = 65535 
	{
		//resize tab with keys and strings
		array_ldata.resize(arr_size);
		array_stringdata.resize(arr_size);
	}
	else
	{
		cin.clear(); //clear state on input
		cout << "Test case nr " << i << " has been skipped, because the number of tab size is incorrect(too big (MAX: " << USHRT_MAX << "), less than or equals zero, or it isn't a number)!" << endl;
		string x;
		cin >> x;
		while (x != "stop")
		{
			cin >> x;
		} //skip all until "stop", which indicates end of test case
		skip_whileloop = true;
	}
	i++;
}

void addData(vector<long>& array_ldata, vector<string>& array_chdata, const unsigned &arr_size)
{
	long value;
	string x;

	cin >> value;
	cin >> x;

	unsigned hash_id = value % arr_size; //a mod b
	unsigned check_whole_table = 0;
	bool no_space = false;

	while (array_chdata[hash_id] != "")
	{
		if (++hash_id >= (array_ldata.size() - 1)) hash_id = 0;
		if (++check_whole_table >= array_ldata.size()) //while can do max 1 loop throught the array
		{
			no_space = true; //if there is no space in tab, the add command will be skipped
			break;
		}
	}

	if (!no_space)
	{
		array_ldata.at(hash_id) = value;
		array_chdata.at(hash_id) = x;
	}
}

void printOutput(vector<long>& array_ldata, vector<string>& array_chdata)
{
	for (unsigned i = 0; i < array_ldata.size(); i++)
	{
		if (array_chdata[i] != "")
			cout << i << " " << array_ldata[i] << " " << array_chdata[i] << endl;
	}
	cout << endl;
}

void deleteElement(vector<long>& array_ldata, vector<string>& array_chdata, const unsigned &arr_size)
{
	unsigned found_id = 0;
	bool check_if_found = false;

	long find_value;
	cin >> find_value;

	for (unsigned i = 0; i < array_ldata.size(); i++)
	{
		if (array_ldata[i] == find_value && array_chdata[i] != "")
		{
			array_ldata.at(i) = 0;
			array_chdata.at(i) = "";
			check_if_found = true;
			found_id = i + 1;; //set id after deleted element
			if (found_id == array_ldata.size()) found_id = 0; //if found_id is out of range, set 0 as id
			break;
		}
	}

	if (check_if_found) //if the key that we were looking for to delete has been found
	{
		string temp_x; //temp var for string
		long temp_l; //temp var for key
		unsigned hash_id;

		for (unsigned i = 0; i < (array_ldata.size() - 1); i++)
		{
			hash_id = array_ldata[found_id] % arr_size; //a mod b

			temp_l = array_ldata[found_id];
			temp_x = array_chdata[found_id];
			//delete id that we're hashing, to make that place free if hash won't change
			array_ldata.at(found_id) = 0;
			array_chdata.at(found_id) = "";

			while (array_chdata[hash_id] != "") //minimum 2 empty strings in tab at this point, so loop can't always be true
			{
				if (hash_id >= (array_ldata.size() - 1)) hash_id = 0;
				else hash_id++;
			}
			array_ldata.at(hash_id) = temp_l;
			array_chdata.at(hash_id) = temp_x;

			if (++found_id == array_ldata.size())found_id = 0;
		}
	}
}
