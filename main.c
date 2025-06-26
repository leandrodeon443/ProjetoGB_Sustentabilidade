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
#include <string.h>
#include <ctype.h>
#include <time.h>   // para usar time() com srand()
#include <locale.h> // para configurar acentuação/UTF-8 no terminal
#ifdef _WIN32 // para usar sleep()
    #include <windows.h>
#else
    #include <unistd.h>
#endif


// Constantes para definir limites
#define NUM_PERGUNTAS 20        // número de perguntas a serem usadas no quiz
#define NUM_TOTAL_PERGUNTAS 20  // número total disponível no banco
#define NUM_ALTERNATIVAS 4      // número de alternativas por pergunta
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


// Estrutura que define uma pergunta do quiz
struct Pergunta {
    char enunciado[200];               
    char alternativas[NUM_ALTERNATIVAS][100];   // lista de alternativas
    int correta;                                // índice da alternativa correta (0 a 3)
    int pontuacao;                              // pontuação associada à pergunta
};

struct Pergunta banco[NUM_TOTAL_PERGUNTAS] = {
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


// Função que embaralha os índices das perguntas para apresentar em ordem aleatória
void embaralhar_perguntas(int indices[], int tamanho) {
    // Preenche o vetor com os índices originais
    for (int i = 0; i < tamanho; i++) {
        indices[i] = i;
    }
    // Embaralha os índices usando troca aleatória
    for (int i = 0; i < tamanho; i++) {
        int j = rand() % tamanho;
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
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


// Função que embaralha as alternativas de uma pergunta mantendo controle da resposta correta
void embaralhar_alternativas(char alternativas[][100], int *correta) {
    for (int i = 0; i < 10; i++) {

        int a = rand() % NUM_ALTERNATIVAS;
        int b = rand() % NUM_ALTERNATIVAS;
        if (a == b) continue;

        // Troca o texto das alternativas
        char temp[100];
        strcpy(temp, alternativas[a]);
        strcpy(alternativas[a], alternativas[b]);
        strcpy(alternativas[b], temp);

        // Ajusta o índice da correta caso ela tenha sido trocada
        if (a == *correta)
            *correta = b;
        else if (b == *correta)
            *correta = a;
    }
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
    setlocale(LC_ALL, "Portuguese_Brazil"); // print UTF-8 char

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
        int id = indices[i];
        struct Pergunta p = banco[id];

        int correta = p.correta;
        pontuacao_maxima += p.pontuacao;    
        embaralhar_alternativas(p.alternativas, &correta);

        printf("Pergunta %d:\n%s\n", i + 1, p.enunciado);
        for (int j = 0; j < NUM_ALTERNATIVAS; j++) {
            printf("%c) %s\n", 'a' + j, p.alternativas[j]);
        }

        // Lê a resposta do usuário
        char resp;
        printf("Sua resposta: ");
        scanf(" %c", &resp);
        while ((getchar()) != '\n'); // limpa o buffer do teclado
        int index = resp - 'a'; // converte letra para índice (ex: 'a' → 0)
        
        // Verifica se a resposta está correta
        if (index == correta) {
            printf("✅ Correto! +%d pontos\n", p.pontuacao);
            pontuacao_total += p.pontuacao;
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

    Sleep(10);

    return 0;
}