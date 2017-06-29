/*---------------------------------------------------------*/
/*
 * Author: Bartosz Stasiak
 * Date: 22/03/2017
 * 
 * Description: Alghoritm for heapsort
 * 
 * Example of use:
 * Type in console: heapsort.exe < testsource.txt
*/
/*---------------------------------------------------------*/

#include <vector>
#include <iostream>

//fill an array with numbers, get address of stream to remember cursor position
void fillArrayWithData(std::vector<long>&, unsigned short);
//just heapsort
void heapsort(std::vector<long>&);
//show an array ascending or descending. For ascending skip first element
void showArray(const std::vector<long>&, char);
//Move last element of array to root
void moveLastToRoot(std::vector<long>&);

int main()
{
	using namespace std;

	int in_nr; //number of test cases
	cin >> in_nr;

	for (int i = 0; i < in_nr; i++)
	{
		unsigned short arr_size; //array size
		vector<long> output_array; //output array
		vector<long> array_to_sort; //array with numbers

		cin >> arr_size; //get array size (max 65 534), for bigger val it'll set 0, because of ++arr_size
		array_to_sort.resize(++arr_size); //set size for array with numbers (array size+1)
		fillArrayWithData(array_to_sort, arr_size); //filling array with data

		unsigned short counter = 1; //count 

		while (counter < arr_size) //if counter equals array size, it's end of test case
		{
			heapsort(array_to_sort); //sort elements in tab to get the biggest one number at root position
			output_array.push_back(array_to_sort[1]); //push the root element into back of output array

			if (counter < (arr_size - 1))
			{
				showArray(array_to_sort, 'a'); //show array ascending
				moveLastToRoot(array_to_sort); //move last element to the root
			}

			counter++;
		}

		showArray(output_array, 'd'); //show output array descending
		cout << endl;
	}
	return 0;
}

void fillArrayWithData(std::vector<long>& tab, unsigned short size)
{
	long value;
	for (int i = 1; i < size; i++)
	{
		std::cin >> value;
		tab.at(i) = value;
	}
}

void heapsort(std::vector<long>& tab)
{
	bool state_sort = false;
	while (!state_sort)
	{
		state_sort = true;
		for (unsigned int i = 2; i < tab.size(); i++)
		{
			if (tab[i] > tab[i / 2])
			{
				long temp_val = tab[i];
				tab[i] = tab[i / 2];
				tab[i / 2] = temp_val;
				state_sort = false;
			}
		}
	}
}

void showArray(const std::vector<long>& tab, char ascdesc)
{
	if (ascdesc == 'a')
	{
		for (unsigned short i = 1; i < tab.size(); i++)
			std::cout << tab[i] << " ";
		std::cout << std::endl;
	}
	else if (ascdesc == 'd')
	{
		for (long i = (tab.size() - 1); i >= 0; i--)
			std::cout << tab[i] << " ";
		std::cout << std::endl;
	}
}

void moveLastToRoot(std::vector<long>& tab)
{
	tab[1] = tab[tab.size() - 1];
	tab.erase(tab.begin() + (tab.size() - 1));
}
