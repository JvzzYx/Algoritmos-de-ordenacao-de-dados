#include <string>

class Imagem {
private:
    int id;
    std::string nome;
    double tamanho;
    int largura;
    int altura;
public:
    Imagem()
        : id(0),
        nome(""),
        tamanho(0.0),
        largura(0),
        altura(0){
    }
    Imagem(
        int id,
        std::string nome,
        double tamanho,
        int largura,
        int altura
    )
        : id(id),
          nome(nome),
          tamanho(tamanho),
          largura(largura),
          altura(altura) {
    }
    int getId() const {
        return id;
    }
    std::string getNome() const {
        return nome;
    }
    double getTamanho() const {
        return tamanho;
    }
    int getLargura() const {
        return largura;
    }
    int getAltura() const {
        return altura;
    }
};