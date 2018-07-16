all:
	g++ --std=c++11 -Ofast -ffast-math main.cpp `pkg-config gtkmm-3.0 --cflags --libs` workload_distributor.cpp result_store.cpp fractal_worker.cpp  -o fraktal_kundschafter -lpthread -lSDL2