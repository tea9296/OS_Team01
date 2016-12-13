#include <iostream>
#include <thread>
#include <cstdlib>
#include <mutex>
#include <windows.h>
#include <cstdlib>
using namespace std;

int match=0;
int tobacco=0;
int paper=0;

mutex agent_Mutex;
mutex smoker_Mutex;


void agent_1(){
    while(1){
        agent_Mutex.lock();
        if(match+tobacco+paper==0){
        match=1;
        tobacco=1;
        cout << endl;
        cout << "|||||||||||||||||\n";
        cout << "| match tobacco |\n";
        cout << "|||||||||||||||||\n";
        //Sleep(1234);
        }
        smoker_Mutex.unlock();
    }
}
void agent_2(){
    while(1){
        agent_Mutex.lock();
        if(match+tobacco+paper==0){
        match=1;
        paper=1;
        cout << endl;
        cout << "|||||||||||||||||\n";
        cout << "| match   paper |\n";
        cout << "|||||||||||||||||\n";
        //Sleep(1524);
        }
        smoker_Mutex.unlock();
    }
}
void agent_3(){
    while(1){
        agent_Mutex.lock();
        if(match+tobacco+paper==0){
        tobacco=1;
        paper=1;
        cout << endl;
        cout << "|||||||||||||||||\n";
        cout << "| tobacco paper |\n";
        cout << "|||||||||||||||||\n";
        //Sleep(1895);
        }
        smoker_Mutex.unlock();
    }
}

void smoke_match(){
	while(1){
        smoker_Mutex.lock();
		if(tobacco==1 && paper==1){
			cout << "match smoke!\n";
			tobacco=0;
			paper=0;
            agent_Mutex.unlock();
            Sleep(rand()*2%10000);
		}
		else{
            cout << "match can't smoke!\n";
            agent_Mutex.unlock();
            Sleep(rand()*29%10000);
		}
	}
}

void smoke_tobacco(){
	while(1){
        smoker_Mutex.lock();
		if(match==1 && paper==1){
			cout << "tobacco smoke!\n";
			match=0;
			paper=0;
            agent_Mutex.unlock();
            Sleep(rand()*6%10000);

		}
		else{
            cout << "tobacco can't smoke!\n";
            agent_Mutex.unlock();
            Sleep(rand()%10000);
		}
	}
}

void smoke_paper(){
	while(1){
        smoker_Mutex.lock();
		if(match==1 && tobacco==1){
			cout << "paper smoke!\n";
			match=0;
			tobacco=0;
			agent_Mutex.unlock();
            Sleep(rand()*76%10000);
		}
		else{
            cout << "paper can't smoke!\n";
            agent_Mutex.unlock();
            Sleep(rand()*38%10000);
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

    cout << "Check\n";
    thread mThreadA_1(agent_1);
	thread mThreadA_2(agent_2);
	thread mThreadA_3(agent_3);
	thread mThreadM(smoke_match);
	thread mThreadT(smoke_tobacco);
	thread mThreadP(smoke_paper);
	//thread mThread1(agent);
	mThreadM.join();
	mThreadT.join();
	mThreadP.join();
	mThreadA_1.join();
	mThreadA_2.join();
	mThreadA_3.join();
	return 0;
}
