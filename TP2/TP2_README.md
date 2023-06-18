# Experimento 1:


1 - Existem dois utilitários de rede muito populares, desenvolvidos originalmente no ambiente Unix, mas hoje também disponíveis nos outros sistemas operacionais, que servem para determinar se um endereço IP específico está ativo na rede, o valor aproximado do RTT (round-trip time) até o mesmo e a rota para alcançá-lo: o ping e o traceroute. 

a) Pesquisem e respondam. Qual é a diferença entre o uso do ping e do  traceroute? Como o ping é implementado (que mecanismos e protocolos da família TCP/IP ele usa para funcionar)? Como o traceroute é implementado (que mecanismos e protocolos da família TCP/IP ele usa para funcionar)? Forneçam  respostas detalhadas e citem suas fontes bibliográficas. (A qualidade destas respostas e das fontes consultadas impactará fortemente a nota desta questão.) 
    
b) Usando o traceroute, com a opção de uso de apenas endereços IPv4, levantem o RTT e a rota na Internet para cada um dos quatro destinos abaixo. Para isso, para cada um dos destinos, façam em um mesmo dia “medições” em três períodos  diferentes: 6-12 h; 12-18 h; 18-24 h. Em cada um dos períodos façam 10 “medições” de rota e RTT, sendo que a média dos 10 valores medidos de RTT representará o valor do RTT daquele período. Para cada destino, apresentem em tabelas todos os valores de RTT obtidos e as médias respectivas, plotem os resultados de RTT médio por período do dia em um gráfico tipo histograma e listem as rotas obtidas em cada período, destacando possíveis variações nas mesmas.
DESTINO 1: www.ufrj.br
DESTINO 2: www.ucsc.edu
DESTINO 3: www.phil.cam.ac.uk
DESTINO 4: www.adelaide.edu.au

c) Baseado nas “medições” feitas, respondam: houve variação do valor do RTT durante o dia? Expliquem em detalhes o que ocorreu e busquem justificativas para o comportamento observado. 


# Experimento 2:

2 - Façam o Exercício 48 do Capítulo 5 do livro-texto, letras (a) e (b),  apenas para o protocolo UDP. Para os itens (a) e (b) do exercício, cada teste consiste em repetir 100.000 vezes a sequência: enviar uma mensagem de tamanho determinado do Host A para o Host B e refletir (retornar) a mensagem de volta para o Host A. A latência será o tempo total decorrido entre o início e o fim do teste, dividido por 100.000. A vazão (throughput) será o tamanho da mensagem (em bits) dividido pela latência (em segundos). Cada teste deverá ser repetido três vezes, sendo que a
média aritmética destas três execuções é que será o valor final a ser considerado. Diferentemente do que pede o livro, apresentem em tabelas os resultados do experimento e também façam os gráficos tanto para latência quanto para vazão. Discutam os resultados obtidos e busquem justificativas para os comportamentos observados.