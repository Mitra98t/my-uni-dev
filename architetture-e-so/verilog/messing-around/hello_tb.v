`timescale 1ns/1ns
`include "hello.v"

module hello_tb;

    reg a;
    wire z;

    hello uut(z, a);

    initial begin

        $dumpfile("hello_tb.vcd");
        $dumpvars(0, hello_tb);

        a = 0;
        #20;

        a = 1;
        #20;

        a = 0;
        #20;

        $display("Test Complete");

    end

endmodule