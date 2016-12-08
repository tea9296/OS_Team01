#include <iostream>
#include <thread>
#include <time.h>

using namespace std;

void CreateIngre(int Ingres[3],int Ingre )
{
	//Ingre=0->Tabacoo    Ingre=1->Match     Ingre=2->Paper
  Ingres[Ingre]=1;
  if(Ingre==0)
  cout<<"create Tabacoo on the table!!"<<"\n";
  else if(Ingre==1)
  cout<<"create Match on the table!!"<<"\n";
  else if (Ingre==2)
  cout<<"create Paper on the table!!"<<"\n";
}

void Smoking(int Ingres[3])
{	
	cout<<"no any ingredient on the table,need to restart."<<"\n";
	for(int i=0;i<3;i++)
	Ingres[i]=0;
}


void TabacooSmoker(int Ingres[3])
{
	if(Ingres[1]==1&&Ingres[2]==1){
	cout<<"I'm Smoker1,I,got Match and Paper and now I have all ingredients,I can smoke!!"<<"\n";
	Smoking(Ingres);
	}
	else{
		cout<<"I'm Smoker1,I can't smoke...QAQ"<<"\n";
	}
}

void MatchSmoker(int Ingres[3])
{
	if(Ingres[0]==1&&Ingres[2]==1){
	cout<<"I'm Smoker2,I,got Tabacoo and Paper and now I have all ingredients,I can smoke!!"<<"\n";
	Smoking(Ingres);
	}
	else{
		cout<<"I'm Smoker2,I can't smoke...QAQ"<<"\n";
	}
}


void PaperSmoker(int Ingres[3])
{
	if(Ingres[0]==1&&Ingres[1]==1){
	cout<<"I'm Smoker3,I,got Tabacoo and Match and now I have all ingredients,I can smoke!!"<<"\n";
	Smoking(Ingres);
	}
	else{
		cout<<"I'm Smoker3,I can't smoke...QAQ"<<"\n";
	}
}



int main( int argc, char** argv )
{	int Ingres[3]={0},Ingre1=0,Ingre2=0;
	srand((unsigned)time(NULL));
	for(int k=0;k<10;k++){
		
	cout<<"start new game\n";

	while(Ingre1==Ingre2)
	{	Ingre1=rand()%3;
		Ingre2=rand()%3;
	}	
  thread mThread1( CreateIngre,Ingres,Ingre1 );
  thread mThread2(CreateIngre,Ingres,Ingre2);
   mThread1.join();
   mThread2.join();
  
  Ingre1=0;
  Ingre2=0;
  
  thread mThread3(TabacooSmoker,Ingres);
   thread mThread4(MatchSmoker,Ingres);
    thread mThread5(PaperSmoker,Ingres);
  mThread3.join();
  mThread4.join();
  mThread5.join();
 
	}
 
 

  return 0;
}
