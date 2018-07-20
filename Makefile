all:
	g++ --std=c++11 -Ofast -ffast-math main.cpp workload_distributor.cpp result_store.cpp fractal_worker.cpp calculation_handler.cpp display.cpp options_panel.cpp range-panel.cpp -o fraktal_kundschafter -lpthread `pkg-config gtkmm-3.0 --cflags --libs`