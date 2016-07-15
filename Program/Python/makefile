UNAME := $(shell uname)

ifeq ($(OSTYPE),cygwin)
	RM=rm -f
else ifeq ($(OS),Windows_NT)
	ifeq ($(UNAME),MINGW64_NT-10.0)
		RM=rm -f
	else
		RM=del
	endif
else
	RM=rm -f
endif

PY=python
MAIN_SRC_FILE=main.py
SRC_FILES= parameters.py load_params.py verify_params.py temperature.py event.py energy.py verify_output.py plot.py output.py
INPUT_FILES = $(wildcard *.in)
OUTPUT_FILES = $(patsubst %.in, %.out, $(INPUT_FILES))
GRAPH_FILES = $(patsubst %.in, %.png, $(INPUT_FILES))

.PHONY : results
results : $(OUTPUT_FILES) $(GRAPH_FILES)

%.png %.out : %.in $(MAIN_SRC_FILE) $(SRC_FILES)
	$(PY) $(MAIN_SRC_FILE) $*.in

.PHONY : clean
clean :
	$(RM) $(OUTPUT_FILES)
	$(RM) $(GRAPH_FILES)