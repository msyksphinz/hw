set PROJ_NAME nvdla_full
set PROJ_DIR .
set TOP_NAME NV_nvdla

set dump 1
set checkpoint 1

create_project -in_memory -part xc7z020clg484-1

set_property parent.project_path ${PROJ_DIR}/${PROJ_NAME}.xpr [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language Verilog [current_project]
set_property board_part em.avnet.com:zed:part0:1.3 [current_project]
set_property vhdl_version vhdl_2k [current_fileset]
# add_files ${PROJ_DIR}/${PROJ_NAME}.srcs/sources_1/bd/zed_base/zed_base.bd

source filelist.tcl

# set XDC_LIST "\
#   ${PROJ_DIR}/${PROJ_NAME}.srcs/sources_1/bd/zed_base/ip/zed_base_axi_gpio_0_0/zed_base_axi_gpio_0_0_board.xdc \
#   ${PROJ_DIR}/${PROJ_NAME}.srcs/sources_1/bd/zed_base/ip/zed_base_axi_gpio_0_0/zed_base_axi_gpio_0_0_ooc.xdc \
# "

# foreach i $XDC_LIST {
#   set_property used_in_implementation false [get_files -all ${i} ]
# }

# foreach i $V_LIST {
#   read_verilog  -library xil_defaultlib ${i}
# }

read_xdc ${PROJ_NAME}.xdc
# set_property used_in_implementation false [get_files ${TOP_NAME}.xdc]

# read_xdc dont_touch.xdc
# set_property used_in_implementation false [get_files dont_touch.xdc]

synth_design -top ${TOP_NAME} \
    -part xc7z020clg484-1 \
    -verilog_define PP_BUSWIDTH_64=1 \
    -verilog_define DESIGNWARE_NOEXIST \
    -include_dirs {../../../common/include ../../../common/rtl} \
    -fanout_limit 10000 \
    -flatten_hierarchy rebuilt
write_checkpoint -force ${TOP_NAME}.dcp
report_utilization -hierarchical -file ${TOP_NAME}_utilization_synth.rpt -pb ${TOP_NAME}_utilization_synth.pb

if {$checkpoint} {write_checkpoint -force ${TOP_NAME}.synth.dcp}
if {$checkpoint} {write_verilog -force ${TOP_NAME}.synth.v}

if {$dump} {report_io -file ${TOP_NAME}.io.rpt}
if {$dump} {report_timing_summary -file ${TOP_NAME}.timing_summary.rpt}
if {$dump} {report_timing -delay_type min_max -sort_by group -max_paths 10 -path_type full -input_pins -file ${TOP_NAME}.timing_detail.rpt}
if {$dump} {report_route_status -show_all -file ${TOP_NAME}.route.rpt}
if {$dump} {report_utilization -file ${TOP_NAME}.util.rpt}
