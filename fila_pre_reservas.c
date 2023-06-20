#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fila_pre_reservas.h"

void cria_fila(tipoFila *fila_ptr){ // Coloca a NULL os ponteiros da fila_ptr
    fila_ptr -> inicio = NULL;
    fila_ptr -> fim = NULL;
}

int vazia_fila(tipoFila *fila_ptr){ // verifica se a fila_ptr está vazia (Sim - 1, Não 0;)
    if(fila_ptr -> inicio == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

void destroi_fila(tipoFila *fila_ptr){ // limpa a fila_ptr
    noFila *temp_ptr;
    while(!vazia_fila(fila_ptr)){
        temp_ptr = fila_ptr -> inicio;
        fila_ptr -> inicio = fila_ptr -> inicio -> prox;
        free(temp_ptr);
    }
    if(fila_ptr -> inicio == NULL){
        fila_ptr -> fim = NULL;
    }
    free(fila_ptr);
}

int insere_fila(tipoFila *fila_ptr, struct conteudoFila pre_reserva){
    noFila *temp_ptr;
    temp_ptr = (noFila *) malloc (sizeof(noFila));

    if(temp_ptr != NULL){
        temp_ptr -> itemFila = pre_reserva;
        temp_ptr -> prox = NULL;
        if(vazia_fila(fila_ptr)){
            fila_ptr -> inicio = temp_ptr;
        }
        else{
            fila_ptr -> fim -> prox = temp_ptr;
        }
        fila_ptr -> fim = temp_ptr;
        return 1;
    }
    else{
        return 0;
    }
}

struct conteudoFila retira_fila(tipoFila *fila_ptr){
    noFila *temp_ptr;
    struct conteudoFila pre_reserva;
    if(!vazia_fila(fila_ptr)){
        temp_ptr = fila_ptr -> inicio;
        pre_reserva = temp_ptr -> itemFila;
        fila_ptr -> inicio = fila_ptr -> inicio -> prox;
        if(vazia_fila(fila_ptr)){
            fila_ptr -> fim = NULL;
        }
        free(temp_ptr);
        return (pre_reserva);
    }
    return (struct conteudoFila) {};
}

void imprime_fila(tipoFila *fila_ptr){
    noFila *auxiliar = fila_ptr -> inicio;
    if(auxiliar == NULL){
        printf("A fila de pré-reservas está vazia!\n");
        return;
    }

    printf("//////////////////////////\nPRÉ-RESERVAS\n//////////////////////////\n");
    printf("--------------------------------------\n");
    while(auxiliar != NULL){
        printf("Nome: %s\n", auxiliar->itemFila.pre_reserva.nome);
        printf("Dia: %d\n", auxiliar -> itemFila.pre_reserva.data_pre_reserva.dia);
        printf("Mês: ");
        switch(auxiliar -> itemFila.pre_reserva.data_pre_reserva.mes){
            case 1:
                printf("Janeiro\n");
                break;
            case 2:
                printf("Fevereiro\n");
                break;
            case 3:
                printf("Março\n");
                break;
            case 4:
                printf("Abril\n");
                break;
            case 5:
                printf("Maio\n");
                break;
            case 6:
                printf("Junho\n");
                break;
            case 7:
                printf("Julho\n");
                break;
            case 8:
                printf("Agosto\n");
                break;
            case 9:
                printf("Setembro\n");
                break;
            case 10:
                printf("Outubro\n");
                break;
            case 11:
                printf("Novembro\n");
                break;
            case 12:
                printf("Dezembro\n");
                break;
        }
        if(auxiliar->itemFila.pre_reserva.hora_pre_reserva.minutos == 0){
            printf("Hora: %d : 00\n", auxiliar -> itemFila.pre_reserva.hora_pre_reserva.hora);
        }
        else{
            printf("Hora: %d : %d\n", auxiliar -> itemFila.pre_reserva.hora_pre_reserva.hora, 
                                      auxiliar -> itemFila.pre_reserva.hora_pre_reserva.minutos);
        }
        if(auxiliar -> itemFila.pre_reserva.tipo_pre_reserva == 0){
            printf("Tipo de pré-reserva: Lavagem\n");
        }
        else{
            printf("Tipo de pré-reserva: Manutenção\n");
        }
        printf("--------------------------------------\n");
        auxiliar = auxiliar -> prox;
    }
}

int removerPreReserva(tipoFila *fila_ptr, struct conteudoFila pre_reserva_a_cancelar, int tipo_remocao){
    // Percorrer a fila_ptr até encontrar a reserva com o nome do cliente e o tipo de reserva
    noFila *anterior = NULL;
    noFila *atual = fila_ptr -> inicio;

    while(atual != NULL){
        if(tipo_remocao == 0){
            if(strcmp(atual->itemFila.pre_reserva.nome, pre_reserva_a_cancelar.pre_reserva.nome) == 0 && 
                atual->itemFila.pre_reserva.tipo_pre_reserva == pre_reserva_a_cancelar.pre_reserva.tipo_pre_reserva &&
                atual -> itemFila.pre_reserva.data_pre_reserva.dia == pre_reserva_a_cancelar.pre_reserva.data_pre_reserva.dia &&
                atual -> itemFila.pre_reserva.data_pre_reserva.mes == pre_reserva_a_cancelar.pre_reserva.data_pre_reserva.mes &&
                atual -> itemFila.pre_reserva.hora_pre_reserva.hora == pre_reserva_a_cancelar.pre_reserva.hora_pre_reserva.hora &&
                atual -> itemFila.pre_reserva.hora_pre_reserva.minutos == pre_reserva_a_cancelar.pre_reserva.hora_pre_reserva.minutos){
                // Se o elemento for encontrado, atualizar o ponteiro 'prox' do nó anterior
                if(anterior != NULL){
                    anterior -> prox = atual -> prox;
                } 
                else{
                    // Caso contrário, atualizar o ponteiro para o primeiro elemento
                    fila_ptr -> inicio = atual -> prox;
                }

                // Se o nó a ser removido for o último, atualizar o ponteiro 'fim' da fila_ptr
                if(atual == fila_ptr->fim){
                    fila_ptr -> fim = anterior;
                }

                // Atualizar o ponteiro 'atual' antes de liberar o nó da memória
                noFila *temp = atual;
                atual = atual -> prox;

                // Verificar se o nó já foi removido antes de liberá-lo da memória
                if(temp != NULL){
                    free(temp);
                }
                return 1;
            }
        }

        if(tipo_remocao == 1){
            if(atual->itemFila.pre_reserva.tipo_pre_reserva == pre_reserva_a_cancelar.pre_reserva.tipo_pre_reserva &&
               atual -> itemFila.pre_reserva.data_pre_reserva.dia == pre_reserva_a_cancelar.pre_reserva.data_pre_reserva.dia &&
               atual -> itemFila.pre_reserva.data_pre_reserva.mes == pre_reserva_a_cancelar.pre_reserva.data_pre_reserva.mes &&
               atual -> itemFila.pre_reserva.hora_pre_reserva.hora == pre_reserva_a_cancelar.pre_reserva.hora_pre_reserva.hora &&
               atual -> itemFila.pre_reserva.hora_pre_reserva.minutos == pre_reserva_a_cancelar.pre_reserva.hora_pre_reserva.minutos){
                // Se o elemento for encontrado, atualizar o ponteiro 'prox' do nó anterior
                if(anterior != NULL){
                    anterior -> prox = atual -> prox;
                } 
                else{
                    // Caso contrário, atualizar o ponteiro para o primeiro elemento
                    fila_ptr -> inicio = atual -> prox;
                }

                // Se o nó a ser removido for o último, atualizar o ponteiro 'fim' da fila_ptr
                if(atual == fila_ptr->fim){
                    fila_ptr -> fim = anterior;
                }

                // Atualizar o ponteiro 'atual' antes de liberar o nó da memória
                noFila *temp = atual;
                atual = atual -> prox;

                // Verificar se o nó já foi removido antes de liberá-lo da memória
                if(temp != NULL){
                    free(temp);
                }
                return 1;
            }
        }
        anterior = atual;
        atual = atual -> prox;
    }
    return 0;
}

tipoFila* copiarFila(tipoFila *fila_ptr){
    tipoFila* copia_fila = (tipoFila*) malloc(sizeof(tipoFila));
    cria_fila(copia_fila);
    noFila* atual = fila_ptr -> inicio;

    while(atual != NULL) {
        insere_fila(copia_fila, atual->itemFila);
        atual = atual->prox;
    }
    return copia_fila;
}

tipoFila* ordenar_pre_reservas_recentes(tipoFila* fila_ptr){
    tipoFila* copia_pre_reservas = copiarFila(fila_ptr);
    tipoFila* filaOrdenada = (tipoFila*) malloc(sizeof(tipoFila));
    cria_fila(filaOrdenada);

    if(copia_pre_reservas->inicio == NULL){
        free(copia_pre_reservas);
        return filaOrdenada;
    }

    while(copia_pre_reservas->inicio != NULL){
        noFila* antigo = copia_pre_reservas -> inicio;
        noFila* atual = copia_pre_reservas -> inicio -> prox;
        noFila* antigo_anterior = NULL;
        noFila* atual_anterior = copia_pre_reservas -> inicio;

        while(atual != NULL){
            if(atual->itemFila.pre_reserva.data_pre_reserva.mes < antigo->itemFila.pre_reserva.data_pre_reserva.mes){
                antigo = atual;
                antigo_anterior = atual_anterior;
            } 
            else if(atual->itemFila.pre_reserva.data_pre_reserva.mes == antigo->itemFila.pre_reserva.data_pre_reserva.mes &&
                    atual->itemFila.pre_reserva.data_pre_reserva.dia < antigo->itemFila.pre_reserva.data_pre_reserva.dia){
                antigo = atual;
                antigo_anterior = atual_anterior;
            } 
            else if(atual->itemFila.pre_reserva.data_pre_reserva.dia == antigo->itemFila.pre_reserva.data_pre_reserva.dia &&
                    atual->itemFila.pre_reserva.data_pre_reserva.mes == antigo->itemFila.pre_reserva.data_pre_reserva.mes &&
                    atual->itemFila.pre_reserva.hora_pre_reserva.hora < antigo->itemFila.pre_reserva.hora_pre_reserva.hora){
                antigo = atual;
                antigo_anterior = atual_anterior;
            } 
            else if(atual->itemFila.pre_reserva.data_pre_reserva.dia == antigo->itemFila.pre_reserva.data_pre_reserva.dia &&
                    atual->itemFila.pre_reserva.data_pre_reserva.mes == antigo->itemFila.pre_reserva.data_pre_reserva.mes &&
                    atual->itemFila.pre_reserva.hora_pre_reserva.hora == antigo->itemFila.pre_reserva.hora_pre_reserva.hora &&
                    atual->itemFila.pre_reserva.hora_pre_reserva.minutos < antigo->itemFila.pre_reserva.hora_pre_reserva.minutos){
                antigo = atual;
                antigo_anterior = atual_anterior;
            }

            atual_anterior = atual;
            atual = atual -> prox;
        }

        if (antigo_anterior == NULL) {
            copia_pre_reservas -> inicio = copia_pre_reservas -> inicio -> prox;
        } 
        else{
            antigo_anterior -> prox = antigo -> prox;
        }

        if(antigo == copia_pre_reservas->fim){
            copia_pre_reservas -> fim = antigo_anterior;
        }

        antigo -> prox = NULL;

        if(filaOrdenada -> inicio == NULL){
            filaOrdenada -> inicio = antigo;
            filaOrdenada -> fim = antigo;
        } 
        else{
            if(antigo != filaOrdenada -> fim){ // Verifica se o elemento já foi adicionado anteriormente
                filaOrdenada -> fim -> prox = antigo;
                filaOrdenada -> fim = antigo;
            }
        }
    }
    destroi_fila(copia_pre_reservas);
    return filaOrdenada;
}

tipoFila* ordenar_pre_reservas_antigas(tipoFila* fila_ptr){
    tipoFila* copia_pre_reservas = copiarFila(fila_ptr);
    tipoFila* filaOrdenada = (tipoFila*) malloc(sizeof(tipoFila));
    cria_fila(filaOrdenada);

    if(copia_pre_reservas->inicio == NULL){
        free(copia_pre_reservas);
        return filaOrdenada;
    }

    while(copia_pre_reservas->inicio != NULL){
        noFila* antigo = copia_pre_reservas -> inicio;
        noFila* atual = copia_pre_reservas -> inicio -> prox;
        noFila* antigo_anterior = NULL;
        noFila* atual_anterior = copia_pre_reservas -> inicio;

        while(atual != NULL){
            if(atual->itemFila.pre_reserva.data_pre_reserva.mes > antigo->itemFila.pre_reserva.data_pre_reserva.mes){
                antigo = atual;
                antigo_anterior = atual_anterior;
            } 
            else if(atual->itemFila.pre_reserva.data_pre_reserva.mes == antigo->itemFila.pre_reserva.data_pre_reserva.mes &&
                    atual->itemFila.pre_reserva.data_pre_reserva.dia > antigo->itemFila.pre_reserva.data_pre_reserva.dia){
                antigo = atual;
                antigo_anterior = atual_anterior;
            } 
            else if(atual->itemFila.pre_reserva.data_pre_reserva.dia == antigo->itemFila.pre_reserva.data_pre_reserva.dia &&
                    atual->itemFila.pre_reserva.data_pre_reserva.mes == antigo->itemFila.pre_reserva.data_pre_reserva.mes &&
                    atual->itemFila.pre_reserva.hora_pre_reserva.hora > antigo->itemFila.pre_reserva.hora_pre_reserva.hora){
                antigo = atual;
                antigo_anterior = atual_anterior;
            } 
            else if(atual->itemFila.pre_reserva.data_pre_reserva.dia == antigo->itemFila.pre_reserva.data_pre_reserva.dia &&
                    atual->itemFila.pre_reserva.data_pre_reserva.mes == antigo->itemFila.pre_reserva.data_pre_reserva.mes &&
                    atual->itemFila.pre_reserva.hora_pre_reserva.hora == antigo->itemFila.pre_reserva.hora_pre_reserva.hora &&
                    atual->itemFila.pre_reserva.hora_pre_reserva.minutos > antigo->itemFila.pre_reserva.hora_pre_reserva.minutos){
                antigo = atual;
                antigo_anterior = atual_anterior;
            }

            atual_anterior = atual;
            atual = atual -> prox;
        }

        if (antigo_anterior == NULL) {
            copia_pre_reservas -> inicio = copia_pre_reservas -> inicio -> prox;
        } 
        else {
            antigo_anterior -> prox = antigo -> prox;
        }

        if(antigo == copia_pre_reservas->fim){
            copia_pre_reservas -> fim = antigo_anterior;
        }

        antigo -> prox = NULL;

        if(filaOrdenada -> inicio == NULL){
            filaOrdenada -> inicio = antigo;
            filaOrdenada -> fim = antigo;
        } 
        else{
            if(antigo != filaOrdenada -> fim){ // Verifica se o elemento já foi adicionado anteriormente
                filaOrdenada -> fim -> prox = antigo;
                filaOrdenada -> fim = antigo;
            }
        }
    }
    destroi_fila(copia_pre_reservas);
    return filaOrdenada;
}

int procurar_pre_reserva(struct conteudoFila pre_reserva, tipoFila *fila_ptr){
    noFila* aux = fila_ptr -> inicio;
    while(aux != NULL){
        if(pre_reserva.pre_reserva.data_pre_reserva.dia == aux ->itemFila.pre_reserva.data_pre_reserva.dia &&
           pre_reserva.pre_reserva.data_pre_reserva.mes == aux ->itemFila.pre_reserva.data_pre_reserva.mes &&
           pre_reserva.pre_reserva.hora_pre_reserva.hora == aux ->itemFila.pre_reserva.hora_pre_reserva.hora &&
           pre_reserva.pre_reserva.hora_pre_reserva.minutos == aux->itemFila.pre_reserva.hora_pre_reserva.minutos &&
           pre_reserva.pre_reserva.tipo_pre_reserva == aux->itemFila.pre_reserva.tipo_pre_reserva){
            return 1;
        }
        aux = aux -> prox;
    }
    return 0;
}

struct conteudoFila pre_reserva_procurada(struct conteudoFila pre_reserva, tipoFila *fila_ptr){
    struct conteudoFila reserva_nula = {
        .pre_reserva = {
            .data_pre_reserva = {0,0},
            .hora_pre_reserva = {0,0},
            .nome = "a",
            .tipo_pre_reserva = 0
        }
    };

    noFila* aux = fila_ptr -> inicio;
    while(aux != NULL){
        if(pre_reserva.pre_reserva.data_pre_reserva.dia == aux ->itemFila.pre_reserva.data_pre_reserva.dia &&
           pre_reserva.pre_reserva.data_pre_reserva.mes == aux ->itemFila.pre_reserva.data_pre_reserva.mes &&
           pre_reserva.pre_reserva.hora_pre_reserva.hora == aux ->itemFila.pre_reserva.hora_pre_reserva.hora &&
           pre_reserva.pre_reserva.hora_pre_reserva.minutos == aux->itemFila.pre_reserva.hora_pre_reserva.minutos &&
           pre_reserva.pre_reserva.tipo_pre_reserva == aux->itemFila.pre_reserva.tipo_pre_reserva){
            return aux->itemFila;
        }
        aux = aux -> prox;
    }
    return reserva_nula;
}