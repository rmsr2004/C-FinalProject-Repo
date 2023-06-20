#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "lista_de_reservas.h"
#include "fila_pre_reservas.h"
#include "funcoes.h"

void aplicacao(int escolha_menu_principal, int escolha_menu_secundario, pLista lista_ptr, tipoFila *fila_ptr);

int main(){
    pLista lista_ptr = (pLista) malloc(sizeof(noLista));
    tipoFila *fila_ptr = (tipoFila*) malloc(sizeof(tipoFila));
    if(lista_ptr == NULL || fila_ptr == NULL){
        perror("Memória não disponível!\n");
        return 1;
    }
    cria_fila(fila_ptr);
    cria_lista(lista_ptr);

    if(carregar_dados(lista_ptr, fila_ptr)){
        printf("Dados carregados com sucesso! A inicializar a aplicação....\n\n");
        sleep(1);

        int escolha_menu_principal = 0, escolha_menu_secundario = 0;
        aplicacao(escolha_menu_principal, escolha_menu_secundario, lista_ptr, fila_ptr);
        
        if(guardar_dados(lista_ptr, fila_ptr)){
            printf("Dados guardados com sucesso! ");
        }
        else{
            printf("Erro: Dados não foram guardados! ");
        }
        printf("Aplicação terminada!\n");
        destroi_fila(fila_ptr);
        destroi_lista(lista_ptr);
        return 0;
    }
    else{
        destroi_fila(fila_ptr);
        destroi_lista(lista_ptr);
        printf("Erro ao abrir a aplicação. Dados não carregados!\n");
        return 0;
    }
}

void aplicacao(int escolha_menu_principal, int escolha_menu_secundario, pLista lista_ptr, tipoFila *fila_ptr){
    int sair = 0;

    while(sair != 1){
        printf("------------------------\n\tM E N U \n------------------------\n");
        printf("0 - Fazer uma reserva.\n1 - Cancelar uma reserva\n2 - Cancelar uma pré-reserva\n\n");
        printf("3 - Listar as reservas e as pré-reservas(as mais antigas primeiro)\n");
        printf("4 - Listar as reservas e as pré-reservas de um cliente(as mais recentes primeiro)\n\n");
        printf("5 - Executar serviço\n\n");
        printf("6 - Sair\n\n");
        escolha_menu_principal =  input_int("Escolha que a opção que deseja: ");

        limpar_tela();
        switch(escolha_menu_principal){ /* switch menu principal */
            /* Reservar */
            case 0:
                do{ /* ciclo do - reserva */
                    printf("Reserva:\n\n0 - Lavagem\n1 - Manutenção\n2 - Voltar ao menu anterior\n");
                    escolha_menu_secundario = input_int("Escolha que a opção que deseja: ");
                    switch(escolha_menu_secundario){ /* switch menu reserva */
                        case 0:
                            int f_reservar = reservar(escolha_menu_secundario, lista_ptr, fila_ptr);
                            if(f_reservar == 1){
                                printf("Processo de reserva concluído!\n");
                            }
                            else if(f_reservar == 0){
                                printf("Processo de reserva não concluído!\n");
                            }
                            else if(f_reservar == 2){
                                printf("Processo de pré-reserva concluído!\n");
                            }
                            else if(f_reservar == -2){
                                printf("Já existe pré-reserva nessa hora!\n");
                            }
                            else if(f_reservar == -3){
                                printf("Processo de pré-reserva não foi concluído!\n");
                            }
                            break;
                        case 1:
                            f_reservar = reservar(escolha_menu_secundario, lista_ptr, fila_ptr);
                            if(f_reservar == 1){
                                printf("Processo de reserva concluído!\n");
                            }
                            else if(f_reservar == 0){
                                printf("Processo de reserva não concluído!\n");
                            }
                            else if(f_reservar == 2){
                                printf("Processo de pré-reserva concluído!\n");
                            }
                            else if(f_reservar == -2){
                                printf("Já existe pré-reserva nessa hora!\n");
                            }
                            else if(f_reservar == -3){
                                printf("Processo de pré-reserva não foi concluído!\n");
                            }
                            break;
                        case 2:
                            break;
                        default:
                            printf("\nOpção Inválida! Escolha uma opção correta!\n");
                            break;
                    } /* switch menu reserva - fim */
                } while(escolha_menu_secundario < 0 || escolha_menu_secundario > 2); /* ciclo do - reserva - fim */
                break;

            /* Cancelar Reserva */
            case 1:
                do{ /* ciclo do - cancelar reserva */
                    if(vazia_lista(lista_ptr)){
                        printf("Lista de reservas vazia!\n");
                        break;
                    }
                    printf("Cancelar:\n\n0 - Lavagem\n1 - Manutenção\n2 - Voltar ao menu anterior\n");
                    escolha_menu_secundario = input_int("Escolha que a opção que deseja: ");
                    switch(escolha_menu_secundario){ /* switch menu cancelar */
                        case 0:
                            int f_cancelar = cancelar_reserva(escolha_menu_secundario, lista_ptr, fila_ptr);
                            if(f_cancelar == 1){
                                printf("A reserva foi cancelada com sucesso!\n");
                            }
                            else if(f_cancelar == 0){
                                printf("A reserva não foi encontrada!\n");
                            }
                            else if(f_cancelar == 2){
                                printf("A reserva foi substituída com sucesso!\n");
                            }
                            else if(f_cancelar == -2){
                                printf("Não foi possível substituir a pré-reserva!\n");
                            }
                            else if(f_cancelar == -1){
                                printf("Não foi possível substituir a reserva!\n");
                            }
                            break;
                        case 1:
                            f_cancelar = cancelar_reserva(escolha_menu_secundario, lista_ptr, fila_ptr);
                            if(f_cancelar == 1){
                                printf("A reserva foi cancelada com sucesso!\n");
                            }
                            else if(f_cancelar == 0){
                                printf("Não foi possível cancelar a reserva!\n");
                            }
                            else if(f_cancelar == 2){
                                printf("A reserva foi substituída com sucesso!\n");
                            }
                            break;
                        case 2:
                            break;
                        default:
                            printf("\nOpção Inválida! Escolha uma opção correta!\n");
                            break;
                    } /* switch menu cancelar - fim */
                } while(escolha_menu_secundario < 0 || escolha_menu_secundario > 2); /* ciclo do - cancelar - fim*/
                break;

            case 2:
                do{ /* ciclo do - cancelar pre reserva */
                    if(vazia_fila(fila_ptr)){
                        printf("Fila de pré-reservas vazia!\n");
                        break;
                    }
                    printf("Cancelar:\n\n0 - Lavagem\n1 - Manutenção\n2 - Voltar ao menu anterior\n");
                    escolha_menu_secundario = input_int("Escolha que a opção que deseja: ");
                    switch(escolha_menu_secundario){ /* switch menu cancelar */
                        case 0:
                            if(cancelar_pre_reserva(escolha_menu_secundario, fila_ptr)){
                                printf("A pré-reserva foi encontrada!\n");
                            }
                            else{
                                printf("A pré-reserva não foi encontrada!\n");
                            }
                            break;
                        case 1: 
                            cancelar_pre_reserva(escolha_menu_secundario, fila_ptr);
                            break;
                        case 2:
                            limpar_tela();
                            break;
                        default:
                            limpar_tela();
                            printf("Opção Inválida! Escolha uma opção correta!\n\n");
                        break; 
                    } /* switch menu cancelar - fim */
                } while(escolha_menu_secundario < 0 || escolha_menu_secundario > 2); /* ciclo do - cancelar - fim*/
                break;

            case 3:
                listar_reservas_e_prereservas_por_data(lista_ptr, fila_ptr);
                break;

            case 4:
                char nome[100];
                printf("Insira o nome do cliente: ");
                getchar();
                if(fgets(nome, 99, stdin) == NULL){
                    printf("Erro ao ler o nome do cliente!\n");
                    return;
                }
                for(long unsigned int i = 0; i < strlen(nome); i++){
                    if(nome[i] == '\n'){
                        nome[i] = '\0';
                        break;
                    }
                }
                listar_reservas_prereservas_cliente(lista_ptr, fila_ptr, nome);
                break;

            case 5:
                if(executar_servico(lista_ptr, fila_ptr)){
                    printf("O serviço foi executado com sucesso!\n");
                    break;
                }
                printf("O serviço não foi executado!\n");
                break;
            /* Sair */
            case 6:
                sair = 1;
                break;
            /* Opção inválida (< 0 ou > 5)*/
            default:
                printf("Opção Inválida! Escolha uma opção correta!\n\n");
                break;
        } /* switch menu principal - fim */
    } /* fim da funçao */
}