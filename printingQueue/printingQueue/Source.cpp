/*
 * Purpose: Count when my task will be printed.
 * Assumptions: The data is valid.
 * 
 * \author: Bartosz Stasiak
 * \version: 1.0 2017.04.22
 */

#include <iostream>
#include <vector>

using std::cin;


/**
 * \class PrintingQueue
 * \brief Printing Queue Class
 * to create Queue of tasks to print.
 * It also counts, how much time will it take to print our task.
 * \author: Bartosz Stasiak
 * \version: 1.0 2017.04.22
 */
class PrintingQueue
{
	std::vector<int> tasksArray;	/*!< An array for tasks.*/
	int arraySize;	/*!< An array size.*/
	int timeToWait;	/*!< Time to wait until our task will be printed.*/
	int myTaskPositon;	/*!< Position of our task in queue.*/
	bool printMyTask;	/*!< To check if our task's been printed.*/

public:
	//! A constructor.
	PrintingQueue();
	//! A destructor.
	~PrintingQueue();
	//! Load data from file (arraySize, myTaskPosition and tasks queue).
	void loadData();
	//! Find position of the biggest priority in tasks queue.
	/*!
	 * \return Position of the biggest priority in tasks queue.
	 */
	int findBiggestPriorityPos();
	//! Shift queue left until the element with biggest priority
	//! won't be on first place of queue.
	/*!
	 * \param biggestPriorityPosition an integer value.
	 */
	void shiftCircleLeft(int biggestPriorityPosition);
	//! Delete first element from queue, and add +1minute to timeToWait.
	void printFirstElement();
	//! Get an information if is our task printed.
	/*!
	 * \return a bool state: true or false.
	 */
	bool isMyTaskPrinted() const;
	//! Get an information, how much do i have to wait until my task will be printed.
	/*!
	 * \return an integer value, which represents time in mins.
	 */
	int getTimeToWait() const;
};

int main()
{
	int numberOfTestCases;
	cin >> numberOfTestCases;

	for (int i = 0; i < numberOfTestCases; i++)
	{
		PrintingQueue obj;
		obj.loadData();

		while (!obj.isMyTaskPrinted())
		{
			int biggestPriorityPosition = obj.findBiggestPriorityPos();
			obj.shiftCircleLeft(biggestPriorityPosition);
			obj.printFirstElement();
		}

		std::cout << obj.getTimeToWait() << std::endl;
	}

	return 0;
}


PrintingQueue::PrintingQueue()
{
	this->arraySize = 0;
	this->timeToWait = 0;
	this->myTaskPositon = 0;
	this->printMyTask = false;
}

PrintingQueue::~PrintingQueue()
{
}

void PrintingQueue::loadData()
{
	cin >> arraySize >> myTaskPositon;
	for (int i = 0; i < arraySize; i++)
	{
		int temp_val;
		cin >> temp_val;
		tasksArray.push_back(temp_val);
	}
}

int PrintingQueue::findBiggestPriorityPos()
{
	int maxPriority = tasksArray[0];
	int maxPriorityId = 0;
	for (unsigned i = 1; i < tasksArray.size(); i++)
	{
		if (maxPriority < tasksArray[i])
		{
			maxPriority = tasksArray[i];
			maxPriorityId = i;
		}
	}
	return maxPriorityId;
}

void PrintingQueue::shiftCircleLeft(int biggestPriorityPosition)
{
	while (biggestPriorityPosition > 0)
	{
		int temp_val = tasksArray[0];
		for (unsigned i = 1; i < tasksArray.size(); i++)
		{
			tasksArray[i - 1] = tasksArray[i];
		}
		tasksArray[tasksArray.size() - 1] = temp_val;
		biggestPriorityPosition--;
		if (--myTaskPositon < 0)
			myTaskPositon = tasksArray.size() - 1;
	}
}

void PrintingQueue::printFirstElement()
{
	tasksArray.erase(tasksArray.begin());

	if (myTaskPositon == 0)
		printMyTask = true;

	if (--myTaskPositon < 0)
		myTaskPositon = 0;

	timeToWait++;
}

bool PrintingQueue::isMyTaskPrinted() const
{
	return printMyTask;
}

int PrintingQueue::getTimeToWait() const
{
	return timeToWait;
}
