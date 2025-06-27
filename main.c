/*
 * GRUPO: Gustavo Dosso, Leandro Deon, Lucas Pontes
 *
 * Quiz da Sustentabilidade
 * -------------------------
 * Este programa é um quiz interativo em linguagem C com 20 perguntas sobre sustentabilidade,
 * consumo consciente, meio ambiente e responsabilidade social.
 * As perguntas e alternativas são embaralhadas para tornar o jogo dinâmico.
 * Ao final, a pontuação do usuário é calculada e apresentada com feedback visual.
 *
 * Recursos utilizados:
 * - Embaralhamento de perguntas e alternativas
 * - Cores ANSI para destacar acertos e erros
 * - Localização UTF-8 para exibir acentuação corretamente
 *
 * Desenvolvido para fins educacionais.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //funções para trabalhar com strings
#include <time.h> //funções de tempo
#include <windows.h> //para reconhecer acentuação
#include <ctype.h>
#include <time.h>   // para usar time() com srand()
#ifdef _WIN32 // para usar sleep()
    #include <windows.h>
#else
    #include <unistd.h>
#endif


// Constantes para definir limites
#define NUM_PERGUNTAS 4 //a principio será fixo o número de perguntas, temos que revisar
#define NUM_ALTERNATIVAS 4 // isso é fixo
#define TAM 100                 // Define o tamanho de entrada aceita pelo usuário no cadastro

// constantes para os banners
#define MAX_LINHAS 10
#define LARGURA_BANNER 60
#define bb_up_left "#"      // "╔"
#define bb_up_right "#"     // "╗"
#define bb_down_left "#"    // "╚"
#define bb_down_right "#"   // "╝"
#define bb_up_down "="      // "═"
#define bb_left_right "|"   // "║"


// Estrutura para armazenar dados de cadastro do usuário
struct Usuario {
    int idade;
    char cidade[TAM];
    char genero[TAM];
    char escolaridade[TAM];
    char ocupacao[TAM];
    char frequenciaInternet[TAM];
    char participacaoAmbiental[TAM];
};

struct Pergunta {  //um objeto 'Pergunta', essa pergunta contém: tem enunciado | alternativas | resposta certa | pontuação;
    char enunciado[200];
    char alternativas[NUM_ALTERNATIVAS][100];
    int correta; // índice da alternativa correta (0 a 3)
    int pontuacao;
};

//BANCO DE DADOS ----------------------------------------------------------------------------
//cada item do vetor é um objeto Pergunta (contem as caracteristicas da pergunta)
struct Pergunta banco[] = { 
    {"Qual é uma prática sustentável para reduzir o consumo de plástico?",
     {"Usar sacolas reutilizáveis", "Comprar mais embalagens", "Jogar no rio", "Usar copo descartável"}, 0, 100},
    {"O que é reciclagem?",
     {"Transformar resíduos em novos produtos", "Descartar em lixão", "Queimar lixo", "Ignorar resíduos"}, 0, 80},
    {"Como economizar energia em casa?",
     {"Desligar aparelhos não utilizados", "Deixar luzes acesas", "Usar ar-condicionado o dia todo", "Abrir geladeira sempre"}, 0, 90},
    {"Qual atitude ajuda a justiça social?",
     {"Incluir minorias no trabalho", "Discriminar pessoas", "Ignorar desigualdades", "Privar acesso à educação"}, 0, 90},
    {"Qual ação combate o desmatamento?",
     {"Reflorestamento", "Queimada para plantio", "Expansão urbana", "Desmatamento ilegal"}, 0, 95},
    {"O que é consumo consciente?",
     {"Comprar apenas o necessário", "Comprar por impulso", "Acumular objetos", "Ignorar origem dos produtos"}, 0, 85},
    {"Qual o impacto de jogar lixo em local errado?",
     {"Poluição ambiental", "Ajuda na drenagem", "Fertiliza o solo", "Não afeta em nada"}, 0, 70},
    {"Para que serve a compostagem?",
     {"Transformar resíduos orgânicos em adubo", "Criar lixo tóxico", "Produzir plásticos", "Destruir plantas"}, 0, 75},
    {"Qual transporte é mais sustentável?",
     {"Bicicleta", "Carro a gasolina", "Avião particular", "Caminhão"}, 0, 100},
    {"O que representa a pegada ecológica?",
     {"Impacto de consumo no meio ambiente", "Pegada no chão", "Digitalização de serviços", "Consumo de papel"}, 0, 80},
    {"Por que economizar água é importante?",
     {"Evita desperdício e preserva recursos", "Porque é moda", "Porque é caro", "Porque sim"}, 0, 85},
    {"Plantar árvores ajuda como?",
     {"Reduz CO2 e melhora o ar", "Causa poluição", "Gasta energia", "Aumenta calor"}, 0, 95},
    {"O que é energia renovável?",
     {"Energia que se regenera naturalmente", "Energia de carvão", "Gasolina", "Nuclear"}, 0, 90},
    {"Como ajudar no descarte correto?",
     {"Separar lixo reciclável", "Jogar no mato", "Queimar em casa", "Enterrar plástico"}, 0, 80},
    {"Por que é importante respeitar a fauna?",
     {"Preserva o equilíbrio ecológico", "Para caçar melhor", "Porque são bonitos", "Não tem importância"}, 0, 70},
    {"Desenvolvimento sustentável é...",
     {"Atender necessidades sem esgotar recursos", "Crescer sem limites", "Explorar ao máximo", "Desmatar para plantar"}, 0, 95},
    {"A energia solar é...",
     {"Fonte limpa e renovável", "Fóssil", "Inútil", "Poluente"}, 0, 85},
    {"O que é efeito estufa?",
     {"Aquecimento da Terra por gases", "Resfriamento global", "Fumaça da indústria", "Chuva ácida"}, 0, 80},
    {"Como evitar o desperdício de alimentos?",
     {"Planejar compras e reaproveitar", "Jogar comida fora", "Comprar além do necessário", "Deixar estragar"}, 0, 90},
    {"Por que reutilizar é importante?",
     {"Reduz o lixo e economiza recursos", "Gera mais resíduos", "É moda", "Não tem impacto"}, 0, 85}
};

#define NUM_TOTAL_PERGUNTAS (sizeof(banco) / sizeof(banco[0])) //defini automatico a quantidade de perguntas que existem no banco

void embaralhar_perguntas(int indices[], int tamanho) { // um função que recebe um indices e um tamanho
    for (int i = 0; i < tamanho; i++) { //gera um indice de todas as perguntas (ex: 20 indices)
        indices[i] = i;
    }
    for (int i = 0; i < tamanho; i++) { //embaralha os 20 indices entre eles mesmo (troca o 1 pelo 7 | o 2 pelo 12....)
        int j = rand() % tamanho; //gera número aleatório valido (tamnho do indices)
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }
}


void embaralhar_alternativas(char alternativas[][100], int *correta) { //embaralha as alternativas
    for (int i = 0; i < 10; i++) { //roda 10 vezes, alterando 2 alternativas aleatóriamente
        int a = rand() % NUM_ALTERNATIVAS; //seleciona 2 alternativas A e B entre as 4 disponiveis
        int b = rand() % NUM_ALTERNATIVAS;
        if (a == b) continue; //se A e B forem igual, continua sem alterar nada.
        char temp[100];                            // cria um espaço temporario
        strcpy(temp, alternativas[a]);             // copia o conteudo de A para temp
        strcpy(alternativas[a], alternativas[b]);  // copia o conteúdo de B para A
        strcpy(alternativas[b], temp);             // copia o conteúdo de A salvo em 'temp' para B
        if (a == *correta)  // caso uma delas seja a correta ajusta o indice de qual é a correta depois da alteração
            *correta = b;  // o * (ponteiro)  é usado pq temos que mudar o valor de um variavel que não  está na função
        else if (b == *correta)
            *correta = a;
    }
}


// Função para remover '\n' final de strings
void limparNovaLinha(char *str) {
    str[strcspn(str, "\n")] = 0;
}

// Função para verificar se uma string está vazia (apenas espaços ou nada)
int stringVazia(const char *str) {
    while (*str) {
        if (!isspace(*str)) return 0;
        str++;
    }
    return 1;
}

void print_banner(const char *linhas[], int qtd_linhas) {
    int i;

    // Topo ╔═══════════════╗
    printf(bb_up_left);
    for (i = 0; i < LARGURA_BANNER; i++) printf(bb_up_down);
    printf("%s\n", bb_up_right);


    // Linhas com texto centralizado
    for (i = 0; i < qtd_linhas; i++) {
        int espacos = LARGURA_BANNER - strlen(linhas[i]);
        int esquerda = espacos / 2;
        int direita = espacos - esquerda;

        printf(bb_left_right);
        for (int j = 0; j < esquerda; j++) printf(" ");
        printf("%s", linhas[i]);
        for (int j = 0; j < direita; j++) printf(" ");
        printf("%s\n", bb_left_right);
    }

    // Base ╚═══════════════╝
    printf(bb_down_left);
    for (i = 0; i < LARGURA_BANNER; i++) printf(bb_up_down);
    printf("%s\n", bb_down_right);
}

int main( void ) {
    SetConsoleOutputCP(CP_UTF8); //para reconhecer acentuação

    // banners
    const char *banner_title[] = {
        "BEM-VINDO AO QUIZ DA SUSTENTABILIDADE",
        "Coleta de Dados do Participante"
    };
    const char *banner_data_collected[] = {
        "DADOS COLETADOS COM SUCESSO!"
    };
    const char *banner_welcome_quiz[] = {
        "JOGO - QUIZ DA SUSTENTABILIDADE"
    };
    const char *banner_end_game[] = {
        "FIM DO JOGO"
    };

    // *******************
    // CADASTRO DO USUÁRIO
    // *******************

    print_banner(banner_title, 2);
    printf("\n");

    struct Usuario usuario;

    char buffer[TAM];

    // Idade: deve ser um número positivo
    do {
        printf("Digite sua idade: ");
        fgets(buffer, TAM, stdin);
        usuario.idade = atoi(buffer);
        if (usuario.idade <= 0) {
            printf("❌ Idade inválida. Tente novamente.\n");
        }
    } while (usuario.idade <= 0);

    // Cidade: não pode ser vazia
    do {
        printf("Cidade: ");
        fgets(usuario.cidade, TAM, stdin);
        limparNovaLinha(usuario.cidade);
        if (stringVazia(usuario.cidade)) {
            printf("❌ Cidade não pode estar vazia. Tente novamente.\n");
        }
    } while (stringVazia(usuario.cidade));

    // Gênero (opcional)
    printf("Gênero (opcional): ");
    fgets(usuario.genero, TAM, stdin);
    limparNovaLinha(usuario.genero);

    // Escolaridade: não pode ser vazia
    do {
        printf("Nível de Escolaridade: ");
        fgets(usuario.escolaridade, TAM, stdin);
        limparNovaLinha(usuario.escolaridade);
        if (stringVazia(usuario.escolaridade)) {
            printf("❌ Escolaridade não pode estar vazia. Tente novamente.\n");
        }
    } while (stringVazia(usuario.escolaridade));

    // Ocupação: não pode ser vazia
    do {
        printf("Digite sua ocupação principal (ex: estudante, agricultor, engenheiro...): ");
        fgets(usuario.ocupacao, TAM, stdin);
        limparNovaLinha(usuario.ocupacao);
        if (stringVazia(usuario.ocupacao)) {
            printf("❌ Ocupação não pode estar vazia. Tente novamente.\n");
        }
    } while (stringVazia(usuario.ocupacao));

    // Frequência de Acesso à Internet: não pode ser vazia
    do {
        printf("Frequência de Acesso à Internet: ");
        fgets(usuario.frequenciaInternet, TAM, stdin);
        limparNovaLinha(usuario.frequenciaInternet);
        if (stringVazia(usuario.frequenciaInternet)) {
            printf("❌ Esse campo não pode estar vazio. Tente novamente.\n");
        }
    } while (stringVazia(usuario.frequenciaInternet));

    // Participação em Ações Ambientais: não pode ser vazia
    do {
        printf("Participação em Ações Ambientais: ");
        fgets(usuario.participacaoAmbiental, TAM, stdin);
        limparNovaLinha(usuario.participacaoAmbiental);
        if (stringVazia(usuario.participacaoAmbiental)) {
            printf("❌ Esse campo não pode estar vazio. Tente novamente.\n");
        }
    } while (stringVazia(usuario.participacaoAmbiental));


    // *******************
    // QUIZ
    // *******************

    srand(time(NULL)); // inicializa gerador de números aleatórios com base no tempo atual
    int indices[NUM_TOTAL_PERGUNTAS];
    embaralhar_perguntas(indices, NUM_TOTAL_PERGUNTAS);

    int pontuacao_total = 0;
    int pontuacao_maxima = 0;

    print_banner(banner_welcome_quiz, 1);
    printf("\n");

    for (int i = 0; i < NUM_PERGUNTAS; i++) {
        int id = indices[i]; //pega um indice de uma pergunta, já embaralhada
        struct Pergunta p = banco[id]; //pega a pergunta conforme  o indice

        int correta = p.correta; //salva qual é a alternativa correta
        pontuacao_maxima += p.pontuacao;  
        embaralhar_alternativas(p.alternativas, &correta); //embaralha as alternativas mantendo a info de qual é a correta

        printf("\nPergunta %d:\n%s\n", i + 1, p.enunciado); //mostra a pergunta
        for (int j = 0; j < NUM_ALTERNATIVAS; j++) { //mostra as 4 alternativas (possivel colocar mais)
            printf("%c) %s\n", 'a' + j, p.alternativas[j]);
        }

        char resp;
        printf("Sua resposta: "); //resposta do usuário
        scanf(" %c", &resp);
        while ((getchar()) != '\n'); //limpa buffer teclado e "enter" sobrando
        int index = resp - 'a'; //converte a resposta para um número de 0 a 3 [a=97 b=98 c=99 d=100] || b(98) - a(97) = 1(b)

        if (index == correta) {
            printf("✅ Correto! +%d pontos\n", p.pontuacao);
            pontuacao_total += p.pontuacao; //adiciona pontuação
        } else {
            printf("❌ Errado! Resposta correta: %s\n", p.alternativas[correta]);
        }
    }

    // Mostra a pontuação final
    printf("\n\n");
    print_banner(banner_end_game, 1);
    printf("Pontuação final: %d de %d pontos possíveis.\n", 
        pontuacao_total, 
        pontuacao_maxima
    );

    
    // Registra os dados em um banco

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);  

    FILE *banco_de_dados = fopen("database.txt", "a");

    if (banco_de_dados == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
    return 1;
}

    fprintf( 
        banco_de_dados, 
        "\n\n[%4d-%2d-%2d | %2d:%2d]", 
        tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min
    );

    fprintf(banco_de_dados, "\n");
    fprintf(banco_de_dados, "Idade: %d\n", usuario.idade);
    fprintf(banco_de_dados, "Cidade: %s\n", usuario.cidade);
    fprintf(banco_de_dados, "Gênero: %s\n", usuario.genero);
    fprintf(banco_de_dados, "Escolaridade: %s\n", usuario.escolaridade);
    fprintf(banco_de_dados, "Ocupação: %s\n", usuario.ocupacao);
    fprintf(banco_de_dados, "Frequência de Internet: %s\n", usuario.frequenciaInternet);
    fprintf(banco_de_dados, "Participação Ambiental: %s\n", usuario.participacaoAmbiental);
    
    fclose(banco_de_dados);

    Sleep(10000); // 10s para o usuário analizar o resultado

    return 0;
}