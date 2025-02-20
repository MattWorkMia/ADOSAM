# Determine the operating system
ifeq ($(shell uname),Darwin)
    MAKEFILE = MacMakefile
else
    MAKEFILE = LinuxMakefile
endif

# Include the appropriate Makefile
include $(MAKEFILE)