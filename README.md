# RACIOCÍNIO BASEADO EM CASOS - RBC

Programa implementado em C para classificar novas instâncias. O algoritmo funciona com qualquer entrada que tenha como requisito 4 atributos e 1 classe.

### FUNCIONAMENTO DO ALGORITMO 
O arquivo de entrada iris.data possui, por instância, 3 atributos e a classe do objeto, respectivamente.
Na sua totalidade, o arquivo iris.data possui 150 instâncias que serão analisadas.


Das 150 instâncias, 5 são selecionadas aleatoriamente para amostras.


A partir da distância euclidiana, é possível identificar quais instâncias são parecidas com outras.
O algoritmo possui tratamento de ruído. O objetivo é excluir instâncias muito parecidas da avaliação.


Novas instâncias são classificadas e inseridas em suas classes equivalentes.

### COMO COMPILAR E EXECUTAR
Basta executar o arquivo "executa.sh"

>> ./executa.sh

### REQUISITOS
math.h

entrada de dados: 4 atributos e 1 classe.