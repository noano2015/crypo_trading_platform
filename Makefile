CC = g++
CPP_FLAGS = -Wall -g --std=c++17

SRC = src/main.cpp src/MerkelMain.cpp src/CSVReader.cpp src/OrderBook.cpp src/OrderBookEntry.cpp src/Wallet.cpp
OUT = merkelrex

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CPP_FLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
