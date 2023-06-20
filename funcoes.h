#ifndef FUNCOES_H
#define FUNCOES_H

#include "fila_pre_reservas.h"
#include "lista_de_reservas.h"

int reservar(int tipo_de_reserva, pLista lista_ptr, tipoFila *fila_ptr);
int pre_reservar(struct conteudoFila pre_reserva, tipoFila *fila_ptr);
int cancelar_reserva(int tipo_de_reserva, pLista lista_ptr, tipoFila *fila_ptr);
int cancelar_pre_reserva(int tipo_de_pre_reserva, tipoFila *fila_ptr);
int carregar_dados(pLista lista_ptr, tipoFila *fila_ptr);
int guardar_dados(pLista lista_ptr, tipoFila *fila_ptr);
int executar_servico(pLista lista_ptr, tipoFila* fila_ptr);
void listar_reservas_e_prereservas_por_data(pLista lista_ptr, tipoFila *fila_ptr);
int verificar_disponibilidade(pLista lista_ptr, struct conteudoLista reserva);
struct conteudoFila verificar_compatibilidade(struct conteudoLista reserva, tipoFila *fila_ptr, pLista lista_ptr);
int substituir_reserva(struct conteudoFila pre_reserva, pLista lista_ptr);
struct conteudoFila reserva_para_pre_reserva(struct conteudoLista reserva);
struct conteudoLista pre_reserva_para_reserva(struct conteudoFila pre_reserva);
int input_int(char* string);
char* input_string(char* string);
int str_to_int(char* string);
int validar_horas(int hora, int minutos);
int validar_data(int mes, int dia);
void limpar_tela();
int hora_para_minutos(int hora, int minutos);
void listar_reservas_prereservas_cliente(pLista lista_ptr, tipoFila *fila_ptr, char *nome_cliente);


#endif