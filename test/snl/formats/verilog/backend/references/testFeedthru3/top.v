module top(input [-4:-4] in, output [6:6] out);
wire [5:5] feedtru;

assign feedtru[5] = in[-4];
assign out[6] = feedtru[5];

endmodule //top
