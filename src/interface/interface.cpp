#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <random>
#include <limits>
#include "../modelo/imagens.cpp"
using namespace std;
// Funcoes dos algoritmos
void bubbleSort(
    vector<Imagem>& dados,
    int criterio
);
void insertionSort(
    vector<Imagem>& dados,
    int criterio
);
void quickSort(
    vector<Imagem>& dados,
    int criterio
);
class Interface {
private:
    int origemSelecionada;
    int quantidadeSelecionada;
    int criterioSelecionado;
    int algoritmoSelecionado;
    string caminhoArquivoExterno;
    vector<Imagem> dados;
public:
    Interface() {
        origemSelecionada = 1;
        quantidadeSelecionada = 1000;
        criterioSelecionado = 1;
        algoritmoSelecionado = 1;
    }
    void executar() {
        bool continuar = true;
        while (continuar) {
            cout << "\n\n";
            cout
                << "============================================================\n";
            cout
                << "       SISTEMA DE ALGORITMOS DE ORDENACAO\n";
            cout
                << "============================================================\n";
            cout
                << " Bubble Sort | Insertion Sort | Quick Sort\n";
            cout
                << "============================================================\n";
            escolherOrigem();
            escolherQuantidade();
            escolherCriterio();
            escolherAlgoritmo();
            if (!carregarDados()) {
                cout
                    << "\nNao foi possivel carregar os dados.\n";
                return;
            }
            mostrarResumo();
            executarAlgoritmo();
            cout << "\n";
            cout
                << "Deseja executar outro teste?\n";
            cout
                << "1 - Sim\n";
            cout
                << "2 - Nao\n";
            int opcao =
                lerOpcao(
                    "Escolha: ",
                    1,
                    2
                );
            if (opcao == 2) {
                continuar = false;
            }
        }
        cout
            << "\nPrograma encerrado.\n";
    }
private:
    int lerOpcao(
        string mensagem,
        int minimo,
        int maximo
    ) {
        int valor;
        while (true) {
            cout << mensagem;
            if (
                cin >> valor &&
                valor >= minimo &&
                valor <= maximo
            ) {
                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n'
                );
                return valor;
            }
            cout
                << "Opcao invalida.\n";
            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );
        }
    }
    void escolherOrigem() {
        cout << "\n";
        cout
            << "---------------- ORIGEM DOS DADOS ----------------\n";
        cout
            << "1 - Arquivo interno\n";
        cout
            << "2 - Arquivo externo\n";
        cout
            << "3 - Amostra aleatoria\n";
        cout << "\n";
        origemSelecionada =
            lerOpcao(
                "Escolha: ",
                1,
                3
            );
        if (
            origemSelecionada == 2
        ) {
            cout << "\n";
            cout
                << "Digite o caminho do arquivo:\n";
            getline(
                cin,
                caminhoArquivoExterno
            );
        }
    }
    void escolherQuantidade() {
        cout << "\n";
        cout
            << "------------- QUANTIDADE DE REGISTROS -------------\n";
        cout
            << "Exemplos: 1000, 5000, 10000, 50000\n\n";
        while (true) {
            cout
                << "Quantidade: ";
            if (
                cin >> quantidadeSelecionada &&
                quantidadeSelecionada > 0
            ) {
                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n'
                );
                break;
            }
            cout
                << "Quantidade invalida.\n";
            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );
        }
    }
    void escolherCriterio() {
        cout << "\n";
        cout
            << "-------------- CRITERIO DE ORDENACAO --------------\n";
        cout
            << "1 - ID\n";
        cout
            << "2 - Nome\n";
        cout
            << "3 - Tamanho\n";
        cout
            << "4 - Largura\n";
        cout
            << "5 - Altura\n";
        cout << "\n";
        criterioSelecionado =
            lerOpcao(
                "Escolha: ",
                1,
                5
            );
    }
    void escolherAlgoritmo() {
        cout << "\n";
        cout
            << "-------------------- ALGORITMO --------------------\n";
        cout
            << "1 - Bubble Sort\n";
        cout
            << "2 - Insertion Sort\n";
        cout
            << "3 - Quick Sort\n";
        cout
            << "4 - Comparar todos\n";
        cout << "\n";
        algoritmoSelecionado =
            lerOpcao(
                "Escolha: ",
                1,
                4
            );
    }
    bool carregarDados() {
        dados.clear();
        if (
            origemSelecionada == 1
        ) {
            dados =
                lerArquivo(
                    "src/dados/dados.txt"
                );
        }
        else if (
            origemSelecionada == 2
        ) {
            dados =
                lerArquivo(
                    caminhoArquivoExterno
                );
        }
        else {
            dados =
                lerArquivo(
                    "src/dados/dados.txt"
                );
            random_device dispositivo;
            mt19937 gerador(
                dispositivo()
            );
            shuffle(
                dados.begin(),
                dados.end(),
                gerador
            );
        }
        if (
            dados.empty()
        ) {
            return false;
        }
        if (
            quantidadeSelecionada <
            static_cast<int>(
                dados.size()
            )
        ) {
            dados.resize(
                quantidadeSelecionada
            );
        }
        else if (
            quantidadeSelecionada >
            static_cast<int>(
                dados.size()
            )
        ) {
            cout << "\n";
            cout
                << "O arquivo possui apenas "
                << dados.size()
                << " registros.\n";
            quantidadeSelecionada =
                static_cast<int>(
                    dados.size()
                );
        }
        return true;
    }
    vector<Imagem> lerArquivo(
        string caminho
    ) {
        vector<Imagem> registros;
        ifstream arquivo(
            caminho
        );
        if (
            !arquivo.is_open()
        ) {
            cout << "\n";
            cout
                << "Erro ao abrir arquivo:\n";
            cout
                << caminho
                << "\n";
            return registros;
        }
        string linha;
        while (
            getline(
                arquivo,
                linha
            )
        ) {
            if (
                linha.empty()
            ) {
                continue;
            }
            stringstream leitor(
                linha
            );
            string idTexto;
            string nome;
            string tamanhoTexto;
            string alturaTexto;
            string larguraTexto;
            getline(
                leitor,
                idTexto,
                ';'
            );
            getline(
                leitor,
                nome,
                ';'
            );
            getline(
                leitor,
                tamanhoTexto,
                ';'
            );
            getline(
                leitor,
                alturaTexto,
                ';'
            );
            getline(
                leitor,
                larguraTexto,
                ';'
            );
            try {
                replace(
                    tamanhoTexto.begin(),
                    tamanhoTexto.end(),
                    ',',
                    '.'
                );
                int id =
                    stoi(
                        idTexto
                    );
                double tamanho =
                    stod(
                        tamanhoTexto
                    );
                int altura =
                    stoi(
                        alturaTexto
                    );
                int largura =
                    stoi(
                        larguraTexto
                    );
                registros.push_back(
                    Imagem(
                        id,
                        nome,
                        tamanho,
                        largura,
                        altura
                    )
                );
            }
            catch (...) {
                cout << "\n";
                cout
                    << "Erro ao processar linha:\n";
                cout
                    << linha
                    << "\n";
            }
        }
        arquivo.close();
        return registros;
    }
    void mostrarResumo() {
        cout << "\n";
        cout
            << "============================================================\n";
        cout
            << "                    RESUMO DO TESTE\n";
        cout
            << "============================================================\n";
        cout
            << "Origem:     "
            << nomeOrigem()
            << "\n";
        cout
            << "Quantidade: "
            << dados.size()
            << "\n";
        cout
            << "Criterio:   "
            << nomeCriterio()
            << "\n";
        cout
            << "Algoritmo:  "
            << nomeAlgoritmo()
            << "\n";
        cout
            << "============================================================\n";
    }
    void executarAlgoritmo() {
        if (
            algoritmoSelecionado == 1
        ) {
            executarBubble();
        }
        else if (
            algoritmoSelecionado == 2
        ) {
            executarInsertion();
        }
        else if (
            algoritmoSelecionado == 3
        ) {
            executarQuick();
        }
        else {
            compararTodos();
        }
    }
    double medirBubble(
        vector<Imagem>& dadosTeste
    ) {
        auto inicio =
            chrono::high_resolution_clock::now();
        bubbleSort(
            dadosTeste,
            criterioSelecionado
        );
        auto fim =
            chrono::high_resolution_clock::now();
        return chrono::duration<
            double,
            milli
        >(
            fim - inicio
        ).count();
    }
    double medirInsertion(
        vector<Imagem>& dadosTeste
    ) {
        auto inicio =
            chrono::high_resolution_clock::now();
        insertionSort(
            dadosTeste,
            criterioSelecionado
        );
        auto fim =
            chrono::high_resolution_clock::now();
        return chrono::duration<
            double,
            milli
        >(
            fim - inicio
        ).count();
    }
    double medirQuick(
        vector<Imagem>& dadosTeste
    ) {
        auto inicio =
            chrono::high_resolution_clock::now();
        quickSort(
            dadosTeste,
            criterioSelecionado
        );
        auto fim =
            chrono::high_resolution_clock::now();
        return chrono::duration<
            double,
            milli
        >(
            fim - inicio
        ).count();
    }
    void executarBubble() {
        vector<Imagem> copia =
            dados;
        double tempo =
            medirBubble(
                copia
            );
        mostrarResultado(
            "Bubble Sort",
            tempo
        );
        mostrarDados(
            copia
        );
    }
    void executarInsertion() {
        vector<Imagem> copia =
            dados;
        double tempo =
            medirInsertion(
                copia
            );
        mostrarResultado(
            "Insertion Sort",
            tempo
        );
        mostrarDados(
            copia
        );
    }
    void executarQuick() {
        vector<Imagem> copia =
            dados;
        double tempo =
            medirQuick(
                copia
            );
        mostrarResultado(
            "Quick Sort",
            tempo
        );
        mostrarDados(
            copia
        );
    }
    void compararTodos() {
        vector<Imagem> dadosBubble =
            dados;
        vector<Imagem> dadosInsertion =
            dados;
        vector<Imagem> dadosQuick =
            dados;
        double tempoBubble =
            medirBubble(
                dadosBubble
            );
        double tempoInsertion =
            medirInsertion(
                dadosInsertion
            );
        double tempoQuick =
            medirQuick(
                dadosQuick
            );
        cout << "\n";
        cout
            << "============================================================\n";
        cout
            << "              COMPARACAO DE DESEMPENHO\n";
        cout
            << "============================================================\n\n";
        cout
            << left
            << setw(22)
            << "ALGORITMO"
            << setw(18)
            << "TEMPO (ms)"
            << "\n";
        cout
            << "---------------------------------------------\n";
        cout
            << fixed
            << setprecision(4);
        cout
            << left
            << setw(22)
            << "Bubble Sort"
            << setw(18)
            << tempoBubble
            << "\n";
        cout
            << left
            << setw(22)
            << "Insertion Sort"
            << setw(18)
            << tempoInsertion
            << "\n";
        cout
            << left
            << setw(22)
            << "Quick Sort"
            << setw(18)
            << tempoQuick
            << "\n";
        cout
            << "---------------------------------------------\n";
        string maisRapido =
            "Bubble Sort";
        double menorTempo =
            tempoBubble;
        if (
            tempoInsertion <
            menorTempo
        ) {
            menorTempo =
                tempoInsertion;
            maisRapido =
                "Insertion Sort";
        }
        if (
            tempoQuick <
            menorTempo
        ) {
            menorTempo =
                tempoQuick;
            maisRapido =
                "Quick Sort";
        }
        cout << "\n";
        cout
            << "Mais rapido: "
            << maisRapido
            << "\n";
        cout
            << "Tempo: "
            << menorTempo
            << " ms\n";
        cout << "\n";
        cout
            << "Os tres algoritmos receberam o mesmo conjunto de dados.\n";
    }
    void mostrarResultado(
        string algoritmo,
        double tempo
    ) {
        cout << "\n";
        cout
            << "============================================================\n";
        cout
            << "                       RESULTADO\n";
        cout
            << "============================================================\n";
        cout
            << "Algoritmo: "
            << algoritmo
            << "\n";
        cout
            << "Criterio:  "
            << nomeCriterio()
            << "\n";
        cout
            << "Registros: "
            << dados.size()
            << "\n";
        cout
            << fixed
            << setprecision(4);
        cout
            << "Tempo:     "
            << tempo
            << " ms\n";
        cout
            << "============================================================\n";
    }
    void mostrarDados(
        vector<Imagem>& registros
    ) {
        int quantidadeMostrar =
            min(
                10,
                static_cast<int>(
                    registros.size()
                )
            );
        cout << "\n";
        cout
            << "Primeiros "
            << quantidadeMostrar
            << " registros ordenados:\n\n";
        cout
            << left
            << setw(8)
            << "ID"
            << setw(25)
            << "NOME"
            << setw(15)
            << "TAMANHO"
            << setw(12)
            << "LARGURA"
            << setw(12)
            << "ALTURA"
            << "\n";
        cout
            << "------------------------------------------------------------------------\n";
        for (
            int i = 0;
            i < quantidadeMostrar;
            i++
        ) {
            cout
                << left
                << setw(8)
                << registros[i].getId()
                << setw(25)
                << registros[i].getNome()
                << setw(15)
                << registros[i].getTamanho()
                << setw(12)
                << registros[i].getLargura()
                << setw(12)
                << registros[i].getAltura()
                << "\n";
        }
    }
    string nomeOrigem() {
        if (
            origemSelecionada == 1
        ) {
            return "Arquivo interno";
        }
        if (
            origemSelecionada == 2
        ) {
            return "Arquivo externo";
        }
        return "Amostra aleatoria";
    }
    string nomeCriterio() {
        if (
            criterioSelecionado == 1
        ) {
            return "ID";
        }
        if (
            criterioSelecionado == 2
        ) {
            return "Nome";
        }
        if (
            criterioSelecionado == 3
        ) {
            return "Tamanho";
        }
        if (
            criterioSelecionado == 4
        ) {
            return "Largura";
        }
        return "Altura";
    }
    string nomeAlgoritmo() {
        if (
            algoritmoSelecionado == 1
        ) {
            return "Bubble Sort";
        }
        if (
            algoritmoSelecionado == 2
        ) {
            return "Insertion Sort";
        }
        if (
            algoritmoSelecionado == 3
        ) {
            return "Quick Sort";
        }
        return "Comparar todos";
    }
};
