#//////////////////////////////////////////////////////////////////////////////
#   -- clMAGMA (version 0.1) --
#      Univ. of Tennessee, Knoxville
#      Univ. of California, Berkeley
#      Univ. of Colorado, Denver
#      April 2012
#//////////////////////////////////////////////////////////////////////////////

MAGMA_DIR = .
include ./Makefile.internal

.PHONY: lib

all: lib test

lib: libmagma libmagmablas

libmagma:
	( cd control          && $(MAKE) )
	( cd interface_opencl && $(MAKE) )
	( cd src              && $(MAKE) )

libmagmablas:
	( cd magmablas        && $(MAKE) )

#lapacktest:
#	( cd testing/lin      && $(MAKE) )

test:
	( cd testing          && $(MAKE) )

clean:
	( cd control          && $(MAKE) clean )
	( cd interface_opencl && $(MAKE) clean )
	( cd src              && $(MAKE) clean )
	( cd magmablas        && $(MAKE) clean ) 
	( cd testing          && $(MAKE) clean )
	#( cd testing/lin      && $(MAKE) clean )
	-rm -f $(LIBMAGMA) $(LIBMAGMABLAS)

cleanall:
	( cd control          && $(MAKE) cleanall )
	( cd interface_opencl && $(MAKE) cleanall )
	( cd src              && $(MAKE) cleanall )
	( cd magmablas        && $(MAKE) cleanall ) 
	( cd testing          && $(MAKE) cleanall )
	#( cd testing/lin      && $(MAKE) cleanall )
	$(MAKE) cleanall2

# cleanall2 is a dummy rule to run cleangen at the *end* of make cleanall, so
cleanall2:
	@echo

dir:
	mkdir -p $(prefix)
	mkdir -p $(prefix)/include
	mkdir -p $(prefix)/lib
	mkdir -p $(prefix)/lib/pkgconfig

install: lib dir
#       MAGMA
	cp $(MAGMA_DIR)/include/*.h  $(prefix)/include
	cp $(LIBMAGMA)               $(prefix)/lib
	cp $(LIBMAGMABLAS)           $(prefix)/lib
	cat $(MAGMA_DIR)/lib/pkgconfig/magma.pc | \
	    sed -e s:\__PREFIX:"$(prefix)":     | \
	    sed -e s:\__LIBEXT:"$(LIBEXT)":       \
	    > $(prefix)/lib/pkgconfig/magma.pc