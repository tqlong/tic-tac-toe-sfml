all: resource_manager.h game_state.h render_engine.h controller.h
	g++ main.cpp \
		resource_manager.cpp \
		game_state.cpp \
		alpha_beta.cpp \
		render_engine.cpp \
		controller.cpp \
		-o tic-tac-toe \
		-std=c++17 \
		-I /opt/homebrew/Cellar/sfml/2.5.1_2/include \
		-L /opt/homebrew/Cellar/sfml/2.5.1_2/lib \
		-l sfml-graphics -l sfml-window -l sfml-system \
		-mmacosx-version-min=13.0
