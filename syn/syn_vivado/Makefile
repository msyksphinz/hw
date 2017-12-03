-include Makefile.local

all: filelist.f
	vivado -m64 -mode batch -source vivado_synth.tcl

filelist.f:
	cpp -P 	../../verif/dut/dut.f | grep -v "\-y"  > filelist.tcl
	find ../../vmod/vlibs/ -name *.v >> filelist.tcl
	find ../../vmod/rams/  -name *.v >> filelist.tcl
	sed -i '/^\s*$$/d' filelist.tcl && sed -i 's/^/read_verilog -sv /g' filelist.tcl
	sed -i '/^read_verilog -sv $$/d' filelist.tcl

clean:
	rm -rf *.jou *.log vivado_pid*.str
