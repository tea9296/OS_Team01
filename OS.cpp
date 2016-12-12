#include<iostream>
#include<thread>
#include<time.h>
#include<mutex>
#include<chrono>
using namespace std;
int Privide_tobacco=0, Privide_paper=0, Privide_match=0;
int Paper=0, Tobacco=0, Match=0;
mutex agent_tobacco_mutex;
mutex agent_paper_mutex;
mutex agent_match_mutex;
mutex smoker_tobacco_mutex;
mutex smoker_paper_mutex;
mutex smoker_match_mutex;
mutex random_mutex;
void Random(){
	while(1){
		random_mutex.lock();
		int x;
		x = rand()%3;
		if(x == 0){
			Paper = 0;
			Tobacco = 1;
			Match = 1;
		}
		else if(x ==1){
			Paper = 1;
			Tobacco = 0;
			Match = 1;
		}
		else{
			Paper = 1;
			Tobacco = 1;
			Match = 0;
		}
		agent_tobacco_mutex.unlock();
		agent_paper_mutex.unlock();
		agent_match_mutex.unlock();
	}
}
void agent_Tobacco(){
	while(1){
		agent_tobacco_mutex.lock();	
		if(Tobacco){
			Privide_tobacco = 1;
			cout<<"Agent privide Tabacoo!\n";
		}
		smoker_tobacco_mutex.unlock();
		smoker_paper_mutex.unlock();
		smoker_match_mutex.unlock();
	}
}
void agent_Paper(){
	while(1){
		agent_paper_mutex.lock();
		if(Paper){
			Privide_paper = 1;
			cout<<"Agent privide Paper!\n";
		}
		/*		smoker_tobacco_mutex.unlock();
				smoker_paper_mutex.unlock();
				smoker_match_mutex.unlock();
				*/	}
}
void agent_Match(){
	while(1){
		agent_match_mutex.lock();
		if(Match){
			Privide_match = 1;
			cout<<"Agent privide Match!\n";
		}
		/*		smoker_tobacco_mutex.unlock();
				smoker_paper_mutex.unlock();
				smoker_match_mutex.unlock();
				*/	}
}
void smoker_Tobacco(){
	while(1){
		smoker_tobacco_mutex.lock();
		if(Privide_paper && Privide_match){
			cout<<"Smoker_Tobacco go to smoke...\n\n";
			Privide_paper = 0;
			Privide_match = 0;
			this_thread::sleep_for(chrono::seconds(2));
/*			agent_tobacco_mutex.unlock();
			agent_paper_mutex.unlock();
			agent_match_mutex.unlock();
*/			random_mutex.unlock();
		}
	}
}
void smoker_Paper(){
	while(1){
		smoker_paper_mutex.lock();
		if(Privide_tobacco && Privide_match){
			cout<<"Smoker_Paper go to smoke...\n\n";
			Privide_tobacco = 0;
			Privide_match =0;
			this_thread::sleep_for(chrono::seconds(2));
/*			agent_tobacco_mutex.unlock();
			agent_paper_mutex.unlock();
			agent_match_mutex.unlock();
*/			random_mutex.unlock();
		}
	}
}
void smoker_Match(){
	while(1){
		smoker_match_mutex.lock();
		if(Privide_paper && Privide_tobacco){
			cout<<"Smoker_Match go to smoke...\n\n";
			Privide_paper = 0;
			Privide_tobacco = 0;
			this_thread::sleep_for(chrono::seconds(2));
/*			agent_tobacco_mutex.unlock();
			agent_paper_mutex.unlock();
			agent_match_mutex.unlock();
*/			random_mutex.unlock();
		}
	}
}
int main(){
	int i=0;
	srand(time(NULL));
	cout<<endl;
	thread Thread_Random(Random);		
	thread Thread_Agent_Tobacco(agent_Tobacco);
	thread Thread_Agent_Paper(agent_Paper);
	thread Thread_Agent_Match(agent_Match);

	thread Thread_Smoker_Tobacco(smoker_Tobacco);
	thread Thread_Smoker_Paper(smoker_Paper);
	thread Thread_Smoker_Match(smoker_Match);

	/*	Thread_Agent_Tobacco.join();
		Thread_Agent_Paper.join();
		Thread_Agent_Match.join();
		*/
	Thread_Random.join();
	Thread_Agent_Tobacco.join();
	Thread_Agent_Paper.join();
	Thread_Agent_Match.join();
	Thread_Smoker_Tobacco.join();
	Thread_Smoker_Paper.join();
	Thread_Smoker_Match.join();
	return 0;
}
