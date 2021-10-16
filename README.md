# Instruction-Level-Parallelism
To calculate the performance of a program with dependent register arithmetic instructions, by simulating the execution on a 5-stage pipeline processor by adding NOP’s as appropriate.

# Objective:
To calculate the performance of a program with dependent register arithmetic instructions, by
simulating the execution on a 5-stage pipeline processor by adding NOP’s as appropriate.
The five stages are: Instruction Fetch (IF), Instruction Decode (ID), Execute Operation (EX), 
Memory Reference (ME), and Write Back to Register (WB). 
{Note: for register arithmetic instructions, the Memory Reference cycle is unused but still 
included in the pipeline}
# Inputs:
• Number of instructions in the program
• Set of instructions containing register arithmetic instructions, such as:
ADD_X2,X1,X0
where X2 is the destination register, and X1,X0 are the source registers
{Note: to parse correctly, there should not be any space, so a “_” is added}
# Outputs:
• The total cycle count for the program run on the pipeline processor
• A chart of the pipeline stages of the instructions for the pipeline processo
