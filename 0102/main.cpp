#include "mainwindow.h"
#include <QString>
#include <iostream>
#include <QApplication>
#include <thread>
#include <cstdlib>
#include <mutex>
#include <chrono>
#include <cstdlib>
#include <QPushButton>
#include <QObject>
using namespace std;
MainWindow *w;
int agent=-1;

//light_there
int match=0;//light_match
int tobacco=0;//light_tobacco
int paper=0;//light_paper
int light_s1=0;//S_match
int light_s2=0;//S_tobacco
int light_s3=0;//S_paper
int Text=0,stop=0;

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
           // Sleep(2000);
            this_thread::sleep_for(chrono::seconds(2));
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
          //  Sleep(2000);
           this_thread::sleep_for(chrono::seconds(2));
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
           // Sleep(2000);
            this_thread::sleep_for(chrono::seconds(2));
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
            Text=1;
          //   Sleep(2000);
           this_thread::sleep_for(chrono::seconds(2));
            tobacco=0;
            paper=0;
            cout << "goto smoke!\n";
            Text=4;
          //  Sleep(2000);
           this_thread::sleep_for(chrono::seconds(2));
            cout << "Agent wake up!\n";
            Text=5;
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
            Text=2;
          //   Sleep(2000);
           this_thread::sleep_for(chrono::seconds(2));
            match=0;
            paper=0;
            cout << "goto smoke!\n";
            Text=4;
           // Sleep(2000);
           this_thread::sleep_for(chrono::seconds(2));
            cout << "Agent wake up!\n";
            Text=5;
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
            Text=3;
            // Sleep(2000);

            this_thread::sleep_for(chrono::seconds(2));
            match=0;
            tobacco=0;
            cout << "goto smoke!\n";
            Text=4;
            //Sleep(2000);
            this_thread::sleep_for(chrono::seconds(2));
            cout << "Agent wake up!\n";
            Text=5;
            light_s3=0;
            agent_Mutex.unlock();
        }
    }
}

int main( int argc, char** argv){
    QApplication a(argc, argv);
    w=new MainWindow();




    w->show();



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
    while(1){
        stop=w->Tk();
        if(light_s1==1){
           w->setMatchON();
           QApplication::processEvents();
        }
        else if(light_s1==0){
            w->setMatchOFF();
            QApplication::processEvents();
        }
        if(light_s2==1){
            w->setTabaccoON();
            QApplication::processEvents();
        }
        else if(light_s2==0){
            w->setTabaccoOFF();
            QApplication::processEvents();
        }
        if(light_s3==1){
            w->setPaperON();
            QApplication::processEvents();
        }
        else if(light_s3==0){
            w->setPaperOFF();
            QApplication::processEvents();
        }
        if(match==1){
            w->setMmonoON();
            QApplication::processEvents();
        }
        else if(match==0){
            w->setMmonoOFF();
            QApplication::processEvents();
        }
        if(tobacco==1){
            w->setBmonoON();
            QApplication::processEvents();
        }
        else if(tobacco==0){
            w->setBmonoOFF();
            QApplication::processEvents();
        }
        if(paper==1){
            w->setPmonoON();
            QApplication::processEvents();
        }
        else if(paper==0){
            w->setPmonoOFF();
            QApplication::processEvents();
        }

        if(Text==1){
            w->setAnn("Hey, I'm match.");
            QApplication::processEvents();
        }
        else if(Text==2){
            w->setAnn("Hey, I'm tobacco.");
            QApplication::processEvents();
        }
        else if(Text==3){
            w->setAnn("Hey, I'm paper.");
            QApplication::processEvents();
        }
        else if(Text==4){
            w->setAnn("goto smoke!");
            QApplication::processEvents();
        }
        else if(Text==5){
            w->setAnn("Agent wake up!");
            QApplication::processEvents();
        }
        if(stop==1)
        {
            while(stop==1)
            {   stop=w->Tk();
                QApplication::processEvents();
               // Sleep(100);
                this_thread::sleep_for(chrono::milliseconds(20));
            }
        }
    }


    mThreadA.join();
    mThreadM.join();
    mThreadT.join();
    mThreadP.join();
    mThreadA_1.join();
    mThreadA_2.join();
    mThreadA_3.join();

      return a.exec();
}
