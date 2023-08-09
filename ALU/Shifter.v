`timescale 1ns/1ns
module Shifter( a, b, Signal, out, reset);
input reset ;
input [5:0] Signal;
input [31:0] a ;
input [31:0] b ;
output wire[31:0] out ;

wire [4:0] sel ;
assign sel = b ;


wire [31:0] lv1 ;
wire [31:0] lv2 ;
wire [31:0] lv3 ;
wire [31:0] lv4 ;
wire [31:0] lv5 ;




Mux2_1 lv1_1( a[31], a[30], sel[0], lv1[31] ) ;
Mux2_1 lv1_2( a[30], a[29], sel[0], lv1[30] ) ;
Mux2_1 lv1_3( a[29], a[28], sel[0], lv1[29] ) ;
Mux2_1 lv1_4( a[28], a[27], sel[0], lv1[28] ) ;
Mux2_1 lv1_5( a[27], a[26], sel[0], lv1[27] ) ;
Mux2_1 lv1_6( a[26], a[25], sel[0], lv1[26] ) ;
Mux2_1 lv1_7( a[25], a[24], sel[0], lv1[25] ) ;
Mux2_1 lv1_8( a[24], a[23], sel[0], lv1[24] ) ;
Mux2_1 lv1_9( a[23], a[22], sel[0], lv1[23] ) ;
Mux2_1 lv1_10( a[22], a[21], sel[0], lv1[22] ) ;
Mux2_1 lv1_11( a[21], a[20], sel[0], lv1[21] ) ;
Mux2_1 lv1_12( a[20], a[19], sel[0], lv1[20] ) ;
Mux2_1 lv1_13( a[19], a[18], sel[0], lv1[19] ) ;
Mux2_1 lv1_14( a[18], a[17], sel[0], lv1[18] ) ;
Mux2_1 lv1_15( a[17], a[16], sel[0], lv1[17] ) ;
Mux2_1 lv1_16( a[16], a[15], sel[0], lv1[16] ) ;
Mux2_1 lv1_17( a[15], a[14], sel[0], lv1[15] ) ;
Mux2_1 lv1_18( a[14], a[13], sel[0], lv1[14] ) ;
Mux2_1 lv1_19( a[13], a[12], sel[0], lv1[13] ) ;
Mux2_1 lv1_20( a[12], a[11], sel[0], lv1[12] ) ;
Mux2_1 lv1_21( a[11], a[10], sel[0], lv1[11] ) ;
Mux2_1 lv1_22( a[10], a[9], sel[0], lv1[10] ) ;
Mux2_1 lv1_23( a[9], a[8], sel[0], lv1[9] ) ;
Mux2_1 lv1_24( a[8], a[7], sel[0], lv1[8] ) ;
Mux2_1 lv1_25( a[7], a[6], sel[0], lv1[7] ) ;
Mux2_1 lv1_26( a[6], a[5], sel[0], lv1[6] ) ;
Mux2_1 lv1_27( a[5], a[4], sel[0], lv1[5] ) ;
Mux2_1 lv1_28( a[4], a[3], sel[0], lv1[4] ) ;
Mux2_1 lv1_29( a[3], a[2], sel[0], lv1[3] ) ;
Mux2_1 lv1_30( a[2], a[1], sel[0], lv1[2] ) ;
Mux2_1 lv1_31( a[1], a[0], sel[0], lv1[1] ) ;
Mux2_1 lv1_32( a[0], 1'b0, sel[0], lv1[0] ) ;


Mux2_1 lv2_1( lv1[31], lv1[29], sel[1], lv2[31] ) ;
Mux2_1 lv2_2( lv1[30], lv1[28], sel[1], lv2[30] ) ;
Mux2_1 lv2_3( lv1[29], lv1[27], sel[1], lv2[29] ) ;
Mux2_1 lv2_4( lv1[28], lv1[26], sel[1], lv2[28] ) ;
Mux2_1 lv2_5( lv1[27], lv1[25], sel[1], lv2[27] ) ;
Mux2_1 lv2_6( lv1[26], lv1[24], sel[1], lv2[26] ) ;
Mux2_1 lv2_7( lv1[25], lv1[23], sel[1], lv2[25] ) ;
Mux2_1 lv2_8( lv1[24], lv1[22], sel[1], lv2[24] ) ;
Mux2_1 lv2_9( lv1[23], lv1[21], sel[1], lv2[23] ) ;
Mux2_1 lv2_10( lv1[22], lv1[20], sel[1], lv2[22] ) ;
Mux2_1 lv2_11( lv1[21], lv1[19], sel[1], lv2[21] ) ;
Mux2_1 lv2_12( lv1[20], lv1[18], sel[1], lv2[20] ) ;
Mux2_1 lv2_13( lv1[19], lv1[17], sel[1], lv2[19] ) ;
Mux2_1 lv2_14( lv1[18], lv1[16], sel[1], lv2[18] ) ;
Mux2_1 lv2_15( lv1[17], lv1[15], sel[1], lv2[17] ) ;
Mux2_1 lv2_16( lv1[16], lv1[14], sel[1], lv2[16] ) ;
Mux2_1 lv2_17( lv1[15], lv1[13], sel[1], lv2[15] ) ;
Mux2_1 lv2_18( lv1[14], lv1[12], sel[1], lv2[14] ) ;
Mux2_1 lv2_19( lv1[13], lv1[11], sel[1], lv2[13] ) ;
Mux2_1 lv2_20( lv1[12], lv1[10], sel[1], lv2[12] ) ;
Mux2_1 lv2_21( lv1[11], lv1[9], sel[1], lv2[11] ) ;
Mux2_1 lv2_22( lv1[10], lv1[8], sel[1], lv2[10] ) ;
Mux2_1 lv2_23( lv1[9], lv1[7], sel[1], lv2[9] ) ;
Mux2_1 lv2_24( lv1[8], lv1[6], sel[1], lv2[8] ) ;
Mux2_1 lv2_25( lv1[7], lv1[5], sel[1], lv2[7] ) ;
Mux2_1 lv2_26( lv1[6], lv1[4], sel[1], lv2[6] ) ;
Mux2_1 lv2_27( lv1[5], lv1[3], sel[1], lv2[5] ) ;
Mux2_1 lv2_28( lv1[4], lv1[2], sel[1], lv2[4] ) ;
Mux2_1 lv2_29( lv1[3], lv1[1], sel[1], lv2[3] ) ;
Mux2_1 lv2_30( lv1[2], lv1[0], sel[1], lv2[2] ) ;
Mux2_1 lv2_31( lv1[1], 1'b0, sel[1], lv2[1] ) ;
Mux2_1 lv2_32( lv1[0], 1'b0, sel[1], lv2[0] ) ;


Mux2_1 lv3_1( lv2[31], lv2[27], sel[2], lv3[31] ) ;
Mux2_1 lv3_2( lv2[30], lv2[26], sel[2], lv3[30] ) ;
Mux2_1 lv3_3( lv2[29], lv2[25], sel[2], lv3[29] ) ;
Mux2_1 lv3_4( lv2[28], lv2[24], sel[2], lv3[28] ) ;
Mux2_1 lv3_5( lv2[27], lv2[23], sel[2], lv3[27] ) ;
Mux2_1 lv3_6( lv2[26], lv2[22], sel[2], lv3[26] ) ;
Mux2_1 lv3_7( lv2[25], lv2[21], sel[2], lv3[25] ) ;
Mux2_1 lv3_8( lv2[24], lv2[20], sel[2], lv3[24] ) ;
Mux2_1 lv3_9( lv2[23], lv2[19], sel[2], lv3[23] ) ;
Mux2_1 lv3_10( lv2[22], lv2[18], sel[2], lv3[22] ) ;
Mux2_1 lv3_11( lv2[21], lv2[17], sel[2], lv3[21] ) ;
Mux2_1 lv3_12( lv2[20], lv2[16], sel[2], lv3[20] ) ;
Mux2_1 lv3_13( lv2[19], lv2[15], sel[2], lv3[19] ) ;
Mux2_1 lv3_14( lv2[18], lv2[14], sel[2], lv3[18] ) ;
Mux2_1 lv3_15( lv2[17], lv2[13], sel[2], lv3[17] ) ;
Mux2_1 lv3_16( lv2[16], lv2[12], sel[2], lv3[16] ) ;
Mux2_1 lv3_17( lv2[15], lv2[11], sel[2], lv3[15] ) ;
Mux2_1 lv3_18( lv2[14], lv2[10], sel[2], lv3[14] ) ;
Mux2_1 lv3_19( lv2[13], lv2[9], sel[2], lv3[13] ) ;
Mux2_1 lv3_20( lv2[12], lv2[8], sel[2], lv3[12] ) ;
Mux2_1 lv3_21( lv2[11], lv2[7], sel[2], lv3[11] ) ;
Mux2_1 lv3_22( lv2[10], lv2[6], sel[2], lv3[10] ) ;
Mux2_1 lv3_23( lv2[9], lv2[5], sel[2], lv3[9] ) ;
Mux2_1 lv3_24( lv2[8], lv2[4], sel[2], lv3[8] ) ;
Mux2_1 lv3_25( lv2[7], lv2[3], sel[2], lv3[7] ) ;
Mux2_1 lv3_26( lv2[6], lv2[2], sel[2], lv3[6] ) ;
Mux2_1 lv3_27( lv2[5], lv2[1], sel[2], lv3[5] ) ;
Mux2_1 lv3_28( lv2[4], lv2[0], sel[2], lv3[4] ) ;
Mux2_1 lv3_29( lv2[3], 1'b0,sel[2], lv3[3] ) ;
Mux2_1 lv3_30( lv2[2], 1'b0, sel[2], lv3[2] ) ;
Mux2_1 lv3_31( lv2[1], 1'b0, sel[2], lv3[1] ) ;
Mux2_1 lv3_32( lv2[0], 1'b0, sel[2], lv3[0] ) ;


Mux2_1 lv4_1( lv3[31], lv3[23], sel[3], lv4[31] ) ;
Mux2_1 lv4_2( lv3[30], lv3[22], sel[3], lv4[30] ) ;
Mux2_1 lv4_3( lv3[29], lv3[21], sel[3], lv4[29] ) ;
Mux2_1 lv4_4( lv3[28], lv3[20], sel[3], lv4[28] ) ;
Mux2_1 lv4_5( lv3[27], lv3[19], sel[3], lv4[27] ) ;
Mux2_1 lv4_6( lv3[26], lv3[18], sel[3], lv4[26] ) ;
Mux2_1 lv4_7( lv3[25], lv3[17], sel[3], lv4[25] ) ;
Mux2_1 lv4_8( lv3[24], lv3[16], sel[3], lv4[24] ) ;
Mux2_1 lv4_9( lv3[23], lv3[15], sel[3], lv4[23] ) ;
Mux2_1 lv4_10( lv3[22], lv3[14], sel[3], lv4[22] ) ;
Mux2_1 lv4_11( lv3[21], lv3[13], sel[3], lv4[21] ) ;
Mux2_1 lv4_12( lv3[20], lv3[12], sel[3], lv4[20] ) ;
Mux2_1 lv4_13( lv3[19], lv3[11], sel[3], lv4[19] ) ;
Mux2_1 lv4_14( lv3[18], lv3[10], sel[3], lv4[18] ) ;
Mux2_1 lv4_15( lv3[17], lv3[9], sel[3], lv4[17] ) ;
Mux2_1 lv4_16( lv3[16], lv3[8], sel[3], lv4[16] ) ;
Mux2_1 lv4_17( lv3[15], lv3[7], sel[3], lv4[15] ) ;
Mux2_1 lv4_18( lv3[14], lv3[6], sel[3], lv4[14] ) ;
Mux2_1 lv4_19( lv3[13], lv3[5], sel[3], lv4[13] ) ;
Mux2_1 lv4_20( lv3[12], lv3[4], sel[3], lv4[12] ) ;
Mux2_1 lv4_21( lv3[11], lv3[3], sel[3], lv4[11] ) ;
Mux2_1 lv4_22( lv3[10], lv3[2], sel[3], lv4[10] ) ;
Mux2_1 lv4_23( lv3[9], lv3[1], sel[3], lv4[9] ) ;
Mux2_1 lv4_24( lv3[8], lv3[0], sel[3], lv4[8] ) ;
Mux2_1 lv4_25( lv3[7], 1'b0, sel[3], lv4[7] ) ;
Mux2_1 lv4_26( lv3[6], 1'b0, sel[3], lv4[6] ) ;
Mux2_1 lv4_27( lv3[5], 1'b0, sel[3], lv4[5] ) ;
Mux2_1 lv4_28( lv3[4], 1'b0, sel[3], lv4[4] ) ;
Mux2_1 lv4_29( lv3[3], 1'b0, sel[3], lv4[3] ) ;
Mux2_1 lv4_30( lv3[2], 1'b0, sel[3], lv4[2] ) ;
Mux2_1 lv4_31( lv3[1], 1'b0, sel[3], lv4[1] ) ;
Mux2_1 lv4_32( lv3[0], 1'b0, sel[3], lv4[0] ) ;



Mux2_1 lv5_1( lv4[31], lv4[15], sel[4], lv5[31] ) ;
Mux2_1 lv5_2( lv4[30], lv4[14], sel[4], lv5[30] ) ;
Mux2_1 lv5_3( lv4[29], lv4[13], sel[4], lv5[29] ) ;
Mux2_1 lv5_4( lv4[28], lv4[12], sel[4], lv5[28] ) ;
Mux2_1 lv5_5( lv4[27], lv4[11], sel[4], lv5[27] ) ;
Mux2_1 lv5_6( lv4[26], lv4[10], sel[4], lv5[26] ) ;
Mux2_1 lv5_7( lv4[25], lv4[9], sel[4], lv5[25] ) ;
Mux2_1 lv5_8( lv4[24], lv4[8], sel[4], lv5[24] ) ;
Mux2_1 lv5_9( lv4[23], lv4[7], sel[4], lv5[23] ) ;
Mux2_1 lv5_10( lv4[22], lv4[6], sel[4], lv5[22] ) ;
Mux2_1 lv5_11( lv4[21], lv4[5], sel[4], lv5[21] ) ;
Mux2_1 lv5_12( lv4[20], lv4[4], sel[4], lv5[20] ) ;
Mux2_1 lv5_13( lv4[19], lv4[3], sel[4], lv5[19] ) ;
Mux2_1 lv5_14( lv4[18], lv4[2], sel[4], lv5[18] ) ;
Mux2_1 lv5_15( lv4[17], lv4[1], sel[4], lv5[17] ) ;
Mux2_1 lv5_16( lv4[16], lv4[0], sel[4], lv5[16] ) ;
Mux2_1 lv5_17( lv4[15], 1'b0, sel[4], lv5[15] ) ;
Mux2_1 lv5_18( lv4[14], 1'b0, sel[4], lv5[14] ) ;
Mux2_1 lv5_19( lv4[13], 1'b0, sel[4], lv5[13] ) ;
Mux2_1 lv5_20( lv4[12], 1'b0, sel[4], lv5[12] ) ;
Mux2_1 lv5_21( lv4[11], 1'b0, sel[4], lv5[11] ) ;
Mux2_1 lv5_22( lv4[10], 1'b0, sel[4], lv5[10] ) ;
Mux2_1 lv5_23( lv4[9], 1'b0, sel[4], lv5[9] ) ;
Mux2_1 lv5_24( lv4[8], 1'b0, sel[4], lv5[8] ) ;
Mux2_1 lv5_25( lv4[7], 1'b0, sel[4], lv5[7] ) ;
Mux2_1 lv5_26( lv4[6], 1'b0, sel[4], lv5[6] ) ;
Mux2_1 lv5_27( lv4[5], 1'b0, sel[4], lv5[5] ) ;
Mux2_1 lv5_28( lv4[4], 1'b0, sel[4], lv5[4] ) ;
Mux2_1 lv5_29( lv4[3], 1'b0, sel[4], lv5[3] ) ;
Mux2_1 lv5_30( lv4[2], 1'b0, sel[4], lv5[2] ) ;
Mux2_1 lv5_31( lv4[1], 1'b0, sel[4], lv5[1] ) ;
Mux2_1 lv5_32( lv4[0], 1'b0, sel[4], lv5[0] ) ;

assign out = ( reset == 1'b1 ) ? 0 : lv5 ;

endmodule 
