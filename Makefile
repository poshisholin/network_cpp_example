SERVER = server
CLIENT = client

CXXFLAGS = -std=c++11 -Wall -Wextra

SERVER_SRC = server.cpp
CLIENT_SRC = client.cpp

all: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_SRC)
	$(CXX) $(CXXFLAGS) -o $(SERVER) $(SERVER_SRC)

$(CLIENT): $(CLIENT_SRC)
	$(CXX) $(CXXFLAGS) -o $(CLIENT) $(CLIENT_SRC)

clean:
	rm -f $(SERVER) $(CLIENT)

run_server: $(SERVER)
	@echo "Starting server..."
	./$(SERVER)

run_client: $(CLIENT)
	@echo "Starting client..."
	./$(CLIENT)

.PHONY: all clean run_server run_client