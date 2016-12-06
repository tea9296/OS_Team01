#include <iostream>
#include <thread>
#include <cstdlib>

using namespace std;

int match=0;
int tobacco=0;
int paper=0;
int signal=1, signalM=0, signalT=0, signalP=0;

void agent(){
	int num;
	while(1){
		if(match+tobacco+paper==0 && signal==1){
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
			signal=0;
		}
	}
}

void smoke_match(){
	while(1){
		if(tobacco==1 && paper==1 && signalM==1){
			cout << "match smoke!" << endl;	
			tobacco=0;
			paper=0;
			signalM=0;
			signal=1;
		}
		else if(signal==1){
			//cout << "match can't smoke!" << endl;
			signalM=0;
		}
		
	}
}

void smoke_tobacco(){
	while(1){
		if(match==1 && paper==1 && signalT==1){
			cout << "tobacco smoke!" << endl;
			match=0;
			paper=0;
			signalT=0;
			signal=1;
		}
		else if(signal==1){
			//cout << "tobacco can't smoke!" << endl;
			signalT=0;
		}
		
	}
}

void smoke_paper(){
	while(1){
		if(match==1 && tobacco==1 && signalP==1){
			cout << "paper smoke!" << endl;
			match=0;
			tobacco=0;
			signalP=0;
			signal=1;
		}
		else if(signal==1){
			//cout << "paper can't smoke!" << endl;
			signalP=0;
		}
		
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
