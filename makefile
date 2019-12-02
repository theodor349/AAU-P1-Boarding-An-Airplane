CFLAGS = -Wall -pedantic -std=c99
H = Header
GA = Gather
BA = BoardingAlgorithms
SIM = Simulation
BAPATH = /BoardingAlgorithms/BoardingAlgorithms
GAPATH = Gather/Gather
SIMPATH = Simulation/Simulation
STATEPATH = Simulation/States

PROGRAMNAME = Program # replace programName




#$(PROGRAMNAME).exe: $(SIM).o $(GA).o $(BA).o Main.c
#	gcc $(CFLAGS) -o $(PROGRAMNAME) Main.c $(SIM).o $(GA).o $(BA).o

#Gather.o: $(GAPATH).c $(H)/$(GA).h
#	gcc $(CFLAGS) -c $(GAPATH).c

#BoardingAlgorithms.o: $(BAPATH).c $(H)/$(BA).h
#	gcc $(CFLAGS) -c $(BAPATH).c

Simulation.o: $(SIMPATH).c $(H)/$(SIM).h LookingForRow.o Luggage.o Seating.o
	gcc $(CFLAGS) -c $(SIMPATH).c LookingForRow.o Luggage.o Seating.o

LookingForRow.o: $(STATEPATH)/LookingForRow.c $(H)/$(SIM).h
	gcc $(CFLAGS) -c $(STATEPATH)/LookingForRow.c

Luggage.o: $(STATEPATH)/Luggage.c $(H)/$(SIM).h
	gcc $(CFLAGS) -c $(STATEPATH)/Luggage.c

Seating.o: $(STATEPATH)/Seating.c $(H)/$(SIM).h
	gcc $(CFLAGS) -c $(STATEPATH)/Seating.c


# Removes generated .o files
#clean:
#	$(RM) *.o
