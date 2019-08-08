Target = music
Object = Main_player.cpp Music_player_src.cpp TCP_Server.cpp 

$(Target):$(Object)
	g++ $(Object) -o $(Target) -lpthread -lsqlite3 -g
.PHONY:clean
clean:
	-rm -rf $(Target)
