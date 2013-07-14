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

#define TRADERS (16)

using namespace std;

int main(int argc, char** argv)
{

/*  ifstream Inputs(argv[1]);
  for(int i = 0; i < TRADERS; i++)
    for(int j = 0; j < TRADERS; j++)
      Inputs >> connections[i][j];
  Inputs.close();  */

  int connections[TRADERS][TRADERS];
  double counts[TRADERS];
  double prices[TRADERS];
  double lastPrice[TRADERS];
  double demands[TRADERS];
  double demandsP[TRADERS][TRADERS];
  double est[TRADERS];
  bool types[TRADERS];
 
  srand(atoi(argv[1]));  // sets the seed
  int M = 0;//atoi(argv[2]);
  int chartists = atoi(argv[3]);
  double A = atof(argv[4]);
  double B = atof(argv[5]);
  double C = atof(argv[6]);

for(M = 16; M <= 120; M+=2)
{
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
    types[i] = 1;
  for(int i = chartists; i < TRADERS; i++)
    types[i] = 0;


  for(int net = 0; net < NETS; net++)
  {
    /*for(int i = 0; i < TRADERS; i++)
      for(int j = 0; j < TRADERS; j++)
      {
        if(i == j || i == (j+TRADERS-1)%TRADERS || i == (j+1)%TRADERS)
          connections[i][j] = 1;
        else
          connections[i][j] = 0;
      }  
    int count = TRADERS;
    while(count < M)
    {  
      int x = (int)(TRADERS*(rand()/(RAND_MAX+1.0)));
      int y = (int)(TRADERS*(rand()/(RAND_MAX+1.0)));
      if(connections[x][y] == 0)
      {
        count++;
        connections[x][y]=1;
        connections[y][x]=1;
      }
    }*/
    bool noCon = true;
    while(noCon)
    {
      for(int i = 0; i < TRADERS; i++)
        for(int j = 0; j < TRADERS; j++)
        {
          if(i == j)
            connections[i][j] = 1;
          else
            connections[i][j] = 0;
        }  
      int count = 0;
      while(count < M)
      {  
        int x = (int)(TRADERS*(rand()/(RAND_MAX+1.0)));
        int y = (int)(TRADERS*(rand()/(RAND_MAX+1.0)));
        if(connections[x][y] == 0)
        {
          count++;
          connections[x][y]=1;
          connections[y][x]=1;
        }
      }
      bool reached[TRADERS];
      for(int i = 0; i < TRADERS; i++)
        reached[i] = false;
      bool toCheck[TRADERS];
      for(int i = 0; i < TRADERS; i++)
        toCheck[i] = false;
      toCheck[0] = true;
      int needChecking = 1;
      int found = 0;
      while(needChecking > 0 && found < TRADERS)
      {
        int choice = 0;
        while(toCheck[choice] == false)
          choice++;
        needChecking--;
        toCheck[choice] = false;
        found++;
        reached[choice] = true;
        for(int i = 0; i < TRADERS; i++)
          if(connections[choice][i] == 1)
            if(reached[i] == false && toCheck[i] == false)
            {
              needChecking++;
              toCheck[i] = true;
            }
      }
      if(found == TRADERS)
        noCon = false;
    }
  /*  for(int i = 0; i < TRADERS; i++)
    {
      for(int j = 0; j < TRADERS; j++)
        cout << connections[i][j] << " ";
      cout << endl;
    }
      cout << endl;
*/
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
    
        if(types[choice])
        {
          double deltaP = prices[choice] - lastPrice[choice];
          lastPrice[choice] = prices[choice];
          est[choice] = est[choice] + C*(deltaP-est[choice]);
          double x = est[choice] - BONDRETURN;
          demands[choice] = 1.0/(1+exp(-4*B*x)) - 0.5;
        }
        else
        {
          demands[choice] = A*(ASSETVALUE-prices[choice]);
        } 
        for(int i = 0; i <TRADERS; i++)
          demandsP[i][choice] += demands[choice];
        if(!prePrice)
        {
          for(int i  =0; i < TRADERS; i++)
            if(connections[choice][i]==1)
               prices[i] += demands[choice]/counts[choice];
        }

        double price = 0;
        for(int i  =0; i < TRADERS; i++)
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
//        cout << price/TRADERS << " ";
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
  //    cout << reps << " " << minima << endl;
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
  cout << M << " " << chartists << " " << totSteady/NETS << " " << totLimit/NETS << " " << totChaotic/NETS << " " << sqrt((lisq - totLimit*totLimit/NETS)/NETS) << " " << sqrt((chsq - totChaotic*totChaotic/NETS)/NETS) << " " << maxLi*(100.0/REPS) << " " << maxCh*(100.0/REPS) << endl;
}
  return 0;
}
