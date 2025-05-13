#include <stdio.h>
#include <stdlib.h>

#define TAM_TABULEIRO 10
#define TAM_HABILIDADE 5

// Função para inicializar o tabuleiro com água (0) e alguns navios (3)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            // Coloca água em todas as posições
            tabuleiro[i][j] = 0;
            
            // Adiciona alguns navios aleatoriamente (cerca de 20% do tabuleiro)
            if (rand() % 5 == 0) {
                tabuleiro[i][j] = 3;
            }
        }
    }
}

// Função para criar a matriz de habilidade em formato de Cone
void criarHabilidadeCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Cone: forma triangular que se expande para baixo
            if (j >= i && j < TAM_HABILIDADE - i) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar a matriz de habilidade em formato de Cruz
void criarHabilidadeCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Cruz: linha central horizontal e vertical
            if (i == centro || j == centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar a matriz de habilidade em formato de Octaedro (losango)
void criarHabilidadeOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Octaedro: forma de losango (diagonais dentro de um raio do centro)
            int distVertical = abs(i - centro);
            int distHorizontal = abs(j - centro);
            if (distVertical + distHorizontal <= centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para aplicar uma habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], 
                      int habilidade[TAM_HABILIDADE][TAM_HABILIDADE],
                      int linha_origem, int coluna_origem) {
    int offset = TAM_HABILIDADE / 2;
    
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Calcula as coordenadas no tabuleiro
            int tab_linha = linha_origem - offset + i;
            int tab_coluna = coluna_origem - offset + j;
            
            // Verifica se está dentro dos limites do tabuleiro
            if (tab_linha >= 0 && tab_linha < TAM_TABULEIRO &&
                tab_coluna >= 0 && tab_coluna < TAM_TABULEIRO) {
                
                // Se a posição na matriz de habilidade estiver ativa, marca no tabuleiro
                if (habilidade[i][j] == 1) {
                    tabuleiro[tab_linha][tab_coluna] = 5; // Área afetada
                }
            }
        }
    }
}

// Função para imprimir o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];
    
    // Inicializa o tabuleiro com navios aleatórios
    inicializarTabuleiro(tabuleiro);
    
    // Cria as matrizes de habilidades
    criarHabilidadeCone(cone);
    criarHabilidadeCruz(cruz);
    criarHabilidadeOctaedro(octaedro);
    
    // Imprime o tabuleiro original
    printf("Tabuleiro original:");
    imprimirTabuleiro(tabuleiro);
    
    // Aplica a habilidade Cone no centro do tabuleiro
    aplicarHabilidade(tabuleiro, cone, 4, 4);
    printf("\nTabuleiro com habilidade Cone (5,5):");
    imprimirTabuleiro(tabuleiro);
    
    // Aplica a habilidade Cruz em outra posição
    aplicarHabilidade(tabuleiro, cruz, 7, 2);
    printf("\nTabuleiro com habilidade Cruz (7,2):");
    imprimirTabuleiro(tabuleiro);
    
    // Aplica a habilidade Octaedro em outra posição
    aplicarHabilidade(tabuleiro, octaedro, 2, 7);
    printf("\nTabuleiro com habilidade Octaedro (2,7):");
    imprimirTabuleiro(tabuleiro);
    
    return 0;
}