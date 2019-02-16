appname=NeuronStudy

path=bin

obj=$(path)/main.o\
	$(path)/grid.o\
	$(path)/pool.o\
	$(path)/study.o\
	$(path)/game.o\
	$(path)/type_array.o

all : check_path $(path)/$(appname)

$(path)/$(appname) : $(obj)
	g++ $(obj) -o $(path)/$(appname)

$(path)/%.o : %.cpp
	g++ -c $< -o $@ -Wall -Werror

clean : $(path)
	rm -r $<

check_path :
	@ if [ ! -d $(path) ]; then mkdir $(path); fi
