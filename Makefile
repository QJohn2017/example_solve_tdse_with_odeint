CC		=	g++
FC		=	gfortran
SRC		=	main.cc
OBJ		=	$(patsubst %.cc,%.o,$(filter %.cc,$(SRC))) \
			$(patsubst %.f90,%.o,$(filter %.f90,$(SRC)))

EXE		=	test

CFLAGS	+=	-g -std=c++11
LFLAGS	+=	-lgfortran
FFLAGS	+=

%.o : %.f90
	$(FC) $< $(FFLAGS) -c -o $@

%.o : %.cc
	$(CC) $< $(CFLAGS) -c -o $@

all : $(EXE)

$(EXE) : $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) -o $@

clean:
	$(RM)
	$(RM) $(OBJ)
	$(RM) *~

show:
	echo $(OBJ)
