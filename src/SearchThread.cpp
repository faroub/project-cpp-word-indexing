#include "SearchThread.h"
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
#include <map>
#include <iterator>
#include<iostream>

using namespace std;

//to access Queue object
// defined somewhere in the program
extern SyncQueue Qobject;

//filter to search only .txt file
// only visible from this translation unit
static const char * filter = "*.txt";

//SearchFinished flag is set when search of .txt file is over
// defined somewhere in the program
extern unsigned char SearchFinishedFlag;

SearchThread :: SearchThread(){

}

SearchThread :: ~ SearchThread(){

}
/*
Name: StartSearchTxtFiles()
Description: This funcion search for all .txt file in specified path
Parameter: string filepath    path of directory
Return Value: int 
*/
void SearchThread :: StartSearchTxtFiles(string filepath){
    int flags = 0;
    if (nftw(filepath.c_str(), // directory path
         callback, // called once for each entry in the tree
         20, // maximum number of directories that nftw() will hold open simultaneously
         flags)==-1 //
            ){
        perror("nftw");
        exit(EXIT_FAILURE);
    }
    //if Search is over then SearchFinishedFlag =1
    SearchFinishedFlag = 1;

}

int SearchThread:: callback(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
    if (typeflag == FTW_F) {
        if(fnmatch(filter, fpath, FNM_CASEFOLD) == 0) {               
		     Qobject.AddFileNameinQ(fpath);  
            }
    }
    return 0;
}
