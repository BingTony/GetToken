`timescale 1ns/ 1ns
 module ALU(a, b, cin, cout,sel,out);

    input a, b,cin ;
	input[5:0] sel;
    output cout , out;
    
    wire   andout, orout, sumout, inv, bb; 
	assign inv = (sel[1] == 1'b1) ?  1'b1 : 1'b0 ; // 1 if SUB
	
	xor( bb, b, inv ); // bb is b's two's complement
	and(andout,a,b);
	or(orout,a,b);
	FA fifa(.a(a), .b(bb), .c(cin), .cout(cout), .sum(sumout));
	assign out =	( sel==6'b100100 ) ? andout : // op=36
					( sel==6'b100101 ) ? orout :  // op=37
					( sel==6'b100010 ) ? sumout : // SUB op=34
                    ( sel==6'b100000 ) ? sumout : // ADD op=32
                   
                        1'b0;

endmodule
