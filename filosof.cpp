#include <thread>
#include <stdio.h>
#include <chrono>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <mutex>
using namespace std;

#define giNomberOfPhilosophers      5
#define giDelay                   500
#define giAmmountOfFood            50

void philosopherPerformAction(int iNumb);
void grabChopstick(int, int, const char *);
void putDownChopsticks(int, int);
int eatFoodOnTable();

mutex  gaChopsticks  [giNomberOfPhilosophers];
thread gaPhilosophers[giNomberOfPhilosophers];
mutex  gFoodLock;
int             giSleepSeconds = 1;





int main(int argc, char **argv)
{
	int i;
	if (argc == 2)
		giSleepSeconds = atoi(argv[1]);


	for (i = 0; i < giNomberOfPhilosophers; i++)
		gaPhilosophers[i] = thread (philosopherPerformAction, i);

	for (i = 0; i < giNomberOfPhilosophers; i++)
		gaPhilosophers[i].join();

	puts("Bye");
	return 0;
}

void philosopherPerformAction(int iNumber)
{
	int iNum;
	int iLeftStick, iRightStick, iFoodSupply;
	iNum = iNumber;
	printf("Philosopher %d is done thinking and now ready to eat.\n", iNum);
	iRightStick = iNum;
	iLeftStick = iNum + 1;
	if (iLeftStick == giNomberOfPhilosophers)
		iLeftStick = 0;
	while (  ( iFoodSupply = eatFoodOnTable() )  ) {
		if (iNum == 1)
			this_thread::sleep_for(chrono::seconds(giSleepSeconds));
		grabChopstick(iNum, iRightStick, "right");
		grabChopstick(iNum, iLeftStick, "left");
		printf("Philosopher %d: eating.\n", iNum);
		this_thread::sleep_for(chrono::microseconds(giDelay * (giAmmountOfFood - iFoodSupply + 1)));
		putDownChopsticks(iLeftStick, iRightStick);
	}
	printf("Philosopher %d is done eating.\n", iNum);
	return;
}

int eatFoodOnTable()
{
	static int iFood = giAmmountOfFood;
	int        iMyFood;
	gFoodLock.lock();
	if (iFood > 0)
		iFood--;
	iMyFood = iFood;
	gFoodLock.unlock();
	return iMyFood;
}

void grabChopstick(int iPhilosopher, int iStick, const char *acHand)
{
	gaChopsticks[iStick].lock();
	printf("Philosopher number %d with his %s hand grab stick number %d\n", iPhilosopher, acHand, iStick);
}

void putDownChopsticks(int Stick1st, int Stick2nd)
{
	gaChopsticks[Stick1st].unlock();
	gaChopsticks[Stick2nd].unlock();
}



