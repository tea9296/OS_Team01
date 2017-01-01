#include <iostream>
#include <thread>
#include <cstdlib>
#include <mutex>
#include <windows.h>
#include <cstdlib>
using namespace std;

int agent=-1;

//light_there
int match=0;//light_match
int tobacco=0;//light_tobacco
int paper=0;//light_paper
int light_s1=0;//S_match
int light_s2=0;//S_tobacco
int light_s3=0;//S_paper


mutex agent_Mutex;
mutex agent_Mutex1;
mutex agent_Mutex2;
mutex agent_Mutex3;
mutex smoker_Mutex1;
mutex smoker_Mutex2;
mutex smoker_Mutex3;

void rAgent(){
    while(1){
        agent_Mutex.lock();
        agent = rand()%3;
        if(agent==0){
            agent_Mutex1.unlock();//match,tobacco
        }
        else if(agent==1){
            agent_Mutex2.unlock();//match,paper
        }
        else if(agent==2){
            agent_Mutex3.unlock();//tobacoo,paper
        }
    }
}

void agent_1(){
    while(1){
        agent_Mutex1.lock();
        if(agent==0 && match+tobacco+paper==0){
            match=1;
            tobacco=1;
            cout << endl;
            cout << "|||||||||||||||||\n";
            cout << "| match tobacco |\n";
            cout << "|||||||||||||||||\n";
            Sleep(2000);
            smoker_Mutex1.unlock();
            smoker_Mutex2.unlock();
            smoker_Mutex3.unlock();
        }
    }
}
void agent_2(){
    while(1){
        agent_Mutex2.lock();
        if(agent==1 && match+tobacco+paper==0){
            match=1;
            paper=1;
            cout << endl;
            cout << "|||||||||||||||||\n";
            cout << "| match   paper |\n";
            cout << "|||||||||||||||||\n";
            Sleep(2000);
            smoker_Mutex1.unlock();
            smoker_Mutex2.unlock();
            smoker_Mutex3.unlock();
        }
    }
}
void agent_3(){
    while(1){
        agent_Mutex3.lock();
        if(agent==2 && match+tobacco+paper==0){
            tobacco=1;
            paper=1;
            cout << endl;
            cout << "|||||||||||||||||\n";
            cout << "| tobacco paper |\n";
            cout << "|||||||||||||||||\n";
            Sleep(2000);
            smoker_Mutex1.unlock();
            smoker_Mutex2.unlock();
            smoker_Mutex3.unlock();
        }
    }
}

void smoke_match(){
	while(1){
        smoker_Mutex1.lock();
		if(tobacco==1 && paper==1){
            light_s1=1;
            cout << "Hey, I'm match.\n";
			tobacco=0;
			paper=0;
			cout << "goto smoke!\n";
			Sleep(2000);
			cout << "Agent wake up!\n";
			light_s1=0;
            agent_Mutex.unlock();
		}
	}
}

void smoke_tobacco(){
	while(1){
        smoker_Mutex2.lock();
		if(match==1 && paper==1){
            light_s2=1;
            cout << "Hey, I'm tobacco.\n";
			match=0;
			paper=0;
			cout << "goto smoke!\n";
			Sleep(2000);
			cout << "Agent wake up!\n";
			light_s2=0;
            agent_Mutex.unlock();
		}
	}
}

void smoke_paper(){
	while(1){
        smoker_Mutex3.lock();
		if(match==1 && tobacco==1){
            light_s3=1;
            cout << "Hey, I'm paper.\n";
			match=0;
			tobacco=0;
			cout << "goto smoke!\n";
			Sleep(2000);
			cout << "Agent wake up!\n";
			light_s3=0;
			agent_Mutex.unlock();
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
    smoker_Mutex1.lock();
    smoker_Mutex2.lock();
    smoker_Mutex3.lock();
    agent_Mutex1.lock();
    agent_Mutex2.lock();
    agent_Mutex3.lock();
    thread mThreadA(rAgent);
    thread mThreadA_1(agent_1);
	thread mThreadA_2(agent_2);
	thread mThreadA_3(agent_3);
	thread mThreadM(smoke_match);
	thread mThreadT(smoke_tobacco);
	thread mThreadP(smoke_paper);
	//thread mThread1(agent);
	mThreadA.join();
	mThreadM.join();
	mThreadT.join();
	mThreadP.join();
	mThreadA_1.join();
	mThreadA_2.join();
	mThreadA_3.join();
	return 0;
}
