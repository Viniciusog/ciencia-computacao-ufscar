### Fila encadeada com prioridade

##### Ideia
- Em uma fila de atendimento, quem tem a maior idade é atendido primeiro. 
- Se duas pessoas tem a mesma idade, o primeiro a chegar será o primeiro a ser atendido.

##### Algoritmo
- O algoritmo é basicamente um fila encadeada circular que ordena os elementos quando são adicionados.
- O início da fila terá os elementos com maiores valores.
- O "próximo" do último nó é o 1º nó (fila circular).
- Não pode remover elemento da fila caso a fila esteja vazia.