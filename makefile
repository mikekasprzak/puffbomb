# - -------------------------------------------------------------------------------------------- - #
-include config.mak
# - -------------------------------------------------------------------------------------------- - #
ifeq "$(PLATFORM)" "Tools"
ARGS		:=	-j$(THREADS) -f Code/$(PLATFORM)/makefile.mak -k --no-print-directory
else
ifeq "$(PLATFORM)" "TestSuite"
ARGS		:=	-j$(THREADS) -f Code/$(PLATFORM)/makefile.mak -k --no-print-directory
else
ARGS		:=	-j$(THREADS) -f Code/Platform/$(PLATFORM)/makefile.mak --no-print-directory
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
	@echo ---- No configuration found.  Acquiring default. ------------------------
	cp Code/Tools/ToolChain/config.mak .
	@echo ---- Configuration copied.  Dying... ------------------------------------
	@1 
# - -------------------------------------------------------------------------------------------- - #
