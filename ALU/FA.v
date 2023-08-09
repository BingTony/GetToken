`timescale 1ns/1ns
module FA(a, b, c, cout, sum);

    input a, b, c;
    output  cout, sum;
  wire eog, e1, e2, e3 ;

  // cal sum
  xor( eog, a, b ) ;
  xor( sum, eog, c ) ;

  // carry out case1  
  or( e1, a, b ) ; // ********maybe xor?
  and( e2, e1, c ) ;
  // carry out case2
  and( e3, a, b ) ;  
  // one of case1/case2 = 1, we have carry out
  or( cout, e2, e3 ) ;

endmodule

