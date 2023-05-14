#include "game_of_life.h"
#include <ctime>
#include <iostream>
using namespace std;

int game_of_life::gen_rnd(int min, int max)
{
	int slucajni_broj = rand() % (max-min+1) + min;
	return slucajni_broj;
}

bool game_of_life::slucajna_vrijednost()
{	
	if (gen_rnd(1, 4) == 3) {
		return true;
		
	}
	else
	{
		return false;
		
	}
}

bool game_of_life::celija_zauzeta(int i, int j)
{
	return _generacija[i][j];
}

int game_of_life::broj_susjeda(int i, int j)
{
	int susjedi = 0;
	if (celija_zauzeta(i + 1, j) && i+1<REDAKA)
	{
		susjedi++;
	}
	if (celija_zauzeta(i -1, j) && i-1>=0)
	{
		susjedi++;
	}
	if (celija_zauzeta(i, j+1) && j+1<STUPACA)
	{
		susjedi++;
	}
	if (celija_zauzeta(i, j - 1) && j-1>= 0)
	{
		susjedi++;
	}

	if (celija_zauzeta(i+1, j - 1) && j - 1 >= 0 && i + 1 < REDAKA)
	{
		susjedi++;
	}
	if (celija_zauzeta(i-1, j - 1) && j-1>= 0 && i - 1 >= 0)
	{
		susjedi++;
	}
	if (celija_zauzeta(i+1, j +1) && j + 1 < STUPACA && i + 1 < REDAKA)
	{
		susjedi++;
	}
	if (celija_zauzeta(i-1, j +1) && j + 1 < STUPACA && i - 1 >= 0)
	{
		susjedi++;
	}
	
	
	return susjedi;
}



game_of_life::game_of_life()
{
	srand(time(nullptr));
	for (size_t i = 0; i < REDAKA; i++)
	{
		for (size_t j = 0; j < STUPACA; j++)
		{
			_generacija[i][j] = slucajna_vrijednost();
		}
	}
}
	
	


void game_of_life::sljedeca_generacija()
{
	for (int i = 0; i < REDAKA; i++)
	{
		for (int j = 0; j < STUPACA; j++)
		{	
			if (celija_zauzeta(i,j))
			{
				if (broj_susjeda(i,j) == 2 || broj_susjeda(i,j) == 3)
				{
					_sljedeca_generacija[i][j] = true;
				}
				else
				{
					_sljedeca_generacija[i][j] = false;
				}	
			}
			if (!celija_zauzeta(i,j))
			{
				if (broj_susjeda(i,j) == 3)
				{
					_sljedeca_generacija[i][j] = true;
				}
				else
				{
					_sljedeca_generacija[i][j] = false;
				}
			}
		}
	}
	for (int i = 0; i < REDAKA; i++)
	{
		for (int j = 0; j < STUPACA; j++)
		{
			_generacija[i][j] = _sljedeca_generacija[i][j];
		}
	}
	
}

void game_of_life::iscrtaj()
{
	for (int i = 0; i < REDAKA; i++)
	{
		for (int j = 0; j < STUPACA; j++)
		{
			if (celija_zauzeta(i,j))
			{
				cout << "*";
			}
			else
			{
				cout << "-";
			}
		}
		cout << endl;
	}
}

