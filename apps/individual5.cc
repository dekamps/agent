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

const int TRADERS = 16;

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
 
//  srand(atoi(argv[1]));
  srand(1234);
  int chartists = 4;
  int REPS = 1;
  int STEPS = 1000;

  double A = 0.3;
  double B = 5.0;
  double C = 1.5;

//  double A = atof(argv[3]);
//  double B = atof(argv[4]);
//  double C = atof(argv[5]);
  double INITIALPRICE = 0.505;
  double ASSETVALUE = 0.5;
  double BONDRETURN = 0.0; 
  bool prePrice = true;
  double totChaotic = 0;
  double totLimit = 0;
  double chsq = 0;
  double lisq = 0;
  double maxCh = 0;
  double maxLi = 0;    
  int M = 32;
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

    for(int i = 0; i < TRADERS; i++)
    {
      int sum = 0;
      for(int j = 0; j < TRADERS; j++)
        sum += connections[i][j];
      counts[i] = sum;
    }
      
    cout << "X = [";

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
       
    double sum = 0;
    for(int i = 0; i < TRADERS; i++)
      sum+=prices[i]; 
    sum/=TRADERS;
    cout << sum << " ";
    for(int i = 0; i < TRADERS; i++)
      cout << prices[i] << " ";
    cout << endl;

      }
  }
cout<<"];"<<endl;
cout <<"plot(X(:,1),'k','LineWidth',2); " << endl;
cout <<"hold on" << endl;
cout << "for i = 2:2:16" << endl; 
cout << "  plot(X(:,i),'-','Color',[0.5 0.5 0.5],'LineWidth',2);" << endl; 
cout << "end" << endl; 
cout << "for i = 3:2:16" << endl; 
cout << "  plot(X(:,i),':','Color',[0.5 0.5 0.5],'LineWidth',2);" << endl; 
cout << "end" << endl; 
cout << "xlabel('Time','FontSize',24);" << endl; 
cout << "ylabel('Price','FontSize',24);" << endl; 
  return 0;
}
