#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista_de_reservas.h"
#include "funcoes.h"

void cria_lista(pLista lista_ptr){
    struct conteudoLista reserva = {0};
    if(lista_ptr != NULL){
        lista_ptr -> itemLista = reserva;
        lista_ptr -> prox = NULL;
    }
}

int vazia_lista(pLista lista_ptr){
    if(lista_ptr -> prox == NULL){
        return 1;
    }
    else{ 
        return 0;
    }
}

void destroi_lista(pLista lista_ptr){
    pLista temp_ptr;
    while(!vazia_lista(lista_ptr)){
        temp_ptr = lista_ptr;
        lista_ptr = lista_ptr -> prox;
        free(temp_ptr);
    }
    free(lista_ptr);
}

int insere_lista(pLista lista_ptr, struct conteudoLista reserva){
    pLista novo = (pLista)malloc(sizeof(noLista));
    if(novo == NULL){
        printf("Falha na alocação de memória.\n");
        return 0;
    }

    novo -> itemLista = reserva;
    novo -> prox = NULL;

    if(lista_ptr == NULL){
        lista_ptr = novo; // A lista estava vazia, então o novo nó se torna o primeiro nó.
    } 
    else{
        pLista ultimo = lista_ptr;
        while(ultimo->prox != NULL){
            ultimo = ultimo -> prox;
        }
        ultimo -> prox = novo;
    }
    return 1;
}

void imprime_lista(pLista lista_ptr){
    pLista auxiliar = lista_ptr -> prox; /* Salta o header */
    if(auxiliar == NULL){
        printf("A lista de reservas está vazia!\n");
        return;
    }

    printf("//////////////////////////\nRESERVAS\n//////////////////////////\n");
    printf("--------------------------------------\n");
    while(auxiliar != NULL){
        printf("Nome: %s\n", auxiliar->itemLista.reserva.nome);
        printf("Dia: %d\n", auxiliar -> itemLista.reserva.data_reserva.dia);
        printf("Mês: ");
        switch(auxiliar -> itemLista.reserva.data_reserva.mes){
            case 0:
                printf("0\n");
                break;
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
            default:
                printf("Mês inválido!\n");
        }

        if(auxiliar -> itemLista.reserva.hora_reserva.minutos == 0){
            printf("Hora: %d : 00\n", auxiliar -> itemLista.reserva.hora_reserva.hora);
        }
        else{
            printf("Hora: %d : %d\n", auxiliar -> itemLista.reserva.hora_reserva.hora, 
                                      auxiliar -> itemLista.reserva.hora_reserva.minutos);
        }
        if(auxiliar -> itemLista.reserva.tipo_reserva == 0){
            printf("Tipo de reserva: Lavagem\n");
        }
        else{
            printf("Tipo de reserva: Manutenção\n");
        }
        printf("--------------------------------------\n");
        auxiliar = auxiliar -> prox;
    }
}

int removerReserva(pLista lista_ptr, struct conteudoLista reserva_a_cancelar){
    pLista anterior, atual;

    anterior = NULL;
    atual = lista_ptr;

    // Percorrer a lista até encontrar a reserva com o nome do cliente e o tipo de reserva
    while(atual != NULL){
        if(strcmp(atual->itemLista.reserva.nome, reserva_a_cancelar.reserva.nome) == 0 && 
            atual->itemLista.reserva.tipo_reserva == reserva_a_cancelar.reserva.tipo_reserva &&
            atual -> itemLista.reserva.data_reserva.dia == reserva_a_cancelar.reserva.data_reserva.dia &&
            atual -> itemLista.reserva.data_reserva.mes == reserva_a_cancelar.reserva.data_reserva.mes &&
            atual -> itemLista.reserva.hora_reserva.hora == reserva_a_cancelar.reserva.hora_reserva.hora &&
            atual -> itemLista.reserva.hora_reserva.minutos == reserva_a_cancelar.reserva.hora_reserva.minutos){
            // Se o elemento for encontrado, atualizar o ponteiro 'prox' do nó anterior
            if(anterior != NULL){
                anterior -> prox = atual -> prox;
            } 
            else{
                // Caso contrário, atualizar o ponteiro para o primeiro elemento
                lista_ptr = atual -> prox;
            }
            // Liberar a memória ocupada pelo nó que foi removido
            free(atual);
            return 1;
        }
        anterior = atual;
        atual = atual -> prox;
    }
    return 0;
}

pLista copiarLista(pLista lista_ptr){
    pLista copia = NULL;
    pLista atual = lista_ptr;
    pLista ultimo = NULL;

    while(atual != NULL){
        /* Cria um novo nó e copia o conteúdo do nó lista_ptr para ele */
        pLista novo = (pLista) malloc(sizeof(noLista));
        novo -> itemLista = atual -> itemLista;
        novo -> prox = NULL;

        /* Insere o novo nó no final da lista de cópia */
        if(ultimo == NULL){
            copia = novo;
            ultimo = novo;
        }    
        else{
            ultimo -> prox = novo;
            ultimo = novo;
        }
        atual = atual -> prox;
    }
    return copia;
}

pLista ordenar_reservas_recentes(pLista lista_ptr){
    pLista copia_reservas = copiarLista(lista_ptr);
    pLista listaOrdenada = (pLista) malloc(sizeof(noLista));
    cria_lista(listaOrdenada);
    
    while(copia_reservas != NULL){
        pLista antigo = copia_reservas;
        pLista atual = copia_reservas -> prox;
        while(atual != NULL){
            if(atual->itemLista.reserva.data_reserva.mes > antigo->itemLista.reserva.data_reserva.mes){
                antigo = atual;
            }
            else if(atual->itemLista.reserva.data_reserva.mes == antigo->itemLista.reserva.data_reserva.mes &&
                    atual ->itemLista.reserva.data_reserva.dia > antigo->itemLista.reserva.data_reserva.dia){
                antigo = atual;
            }
            else if(atual->itemLista.reserva.data_reserva.dia == antigo->itemLista.reserva.data_reserva.dia && 
                    atual ->itemLista.reserva.data_reserva.mes == antigo->itemLista.reserva.data_reserva.mes &&
                    atual->itemLista.reserva.hora_reserva.hora > antigo->itemLista.reserva.hora_reserva.hora){
                antigo = atual;
            }
            else if(atual->itemLista.reserva.data_reserva.dia == antigo->itemLista.reserva.data_reserva.dia && 
                    atual ->itemLista.reserva.data_reserva.mes == antigo->itemLista.reserva.data_reserva.mes &&
                    atual->itemLista.reserva.hora_reserva.hora == antigo->itemLista.reserva.hora_reserva.hora && 
                    atual->itemLista.reserva.hora_reserva.minutos > antigo->itemLista.reserva.hora_reserva.minutos){
                antigo = atual;
            }
            atual = atual -> prox;
        }
        
        if(antigo == copia_reservas){
            copia_reservas = copia_reservas -> prox;
        } 
        else{
            pLista anterior = copia_reservas;
            while(anterior -> prox != antigo){
                anterior = anterior -> prox;
            }
            anterior -> prox = antigo -> prox;
        }
        
        antigo -> prox = listaOrdenada;
        listaOrdenada = antigo;
    }

    /* eliminar reserva nula que aparece*/
    struct conteudoLista reserva_nula = {
        .reserva = {
            .data_reserva = {0,0},
            .hora_reserva = {0,0},
            .nome = "a",
            .tipo_reserva = 0
        }
    };

    pLista aux = listaOrdenada -> prox;
    while(aux != NULL){
        if(aux->itemLista.reserva.data_reserva.dia == 0 && aux->itemLista.reserva.data_reserva.mes == 0 &&
           aux->itemLista.reserva.hora_reserva.hora == 0 && aux->itemLista.reserva.hora_reserva.minutos == 0 &&
           aux->itemLista.reserva.tipo_reserva == 0){
            strcpy(aux->itemLista.reserva.nome, "a");
            removerReserva(listaOrdenada, reserva_nula);
        }
        aux = aux -> prox;
    }
    return listaOrdenada;
}

pLista ordenar_reservas_antigas(pLista lista_ptr){
    pLista copia_reservas = copiarLista(lista_ptr);
    pLista listaOrdenada = (pLista) malloc(sizeof(noLista));
    if(listaOrdenada == NULL){
        printf("Erro a alocar memória!\n");
        return 0;
    }
    cria_lista(listaOrdenada);

    while(copia_reservas != NULL){
        pLista antigo = copia_reservas;
        pLista atual = copia_reservas -> prox;
        while(atual != NULL){
            if(atual->itemLista.reserva.data_reserva.mes < antigo->itemLista.reserva.data_reserva.mes){
                antigo = atual;
            }
            else if(atual->itemLista.reserva.data_reserva.mes == antigo->itemLista.reserva.data_reserva.mes &&
                    atual ->itemLista.reserva.data_reserva.dia < antigo->itemLista.reserva.data_reserva.dia){
                antigo = atual;
            }
            else if(atual->itemLista.reserva.data_reserva.dia == antigo->itemLista.reserva.data_reserva.dia && 
                    atual ->itemLista.reserva.data_reserva.mes == antigo->itemLista.reserva.data_reserva.mes &&
                    atual->itemLista.reserva.hora_reserva.hora < antigo->itemLista.reserva.hora_reserva.hora){
                antigo = atual;
            } 
            else if(atual->itemLista.reserva.data_reserva.dia == antigo->itemLista.reserva.data_reserva.dia && 
                    atual ->itemLista.reserva.data_reserva.mes == antigo->itemLista.reserva.data_reserva.mes &&
                    atual->itemLista.reserva.hora_reserva.hora == antigo->itemLista.reserva.hora_reserva.hora && 
                    atual->itemLista.reserva.hora_reserva.minutos < antigo->itemLista.reserva.hora_reserva.minutos){
                antigo = atual;
            }

            atual = atual -> prox;
        }
        
        if(antigo == copia_reservas){
            copia_reservas = copia_reservas -> prox;
        } 
        else{
            pLista anterior = copia_reservas;
            while(anterior -> prox != antigo){
                anterior = anterior -> prox;
            }  
            anterior -> prox = antigo -> prox;
        }
        antigo -> prox = listaOrdenada->prox;
        listaOrdenada->prox = antigo;
    }
    
    /* eliminar reserva nula que aparece */

    struct conteudoLista reserva_nula = {
        .reserva = {
            .data_reserva = {0, 0},
            .hora_reserva = {0, 0},
            .nome = "a",
            .tipo_reserva = 0
        }
    };

    pLista aux = listaOrdenada->prox; // Pula o primeiro elemento nulo
    while(aux != NULL){
        if(aux->itemLista.reserva.data_reserva.dia == 0 && aux->itemLista.reserva.data_reserva.mes == 0 &&
           aux->itemLista.reserva.hora_reserva.hora == 0 && aux->itemLista.reserva.hora_reserva.minutos == 0 &&
           aux->itemLista.reserva.tipo_reserva == 0){
            strcpy(aux->itemLista.reserva.nome, "a");
            removerReserva(listaOrdenada, reserva_nula);
        }
        aux = aux -> prox;
    }    
    return listaOrdenada;
}

int procurar_reserva(struct conteudoLista reserva, pLista lista_ptr){
    pLista aux = lista_ptr -> prox;
    while(aux != NULL){
        if(reserva.reserva.data_reserva.dia == aux ->itemLista.reserva.data_reserva.dia &&
           reserva.reserva.data_reserva.mes == aux ->itemLista.reserva.data_reserva.mes &&
           reserva.reserva.hora_reserva.hora == aux ->itemLista.reserva.hora_reserva.hora &&
           reserva.reserva.hora_reserva.minutos == aux->itemLista.reserva.hora_reserva.minutos){
            return 1;
        }
        aux = aux -> prox;
    }
    return 0;
}