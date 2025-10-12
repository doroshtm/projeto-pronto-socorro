Projeto: Sistema de Pronto Socorro

Autores:
//Arthur de Castro Dias
//Gabriel Carraro Salzedas
//Kaua Benjamin Trombim Silva

Descrição:
Este projeto implementa um sistema simples de gerenciamento de pacientes para um pronto-socorro. É composto por três TADs principais e um programa principal (`main.c`) que fornece um menu interativo para registrar pacientes, inserir na fila de triagem, adicionar/remover procedimentos do histórico, chamar pacientes para atendimento, e salvar/carregar os dados de persistência em arquivos JSON simples.

Estrutura do projeto:
- `main.c`: interface de usuário em linha de comando e fluxo principal do programa.
- `lista_paciente.c` / `lista_paciente.h`: TAD `lista_paciente` — implementação de uma lista encadeada (lista de pacientes cadastradados). Responsável por armazenar, buscar, listar e apagar pacientes.
- `triagem.c` / `triagem.h`: TAD `triagem` — implementação de uma fila (FIFO) que representa a fila de espera da triagem. A ordem de atendimento é por ordem de aparição.
- `historico.c` / `historico.h`: TAD `historico` — implementação de uma pilha (LIFO) para armazenar procedimentos realizados em cada paciente (LIFO), conforme especificação do projeto.
- `paciente.c` / `paciente.h`: definição do tipo `PACIENTE` e funções auxiliares (criar, apagar, getters).
- `makefile`: alvo para compilar o projeto (pode exigir `make` no Windows; veja instruções abaixo).

TADs e estruturas:
- `lista_paciente` é um TAD de lista encadeada. Cada nó armazena um ponteiro para um `PACIENTE`.
- `triagem` é um TAD de fila (FIFO). A fila armazena ponteiros para `PACIENTE` e atende na ordem de chegada.
- `historico` é implementado como uma pilha (LIFO), conforme exigido pela especificação — procedimentos são empilhados quando adicionados e desempilhados quando desfeitos.

Como compilar e executar (Windows PowerShell):
1. Se você tem `make` instalado, na pasta do projeto execute:

```powershell
make
```

2. Se `make` não estiver disponível (Windows padrão), compile manualmente com `gcc`:

```powershell
gcc -c historico.c -o historico.o -std=c99 -Wall
gcc -c lista_paciente.c -o lista_paciente.o -std=c99 -Wall
gcc -c paciente.c -o paciente.o -std=c99 -Wall
gcc -c triagem.c -o triagem.o -std=c99 -Wall
gcc -c main.c -o main.o -std=c99 -Wall
gcc historico.o lista_paciente.o paciente.o triagem.o main.o -o main -std=c99 -Wall
```

3. Execute o programa:

```powershell
.\main.exe
```

Dados persistentes:
- A lista de pacientes é salva em `lista.json`.
- A fila de triagem é salva em `fila.json`.

Observações e limitações:
- `historico` aceita até 10 procedimentos por paciente.
- IDs de pacientes são gerados sequencialmente pela função `lista_paciente_gerar_id_unico`, de modo que um id já existente mas apagado não será repetido (possível overflow de int a depender da quantidade de pacientes cadastrados).