#0 use '@' before 'for' because we just want to print 'building ...'
#  but not the sentence itself
#  using '\' because every line of shell order means a sub shell process
#  we must put them in one line or use '\'
SUBDIR=src example

all:

	@for subdir in $(SUBDIR);\
	do\
		echo "building" $$subdir;\
	done

#1 use '$$' before 'PATH' because 'PATH' is a shell variable
#  use a single '$' before 'APATH' is a Makefile variable
APATH = "/data/"

all:

        @echo ${APATH}
        @echo $$PATH

