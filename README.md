# TP 1 - Redes TCP IP
### Etapa inicial de preparação   
Após estudar os textos de referência sobre programação em
rede usando soquetes, digitem, compilem e executem os programas cliente e servidor do
exemplo simplex-talk da seção 1.4 do Capítulo 1 do livro-texto.    
Fiquem atentos às observações
detalhadas no arquivo *“simplex-talk COMENTARIOS”*, disponível no espaço da disciplina no
Moodle.
    Resolvam todos os possíveis problemas, de modo que os programas funcionem e
“conversem” um com o outro. Nenhum relatório deverá ser gerado sobre esta etapa inicial.   
##### Experimento 1- Façam o Exercício 33 do Capítulo 1 do livro-texto.     
##### Experimento 2- Façam o Exercício 34 do Capítulo 1 do livro-texto.    
##### Experimento 3- Façam o Exercício 35 do Capítulo 1 do livro-texto.    

O repositório está organizado de forma que exista arquivos client.c e server.c de base, e que
as respostas pra cada um dos exercicios fiquem em sua respectiva pasta. 

Para rodar os códigos do repositório, usar os seguintes comandos:

    gcc file_name.c -o file_name && ./file_name

### Exemplos:

    gcc client_base.c -o client_base && ./client_base
    gcc server_base.c -o server_base && ./server_base