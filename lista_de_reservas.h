#ifndef LISTA_RESERVAS
#define LISTA_RESERVAS

struct conteudoLista{
    struct reserva{
        struct hora_reserva{
            int hora;
            int minutos;
        } hora_reserva;
        
        struct data_reserva{
            int dia;
            int mes;
        } data_reserva;
        char nome[100];
        int tipo_reserva; /* 0 - lavagem ; 1 - manutenção */
    } reserva;
};

typedef struct noLista{
    struct conteudoLista itemLista;
    struct noLista *prox;
} noLista;

typedef noLista *pLista;

void cria_lista(pLista lista_ptr);
int vazia_lista(pLista lista_ptr);
void destroi_lista(pLista lista_ptr);
int insere_lista(pLista lista_ptr, struct conteudoLista reserva);
void imprime_lista(pLista lista_ptr);
int removerReserva(pLista lista_ptr, struct conteudoLista reserva_a_cancelar);
pLista copiarLista(pLista lista_ptr);
pLista ordenar_reservas_recentes(pLista lista_ptr);
pLista ordenar_reservas_antigas(pLista lista_ptr);
int procurar_reserva(struct conteudoLista reserva, pLista lista_ptr);

#endif