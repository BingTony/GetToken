`timescale 1ns/1ns


module	Multiplier  ( clk, dataA, dataB, Signal, dataOut, reset );
input clk ;
input reset ;
input	[31:0]  dataA ; //MCND
input	[31:0]  dataB ; //MPY
input   [5:0]   Signal ;
reg     [63:0]  temp ;
reg	[31:0]	tempA, tempB;
output	[63:0]	dataOut  ;


reg     [63:0]  result ;


parameter MM = 6'b011001 ;
parameter OUT = 6'b111111;


always@( Signal ) begin
  if (Signal == MM) begin
    result = 64'b0 ;
    tempA = dataA ;
    tempB = dataB ;
  end
end


always@( posedge clk or reset ) begin 
	
  if ( reset ) begin 
                result = 64'b0 ;
  end

  else begin
      if ( Signal == MM ) begin
        if (tempB[0] == 1) begin //為1的話 result＋被乘數
          result = result + tempA ;
        end

        tempA = tempA << 1 ; //被乘數左移
	tempB = tempB >> 1 ; //乘數右移
       end     

      else if ( Signal == OUT ) begin //32個週期結束，傳入訊號OUT
         temp = result ;

      end
   end
end


assign dataOut = temp ;
endmodule

/*
always@( posedge clk or reset or done )
begin
        if ( reset )
               PROD = 64'b0 ;
	else
	
	begin	
	  if (PROD[0] == 1) begin
		temp = temp + MCND ;
		PROD[63:31] = temp ;
		// ALU_1(.dataA,.dataB,.Signal,.dataOut,.reset) ;
	        //add = 1 ;
	  end

	  PROD[62:0] = PROD[63:1] ;
          PROD[63] = 0 ;
	  count = count + 1 ;
	  if (count == 32)
		done = 1 ;
	end
end
*/






