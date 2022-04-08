# Executable names:
EXE = flights
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = Airport.o Route.o WeightedGraph.o main.o #dsets.o maze.o

# Generated files
CLEAN_RM = unsolved.png solved.png testdijkstra testdfs testvisual \
						*.o *.d tests/*.o tests/*.d cs225/*.d cs225/*.o \
						cs225/lodepng/*.o cs225/lodepng/*.d \
						cs225/catch/*.o cs225/catch/*.d

# Use the cs225 makefile template:
include cs225/make/cs225.mk


# Part-specific targets
DIJKSTRA_OBJS = $(filter-out $(EXE_OBJ), $(OBJS))
DIJKSTRA_OBJS += testdijkstra.o

testdijkstra: $(DIJKSTRA_OBJS)
	$(LD) $^ $(LDFLAGS) -o $@


DFS_OBJS = $(filter-out $(EXE_OBJ), $(OBJS))
DFS_OBJS += testdfs.o

testdfs: $(DFS_OBJS)
	$(LD) $^ $(LDFLAGS) -o $@


VISUAL_OBJS = $(filter-out $(EXE_OBJ), $(OBJS))
VISUAL_OBJS += StickerSheet.o testvisual.o 

testvisual: $(VISUAL_OBJS)
	$(LD) $^ $(LDFLAGS) -o $@
