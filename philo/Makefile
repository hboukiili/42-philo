src = *.c
philo = philo
FLAGS =  -lreadline -Wall -Wextra -Werror #-fsanitize=address -g3
CC = cc

all : philo
	
$(philo): $(src)	
	@$(CC) $(FLAGS) $(src) -o philo
	@tput setaf 2; echo "philo IS READY"

clean :
	@rm -f philo
	@tput setaf 1; echo "philo clean COMPLET"

fclean : clean

re: fclean all 