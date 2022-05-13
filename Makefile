default:
	g++ main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system; ./main
clean:
	rm main