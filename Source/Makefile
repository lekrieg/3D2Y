# GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  AbyssCore_config = debug
  EngineEditor_config = debug
  Game_config = debug

else ifeq ($(config),release)
  AbyssCore_config = release
  EngineEditor_config = release
  Game_config = release

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := AbyssCore EngineEditor Game

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

AbyssCore:
ifneq (,$(AbyssCore_config))
	@echo "==== Building AbyssCore ($(AbyssCore_config)) ===="
	@${MAKE} --no-print-directory -C AbyssCore -f Makefile config=$(AbyssCore_config)
endif

EngineEditor: AbyssCore
ifneq (,$(EngineEditor_config))
	@echo "==== Building EngineEditor ($(EngineEditor_config)) ===="
	@${MAKE} --no-print-directory -C EngineEditor -f Makefile config=$(EngineEditor_config)
endif

Game: AbyssCore
ifneq (,$(Game_config))
	@echo "==== Building Game ($(Game_config)) ===="
	@${MAKE} --no-print-directory -C Game -f Makefile config=$(Game_config)
endif

clean:
	@${MAKE} --no-print-directory -C AbyssCore -f Makefile clean
	@${MAKE} --no-print-directory -C EngineEditor -f Makefile clean
	@${MAKE} --no-print-directory -C Game -f Makefile clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   AbyssCore"
	@echo "   EngineEditor"
	@echo "   Game"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"