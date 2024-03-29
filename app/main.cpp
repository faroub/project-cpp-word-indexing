//File : main.cpp
//Desc : This starts the program to execute
//Date : 10 Jan 2015
//author : Kripal Thakur


#include "SyncQueue.h"
#include "WorkerThread.h"
#include "SearchThread.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <ftw.h>
#include <fnmatch.h>
#include <signal.h>
#include <errno.h>
#include <fstream>
#include <vector>
#include <utility>
#include <iterator>
#include <map>
#include <iomanip>
#include <unistd.h>
using namespace std;

//max 3 worker thread
const unsigned int WThreadCount = 3;

//to know if seraching of txt file is over
unsigned char SearchFinishedFlag=0;

//Queue object
SyncQueue Qobject;

int main(int argc, char * argv[]){

if(argc<2){

    cout<<"Please specify the directory name "<<endl;	
    cout<<"Usage :  ./SearchExecutable <dirname>"<<endl;
    return -1;
}
DIR *pDir;
pDir = opendir (argv[1]);

if(pDir==NULL){
    cout << endl << "Directory doesn't exists" << endl;
    return -1;
}
closedir(pDir);

cout << endl <<"Please wait while process(" << getpid() << ")" << " is processing...." <<  endl;

//Creating worker threads
WorkerThread WThread(WThreadCount);
WThread.CreateThreeWorkerThread();

//Creating Search thread to add .txt file in Queue
SearchThread STobject;
STobject.StartSearchTxtFiles(string(argv[1]));

while(1){
    if(SearchFinishedFlag && !(Qobject.GetCount()))
    break;
}

multimap<int,string,greater<int>> MMtable;
MMtable = WThread.getTableEntry();

cout << endl <<"Total files Processed "<< Qobject.GetFileCount() << endl;     

cout << "***********************************************"<<endl;
cout << " "<< setw(10)<< "Words" <<  setw(20) << "No of occurences"<<endl;
cout << "***********************************************"<<endl;        
        
int i=0;
for(auto iter=MMtable.begin(); iter!=MMtable.end(); ++iter){
    std::cout << " " << setw(10)  << iter->second << setw(10)<<  iter->first << std::endl;
    i++;
    if(i==10) //To get only top 10 words.
       break;
}
cout << "***********************************************"<<endl;

return 0;
}
