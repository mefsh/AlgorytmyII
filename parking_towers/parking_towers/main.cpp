#include <iostream>
#include <vector>

struct position //struct for x,y
{
	short x;
	short y;
	position() { x = 0 , y = 0; }
};

void runAlgorithhm();
//fill array with data
void fillArray(std::vector<std::vector<long>>&, const int&, const int&);
//count how much free spaces are on parking
short countFreeSpace(const std::vector<std::vector<long>>&, const int&, const int&);
//set x and y (position) of queued car
void setPosition(const std::vector<std::vector<long>>&, const int&, const int&, int&, position& obj);
//shift circle left until the car won't be in elevator
void shiftCircleLeft(std::vector<std::vector<long>>&, const int&, const int&, const int&, long&);
//shift circle right until the car won't be in elevator
void shiftCircleRight(std::vector<std::vector<long>>&, const int&, const int&, const int&, long&);
//add seconds to total time
void addSecs(long&, int);

//show all spaces on parking
//void showArray(const std::vector<std::vector<long>>&, const int&, const int&);

int main()
{
	runAlgorithhm();
	return 0;
}

void runAlgorithhm()
{
	int nrTestCases; //var for number of test cases
	std::cin >> nrTestCases;

	for (int i = 0; i < nrTestCases; i++)
	{
		long time_in_sec = 0; //var for time in seconds

		short tower_height, circle_length; //vars for tower_height(h) and circle_length(l)
		std::cin >> tower_height >> circle_length;

		std::vector<std::vector<long>> parking(tower_height, std::vector<long>(circle_length)); //create two-dim vector tab

		fillArray(parking, tower_height, circle_length); //fill array with data about parking
		int free_space = countFreeSpace(parking, tower_height, circle_length); //get the number of free spaces
		int car_queue = 1; //the number of queued car
		position pos; //object for positions of cars
		while (free_space < (tower_height * circle_length)) //repeat until whole parking won't be empty
		{
			setPosition(parking, tower_height, circle_length, car_queue, pos); //find the position of car in queue (x and y - coords)
			//shift circle until the queued car won't be in elevator
			if (pos.y <= (circle_length / 2))
				shiftCircleLeft(parking, circle_length, pos.x, car_queue, time_in_sec);
			else
				shiftCircleRight(parking, circle_length, pos.x, car_queue, time_in_sec);
			//showArray(parking, tower_height, circle_length);

			++car_queue; //id of next car that will be queued
			++free_space; //car went off, we have one more free space on parking
		}

		std::cout << time_in_sec << std::endl; //show time in seconds
	}
}

void fillArray(std::vector<std::vector<long>>& parking, const int& tower_height, const int& circle_length)
{
	for (int rows = 0; rows < tower_height; rows++)
		for (int columns = 0; columns < circle_length; columns++)
			std::cin >> parking[rows][columns];
}


short countFreeSpace(const std::vector<std::vector<long>>& parking, const int& tower_height, const int& circle_length)
{
	short counter = 0;
	for (int rows = 0; rows < tower_height; rows++)
		for (int columns = 0; columns < circle_length; columns++)
			if (parking[rows][columns] == -1) counter++;

	return counter;
}

void setPosition(const std::vector<std::vector<long>>& parking, const int& tower_height, const int& circle_length, int& car_queue, position& obj)
{
	bool stop = false;
	for (int rows = 0; rows < tower_height; rows++)
	{
		for (int columns = 0; columns < circle_length; columns++)
		{
			if (parking[rows][columns] == car_queue)
			{
				obj.x = rows;
				obj.y = columns;
				stop = true;
				break;
			}
		}
		if (stop) break;
	}
}

void shiftCircleLeft(std::vector<std::vector<long>>& parking, const int& circle_length, const int& posx, const int& car_queue, long& time_in_sec)
{
	while (parking[posx][0] != car_queue)
	{
		int temp_val = parking[posx][0];
		for (int columns = 1; columns < circle_length; columns++)
		{
			parking[posx][columns - 1] = parking[posx][columns];
		}
		parking[posx][circle_length - 1] = temp_val;
		addSecs(time_in_sec, 5);
	}
	addSecs(time_in_sec, (posx * 10 * 2));
}

void shiftCircleRight(std::vector<std::vector<long>>& parking, const int& circle_length, const int& posx, const int& car_queue, long& time_in_sec)
{
	while (parking[posx][0] != car_queue)
	{
		int temp_val = parking[posx][circle_length - 1];
		for (int columns = (circle_length - 1); columns > 0; columns--)
		{
			parking[posx][columns] = parking[posx][columns - 1];
		}
		parking[posx][0] = temp_val;
		addSecs(time_in_sec, 5);
	}
	addSecs(time_in_sec, (posx * 10 * 2));
}

void addSecs(long& time_in_sec, int howMuchToAdd)
{
	time_in_sec += howMuchToAdd;
}

//void showArray(const std::vector<std::vector<long>>& parking, const int& tower_height, const int& circle_length)
//{
//	for (int rows = 0; rows < tower_height; rows++)
//	{
//		for (int columns = 0; columns < circle_length; columns++)
//		{
//			std::cout << parking[rows][columns] << " ";
//		}
//		std::cout << std::endl;
//	}
//}
