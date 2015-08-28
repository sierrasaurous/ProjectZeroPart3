//
//  main.cpp
//  ProjectZeroPart3
//
//  Created by Sierra on 8/28/15.
//  Copyright (c) 2015 Sierra Adibi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class machine{  // this is like the type, which is why can define the vector machines using this below
public:
    double average; // current defined average
    double range; // current defined range
    double total;
    int count;
    double calcAverage; // calculated average from previous winnings
    double Q; // Q value
    vector<double> winnings;
    
    void initialize();
    void setstats();
    void calcs();
    void printvalues();
};

void machine::initialize(){
    total = 0;
    count = 0;
    Q = 20;
}

void machine::setstats(){
    average = rand()%10;
    range = rand()%10;
}

void machine::calcs(){
    total = 0;
    for (int i=0; i<winnings.size(); i++) {
        total = total + winnings.at(i);
    }
    calcAverage = total/winnings.size();
}

void machine::printvalues(){
    cout << "\t\t\t" << total << "\t\t\t" << calcAverage;
    
    cout << "\t\t\t\t"<< Q << "\t\t\t\t"  <<count <<endl << endl;
}


class casino{
public:
    int numofmachines;
    vector<machine> slots;
    
    void initialize();
};

void casino::initialize(){
    numofmachines = 3;
    
    for(int i=0;i<numofmachines;i++){
        machine m;
        m.initialize();
        m.setstats();
        
        slots.push_back(m);
    }
}

double pull(double median, double range){
    double r1 = ((double)rand()/RAND_MAX)*range;
    double r2 = ((double)rand()/RAND_MAX)*range;
    
    return median+r1-r2;
}

void printheader(int num){
    cout << "\n The results of your first " << num <<" rounds are below: \n";
    
    cout << "Machine Number | Total Winnings | Average Pull Value | Q Value | Number of Pulls  \n";
    cout << "----------------------------------------------------------------------------------\n";
};



int main(){
    srand(time(NULL));
    
    vector<casino> southlake;
    int numofcasinos = 3;
    int rounds = 100;
    double alpha = 0.1; //learning rate
    int epsilon = 10; // 10% of the time, take random.
    
    // set up the number of casinos
    for( int i=0;i<numofcasinos;i++){
        casino c;
        c.initialize();
        southlake.push_back(c);
    }

    // Begin with three pulls on each:
    
    cout << "Welcome to the Multi-Armed Bandit Game!  Today we are playing with " << numofcasinos << " casinos." << endl;
    
    for(int r=0;r<rounds;r++){
        
        double test = r%epsilon;
        
        int state = abs(rand()%numofcasinos);
        
        
        
        if(test!=0){
        
        for( int i=0;i<southlake.at(state).slots.size();i++){
            for(int j=0; j<southlake.at(i).slots.size();j++){
                if(i!=j){
                
                if(southlake.at(state).slots.at(i).Q>=southlake.at(state).slots.at(j).Q){
                    double win = pull(southlake.at(state).slots.at(i).average, southlake.at(state).slots.at(i).range);
                    
                    southlake.at(state).slots.at(i).winnings.push_back(win);
                    southlake.at(state).slots.at(i).count++;
                    southlake.at(state).slots.at(i).Q = (1-alpha)*southlake.at(state).slots.at(i).Q+ alpha*win;
                }
                }/*else{
                    double win = pull(southlake.at(state).slots.at(j).average, southlake.at(state).slots.at(j).range);
                    
                    southlake.at(state).slots.at(j).winnings.push_back(win);
                    southlake.at(state).slots.at(j).count++;
                    southlake.at(state).slots.at(j).Q = (1-alpha)*southlake.at(state).slots.at(j).Q+ alpha*win;
                }*/
            }
        }}else{
            int nongreedy = rand()%(southlake.at(state).slots.size());
            int action = abs(nongreedy);
            double win = pull(southlake.at(state).slots.at(action).average, southlake.at(state).slots.at(action).range);
            
            southlake.at(state).slots.at(action).winnings.push_back(win);
            southlake.at(state).slots.at(action).count++;
            southlake.at(state).slots.at(action).Q = (1-alpha)*southlake.at(state).slots.at(action).Q+ alpha*win;
        }
    }
    
    for (int i=0; i<numofcasinos; i++){
        
        cout << "Casino Number " << i << ":" << endl;
        printheader(rounds);
        
        for (int j=0; j<southlake.at(i).slots.size();j++){
            
            southlake.at(i).slots.at(j).calcs();
            
            cout << "\t\t" << j;
            
            southlake.at(i).slots.at(j).printvalues();
        }
    }
    
    int totalpulls = 0;
    
    for(int i=0;i<numofcasinos;i++) {
        for(int j=0;j<southlake.at(i).slots.size();j++){
            totalpulls = totalpulls + southlake.at(i).slots.at(j).count;
        }}
    
    cout << endl << endl<< "Total Pulls = " << totalpulls;
    
    return 0;
}
