#ifndef SIGNALS_H
#define SIGNALS_H

#include "executor.h"
#include "minishell.h"
#include <signal.h>
#include <termios.h>

struct termios orig_termios;

void ft_configure_terminal(void);
void handle_execution_signal(int signal);
void handle_parser_signal(int signal);
void setup_parser_signals(void);
void setup_execution_signals(void);
void ft_restore_terminal(int i);

#endif
