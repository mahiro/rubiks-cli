CC = g++
CFLAGS = -fast -Wall
MKDIR = mkdir -p

BINS = rubiks-search rubiks-apply rubiks-reverse rubiks-scramble
SRCS = $(shell find . -name '*.cpp' -print | sed s/^.\\///)
OBJS = $(patsubst %.cpp, obj/%.o, $(SRCS))
DEPS = $(patsubst %.cpp, obj/%.d, $(SRCS))

.PHONY: all clean
all: $(BINS)

clean:
	$(RM) -r obj $(BINS)

rubiks-%: obj/%.o obj/rubiks.o $(DEPS)
	$(CC) -o $@ $< obj/rubiks.o

.SUFFIXES: .cpp .o .d
obj/%.o: %.cpp
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

obj/%.d: %.cpp
	@$(MKDIR) $(dir $@)
	@$(CC) -MM -MG -MP -MT $(@:.d=.o) -MT $@ $< > $@

-include $(DEPS)
