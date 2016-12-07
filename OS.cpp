#include<iostream>
#include<thread>
#include<time.h>
#include<mutex>
#include<chrono>
using namespace std;
int Privide_tabacoo=0, Privide_paper=0, Privide_match=0;
int Paper=0, Tabacoo=0, Match=0;
mutex agent_mutex;
mutex smoker_tabacoo_mutex;
mutex smoker_paper_mutex;
mutex smoker_match_mutex;
void Random(){
	int x;
	x = rand()%3;
	if(x == 0){
		Paper = 0;
		Tabacoo = 1;
		Match = 1;
	}
	else if(x ==1){
		Paper = 1;
		Tabacoo = 0;
		Match = 1;
	}
	else{
		Paper = 1;
		Tabacoo = 1;
		Match = 0;
	}
}
void agent_Tabacoo(){
	if(Tabacoo){
		Privide_tabacoo = 1;
		cout<<"Agent privide Tabacoo!\n";
	}
}
void agent_Paper(){
	if(Paper){
		Privide_paper = 1;
		cout<<"Agent privide Paper!\n";
	}
}
void agent_Match(){
	if(Match){
		Privide_match = 1;
		cout<<"Agent privide Match!\n";
	}
}
void smoker_Tabacoo(){
	if(Privide_paper && Privide_match){
		cout<<"Smoker_Tabacoo go to smoke...\n";
		Privide_paper = 0;
		Privide_match = 0;
		this_thread::sleep_for(chrono::seconds(1));
//		sleep(2);
	}
}
void smoker_Paper(){
	if(Privide_tabacoo && Privide_match){
		cout<<"Smoker_Paper go to smoke...\n";
		Privide_tabacoo = 0;
		Privide_match =0;
		this_thread::sleep_for(chrono::seconds(1));
//		sleep(2);
	}
}
void smoker_Match(){
	if(Privide_paper && Privide_tabacoo){
		cout<<"Smoker_Match go to smoke...\n";
		Privide_paper = 0;
		Privide_tabacoo = 0;
		this_thread::sleep_for(chrono::seconds(1));
	}
}
int main(){
	int i=0;
	srand(time(NULL));
	cout<<endl;
	while(i<3){
		thread Thread_Random(Random);		
		Thread_Random.join();

		thread Thread_Agent_Tabocoo(agent_Tabacoo);
		thread Thread_Agent_Paper(agent_Paper);
		thread Thread_Agent_Match(agent_Match);
/*		Thread_Agent_Tabocoo.join();
		Thread_Agent_Paper.join();
		Thread_Agent_Match.join();
*/
		thread Thread_Smoker_Tabacoo(smoker_Tabacoo);
		thread Thread_Smoker_Paper(smoker_Paper);
		thread Thread_Smoker_Match(smoker_Match);

		Thread_Agent_Tabocoo.join();
		Thread_Agent_Paper.join();
		Thread_Agent_Match.join();
		Thread_Smoker_Tabacoo.join();
		Thread_Smoker_Paper.join();
		Thread_Smoker_Match.join();
		i++;
		cout<<endl;
	}
	return 0;
}
