# Crud - Almoxarifado!

Projeto proposto pelo professor Derzu Omaia na disciplina de Linguagem de Programação I - Período: 2023.1

> O tema do projeto é Almoxarifado, um CRUD onde as entradas ficaram salvas em um arquivo de texto e toda vez que o usuário fazer uma busca, será possível acessar entradas passadas.

<br/>

# Requisitos do projeto:

1. Ser feito em C++

2. O Menu deve possuir no mínimo essas opções:

	2.1 Inserir

	2.2 Listar todos

	2.3 Exibir um (pesquisar por nome ou por índice)

	2.4 Alterar (pesquisar por nome ou por índice)

	2.5 Remover (pesquisar por nome ou por índice)

	2.6 Exibir Relatório

	2.7 Sair

3.Fazer modelagem das classes que serão utilizadas no sistema utilizando diagrama UML de classe.

4.O objeto principal deve ter pelo menos 4 atributos, entre eles um que seja do tipo de outra classe criada pela equipe (composição). Ex.: Endereço, Data, etc.

5.Utilize pelo menos herança com pelo menos 1 superclasse e 2 subclasses (requisito faltante)

6.Sobrescreva o algum método da superclasse.

7.Utilize uma classe que vai gerenciar as operações CRUD. Não faça na main();  

8.Utilize bastante métodos.

9.Gerar relatório com um resumo das informações. Ex: Relatório de vendas, relatório de estoque, relatório de clientes. No relatório devem ser exibidas informações como, quantidade de elementos cadastrados, valor total, entre outros.

10.O programa deve rodar indefinidamente, até que o usuário escolha sair

11.Todos os dados armazenados no programa devem ser salvos em arquivo, para que ao sair do programa os dados não se percam. E ao abrir o programa novamente os dados salvos devem ser carregados.
Carregar o arquivo automaticamente ao entrar na aplicação. Salvar em arquivo ao finalizar o programa. Todas as operações de inserção, exibição, edição e remoção deve ser realizada no vetor de objetos, e não diretamente no arquivo.  

12. Entrega dia: 25 e 26/09/2023

<br/>

# Diagrama UML

  ![Imagem](https://github.com/GabriellyMarques02/CRUD_LP1_ALMOXARIFADO/blob/main/cruddiagrama.drawio.png)

	Relações:
	A classe Gerenciador possui um objeto Estoque para realizar operações de gerenciamento de estoque.
	A classe Estoque possui uma composição de objetos Produto (vector<Produto>) para armazenar os produtos em estoque.

<br/>
<br/>

## Referências: 

  	+ Documentação oferecida pelo professor

	https://creately.com/blog/pt/diagrama/tutorial-diagrama-de-classes/

	https://www.delftstack.com/pt/howto/cpp/read-csv-file-in-cpp/

	https://augustoprogrammer.files.wordpress.com/2015/03/farmacia_classdiagram.jpg

	https://www.devmedia.com.br/trabalhando-com-os-diagramas-da-uml-parte-2/33224

	https://stackedit.io/app#

	https://pt.stackoverflow.com/editing-help