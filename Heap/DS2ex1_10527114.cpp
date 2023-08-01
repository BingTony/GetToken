// 10527114 郭柄村 
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <fstream>
#include <math.h>

using namespace std;

struct school {		// school info
	string name, department, type, level, graduateNum;
	int heapNum;
}; // school

void selectSchool( vector<school> &sVector, vector<school> &mVector, int schoolNum,
				 string sName, string sDep, string sType, string sLevel );
				 
void heapInsert( vector<school> &hVector, school item ); 

int main(int argc, char** argv) {
	fstream fin;
	string fileName;
	
	while ( fin.is_open() != true ){		// read txt
		cout << "Input the file number: 101, 102 ... [0]Quit" << endl;
		cin >> fileName ;
		cout << endl;
	
		if( fileName == "0" )
			return 0;
		
		fileName = "input" + fileName + ".txt" ;

		fin.open( fileName.c_str(), ios::in );
		if( fin.is_open() != true )
			cout << "### " << fileName << " does not exist! ### " << endl << endl;
	} // while
	
	vector<school> sVector;		// school vector
	vector<school> mVector;		// matched school
	vector<school> hVector;		// max heap of matched school
	
	int schoolNum = 0;		// number of school
	school temp;
	char buffer[200];
	
	fin.ignore(200, '\n' );		// skip unused
	fin.ignore(200, '\n' );
	fin.ignore(200, '\n' );
	while( fin.getline( buffer, 200, '\t' ) ){	// input txt info to vector
		fin.getline( buffer, 200, '\t' );
		if( buffer == "/t" )					// if input double tab
			temp.name.assign( "\0" );
		else
			temp.name.assign( buffer );
		
		fin.getline( buffer, 200, '\t' );
		fin.getline( buffer, 200, '\t' );
		if( buffer == "/t" )
			temp.department.assign( "\0" );
		else
			temp.department.assign( buffer );
		
		fin.getline( buffer, 200, '\t' );
		if( buffer == "/t" )
			temp.type.assign( "\0" );
		else
			temp.type.assign( buffer );
		
		fin.getline( buffer, 200, '\t' );
		if( buffer == "/t" )
			temp.level.assign( "\0" );
		else
			temp.level.assign( buffer );
		
		fin.getline( buffer, 200, '\t' );
		fin.getline( buffer, 200, '\t' );
		fin.getline( buffer, 200, '\t' );
		if( buffer == "/t" )
			temp.graduateNum.assign( "\0" );
		else
			temp.graduateNum.assign( buffer );
		
		fin.getline( buffer, 200, '\t' );
		fin.getline( buffer, 200, '\n' );
		
		if( temp.graduateNum != "\0" ) {	// graduates is not nothing so do not ignore this info
			sVector.push_back( temp );
			schoolNum++;
		} // if
	} // while
	
	//---------------------------start select and build heap-----------------------------
	string command;
	while( command != "0" ) {
		cout << endl << "******************************************************" << endl;
		cout << "Mission One: Select Matched Records form a Text File" << endl;
		cout << "******************************************************" << endl;
		mVector.clear();
		hVector.clear();
		
		string sName, sDep, sType, sLevel;		// user's keys
		mVector.clear();
		cout << "Enter a keyword of 學校名稱: [*]for all" << endl;
		cin >> sName;
		cout << "Enter a keyword of 科系名稱: [*]for all" << endl;
		cin >> sDep;
		cout << "Enter a keyword of 日夜別: [*]for all" << endl;
		cin >> sType;
		cout << "Enter a keyword of 等級別: [*]for all" << endl;
		cin >> sLevel;
	
		selectSchool( sVector, mVector, schoolNum, sName, sDep, sType, sLevel );		// select
	
		cout << "*** There are " << mVector.size() << " matched records, listed as below:" << endl;		// print match info
		int n = 0;
		while( n < mVector.size() ){
			cout << "[" << n + 1 << "] ";
			cout << mVector[n].name ;
			cout << ' ' << mVector[n].department ;
			cout << ' ' << mVector[n].type ;
			cout << ' ' << mVector[n].level ;
			cout << ' ' << mVector[n].graduateNum << endl;
			n++;
		} // while
		
		//----------------build heap-------------------
		for( ; hVector.size() < mVector.size() ;){				// till all match are in the heap 
			mVector[hVector.size()].heapNum = hVector.size();	// give the nodes in heap the number
			heapInsert( hVector, mVector[hVector.size()] );		// give heap vector and one info of matched school
		} // for
		
		
		//---------------------output-------------------
		cout << endl << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
		cout << "Mission Two: Build a Max Heap from the Selected Data" << endl;
		cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
		
		if( hVector.size() == 0 )
			cout << "###  There is nothing matchd!  ###" << endl;
		else{
			cout << endl << "<max heap>" << endl;
			cout << "root:[" << hVector[0].heapNum + 1 << "] "<< hVector[0].graduateNum << endl;
			cout << "bottom:[" << hVector[hVector.size() - 1].heapNum + 1 << "] " << hVector[hVector.size() - 1].graduateNum << endl;
		
			// use pow to find leftmost bottom
			int lmb = 0, judge = pow( 2, 1 ) - 1;		// lefrmost bottom, judge is lmb's next level
			n = 0;
			while( judge < hVector.size() ) {
				lmb = pow( 2, n ) - 1;
				judge = pow( 2, n+1 ) - 1;
				n++;
			} // while
			cout << "leftmost bottom:[" << hVector[lmb].heapNum + 1 << "] " << hVector[lmb].graduateNum << endl;
		} // else
		
		cout << endl << "*************************************" << endl;
		cout << "[0]Quit or [Any other]continue?" << endl;
		cin >> command;
	} // while
	
	return 0;
} // main()
 
void selectSchool( vector<school> &sVector, vector<school> &mVector, int schoolNum,
				 string sName, string sDep, string sType, string sLevel ) {
	int cnt = 0;
	char *sWord; // search for is sVector contain key or not
	while( cnt < schoolNum ) {
		sWord = strstr( sVector[cnt].name.c_str(), sName.c_str() );
		if( sName == "*" || sWord != NULL ){
			sWord = strstr( sVector[cnt].department.c_str(), sDep.c_str() );
			if( sDep == "*" || sWord != NULL ){
				sWord = strstr( sVector[cnt].type.c_str(), sType.c_str() );
				if( sType == "*" || sWord != NULL ){
					sWord = strstr( sVector[cnt].level.c_str(), sLevel.c_str() );
					if( sLevel == "*" || sWord != NULL ){
						mVector.push_back( sVector[cnt] );
					} // if
				} // if
			} // if
		} // if
		cnt++;
	} // while
} // void selectSchool()


void heapInsert( vector<school> &hVector, school item ){
	int place = hVector.size();		// alse equal bottom
	int parent = (place - 1) / 2;	// plase's parent
	hVector.push_back( item );		// add new item to bottom
	while( parent >= 0 && atoi( hVector[place].graduateNum.c_str() ) > atoi( hVector[parent].graduateNum.c_str() ) ){		// swap
		school temp = hVector[parent];
		hVector[parent] = hVector[place];
		hVector[place] = temp;
		place = parent;
		parent = (place - 1) / 2;
	} // while
} // void headInsert()
