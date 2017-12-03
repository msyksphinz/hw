create_clock -period 10.0 [get_ports dla_core_clk]
set_input_jitter [get_clocks -of_objects [get_ports dla_core_clk]] 0.05

create_clock -period 10.0 [get_ports dla_csb_clk]
set_input_jitter [get_clocks -of_objects [get_ports dla_csb_clk]] 0.05
