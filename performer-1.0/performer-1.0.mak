# -*- mode: Makefile; -*-
# -----------------------------------------
# project performer-1.0


export PATH := /opt/wx/2.8/bin:$(PATH)
export LD_LIBRARY_PATH := /opt/wx/2.8/lib:$(LD_LIBRARY_PATH)

_WX = /home/gr/projects/gui/codeblocks/wx
_WX.LIB = $(_WX)/lib
_WX.INCLUDE = $(_WX)/include

_CB = /home/gr/projects/gui/codeblocks/cb/src
_CB.INCLUDE = $(_CB)/include
_CB.LIB = $(_CB)/devel



CFLAGS_C = $(filter-out -include "sdk.h",$(CFLAGS))

# -----------------------------------------

# MAKE_DEP = -MMD -MT $@ -MF $(@:.o=.d)

CFLAGS = -Wall -g 
INCLUDES = -I../performer-1.0 
LDFLAGS = -Lextlibs  -s
RCFLAGS = 
LDLIBS = $(T_LDLIBS) -lrt -lboost_regex-gcc43-mt -lxerces-c  -lstdc++

LINK_exe = gcc -o $@ $^ $(LDFLAGS) $(LDLIBS)
LINK_con = gcc -o $@ $^ $(LDFLAGS) $(LDLIBS)
LINK_dll = gcc -o $@ $^ $(LDFLAGS) $(LDLIBS) -shared
LINK_lib = rm -f $@ && ar rcs $@ $^
COMPILE_c = gcc $(CFLAGS_C) -o $@ -c $< $(MAKEDEP) $(INCLUDES)
COMPILE_cpp = g++ $(CFLAGS) -o $@ -c $< $(MAKEDEP) $(INCLUDES)
COMPILE_rc = windres $(RCFLAGS) -J rc -O coff -i $< -o $@ -I$(dir $<)

%.o : %.c ; $(COMPILE_c)
%.o : %.cpp ; $(COMPILE_cpp)
%.o : %.cxx ; $(COMPILE_cpp)
%.o : %.rc ; $(COMPILE_rc)
.SUFFIXES: .o .d .c .cpp .cxx .rc

all: all.before all.targets all.after

all.before :
	-
all.after : $(FIRST_TARGET)

# -----------------------------------------------------------
ifeq "$(shell uname)" "Linux"
# -----------------------------------------------------------
	
all.targets : Linux_Dynamic_target Linux_Static_target 

# -----------------------------------------------------------
else
# -----------------------------------------------------------

all.targets : Windows_Dynamic_target Windows_Static_targets

# -----------------------------------------------------------
endif
# -----------------------------------------------------------

clean :
	rm -fv $(clean.OBJ)
	rm -fv $(DEP_FILES)

.PHONY: all clean distclean

# -----------------------------------------------------------
ifeq "$(shell uname)" "Linux"
# -----------------------------------------------------------

# -----------------------------------------
# Linux_Dynamic_target

Linux_Dynamic_target.BIN = libs/libperformer-1-gcc433.so
Linux_Dynamic_target.OBJ = src/analysis/analyzer.o src/analysis/comparer.o src/analysis/paverage.o src/analysis/pfunctor.o src/analysis/pmax.o src/analysis/pmin.o src/analysis/pstddeviation.o src/config/configfile.o src/config/linpriority.o src/data_collection/datacollector.o src/data_collection/linux/linfactory.o src/data_collection/linux/linmemprof.o src/data_collection/linux/lintimer.o src/data_collection/linux/procsmaps.o src/data_collection/linux/procstatus.o src/data_collection/pstructs.o src/data_collection/resultxml.o src/pfactory.o 
DEP_FILES += src/analysis/analyzer.d src/analysis/comparer.d src/analysis/paverage.d src/analysis/pfunctor.d src/analysis/pmax.d src/analysis/pmin.d src/analysis/pstddeviation.d src/config/configfile.d src/config/linpriority.d src/data_collection/datacollector.d src/data_collection/linux/linfactory.d src/data_collection/linux/linmemprof.d src/data_collection/linux/lintimer.d src/data_collection/linux/procsmaps.d src/data_collection/linux/procstatus.d src/data_collection/pstructs.d src/data_collection/resultxml.d src/pfactory.d 
clean.OBJ += $(Linux_Dynamic_target.BIN) $(Linux_Dynamic_target.OBJ)

Linux_Dynamic_target : Linux_Dynamic_target.before $(Linux_Dynamic_target.BIN) Linux_Dynamic_target.after_always
Linux_Dynamic_target : CFLAGS += -Wall -g -DLINUX  -Os
Linux_Dynamic_target : INCLUDES += 
Linux_Dynamic_target : RCFLAGS += 
Linux_Dynamic_target : LDFLAGS +=  $(CREATE_LIB) $(CREATE_DEF)
Linux_Dynamic_target : T_LDLIBS = 
ifdef LMAKE
Linux_Dynamic_target : CFLAGS -= -O1 -O2 -g -pipe
endif

Linux_Dynamic_target.before :
	
	
Linux_Dynamic_target.after_always : $(Linux_Dynamic_target.BIN)
	
$(Linux_Dynamic_target.BIN) : $(Linux_Dynamic_target.OBJ)
	$(LINK_dll)

# -----------------------------------------
# Linux_Static_target

Linux_Static_target.BIN = libs/libperformer-1-gcc433.a
Linux_Static_target.OBJ = src/analysis/analyzer.o src/analysis/comparer.o src/analysis/paverage.o src/analysis/pfunctor.o src/analysis/pmax.o src/analysis/pmin.o src/analysis/pstddeviation.o src/config/configfile.o src/config/linpriority.o src/data_collection/datacollector.o src/data_collection/linux/linfactory.o src/data_collection/linux/linmemprof.o src/data_collection/linux/lintimer.o src/data_collection/linux/procsmaps.o src/data_collection/linux/procstatus.o src/data_collection/pstructs.o src/data_collection/resultxml.o src/pfactory.o 
DEP_FILES += src/analysis/analyzer.d src/analysis/comparer.d src/analysis/paverage.d src/analysis/pfunctor.d src/analysis/pmax.d src/analysis/pmin.d src/analysis/pstddeviation.d src/config/configfile.d src/config/linpriority.d src/data_collection/datacollector.d src/data_collection/linux/linfactory.d src/data_collection/linux/linmemprof.d src/data_collection/linux/lintimer.d src/data_collection/linux/procsmaps.d src/data_collection/linux/procstatus.d src/data_collection/pstructs.d src/data_collection/resultxml.d src/pfactory.d 
clean.OBJ += $(Linux_Static_target.BIN) $(Linux_Static_target.OBJ)

Linux_Static_target : Linux_Static_target.before $(Linux_Static_target.BIN) Linux_Static_target.after_always
Linux_Static_target : CFLAGS += -Wall -g -DLINUX  -Os
Linux_Static_target : INCLUDES += 
Linux_Static_target : RCFLAGS += 
Linux_Static_target : LDFLAGS +=   $(CREATE_DEF)
Linux_Static_target : T_LDLIBS = 
ifdef LMAKE
Linux_Static_target : CFLAGS -= -O1 -O2 -g -pipe
endif

Linux_Static_target.before :
	
	
Linux_Static_target.after_always : $(Linux_Static_target.BIN)
	
$(Linux_Static_target.BIN) : $(Linux_Static_target.OBJ)
	$(LINK_lib)	

# -----------------------------------------------------------
else
# -----------------------------------------------------------	

# -----------------------------------------
# Windows_Dynamic_target

Windows_Dynamic_target.BIN = libs/performer-1-vc9.so
Windows_Dynamic_target.OBJ = src/analysis/analyzer.o src/analysis/comparer.o src/analysis/paverage.o src/analysis/pfunctor.o src/analysis/pmax.o src/analysis/pmin.o src/analysis/pstddeviation.o src/config/configfile.o src/config/winpriority.o src/data_collection/datacollector.o src/data_collection/pstructs.o src/data_collection/resultxml.o src/data_collection/windows/winfactory.o src/data_collection/windows/winmemprof.o src/data_collection/windows/wintimer.o src/pfactory.o 
DEP_FILES += src/analysis/analyzer.d src/analysis/comparer.d src/analysis/paverage.d src/analysis/pfunctor.d src/analysis/pmax.d src/analysis/pmin.d src/analysis/pstddeviation.d src/config/configfile.d src/config/winpriority.d src/data_collection/datacollector.d src/data_collection/pstructs.d src/data_collection/resultxml.d src/data_collection/windows/winfactory.d src/data_collection/windows/winmemprof.d src/data_collection/windows/wintimer.d src/pfactory.d 
clean.OBJ += $(Windows_Dynamic_target.BIN) $(Windows_Dynamic_target.OBJ)

Windows_Dynamic_target : Windows_Dynamic_target.before $(Windows_Dynamic_target.BIN) Windows_Dynamic_target.after_always
Windows_Dynamic_target : CFLAGS += /Wall /Zi -Wall -g -DWINDOWS /DWINDOWS  -Os
Windows_Dynamic_target : INCLUDES += 
Windows_Dynamic_target : RCFLAGS += 
Windows_Dynamic_target : LDFLAGS += /DEBUG  $(CREATE_LIB) $(CREATE_DEF)
Windows_Dynamic_target : T_LDLIBS = 
ifdef LMAKE
Windows_Dynamic_target : CFLAGS -= -O1 -O2 -g -pipe
endif

Windows_Dynamic_target.before :
	
	
Windows_Dynamic_target.after_always : $(Windows_Dynamic_target.BIN)
	
$(Windows_Dynamic_target.BIN) : $(Windows_Dynamic_target.OBJ)
	$(LINK_dll)	

# -----------------------------------------
# Windows_Static_target

Windows_Static_target.BIN = libs/libperformer-10-vc9.a
Windows_Static_target.OBJ = src/analysis/analyzer.o src/analysis/comparer.o src/analysis/paverage.o src/analysis/pfunctor.o src/analysis/pmax.o src/analysis/pmin.o src/analysis/pstddeviation.o src/config/configfile.o src/config/winpriority.o src/data_collection/datacollector.o src/data_collection/pstructs.o src/data_collection/resultxml.o src/data_collection/windows/winfactory.o src/data_collection/windows/winmemprof.o src/data_collection/windows/wintimer.o src/pfactory.o 
DEP_FILES += src/analysis/analyzer.d src/analysis/comparer.d src/analysis/paverage.d src/analysis/pfunctor.d src/analysis/pmax.d src/analysis/pmin.d src/analysis/pstddeviation.d src/config/configfile.d src/config/winpriority.d src/data_collection/datacollector.d src/data_collection/pstructs.d src/data_collection/resultxml.d src/data_collection/windows/winfactory.d src/data_collection/windows/winmemprof.d src/data_collection/windows/wintimer.d src/pfactory.d 
clean.OBJ += $(Windows_Static_target.BIN) $(Windows_Static_target.OBJ)

Windows_Static_target : Windows_Static_target.before $(Windows_Static_target.BIN) Windows_Static_target.after_always
Windows_Static_target : CFLAGS += /Wall /Zi -Wall -g -DWINDOWS /DWINDOWS  -Os
Windows_Static_target : INCLUDES += 
Windows_Static_target : RCFLAGS += 
Windows_Static_target : LDFLAGS += /DEBUG   $(CREATE_DEF)
Windows_Static_target : T_LDLIBS = 
ifdef LMAKE
Windows_Static_target : CFLAGS -= -O1 -O2 -g -pipe
endif

Windows_Static_target.before :
	
	
Windows_Static_target.after_always : $(Windows_Static_target.BIN)
	
$(Windows_Static_target.BIN) : $(Windows_Static_target.OBJ)
	$(LINK_lib)
	

# -----------------------------------------
ifdef MAKE_DEP
-include $(DEP_FILES)
endif

# -----------------------------------------------------------
endif
#

