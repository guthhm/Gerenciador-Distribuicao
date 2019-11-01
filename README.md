# Gerenciador de Distribuição
Este projeto está sendo desenvolvido como forma de avaliação da disciplina de Programação do curso de Engenharia Eletrotécnica e de Computadores do Instituto Superior Técnico da Universidade de Lisboa. 
Todo o projeto será desenvolvido em linguagem C, com foco no cumprimento dos pontos estabelecidos pelo docente e na otimização da execução do código e organização do mesmo.

## Objetivo do programa
O programa consiste em um visualizador e validador de distribuição dos funcionários e aeronaves de uma empresa fictícia, seguindo algumas regras operacionais - esclarecidas no próximo tópico - da mesma. O software deve exibir, em formato de matriz a distribuição indicada em um arquivo de texto (.txt), verificar se atende às regras operacionais e indicar se existem erros e onde se encontram.

## Regras Operacionais

<dl>
    <dt><strong>1. O número total de funcionários deve ser igual ao número total de aeronaves existentes no
    quadro.</strong></dt>
    <dt><strong>2. Cada aeronave deve ter um funcionário atribuído </strong></dt>
        <dd> i. e. cada funcionário deve estar adjacente à
        aeronave vertical ou horizontalmente, porém nunca em diagonal. No entanto um
        funcionário pode estar adjacente a outras aeronaves.
    </dd>
    <dt><strong>3. Os funcionários não podem estar em posições adjacentes entre si.</strong></dt>
</dl>

## Arquivos de texto com distribuição
O primeiro arquivo a ser acessado pelo programa é o arquivo `distribuicao.txt`, o qual indica os nomes com os arquivos que contém as distribuições a serem visualizadas.<br>

A estrutura interna deste arquivo é a seguinte:
```
dist1.txt
dist2.txt
dist3.txt
...
distribui.txt
```
Cada um dos arquivos incluídos contém uma distribuição distinta que tem formatação que indica em cada linha as coordenadas `X Y` (linha e coluna da matriz) e se há neste ponto um funcionário `*` ou aeronave `V`, portanto a estrutura interna do arquivo é a seguinte:
```
0 2 *
0 3 V
0 4 *
0 7 V
1 2 V
1 7 *
2 4 *
3 0 *
```

## Arquivo contendo os resultados

De acordo com a exigência do projeto, o programa produz ao final um arquivo no formato `.txt` com o nome `resultados.txt`. Este contém informações relevantes sobre a execução do software e validação das distribuições indicadas.

Para que seja de fácil visualização do utilizador, o arquivo gerado automaticamente possui clara estrutura e diagramação como apontado a seguir.

```
ID da sessão | Arquivo utilizado | Status de encerramento | Nº de funcionários | Nº de aeronaves

```
> Onde: <br> ID da sessão = Nº único e aleatório de identificação; <br> Arquivo utilizado = Path do arquivo de distribuição aberto; <br> Status de encerramento = Indica 'ERRO' ou 'OK' <br> Nº de funcionários e Nº de Aeronaves = Quantidades dos respectivos ocupantes indicados no arquivo de distribuição.

De acordo com a execução e validação realizadas, podem haver 2 cenários, um no qual não hajam quaisquer erros e o programa adiciona somente a linha representada acima com o respectivo código de status, ou outro no qual exista um erro que será indicado da seguinte forma:

```
ID da sessão | Arquivo utilizado | Status de encerramento | Nº de funcionários | Nº de aeronaves
Status: Nº de Status | Descrição | Ocupante (X | Y) - Ocupante (X | Y)
```
> Nota: As barras verticais ('|') não aparecem no arquivo e tem somente função ilustrativa nestes exemplos.

Sendo assim, estarão abrangidos os pontos iniciais de possíveis falhas e, com o sistema de codificação de estado utilizado, existe a possibilidade de aumentar a abrangência posteriormente. Este será tratado com maior clareza no próximo tópico.

## Códigos de Status

Afim de facilitar a compreensão do usuário do status com o qual o programa completou sua tarefa e também tornar mais claro os processos que desencadearam os mesmos, é utilizado uma tabela - inspirada pelo HTTP Response Status Code - com códigos de 3 dígitos relativos ao estado atual ou final do programa. 

Ao final de cada sessão, o software adiciona ao final do arquivo `resultados.txt` um código de acordo com o estado que completou o que lhe é designado. Cada código possui um significado próprio assim como cada dígito.

Portanto, temos a seguinte estrutura (onde 'A', 'B' e 'C' são números n∈N):

A | B | C
|-|-|-|
|Refere-se à ocorrência ou não de falhas e em qual ponto. <br> 1 - OK; <br> 2 - Referente ao arquivo raíz de distribuições; <br> 3 - Referente ao arquivo de distribuição;|Refere-se principal objeto onde houve o erro. <br>0 - Referente à estrutura do arquivo; <br>1 - Referente aos valores apontados; <br> 2 - Relativo às regras operacionais;| Refere-se ao tipo de estado encotrado neste ponto. <br> Cada valor possui significado próprio de acordo com o objeto e local ao qual o status se refere.|

Os códigos e suas descrições estão dispostos a seguir:


### 100 - Sucesso

----

### 201 - Erro ao abrir o arquivo raíz de distribuições (distribuicao.txt)

### 211 - Formato de um dos arquivos indicado por distribuicao.txt é inválido <br>212 - Caracteres contidos em um dos arquivos indicados por distribuicao.txt são inválidos

----

### 301 - Erro ao abrir o arquivo de distribuição <br>302 - Coordenada 'X' inválida <br>303 - Coordenada 'Y' inválida<br> 304 - Ocupante da posição inválido

### 311 - Funcionário sem aeronave <br>312 - Aeronave sem funcionário <br>313 - Funcionário adjacente a outro

### 321 - Há mais funcionários que aeronaves 