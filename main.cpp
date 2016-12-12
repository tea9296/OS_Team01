#include <iostream>
#include <thread>
#include <cstdlib>
#include <mutex>
#include <windows.h>
using namespace std;

int match=0;
int tobacco=0;
int paper=0;
int Signal=1, signalM=0, signalT=0, signalP=0;
mutex agent_Mutex;
mutex smoker_Mutex;
void agent(){
    while(1){
	int num;
    agent_Mutex.lock();
    if(match+tobacco+paper==0 && Signal==1){
        num=rand()%3;
        if(num==0){
            match=1;
            tobacco=1;
        }
        else if(num==1){
            match=1;
            paper=1;
        }
        else if(num==2){
            tobacco=1;
            paper=1;
        }
        else
            cout << "err" << endl;
        cout << match << " " << tobacco << " " << paper << endl;
        signalM=1;
        signalT=1;
        signalP=1;
        Signal=0;
    }
    Sleep(1000);
	smoker_Mutex.unlock();
    }
}

void smoke_match(){
	while(1){
        smoker_Mutex.lock();
		if(tobacco==1 && paper==1 && signalM==1){
			cout << "match smoke!" << endl;
			tobacco=0;
			paper=0;
			signalM=0;
			Signal=1;
		}
		else if(Signal==1){
			//cout << "match can't smoke!" << endl;
			signalM=0;
		}
        agent_Mutex.unlock();

	}
}

void smoke_tobacco(){
	while(1){
        smoker_Mutex.lock();
		if(match==1 && paper==1 && signalT==1){
			cout << "tobacco smoke!" << endl;
			match=0;
			paper=0;
			signalT=0;
			Signal=1;
		}
		else if(Signal==1){
			//cout << "tobacco can't smoke!" << endl;
			signalT=0;
		}
        agent_Mutex.unlock();

	}
}

void smoke_paper(){
	while(1){
            smoker_Mutex.lock();
		if(match==1 && tobacco==1 && signalP==1){
			cout << "paper smoke!" << endl;
			match=0;
			tobacco=0;
			signalP=0;
			Signal=1;
		}
		else if(Signal==1){
			//cout << "paper can't smoke!" << endl;
			signalP=0;
		}
        agent_Mutex.unlock();

	}
}

int main(){

	/*
	for(int i=0;i<10;i++){
		agent();
		smoke_match();
		smoke_tobacco();
		smoke_paper();
	}
	*/


	thread mThreadM(smoke_match);
	thread mThreadT(smoke_tobacco);
	thread mThreadP(smoke_paper);
	thread mThread1(agent);
	cout << "Are you serious?"<< endl;
	mThread1.join();
	mThreadM.join();
	mThreadT.join();
	mThreadP.join();
	return 0;
}
