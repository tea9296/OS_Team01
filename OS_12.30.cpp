#include<iostream>
#include<thread>
#include<time.h>
#include<mutex>
#include<chrono>
using namespace std;
int Privide_tobacco=0, Privide_paper=0, Privide_match=0;
int Paper=0, Tobacco=0, Match=0;
int UI_text=-1,UI_smoker=-1,UI_agent=-1;

mutex agent_tobacco_paper_mutex;
mutex agent_paper_match_mutex;
mutex agent_match_tobacco_mutex;
mutex smoker_tobacco_mutex;
mutex smoker_paper_mutex;
mutex smoker_match_mutex;
mutex random_mutex;
void Random(){
	while(1){
		random_mutex.lock();
		UI_text = 1;
		this_thread::sleep_for(chrono::seconds(2));
		cout<<"\n\n";
		int x;
		x = rand()%3;
		if(x == 0){
			Paper = 0;
			Tobacco = 1;
			Match = 1;
			agent_match_tobacco_mutex.unlock();
		}
		else if(x ==1){
			Paper = 1;
			Tobacco = 0;
			Match = 1;
			agent_paper_match_mutex.unlock();
		}
		else{
			Paper = 1;
			Tobacco = 1;
			Match = 0;
			agent_tobacco_paper_mutex.unlock();
		}
	}
}
void agent_Tobacco_Paper(){
	while(1){
		agent_tobacco_paper_mutex.lock();	
		if(Tobacco && Paper){
			Privide_match = 0;
			Privide_tobacco = 1;
			Privide_paper = 1;
			UI_text = 2;
			UI_agent = 1;
			cout<<"Agent privide Tabacoo and Paper!\n";
			while(1){
				if(UI_text == -2 && UI_agent == -2){
					smoker_match_mutex.unlock();
					break;
				}

			}
		}
	}
}
void agent_Paper_Match(){
	while(1){
		agent_paper_match_mutex.lock();
		if(Paper && Match){
			Privide_paper = 1;
			Privide_match = 1;
			Privide_tobacco = 0;
			UI_text = 2;
			UI_agent = 2;
			cout<<"Agent privide Paper and Match!\n";
			while(1){
				if(UI_text == -2 && UI_agent == -2){
					smoker_tobacco_mutex.unlock();
					break;
				}

			}
		}	
	}
}
void agent_Match_Tobacco(){
	while(1){
		agent_match_tobacco_mutex.lock();
		if(Match && Tobacco){
			Privide_match = 1;
			Privide_tobacco = 1;
			Privide_paper = 0;
			UI_text = 2;
			UI_agent = 3;
			cout<<"Agent privide Match and Tobacco!\n";
			while(1){
				if(UI_text == -2 && UI_agent == -2){
					smoker_paper_mutex.unlock();
					break;
				}

			}
		}

	}
}
void smoker_Tobacco(){
	int count = 0;
	while(1){
		smoker_tobacco_mutex.lock();
		//		this_thread::sleep_for(chrono::seconds(1));
		if(count == 0){
			count++;
			continue;
		}
		if(Privide_paper && Privide_match){
			UI_smoker = 1;
			UI_text = 3;
			cout<<"Smoker_Tobacco go to smoke...\n";
			this_thread::sleep_for(chrono::seconds(2));
			/*			agent_tobacco_mutex.unlock();
						agent_paper_mutex.unlock();
						agent_match_mutex.unlock();
						*/
			while(1){
				if(UI_text == -2 && UI_smoker == -2){
					random_mutex.unlock();
					break;
				}
			}
		}
		else{
			cout<<"Smoker_tobacco can't smoking.\n";
		}
	}
}
void smoker_Paper(){
	int count = 0;
	while(1){
		smoker_paper_mutex.lock();
		//		this_thread::sleep_for(chrono::seconds(1));
		if(count == 0){
			count++;
			continue;
		}
		if(Privide_tobacco && Privide_match){
			UI_smoker = 2;
			UI_text = 3;
			cout<<"Smoker_Paper go to smoke...\n";
			this_thread::sleep_for(chrono::seconds(2));
			/*			agent_tobacco_mutex.unlock();
						agent_paper_mutex.unlock();
						agent_match_mutex.unlock();
						*/
			while(1){
				if(UI_text == -2 && UI_smoker == -2){
					random_mutex.unlock();
					break;
				}
			}
		}
		else{
			cout<<"Smoker_paper can't smoking.\n";
		}
	}
}
void smoker_Match(){
	int count = 0;
	while(1){
		smoker_match_mutex.lock();
		//		this_thread::sleep_for(chrono::seconds(1));
		if(count == 0){
			count++;
			continue;
		}
		if(Privide_paper && Privide_tobacco){
			UI_smoker = 3;
			UI_text = 3;
			cout<<"Smoker_Match go to smoke...\n";
			this_thread::sleep_for(chrono::seconds(2));
			/*			agent_tobacco_mutex.unlock();
						agent_paper_mutex.unlock();
						agent_match_mutex.unlock();
						*/		
			while(1){
				if(UI_text == -2 && UI_smoker == -2){
					random_mutex.unlock();
					break;
				}
			}
		}
		else{
			cout<<"Smoker_match can't smoking.\n";
		}
	}
}
int main(){
	int i=0;
	srand(time(NULL));
	cout<<endl;
	thread Thread_Random(Random);		
	thread Thread_Agent_Tobacco_Paper(agent_Tobacco_Paper);
	thread Thread_Agent_Paper_Match(agent_Paper_Match);
	thread Thread_Agent_Match_Tobacco(agent_Match_Tobacco);

	thread Thread_Smoker_Tobacco(smoker_Tobacco);
	thread Thread_Smoker_Paper(smoker_Paper);
	thread Thread_Smoker_Match(smoker_Match);

	/*	Thread_Agent_Tobacco.join();
		Thread_Agent_Paper.join();
		Thread_Agent_Match.join();
		*/
	while(1){

		if(UI_text==1){		
			cout<<"Smoker 通知 Agent 發原料\n";
			this_thread::sleep_for(chrono::seconds(2));
			UI_text = -2;
		}
		else if(UI_text==2){
			cout<<"Agent 放原料囉\n";
			this_thread::sleep_for(chrono::seconds(2));
			UI_text = -2;
		}
		else if(UI_text==3){
			cout<<"Smoker 抽菸中\n";
			this_thread::sleep_for(chrono::seconds(2));
			UI_text = -2;
		}

		if(UI_smoker==1){	
			cout<<"Smoker_Tobacco go to smoke 去抽煙囉～\n";
			this_thread::sleep_for(chrono::seconds(2));
			UI_smoker = -2;
		}
		else if(UI_smoker==2){
			cout<<"Smoker_Paper go to smoke 去抽煙囉～\n";
			this_thread::sleep_for(chrono::seconds(2));
			UI_smoker = -2;
		}
		else if(UI_smoker==3){
			cout<<"Smoker_Match go to smoke 去抽煙囉～\n";
			this_thread::sleep_for(chrono::seconds(2));
			UI_smoker = -2;
		}

		if(UI_agent==1){		
			cout<<"Agent privide Tabacoo and Paper! 提供原料～\n";
			this_thread::sleep_for(chrono::seconds(2));
			UI_agent = -2;
		}
		else if(UI_agent==2){
			cout<<"Agent privide Paper and Match! 提供原料～\n";
			this_thread::sleep_for(chrono::seconds(2));
			UI_agent = -2;
		}
		else if(UI_agent==3){
			cout<<"Agent privide Match and Tobacco! 提供原料～\n";
			this_thread::sleep_for(chrono::seconds(2));
			UI_agent = -2;
		}

	}
	Thread_Random.join();
	Thread_Agent_Tobacco_Paper.join();
	Thread_Agent_Paper_Match.join();
	Thread_Agent_Match_Tobacco.join();
	Thread_Smoker_Tobacco.join();
	Thread_Smoker_Paper.join();
	Thread_Smoker_Match.join();
	return 0;
}
