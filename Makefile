default:
	g++ main.cpp -o cube -lsfml-graphics -lsfml-window -lsfml-system; ./cube
clean:
	rm cube