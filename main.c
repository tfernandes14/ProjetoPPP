#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define MAX_FGETS 200
#define MAXIMO_PESSOA 5

int id_Tarefa = 0;

typedef struct pessoa{
    char *nome;
    char *mail;
    int iden;
    int numTarefa;
    struct pessoa *prox;
}t_person;

typedef struct data{
    int dia,mes,ano;
}t_data;

typedef struct tarefas{
    char *tarefa;
    int prioridade;
    int idenTarefa;
    t_data inicio;
    char *person;
    int id_person;
    t_data fim;
    struct tarefas *prox;
}t_tarefa;

t_person *cria_cabecalhoP(void){
    t_person *lista = (t_person*)malloc(sizeof(t_person));
    if (lista != NULL)
        lista->prox = NULL;
    return lista;
}

t_tarefa *cria_cabecalhoT(void){
    t_tarefa *lista = (t_tarefa*)malloc(sizeof(t_tarefa));
    if (lista != NULL)
        lista->prox = NULL;
    return lista;
}

void clrscr(){
    system("@cls||clear");
}

void atualiza_ID_tarefa(t_tarefa *lista, int *id_Tarefa){
    t_tarefa *aux = lista->prox;
    while(aux != NULL && aux->idenTarefa != 100000){
        if (aux->idenTarefa > *id_Tarefa)
            *id_Tarefa = aux->idenTarefa;
        aux = aux->prox;
    }
}

void atualiza_ID_3listas(t_tarefa *todo, t_tarefa *doing, t_tarefa *done, int *id_Tarefa){
    atualiza_ID_tarefa(todo, id_Tarefa);
    atualiza_ID_tarefa(doing, id_Tarefa);
    atualiza_ID_tarefa(done, id_Tarefa);
}

void escrever(char spot[]){
    fgets(spot,MAX_FGETS,stdin);
    spot[strlen(spot)-1]='\0';
}

t_person *inserePessoa(t_person *lista, char *nome, char *mail, int iden, int maxTarefas){
    t_person *novo = (t_person*)malloc(sizeof(t_person));
    if (novo == NULL)
        return NULL;
    while(lista->prox != NULL)
        lista = lista->prox;
    novo->nome = strdup(nome);
    novo->mail = strdup(mail);
    novo->iden = iden;
    novo->numTarefa = maxTarefas;
    novo->prox = lista->prox;
    lista->prox = novo;
    return novo;
}

void menu(char *letra){
    fseek(stdin ,0, SEEK_END);
    printf("\n\n                              Menu Inicial\n\n");
    printf("\t(A) Definir um numero maximo de tarefas\n");
    printf("\t(B) Inserir nova tarefa na lista 'To Do'\n");
    printf("\t(C) Enviar cartao de 'To Do' para 'Doing'\n");
    printf("\t(D) Enviar cartao de 'Doing' para 'Done'\n");
    printf("\t(E) Enviar cartao de 'Done' para 'To Do'\n");
    printf("\t(F) Alterar a pessoa responsavel por um cartao em 'Doing'\n");
    printf("\t(G) Visualizar todas as tarefas do quadro\n");
    printf("\t(H) Visualizar todas as tarefas de uma pessoa\n");
    printf("\t(I) Visualizar todas as tarefas por ordem de data de criacao\n");
    printf("\t(J) Visualzar todas as pessoas do quadro\n");
    printf("\t(K) Apagar uma tarefa\n");
    printf("\t(S) Sair\n");
    printf("\t> ");
    scanf("%c", letra);
    fseek(stdin ,0, SEEK_END);
    *letra = toupper(*letra);
}

void maxTarefas(int *max){
    printf("Introduza o maximo de tarefas:\n>");
    scanf("%d", max);
}

t_tarefa *apagar_Tarefa(t_tarefa *lista){
    int id;
    t_tarefa *aux = lista->prox->prox;
    while (aux != NULL)
    {
        printf("\t %s   |\t%d \n",aux->tarefa, aux->idenTarefa);
        aux = aux->prox;
    }
    printf("Qual o ID da tarefa que deseja apagar?\n");
    scanf("%d", &id);
    aux = lista;
    while(aux->prox != NULL && aux->prox->idenTarefa != id)
        aux = aux->prox;

    t_tarefa *apagar = aux->prox;
    aux->prox = aux->prox->prox;
    free(apagar);
    return aux;
}

t_tarefa *insereToDo(t_tarefa *lista, char *tarefa, int prioridade, int dia_inicio, int mes_inicio, int ano_inicio, int id_Tarefa){
    t_tarefa *novo = (t_tarefa*)malloc(sizeof(t_tarefa));
    if (novo == NULL)
        return NULL;
    while ((lista->prox != NULL) && (lista->prox->prioridade > prioridade))
        lista = lista->prox;
    novo->tarefa = strdup(tarefa);
    novo->prioridade = prioridade;
    novo->inicio.dia = dia_inicio;
    novo->inicio.mes = mes_inicio;
    novo->inicio.ano = ano_inicio;
    novo->idenTarefa = id_Tarefa;
    novo->prox = lista->prox;
    lista->prox = novo;
    return novo;
}

t_tarefa *novaTarefa(t_tarefa *lista, char *tarefa, int prioridade, int dia_inicio, int mes_inicio, int ano_inicio, int *id_Tarefa){
    t_tarefa *novo = (t_tarefa*)malloc(sizeof(t_tarefa));
    *id_Tarefa = *id_Tarefa + 1;
    if (novo == NULL)
        return NULL;
    while ((lista->prox != NULL) && (lista->prox->prioridade > prioridade))
        lista = lista->prox;
    novo->tarefa = strdup(tarefa);
    novo->prioridade = prioridade;
    novo->inicio.dia = dia_inicio;
    novo->inicio.mes = mes_inicio;
    novo->inicio.ano = ano_inicio;
    novo->idenTarefa = *id_Tarefa;
    novo->prox = lista->prox;
    lista->prox = novo;
    return novo;
}

t_tarefa *insereDoing(t_tarefa *lista, char *tarefa, char *pessoa, int dia_inicio, int mes_inicio, int ano_inicio, int prioridade, int id_Tarefa, int id_person){
    t_tarefa *novo = (t_tarefa*)malloc(sizeof(t_tarefa));
    if (novo == NULL)
        return NULL;
    while ((lista->prox != NULL) && (strcmp(pessoa,lista->prox->person) < 0))
        lista = lista->prox;
    novo->tarefa = strdup(tarefa);
    novo->person = strdup(pessoa);
    novo->prioridade = prioridade;
    novo->inicio.dia = dia_inicio;
    novo->inicio.mes = mes_inicio;
    novo->inicio.ano = ano_inicio;
    novo->id_person = id_person;
    novo->idenTarefa = id_Tarefa;
    novo->prox = lista->prox;
    lista->prox = novo;
    return novo;
}

t_tarefa *insereDone(t_tarefa *lista, char *tarefa, char *pessoa, int diaI, int mesI, int anoI, int prioridade, int diaF, int mesF, int anoF, int *id_Tarefa, int id_person){
    t_tarefa *novo = (t_tarefa*)malloc(sizeof(t_tarefa));
    *id_Tarefa = *id_Tarefa + 1;
    if (novo == NULL)
        return NULL;
    while ((lista->prox != NULL) && (strcmp(lista->person,lista->prox->person) > 0))
        lista = lista->prox;
    novo->tarefa = strdup(tarefa);
    novo->person = strdup(pessoa);
    novo->prioridade = prioridade;
    novo->inicio.dia = diaI;
    novo->inicio.mes = mesI;
    novo->inicio.ano = anoI;
    novo->id_person = id_person;
    novo->idenTarefa = *id_Tarefa;
    novo->fim.dia = diaF;
    novo->fim.mes = mesF;
    novo->fim.ano = anoF;
    novo->prox = lista->prox;
    lista->prox = novo;
    return novo;
}

t_tarefa *Move_Todo_Doing(t_tarefa *todo, t_tarefa *doing, t_person *listaP, int idTar, char *nome, int idperson){
    t_tarefa *proxTODO = todo->prox;
    t_person *proxPerson = listaP->prox;
    t_tarefa *novoD = (t_tarefa*)malloc(sizeof(t_tarefa));
    if (novoD == NULL)
        return NULL;
    while (proxPerson != NULL && proxPerson->iden != idperson)
        proxPerson = proxPerson->prox;
    proxPerson->numTarefa = proxPerson->numTarefa + 1;
    while((proxTODO->prox != NULL) && (proxTODO->prox->idenTarefa) != idTar)
        proxTODO = proxTODO->prox;
    novoD->tarefa = proxTODO->prox->tarefa;
    novoD->idenTarefa = idTar;
    novoD->id_person = idperson;
    novoD->prioridade = proxTODO->prox->prioridade;
    novoD->inicio.dia = proxTODO->prox->inicio.dia;
    novoD->inicio.mes = proxTODO->prox->inicio.mes;
    novoD->inicio.ano = proxTODO->prox->inicio.ano;
    novoD->person = nome;
    novoD->prox = doing->prox;
    doing->prox = novoD;
    t_tarefa *aux = proxTODO->prox;
    proxTODO->prox = proxTODO->prox->prox;
    free(aux);
    return novoD;
}

t_tarefa *Move_Doing_Done(t_tarefa *doing, t_tarefa *done, t_person *listaP, int idTar, int diaF, int mesF, int anoF){
    t_tarefa *proxDOING = doing->prox;
    t_person *proxPerson = listaP->prox;
    t_tarefa *novoDo = (t_tarefa*)malloc(sizeof(t_tarefa));
    if (novoDo == NULL)
        return NULL;
    while((proxDOING->prox != NULL) && (proxDOING->prox->idenTarefa) != idTar)
        proxDOING = proxDOING->prox;
    while (proxPerson != NULL && proxPerson->iden != proxDOING->id_person)
        proxPerson = proxPerson->prox;
    proxPerson->numTarefa = proxPerson->numTarefa - 1;
    novoDo->tarefa = proxDOING->prox->tarefa;
    novoDo->idenTarefa = proxDOING->prox->idenTarefa;
    novoDo->prioridade = proxDOING->prox->prioridade;
    novoDo->inicio.dia = proxDOING->prox->inicio.dia;
    novoDo->inicio.mes = proxDOING->prox->inicio.mes;
    novoDo->inicio.ano = proxDOING->prox->inicio.ano;
    novoDo->person = proxDOING->prox->person;
    novoDo->id_person = proxDOING->id_person;
    novoDo->fim.dia = diaF;
    novoDo->fim.mes = mesF;
    novoDo->fim.ano = anoF;
    novoDo->prox = done->prox;
    done->prox = novoDo;
    t_tarefa *aux = proxDOING->prox;
    proxDOING->prox = proxDOING->prox->prox;
    free(aux);
    return novoDo;
}

void alteraResponsavel(t_tarefa *doing, t_person *lista){
    t_tarefa *aux = doing->prox;
    t_person *auxP = lista->prox;
    int id_tarefa, id_person;
    printf("\nTAREFAS:\n");
    while (aux != NULL)
    {
        printf("%s\t|   %d\t|  %s \n",aux->tarefa, aux->idenTarefa, aux->person);
        aux = aux->prox;
    }
    aux = doing;
    printf("Qual e o ID da tarefa que quer alterar o responsavel?\n>");
    scanf("%d",&id_tarefa);
    printf("\nPESSOAS:\n");
    while (auxP != NULL)
    {
        printf("%s\t|   %d \n",auxP->nome, auxP->iden);
        auxP = auxP->prox;
    }
    auxP = lista;
    printf("Qual e o ID da pessoa que meter como responsavel da tarefa?\n>");
    scanf("%d",&id_person);
    while (auxP != NULL && auxP->iden != id_person)
        auxP = auxP->prox;
    while (aux != NULL && aux->idenTarefa != id_tarefa)
        aux = aux->prox;
    aux->person = auxP->nome;
    aux->id_person = id_person;
}

void obter_dados_limitados(int *dado, int min, int max){
    int cont = 0;
    do{
        if (cont != 0)
            printf("Tente outra vez:\n>");
        scanf("%d", dado);
        cont++;
    }while(*dado < min || *dado > max);
}

void prepara_done(t_tarefa *doing, t_tarefa *done, t_person *listaP){
    int idTar, dia_done, mes_done, ano_done, verTarefa = 0;
    t_tarefa *aux = doing->prox;
    printf("TAREFA | ID:");
    while(aux != NULL){
        printf("%s | %d\n",aux->tarefa, aux->idenTarefa);
        aux = aux->prox;
    }
    printf("Parabens! Concluiu a tarefa!\nIntroduza o ID da Tarefa: \n>");
    scanf("%d", &idTar);
    aux = doing;
    while (aux != NULL){
        if (aux->idenTarefa == idTar)
            verTarefa = 1;
        if(aux->prox == NULL && verTarefa == 0){
            printf("Tarefa nao encontrada, introduza o ID da tarefa novamente:\n>");
            scanf("%d", &idTar);
            aux = doing;
        }
        aux = aux->prox;
    }
    printf("Introduza o dia de conclusão:\n>");
    obter_dados_limitados(&dia_done, 1, 31);
    printf("Introduza o mes de conclusão:\n>");
    obter_dados_limitados(&mes_done, 1, 12);
    printf("Introduza o ano de conclusão (so e possivel entre 1950 e 2050): \n>");
    obter_dados_limitados(&ano_done, 1950, 2050);
    Move_Doing_Done(doing, done, listaP, idTar, dia_done, mes_done, ano_done);
}

t_tarefa *Dadostarefa(t_tarefa *lista){
    char tarefa[MAX_FGETS];
    int prioridade, dia_inicio, mes_inicio, ano_inicio;
    fseek(stdin ,0, SEEK_END);
    printf("Introduza a prioridade, com uma escala de 1 a 10: \n>");
    obter_dados_limitados(&prioridade, 1, 10);
    getchar();
    printf("Introduza a tarefa: \n>");
    escrever(tarefa);
    printf("Introduza o dia: \n>");
    obter_dados_limitados(&dia_inicio, 1, 31);
    printf("Introduza o mes: \n>");
    obter_dados_limitados(&mes_inicio, 1, 12);
    printf("Introduza o ano (so e possivel entre 1950 e 2050): \n>");
    obter_dados_limitados(&ano_inicio, 1950, 2050);
    novaTarefa(lista, tarefa, prioridade, dia_inicio, mes_inicio, ano_inicio, &id_Tarefa);
    return lista;
}

int diferenca_dias(int dia, int iniciomes, int ano, int diaF, int mesF, int anoF){
    int mes[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
    int contIni, contFim, diferenca;
    contIni = ano * 365 + mes[iniciomes] + dia;
    contFim = anoF * 365 + mes[mesF] + diaF;
    diferenca = contFim - contIni;
    return diferenca;
}

int verifica7dias(t_tarefa *doing, t_tarefa *todo, int idPerson, int idTarefa){
    t_tarefa *aux = doing->prox;
    t_tarefa *novaTarefa = todo->prox;
    int dia, mes, ano, diaF, mesF, anoF, n;
    while(novaTarefa != NULL && novaTarefa->idenTarefa != idTarefa)
        novaTarefa = novaTarefa->prox;
    diaF = novaTarefa->inicio.dia;
    mesF = novaTarefa->inicio.mes;
    anoF = novaTarefa->inicio.ano;
    while(aux != NULL){
        if (aux->id_person == idPerson){
            dia = aux->inicio.dia;
            mes = aux->inicio.mes;
            ano = aux->inicio.ano;
            n = diferenca_dias(dia, mes, ano, diaF, mesF, anoF);
            if(n < 7 && n > -7)
                return 0;
        }
        aux = aux->prox;
    }
    return 1;
}

t_tarefa *toDo_Doing (t_person *list, t_tarefa *todo, t_tarefa *doing, int max){
    int id, idTar, verID = 0, verTarefa = 0, ver7dias;
    char *nome;
    t_person *auxP = list->prox;
    printf("\nPESSOAS:\n");
    while (auxP != NULL)
    {
        printf("%s\t|   %d \n",auxP->nome, auxP->iden);
        auxP = auxP->prox;
    }
    t_tarefa *aux = todo->prox->prox;
    printf("\nIntroduza o ID da pessoa para atribuir a tarefa:\n>");
    scanf("%d", &id);
    auxP = list;
    while(auxP != NULL && auxP->iden != id)
        auxP = auxP->prox;
    if(auxP->numTarefa >= max){
        printf("A pessoa que escolheu esta com muito trabalho, temos muitos experientes na equipa! Tente outra!\n>");
        scanf("%d", &id);
    }
    auxP = list;
    while(auxP != NULL){
        if (id == auxP->iden){
            verID = 1;
            nome = auxP->nome;
        }
        if(auxP->prox == NULL && verID == 0){
            printf("Pessoa nao encontrada, introduza outro ID:\n>");
            scanf("%d", &id);
            auxP = list;
        }
        auxP = auxP->prox;
    }
    printf("\nTAREFAS:\n");
    while (aux != NULL){
        printf("%s\t|   %d \n",aux->tarefa, aux->idenTarefa);
        aux = aux->prox;
    }
    printf("Introduza o ID da tarefa para associar a pessoa %s:\n>",nome);
    scanf("%d", &idTar);
    ver7dias = verifica7dias(doing, todo, id, idTar);
    while(ver7dias == 0){
        printf("A pessoa esta ocupada nessa semana, escolha outra tarefa:\n>");
        scanf("%d", &idTar);
        ver7dias = verifica7dias(doing, todo, id, idTar);
    }
    aux = todo;
    while (aux != NULL){
        if (aux->idenTarefa == idTar)
            verTarefa = 1;
        if(aux->prox == NULL && verTarefa == 0){
            printf("Tarefa nao encontrada, introduza o ID da tarefa novamente:\n>");
            scanf("%d", &idTar);
            aux = todo;
        }
        aux = aux->prox;
    }
    Move_Todo_Doing(todo, doing, list, idTar, nome, id);
    return 0;
}

t_tarefa *todas_tarefas_ordem(t_tarefa *todo, t_tarefa *doing, t_tarefa *done, t_tarefa *ordena){
    t_tarefa *novo = (t_tarefa *) malloc(sizeof(t_tarefa));
    t_tarefa *auxDoing = doing->prox;
    t_tarefa *auxDone = done->prox;
    t_tarefa *auxTodo = todo->prox;
    t_tarefa *auxOrdena = ordena->prox;
    int diaI, mesI, anoI, diaF, mesF, anoF, help, conta, i;
    if (novo == NULL)
        return NULL;
    while (auxTodo != NULL){
        novo->tarefa = auxTodo->tarefa;
        novo->idenTarefa = auxTodo->idenTarefa;
        novo->inicio.dia = auxTodo->inicio.dia;
        novo->inicio.mes = auxTodo->inicio.mes;
        novo->inicio.ano = auxTodo->inicio.ano;
        auxTodo = auxTodo->prox;
    }
    while (auxDoing != NULL){
        novo->tarefa = auxDoing->tarefa;
        novo->idenTarefa = auxDoing->idenTarefa;
        novo->inicio.dia = auxDoing->inicio.dia;
        novo->inicio.mes = auxDoing->inicio.mes;
        novo->inicio.ano = auxDoing->inicio.ano;
        auxDoing = auxDoing->prox;
    }
    while (auxDone != NULL){
        novo->tarefa = auxDone->tarefa;
        novo->idenTarefa = auxDone->idenTarefa;
        novo->inicio.dia = auxDone->inicio.dia;
        novo->inicio.mes = auxDone->inicio.mes;
        novo->inicio.ano = auxDone->inicio.ano;
        auxDone = auxDone->prox;
    }
    while (ordena != NULL){
            while (auxOrdena != NULL && auxOrdena->prox != NULL){
                diaI = ordena->prox->prox->inicio.dia;
                mesI = ordena->prox->prox->inicio.mes;
                anoI = ordena->prox->prox->inicio.ano;
                while(auxOrdena != NULL){
                    diaF = auxOrdena->prox->inicio.dia;
                    mesF = auxOrdena->prox->inicio.mes;
                    anoF = auxOrdena->prox->inicio.ano;
                    help = diferenca_dias(diaI, mesI, anoI, diaF, mesF, anoF);
                    if (help < 0){
                        ordena->prox = auxOrdena->prox;
                        auxOrdena->prox->prox = ordena->prox->prox;
                        auxOrdena->prox = ordena->prox;
                        ordena->prox->prox = auxOrdena->prox->prox;
                    }
                auxOrdena = auxOrdena->prox;
                }
            ordena = ordena->prox;
            }
    }
    auxOrdena = ordena;
    while (auxOrdena != NULL){
        printf("%s | %d | %d/%d/%d\n", ordena->tarefa, ordena->idenTarefa, ordena->inicio.dia, ordena->inicio.mes, ordena->inicio.ano);
        auxOrdena = auxOrdena->prox;
    }
}

void imprimeLista_p(t_person *lista){
    t_person *aux = lista->prox;
    while(aux != NULL)
    {
        printf("Pessoa: %s\n",aux->nome);
        printf("E-mail: %s\n",aux->mail);
        printf("ID da pessoa: %d\n",aux->iden);
        aux=aux->prox;
    }
}

void imprimeLista_t_Done(t_tarefa *lista){
    t_tarefa *aux = lista->prox;
    printf("-------------------------DONE-------------------------\n");
    while(aux != NULL)
    {
        printf("_______________________________________________________\n\n");
        printf("\tTarefa: %s, ID: %d\n",aux->tarefa, aux->idenTarefa);
        printf("\t%s com o ID %d concluiu a tarefa\n",aux->person, aux->id_person);
        printf("\tData de inicio: %d/%d/%d\n",aux->inicio.dia, aux->inicio.mes, aux->inicio.ano);
        printf("\tData de conclusao: %d/%d/%d\n",aux->fim.dia, aux->fim.mes, aux->fim.ano);
        printf("______________________________________________________\n");
        aux = aux->prox;
    }
}

void imprimeLista_t_Doing(t_tarefa *lista){
    t_tarefa *aux = lista->prox;
    printf("-------------------------DOING-------------------------\n");
    while(aux != NULL)
    {
        printf("_______________________________________________________\n\n");
        printf("\t%s esta a trabalhar na tarefa: %s.\n",aux->person, aux->tarefa);
        printf("\tData de inicio: %d/%d/%d\n",aux->inicio.dia, aux->inicio.mes, aux->inicio.ano);
        printf("\tPrioridade: %d\n",aux->prioridade);
        printf("______________________________________________________\n");
        aux = aux->prox;
    }
}

void imprimeLista_t_ToDo(t_tarefa *lista){
    t_tarefa *aux = lista->prox->prox;
    printf("-------------------------TO DO-------------------------\n");
    while(aux != NULL)
    {
        printf("_______________________________________________________\n\n");
        printf("\tTarefa: %s, ID: %d\n",aux->tarefa, aux->idenTarefa);
        printf("\tData de inicio: %d/%d/%d\n",aux->inicio.dia, aux->inicio.mes, aux->inicio.ano);
        printf("\tPrioridade: %d\n",aux->prioridade);
        printf("_______________________________________________________\n");
        aux = aux->prox;
    }
}

void FICH_tarefas_ToDo (t_tarefa *lista){
    FILE *fp;
    char linha[MAX_FGETS], tarefa[MAX_FGETS], prioridade[MAX_FGETS], idenTarefa[MAX_FGETS], dia[MAX_FGETS], mes[MAX_FGETS], ano[MAX_FGETS];
    int prio, ID, day, month, year;
    fp = fopen("tarefasToDo.txt","r");
    if (fp == NULL)
        printf ("Erro ao abrir ao ficheiro\n");
    else{
        while (fgets(linha,MAX_FGETS,fp) != NULL)
        {
            strcpy(tarefa, strtok(linha,"/"));
            strcpy(prioridade, strtok(NULL,"/"));
            strcpy(idenTarefa, strtok(NULL,"/"));
            strcpy(dia, strtok(NULL,"/"));
            strcpy(mes, strtok(NULL,"/"));
            strcpy(ano, strtok(NULL,"/"));

            sscanf(prioridade,"%d",&prio);
            sscanf(idenTarefa,"%d",&ID);
            sscanf(dia,"%d",&day);
            sscanf(mes,"%d",&month);
            sscanf(ano,"%d",&year);
            insereToDo(lista, tarefa, prio, day, month, year, ID);
        }
        fclose(fp);
    }
}

void FICH_tarefas_Doing (t_tarefa *lista){
    FILE *fp;
    char linha[MAX_FGETS], tarefa[MAX_FGETS], id_pessoa[MAX_FGETS], prioridade[MAX_FGETS], idenTarefa[MAX_FGETS], dia[MAX_FGETS], mes[MAX_FGETS], ano[MAX_FGETS], pessoa[MAX_FGETS];
    int prio, ID, day, month, year, idPerson;
    fp = fopen("tarefasDoing.txt","r");
    if (fp == NULL)
        printf ("Erro ao abrir ao ficheiro\n");
    else{
        while (fgets(linha,MAX_FGETS,fp) != NULL)
        {
            strcpy(tarefa,strtok(linha,"/"));
            strcpy(pessoa,strtok(NULL,"/"));
            strcpy(id_pessoa,strtok(NULL,"/"));
            strcpy(prioridade,strtok(NULL,"/"));
            strcpy(idenTarefa,strtok(NULL,"/"));
            strcpy(dia,strtok(NULL,"/"));
            strcpy(mes,strtok(NULL,"/"));
            strcpy(ano,strtok(NULL,"/"));

            sscanf(prioridade,"%d",&prio);
            sscanf(idenTarefa,"%d",&ID);
            sscanf(id_pessoa,"%d",&idPerson);
            sscanf(dia,"%d",&day);
            sscanf(mes,"%d",&month);
            sscanf(ano,"%d",&year);
            insereDoing(lista, tarefa, pessoa, day, month, year, prio, ID, idPerson);
        }
        fclose(fp);
    }
}

void FICH_tarefas_Done (t_tarefa *lista){
    FILE *fp;
    char linha[MAX_FGETS], id_pessoa[MAX_FGETS], tarefa[MAX_FGETS], prioridade[MAX_FGETS], idenTarefa[MAX_FGETS], dia_inicio[MAX_FGETS], mes_inicio[MAX_FGETS], ano_inicio[MAX_FGETS], pessoa[MAX_FGETS], dia_fim[MAX_FGETS], mes_fim[MAX_FGETS], ano_fim[MAX_FGETS];
    int prio, ID, dayI, monthI, yearI, dayF, monthF, yearF, idPerson;
    fp = fopen("tarefasDone.txt","r");
    if (fp == NULL)
        printf ("Erro ao abrir ao ficheiro\n");
    else{
        while (fgets(linha,MAX_FGETS,fp) != NULL)
        {
            strcpy(tarefa,strtok(linha,"/"));
            strcpy(pessoa,strtok(NULL,"/"));
            strcpy(id_pessoa,strtok(NULL,"/"));
            strcpy(prioridade,strtok(NULL,"/"));
            strcpy(idenTarefa,strtok(NULL,"/"));
            strcpy(dia_inicio,strtok(NULL,"/"));
            strcpy(mes_inicio,strtok(NULL,"/"));
            strcpy(ano_inicio,strtok(NULL,"/"));
            strcpy(dia_fim,strtok(NULL,"/"));
            strcpy(mes_fim,strtok(NULL,"/"));
            strcpy(ano_fim,strtok(NULL,"/"));

            sscanf(prioridade,"%d",&prio);
            sscanf(idenTarefa,"%d",&ID);
            sscanf(dia_inicio,"%d",&dayI);
            sscanf(id_pessoa,"%d",&idPerson);
            sscanf(mes_inicio,"%d",&monthI);
            sscanf(ano_inicio,"%d",&yearI);
            sscanf(dia_fim,"%d",&dayF);
            sscanf(mes_fim,"%d",&monthF);
            sscanf(ano_fim,"%d",&yearF);
            insereDone(lista, tarefa, pessoa, dayI, monthI, yearI, prio, dayF, monthF, yearF, &id_Tarefa, idPerson);
        }
        fclose(fp);
    }
}

void ToDo_tarefas_FICH(t_tarefa *lista){
    FILE *fp;
    t_tarefa *aux = lista->prox;
    fp = fopen("tarefasToDo.txt","w");
    if (fp == NULL)
        printf("Erro ao abir o ficheiro\n");
    while (aux != NULL)
    {
        fprintf(fp,"%s/%d/%d/%d/%d/%d\n", aux->tarefa, aux->prioridade, aux->idenTarefa, aux->inicio.dia, aux->inicio.mes, aux->inicio.ano);
        aux = aux->prox;
    }
    fclose(fp);
}

void Doing_tarefas_FICH(t_tarefa *lista){
    FILE *fp;
    t_tarefa *aux = lista->prox;
    fp = fopen("tarefasDoing.txt","w");
    if (fp == NULL)
        printf("Erro ao abrir o ficheiro\n");
    while (aux != NULL)
    {
        fprintf(fp,"%s/%s/%d/%d/%d/%d/%d/%d\n",aux->tarefa, aux->person, aux->id_person, aux->prioridade, aux->idenTarefa, aux->inicio.dia, aux->inicio.mes, aux->inicio.ano);
        aux = aux->prox;
    }
}

void Done_tarefas_FICH(t_tarefa *lista){
    FILE *fp;
    t_tarefa *aux = lista->prox;
    fp = fopen("tarefasDone.txt","w");
    if (fp == NULL)
        printf("Erro ao abrir o ficheiro\n");
    while (aux != NULL)
    {
        fprintf(fp,"%s/%s/%d/%d/%d/%d/%d/%d/%d/%d/%d\n",aux->tarefa, aux->person, aux->id_person, aux->prioridade, aux->idenTarefa, aux->inicio.dia, aux->inicio.mes, aux->inicio.ano, aux->fim.dia, aux->fim.mes, aux->fim.ano);
        aux = aux->prox;
    }
}

void carregaTarefas(t_tarefa *todo, t_tarefa *doing, t_tarefa *done){
    FICH_tarefas_ToDo(todo);         /*Ordem do ficheiro: "tarefa/prioridade/idenTarefa/diaI/mesI/anoI"*/
    FICH_tarefas_Doing(doing);       /*Ordem do ficheiro: "tarefa/pessoa/id_person/prioridade/idenTarefa/diaI/mesI/anoI"*/
    FICH_tarefas_Done(done);         /*Ordem do ficheiro: "tarefa/pessoa/id_person/prioridade/idenTarefa/diaI/mesI/anoI/diaF/mesF/anoF"*/
}

void guardaTarefas(t_tarefa *todo, t_tarefa *doing, t_tarefa *done){
    int tarefitas;
    printf("Pretende guardar as tarefas inseridas? (0 = NAO, 1 = SIM)\n");
    scanf("%d",&tarefitas);
    if (tarefitas == 1)
    {
        ToDo_tarefas_FICH(todo);           /*Ordem do ficheiro: "tarefa/prioridade/idenTarefa/diaI/mesI/anoI"*/
        Doing_tarefas_FICH(doing);         /*Ordem do ficheiro: "tarefa/pessoa/id_person/prioridade/idenTarefa/diaI/mesI/anoI"*/
        Done_tarefas_FICH(done);           /*Ordem do ficheiro: "tarefa/pessoa/id_person/prioridade/idenTarefa/diaI/mesI/anoI/diaF/mesF/anoF"*/
    }
}

void imprimePessoa_ID(t_person *lista){
    t_person *aux = lista->prox;
    while (aux != NULL)
    {
        printf("%s | %d\n",aux->nome,aux->iden);
        aux = aux->prox;
    }
}

t_tarefa *imprimeTarefasPessoa(t_tarefa *lista, int iden){
    t_tarefa *aux = lista->prox;
    int cont = 0;
    while (aux != NULL){
        if(aux->id_person == iden){
            printf("%s\n ", aux->tarefa);
            cont++;
        }
        aux = aux->prox;
    }
    if (cont == 0)
        printf("Nao tem tarefas\n");
    return aux;
}

void verifica_ID_repetido(t_person *lista, int *id){
    t_person *aux = lista->prox;
    while(aux != NULL){
        if(aux->iden == *id){
            printf("Ja existe uma pessoa com esse id, escolha outro por favor:\n>");
            scanf("%d", id);
            aux = lista;
        }
        aux = aux->prox;
    }
}

t_person *leLinhaSeparado(t_person *lista){
    int id, maxTasks;
    char linha[MAX_FGETS], nome[MAX_FGETS], mail[MAX_FGETS], iden[MAX_FGETS], traco[5], maxTarefas[MAX_FGETS];
    char *verificaNome, *verificaMail, *verificaID;
    strcpy(traco, "--");
    FILE *fp;
    fp = fopen("pessoas.txt","r");
    if (fp == NULL){
        printf("Erro ao abrir o ficheiro!\n");
        return 0;
    }
    while (fgets(linha,MAX_FGETS,fp) != NULL){
        verificaNome = strtok(linha,"/");
        if (strcmp(verificaNome, traco) == 0){
            printf("A introducao nao foi bem sucedida porque a pessoa nao tinha nome\n");
            continue;
        }
            else
                strcpy(nome, verificaNome);
        verificaMail = strtok(NULL,"/");
        if (strcmp(verificaMail, traco) == 0){
            printf("A introducao de %s nao foi bem sucedida porque nao tinha email\n", nome);
            continue;
        }
            else
                strcpy(mail, verificaMail);
        verificaID = strtok(NULL,"/");
        if (strcmp(verificaID, traco) == 0){
            printf("A introducao de %s nao foi bem sucedida porque nao tinha ID\n", nome);
            continue;
        }
            else
                strcpy(iden, verificaID);
        strcpy(maxTarefas,strtok(NULL,"/"));
        sscanf(maxTarefas,"%d",&maxTasks);
        sscanf(iden,"%d",&id);
        verifica_ID_repetido(lista, &id);
        inserePessoa(lista, nome, mail, id, maxTasks);
    }
    fclose(fp);
    return 0;
}

int main(){
    int maximo_tarefas_pessoa = MAXIMO_PESSOA, id, flagErro = 0;
    char letra;
    t_person *cabeca_p = cria_cabecalhoP();
    t_tarefa *cabeca_todo = cria_cabecalhoT();
    t_tarefa *cabeca_doing = cria_cabecalhoT();
    t_tarefa *cabeca_done = cria_cabecalhoT();
    t_tarefa *cabeca_ordena = cria_cabecalhoT();
    leLinhaSeparado(cabeca_p);
    carregaTarefas(cabeca_todo, cabeca_doing, cabeca_done);
    atualiza_ID_3listas(cabeca_todo, cabeca_doing, cabeca_done, &id_Tarefa);
    do{
        if (flagErro)
            clrscr();
        flagErro = 1;
        menu(&letra);
        switch (letra){
            case 'A':       /*FUNCIONA BEM*/
                clrscr();
                maxTarefas(&maximo_tarefas_pessoa);
                break;
            case 'B':       /*FUNCIONA BEM*/
                clrscr();
                Dadostarefa(cabeca_todo);
                break;
            case 'C':       /*FUNCIONA MAL - N METE POR ORDEM ALFABETICA NO DOING QUANDO SE MISTURA FICHEIRO COM INSERIDO A MAO*/
                clrscr();
                toDo_Doing(cabeca_p, cabeca_todo, cabeca_doing, maximo_tarefas_pessoa);     /*Mexer de TO DO para DOING*/
                break;
            case 'F':       /*FUNCIONA BEM*/
                clrscr();
                alteraResponsavel(cabeca_doing, cabeca_p);      /*Alterar pessoa responsavel por uma tarefa em DOING*/
                break;
            case 'D':       /*ENVIA PARA DONE, MAS PRECISA DE HEADER NO DOING*/
                clrscr();
                prepara_done(cabeca_doing, cabeca_done, cabeca_p);
                /*Enviar cartao de DOING para DONE*/
                break;
            case 'E':       /*NAO TA FEITA*/
                clrscr();
                /*Enviar cartao de DONE para TO DO*/
                break;
            case 'G':       /*FUNCIONA BEM*/
                clrscr();
                imprimeLista_t_ToDo(cabeca_todo);
                imprimeLista_t_Doing(cabeca_doing);
                imprimeLista_t_Done(cabeca_done);
                getchar();
                getchar();
                break;
            case 'H':       /*FUNCIONA BEM*/
                clrscr();
                imprimePessoa_ID(cabeca_p);
                printf("Qual e o ID da pessoa que pretende saber as tarefas? \n>");
                scanf("%d",&id);
                imprimeTarefasPessoa(cabeca_doing, id);
                imprimeTarefasPessoa(cabeca_done, id);
                getchar();
                break;
            case 'I':       /*TA MAL, NAO IMPRIME*/
                clrscr();
                todas_tarefas_ordem(cabeca_todo, cabeca_doing, cabeca_done, cabeca_ordena);
                break;
            case 'J':       /*FUNCIONA BEM*/
                clrscr();
                imprimeLista_p(cabeca_p);
                getchar();
                break;
            case 'K':       /*FUNCINA BEM*/
                clrscr();
                apagar_Tarefa(cabeca_todo);
                break;
            case 'S':
                break;
            default:
                clrscr();
                break;
        }
    } while (letra != 'S');
    clrscr();
    guardaTarefas(cabeca_todo, cabeca_doing, cabeca_done);
    clrscr();
    imprimeLista_p(cabeca_p);
    printf("\n\n");
    imprimeLista_t_ToDo(cabeca_todo);
    printf("\n\n");
    imprimeLista_t_Doing(cabeca_doing);
    return 0;
}
