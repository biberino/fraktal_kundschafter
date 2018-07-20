#all:
	#g++ --std=c++11 -Ofast -ffast-math main.cpp workload_distributor.cpp result_store.cpp fractal_worker.cpp calculation_handler.cpp display.cpp options_panel.cpp functions_panel.cpp range-panel.cpp -o fraktal_kundschafter -lpthread `pkg-config gtkmm-3.0 --cflags --libs`



#TODO: doku für das makefile
#			checken ob docker container läuft


######### OPTIONEN #########

# subdir mit Quellcode
SRCDIR := src
# subdir für obj Files
BUILDDIR := build
# Endung mit SRCEXT gehen an den Compiler
SRCEXT := cpp

# Flags für linker
LIBS := -lpthread `pkg-config gtkmm-3.0 --libs`
# Flags für dem Compiler
CFLAGS := -std=c++11 -Ofast -ffast-math -g `pkg-config gtkmm-3.0 --cflags`

# Pfad und Name der Binary
BIN_NAME := bin/fraktal_kundschafter
# Compiler
COMPILER := g++


######### ENDE OPTIONEN #########








# findet alle Dateien (rekursiv) in SRCDIR mit Endung SRCEXT
SOURCES := $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
# Erzeugt liste benötigter Obj Files.
# Nimmt alle Einträge aus SOURCES und ersetzt SRCEXT durch .o
OBJ := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

OUT=-o $(BIN_NAME)

PROJECT_DIR= $(shell pwd)
PROJECT_FOLDER = $(shell basename $(CURDIR))
DOCKER_PROJECT_PATH=$(DOCKER_PATH)/$(PROJECT_FOLDER)

MKDIR_P := mkdir -p
BIN_NAME_ONLY := $(notdir $(BIN_NAME))




local: $(OBJ)
	@echo " Fixe Berechtigungen"
	@chmod -R 755 $(BUILDDIR)
	@echo " Linken..."
	$(COMPILER) $(OBJ) $(OUT) $(CFLAGS) $(LIBS)
	@echo "Build erfolgreich"




clear_local:
	rm -rf $(BUILDDIR)/*
	@echo "CLEARED"



$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	$(MKDIR_P) $(dir $@)
	$(COMPILER) -c $(CFLAGS) -o $@ $<



