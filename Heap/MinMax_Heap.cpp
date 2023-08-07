#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <fstream>
#include <math.h>

using namespace std;

enum MinMax{ MIN, MAX };	// which level of mmheap

struct school {		// school info
	string name, department, type, level, graduateNum;
	int heapNum;
	MinMax mm;
}; // school

void readTXT( vector<school> &sVector, int &schoolNum );

void selectSchool( vector<school> &sVector, vector<school> &mVector, int schoolNum,
				 string sName, string sDep, string sType, string sLevel );
				 
void heapInsert( vector<school> &hVector, school item ); 

void mmHeapInsert( vector<school> &mmhVector, school item );
void mmHeapInsert_Sub( vector<school> &mmhVector, int place, int parent, int grandparent );

void mmHeapDelete( vector<school> &mmhVector, int count );

void mmHeapRebuild( vector<school> &mmhVector, int place, int child, int grandchild );


int main(int argc, char** argv) {
	
	
	vector<school> sVector;		// school vector
	vector<school> mVector;		// matched school
	vector<school> hVector;		// max heap of matched school
	vector<school> mmhVector;	// min-max heap of matched school
	
	int schoolNum = 0;		// number of school
	readTXT( sVector, schoolNum );
	
	//---------------------------start select and build heap-----------------------------
	string command;
	while( command != "0" ) {
		mVector.clear();
		hVector.clear();
		mmhVector.clear();
		
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
			cout << ", " << mVector[n].department ;
			cout << ", " << mVector[n].type ;
			cout << ", " << mVector[n].level ;
			cout << ", " << mVector[n].graduateNum << endl;
			n++;
		} // while
		
		/*
		//----------------build heap-------------------
		for( ; hVector.size() < mVector.size() ;){				// till all match are in the heap 
			mVector[hVector.size()].heapNum = hVector.size();	// give the nodes in heap the number
			heapInsert( hVector, mVector[hVector.size()] );		// give heap vector and one info of matched school
		} // for
		*/
		
		//----------------build mmheap-------------------
		for( ; mmhVector.size() < mVector.size() ;){
			mVector[mmhVector.size()].heapNum = mmhVector.size();	// give the nodes in heap the number
			mmHeapInsert( mmhVector, mVector[mmhVector.size()] );		// give heap vector and one info of matched school
		} // for

		
		//----------------mmheap print-------------------
		cout << endl << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
		cout << "Mission 1: Min-max Heap Construction" << endl;
		cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
		
		if( mmhVector.size() == 0 )
			cout << "###  There is nothing matchd!  ###" << endl;
		else{
			cout << "bottom:[" << mmhVector[mmhVector.size() - 1].heapNum + 1 << "] " << mmhVector[mmhVector.size() - 1].graduateNum << endl;
		
			// use pow to find leftmost bottom
			int lmb = 0, judge = pow( 2, 1 ) - 1;		// lefrmost bottom, judge is lmb's next level
			n = 0;
			while( judge < mmhVector.size() ) {
				lmb = pow( 2, n ) - 1;
				judge = pow( 2, n+1 ) - 1;
				n++;
			} // while
			cout << "leftmost bottom:[" << mmhVector[lmb].heapNum + 1 << "] " << mmhVector[lmb].graduateNum << endl;
		} // else
		
		
		//----------------mmheap delete-------------------
		if( mmhVector.size() != 0 ) {
			cout << endl << "Enter the value of K:" << endl << "[1..." << mmhVector.size() << "] : ";
			int keyValue;
			cin >> keyValue;
			cout << endl << "===================================================" << endl;
			cout << "Mission 2: Top-K maximums from min-max heap  (K=" << keyValue << ")" << endl;
			cout << "===================================================" << endl;
			
			int mmHsize = mmhVector.size();
			for( int i = 0; i < keyValue && i < mmHsize ; i++ )
				mmHeapDelete( mmhVector, i );
		} // if
		
		cout << endl << "*************************************" << endl;
		cout << "[0]Quit or [Any other]continue?" << endl;
		cin >> command;
		
		if( command == "0" )
			return 0;
			
		sVector.clear();
		schoolNum = 0;		// number of school
		readTXT( sVector, schoolNum );
	} // while
	
	return 0;
} // main()

void readTXT( vector<school> &sVector, int &schoolNum ){
	fstream fin;
	string fileName;
	
	while ( fin.is_open() != true ){		// read txt
		cout << "Input the file number: 201, 202 ... [0]Quit" << endl;
		cin >> fileName ;
		cout << endl;
	
		if( fileName == "0" )
			exit(0);
		
		fileName = "input" + fileName + ".txt" ;

		fin.open( fileName.c_str(), ios::in );
		if( fin.is_open() != true )
			cout << "### " << fileName << " does not exist! ### " << endl << endl;
	} // while
	
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
} // void readTXT()


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

void mmHeapInsert( vector<school> &mmhVector, school item ){
	int place = mmhVector.size();
	int parent = (place - 1) / 2;
	int grandparent = (parent - 1) / 2;
	int level = ( log2( place + 1 ) );	
	level = level % 2;
	//cout << level << ' ' << place << ' ' << parent << ' ' << grandparent << endl;		// test
	if( level == 0 )		// place is min or max level
		item.mm = MIN;
	else
		item.mm = MAX;
		
	mmhVector.push_back( item );
	mmHeapInsert_Sub( mmhVector, place, parent, grandparent );
	
} // void mmHeapInsert()

void mmHeapInsert_Sub( vector<school> &mmhVector, int place, int parent, int grandparent ){	// use for recursion
	if( parent < 0 )
		;
	else if( mmhVector[place].mm == MIN ){
		if( atoi( mmhVector[place].graduateNum.c_str() ) > atoi( mmhVector[parent].graduateNum.c_str() ) ){
			// place is MIN level and bigger than it's parent so swap
			//cout << "MIN:" << mmhVector[place].graduateNum << ' ' << mmhVector[parent].graduateNum << endl;
			school temp = mmhVector[parent];
			mmhVector[parent] = mmhVector[place];
			mmhVector[place] = temp;
			place = parent;
			parent = (place - 1) / 2;
			if( parent - 1 < 0 )				// -1 / 2 == 0.......
				grandparent = -1;
			else
				grandparent = (parent - 1) / 2;
			
			int level = ( log2( place + 1 ) );	
			level = level % 2;
			if( level == 0 )		// reset place is min or max level
				mmhVector[place].mm = MIN;
			else
				mmhVector[place].mm = MAX;
				
			level = ( log2( parent + 1 ) );	
			level = level % 2;
			if( level == 0 )		// reset parent is min or max level
				mmhVector[parent].mm = MIN;
			else
				mmhVector[parent].mm = MAX;
				
			mmHeapInsert_Sub( mmhVector, place, parent, grandparent );
		} // if
		
		else if( grandparent >= 0 && atoi( mmhVector[place].graduateNum.c_str() ) < atoi( mmhVector[grandparent].graduateNum.c_str() ) ){
			// place is MIN level but smaller than it's parent so check it's grandparent
			//cout << "GMIN:" << mmhVector[place].graduateNum << ' ' << mmhVector[grandparent].graduateNum << endl;
			school temp = mmhVector[grandparent];
			mmhVector[grandparent] = mmhVector[place];
			mmhVector[place] = temp;
			place = grandparent;
			parent = (place - 1) / 2;
			grandparent = (parent - 1) / 2;
			if( parent - 1 < 0 )				// -1 / 2 == 0.......
				grandparent = -1;
			else
				grandparent = (parent - 1) / 2;
			
			mmHeapInsert_Sub( mmhVector, place, parent, grandparent );
		} // else if
	} // else if
	
	else if( mmhVector[place].mm == MAX ){
		if( atoi( mmhVector[place].graduateNum.c_str() ) < atoi( mmhVector[parent].graduateNum.c_str() ) ){
			// place is MAX level and smaller than it's parent so swap
			//cout << "MAX:" << mmhVector[place].graduateNum << ' ' << mmhVector[parent].graduateNum << endl;
			school temp = mmhVector[parent];
			mmhVector[parent] = mmhVector[place];
			mmhVector[place] = temp;
			place = parent;
			parent = (place - 1) / 2;
			grandparent = (parent - 1) / 2;
			if( parent - 1 < 0 )				// -1 / 2 == 0.......
				grandparent = -1;
			else
				grandparent = (parent - 1) / 2;
			
			int level = ( log2( place + 1 ) );	
			level = level % 2;
			if( level == 0 )		// reset place is min or max level
				mmhVector[place].mm = MIN;
			else
				mmhVector[place].mm = MAX;
				
			level = ( log2( parent + 1 ) );	
			level = level % 2;
			if( level == 0 )		// reset parent is min or max level
				mmhVector[parent].mm = MIN;
			else
				mmhVector[parent].mm = MAX;
				
			mmHeapInsert_Sub( mmhVector, place, parent, grandparent );
		} // if
		
		else if( grandparent >= 0 && atoi( mmhVector[place].graduateNum.c_str() ) > atoi( mmhVector[grandparent].graduateNum.c_str() ) ){
			// place is MAX level but bigger than it's parent so check it's grandparent
			//cout << "GMAX:" << mmhVector[place].graduateNum << ' ' << mmhVector[grandparent].graduateNum << endl;
			school temp = mmhVector[grandparent];
			mmhVector[grandparent] = mmhVector[place];
			mmhVector[place] = temp;
			place = grandparent;
			parent = (place - 1) / 2;
			grandparent = (parent - 1) / 2;
			if( parent - 1 < 0 )				// -1 / 2 == 0.......
				grandparent = -1;
			else
				grandparent = (parent - 1) / 2;
			
			mmHeapInsert_Sub( mmhVector, place, parent, grandparent );
		} // else if
	} // else if
} // void mmHeapInsert_Sub()

void mmHeapDelete( vector<school> &mmhVector, int count ){
	//cout << "INTO DELETE" << endl;	// test
	if( mmhVector.size() == 1 ) {
		// mmH have only one node
		cout << "Top   " << count+1 << ":[" << mmhVector[0].heapNum + 1 << "] " << mmhVector[0].name << ", " << mmhVector[0].department;
		cout << ", " << mmhVector[0].type << ", " << mmhVector[0].level << ", " << mmhVector[0].graduateNum << endl;
		mmhVector.erase( mmhVector.begin() );					// delete bottom
	} // if
	
	else if( mmhVector.size() == 2 ) {
		// mmH have only two node
		cout << "Top   " << count+1 << ":[" << mmhVector[1].heapNum + 1 << "] " << mmhVector[1].name << ", " << mmhVector[1].department;
		cout << ", " << mmhVector[1].type << ", " << mmhVector[1].level << ", " << mmhVector[1].graduateNum << endl;
		mmhVector.erase( mmhVector.begin() + 1 );				// delete bottom
	} // if
	
	else{
		if( atoi ( mmhVector[1].graduateNum.c_str() ) >= atoi( mmhVector[2].graduateNum.c_str() ) ) {
			// node 2 bigger than node 3
			cout << "Top   " << count+1 << ":[" << mmhVector[1].heapNum + 1 << "] " << mmhVector[1].name << ", " << mmhVector[1].department;
			cout << ", " << mmhVector[1].type << ", " << mmhVector[1].level << ", " << mmhVector[1].graduateNum << endl;
			mmhVector[1] = mmhVector[mmhVector.size() - 1] ;	// copy bottom to place
			mmhVector[1].mm = MAX;								// reset MIN or MAX
			//cout << mmhVector[1].graduateNum << endl;			// test
			mmhVector.erase( mmhVector.end() );					// delete bottom
			mmHeapRebuild( mmhVector, 1, 2, 4 );				// rebuild
		} // if
		
		else{
			// node 3 bigger than node 2
			//cout << "node 3 bigger than node 2 print node3:" << mmhVector[2].graduateNum << endl;		// test
			cout << "Top   " << count+1 << ":[" << mmhVector[2].heapNum + 1 << "] " << mmhVector[2].name << ", " << mmhVector[2].department;
			cout << ", " << mmhVector[2].type << ", " << mmhVector[2].level << ", " << mmhVector[2].graduateNum << endl;
			mmhVector[2] = mmhVector[mmhVector.size() - 1] ;	// copy bottom to place
			mmhVector[2].mm = MAX;								// reset MIN or MAX
			mmhVector.erase( mmhVector.end() );					// delete bottom
			mmHeapRebuild( mmhVector, 2, 4, 8 );				// rebuild
		} // else
	} // else
} // void mmHeapDelete()

void mmHeapRebuild( vector<school> &mmhVector, int place, int child, int grandchild ){
	if( child > mmhVector.size() )
		;
	else if( mmhVector[place].mm == MIN ){
		// if place is MIN 
		//cout << "INTO MIN" << endl;	//test
		int smallest = -1;
		for( int i = 1 ; i < 3 && child + i < mmhVector.size() ; i++ ){	// find smallest child
			if( atoi( mmhVector[place].graduateNum.c_str() ) > atoi( mmhVector[child+i].graduateNum.c_str() ) )
				if( smallest == -1 )
					smallest = child + i;
				else if( atoi( mmhVector[child+i].graduateNum.c_str() ) < atoi( mmhVector[smallest].graduateNum.c_str() ) )
					smallest = child + i;
		} // for
		
		//cout << "smallest : " << smallest << endl;
		// if place > place's child so swap
		if( smallest != -1 ) {
			cout << "MIN" << smallest << endl;	//test
			school temp = mmhVector[smallest];
			mmhVector[smallest] = mmhVector[place];
			mmhVector[place] = temp;
			int placeOrigin = place, childOrigin = child, grandchildOrigin = grandchild;
			place = smallest;
			child = place * 2;
			grandchild = child * 2;
			
			int level = ( log2( placeOrigin + 1 ) );	
			level = level % 2;
			if( level == 0 )		// reset place is min or max level
				mmhVector[placeOrigin].mm = MIN;
			else
				mmhVector[placeOrigin].mm = MAX;
				
			level = ( log2( smallest + 1 ) );	
			level = level % 2;
			if( level == 0 )		// reset parent is min or max level
				mmhVector[smallest].mm = MIN;
			else					
				mmhVector[smallest].mm = MAX;
			
			mmHeapRebuild( mmhVector, placeOrigin, childOrigin, grandchildOrigin );
			mmHeapRebuild( mmhVector, place, child, grandchild );
		} // if
		
		else if( smallest == -1 ) {
			// if place < place's child so check place and place's grandchild
			// if one of place's grandchild < place then find the smallest one and swap
			smallest = -1;
			for( int i = 3 ; i < 7 && grandchild + i < mmhVector.size() ; i++ ){	// find smallest geandchild
				if( atoi( mmhVector[place].graduateNum.c_str() ) > atoi( mmhVector[grandchild + i].graduateNum.c_str() ) )
					if( smallest == -1 )
						smallest = grandchild + i;
					else if ( atoi( mmhVector[grandchild + i].graduateNum.c_str() ) < atoi( mmhVector[smallest].graduateNum.c_str() ) ){
						smallest = grandchild + i;
					} // else if
			} // for
			
			//cout << "Gsmallest :" << smallest << endl;
			// swap
			if( smallest != -1 ) {
				school temp = mmhVector[smallest];
				mmhVector[smallest] = mmhVector[place];
				mmhVector[place] = temp;
				int placeOrigin = place;
				place = smallest;
				child = place * 2;
				grandchild = child * 2;
			
				int level = ( log2( placeOrigin + 1 ) );	
				level = level % 2;
				if( level == 0 )		// reset place is min or max level
					mmhVector[placeOrigin].mm = MIN;
				else
					mmhVector[placeOrigin].mm = MAX;
				
				level = ( log2( smallest + 1 ) );	
				level = level % 2;
				if( level == 0 )		// reset parent is min or max level
					mmhVector[smallest].mm = MIN;
				else					
					mmhVector[smallest].mm = MAX;
				
				mmHeapRebuild( mmhVector, place, child, grandchild );
			} // if
		} // else if
	} // else if
	
	else if( mmhVector[place].mm == MAX ){
		// if place is MAX
		//cout << "INTO MAX" << endl;	//test
		int biggest = -1;
		for( int i = 1 ; i < 3 && child + i < mmhVector.size() ; i++ ){	// find biggest child
			if( atoi( mmhVector[place].graduateNum.c_str() ) < atoi( mmhVector[child+i].graduateNum.c_str() ) )
				if( biggest == -1 )
					biggest = child + i;
				else if( atoi( mmhVector[child+i].graduateNum.c_str() ) > atoi( mmhVector[biggest].graduateNum.c_str() ) )
					biggest = child + i;
		} // for

		// if place < place's child so swap
		if( biggest != -1 ) {
			//cout << "child : " << child << " biggest :" << biggest << endl;	//test
			school temp = mmhVector[biggest];
			mmhVector[biggest] = mmhVector[place];
			mmhVector[place] = temp;
			int placeOrigin = place, childOrigin = child, grandchildOrigin = grandchild;
			place = biggest;
			child = place * 2;
			grandchild = child * 2;
			
			int level = ( log2( placeOrigin + 1 ) );	
			level = level % 2;
			if( level == 0 )		// reset place is min or max level
				mmhVector[placeOrigin].mm = MIN;
			else
				mmhVector[placeOrigin].mm = MAX;
				
			level = ( log2( biggest + 1 ) );	
			level = level % 2;
			if( level == 0 )		// reset parent is min or max level
				mmhVector[biggest].mm = MIN;
			else					
				mmhVector[biggest].mm = MAX;
				
			
			
			mmHeapRebuild( mmhVector, placeOrigin, childOrigin, grandchildOrigin );
			mmHeapRebuild( mmhVector, place, child, grandchild );
		} // if
		
		else if( biggest == -1 ) {
			// if place > place's child so check place and place's grandchild
			// if one of place's grandchild > place then find the biggest one and swap
			biggest = -1;
			for( int i = 3 ; i < 7 && grandchild + i < mmhVector.size() ; i++ ){	// find smallest geandchild
				if( atoi( mmhVector[place].graduateNum.c_str() ) < atoi( mmhVector[grandchild + i].graduateNum.c_str() ) )
					if( biggest == -1 )
						biggest = grandchild + i;
					else if ( atoi( mmhVector[grandchild + i].graduateNum.c_str() ) > atoi( mmhVector[biggest].graduateNum.c_str() ) ){
						biggest = grandchild + i;
					} // else if
			} // for
			
			
			//cout << "grandchild : " << grandchild << " Gbiggest :" << biggest << endl;	// test
			// swap
			if( biggest != -1 ){
				school temp = mmhVector[biggest];
				mmhVector[biggest] = mmhVector[place];
				mmhVector[place] = temp;
				int placeOrigin = place;
				place = biggest;
				child = place * 2;
				grandchild = child * 2;
			
				int level = ( log2( placeOrigin + 1 ) );	
				level = level % 2;
				if( level == 0 )		// reset place is min or max level
					mmhVector[placeOrigin].mm = MIN;
				else
					mmhVector[placeOrigin].mm = MAX;
				
				level = ( log2( biggest + 1 ) );	
				level = level % 2;
				if( level == 0 )		// reset parent is min or max level
					mmhVector[biggest].mm = MIN;
				else					
					mmhVector[biggest].mm = MAX;
				
				mmHeapRebuild( mmhVector, place, child, grandchild );
			} // if
		} // else if
	} // else if
} // void mmHeapRebuild()







