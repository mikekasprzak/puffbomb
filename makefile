# - -------------------------------------------------------------------------------------------- - #
-include config.mak
-include Code/Game/$(GAME_TARGET)/Makefiles/game.mak
# - -------------------------------------------------------------------------------------------- - #
ifeq "$(PLATFORM)" "Tools"
ARGS		:=	-j$(THREADS) -f Code/$(PLATFORM)/makefile.mak -k --no-print-directory
else
ifeq "$(PLATFORM)" "TestSuite"
ARGS		:=	-j$(THREADS) -f Code/$(PLATFORM)/makefile.mak -k --no-print-directory
else
ARGS		:=	-j$(THREADS) -f Code/Makefiles/$(PLATFORM)/makefile.mak --no-print-directory
endif
endif
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
normal: config.mak
	@make $(ARGS)
# - -------------------------------------------------------------------------------------------- - #
all: config.mak
	@make all $(ARGS)
# - -------------------------------------------------------------------------------------------- - #
run: config.mak
	@make run $(ARGS)
# - -------------------------------------------------------------------------------------------- - #
update: config.mak
	@make update $(ARGS)
	@make $(ARGS)
# - -------------------------------------------------------------------------------------------- - #
clean: config.mak
	@make clean $(ARGS)
# - -------------------------------------------------------------------------------------------- - #
cleanall: config.mak
	@make cleanall $(ARGS)
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
tools:
	@make PLATFORM=Tools --no-print-directory
# - -------------------------------------------------------------------------------------------- - #
Tools:
	@make PLATFORM=Tools --no-print-directory
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
testsuite:
	@make PLATFORM=TestSuite --no-print-directory
# - -------------------------------------------------------------------------------------------- - #
TestSuite:
	@make PLATFORM=TestSuite --no-print-directory
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
config.mak:
ifndef GAME_TARGET
	@echo ---- Error!  No configuration found!! -----------------------------------
	@echo -- Do "make GAME_TARGET=PROJECTNAME" to acquire a configuration ---------
	@echo --
	@echo -- Available Projects: PuffBOMB
	@echo --
	@echo -- Dying... -------------------------------------------------------------
	@1 
else
	@echo ---- Copying default game configuration from GAME_TARGET ----------------
	cp Code/Game/$(GAME_TARGET)/Makefiles/config.mak .
	@echo ---- Configuration copied.  You can use "make", "make run", "make clean"
	@echo --
	@echo -- Dying... -------------------------------------------------------------
	@1 
endif
# - -------------------------------------------------------------------------------------------- - #
