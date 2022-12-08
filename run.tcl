#=============================================================================
# run.tcl 
#=============================================================================
# @brief: A Tcl script for synthesizing the digit recongnition design.
#
# @desc: This script launches a batch of simulation & synthesis runs
# to quickly explore different K parameters.
#
# 1. The user specifies the list of K values.
# 2. Useful simulation & synthesis stats are consolidated into ./result/result.csv

#------------------------------------------------------
# Remove old result file
#------------------------------------------------------
set filename "knn_result.csv"
file delete -force "./result/${filename}"

#------------------------------------------------------
# You can specify a set of parameter K to explore.
#------------------------------------------------------
set value_k { 1 }
#------------------------------------------------------
# run batch experiments
#------------------------------------------------------
foreach { K } $value_k {

# Define the bitwidth macros from CFLAGs
set CFLAGS "-DK_CONST=${K}"

# Project name
set hls_prj ${K}-nn.prj

# Open/reset the project
open_project ${hls_prj} -reset
# Top function of the design is "digitrec"
set_top digitrec
# set_top top

# Add design and testbench files
add_files digitrec.cpp -cflags $CFLAGS
add_files -tb digitrec_test.cpp -cflags $CFLAGS
add_files -tb data

open_solution "solution1"
# Use Zynq device
set_part {xc7z020clg484-1}

# Target clock period is 10ns
create_clock -period 10

# Do not inline update_knn and knn_vote functions 
set_directive_inline -off update_knn
set_directive_inline -off knn_vote
set_directive_inline -off VVadd
set_directive_inline -off MatMul
set_directive_inline -off DotProd
set_directive_inline -off Conv1d
set_directive_inline -off MatVecMul
### You can add your own directives here ###
set_directive_pipeline VVadd/VVadd_pipe

set_directive_pipeline DotProd/DotProd_pipe

set_directive_pipeline MatVecMul/MatVecMul_pipe1
set_directive_pipeline MatVecMul/MatVecMul_pipe2

set_directive_pipeline Conv1d/Conv1d_pipe1
set_directive_pipeline Conv1d/Conv1d_pipe2

# array partition
set_directive_array_partition -type complete -dim 0 Conv1d res

set_directive_array_partition -type complete -dim 0 Conv1d a
set_directive_array_partition -type complete -dim 0 Conv1d b

set_directive_array_partition -type complete -dim 0 MatVecMul res
set_directive_array_partition -type complete -dim 0 MatVecMul A
set_directive_array_partition -type complete -dim 0 MatVecMul x



# Simulate the C++ design
csim_design
# Synthesize the design
csynth_design
# Co-simulate the design
#cosim_design

#---------------------------------------------
# Collect & dump out results from HLS reports
#---------------------------------------------
set argv [list $filename $hls_prj]
set argc 2
source "./script/collect_result.tcl"
}
exit
