`timescale 1ns/ 1ns
module ALU_32( a, b, sel, dataout, reset ) ;

input [31:0] a ;
input [31:0] b ;
input [5:0] sel ;
input reset ;
output wire [31:0] dataout ;


wire cin, inv,overflow ;
wire[31:0] cout, out,temp,slt ;

parameter less = 6'd42;

assign inv = (sel[1] == 1'b1) ?  1'b1 : 1'b0 ;

ALU alu0( .a(a[0]), .b(b[0]), .sel(sel), .out(out[0]), .cin(inv), .cout(cout[0]));
ALU alu1( .a(a[1]), .b(b[1]), .sel(sel), .out(out[1]), .cin(cout[0]), .cout(cout[1]));
ALU alu2( .a(a[2]), .b(b[2]), .sel(sel), .out(out[2]), .cin(cout[1]), .cout(cout[2]));
ALU alu3( .a(a[3]), .b(b[3]), .sel(sel), .out(out[3]), .cin(cout[2]), .cout(cout[3]));
ALU alu4( .a(a[4]), .b(b[4]), .sel(sel), .out(out[4]), .cin(cout[3]), .cout(cout[4]));
ALU alu5( .a(a[5]), .b(b[5]), .sel(sel), .out(out[5]), .cin(cout[4]), .cout(cout[5]));
ALU alu6( .a(a[6]), .b(b[6]), .sel(sel), .out(out[6]), .cin(cout[5]), .cout(cout[6]));
ALU alu7( .a(a[7]), .b(b[7]), .sel(sel), .out(out[7]), .cin(cout[6]), .cout(cout[7]));
ALU alu8( .a(a[8]), .b(b[8]), .sel(sel), .out(out[8]), .cin(cout[7]), .cout(cout[8]));
ALU alu9( .a(a[9]), .b(b[9]), .sel(sel), .out(out[9]), .cin(cout[8]), .cout(cout[9]));
ALU alu10( .a(a[10]), .b(b[10]), .sel(sel), .out(out[10]), .cin(cout[9]), .cout(cout[10]));
ALU alu11( .a(a[11]), .b(b[11]), .sel(sel), .out(out[11]), .cin(cout[10]), .cout(cout[11]));
ALU alu12( .a(a[12]), .b(b[12]), .sel(sel), .out(out[12]), .cin(cout[11]), .cout(cout[12]));
ALU alu13( .a(a[13]), .b(b[13]), .sel(sel), .out(out[13]), .cin(cout[12]), .cout(cout[13]));
ALU alu14( .a(a[14]), .b(b[14]), .sel(sel), .out(out[14]), .cin(cout[13]), .cout(cout[14]));
ALU alu15( .a(a[15]), .b(b[15]), .sel(sel), .out(out[15]), .cin(cout[14]), .cout(cout[15]));
ALU alu16( .a(a[16]), .b(b[16]), .sel(sel), .out(out[16]), .cin(cout[15]), .cout(cout[16]));
ALU alu17( .a(a[17]), .b(b[17]), .sel(sel), .out(out[17]), .cin(cout[16]), .cout(cout[17]));
ALU alu18( .a(a[18]), .b(b[18]), .sel(sel), .out(out[18]), .cin(cout[17]), .cout(cout[18]));
ALU alu19( .a(a[19]), .b(b[19]), .sel(sel), .out(out[19]), .cin(cout[18]), .cout(cout[19]));
ALU alu20( .a(a[20]), .b(b[20]), .sel(sel), .out(out[20]), .cin(cout[19]), .cout(cout[20]));
ALU alu21( .a(a[21]), .b(b[21]), .sel(sel), .out(out[21]), .cin(cout[20]), .cout(cout[21]));
ALU alu22( .a(a[22]), .b(b[22]), .sel(sel), .out(out[22]), .cin(cout[21]), .cout(cout[22]));
ALU alu23( .a(a[23]), .b(b[23]), .sel(sel), .out(out[23]), .cin(cout[22]), .cout(cout[23]));
ALU alu24( .a(a[24]), .b(b[24]), .sel(sel), .out(out[24]), .cin(cout[23]), .cout(cout[24]));
ALU alu25( .a(a[25]), .b(b[25]), .sel(sel), .out(out[25]), .cin(cout[24]), .cout(cout[25]));
ALU alu26( .a(a[26]), .b(b[26]), .sel(sel), .out(out[26]), .cin(cout[25]), .cout(cout[26]));
ALU alu27( .a(a[27]), .b(b[27]), .sel(sel), .out(out[27]), .cin(cout[26]), .cout(cout[27]));
ALU alu28( .a(a[28]), .b(b[28]), .sel(sel), .out(out[28]), .cin(cout[27]), .cout(cout[28]));
ALU alu29( .a(a[29]), .b(b[29]), .sel(sel), .out(out[29]), .cin(cout[28]), .cout(cout[29]));
ALU alu30( .a(a[30]), .b(b[30]), .sel(sel), .out(out[30]), .cin(cout[29]), .cout(cout[30]));
ALU alu31( .a(a[31]), .b(b[31]), .sel(sel), .out(out[31]), .cin(cout[30]), .cout(cout[31]));

xor(overflow,cout[30],cout[31]);


assign slt = ( out[31] == 1'b1 ) ? 32'd1 : 32'd0 ; // 判斷小於
assign dataout = ( reset == 1'b1 ) ? 32'd0 :
				( sel==less ) ? slt : out ;
             


endmodule
