<<<<<<< HEAD
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "ListaEnc.h"


#define TRUE 1
#define FALSE 0

typedef struct {
    char nome[255];
    char login[255];
    char senha[255];
} Usuario; //tipo lista

typedef struct {
    int numero;
    char data[255];
    char hora[255];
    char origem[255];
    char destino[255];
    int poltronas;
    double valor;
} Linha; //tipo lista

typedef struct {
    int numero_linha;
    double valor_linha;
    int vagas[255];
    int cont_idoso;
    int cont_estudante;
} Ocupacao; //tipo lista






//Listas
ListaEnc* listaUsuarios;
ListaEnc* listaLinhas;
ListaEnc* listaOcupacao;




void cadastrarUsuario(char nome[], char login[], char senha[]) {
    //Inicializando a struct Usuario
    Usuario* u = (Usuario*) malloc(sizeof (Usuario));
    strcpy(u->nome, nome);
    strcpy(u->login, login);
    strcpy(u->senha, senha);
    insereNoFim(u, listaUsuarios);
}
// Cadastrar as linhas de onibus

void cadastrarLinha(int numero, char data[], char hora[], char origem[], char destino[], int poltronas, double valor) {
 
    Linha* li = (Linha*) malloc(sizeof (Linha));
    li->numero = numero;
    strcpy(li->data, data);
    strcpy(li->hora, hora);
    strcpy(li->origem, origem);
    strcpy(li->destino, destino);
    li->poltronas = poltronas;
    li->valor = valor;

    insereNoFim(li, listaLinhas);
    cadastrarOcupacao(numero, poltronas, valor);
}

void cadastrarOcupacao(int numero, int poltronas, double valor_) {
 
    Ocupacao* ocu = (Ocupacao*) malloc(sizeof (Ocupacao));
    ocu->numero_linha = numero;
    ocu->valor_linha = valor_;
  
    memset(ocu->vagas, 0, sizeof (poltronas));
    ocu->vagas[poltronas + 1] = -1;
    ocu->cont_idoso = 0;
    ocu->cont_estudante = 0;
    insereNoFim(ocu, listaOcupacao);
}



Usuario* buscarUsuario(char login[]) {
    int i;
    for (i = 0; i < obterTamanhoDaLista(listaUsuarios); i++) {
        Usuario* u = (Usuario*) obterElemento(i, listaUsuarios);
        if (strcmp(login, u->login) == 0) return u;
    }
    return NULL;
}

Linha* buscarLinha(int numero) {
    int i;
    for (i = 0; i < obterTamanhoDaLista(listaLinhas); i++) {
        Linha* li = (Linha*) obterElemento(i, listaLinhas);

        if (numero == li->numero) return li;
    }
    return NULL;
}

Ocupacao* buscarOcupacao(int numero) {
    int i;
    for (i = 0; i < obterTamanhoDaLista(listaOcupacao); i++) {
        Ocupacao* ocu = (Ocupacao*) obterElemento(i, listaOcupacao);

        if (numero == ocu->numero_linha) return ocu;
    }
    return NULL;
}

int autenticado(char login[], char senha[]) {
    Usuario* u = buscarUsuario(login);
    if (u == NULL) return FALSE;
    else if (strcmp(senha, u->senha) != 0) {
        return FALSE;
    }
    system("cls");
    printf("\nBem vindo %s!\n", u->nome);
    return TRUE;
}

int vizualiarLinhas() {

    int i, am = 0;

    printf("\nLista de linhas:\n");
    printf("Numero\t\tData\thora\tOrigem\tDestino\tPoltronas\tValor\n");
    for (i = 0; i < obterTamanhoDaLista(listaLinhas); i++) {
        Linha* li = (Linha*) obterElemento(i, listaLinhas);


        am++;



        printf("%d\t%s\t%s\t%s\t%s\t%d\t\t%.2f\n", li->numero, li->data, li->hora, li->origem, li->destino, li->poltronas, li->valor);


    }
    printf("\n\n");
    if (am == 0)
        return FALSE;
    else
        return TRUE;

}

int vizualiarOcupacao(int numero) {


    int i, j, am = 0, pula = 0;


    Ocupacao* ocu = buscarOcupacao(numero);
    Linha* li = buscarLinha(numero);

    printf("\nInformacoes da linha/onibus %d:\n", ocu->numero_linha);
    printf("Numero\t\tData\thora\tOrigem\tDestino\tPoltronas\tValor\n");
    printf("%d\t%s\t%s\t%s\t%s\t%d\t\t%.2f\n", li->numero, li->data, li->hora, li->origem, li->destino, li->poltronas, li->valor);
    printf("Legenda:\n\tL = livre\n\tO = ocupado\n");




    for (i = 0; i < li->poltronas; i++) {
        if (ocu->vagas[i] == 0) {
            //poltrona livre
            printf("%d-L\t", i + 1);

        } else {
            //poltrona ocupada
            printf("%d-O\t", i + 1);
            am++;
        }
        pula++;
        if (pula == 10) {
            printf("\n");
            pula = 0;
        }

    }





    printf("\n\n");
    printf("Poltronas vendidas: %d\nPara idosos: %d\nPara estudantes: %d\n", am, ocu->cont_idoso, ocu->cont_estudante);
    //refazer esta conta
    am = am - ocu->cont_idoso - ocu->cont_estudante;
    double valor_total = (am * ocu->valor_linha) + (ocu->cont_estudante * ocu->valor_linha * 0.5);
    printf("Valor total: %.2f\n\n", valor_total);


}

int comprarPassagem(int numero, int poltrona_escolhida, int estu, int ido)
{
     int i, j, am = 0, pula = 0;


    Ocupacao* ocu = buscarOcupacao(numero);
    Linha* li = buscarLinha(numero);
    if(ido == 1){
        //eh idoso, vamos ver se ja vendemos as duas para idosos
        if(ocu->cont_idoso < 2){
            printf("Ainda existe vaga para idoso, sua passagem foi inteiramente gratuita!\n");
            
            ocu->cont_idoso++;
            
        }
        else
        {
            printf("Nao existe mais passagens para idosos gratuitas, deseja comprar assim mesmo\n1 - sim\n2 - nao\n");
            scanf("%d",&am);
            if(am == 2) return FALSE;
        }
    
    }
    
    if(estu == 1){
        ocu->cont_estudante++;
    
    }
    
    ocu->vagas[poltrona_escolhida - 1] = 1;
    
    printf("Passagem comprada com sucesso, detalhes:\n");
     printf("Numero\t\tData\thora\tOrigem\tDestino\tPoltrona Selecionada\n");
    printf("%d\t%s\t%s\t%s\t%s\t%d\t\n", li->numero, li->data, li->hora, li->origem, li->destino, poltrona_escolhida);
    
    return TRUE;
    


}

int listarPoltronas(int numero) {


    int i, j, am = 0, pula = 0;


    Ocupacao* ocu = buscarOcupacao(numero);
    Linha* li = buscarLinha(numero);




    for (i = 0; i < li->poltronas; i++) {
        if (ocu->vagas[i] == 0) {
            //poltrona livre
            printf("%d-L\t", i + 1);

        } else {
            //poltrona ocupada
            printf("%d-O\t", i + 1);
            am++;
        }
        pula++;
        if (pula == 10) {
            printf("\n");
            pula = 0;
        }

    }
    
    printf("\n");



}

int verificarPoltrona(int poltrona_numero, int numero) {





    Ocupacao* ocu = buscarOcupacao(numero);
    Linha* li = buscarLinha(numero);

    poltrona_numero = poltrona_numero - 1;

    if (poltrona_numero < li->poltronas && poltrona_numero >= 0) {
        if (ocu->vagas[poltrona_numero] == 0) {

            printf("Poltrona %d livre", poltrona_numero + 1);
            return TRUE;

        } else {

            printf("Poltrona ja ocupada, por favor selecione outra!!\n");
        }


    } else {
        printf("Numero da poltrona digitado nao existe\n");
    }




    return FALSE;

}

int verificarVagasOcupacao(int numero) {


    int i;


    Ocupacao* ocu = buscarOcupacao(numero);
    Linha* li = buscarLinha(numero);


    for (i = 0; i < li->poltronas; i++) {
        if (ocu->vagas[i] == 0) return TRUE;
    }



    return FALSE;

}

double precoPassagem(int numero){

    Ocupacao* ocu = buscarOcupacao(numero);
    double a = ocu->valor_linha;
  
    return a;

}



int main(int argc, char const *argv[]) {
    listaUsuarios = criarLista(sizeof (Usuario));
    listaLinhas = criarLista(sizeof (Linha));
    listaOcupacao = criarLista(sizeof (Ocupacao));
   

    int x = 0, opcao, opcao2 = 0;
    char nome[255], login[255], senha[255], rep_senha[255], msg[255], login_amigo[255];
    cadastrarUsuario("ra", "ra", "123");
    cadastrarLinha(10, "20/11/2015", "13:30", "Jatai", "Goiania", 40, 40.30);
    cadastrarLinha(11, "20/12/2015", "15:30", "Jataia", "Goiania", 50, 70.40);
    //dados para linhas
    int numero,i;
    char data[255];
    char hora[255];
    char origem[255];
    char destino[255];
    int poltronas;
    double valor;

    while (x == 0) {
        printf("Net Passagens v1.0\n");
        printf("#Opcoes:\n");
        printf("1 - Cadastrar novo vendedor\n");
        printf("2 - Login\n");
        printf("3 - Sair\n");
        printf("Digite uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                system("cls");
                printf("Cadastro:\n");
                printf("\nDigite o seu nome: ");
                scanf(" %[^\n]s", nome);

                printf("Digite o seu login: ");
                scanf(" %[^\n]s", login);
                printf("Digite a sua senha: ");
                scanf(" %[^\n]s", senha);
                printf("Repita a sua senha: ");
                scanf(" %[^\n]s", rep_senha);
                //Verifica se as senhas digitadas sao iguais
                if (strcmp(senha, rep_senha) == 0) {
                    //verifica se o login digitado ja existe
                    if (buscarUsuario(login) == NULL) {
                        //Cadastra os dados inseridos
                        cadastrarUsuario(nome, login, senha);
                        printf("Cadastro do vendedor realizado com sucesso!\n\n");
                    }
                    else {
                        printf("Jah existe um vendedor cadastrado com esse login!\n\n");
                    }
                }
                else {
                    printf("As senhas informadas nao conferem!\n\n");
                }
                break;


                //Login
            case 2:
                system("cls"); 

                printf("Login:\n");
                printf("\nDigite o seu login: ");
                scanf(" %[^\n]s", login);
                printf("Digite a sua senha: ");
                scanf(" %[^\n]s", senha);
                int y = 1;
                if (autenticado(login, senha)) {
                    y = 0;
                } else {
                    printf("Nao ha vendedores cadastrados com esse login! ou senha invalida\n\n");
                }

                while (y == 0) {

                    printf("#Opcoes:\n");
                    printf("1 - Cadastrar linha\n");
                    printf("2 - Listar linhas\n");
                    printf("3 - Vender Passagens\n");
                    printf("4 - Relatorio de Vendas por linha\n");
                    printf("5 - Sair\n");
                    printf("Digite uma opcao: ");
                    scanf("%d", &opcao);

                    switch (opcao) {
                        case 1:
                         

                            system("cls"); 

                            printf("Cadastro da linha:\n");
                            printf("\nDigite o numero da linha: ");
                            scanf("%d", &numero);

                            printf("Digite a data da linha: ");
                            scanf(" %[^\n]s", data);
                            printf("Digite a hora da linha: ");
                            scanf(" %[^\n]s", hora);
                            printf("Digite a cidade de origem: ");
                            scanf(" %[^\n]s", origem);

                            printf("Digite a cidade de destino: ");
                            scanf(" %[^\n]s", destino);

                            printf("\nDigite a quantidade de poltronas: ");
                            scanf("%d", &poltronas);

                            printf("\nDigite o valor de cada passagem: ");
                            scanf("%lf", &valor);

                            //Verifica se origem e destino sao iguais
                            if (strcmp(origem, destino) != 0) {
                                if (poltronas > 0 && valor > 0) {
                                    //verifica se o login digitado ja existe
                                    if (buscarLinha(numero) == NULL) {

                                        //Cadastra a linha com os dados digitados
                                        cadastrarLinha(numero, data, hora, origem, destino, poltronas, valor);
                                        printf("Cadastro da linha realizado com sucesso!\n\n");
                                    }
                                    else {
                                        printf("Jah existe uma linha com este numero, por favor escolha outro!\n\n");
                                    }
                                } else {
                                    printf("Poltronas e valor da passagem devem ser maiores que 0!\n\n");
                                }
                            }

                            else {
                                printf("Origem e destino nao pode ser iguais!\n\n");
                            }
                            system("pause");
                            system("cls"); 

                            break;

                        case 2:
                           
                            if (!vizualiarLinhas()) {
                                printf("Nao existe linhas cadastradas\n");
                            }
                            system("pause");
                            system("cls"); 

                            break;



                        case 3:
                           
                            printf("\nDigite o numero da linha/onibus:\n");
                            scanf("%d", &numero);
                            if (buscarLinha(numero)) {
                                //linha existente
                                //verificar vagas
                                int op2=0;
                                if (verificarVagasOcupacao) {
                                    while (opcao2 == 0) {
                                        
                                        int estu = 0;
                                        int ido = 0;
                                        int poltrona_escolhida;
                                        int compra;
                                        printf("Linha/onibus selecionada: %d\n", numero);
                                        printf("1 - Vizualizar Ocupacao da linha/onibus:\n");
                                        printf("2 - Selecionar poltrona para venda\n");
                                        printf("3 - Relatorio completo da linha\n");
                                        printf("4 - Sair\n");
                                        scanf("%d",&op2);
                                                


                                        switch (op2) {
                                            case 1:
                                                listarPoltronas(numero);
                                                 system("pause");
                            
                                                break;

                                            case 2:

                                                printf("Digite o numero da poltrona:\n");
                                                scanf("%d", &poltrona_escolhida);

                                                if (verificarPoltrona(poltrona_escolhida, numero)) {

                                                    printf("\nO passageiro eh estudante?\n1 - Sim\n2 - Nao\n");
                                                    scanf("%d", &estu);

                                                    if (estu == 1) {
                                                        //eh estudante
                                                        printf("Voce tem direito a 50%% na passagem\nDe %.2f por %.2f",precoPassagem(numero),(precoPassagem(numero) * 0.5));
                                                                                                



                                                    } else {
                                                        printf("\nO passageiro eh aposentado?\n1 - Sim\n2 - Nao\n");
                                                        scanf("%d", &ido);

                                                        if (ido == 1) {
                                                            // eh idoso
                                                            printf("Preco da passagem: %.2f\nMas como voce eh idoso, voce pode ter a passagem de forma gratuita\n",precoPassagem(numero));

                                                        } else {
                                                            // nao eh idoso e nem estudante
                                                            printf("Preco da passagem: %.2f",precoPassagem(numero));


                                                        }

                                                    }

                                                      printf("\nDeseja solicitar a passagem?\n1 - Sim\n2 - Nao\n");
                                                       scanf("%d", &compra);
                                                       if(compra == 1){
                                                        if(!(comprarPassagem(numero, poltrona_escolhida, estu, ido))) printf("Processo de compra de passagem falhou, tente novamente!\n");
                                                       }
                                                       else
                                                       {
                                                          printf("Obrigado\n"); 
                                                       
                                                       }
                                                      
                                                    
                                                    

                                                } 
                                              




										 system("pause");
                                          system("cls"); 





                                                break;
                                            case 3:
                                                vizualiarOcupacao(numero);
                                                 system("pause");
                           
                                                break;

                                             case 4:
                                                opcao2 = 1;
                                                break;        
                                            default:
                                                opcao2 = 1;
                                                break;
                                        }



                                    }





                                    //colocar um break aqui;

                                } else {

                                    printf("Nao ha mais vagas nesta linha/onibus\n");
                                }




                            } else {
                                printf("Nao existe esta linha, segue as linhas:\n");
                                vizualiarLinhas();

                            }

                            system("pause");
                            system("cls"); 

                            break;


                        case 4:
                          
                            //relatorio de cada linha
                        
                            
                            for (i = 0; i < obterTamanhoDaLista(listaLinhas); i++) {
                            Linha* li = (Linha*) obterElemento(i, listaLinhas);
                                vizualiarOcupacao(li->numero);
                                   }
                            
                           
                            system("pause");
                            system("cls"); 

                            break;

                            //aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa



                        case 5:
                            //sair
                            system("cls"); 

                            printf("Saindo\n\n");

                            y = 1;
                            break;


                        default:
                            printf("Opcao invalida!\n\n");
                            break;
                    }
                }
                break;


                //Sair
            case 3:
                system(0);
                x = 1;
                break;


            default:
                printf("Opcao invalida!\n\n");
                break;
        }
    }

    
    
    free(listaUsuarios);
    free(listaLinhas);
    free(listaOcupacao);
   

    return 0;
}
=======
#include <stdio.h>
#include <stdlib.h>

int main()
{
//Inicializa varaveis com 0
int i=0,cont=0;
    for(i=0;i<16;i++)
    {
        printf("%d\n",i);

        cont++;
        if(cont == 4)
        {
          printf("\r\r\r\r\t");
          cont=0;
        }

    }


    return 0;
}
>>>>>>> 8457386c1d9b60d2d5dbf09d11807b27d30dc1ac
