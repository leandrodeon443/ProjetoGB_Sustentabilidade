#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_PERGUNTAS 20
#define NUM_TOTAL_PERGUNTAS 20
#define NUM_ALTERNATIVAS 4

struct Pergunta {
    char enunciado[200];
    char alternativas[NUM_ALTERNATIVAS][100];
    int correta; // índice da alternativa correta (0 a 3)
    int pontuacao;
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

void embaralhar_perguntas(int indices[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        indices[i] = i;
    }
    for (int i = 0; i < tamanho; i++) {
        int j = rand() % tamanho;
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }
}

void embaralhar_alternativas(char alternativas[][100], int *correta) {
    for (int i = 0; i < 10; i++) {
        int a = rand() % NUM_ALTERNATIVAS;
        int b = rand() % NUM_ALTERNATIVAS;
        if (a == b) continue;
        char temp[100];
        strcpy(temp, alternativas[a]);
        strcpy(alternativas[a], alternativas[b]);
        strcpy(alternativas[b], temp);
        if (a == *correta)
            *correta = b;
        else if (b == *correta)
            *correta = a;
    }
}

int main() {
    srand(time(NULL));
    int indices[NUM_TOTAL_PERGUNTAS];
    embaralhar_perguntas(indices, NUM_TOTAL_PERGUNTAS);

    int pontuacao_total = 0;
    printf("===== JOGO - QUIZ DA SUSTENTABILIDADE =====\n");

    for (int i = 0; i < NUM_PERGUNTAS; i++) {
        int id = indices[i];
        struct Pergunta p = banco[id];

        int correta = p.correta;
        embaralhar_alternativas(p.alternativas, &correta);

        printf("\nPergunta %d:\n%s\n", i + 1, p.enunciado);
        for (int j = 0; j < NUM_ALTERNATIVAS; j++) {
            printf("%c) %s\n", 'a' + j, p.alternativas[j]);
        }

        char resp;
        printf("Sua resposta: ");
        scanf(" %c", &resp);
        while ((getchar()) != '\n');
        int index = resp - 'a';

        if (index == correta) {
            printf("✅ Correto! +%d pontos\n", p.pontuacao);
            pontuacao_total += p.pontuacao;
        } else {
            printf("❌ Errado! Resposta correta: %s\n", p.alternativas[correta]);
        }
    }

    printf("\n===== FIM DO JOGO =====\n");
    printf("Pontuação final: %d de %d pontos possíveis.\n", pontuacao_total, NUM_PERGUNTAS * 100);

    return 0;
}
