# DESAFIO DE C++

**Objetivo:** 
Criar um simulador de sistema de arquivos básico, executável via terminal, que permita ao usuário criar, deletar, escrever, e ler arquivos, além de criar e remover diretórios dentro de um ambiente simulado (sem interagir com o sistema de arquivos real do sistema operacional).

**Descrição:**
Este desafio envolve conceitos avançados de programação em C++, como gestão de memória, estruturas de dados, manipulação de strings e interação com o usuário via linha de comando. O simulador deve operar inteiramente na memória, usando estruturas de dados para representar arquivos e diretórios.

**Requisitos Funcionais:**
**Estrutura de Dados:**
- Implementar classes para Arquivo e Diretorio. Cada diretório pode conter múltiplos arquivos e subdiretórios.
- A classe Diretorio deve ser capaz de adicionar e remover arquivos e subdiretórios.

**Operações de Arquivos:**
- Criar um novo arquivo.
- Escrever dados em um arquivo. Os dados são fornecidos pelo usuário.
- Ler dados de um arquivo e exibi-los no terminal.
- Deletar um arquivo.

**Operações de Diretórios:**
- Criar um novo diretório.
- Remover um diretório (somente se estiver vazio para simplificar).
- Listar o conteúdo de um diretório (arquivos e subdiretórios).

**Navegação:**
- Permitir ao usuário navegar entre os diretórios (mudar o diretório atual).

**Interface de Usuário:**
- Usar o terminal para aceitar comandos do usuário que permitam realizar todas as operações listadas acima.
- Exibir mensagens apropriadas para sucesso ou erros nas operações (por exemplo, tentar deletar um diretório não vazio).

**Desafios Técnicos:**
- Gestão de Memória: Garantir que não há vazamentos de memória com a criação e destruição dinâmica de objetos.
- Robustez: O sistema deve ser capaz de lidar com entradas inválidas e erros sem falhar.
- Design de Software: Utilizar princípios de design como encapsulamento e separação de responsabilidades para manter o código organizado e modular.

### Exemplo de Comandos do Usuário:
```
create_file nome_do_arquivo.txt
write_file nome_do_arquivo.txt "conteúdo do arquivo"
read_file nome_do_arquivo.txt
delete_file nome_do_arquivo.txt
create_dir nome_do_diretorio
remove_dir nome_do_diretorio
change_dir nome_do_diretorio
list_dir
exit
```
### Critérios de Avaliação:
- Funcionalidade: O código deve compilar sem erros e executar todas as operações conforme especificado.
- Clareza e Legibilidade do Código: Uso adequado de comentários, nomes de variáveis claros e estrutura lógica do código.
- Adesão ao Design Orientado a Objetos: Uso efetivo de classes e objetos.
