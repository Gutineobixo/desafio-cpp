#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>

class Arquivo {
private:
    std::string nome;
    std::string conteudo;

public:
    Arquivo(const std::string& nome) : nome(nome), conteudo("") {}

    void escrever(const std::string& novoConteudo) {
        this->conteudo = novoConteudo;
    }

    void ler() const {
        std::cout << "Conteúdo do arquivo '" << nome << "': " << conteudo << std::endl;
    }

    const std::string& getNome() const {
        return nome;
    }
};

class Diretorio {
private:
    std::string nome;
    std::vector<std::shared_ptr<Arquivo>> arquivos;
    std::vector<std::shared_ptr<Diretorio>> diretorios;

public:
    Diretorio(const std::string& nome) : nome(nome) {}

    bool adicionarArquivo(const std::string& nomeArquivo) {
        if (encontrarArquivo(nomeArquivo)) {
            return false;
        }
        arquivos.push_back(std::make_shared<Arquivo>(nomeArquivo));
        return true;
    }

    bool removerArquivo(const std::string& nomeArquivo) {
        auto it = std::find_if(arquivos.begin(), arquivos.end(),
            [&nomeArquivo](const std::shared_ptr<Arquivo>& arquivo) {
                return arquivo->getNome() == nomeArquivo;
            });
        if (it != arquivos.end()) {
            arquivos.erase(it);
            return true;
        }
        return false;
    }

    bool adicionarDiretorio(const std::string& nomeDiretorio) {
        if (getDiretorio(nomeDiretorio)) {
            return false;
        }
        diretorios.push_back(std::make_shared<Diretorio>(nomeDiretorio));
        return true;
    }

    bool removerDiretorio(const std::string& nomeDiretorio) {
        auto it = std::find_if(diretorios.begin(), diretorios.end(),
            [&nomeDiretorio](const std::shared_ptr<Diretorio>& diretorio) {
                return diretorio->getNome() == nomeDiretorio && diretorio->isEmpty();
            });
        if (it != diretorios.end()) {
            diretorios.erase(it);
            return true;
        }
        return false;
    }

    std::shared_ptr<Diretorio> getDiretorio(const std::string& nomeDiretorio) {
        for (auto& diretorio : diretorios) {
            if (diretorio->getNome() == nomeDiretorio) {
                return diretorio;
            }
        }
        return nullptr;
    }

    std::shared_ptr<Arquivo> encontrarArquivo(const std::string& nomeArquivo) {
        auto it = std::find_if(arquivos.begin(), arquivos.end(),
            [&nomeArquivo](const std::shared_ptr<Arquivo>& arquivo) {
                return arquivo->getNome() == nomeArquivo;
            });
        return it != arquivos.end() ? *it : nullptr;
    }

    void escreverArquivo(const std::string& nomeArquivo, const std::string& conteudo) {
        auto arquivo = encontrarArquivo(nomeArquivo);
        if (arquivo) {
            arquivo->escrever(conteudo);
        }
        else {
            std::cout << "Erro: Arquivo não encontrado.\n";
        }
    }

    void lerArquivo(const std::string& nomeArquivo) {
        auto arquivo = encontrarArquivo(nomeArquivo);
        if (arquivo) {
            arquivo->ler();
        }
        else {
            std::cout << "Erro: Arquivo não encontrado.\n";
        }
    }

    void listarConteudo() const {
        std::cout << "Conteúdo do Diretório '" << nome << "':" << std::endl;
        for (const auto& arquivo : arquivos) {
            std::cout << "  Arquivo: " << arquivo->getNome() << std::endl;
        }
        for (const auto& diretorio : diretorios) {
            std::cout << "  Diretório: " << diretorio->getNome() << std::endl;
        }
    }

    const std::string& getNome() const {
        return nome;
    }

    bool isEmpty() const {
        return arquivos.empty() && diretorios.empty();
    }
};

int main() {
    std::shared_ptr<Diretorio> root = std::make_shared<Diretorio>("root");
    std::shared_ptr<Diretorio> currentDir = root;
    std::string linha, comando, nome, conteudo;

    std::cout << "Simulador de Sistema de Arquivos iniciado. Digite 'help' para ajuda.\n";

    while (true) {
        std::cout << currentDir->getNome() << "> ";
        std::getline(std::cin, linha);
        std::istringstream iss(linha);
        iss >> comando;

        if (comando == "create_file") {
            iss >> nome;
            if (!currentDir->adicionarArquivo(nome)) {
                std::cout << "Erro: Arquivo já existe.\n";
            }
        }
        else if (comando == "write_file") {
            iss >> nome;
            iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, conteudo);  
            currentDir->escreverArquivo(nome, conteudo);
        }
        else if (comando == "read_file") {
            iss >> nome;
            currentDir->lerArquivo(nome);
        }
        else if (comando == "delete_file") {
            iss >> nome;
            if (!currentDir->removerArquivo(nome)) {
                std::cout << "Erro: Arquivo não encontrado ou outro erro.\n";
            }
        }
        else if (comando == "create_dir") {
            iss >> nome;
            if (!currentDir->adicionarDiretorio(nome)) {
                std::cout << "Erro: Diretório já existe.\n";
            }
        }
        else if (comando == "delete_dir") {
            iss >> nome;
            if (!currentDir->removerDiretorio(nome)) {
                std::cout << "Erro: Diretório não encontrado ou não está vazio.\n";
            }
        }
        else if (comando == "change_dir") {
            iss >> nome;
            if (nome == "..") {
                
                if (currentDir->getNome() != "root") {
                    currentDir = root; 
                }
            }
            else {
                auto dir = currentDir->getDiretorio(nome);
                if (dir) {
                    currentDir = dir;
                }
                else {
                    std::cout << "Erro: Diretório não encontrado.\n";
                }
            }
        }
        else if (comando == "list_dir") {
            currentDir->listarConteudo();
        }
        else if (comando == "help") {
            std::cout << "Comandos disponíveis:\n";
            std::cout << "  create_file <nome>, write_file <nome> <conteudo>, read_file <nome>, delete_file <nome>\n";
            std::cout << "  create_dir <nome>, delete_dir <nome>, change_dir <nome>, list_dir\n";
            std::cout << "  exit\n";
        }
        else if (comando == "exit") {
            break;
        }
        else {
            std::cout << "Comando desconhecido: '" << comando << "'. Digite 'help' para ajuda.\n";
        }
    }

    std::cout << "Simulador de Sistema de Arquivos finalizado.\n";
    return 0;
}
