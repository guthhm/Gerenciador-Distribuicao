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