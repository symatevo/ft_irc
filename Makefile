NAME = ircserv

FLAGS = -Werror -Wextra -Wall -std=c++98

SRCS = main.cpp\
		./src/Channel.cpp\
		./src/Client.cpp\
		./src/CommandHandler.cpp\
		server.cpp\
		parsing.cpp\
		./src/JoinCommand.cpp\
		./src/KickCommand.cpp\
		./src/ModeCommand.cpp\
		./src/NickCommand.cpp\
		./src/NoticeCommand.cpp\
		./src/PartCommand.cpp\
		./src/PassCommand.cpp\
		./src/PingCommand.cpp\
		./src/PongCommand.cpp\
		./src/PrivMsgCommand.cpp\
		./src/QuitCommand.cpp\
		./src/UserCommand.cpp


OBJS = ${SRCS:.cpp=.o}

RM = rm -rf

CC = c++

all:${NAME}

${NAME}: 	${OBJS}
		${CC} ${FLAGS} -o ${NAME} ${OBJS} 

clean: 
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re