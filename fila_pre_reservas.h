#ifndef FILA_PRE_RESERVAS
#define FILA_PRE_RESERVAS

struct conteudoFila{
    struct pre_reserva{
        struct hora_pre_reserva{
            int hora;
            int minutos;
        } hora_pre_reserva;

        struct data_pre_reserva{
            int dia;
            int mes;
        } data_pre_reserva;
        char nome[100];
        int tipo_pre_reserva; /* 0 - lavagem ; 1 - manutenção */
    } pre_reserva;
};

typedef struct noFila{
    struct conteudoFila itemFila;
    struct noFila *prox;
} noFila;

typedef struct{
    noFila *inicio;
    noFila *fim;
} tipoFila;

void cria_fila(tipoFila *fila_ptr);
int vazia_fila(tipoFila *fila_ptr);
void destroi_fila(tipoFila *fila_ptr);
int insere_fila(tipoFila *fila_ptr, struct conteudoFila pre_reserva);
struct conteudoFila retira_fila(tipoFila *fila_ptr);
void imprime_fila(tipoFila *fila_ptr);
int removerPreReserva(tipoFila *fila_ptr, struct conteudoFila pre_reserva_a_cancelar, int tipo_remocao);
tipoFila* copiarFila(tipoFila *fila_ptr);
tipoFila* ordenar_pre_reservas_recentes(tipoFila* fila_ptr);
tipoFila* ordenar_pre_reservas_antigas(tipoFila* fila_ptr);
int procurar_pre_reserva(struct conteudoFila reserva, tipoFila *fila_ptr); 
struct conteudoFila pre_reserva_procurada(struct conteudoFila pre_reserva, tipoFila *fila_ptr);

#endif