# Jantar dos Filósofos com Mutexes - Concorrência e Sincronização 🍝

## Índice

* [1. Prefácio](#1-prefácio)
* [2. Resumo do Projeto](#2-resumo-do-projeto)
* [3. Recursos Principais](#3-recursos-principais)
* [4. Guia Prático de Instalação e Uso](#4-guia-prático-de-instalação-e-uso)
* [5. Critérios Mínimos de Aceitação](#5-critérios-mínimos-de-aceitação)
* [6. Estratégia de Sincronização](#6-estratégia-de-sincronização)
* [7. Especificações Técnicas](#7-especificações-técnicas)
* [8. Implementações Futuras](#8-implementações-futuras)
* [9. Integrantes](#9-integrantes)

---

## 1. Prefácio

Este projeto foi desenvolvido como parte da atividade prática da disciplina de **Concorrência e Sincronização**, ministrada pela professora **Artemísia Kimberlly**.

A atividade tem como objetivo consolidar conceitos fundamentais relacionados à execução concorrente de processos e threads, especialmente **Seção Crítica, Condição de Corrida, Deadlock e Inanição (Starvation)**.

Para isso, foram estudados e aplicados diferentes mecanismos de sincronização, como **Semáforos, Mutexes e Monitores**.

O grupo ficou responsável pela implementação do problema clássico do **Jantar dos Filósofos**, utilizando **Mutexes em linguagem C** e a biblioteca **POSIX Threads (pthreads)**.

O projeto busca demonstrar, por meio de uma simulação concorrente, como diferentes threads podem disputar recursos compartilhados e como mecanismos de exclusão mútua podem ser utilizados para controlar esse acesso.

## 2. Resumo do Projeto

O projeto consiste na implementação do problema clássico do **Jantar dos Filósofos**, proposto para representar situações de concorrência em que vários processos ou threads disputam recursos compartilhados.

Na simulação, existem cinco filósofos sentados ao redor de uma mesa. Cada filósofo alterna entre os estados de:

* Pensar;
* Tentar pegar os garfos;
* Comer;
* Liberar os garfos.

Cada filósofo precisa de **dois garfos** para comer: o garfo localizado à sua esquerda e o garfo localizado à sua direita.

Como os garfos são recursos compartilhados entre as threads, é necessário utilizar um mecanismo de sincronização para evitar que dois filósofos utilizem o mesmo garfo simultaneamente.

Neste projeto, cada garfo é representado por um **Mutex (`pthread_mutex_t`)**.

### Principais Características

* **Execução concorrente:** cada filósofo é executado como uma thread independente.
* **Uso de Mutexes:** cada garfo possui um Mutex responsável por controlar seu acesso.
* **Simulação de tempo real:** são utilizados atrasos com `sleep()` e/ou `usleep()` para simular os períodos de pensamento e alimentação.
* **Console descritivo:** o programa apresenta no terminal as ações realizadas pelos filósofos.
* **Múltiplas interações:** os filósofos executam várias rodadas para permitir a observação do comportamento concorrente.
* **Controle de recursos compartilhados:** os garfos são acessados de maneira sincronizada pelas threads.

## 3. Recursos Principais

### Simulação dos Filósofos

Cada filósofo possui uma thread própria e realiza repetidamente as seguintes ações:

1. Pensa por determinado período;
2. Tenta obter o garfo esquerdo;
3. Tenta obter o garfo direito;
4. Come durante determinado período;
5. Libera os dois garfos;
6. Volta ao estado de pensamento.

### Sincronização com Mutexes

Cada garfo da mesa é associado a um Mutex.

Quando um filósofo precisa utilizar um garfo, ele realiza o bloqueio do Mutex correspondente. Enquanto o garfo estiver sendo utilizado, outro filósofo não poderá acessá-lo.

Após terminar de comer, o filósofo libera os Mutexes dos dois garfos.

### Simulação de Tempo

Para permitir que o escalonador do sistema operacional realize trocas de contexto entre as threads, são utilizados atrasos durante a execução.

Exemplo:

```c
sleep(1);
```

ou:

```c
usleep(500000);
```

Esses atrasos simulam o tempo necessário para que um filósofo pense ou coma e tornam a concorrência mais perceptível durante a execução.

### Console/Log

O programa apresenta mensagens descritivas no terminal para facilitar a visualização do comportamento das threads.

Exemplos:

```text
[+] Filósofo 1 está pensando...
[!] Filósofo 1 tentando pegar o garfo esquerdo...
[!] Filósofo 1 tentando pegar o garfo direito...
[+] Filósofo 1 conseguiu os dois garfos.
[+] Filósofo 1 está comendo...
[-] Filósofo 1 terminou de comer e liberou os garfos.
```

Dessa maneira, é possível acompanhar a disputa pelos recursos durante a execução.

## 4. Guia Prático de Instalação e Uso

### 4.1 Instalação no Windows

Para executar o projeto no Windows, é necessário instalar um compilador C compatível com a biblioteca pthreads.

Neste projeto será utilizado o **MinGW**.

### 4.1.1 Baixar o MinGW

Faça o download do MinGW pelo seguinte endereço:

https://sourceforge.net/projects/mingw/

Após realizar o download, instale o MinGW.

Durante a instalação, na seção **Basic Setup**, selecione todos os pacotes disponíveis.

Na seção **All Packages**, selecione os seguintes pacotes relacionados ao pthreads:

* `mingw32-libpthread-old`
* `mingw32-libpthreadgc`
* `mingw32-libpthreadce`
* `mingw32-pthreads-w32`

Para os pacotes que apresentarem mais de uma opção, selecione as opções disponíveis conforme indicado na instalação.

Depois:

1. Acesse o menu **Installation**;
2. Selecione **Apply Changes**;
3. Aguarde a conclusão da instalação.

### 4.1.2 Configurar as Variáveis de Ambiente

Após instalar o MinGW, é necessário adicionar o diretório `bin` às variáveis de ambiente do Windows.

No menu de pesquisa do Windows, procure por:

```text
Editar as variáveis de ambiente do sistema
```

Em seguida:

1. Abra **Variáveis de Ambiente**;
2. Na seção **Variáveis do sistema**, procure por `Path`;
3. Selecione `Path`;
4. Clique em **Editar**;
5. Clique em **Procurar**;
6. Navegue até:

```text
Este Computador
→ Disco Local (C:)
→ MinGW
→ bin
```

7. Selecione a pasta `bin`;
8. Clique em **OK** em todas as janelas abertas.

### 4.1.3 Configurar o Visual Studio Code

Abra o **Visual Studio Code** e instale a extensão:

```text
C/C++ DevTools
```

Após instalar a extensão, reinicie o Visual Studio Code.

Em seguida, pressione:

```text
Ctrl + Shift + P
```

Pesquise por:

```text
C/C++: Edit Configurations (UI)
```

Na configuração aberta, altere:

```text
IntelliSense mode
```

para:

```text
Default
```

Após essas configurações, o ambiente estará preparado para compilar e executar o projeto.

### 4.2 Compilação e Execução no Windows

Abra o arquivo `.c` do projeto no Visual Studio Code.

Abra o terminal integrado do VS Code e navegue até a pasta onde está localizado o arquivo.

Para compilar, utilize:

```bash
gcc seu_arquivo.c -pthread
```

Por exemplo:

```bash
gcc jantar_filosofos.c -pthread
```

Após a compilação, será gerado o executável `a.exe`.

Para executar:

```bash
./a.exe
```

### 4.3 Instalação e Execução no Linux

Em sistemas Linux, o compilador GCC normalmente pode ser instalado por meio do gerenciador de pacotes da distribuição.

Com o projeto aberto, acesse o terminal e navegue até a pasta onde está localizado o arquivo `.c`.

Compile utilizando:

```bash
gcc seu_arquivo.c
```

Por exemplo:

```bash
gcc jantar_filosofos.c
```

Depois da compilação, execute o programa com:

```bash
./a.out
```

Caso seja necessário especificar explicitamente a biblioteca pthread, também pode ser utilizado:

```bash
gcc jantar_filosofos.c -pthread
```

## 5. Critérios Mínimos de Aceitação

A implementação deve atender aos requisitos estabelecidos para a atividade prática.

### 5.1 Simulação de Tempo Real

O programa deve utilizar funções de atraso, como:

```c
sleep()
```

ou:

```c
usleep()
```

Os atrasos devem aparecer dentro e fora das regiões críticas quando necessário, simulando o tempo de processamento e permitindo que o escalonador do sistema operacional realize trocas de contexto entre as threads.

### 5.2 Console/Log Descritivo

O terminal deve apresentar de forma clara o estado dos filósofos e suas ações.

Exemplos:

```text
[+] Filósofo 2 está pensando.
[!] Filósofo 2 tentando pegar o garfo esquerdo.
[!] Filósofo 2 tentando pegar o garfo direito.
[+] Filósofo 2 conseguiu os dois garfos.
[+] Filósofo 2 está comendo.
[-] Filósofo 2 liberou os garfos.
```

Essas mensagens permitem acompanhar o comportamento das threads e identificar a disputa pelos recursos.

### 5.3 Linguagem e Biblioteca

O projeto deve ser desenvolvido utilizando:

* Linguagem C;
* Biblioteca POSIX Threads (`pthread`);
* `pthread_mutex_t` para implementação dos Mutexes.

A sincronização deve ser realizada por meio dos recursos de Mutex disponibilizados pela biblioteca pthreads.

### 5.4 Tratamento do Fim da Execução

O programa não precisa executar indefinidamente.

Entretanto, os filósofos devem realizar uma quantidade suficiente de interações para permitir a análise do comportamento concorrente.

Como referência, podem ser utilizadas:

```text
50 interações por filósofo
```

Ao final das interações, as threads devem ser encerradas corretamente e os recursos utilizados devem ser liberados.

## 6. Estratégia de Sincronização

A estratégia utilizada neste projeto é baseada na associação de um **Mutex para cada garfo**.

Considerando cinco filósofos, existem cinco garfos:

```text
Garfo 0
Garfo 1
Garfo 2
Garfo 3
Garfo 4
```

Cada garfo possui um Mutex:

```c
pthread_mutex_t garfos[5];
```

Cada filósofo possui dois garfos associados a ele:

* Garfo esquerdo;
* Garfo direito.

Antes de comer, o filósofo precisa adquirir os dois Mutexes correspondentes aos seus garfos.

De maneira simplificada:

```text
Filósofo
   │
   ├── Garfo esquerdo → Mutex
   │
   └── Garfo direito  → Mutex
```

Quando o filósofo consegue adquirir os dois Mutexes, ele entra na região crítica e pode realizar a ação de comer.

Após terminar, os dois Mutexes são liberados.

### 6.1 Região Crítica

A região crítica corresponde ao momento em que o filósofo possui os dois garfos e está utilizando os recursos compartilhados para comer.

O acesso aos garfos é protegido pelos Mutexes para impedir que dois filósofos utilizem simultaneamente o mesmo garfo.

### 6.2 Condição de Corrida

Sem sincronização, dois filósofos poderiam tentar acessar o mesmo garfo ao mesmo tempo.

O uso de Mutexes impede esse acesso simultâneo, garantindo exclusão mútua sobre cada recurso.

### 6.3 Deadlock

O problema clássico do Jantar dos Filósofos pode apresentar uma situação de deadlock quando todos os filósofos seguram um garfo e ficam esperando indefinidamente pelo segundo.

A implementação deve utilizar uma estratégia que evite essa situação.

Uma abordagem possível consiste em estabelecer uma **ordem de aquisição dos Mutexes**, fazendo com que os filósofos adquiram os recursos sempre seguindo uma ordem determinada.

Por exemplo:

```text
Primeiro: garfo de menor índice
Segundo: garfo de maior índice
```

Dessa forma, reduz-se a possibilidade de formação de uma espera circular.

### 6.4 Inanição (Starvation)

A execução também deve permitir observar se algum filósofo fica indefinidamente impedido de comer.

A quantidade de interações e a simulação de tempo permitem verificar o comportamento das threads durante diferentes disputas pelos recursos.

O objetivo é garantir que os filósofos tenham oportunidade de executar suas ações durante a simulação.

## 7. Especificações Técnicas

O projeto utiliza as seguintes tecnologias e conceitos:

* **Linguagem:** C
* **Biblioteca de threads:** POSIX Threads (`pthread`)
* **Sincronização:** Mutex (`pthread_mutex_t`)
* **Compilador:** GCC
* **Ambiente Windows:** MinGW
* **Ambiente de desenvolvimento:** Visual Studio Code
* **Sistema operacional:** Windows e Linux
* **Conceitos aplicados:**

  * Threads;
  * Concorrência;
  * Seção crítica;
  * Condição de corrida;
  * Exclusão mútua;
  * Deadlock;
  * Starvation;
  * Escalonamento;
  * Troca de contexto.

### Principais funções utilizadas

A implementação utiliza funções da biblioteca pthread, como:

```c
pthread_create()
```

para criação das threads;

```c
pthread_join()
```

para aguardar a finalização das threads;

```c
pthread_mutex_init()
```

para inicialização dos Mutexes;

```c
pthread_mutex_lock()
```

para bloquear um recurso;

```c
pthread_mutex_unlock()
```

para liberar um recurso;

```c
pthread_mutex_destroy()
```

para destruir os Mutexes ao final da execução.

Também são utilizadas funções de atraso, como:

```c
sleep()
```

e/ou:

```c
usleep()
```

para simular o tempo de processamento.

## 8. Implementações Futuras

Como possíveis melhorias para o projeto, podem ser implementadas:

### Monitoramento das Estatísticas

Adicionar informações sobre:

* Quantas vezes cada filósofo comeu;
* Quanto tempo cada filósofo permaneceu esperando;
* Quantas vezes cada filósofo tentou obter um garfo;
* Tempo médio de espera.

### Comparação entre Mecanismos

Implementar versões alternativas do mesmo problema utilizando:

* Semáforos;
* Monitores;
* Outras estratégias de prevenção de deadlock.

Dessa forma, seria possível comparar o comportamento dos diferentes mecanismos de sincronização.

### Interface de Visualização

Uma possível evolução seria desenvolver uma representação visual da mesa, mostrando:

* Filósofos;
* Garfos;
* Estado de cada filósofo;
* Recursos ocupados;
* Recursos disponíveis.

### Configuração da Simulação

Permitir que o usuário escolha:

* Número de filósofos;
* Quantidade de interações;
* Tempo de pensamento;
* Tempo de alimentação;
* Estratégia de aquisição dos garfos.

## 9. Integrantes

**Professora:** Artemísia Kimberlly

**Atividade:** Projeto Prático de Concorrência e Sincronização

**Tema:** Jantar dos Filósofos com Mutexes em C

### Integrantes do Grupo

* **[Nome do integrante 1]**
* **[Nome do integrante 2]**
* **[Nome do integrante 3]**
* **[Nome do integrante 4]**

---