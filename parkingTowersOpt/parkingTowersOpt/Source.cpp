/*
* Purpose: Count when all cars will leave the parking.
* Assumptions: The data is valid.
*
* \author: Bartosz Stasiak
* \version: 1.1 2017.04.04
* 
*  Changelog in compare with old ParkingTowers program:
*  - Optimalized waiting time for results. It processes much faster.
*  - It's oop version.
*/
#include <iostream>
#include <vector>

//#include <chrono>

/**
* \class ParkingTowers
* \brief Parking Towers Class
* to get waiting time until last car will leave the parking.
* \author: Bartosz Stasiak
* \version: 1.1 2017.04.04
*/
class ParkingTowers
{
	/**
	 *A struture to contain an id(number in queue), x and y pos in array
	 */
	struct positionAddr
	{
		long id;
		long x;
		long y;

		positionAddr(long id = 0, long x = 0, long y = 0);
	};

	std::vector<positionAddr> listOfQueuedCars;/*!< An array for queued cars on parking.*/
	int timeToWait; /*!<A variable that contains waiting time.*/
	int towerHeight; /*!<A var that contains tower height*/
	int circleLength; /*!< A var that contains circle length*/
	int freeSpaces; /*!< A var that contains free spaces on parking.*/
	int queuedCarNr; /*!< A var to contain id of currently queued car.*/

	/**
	 *Shift circle left until queued car won't leave the parking.
	 */
	void shiftCircleLeft();
	/**
	*Shift circle right until queued car won't leave the parking.
	*/
	void shiftCircleRight();

public:

	//! A constructor.
	ParkingTowers();
	//! A destructor.
	~ParkingTowers();
	//! Load data from file (Queued cars, tower height and circle length).
	void loadData();
	//! Checks if is parking empty.
	/*
	 * \return bool state(true/false).
	 */
	bool isParkingEmpty() const;
	//! Handle currently queued car.
	void handleQueuedCar();
	//! Get an information about time to wait.
	/*
	 * \return int an integer value.
	 */
	int get_timeToWait() const;
};


int main()
{
	//	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	int nrTestCases;
	std::cin >> nrTestCases;

	for (int i = 0; i < nrTestCases; i++)
	{
		ParkingTowers parkingTowers;
		parkingTowers.loadData();
		while (!parkingTowers.isParkingEmpty())
		{
			parkingTowers.handleQueuedCar();
		}
		std::cout << parkingTowers.get_timeToWait() << std::endl;
	}
	//	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	//	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	//	std::cout << duration << " microsecs\n";
	return 0;
}

ParkingTowers::positionAddr::positionAddr(long id, long x, long y) : id(0), x(0), y(0)
{
	this->id = id;
	this->x = x;
	this->y = y;
}

void ParkingTowers::shiftCircleLeft()
{
	/*Position of queued car on parking (column)*/
	int posOfCarInCircle = listOfQueuedCars[queuedCarNr].y;
	/*A var that contains an amout of swaps in circle, until queued car won't leave the parking*/
	int countSwaps = 0;
	
	/*While position of queued car isn't first column.*/
	while (posOfCarInCircle != 0)
	{
		posOfCarInCircle--;
		countSwaps++;
		//		std::cout << get_timeToWait() << std::endl;
	}
	for (unsigned i = queuedCarNr; i < listOfQueuedCars.size(); i++)
	{
		/*If the row of queued car is the same that we're checking now.*/
		if (listOfQueuedCars[i].x == listOfQueuedCars[queuedCarNr].x)
		{
			listOfQueuedCars[i].y = listOfQueuedCars[i].y - countSwaps;
			if (listOfQueuedCars[i].y < 0) listOfQueuedCars[i].y = circleLength + listOfQueuedCars[i].y;
		}
	}
	timeToWait += 5 * countSwaps;
	timeToWait += listOfQueuedCars[queuedCarNr].x * 10 * 2;
	queuedCarNr++;
	freeSpaces++;
}

void ParkingTowers::shiftCircleRight()
{
	int posOfCarInCircle = listOfQueuedCars[queuedCarNr].y;
	int countSwaps = 0;
	while (posOfCarInCircle != 0)
	{
		if (++posOfCarInCircle >= circleLength) posOfCarInCircle = 0;
		countSwaps++;
		//		std::cout << get_timeToWait() << std::endl;
	}
	for (unsigned i = queuedCarNr; i < listOfQueuedCars.size(); i++)
	{
		if (listOfQueuedCars[i].x == listOfQueuedCars[queuedCarNr].x)
		{
			listOfQueuedCars[i].y = listOfQueuedCars[i].y + countSwaps;
			if (listOfQueuedCars[i].y >= circleLength) listOfQueuedCars[i].y = listOfQueuedCars[i].y - circleLength;
		}
	}
	timeToWait += 5 * countSwaps;
	timeToWait += listOfQueuedCars[queuedCarNr].x * 10 * 2;
	queuedCarNr++;
	freeSpaces++;
}

int ParkingTowers::get_timeToWait() const
{
	return timeToWait;
}

ParkingTowers::ParkingTowers()
{
	this->timeToWait = 0;
	this->towerHeight = 0;
	this->circleLength = 0;
	this->freeSpaces = 0;
	this->queuedCarNr = 1;
}

ParkingTowers::~ParkingTowers()
{
}

void ParkingTowers::loadData()
{
	std::cin >> towerHeight >> circleLength;

	listOfQueuedCars.resize(towerHeight * circleLength + 1);
	int counter = 0;
	int val;
	for (int i = 0; i < towerHeight; i++)
	{
		for (int j = 0; j < circleLength; j++)
		{
			std::cin >> val;
			if (val == -1)
				freeSpaces++;
			else
			{
				positionAddr posAdr(val, i, j);
				listOfQueuedCars.at(val) = posAdr;
				counter++;
			}
		}
	}
	listOfQueuedCars.resize(++counter);
}

bool ParkingTowers::isParkingEmpty() const
{
	if (freeSpaces >= towerHeight * circleLength)
		return true;
	return false;
}

void ParkingTowers::handleQueuedCar()
{
	/*Checks if it'll be faster to shift circle left or right.*/
	if (listOfQueuedCars[queuedCarNr].y <= circleLength / 2)
	{
		shiftCircleLeft();
	}
	else
	{
		shiftCircleRight();
	}
}
