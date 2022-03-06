### Funcionamento da fila implementada:
 - Conceito geral: Primeiro que entra é o primeiro que sai.
 - A fila possui dois ponteiros: um aponta para o início da fila e o outro aponta para o fim da fila.
 - Sempre que inserir um elemento, o ponteiro do fim da fila e os anteriores/posteriores serão mudados (Inclusive o anterior do início da fila).
 - Não pode remover de uma fila que está vazia
 - Se a fila tiver apenas um elemento, os ponteiros de início e fim apontam para o mesmo local.
 - Se a fila tiver apenas um elemento e ele for removido, os ponteiros de início e fim apontarão para NULL.
