CC = g++
CFLAGS = -fast -Wall
MKDIR = mkdir -p

SRCS = $(shell find src -name '*.cpp' -print)
DEPS = $(patsubst src/%.cpp, obj/%.d, $(SRCS))
BINS = bin/rubiks-search bin/rubiks-apply bin/rubiks-reverse bin/rubiks-mirror bin/rubiks-scramble bin/rubiks-enumerate

TSRCS = $(shell find t -name '*.cpp' -print)
TDEPS = $(patsubst t/%.cpp, obj/%.d, $(TSRCS))
TBINS = $(patsubst t/%.cpp, t/%.t, $(TSRCS))

.PHONY: all clean
all: $(BINS)

test: $(BINS) $(TBINS)
	prove

clean:
	$(RM) -r obj bin $(TBINS)

bin/rubiks-%: obj/%.o obj/rubiks.o $(DEPS)
	@$(MKDIR) $(dir $@)
	$(CC) -o $@ $< obj/rubiks.o

t/%.t: obj/%.o obj/rubiks.o $(DEPS)
	@$(MKDIR) $(dir $@)
	$(CC) -o $@ $< obj/rubiks.o

.SUFFIXES: .cpp .o .d
obj/%.o: src/%.cpp
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

obj/%.d: src/%.cpp
	@$(MKDIR) $(dir $@)
	@$(CC) -MM -MG -MP -MT $(@:.d=.o) -MT $@ $< > $@

obj/%.o: t/%.cpp
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

obj/%.d: t/%.cpp
	@$(MKDIR) $(dir $@)
	@$(CC) -MM -MG -MP -MT $(@:.d=.o) -MT $@ $< > $@

-include $(DEPS)
