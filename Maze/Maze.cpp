
#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>

using namespace std;


class all {
public:
struct Node{
	int xnum, ynum;
	Node*next;
};

struct X{
	char c;
};

struct Y{
	X y11[100]; // 迷宮本身 
};

struct FootStack{  // 儲存路徑的堆疊 
	int nowX ,nowY, delX[3], delY[3] ; // 老鼠目前的位置 和 剛剛刪過的節點的位置 (可能同時有三個位置 
	int firstX, firstY, prevX, prevY; // 老鼠的初始 和 前一個方向 
	bool turned;
	FootStack *next;
};

FILE *fin, *fout;
Y x1[100]; // 老鼠走的迷宮 
Y x2[100]; // 輸出用 
Y x3[100]; // 輸出用 
Y x4[100]; // 輸出用 


vector<FootStack>  minFS ; // 目前最短 
vector<FootStack>  nowFS ; // 目前正在使用 



void PrintMaze( int numX, int numY, int command ) {
	
		// 製作R迷宮 
	for( int n = 0 ; n < minFS.size()  ; n++ )
		if( x4[ minFS[n].nowX ].y11[ minFS[n].nowY ].c == 'E' )
			x4[ minFS[n].nowX ].y11[ minFS[n].nowY ].c = 'R';
			
	printf( "%d  %d\n\n\n", numX, numY );
		
		// 輸出原始迷宮 
	for( int y = 0; y < numY; y++ )
		for( int x = 0; x < numX ; x++ ) {
			printf( "%c", x2[x].y11[y].c );
			if( x == numX - 1 )
				printf( "\n" );
		} // for
		
	printf( "\n\n" );
	
		// 輸出V迷宮 
	for( int y = 0; y < numY; y++ )
		for( int x = 0; x < numX ; x++ ) {
			printf( "%c", x3[x].y11[y].c );
			if( x == numX - 1 )
				printf( "\n" );
		} // for

	printf( "\n\n" );


		// 輸出R迷宮 
	for( int y = 0; y < numY; y++ )
		for( int x = 0; x < numX ; x++ ) {
			printf( "%c", x4[x].y11[y].c );
			if( x == numX - 1 )
				printf( "\n" );
		} // for
		
	printf( "\n\n" );

		
		// 輸出stack 
	if( command == 1 )
		printf( "Shortest path length = %d\n", minFS.size() );
		
	else{
	printf( "The shortest path to the nearest goal is as follows:\n" );
	for( int n = 0; n < minFS.size() ; n++ )
		printf( "[%d]( %d,%d )\n", n + 1, minFS[n].nowX + 1, minFS[n].nowY + 1 );
	} // else
	
	printf( "\n\n" );
} // void PrintMaze()


void FindShortest( int numX, int numY, int command ){
	// 依右下左上的順序找，找到的第一條路徑先存在minFS裡
	FootStack temp, tempG;
	temp.nowX = 0, temp.nowY = 0, temp.delX[0] = -1, temp.delY[0] = -1, temp.delX[1] = -1, temp.delY[1] = -1, temp.delX[2] = -1, temp.delY[2] = -1;
	temp.firstX = 1, temp.firstY = 0, temp.prevX = 1, temp.prevY = 0;
	temp.turned = false;
	temp.next = NULL;
	nowFS.push_back( temp );
	
	int n = 0;
	while( nowFS.empty() != true){ // 每走一步就存在stack裡，各節點的四個方向都走過了就刪掉，直到刪完 

		if( nowFS.back().nowX + nowFS.back().prevX == nowFS.back().delX[0] &&
			nowFS.back().nowY + nowFS.back().prevY == nowFS.back().delY[0] ) { // 剛剛刪過的節點不能過去 
			nowFS.back().turned = true;
		
			if( nowFS.back().prevX == 1 && nowFS.back().prevY == 0  )
				nowFS.back().prevX = 0, nowFS.back().prevY = 1;
			else if( nowFS.back().prevX == 0 && nowFS.back().prevY == 1  )
				nowFS.back().prevX = -1, nowFS.back().prevY = 0;
			else if( nowFS.back().prevX == -1 && nowFS.back().prevY == 0  )
				nowFS.back().prevX = 0, nowFS.back().prevY = -1;
			else if( nowFS.back().prevX == 0 && nowFS.back().prevY == -1  )
				nowFS.back().prevX = 1, nowFS.back().prevY = 0;
				
			if( nowFS.back().turned == true && nowFS.back().prevX == nowFS.back().firstX && nowFS.back().prevY == nowFS.back().firstY ){ // 四個方向找完了
				x1[ nowFS.back().nowX ].y11[ nowFS.back().nowY ].c = 'E';
			
				if( nowFS[nowFS.size()-2].delX[0] == -1 && nowFS[nowFS.size()-2].delY[0] == -1 )
					nowFS[nowFS.size()-2].delX[0] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[0] = nowFS.back().nowY; // 把刪掉的節點的位置記在倒數第二個節點
				else if( nowFS[nowFS.size()-2].delX[1] == -1 && nowFS[nowFS.size()-2].delY[1] == -1 )
					nowFS[nowFS.size()-2].delX[1] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[1] = nowFS.back().nowY;
				else
					nowFS[nowFS.size()-2].delX[2] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[2] = nowFS.back().nowY;
				
				//printf( "pop1.1 :%d %d\n", nowFS.back().nowX, nowFS.back().nowY );   // test
				nowFS.pop_back();
			} // if
		} // if
		
		else if( nowFS.back().nowX + nowFS.back().prevX == nowFS.back().delX[1] &&
			nowFS.back().nowY + nowFS.back().prevY == nowFS.back().delY[1] ) { // 剛剛刪過的節點不能過去 
			nowFS.back().turned = true;
		
			if( nowFS.back().prevX == 1 && nowFS.back().prevY == 0  )
				nowFS.back().prevX = 0, nowFS.back().prevY = 1;
			else if( nowFS.back().prevX == 0 && nowFS.back().prevY == 1  )
				nowFS.back().prevX = -1, nowFS.back().prevY = 0;
			else if( nowFS.back().prevX == -1 && nowFS.back().prevY == 0  )
				nowFS.back().prevX = 0, nowFS.back().prevY = -1;
			else if( nowFS.back().prevX == 0 && nowFS.back().prevY == -1  )
				nowFS.back().prevX = 1, nowFS.back().prevY = 0;
				
			if( nowFS.back().turned == true && nowFS.back().prevX == nowFS.back().firstX && nowFS.back().prevY == nowFS.back().firstY ){ // 四個方向找完了
				x1[ nowFS.back().nowX ].y11[ nowFS.back().nowY ].c = 'E';
			
				if( nowFS[nowFS.size()-2].delX[0] == -1 && nowFS[nowFS.size()-2].delY[0] == -1 )
					nowFS[nowFS.size()-2].delX[0] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[0] = nowFS.back().nowY; // 把刪掉的節點的位置記在倒數第二個節點
				else if( nowFS[nowFS.size()-2].delX[1] == -1 && nowFS[nowFS.size()-2].delY[1] == -1 )
					nowFS[nowFS.size()-2].delX[1] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[1] = nowFS.back().nowY;
				else
					nowFS[nowFS.size()-2].delX[2] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[2] = nowFS.back().nowY;
				
				//printf( "pop1.2 :%d %d\n", nowFS.back().nowX, nowFS.back().nowY );  // test
				nowFS.pop_back();
			} // if
		} // if
		
		else if( nowFS.back().nowX + nowFS.back().prevX == nowFS.back().delX[2] &&
			nowFS.back().nowY + nowFS.back().prevY == nowFS.back().delY[2] ) { // 剛剛刪過的節點不能過去 
			nowFS.back().turned = true;
		
			if( nowFS.back().prevX == 1 && nowFS.back().prevY == 0  )
				nowFS.back().prevX = 0, nowFS.back().prevY = 1;
			else if( nowFS.back().prevX == 0 && nowFS.back().prevY == 1  )
				nowFS.back().prevX = -1, nowFS.back().prevY = 0;
			else if( nowFS.back().prevX == -1 && nowFS.back().prevY == 0  )
				nowFS.back().prevX = 0, nowFS.back().prevY = -1;
			else if( nowFS.back().prevX == 0 && nowFS.back().prevY == -1  )
				nowFS.back().prevX = 1, nowFS.back().prevY = 0;
				
			if( nowFS.back().turned == true && nowFS.back().prevX == nowFS.back().firstX && nowFS.back().prevY == nowFS.back().firstY ){ // 四個方向找完了
				x1[ nowFS.back().nowX ].y11[ nowFS.back().nowY ].c = 'E';
			
				if( nowFS[nowFS.size()-2].delX[0] == -1 && nowFS[nowFS.size()-2].delY[0] == -1 )
					nowFS[nowFS.size()-2].delX[0] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[0] = nowFS.back().nowY; // 把刪掉的節點的位置記在倒數第二個節點
				else if( nowFS[nowFS.size()-2].delX[1] == -1 && nowFS[nowFS.size()-2].delY[1] == -1 )
					nowFS[nowFS.size()-2].delX[1] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[1] = nowFS.back().nowY;
				else
					nowFS[nowFS.size()-2].delX[2] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[2] = nowFS.back().nowY;
				
				nowFS.pop_back();
			} // if
		} // if
		
			
		else if( nowFS.back().nowX + nowFS.back().prevX >= 0 && nowFS.back().nowY + nowFS.back().prevY >= 0 &&
			nowFS.back().nowX + nowFS.back().prevX < numX && nowFS.back().nowY + nowFS.back().prevY < numY &&
			x1[ nowFS.back().nowX + nowFS.back().prevX ].y11[ nowFS.back().nowY + nowFS.back().prevY ].c == 'E' ) { // 走路 
			
			x1[ nowFS.back().nowX + nowFS.back().prevX ].y11[ nowFS.back().nowY + nowFS.back().prevY ].c = 'R'; // 紀錄目前的位置 
			x3[ nowFS.back().nowX + nowFS.back().prevX ].y11[ nowFS.back().nowY + nowFS.back().prevY ].c = 'V'; // 單純輸出用迷宮 
			
			temp.nowX = nowFS.back().nowX + nowFS.back().prevX, temp.nowY = nowFS.back().nowY + nowFS.back().prevY;
			temp.firstX = nowFS.back().prevX, temp.firstY = nowFS.back().prevY, temp.prevX = nowFS.back().prevX, temp.prevY = nowFS.back().prevY;
			temp.turned = false;
			temp.next = NULL;
			nowFS.push_back( temp );
			
		} // if
		
	
		
		else if( nowFS.back().nowX + nowFS.back().prevX >= 0 || nowFS.back().nowY + nowFS.back().prevY >= 0 ||
			     nowFS.back().nowX + nowFS.back().prevX < numX || nowFS.back().nowY + nowFS.back().prevY < numY ||
			 	 x1[ nowFS.back().nowX + nowFS.back().prevX ].y11[ nowFS.back().nowY + nowFS.back().prevY ].c == 'O' ||
				 x1[ nowFS.back().nowX + nowFS.back().prevX ].y11[ nowFS.back().nowY + nowFS.back().prevY ].c == 'R' ||
				 x1[ nowFS.back().nowX + nowFS.back().prevX ].y11[ nowFS.back().nowY + nowFS.back().prevY ].c == 'G' ){ // 碰到O,R,G,邊界的時候轉向 
				 
			if( x1[ nowFS.back().nowX + nowFS.back().prevX ].y11[ nowFS.back().nowY + nowFS.back().prevY ].c == 'G' ) { // 找到G就把目前的堆疊複製到最小的堆疊，再把G加到最後一個節點 
				minFS.assign( nowFS.begin(), nowFS.end() );
				tempG.nowX = nowFS.back().nowX + nowFS.back().prevX, tempG.nowY = nowFS.back().nowY + nowFS.back().prevY;
				
				//printf( "size : %d\n", minFS.size() ); // test
			} // if
				 
				 
			nowFS.back().turned = true;
		
			if( nowFS.back().prevX == 1 && nowFS.back().prevY == 0  )
				nowFS.back().prevX = 0, nowFS.back().prevY = 1;
			else if( nowFS.back().prevX == 0 && nowFS.back().prevY == 1  )
				nowFS.back().prevX = -1, nowFS.back().prevY = 0;
			else if( nowFS.back().prevX == -1 && nowFS.back().prevY == 0  )
				nowFS.back().prevX = 0, nowFS.back().prevY = -1;
			else if( nowFS.back().prevX == 0 && nowFS.back().prevY == -1  )
				nowFS.back().prevX = 1, nowFS.back().prevY = 0;
				

				
			if( nowFS.back().turned == true && nowFS.back().prevX == nowFS.back().firstX && nowFS.back().prevY == nowFS.back().firstY ){ // 四個方向找完了
				x1[ nowFS.back().nowX ].y11[ nowFS.back().nowY ].c = 'E';
			
				if( nowFS[nowFS.size()-2].delX[0] == -1 && nowFS[nowFS.size()-2].delY[0] == -1 )
					nowFS[nowFS.size()-2].delX[0] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[0] = nowFS.back().nowY; // 把刪掉的節點的位置記在倒數第二個節點
				else if( nowFS[nowFS.size()-2].delX[1] == -1 && nowFS[nowFS.size()-2].delY[1] == -1 )
					nowFS[nowFS.size()-2].delX[1] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[1] = nowFS.back().nowY;
				else
					nowFS[nowFS.size()-2].delX[2] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[2] = nowFS.back().nowY;
				
				//printf( "pop2 :%d %d\n", nowFS.back().nowX, nowFS.back().nowY );  // test
				nowFS.pop_back();

				//printf( "pop :%d\n", nowFS.back().nowX );  // test
			} // if
		} // else if
		
		if( minFS.size() != 0 && nowFS.size() >= minFS.size() ) { // 不小於最短距離 
			x1[ nowFS.back().nowX ].y11[ nowFS.back().nowY ].c = 'E';
			
			if( nowFS[nowFS.size()-2].delX[0] == -1 && nowFS[nowFS.size()-2].delY[0] == -1 )
				nowFS[nowFS.size()-2].delX[0] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[0] = nowFS.back().nowY; // 把要刪掉的節點的位置記在倒數第二個節點
			else if( nowFS[nowFS.size()-2].delX[1] == -1 && nowFS[nowFS.size()-2].delY[1] == -1 )
				nowFS[nowFS.size()-2].delX[1] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[1] = nowFS.back().nowY;
			else
				nowFS[nowFS.size()-2].delX[2] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[2] = nowFS.back().nowY;
				
			//printf( "pop3 :%d %d\n", nowFS.back().nowX, nowFS.back().nowY );  // test
			nowFS.pop_back();
			
		} // else if
		


		
		//printf( "%d  %d  %d  %d  %d %d %d\n", nowFS.size(), nowFS.back().nowX, nowFS.back().nowY, nowFS.back().prevX, nowFS.back().prevY, nowFS.back().delX[0], nowFS.back().delY[0] ); // test
		//print( numY, numX ); // test
		 n++;
	} // while
	
	minFS.push_back( tempG ); // 將G加入最後的節點 
	PrintMaze( numX, numY, command );  
} // void FindShortest()





void save (int numX, int numY, int command) {   // 任務1  num1.num2 分別是xy長度  ------存迷宮
	int x = 0, y = 0;
	char e; // 換行
	fscanf(fin, "%c", &e);
	while (y < numY){
		while (x < numX){
			fscanf(fin, "%c", &x1[x].y11[y].c);
			x++;
		} // while
		x = 0;
		fscanf(fin, "%c", &e); // 讀掉換行
		y++;
		printf("\n");
	} // while
	
	// 複製三個迷宮來做輸出 
	for( int y = 0; y < numY; y++ )
		for( int x = 0; x < numX ; x++ ) {
			x2[x].y11[y].c = x1[x].y11[y].c;
			x3[x].y11[y].c = x1[x].y11[y].c;
			x4[x].y11[y].c = x1[x].y11[y].c;
		} // for
		

	FindShortest( numX, numY, command );


} // save
};




int main(int argc, char *argv[]) {
	int command = 0, num1 = 0, num2 = 0;
	char str1[999], str[999];
	cout << "*** Path Finding ***" << endl;
	cout << "* 0. Quit          *" << endl;
	cout << "* 1. One goal      *" << endl;
	cout << "* 2. More goals    *" << endl;
	cout << "********************" << endl;
	cout << "Input a command(0, 1, 2):";

	cin >> command;
	while (command != 0){
		if ( command == 1 || command == 2 ){  // 從左上角走到食物的一條捷徑
			all maze;
			cout << endl << "Input a file <e.g.,411, 421>: ";
			cin >> str1; // scanf("%s", &str1);
			// if (str1 == NULL) cout << str1 << ".txt does not exist!";
			strcpy(str, "input");
			strcat(str, str1);
			strcat(str, ".txt");
			maze.fin = fopen(str, "rt");
			fscanf(maze.fin, "%d", &num1);  // 迷宮的長或寬 
			fscanf(maze.fin, "%d", &num2);  // 同上 
			
			maze.save(num1, num2, command);  // 存迷宮
		} // if

		cout << "*** Path Finding ***" << endl;
		cout << "* 0. Quit          *" << endl;
		cout << "* 1. One goal      *" << endl;
		cout << "* 2. More goals    *" << endl;
		cout << "********************" << endl;
		cout << "Input a command(0, 1, 2):";

		cin >> command;
	} // while
	
	system("PAUSE");
	return EXIT_SUCCESS;
} // main
