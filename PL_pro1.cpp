# include <iostream>
# include <string>
# include <vector>
# include <ctype.h>
# include <sstream>
# include <stdlib.h>
# include <stdio.h>

using namespace std;

enum TokenType {
  EMPTY, LEFT_PAREN, RIGHT_PAREN, INT, FLOAT, DOT, NIL, T, QUOTE, STRING, SYMBOL // 0~10
};

enum NodeType {
  NODE_ATOM, NODE_QUOTE, NODE_INTERNAL, NODE_DOT
};

enum TreePath {
  PATH_LEFT, PATH_RIGHT, PATH_ROOT
};

// token的內容
class Token {
public:
  TokenType mType;
  string mTheToken;
  Token() {
    mType = EMPTY;
    mTheToken = "";
  } // Token() initial
};

class TreeNode {
public:
  TokenType mType;
  NodeType mNodeType;
  string mTheToken;

  TreeNode * mLeftNode;
  TreeNode * mRightNode;

  TreeNode() {
    mType = NIL;
    mNodeType = NODE_ATOM;
    mTheToken = "";
    mLeftNode = NULL;
    mRightNode = NULL;
  } // TreeNode() initial

  void EditNode( TokenType type, NodeType nodeType, string theToken ) {
    mType = type;
    mNodeType = nodeType;
    mTheToken = theToken;

    // 這個node不是leafnode，就new左右子樹
    if ( mNodeType != NODE_QUOTE && mNodeType != NODE_ATOM ) {
      mLeftNode = new TreeNode();
      mRightNode = new TreeNode();
    } // if()
  } // EditNode()
};

typedef Token * TokenPtr;
// 目前讀到哪
// 讀一個char就col+1、'\n'就row+1 & col = 0，s-exp讀完就reset( row = 1 & col = 0 )
int gRow = 1, gCol = 0;
bool gEOF = false, gSyntaxError = false;
bool gComment = false, gExit = false;
string gErrorMessage = "";
TokenPtr gCurrentToken = NULL;

bool IsSpace( char c ) {
  bool result = false;

  if ( c == ' ' || c == '\n' || c == '\t' || c == 't' )
    result = true;

  return result;
} // IsSpace()

bool IsFloat( string str ) {
  bool result = true;
  
  if ( str == "." || str == "+." || str == "-." )
    return false;

  // 前面有+ or -
  if ( ( str[0] == '+' || str[0] == '-' ) && str.length() >= 3 ) {
    // 從第二個char開始檢查
    for ( int i = 1 ; i < str.length() ; i++ ) {
      if ( str[i] == '.' )
        result = true;
      else if ( isdigit( str[i] ) == false ) { // 字串不是int or float
        result = false;
        i = str.length();
      } // else if()
    } // for()
  } // if()

  else
    for ( int i = 0 ; i < str.length() ; i++ ) {
      if ( str[i] == '.' )
        result = true;
      else if ( isdigit( str[i] ) == false ) { // 字串不是int or float
        result = false;
        i = str.length();
      } // else if()
    } // for()

  return result;
} // IsFloat()

bool IsInt( string str ) {
  bool result = true;

  // 前面有+ or -
  if ( ( str[0] == '+' || str[0] == '-' ) && str.length() >= 2 ) {
    // 從第二個char開始檢查
    for ( int i = 1 ; i < str.length() ; i++ ) {
      if ( isdigit( str[i] ) == false )
        result = false;
      // cout << result << endl;
    } // for()
  } // if()

  else
    for ( int i = 0 ; i < str.length() ; i++ ) {
      if ( isdigit( str[i] ) == false )
        result = false;
      // cout << result << endl;
    } // for()

  return result;
} // IsInt()

// get a char and calculate row&column
char GetChar() {
  int intC = '\0';

  intC = cin.peek();
  // EOF
  if ( intC == -1 ) {
    gEOF = true;
    gErrorMessage = "\n> ERROR (no more input) : END-OF-FILE encountered\n";
    return '\0';
  } // if()
  // 換行
  char c = ( char ) intC;
  if ( c == '\n' ) {
    c = cin.get();
    gCol = 0;
    gRow = gRow + 1;

    return c;
  } // if()
  // 正常繼續讀
  else {
    c = cin.get();
    gCol = gCol + 1;
    return c;
  } // else
} // GetChar()

// 是不是 ' ' or '(' or ')' or '\'' or '\"' or ';'
bool IsSeparator( char c ) {
  if ( isspace( c ) || c == '(' || c == ')' || c == '\'' || c == '\"' || c == ';' )
    return true;
  else
    return false;
} // IsSeparator()

// set token type
void SetTokenType( TokenPtr & currnetToken ) {
  // cout << "mTT " << currnetToken->mTheToken << endl; // test print
  if ( currnetToken->mTheToken == "\0" ) // 有error發生，所以才會是EMPTY
    currnetToken->mType = EMPTY;
  else if ( currnetToken->mTheToken == "(" )
    currnetToken->mType = LEFT_PAREN;
  else if ( currnetToken->mTheToken == ")" )
    currnetToken->mType = RIGHT_PAREN;
  else if ( IsInt( currnetToken->mTheToken ) == true )
    currnetToken->mType = INT;
  else if ( IsFloat( currnetToken->mTheToken ) == true )
    currnetToken->mType = FLOAT;
  else if ( currnetToken->mTheToken == "." )
    currnetToken->mType = DOT;
  else if ( currnetToken->mTheToken == "nil" || currnetToken->mTheToken == "#f" || 
            currnetToken->mTheToken == "()" )
    currnetToken->mType = NIL;
  else if ( currnetToken->mTheToken == "t" || currnetToken->mTheToken == "#t" )
    currnetToken->mType = T;
  else if ( currnetToken->mTheToken == "\'" )
    currnetToken->mType = QUOTE;
  else
    currnetToken->mType = SYMBOL;
} // SetTokenType()

// 讀string token-----------------------------------------------------------------
string GetStringInput() {
  string str = "";
  char c = '\0';

  // 開始讀string，直到遇到換行或close quote
  while ( cin.peek() != '\n' && cin.peek() != '\"' ) {
    c = GetChar();
    // escape character 'n', '"', 't', 或'\'
    if ( c == '\\' && ( cin.peek() == 'n' || cin.peek() == '\"' ||
                        cin.peek() == 't' || cin.peek() == '\\' ) ) {
      c = GetChar();
      if ( c == 'n' )
        str += "\n";
      else if ( c == '\"' )
        str += "\"";
      else if ( c == 't' )
        str += "\t";
      else if ( c == '\\' )
        str += "\\";
      else
        cout << "STRING ENCOUNT ERROR???" << endl;
    } // if()
    // 沒有escape
    else
      str += c;
  } // while()

  // 一個string完成
  if ( cin.peek() == '\"' ) {
    c = GetChar();
    str += c;
  } // if()
  // ERROR (no closing quote) : END-OF-LINE encountered at Line ? Column ?
  else {
    gRow --; // 遇到"\""前先遇到的\n
    gCol ++; // 這個才需要"\""

    stringstream sR, sC;
    sR << gRow; 
    sC << gCol;
    string tempR, tempC;
    sR >> tempR;
    sC >> tempC;
    // cout << " no closing quote :" << str << endl; // test print
    gSyntaxError = true;
    gErrorMessage = "\n> ERROR (no closing quote) : END-OF-LINE encountered at Line ";
    gErrorMessage += tempR;
    gErrorMessage += " Column ";
    gErrorMessage += tempC;
    gErrorMessage += "\n";
    c = GetChar(); // 讀掉 '\n'
  } // else if()

  return str;
} // GetStringInput()

// 如果遇到"則呼叫GetStringInput()，將之後的String讀成一個token，直到"或\n
TokenPtr GetToken() {
  TokenPtr currnetToken = new Token(); // current token
  char buf = '\0'; // catch GetChar()
  string str = "\0";

  // ------skip white-space------
  while ( isspace( cin.peek() ) && cin.peek() != -1 ) {
    buf = GetChar();
  } // while()
  // EOF
  if ( cin.peek() == -1 ) {
    gEOF = true;
    gErrorMessage = "\n> ERROR (no more input) : END-OF-FILE encountered\n";
    return NULL;
  } // if()
  // ------skip white-space------

  // start read the token's char
  while ( IsSeparator( cin.peek() ) == false && cin.peek() != -1 ) {
    buf = GetChar();
    str += buf;
  } // while()

  // EOF
  if ( cin.peek() == -1 ) {
    gEOF = true;
    gErrorMessage = "\n> ERROR (no more input) : END-OF-FILE encountered\n";
    return NULL;
  } // if()

  // 處理separator
  if ( cin.peek() == '(' || cin.peek() == ')' || cin.peek() == '\'' ) {
    // 如果此三個token沒有接在任何token後面，則自身為一個token，get完直接回傳
    // 如果接在目前token後面，則先把目前token做完，這三個token放著給下一次get
    if ( str.size() == 0 ) {
      buf = GetChar();
      str += buf;
    } // if()
  } // if()
  // 處理string
  else if ( cin.peek() == '\"' ) {
    buf = GetChar();
    str += buf; // 接上第一個"
    // 接上後續string跟"，若no close Quote則捨棄整行input
    str += GetStringInput();
    if ( str.at( str.length() - 1 ) != '\"' ) {
      str = "\0";
    } // if
    else {
      currnetToken->mType = STRING;
    } // else()
  } // else if()
  // 處理comment
  else if ( cin.peek() == ';' ) {
    // 讀掉comment直到換行
    buf = GetChar();
    while ( buf != '\n' ) {
      buf = GetChar();
    } // while()

    // 讀下一個token
    return GetToken();
  } // else if()

  currnetToken->mTheToken = str;
  if ( currnetToken->mType == EMPTY )
    SetTokenType( currnetToken );
  return currnetToken;
} // GetToken() ------讀入一個token後傳給readinput()------

// 如果gCurrentToken沒東西則get一個token進去，如果有東西則不變，再回傳
void PeekToken() {
  if ( gCurrentToken == NULL )
    gCurrentToken = GetToken();

  if ( gCurrentToken == NULL ) {
    gEOF = true;
    gErrorMessage = "\n> ERROR (no more input) : END-OF-FILE encountered\n";
  } // if()
} // PeekToken()

// 將gCurrentToken放入vector，並清空gCurrentToken
void PutCurrentTokenTo( vector<TokenPtr> & tokens ) {
  if ( gCurrentToken == NULL ) {
    return;
  } // if()

  tokens.push_back( gCurrentToken );
  gCurrentToken = NULL;
} // PutCurrentTokenTo()

void ReadAtom( vector<TokenPtr> & tokens ) {
  if ( gCurrentToken->mType == SYMBOL || gCurrentToken->mType == INT ||
       gCurrentToken->mType == FLOAT || gCurrentToken->mType == STRING ||
       gCurrentToken->mType == NIL || gCurrentToken->mType == T ) {
    PutCurrentTokenTo( tokens );
  } // if()

  else {
    stringstream sR, sC;
    sR << gRow;
    sC << gCol;
    string tempR, tempC;
    sR >> tempR;
    sC >> tempC;

    gSyntaxError = true;
    gErrorMessage = "\n> ERROR (unexpected token) : atom or '(' expected when token at Line ";
    gErrorMessage += tempR;
    gErrorMessage += " Column ";
    gErrorMessage += tempC;
    gErrorMessage += " is >>" + gCurrentToken->mTheToken + "<<\n";
  } // else
} // ReadAtom()

void ReadSExp( vector<TokenPtr> & tokens ) {
  // <ATOM> 
  // | LEFT-PAREN <S-exp> { <S-exp> } [ DOT <S-exp> ] RIGHT-PAREN
  // | QUOTE <S-exp>
  if ( gEOF != true && gSyntaxError != true )
    PeekToken();
  if ( gEOF == true || gSyntaxError == true ) return ;
  
  // ----------第一層 : <ATOM> || LEFT-PAREN || QUOTE----------
  if ( gCurrentToken->mType == LEFT_PAREN ) {
    PutCurrentTokenTo( tokens );

    // 如果下個token是')'，跟'('組成ATOM，如果不是則繼續往第二層
    PeekToken();
    if ( gEOF == true || gSyntaxError == true ) return ;
    if ( gCurrentToken->mType == RIGHT_PAREN ) {
      PutCurrentTokenTo( tokens );
      return;
    } // if()

    // ----------第二層 : <S-exp> ----------
    ReadSExp( tokens );
    if ( gEOF == true || gSyntaxError == true ) return ;
    // cout << " level 2 " << endl;

    // ----------第三之一層 : { <S-exp> } ----------
    PeekToken();
    if ( gEOF == true || gSyntaxError == true ) return ;

    while ( gCurrentToken != NULL &&
            ! ( gEOF == true || gSyntaxError == true ) && 
            gCurrentToken->mType != DOT && gCurrentToken->mType != RIGHT_PAREN ) {

      // cout << " level 3 " << endl;
      ReadSExp( tokens );
      PeekToken();
      if ( gEOF == true || gSyntaxError == true ) return ;
    } // while()

    // ----------第三之二層 : [ DOT <S-exp> ] ----------
    if ( gCurrentToken->mType == DOT ) {
      // cout << " DOT "; // test print
      PutCurrentTokenTo( tokens );
      ReadSExp( tokens );
      if ( gEOF == true || gSyntaxError == true ) return ;
    } // if()

    // ----------第四層 : RIGHT-PAREN ----------
    PeekToken();
    if ( gCurrentToken->mType == RIGHT_PAREN ) {
      PutCurrentTokenTo( tokens );
      return;
    } // if()

    // error : ')' expected
    else {
      stringstream sR, sC;
      sR << gRow;
      sC << gCol;
      string tempR, tempC;
      sR >> tempR;
      sC >> tempC;

      gSyntaxError = true;
      gErrorMessage = "\n> ERROR (unexpected token) : ')' expected when token at Line ";
      gErrorMessage += tempR;
      gErrorMessage += " Column ";
      gErrorMessage += tempC;
      gErrorMessage += " is >>" + gCurrentToken->mTheToken + "<<\n";
    } // else
  } // if()

  else if ( gCurrentToken->mType == QUOTE ) {
    PutCurrentTokenTo( tokens );
    ReadSExp( tokens );
  } // else if()

  else {
    // cout << "atom : " << gCurrentToken->mTheToken << endl; // test print
    ReadAtom( tokens );
  } // else
} // ReadSExp()

// tree-like data structure for this S-expression
// 每一個遞迴處理一個Token
void BuildTree( vector<TokenPtr> & tokens, TreeNode * currentNode,
                TreePath path, bool preDot, bool preQuote ) {
  // vector空了
  // cout << "Vsize:" << tokens.size() << "-- "; // test print
  if ( tokens.size() == 0 ) return;
  
  // 遇到"("，必須讀到對應的")"為止
  if ( tokens.at( 0 )->mType == LEFT_PAREN ) {
    // 如果下個token是")"，"()"組成ATOM node
    if ( tokens.size() >= 2 && tokens.at( 1 )->mType == RIGHT_PAREN ) {
      currentNode->EditNode( NIL, NODE_ATOM, "()" );
      tokens.erase( tokens.begin() );
      tokens.erase( tokens.begin() );
    } // if()

    // (s1 s2 ... sn)型態
    else {
      // 把currentNode設為"(" node (internal node)
      currentNode->EditNode( tokens.at( 0 )->mType, NODE_INTERNAL, tokens.at( 0 )->mTheToken );
      tokens.erase( tokens.begin() );

      // 繼續處理(裡面的東西)
      BuildTree( tokens, currentNode->mLeftNode, PATH_LEFT, false, false );
      if ( tokens.size() == 0 ) return;

      // next token 如果是 DOT 則currentNode設為DOT node (internal node)
      if ( tokens.at( 0 )->mType == DOT ) {
        currentNode->mNodeType = NODE_DOT; // LEFT_PAREN, DOT, "("
        tokens.erase( tokens.begin() );
        BuildTree( tokens, currentNode->mRightNode, PATH_RIGHT, true, false );
      } // if()

      // next token 不是 DOT
      else {
        BuildTree( tokens, currentNode->mRightNode, PATH_RIGHT, false, false ); 
      } // else

      if ( tokens.size() == 0 ) return;

      // 遇到RP，結束這個s-exp
      if ( tokens.at( 0 )->mType == RIGHT_PAREN ) {
        tokens.erase( tokens.begin() );
        return;
      } // if()
    } // else
  } // if()

  // 遇到QUOTE ; '... -> (QUOTE ...)
  // QUOTE後面接<s-exp>
  // Q放左子樹，然後往右繼續遞迴
  else if ( tokens.at( 0 )->mType == QUOTE ) {
    currentNode->mLeftNode->EditNode( tokens.at( 0 )->mType, NODE_QUOTE, tokens.at( 0 )->mTheToken );
    tokens.erase( tokens.begin() );
    BuildTree( tokens, currentNode->mRightNode, PATH_RIGHT, false, true );
  } // else if()

  // 理論上在右子樹遇到")"，設成nil(leafNode)
  else if ( tokens.at( 0 )->mType == RIGHT_PAREN ) {
    if ( path == PATH_LEFT ) {
      cout << "---encounter RP at left node---" ;
      return;
    } // if()

    currentNode->EditNode( NIL, NODE_ATOM, "nil" );
    tokens.erase( tokens.begin() );
  } // else if()

  // 遇到ATOM
  else {
    // 如果currentNode是左子樹 or Root，則將此ATOM放進此Node成為leafNode
    if ( path != PATH_RIGHT ) {
      currentNode->EditNode( tokens.at( 0 )->mType, NODE_ATOM, tokens.at( 0 )->mTheToken );
      tokens.erase( tokens.begin() );
    } // if()

    // currentNode是右子樹
    else {
      // 1.目前token前面有 DOT or QUOTE 則將此ATOM放進此Node成為leafNode
      if ( preDot == true || preQuote == true ) {
        currentNode->EditNode( tokens.at( 0 )->mType, NODE_ATOM, tokens.at( 0 )->mTheToken );
        tokens.erase( tokens.begin() );
      } // if()
      
      // 2.前面沒有 DOT or QUOTE 則currentNode設成internal node，然後 recursive
      else {
        currentNode->EditNode( EMPTY, NODE_INTERNAL, "" );
        BuildTree( tokens, currentNode->mLeftNode, PATH_LEFT, false, false );

        if ( tokens.size() == 0 ) return;

        // next token 如果是 DOT 則currentNode設為DOT node (internal node)
        if ( tokens.at( 0 )->mType == DOT ) {
          currentNode->mNodeType = NODE_DOT; // LEFT_PAREN, DOT, "("
          tokens.erase( tokens.begin() );
          BuildTree( tokens, currentNode->mRightNode, PATH_RIGHT, true, false );
        } // if()

        // next token 不是 DOT
        else {
          BuildTree( tokens, currentNode->mRightNode, PATH_RIGHT, false, false );
        } // else

        if ( tokens.size() == 0 ) return;

        // 遇到RP，結束這個s-exp
        if ( tokens.at( 0 )->mType == RIGHT_PAREN ) {
          tokens.erase( tokens.begin() );
          return;
        } // if()
      } // else
    } // else
  } // else
} // BuildTree()

void PrintTree( TreeNode * node, int m, TreePath path ) {
  if ( node == NULL ) return;

  // print atom
  if ( node->mNodeType == NODE_ATOM ) {
    if ( node->mType == INT ) {
      int tempI;
      tempI = atoi( node->mTheToken.c_str() );
      printf( "%d\n", tempI );
    } // if()

    else if ( node->mType == FLOAT ) {
      float tempF;
      tempF = atof( node->mTheToken.c_str() );
      printf( "%.3f\n", tempF );
    } // else if()

    // 不是數字
    else
      if ( node->mType == T )
        cout << "#t" << endl;
      else if ( node->mType == NIL )
        cout << "nil" << endl;
      else
        cout << node->mTheToken << endl;
  } // if()

  else {
    // 往左 or Root時遇到cons node印"("
    if ( path != PATH_RIGHT ) 
      cout << "( ";
    
    PrintTree( node->mLeftNode, m+2, PATH_LEFT ); // LEFT

    // print m+2 space & one DOT
    if ( node->mLeftNode->mNodeType == NODE_ATOM && node->mRightNode->mNodeType == NODE_ATOM
         && node->mRightNode->mType != NIL ) {
      for ( int n = 0 ; n < m+2 ; n++ ) 
        cout << " ";
      cout << "." << endl;
    } // if( DOT )

    // print m+2 space
    if ( node->mRightNode->mType != NIL )
      for ( int n = 0 ; n < m+2 ; n++ ) 
        cout << " ";

    // 右子樹的NIL不印
    if ( node->mRightNode->mType != NIL )
      PrintTree( node->mRightNode, m, PATH_RIGHT ); // RIGHT

    // 對應的")"
    if ( path != PATH_RIGHT ) {
      for ( int n = 0 ; n < m ; n++ ) 
        cout << " ";
      cout << ")" << endl;
    } // if()
  } // else
} // PrintTree()

// 看是不是(exit)了
bool CheckExit( TreeNode * root ) {
  if ( root->mLeftNode != NULL && root->mRightNode != NULL &&
       root->mLeftNode->mTheToken == "exit" && root->mRightNode->mType == NIL )
    return true;
  else
    return false;
} // CheckExit()

int main( ) {
  cout << "Welcome to OurScheme!" << endl;
  char testNum = '\0';
  while ( testNum != '\n' ) {
    testNum = cin.get();
  } // while()

  vector<TokenPtr> tokens;

  while ( gEOF != true && gExit != true ) {
    ReadSExp( tokens );

    if ( gSyntaxError || gEOF )
      cout << gErrorMessage;

    else {
      TreeNode * root = new TreeNode();
      BuildTree( tokens, root, PATH_ROOT, false, false );

      gExit = CheckExit( root );
      if ( gExit != true ) {
        cout << endl << "> ";
        PrintTree( root, 0, PATH_ROOT );
      } // if()
      
      else
        cout << endl << "> " << endl;
    } // else

    // reset
    gErrorMessage = "";
    gSyntaxError = false;
    gCurrentToken = NULL;
    gRow = 1, gCol = 0;

  } // while()

  cout << "Thanks for using OurScheme!";

  return 0;
} // main()
