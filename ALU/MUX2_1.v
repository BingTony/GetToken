`timescale 1ns/1ns
module Mux2_1( org, adv, sel, out ) ;

input org, adv, sel ;
output wire out ;


assign out = ( sel == 1 ) ? adv : org ;

endmodule 
