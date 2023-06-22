#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funcoes.h"

int reservar(int tipo_de_reserva, pLista lista_ptr, tipoFila *fila_ptr){
    struct conteudoLista reserva;

    /* Input do utilizador */

    reserva.reserva.data_reserva.dia = input_int("Dia: ");
    reserva.reserva.data_reserva.mes = input_int("Mês: ");

    while(validar_data(reserva.reserva.data_reserva.mes, reserva.reserva.data_reserva.dia) == 0){
        printf("Data inválida! Tente novamente.\n");
        reserva.reserva.data_reserva.dia = input_int("Dia: ");
        reserva.reserva.data_reserva.mes = input_int("Mês: ");
    }

    reserva.reserva.hora_reserva.hora = input_int("Hora: ");
    reserva.reserva.hora_reserva.minutos = input_int("Minutos: ");
    while(!validar_horas(reserva.reserva.hora_reserva.hora, reserva.reserva.hora_reserva.minutos)){
        printf("A hora que escreveu está errada! O horário de funcionamento é das 8h00m - 18h00m\n");
        reserva.reserva.hora_reserva.hora = input_int("Hora: ");
        reserva.reserva.hora_reserva.minutos = input_int("Minutos: ");
    }

    getchar(); /* getchar() - remover o '\n' que resta do input anterior! */
    strcpy(reserva.reserva.nome, input_string("Nome: "));
    reserva.reserva.tipo_reserva = tipo_de_reserva;

    /* verificar se já existe uma reserva marcada */
    if(procurar_reserva(reserva, lista_ptr)){
        int escolha = 1;
        do{
            printf("Já existe reserva nessa hora! Pretende pré-reservar?\n0 - Sim\n1 - Não\n");
            escolha = input_int("Escolha a opção que deseja: ");
            switch(escolha){
                case 0:
                    struct conteudoFila pre_reserva = reserva_para_pre_reserva(reserva);
                    int f_pre_reservar = pre_reservar(pre_reserva, fila_ptr);
                    if(f_pre_reservar == 1){
                        return 2;
                    }
                    if(f_pre_reservar == -1){
                        return -2;
                    }
                    if(f_pre_reservar == 0){
                        return -3;
                    }
                break;
                case 1:
                    return 0;
                    break;
                default:
                    printf("Escolha uma opção válida!\n");
                    break;
            }
        } while(escolha < 0 || escolha > 1);
    }

    /* verificar se a reserva pode ser inserida */
    if(verificar_disponibilidade(lista_ptr, reserva)){
        if(insere_lista(lista_ptr, reserva)){
        return 1;
        }
        return 0;
    }
    return 0;
}

int pre_reservar(struct conteudoFila pre_reserva, tipoFila *fila_ptr){
    if(procurar_pre_reserva(pre_reserva, fila_ptr)){
        return -1; /* pré-reserva já marcada na mesma hora */
    }

    if(insere_fila(fila_ptr, pre_reserva)){
        return 1;
    }
    return 0;
}

int cancelar_reserva(int tipo_de_reserva, pLista lista_ptr, tipoFila *fila_ptr){
    struct conteudoLista reserva_a_cancelar;

    /* Input do utilizador */

    reserva_a_cancelar.reserva.tipo_reserva = tipo_de_reserva;
    reserva_a_cancelar.reserva.data_reserva.dia = input_int("Dia: ");
    reserva_a_cancelar.reserva.data_reserva.mes = input_int("Mês: ");
    while(!validar_data(reserva_a_cancelar.reserva.data_reserva.mes, reserva_a_cancelar.reserva.data_reserva.dia)){
        printf("Data inválida! Tente novamente.\n");
        reserva_a_cancelar.reserva.data_reserva.dia = input_int("Dia: ");
        reserva_a_cancelar.reserva.data_reserva.mes = input_int("Mês: ");   
    }
    reserva_a_cancelar.reserva.hora_reserva.hora = input_int("Hora: ");
    reserva_a_cancelar.reserva.hora_reserva.minutos = input_int("Minutos: ");
    while(!validar_horas(reserva_a_cancelar.reserva.hora_reserva.hora, reserva_a_cancelar.reserva.hora_reserva.minutos)){
        printf("A hora que escreveu está errada! O horário de funcionamento é das 8h00m - 18h00m\n");
        reserva_a_cancelar.reserva.hora_reserva.hora = input_int("Hora: ");
        reserva_a_cancelar.reserva.hora_reserva.minutos = input_int("Minutos: ");
    }
    getchar();
    strcpy(reserva_a_cancelar.reserva.nome, input_string("Em que nome está marcada a reserva: "));
    
    struct conteudoFila pre_reserva_compativel = verificar_compatibilidade(reserva_a_cancelar, fila_ptr, lista_ptr);
    printf("Nome: %s\n", pre_reserva_compativel.pre_reserva.nome);
    printf("Dia: %d\n",pre_reserva_compativel.pre_reserva.data_pre_reserva.dia);
    printf("Mês: %d\n", pre_reserva_compativel.pre_reserva.data_pre_reserva.mes);
    printf("Hora: %d : %d\n", pre_reserva_compativel.pre_reserva.hora_pre_reserva.hora, 
                                pre_reserva_compativel.pre_reserva.hora_pre_reserva.minutos);
    if(pre_reserva_compativel.pre_reserva.tipo_pre_reserva == 0){
        printf("Tipo de pré-reserva: Lavagem\n");
    }
    else{
        printf("Tipo de pré-reserva: Manutenção\n");
    }
    /* verificar se existe alguma pré-reserva compatível */
    if(pre_reserva_compativel.pre_reserva.hora_pre_reserva.hora != 0){
        int escolha = 1;
        do{
            printf("Foi encontrada uma pré-reserva compatível com o horário da reserva cancelada. Pretende colocar a pré-reserva no buraco deixado?\n");
            printf("0 - Sim\n1 - Não\n\n"); 
            escolha = input_int("Escolha que a opção que deseja: ");
            switch(escolha){
                case 0:
                    struct conteudoLista reserva_compativel = pre_reserva_para_reserva(pre_reserva_compativel);
                    if(insere_lista(lista_ptr, reserva_compativel) && removerReserva(lista_ptr, reserva_a_cancelar)){
                        if(removerPreReserva(fila_ptr, pre_reserva_compativel, 1)){
                            return 2;
                        }
                        return -2;
                    }
                    return -1;
                    break;
                case 1:
                    if(removerReserva(lista_ptr, reserva_a_cancelar)){
                        return 1;
                    }
                    return 0;
                    break;
                default:
                    printf("Insira uma opção váldida!\n");
                    break;
            }
        } while(escolha < 0 || escolha > 1);
    }

    if(removerReserva(lista_ptr, reserva_a_cancelar)){
        return 1;
    }
    return 0;
}

int cancelar_pre_reserva(int tipo_de_pre_reserva, tipoFila *fila_ptr){
    struct conteudoFila pre_reserva_a_cancelar;

    /* Input do utilizador */

    pre_reserva_a_cancelar.pre_reserva.tipo_pre_reserva = tipo_de_pre_reserva;
    pre_reserva_a_cancelar.pre_reserva.data_pre_reserva.dia = input_int("Dia: ");
    pre_reserva_a_cancelar.pre_reserva.data_pre_reserva.mes = input_int("Mês: ");
    while(!validar_data(pre_reserva_a_cancelar.pre_reserva.data_pre_reserva.mes, pre_reserva_a_cancelar.pre_reserva.data_pre_reserva.dia)){
        printf("Data inválida! Tente novamente.\n");
        pre_reserva_a_cancelar.pre_reserva.data_pre_reserva.dia = input_int("Dia: ");
        pre_reserva_a_cancelar.pre_reserva.data_pre_reserva.mes = input_int("Mês: ");   
    }
    pre_reserva_a_cancelar.pre_reserva.hora_pre_reserva.hora = input_int("Hora: ");
    pre_reserva_a_cancelar.pre_reserva.hora_pre_reserva.minutos = input_int("Minutos: ");
    while(!validar_horas(pre_reserva_a_cancelar.pre_reserva.hora_pre_reserva.hora, pre_reserva_a_cancelar.pre_reserva.hora_pre_reserva.minutos)){
        printf("A hora que escreveu está errada! O horário de funcionamento é das 8h00m - 18h00m\n");
        pre_reserva_a_cancelar.pre_reserva.hora_pre_reserva.hora = input_int("Hora: ");
        pre_reserva_a_cancelar.pre_reserva.hora_pre_reserva.minutos = input_int("Minutos: ");
    }
    getchar();
    strcpy(pre_reserva_a_cancelar.pre_reserva.nome, input_string("Em que nome está marcada a reserva: "));
    if(removerPreReserva(fila_ptr, pre_reserva_a_cancelar, 0)){
        return 1;
    }
    return 0;
}

int carregar_dados(pLista lista_ptr, tipoFila *fila_ptr){
    char linha[100];
    char *token;

    /* Carregar Reservas */

    struct conteudoLista reserva;
    
    FILE *reservas = fopen("reservas.txt", "r");
    while(reservas == NULL){
        reservas = fopen("reservas.txt", "w");
    }

    /* hora - minutos - dia - tipo de reserva - nome*/

    while(fgets(linha, 100, reservas) != NULL){
        token = strtok(linha, "-");
        reserva.reserva.hora_reserva.hora = str_to_int(token);
        token = strtok(NULL, "-");
        reserva.reserva.hora_reserva.minutos = str_to_int(token);
        token = strtok(NULL, "-");
        reserva.reserva.data_reserva.dia = str_to_int(token);
        token = strtok(NULL, "-");
        reserva.reserva.data_reserva.mes = str_to_int(token);
        token = strtok(NULL, "-");
        reserva.reserva.tipo_reserva = str_to_int(token);
        token = strtok(NULL, "-");
        for(long unsigned int i = 0; i < strlen(token); i++){
            if(token[i] == '\n'){
                token[i] = '\0';
                break;
            }
        }
        strcpy(reserva.reserva.nome, token);
        insere_lista(lista_ptr, reserva);
    }
    if(fclose(reservas)){
        perror("Erro a fechar o ficheiro das reservas: ");
        return 0;
    }

    /* Carregar Pré-Reservas */

    struct conteudoFila pre_reserva;
    FILE *pre_reservas = fopen("pre_reservas.txt", "r");
    while(pre_reservas == NULL){
        pre_reservas = fopen("pre_reservas.txt", "w");
    }
    /* hora - minutos - dia - tipo de reserva - nome*/
    while(fgets(linha, 100, pre_reservas) != NULL){
        token = strtok(linha, "-");
        pre_reserva.pre_reserva.hora_pre_reserva.hora = str_to_int(token);
        token = strtok(NULL, "-");
        pre_reserva.pre_reserva.hora_pre_reserva.minutos = str_to_int(token);
        token = strtok(NULL, "-");
        pre_reserva.pre_reserva.data_pre_reserva.dia = str_to_int(token);
        token = strtok(NULL, "-");
        pre_reserva.pre_reserva.data_pre_reserva.mes = str_to_int(token);
        token = strtok(NULL, "-");
        pre_reserva.pre_reserva.tipo_pre_reserva = str_to_int(token);
        token = strtok(NULL, "-");
        for(long unsigned int i = 0; i < strlen(token); i++){
            if(token[i] == '\n'){
                token[i] = '\0';
                break;
            }
        }
        strcpy(pre_reserva.pre_reserva.nome, token);
        insere_fila(fila_ptr, pre_reserva);
    }
    if(fclose(pre_reservas)){
        perror("Erro a fechar o ficheiro das pré-reservas: ");
        return 0;
    }
    return 1;
}

int guardar_dados(pLista lista_ptr, tipoFila *fila_ptr){
    /* Guardar Reservas*/

    pLista aux = lista_ptr -> prox;
    FILE *reservas = fopen("reservas.txt", "w");
    while(reservas == NULL){
        reservas = fopen("reservas.txt", "w");      
    }

    /* hora - minutos - dia - mes - tipo de reserva - nome */
    while(aux != NULL){
        fprintf(reservas, "%d-", aux -> itemLista.reserva.hora_reserva.hora);
        fprintf(reservas, "%d-", aux -> itemLista.reserva.hora_reserva.minutos);
        fprintf(reservas, "%d-", aux -> itemLista.reserva.data_reserva.dia);
        fprintf(reservas, "%d-", aux ->itemLista.reserva.data_reserva.mes);
        fprintf(reservas, "%d-", aux -> itemLista.reserva.tipo_reserva);
        fprintf(reservas, "%s\n", aux -> itemLista.reserva.nome);
        aux = aux -> prox;
    }
    if(fclose(reservas)){
        perror("Erro a fechar o ficheiro das reservas: ");
        return 0;
    }

    /* Guardar pré - reservas */

    noFila *auxiliar = fila_ptr -> inicio;
    FILE *pre_reservas = fopen("pre_reservas.txt", "w");
    while(pre_reservas == NULL){
        pre_reservas = fopen("pre_reservas.txt", "w");
    }
    while(auxiliar != NULL){
        fprintf(pre_reservas,"%d-", auxiliar -> itemFila.pre_reserva.hora_pre_reserva.hora);
        fprintf(pre_reservas,"%d-", auxiliar -> itemFila.pre_reserva.hora_pre_reserva.minutos);
        fprintf(pre_reservas,"%d-", auxiliar -> itemFila.pre_reserva.data_pre_reserva.dia);
        fprintf(pre_reservas, "%d-", auxiliar ->itemFila.pre_reserva.data_pre_reserva.mes);
        fprintf(pre_reservas,"%d-", auxiliar -> itemFila.pre_reserva.tipo_pre_reserva);
        fprintf(pre_reservas,"%s\n", auxiliar -> itemFila.pre_reserva.nome);
        auxiliar = auxiliar -> prox;
    }
    free(auxiliar);
    if(fclose(pre_reservas)){
        perror("Erro a fechar o ficheiro das pré-reservas: ");
        return 0;
    }
    return 1;
}

int executar_servico(pLista lista_ptr, tipoFila *fila_ptr){
    if(vazia_lista(lista_ptr)){
        printf("A lista de reservas está vazia!\n");
        return -1;
    }

    pLista listaOrdenada = ordenar_reservas_recentes(lista_ptr);
    pLista atual = listaOrdenada -> prox;
    struct conteudoLista reserva_a_ser_cancelada = atual ->itemLista;

    if(removerReserva(lista_ptr, reserva_a_ser_cancelada)){ /* eliminar 1ª reserva */
        /* eliminar pré-reservas cuja hora e data sejam anteriores à da reserva eliminada */
        noFila *aux = fila_ptr->inicio;
        while(aux != NULL){
            if(aux->itemFila.pre_reserva.data_pre_reserva.mes <= reserva_a_ser_cancelada.reserva.data_reserva.mes){
                removerPreReserva(fila_ptr, aux->itemFila, 1);
            }
            
            if(aux->itemFila.pre_reserva.data_pre_reserva.mes == reserva_a_ser_cancelada.reserva.data_reserva.mes &&
               aux->itemFila.pre_reserva.data_pre_reserva.dia <= reserva_a_ser_cancelada.reserva.data_reserva.dia){
                removerPreReserva(fila_ptr, aux->itemFila, 1);
            }

            if(aux->itemFila.pre_reserva.data_pre_reserva.dia == reserva_a_ser_cancelada.reserva.data_reserva.dia &&
               aux->itemFila.pre_reserva.data_pre_reserva.mes == reserva_a_ser_cancelada.reserva.data_reserva.mes &&
               aux->itemFila.pre_reserva.hora_pre_reserva.hora <= reserva_a_ser_cancelada.reserva.hora_reserva.hora){
                removerPreReserva(fila_ptr, aux->itemFila, 1);
            }

            if(aux->itemFila.pre_reserva.data_pre_reserva.dia == reserva_a_ser_cancelada.reserva.data_reserva.dia &&
               aux->itemFila.pre_reserva.data_pre_reserva.mes == reserva_a_ser_cancelada.reserva.data_reserva.mes &&
               aux->itemFila.pre_reserva.hora_pre_reserva.hora == reserva_a_ser_cancelada.reserva.hora_reserva.hora &&
               aux->itemFila.pre_reserva.hora_pre_reserva.minutos <= reserva_a_ser_cancelada.reserva.hora_reserva.minutos){
                removerPreReserva(fila_ptr, aux->itemFila, 1);
            }
            aux = aux -> prox;
        }
        return 1;
    }
    destroi_lista(listaOrdenada);
    return 0;
}

void listar_reservas_e_prereservas_por_data(pLista lista_ptr, tipoFila *fila_ptr){
    pLista listaOrdenada = ordenar_reservas_antigas(lista_ptr);
    imprime_lista(listaOrdenada);
    destroi_lista(listaOrdenada);

    tipoFila* filaOrdenada = ordenar_pre_reservas_antigas(fila_ptr);
    imprime_fila(filaOrdenada);
    destroi_fila(filaOrdenada);
}

void listar_reservas_prereservas_cliente(pLista lista_ptr, tipoFila *fila_ptr, char *nome_cliente){
    pLista lista_reservas_cliente = (pLista) malloc(sizeof(noLista));
    tipoFila *fila_pre_reservas_cliente = (tipoFila*) malloc(sizeof(tipoFila));
   
    if(lista_reservas_cliente == NULL || fila_pre_reservas_cliente == NULL){
        printf("Memória não disponível!\n");
        return;
    }
    
    cria_fila(fila_pre_reservas_cliente);
    cria_lista(lista_reservas_cliente);

    /* Procurar reservas do cliente na lista */
    pLista aux_lista = lista_ptr -> prox;
    while(aux_lista != NULL){
        if(strcmp(aux_lista->itemLista.reserva.nome, nome_cliente) == 0){
            insere_lista(lista_reservas_cliente, aux_lista->itemLista);
        }
        aux_lista = aux_lista -> prox;
    }
    /* Procurar pré-reservas do cliente na fila */
    noFila* aux_fila = fila_ptr->inicio;
    while(aux_fila != NULL){
        if(strcmp(aux_fila->itemFila.pre_reserva.nome, nome_cliente) == 0) {
            insere_fila(fila_pre_reservas_cliente, aux_fila->itemFila);
        }
        aux_fila = aux_fila->prox;
    }

    pLista listaOrdenada = ordenar_reservas_recentes(lista_reservas_cliente);
    tipoFila* filaOrdenada = ordenar_pre_reservas_recentes(fila_pre_reservas_cliente);
    
    imprime_lista(listaOrdenada);
    imprime_fila(filaOrdenada);

    destroi_lista(listaOrdenada);
    destroi_fila(filaOrdenada);
}

int verificar_disponibilidade(pLista lista_ptr, struct conteudoLista reserva){
    if(vazia_lista(lista_ptr)){
        return 1;
    }

    int cont = 0, tempo_ocupado_reserva, tempo_ocupado_ant, tempo_ocupado_atual, tempo_ocupado_prox, diferença_tempo, hora_ant, hora_atual, hora_prox; 
    int hora_reserva = hora_para_minutos(reserva.reserva.hora_reserva.hora, reserva.reserva.hora_reserva.minutos);
    if(reserva.reserva.tipo_reserva == 0){
        tempo_ocupado_reserva = 30;
    }
    else{
        tempo_ocupado_reserva = 60;
    }
    /* se a reserva passa das 18h00 */
    if((hora_reserva + tempo_ocupado_reserva) > hora_para_minutos(18,0)){
        return 0;
    }
    pLista listaOrdenada = ordenar_reservas_recentes(lista_ptr);
    pLista aux = listaOrdenada->prox;

    while(aux != NULL){
        cont++;
        aux = aux -> prox;
    }
    printf("Contador: %d\n", cont);
    free(aux);

    pLista atual, proximo;
    /* SÓ EXISTE UMA RESERVA NA LISTA */
    if(cont == 1){
        atual = listaOrdenada -> prox;
        if(atual->itemLista.reserva.tipo_reserva == 0){
            tempo_ocupado_atual = 30;
        }
        else{
            tempo_ocupado_atual = 60;
        }
        hora_atual = hora_para_minutos(atual->itemLista.reserva.hora_reserva.hora, atual->itemLista.reserva.hora_reserva.minutos);
        
        /* se a reserva sobrepõe a única reserva presente na lista */
        if(hora_reserva < (hora_atual + tempo_ocupado_atual)){
            return 0;
        }
        return 1;
    }
    /* EXISTEM DUAS RESERVAS */
    else if(cont == 2){
        atual = listaOrdenada->prox;
        proximo = atual->prox;
        if(atual->itemLista.reserva.tipo_reserva == 0){
            tempo_ocupado_atual = 30;
        } else{
            tempo_ocupado_atual = 60;
        }
        hora_atual = hora_para_minutos(atual->itemLista.reserva.hora_reserva.hora, atual->itemLista.reserva.hora_reserva.minutos);
        
        if(proximo->itemLista.reserva.tipo_reserva == 0){
            tempo_ocupado_prox = 30;
        } else{
            tempo_ocupado_prox = 60;
        }
        hora_prox = hora_para_minutos(proximo->itemLista.reserva.hora_reserva.hora, proximo->itemLista.reserva.hora_reserva.minutos);

        /* 1a hipótese - inserir no ínicio da lista */
        if(hora_reserva < hora_atual){
            if((hora_reserva + tempo_ocupado_reserva) > hora_atual){
                return 0;
            }
            return 1;
        }
        /* 2a hipotese - inserir entre atual e prox */
        else if(hora_reserva > hora_atual && hora_reserva < hora_prox){
            if((hora_atual + tempo_ocupado_atual) > hora_reserva){
                return 0;
            }
            if((hora_reserva + tempo_ocupado_reserva) > hora_prox){
                return 0;
            }
            return 1;
        }
        /* 3a hipotese - inserir no fim da lista */
        else if(hora_reserva > hora_prox){
            if((hora_prox + tempo_ocupado_prox) > hora_reserva){
                return 0;
            }
            return 1;
        }
    }
    /* MAIS DE 2 RESERVAS*/
    else{
        pLista anterior = listaOrdenada -> prox;
        atual = anterior->prox;
        proximo = atual->prox;
        if(anterior->itemLista.reserva.tipo_reserva == 0){
            tempo_ocupado_ant= 30;
        } else{
            tempo_ocupado_ant = 60;
        }
        hora_ant = hora_para_minutos(anterior->itemLista.reserva.hora_reserva.hora, anterior->itemLista.reserva.hora_reserva.minutos);
        /* inserir no ínicio da lista */
        if(reserva.reserva.data_reserva.mes == anterior->itemLista.reserva.data_reserva.mes &&
           reserva.reserva.data_reserva.dia == anterior->itemLista.reserva.data_reserva.mes &&
           reserva.reserva.hora_reserva.hora == anterior->itemLista.reserva.hora_reserva.hora && 
           reserva.reserva.hora_reserva.minutos < anterior->itemLista.reserva.hora_reserva.minutos){
            if((hora_reserva + tempo_ocupado_reserva) > hora_ant){
                return 0;
            }
            return 1;
        }
        if(reserva.reserva.data_reserva.mes == anterior->itemLista.reserva.data_reserva.mes &&
           reserva.reserva.data_reserva.dia == anterior->itemLista.reserva.data_reserva.dia &&
           reserva.reserva.hora_reserva.hora < anterior->itemLista.reserva.hora_reserva.hora){
            if((hora_reserva + tempo_ocupado_reserva) > hora_ant){
                return 0;
            }
            return 1;
        }
        if(reserva.reserva.data_reserva.mes == anterior->itemLista.reserva.data_reserva.mes &&
           reserva.reserva.data_reserva.dia < anterior->itemLista.reserva.data_reserva.dia){
            return 1;
        }
        if(reserva.reserva.data_reserva.mes < anterior->itemLista.reserva.data_reserva.mes){
            return 1;
        }
        while(proximo != NULL){
            if(anterior->itemLista.reserva.tipo_reserva == 0){
                tempo_ocupado_ant = 30;
            } else{
                tempo_ocupado_ant = 60;
            }
            hora_ant = hora_para_minutos(anterior->itemLista.reserva.hora_reserva.hora, anterior->itemLista.reserva.hora_reserva.minutos);
            if(atual->itemLista.reserva.tipo_reserva == 0){
                tempo_ocupado_atual = 30;
            } else{
                tempo_ocupado_atual = 60;
            }
            hora_atual = hora_para_minutos(atual->itemLista.reserva.hora_reserva.hora, atual->itemLista.reserva.hora_reserva.minutos);
            
            if(proximo->itemLista.reserva.tipo_reserva == 0){
                tempo_ocupado_prox = 30;
            } else{
                tempo_ocupado_prox = 60;
            }
            hora_prox = hora_para_minutos(proximo->itemLista.reserva.hora_reserva.hora, proximo->itemLista.reserva.hora_reserva.minutos);
            
            /* inserir antes do anterior */
            // se anterior e a reserva estão no mesmo dia e mês
            if(reserva.reserva.data_reserva.mes == anterior->itemLista.reserva.data_reserva.mes &&
               reserva.reserva.data_reserva.dia == anterior->itemLista.reserva.data_reserva.dia){
                
            }
            /* inserir entre anterior e atual */

            /* inserir entre atual e prox */

            anterior = anterior->prox;
            aux = aux->prox;
            proximo = proximo->prox;
        }

        /* inserir no fim da lista */
        if(reserva.reserva.data_reserva.mes == atual->itemLista.reserva.data_reserva.mes &&
           reserva.reserva.data_reserva.dia == atual->itemLista.reserva.data_reserva.mes &&
           reserva.reserva.hora_reserva.hora == atual->itemLista.reserva.hora_reserva.hora && 
           reserva.reserva.hora_reserva.minutos > atual->itemLista.reserva.hora_reserva.minutos){
            if((hora_atual + tempo_ocupado_atual) > hora_reserva){
                return 0;
            }
            return 1;
        }
        if(reserva.reserva.data_reserva.mes == atual->itemLista.reserva.data_reserva.mes &&
           reserva.reserva.data_reserva.dia == atual->itemLista.reserva.data_reserva.dia &&
           reserva.reserva.hora_reserva.hora > atual->itemLista.reserva.hora_reserva.hora){
            if((hora_atual + tempo_ocupado_atual) > hora_reserva){
                return 0;
            }
            return 1;
        }
        if(reserva.reserva.data_reserva.mes == atual->itemLista.reserva.data_reserva.mes &&
           reserva.reserva.data_reserva.dia > atual->itemLista.reserva.data_reserva.dia){
            return 1;
        }
        if(reserva.reserva.data_reserva.mes > atual->itemLista.reserva.data_reserva.mes){
            return 1;
        }
    } 
    destroi_lista(listaOrdenada);
    return 0;
}

struct conteudoFila verificar_compatibilidade(struct conteudoLista reserva, tipoFila* fila_ptr, pLista lista_ptr){
}

int substituir_reserva(struct conteudoFila pre_reserva, pLista lista_ptr){
    pLista aux = lista_ptr;
    while(aux != NULL){
        if(aux->itemLista.reserva.hora_reserva.hora == pre_reserva.pre_reserva.hora_pre_reserva.hora &&
           aux->itemLista.reserva.hora_reserva.minutos == pre_reserva.pre_reserva.hora_pre_reserva.minutos && 
           aux->itemLista.reserva.data_reserva.dia == pre_reserva.pre_reserva.data_pre_reserva.dia &&
           aux->itemLista.reserva.data_reserva.mes == pre_reserva.pre_reserva.data_pre_reserva.mes){
            strcpy(aux->itemLista.reserva.nome, pre_reserva.pre_reserva.nome);
            aux->itemLista.reserva.tipo_reserva = pre_reserva.pre_reserva.tipo_pre_reserva;
            return 1;
        }
        aux = aux -> prox;
    }
    return 0;
}

struct conteudoFila reserva_para_pre_reserva(struct conteudoLista reserva){
    struct conteudoFila pre_reserva;
    pre_reserva.pre_reserva.data_pre_reserva.dia = reserva.reserva.data_reserva.dia;
    pre_reserva.pre_reserva.data_pre_reserva.mes = reserva.reserva.data_reserva.mes;
    pre_reserva.pre_reserva.hora_pre_reserva.hora = reserva.reserva.hora_reserva.hora;
    pre_reserva.pre_reserva.hora_pre_reserva.minutos = reserva.reserva.hora_reserva.minutos;
    strcpy(pre_reserva.pre_reserva.nome, reserva.reserva.nome);
    pre_reserva.pre_reserva.tipo_pre_reserva = reserva.reserva.tipo_reserva;
    return pre_reserva;
}

struct conteudoLista pre_reserva_para_reserva(struct conteudoFila pre_reserva){
    struct conteudoLista reserva;
    reserva.reserva.data_reserva.dia = pre_reserva.pre_reserva.data_pre_reserva.dia;
    reserva.reserva.data_reserva.mes = pre_reserva.pre_reserva.data_pre_reserva.mes;
    reserva.reserva.hora_reserva.hora = pre_reserva.pre_reserva.hora_pre_reserva.hora;
    reserva.reserva.hora_reserva.minutos = pre_reserva.pre_reserva.hora_pre_reserva.minutos;
    strcpy(reserva.reserva.nome, pre_reserva.pre_reserva.nome);
    reserva.reserva.tipo_reserva = pre_reserva.pre_reserva.tipo_pre_reserva;
    return reserva;
}

int input_int(char* string){
    int input;
    while(1){
        printf("%s", string);
        if(scanf("%d", &input) == 1){
            break;
        }
        else{
            printf("Digite um numero inteiro válido.\n");
            while(getchar() != '\n');
        }
    }
    return input;
}

char* input_string(char* string){
    int cont = 1;
    char* input = (char*) malloc(100 * sizeof(char));
    if(input == NULL){
        printf("Memória indisponível!\n");
        return NULL;
    }
    while(cont){
        cont = 0;
        printf("%s", string);

        if(fgets(input, 100, stdin) == NULL){
            printf("Erro ao ler o input!\n");
            free(input);
            return NULL;
        }

        for(long unsigned int i = 0; i < strlen(input); i++){
            if(input[i] == '\n'){
                input[i] = '\0';
                break;
            }
        }

        for(long unsigned int i = 0; i < strlen(input); i++){
            if(!isalpha(input[i])){
                printf("Digite um nome valido.\n");
                cont = 1;
                break;
            }
        }
    }
    return input;
}

int str_to_int(char* string){
    int resultado;
    for(int i = 0; string[i] != '\0'; i++){
        if(string[i] >= '0' && string[i] <= '9'){
            resultado = resultado * 10 + (string[i] - '0');
        } 
        else{
            break;
        }
    }
    return resultado;
}

int validar_horas(int hora, int minutos){
    if(hora >= 8 && hora <= 17 && minutos >= 0 && minutos <= 59){
        return 1;
    }
    return 0;
}

int validar_data(int mes, int dia){
    if(mes == 2 && dia > 28){
        return 0;
    }

    if((mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12) && dia > 31){
        return 0;
    }

    if((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30 ){
        return 0;
    }

    if(mes > 12 || mes <= 0){
        return 0;
    }

    if(dia < 1 || dia > 31){
        return 0;
    }
    return 1;
}

void limpar_tela(){
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #elif __APPLE__
        system("clear");
    #else 
    #endif
}

int hora_para_minutos(int hora, int minutos){
    return hora*60 + minutos;
}