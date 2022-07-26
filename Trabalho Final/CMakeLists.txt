cmake_minimum_required(VERSION 3.22)
project(Trabalho_Final C)

set(CMAKE_C_STANDARD 99)

#add_executable(Trabalho_Final calcula_fatorial_sockets_tcp_servidor.c calcula_fatorial_sockets_tcp_cliente.c)

add_executable(Trabalho_Final calcula_fatorial_sequencial.c calcula_fatorial_mpi.c)
#add_executable(Trabalho_Final calcula_fatorial_sockets_tcp_cliente.c exemplo.c)
#add_executable(Trabalho_Final calcula_fatorial_sockets_tcp_servidor.c)
#add_executable(Trabalho_Final exemplo.c)