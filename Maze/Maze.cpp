
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
	X y11[100]; // �g�c���� 
};

struct FootStack{  // �x�s���|�����| 
	int nowX ,nowY, delX[3], delY[3] ; // �ѹ��ثe����m �M ���R�L���`�I����m (�i��P�ɦ��T�Ӧ�m 
	int firstX, firstY, prevX, prevY; // �ѹ�����l �M �e�@�Ӥ�V 
	bool turned;
	FootStack *next;
};

FILE *fin, *fout;
Y x1[100]; // �ѹ������g�c 
Y x2[100]; // ��X�� 
Y x3[100]; // ��X�� 
Y x4[100]; // ��X�� 


vector<FootStack>  minFS ; // �ثe�̵u 
vector<FootStack>  nowFS ; // �ثe���b�ϥ� 



void PrintMaze( int numX, int numY, int command ) {
	
		// �s�@R�g�c 
	for( int n = 0 ; n < minFS.size()  ; n++ )
		if( x4[ minFS[n].nowX ].y11[ minFS[n].nowY ].c == 'E' )
			x4[ minFS[n].nowX ].y11[ minFS[n].nowY ].c = 'R';
			
	printf( "%d  %d\n\n\n", numX, numY );
		
		// ��X��l�g�c 
	for( int y = 0; y < numY; y++ )
		for( int x = 0; x < numX ; x++ ) {
			printf( "%c", x2[x].y11[y].c );
			if( x == numX - 1 )
				printf( "\n" );
		} // for
		
	printf( "\n\n" );
	
		// ��XV�g�c 
	for( int y = 0; y < numY; y++ )
		for( int x = 0; x < numX ; x++ ) {
			printf( "%c", x3[x].y11[y].c );
			if( x == numX - 1 )
				printf( "\n" );
		} // for

	printf( "\n\n" );


		// ��XR�g�c 
	for( int y = 0; y < numY; y++ )
		for( int x = 0; x < numX ; x++ ) {
			printf( "%c", x4[x].y11[y].c );
			if( x == numX - 1 )
				printf( "\n" );
		} // for
		
	printf( "\n\n" );

		
		// ��Xstack 
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
	// �̥k�U���W�����ǧ�A��쪺�Ĥ@�����|���s�bminFS��
	FootStack temp, tempG;
	temp.nowX = 0, temp.nowY = 0, temp.delX[0] = -1, temp.delY[0] = -1, temp.delX[1] = -1, temp.delY[1] = -1, temp.delX[2] = -1, temp.delY[2] = -1;
	temp.firstX = 1, temp.firstY = 0, temp.prevX = 1, temp.prevY = 0;
	temp.turned = false;
	temp.next = NULL;
	nowFS.push_back( temp );
	
	int n = 0;
	while( nowFS.empty() != true){ // �C���@�B�N�s�bstack�̡A�U�`�I���|�Ӥ�V�����L�F�N�R���A����R�� 

		if( nowFS.back().nowX + nowFS.back().prevX == nowFS.back().delX[0] &&
			nowFS.back().nowY + nowFS.back().prevY == nowFS.back().delY[0] ) { // ���R�L���`�I����L�h 
			nowFS.back().turned = true;
		
			if( nowFS.back().prevX == 1 && nowFS.back().prevY == 0  )
				nowFS.back().prevX = 0, nowFS.back().prevY = 1;
			else if( nowFS.back().prevX == 0 && nowFS.back().prevY == 1  )
				nowFS.back().prevX = -1, nowFS.back().prevY = 0;
			else if( nowFS.back().prevX == -1 && nowFS.back().prevY == 0  )
				nowFS.back().prevX = 0, nowFS.back().prevY = -1;
			else if( nowFS.back().prevX == 0 && nowFS.back().prevY == -1  )
				nowFS.back().prevX = 1, nowFS.back().prevY = 0;
				
			if( nowFS.back().turned == true && nowFS.back().prevX == nowFS.back().firstX && nowFS.back().prevY == nowFS.back().firstY ){ // �|�Ӥ�V�䧹�F
				x1[ nowFS.back().nowX ].y11[ nowFS.back().nowY ].c = 'E';
			
				if( nowFS[nowFS.size()-2].delX[0] == -1 && nowFS[nowFS.size()-2].delY[0] == -1 )
					nowFS[nowFS.size()-2].delX[0] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[0] = nowFS.back().nowY; // ��R�����`�I����m�O�b�˼ƲĤG�Ӹ`�I
				else if( nowFS[nowFS.size()-2].delX[1] == -1 && nowFS[nowFS.size()-2].delY[1] == -1 )
					nowFS[nowFS.size()-2].delX[1] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[1] = nowFS.back().nowY;
				else
					nowFS[nowFS.size()-2].delX[2] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[2] = nowFS.back().nowY;
				
				//printf( "pop1.1 :%d %d\n", nowFS.back().nowX, nowFS.back().nowY );   // test
				nowFS.pop_back();
			} // if
		} // if
		
		else if( nowFS.back().nowX + nowFS.back().prevX == nowFS.back().delX[1] &&
			nowFS.back().nowY + nowFS.back().prevY == nowFS.back().delY[1] ) { // ���R�L���`�I����L�h 
			nowFS.back().turned = true;
		
			if( nowFS.back().prevX == 1 && nowFS.back().prevY == 0  )
				nowFS.back().prevX = 0, nowFS.back().prevY = 1;
			else if( nowFS.back().prevX == 0 && nowFS.back().prevY == 1  )
				nowFS.back().prevX = -1, nowFS.back().prevY = 0;
			else if( nowFS.back().prevX == -1 && nowFS.back().prevY == 0  )
				nowFS.back().prevX = 0, nowFS.back().prevY = -1;
			else if( nowFS.back().prevX == 0 && nowFS.back().prevY == -1  )
				nowFS.back().prevX = 1, nowFS.back().prevY = 0;
				
			if( nowFS.back().turned == true && nowFS.back().prevX == nowFS.back().firstX && nowFS.back().prevY == nowFS.back().firstY ){ // �|�Ӥ�V�䧹�F
				x1[ nowFS.back().nowX ].y11[ nowFS.back().nowY ].c = 'E';
			
				if( nowFS[nowFS.size()-2].delX[0] == -1 && nowFS[nowFS.size()-2].delY[0] == -1 )
					nowFS[nowFS.size()-2].delX[0] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[0] = nowFS.back().nowY; // ��R�����`�I����m�O�b�˼ƲĤG�Ӹ`�I
				else if( nowFS[nowFS.size()-2].delX[1] == -1 && nowFS[nowFS.size()-2].delY[1] == -1 )
					nowFS[nowFS.size()-2].delX[1] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[1] = nowFS.back().nowY;
				else
					nowFS[nowFS.size()-2].delX[2] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[2] = nowFS.back().nowY;
				
				//printf( "pop1.2 :%d %d\n", nowFS.back().nowX, nowFS.back().nowY );  // test
				nowFS.pop_back();
			} // if
		} // if
		
		else if( nowFS.back().nowX + nowFS.back().prevX == nowFS.back().delX[2] &&
			nowFS.back().nowY + nowFS.back().prevY == nowFS.back().delY[2] ) { // ���R�L���`�I����L�h 
			nowFS.back().turned = true;
		
			if( nowFS.back().prevX == 1 && nowFS.back().prevY == 0  )
				nowFS.back().prevX = 0, nowFS.back().prevY = 1;
			else if( nowFS.back().prevX == 0 && nowFS.back().prevY == 1  )
				nowFS.back().prevX = -1, nowFS.back().prevY = 0;
			else if( nowFS.back().prevX == -1 && nowFS.back().prevY == 0  )
				nowFS.back().prevX = 0, nowFS.back().prevY = -1;
			else if( nowFS.back().prevX == 0 && nowFS.back().prevY == -1  )
				nowFS.back().prevX = 1, nowFS.back().prevY = 0;
				
			if( nowFS.back().turned == true && nowFS.back().prevX == nowFS.back().firstX && nowFS.back().prevY == nowFS.back().firstY ){ // �|�Ӥ�V�䧹�F
				x1[ nowFS.back().nowX ].y11[ nowFS.back().nowY ].c = 'E';
			
				if( nowFS[nowFS.size()-2].delX[0] == -1 && nowFS[nowFS.size()-2].delY[0] == -1 )
					nowFS[nowFS.size()-2].delX[0] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[0] = nowFS.back().nowY; // ��R�����`�I����m�O�b�˼ƲĤG�Ӹ`�I
				else if( nowFS[nowFS.size()-2].delX[1] == -1 && nowFS[nowFS.size()-2].delY[1] == -1 )
					nowFS[nowFS.size()-2].delX[1] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[1] = nowFS.back().nowY;
				else
					nowFS[nowFS.size()-2].delX[2] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[2] = nowFS.back().nowY;
				
				nowFS.pop_back();
			} // if
		} // if
		
			
		else if( nowFS.back().nowX + nowFS.back().prevX >= 0 && nowFS.back().nowY + nowFS.back().prevY >= 0 &&
			nowFS.back().nowX + nowFS.back().prevX < numX && nowFS.back().nowY + nowFS.back().prevY < numY &&
			x1[ nowFS.back().nowX + nowFS.back().prevX ].y11[ nowFS.back().nowY + nowFS.back().prevY ].c == 'E' ) { // ���� 
			
			x1[ nowFS.back().nowX + nowFS.back().prevX ].y11[ nowFS.back().nowY + nowFS.back().prevY ].c = 'R'; // �����ثe����m 
			x3[ nowFS.back().nowX + nowFS.back().prevX ].y11[ nowFS.back().nowY + nowFS.back().prevY ].c = 'V'; // ��¿�X�ΰg�c 
			
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
				 x1[ nowFS.back().nowX + nowFS.back().prevX ].y11[ nowFS.back().nowY + nowFS.back().prevY ].c == 'G' ){ // �I��O,R,G,��ɪ��ɭ���V 
				 
			if( x1[ nowFS.back().nowX + nowFS.back().prevX ].y11[ nowFS.back().nowY + nowFS.back().prevY ].c == 'G' ) { // ���G�N��ثe�����|�ƻs��̤p�����|�A�A��G�[��̫�@�Ӹ`�I 
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
				

				
			if( nowFS.back().turned == true && nowFS.back().prevX == nowFS.back().firstX && nowFS.back().prevY == nowFS.back().firstY ){ // �|�Ӥ�V�䧹�F
				x1[ nowFS.back().nowX ].y11[ nowFS.back().nowY ].c = 'E';
			
				if( nowFS[nowFS.size()-2].delX[0] == -1 && nowFS[nowFS.size()-2].delY[0] == -1 )
					nowFS[nowFS.size()-2].delX[0] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[0] = nowFS.back().nowY; // ��R�����`�I����m�O�b�˼ƲĤG�Ӹ`�I
				else if( nowFS[nowFS.size()-2].delX[1] == -1 && nowFS[nowFS.size()-2].delY[1] == -1 )
					nowFS[nowFS.size()-2].delX[1] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[1] = nowFS.back().nowY;
				else
					nowFS[nowFS.size()-2].delX[2] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[2] = nowFS.back().nowY;
				
				//printf( "pop2 :%d %d\n", nowFS.back().nowX, nowFS.back().nowY );  // test
				nowFS.pop_back();

				//printf( "pop :%d\n", nowFS.back().nowX );  // test
			} // if
		} // else if
		
		if( minFS.size() != 0 && nowFS.size() >= minFS.size() ) { // ���p��̵u�Z�� 
			x1[ nowFS.back().nowX ].y11[ nowFS.back().nowY ].c = 'E';
			
			if( nowFS[nowFS.size()-2].delX[0] == -1 && nowFS[nowFS.size()-2].delY[0] == -1 )
				nowFS[nowFS.size()-2].delX[0] = nowFS.back().nowX, nowFS[nowFS.size()-2].delY[0] = nowFS.back().nowY; // ��n�R�����`�I����m�O�b�˼ƲĤG�Ӹ`�I
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
	
	minFS.push_back( tempG ); // �NG�[�J�̫᪺�`�I 
	PrintMaze( numX, numY, command );  
} // void FindShortest()





void save (int numX, int numY, int command) {   // ����1  num1.num2 ���O�Oxy����  ------�s�g�c
	int x = 0, y = 0;
	char e; // ����
	fscanf(fin, "%c", &e);
	while (y < numY){
		while (x < numX){
			fscanf(fin, "%c", &x1[x].y11[y].c);
			x++;
		} // while
		x = 0;
		fscanf(fin, "%c", &e); // Ū������
		y++;
		printf("\n");
	} // while
	
	// �ƻs�T�Ӱg�c�Ӱ���X 
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
		if ( command == 1 || command == 2 ){  // �q���W�����쭹�����@�����|
			all maze;
			cout << endl << "Input a file <e.g.,411, 421>: ";
			cin >> str1; // scanf("%s", &str1);
			// if (str1 == NULL) cout << str1 << ".txt does not exist!";
			strcpy(str, "input");
			strcat(str, str1);
			strcat(str, ".txt");
			maze.fin = fopen(str, "rt");
			fscanf(maze.fin, "%d", &num1);  // �g�c�����μe 
			fscanf(maze.fin, "%d", &num2);  // �P�W 
			
			maze.save(num1, num2, command);  // �s�g�c
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
