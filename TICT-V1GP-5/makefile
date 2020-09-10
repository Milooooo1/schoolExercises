DIRECTORIES = src/ai src/config src/game
EXECUTABLES = src/ai/ai src/config/config src/game/wumpus

.PHONY: all clean

all:
	@for dir in $(DIRECTORIES); do \
		$(MAKE) --directory=$$dir; \
	done 
	cp $(EXECUTABLES) --target-directory=.

clean:
	@for dir in $(DIRECTORIES); do \
		$(MAKE) clean --directory=$$dir; \
	done
	rm ai config wumpus