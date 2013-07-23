/*
* Copyright (c) 2013 Dan Ladley, Marc de Kamps <M.deKamps@leeds.ac.uk>
*
* Permission to use, copy, modify, and distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>

const int  TRADERS = 3;

using namespace std;

int main(int argc, char** argv)
{

  int connections[TRADERS][TRADERS];
  double counts[TRADERS];
  double prices[TRADERS];
  double lastPrice[TRADERS];
  double demands[TRADERS];
  double demandsP[TRADERS][TRADERS];
  double est[TRADERS];
  bool types[TRADERS];
 
  srand(1234);             //               ---NEW

  int M = 0;//atoi(argv[2]);

  int chartists = 8;

  double A = 0.3;          //               ---NEW
  double B = 5.0;          //               ---NEW
  double C = 1.5;          //               ---NEW

  enum Trader {FUNDAMENTALIST, CHARTIST};


  int WIN = 5;
  int REPS = 100;
  int NETS = 1000; 
  const int STEPS = 1000;
  double PT[STEPS];
  double INITIALPRICE = 0.505;
  double ASSETVALUE = 0.5;
  double BONDRETURN = 0.0; 
  bool prePrice = true;
  double totChaotic = 0;
  double totLimit = 0;
  double totSteady = 0;
  double chsq = 0;
  double lisq = 0;
  double maxCh = 0;
  double maxLi = 0;    

  for(int i = 0; i < chartists; i++)
    types[i] = CHARTIST;
  for(int i = chartists; i < TRADERS; i++)
    types[i] = FUNDAMENTALIST;

	connections[0][0] = 1;
	connections[0][1] = 1;
	connections[0][2] = 1;
	connections[1][0] = 1;
	connections[1][1] = 1;
	connections[1][2] = 1;
	connections[2][0] = 1;
	connections[2][1] = 1;
	connections[2][2] = 1;
	

	/// initialization ends here

    for(int i = 0; i < TRADERS; i++)
    {
      int sum = 0;
      for(int j = 0; j < TRADERS; j++)
        sum += connections[i][j];
      counts[i] = sum;
    }
      
    int chaotic = 0;
    int limit = 0;
    int steady  =0;

    for(int reps = 0; reps < REPS; reps++)
    {
      for(int i = 0; i < TRADERS; i++)
      {
        lastPrice[i] = INITIALPRICE;
        prices[i] = INITIALPRICE;
        est[i] = 0;
        demands[i] = 0;
        for(int j = 0; j < TRADERS; j++)
          demandsP[i][j] = 0;
      } 

      double sqdif = 0;
      int minima = 0;
      double p2 = 0;
      double p1 = 0;
      double p = 0;

      for(int step = 0; step < STEPS; step++)
      {
        int choice = (int)(TRADERS*(rand()/(RAND_MAX+1.0)));
        if(prePrice)
        {
          double demand = 0;
          for(int i  =0; i < TRADERS; i++)
            if(connections[choice][i]==1)// && i != choice)
            {
               demand += demandsP[choice][i];
               demandsP[choice][i] = 0;
            }
            //if(connections[choice][i]==1 && i != choice)
            //   demand += demands[i];
          prices[choice] += demand/(counts[choice]/*-1*/);
        }
    
        if(types[choice] == CHARTIST)
        {
          double deltaP = prices[choice] - lastPrice[choice];
          lastPrice[choice] = prices[choice];
          est[choice] = est[choice] + C*(deltaP-est[choice]);
          double x = est[choice] - BONDRETURN;
          demands[choice] = 1.0/(1+exp(-4*B*x)) - 0.5;
        }
        else // fundamentalist
        {
          demands[choice] = A*(ASSETVALUE-prices[choice]);
        } 
        for(int i = 0; i <TRADERS; i++)
          demandsP[i][choice] += demands[choice];
        if(!prePrice)
        {
          for(int i  = 0; i < TRADERS; i++)
            if(connections[choice][i]==1)
               prices[i] += demands[choice]/counts[choice];
        }

        double price = 0;
        for(int i  = 0; i < TRADERS; i++)
          price += prices[i];
        PT[step] = price;
        p2 = p1;
        p1 = p;
        p = price/TRADERS;

        if(step >= 2*WIN)
        {
          sqdif += (p-p1)*(p-p1);
          if((PT[step-WIN] < PT[step] && PT[step-WIN] < PT[step-2*WIN]) ||(PT[step-WIN] > PT[step] && PT[step-WIN] > PT[step-2*WIN]))
            ++minima;
        }
        cout << price/TRADERS << " " << endl;
	  }

      if(sqdif < 0.001)
      {
        steady++;
      }
      else
      {
        if(minima >= 300)
          chaotic++;
        else
          limit++;
      }
//	  cout << reps << " " << minima << endl;
    }
    totSteady+= steady;
    totChaotic+= chaotic;
    totLimit += limit;
    chsq += chaotic*chaotic;
    lisq += limit*limit;
    if(chaotic > maxCh)
      maxCh = chaotic;
    if(limit > maxLi)
      maxLi = limit;
  }
