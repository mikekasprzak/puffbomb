# - -------------------------------------------------------------------------------------------- - #
-include config.mak
-include Code/Game/$(GAME_TARGET)/Makefiles/game.mak
# - -------------------------------------------------------------------------------------------- - #
ARGS		:=	-f Code/Makefiles/$(PLATFORM)/makefile.mak --no-print-directory
ARG_THREADS	:=	-j$(THREADS) 
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
normal: config.mak
	@make update $(ARGS)
	@make $(ARG_THREADS) $(ARGS)
# - -------------------------------------------------------------------------------------------- - #
run: config.mak
	@make update $(ARGS)
	@make run $(ARG_THREADS) $(ARGS)
# - -------------------------------------------------------------------------------------------- - #
update: config.mak
	@make update $(ARGS)
# - -------------------------------------------------------------------------------------------- - #
clean: config.mak
	@make clean $(ARGS)
# - -------------------------------------------------------------------------------------------- - #
#cleanall: config.mak
#	@make cleanall $(ARGS)
# - -------------------------------------------------------------------------------------------- - #

.phony: content tools testsuite

# - -------------------------------------------------------------------------------------------- - #
cleancontent: config.mak
	@make clean -f Content/Makefiles/$(PLATFORM)/makefile.mak --no-print-directory
#	@make clean -f Content/Makefiles/minimaps.mak --no-print-directory
# - -------------------------------------------------------------------------------------------- - #
content:
	@make update -f Content/Makefiles/$(PLATFORM)/makefile.mak --no-print-directory
	@make $(ARG_THREADS) -f Content/Makefiles/$(PLATFORM)/makefile.mak --no-print-directory
	@make $(ARG_THREADS) -f Content/Makefiles/minimaps.mak --no-print-directory
# - -------------------------------------------------------------------------------------------- - #
	
# - -------------------------------------------------------------------------------------------- - #
tools:
	@make PLATFORM=Tools --no-print-directory
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
testsuite:
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
