// Copyright The Naja Authors.
// SPDX-FileCopyrightText: 2023 The Naja authors <https://github.com/xtofalex/naja/blob/main/AUTHORS>
//
// SPDX-License-Identifier: Apache-2.0
//

module model(input [2:-2] i0, input [-2:2] i1, output [2:-2] o0, output [-2:2] o1);
parameter PARAM0 = "0000" ;
parameter PARAM1 = "FALSE" ;
parameter PARAM2 = 4h'0 ;
parameter PARAM3 = 10 ;

endmodule //model

module top();
wire [2:-2] bus0;
wire [-2:2] bus1;
wire [2:-2] bus2;
wire [-2:2] bus3;

model instance1 (
  .i0(),
  .i1(),
  .o0(bus0),
  .o1(bus1)
);

model instance2 (
  .i0(bus0),
  .i1(bus1),
  .o0(),
  .o1()
);
endmodule //top
