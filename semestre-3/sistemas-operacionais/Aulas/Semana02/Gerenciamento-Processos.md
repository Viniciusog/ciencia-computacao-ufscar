# Gerenciamento de processos
## Professor: Hélio Crestana Guardia
## Universidade Federal de São Carlos
---

## Gerenciamento de processos

A execução de programas pode gerar a criação de um ou mais processos (e threads). Assim, o termo processo é geralmente usado para indicar um programa em execução. Processos são uma das principais abstrações oferecidas pelos sistemas operacionais para a execução de programas. 

Usando uma interface gráfica do sistema operacional, em geral o usuário não está preocupado com a criação de processos, mas com a ativação de programas. Essa ativação pode ser realizada através de ícones associados a aplicações específicas, bem como utilizando menus e atalhos pré-definidos. Utilizando um programa gerenciador de arquivos, também é possível navegar por diretórios e, clicando-se sobre ícones associados a arquivos executáveis, inicia-se a execução de programas.

Cada um desses programas pode gerar um ou mais processos, dependendo de como foram implementados. Em geral, cada (instância de um) programa gera um processo em execução. 

Usando algum tipo de utilitário monitor de sistema, é possível selecionar processos, verificar seus estados e terminar suas execuções.

Ativação de programas via shell
Quando interagindo com um programa shell, em qualquer sistema Unix, usuários podem iniciar a execução pela linha de comandos. Alguns comandos internos do shell e alguns programas utilitários permitem o controle das execuções dos processos.

A execução de programas a partir do shell pode ser feita colocando os processos em execução em primeiro ou segundo planos, comumente chamados de foreground ou background.

- **prog** <enter>         // ativação de programa para execução em primeiro plano (foreground). 
                                  // Shell espera programa terminar antes de voltar a mostrar o prompt para o usuário
- **prog** & <enter>     // execução em segundo plano (background), liberando o shell da espera pela conclusão
                                  // da execução do processo. Prompt é reativado assim que programa é posto em execução.
Quando digitando comandos no shell o caractere ";” permite separar diversos comandos numa única linha. Ex: prog1 args; prog2 args; ...

Também é possível solicitar a execução condicional de listas de comandos. Para tanto, usa-se os caracteres &&, que indicam que um comando seguinte deverá ser executado apenas se o anterior for concluído com sucesso.

Ex.:  ```$ prog1 && prog2 <enter>```

Por outro lado, é possível que um comando ou conjunto de comandos expandam-se por mais de uma linha. Para tanto, usa-se o caractere "\” ao final de cada linha que não é a última do comando.

Ex:   ```
$ programa parâmetros ... \ <enter>
         ... mais parâmetros \. <enter>
         ... parâmetros finais <enter>```

**Encerrando e suspendendo (parando) a execução de processos**

Usando algum tipo de programa monitor de sistema, SOs em geral permitem selecionar processos e encerrar suas execuções.

O controle de processos em sistemas Unix é feito através do envio de sinais. Sinais, em geral, estão relacionados à ocorrência de eventos específicos durante a execução dos processos, mas também podem lhes ser enviados explicitamente pelo usuário ou por outros processos.

Para o controle de processos iniciados a partir da sessão de shell corrente, por exemplo, é possível usar algumas combinações de teclas configuradas no terminal (stty). Pressionadas no terminal, as teclas relacionadas a seguir geram o envio de sinais para o processo em foreground:

- <**ctrl**> **c**             // interrompe (termina) a execução de um processo em foreground
- <**ctrl**> **z**             // suspende (para) a execução de um processo em foreground
Há também comandos internos do shell que permitem consultar o estado dos processos que foram iniciados na sessão corrente: jobs, bg e fg. Digitados na linha de comando do shell, esses comandos permitem observar e mudar o plano de execução dos processos iniciados a partir da sessão corrente:

- jobs: comando interno do shell que mostra os processos iniciados na sessão de shell corrente e que estão parados ou sendo executados em background.
- bg: comando interno do shell que envia para execução em background um processo (job) da sessão corrente que suspenso ou parado. Ex.: ```$ bg <enter>;  $ bg %3 <enter>   // %3, neste caso indica o job # 3.```
- fg: comando interno do shell que envia um processo parado ou em background para execução em foreground. Ex.: ```$ fg <enter>;  $ fg %2 <enter>```

**Envio de sinais aos processos**

Além do comando jobs, que trata dos processos iniciados na sessão de shell corrente, há outras formas para identificar processos (programas em execução) e enviar-lhes sinais. Os utilitários ps, kill, killall e pkill servem para identificar processos em execução e enviar sinais a eles, independentemente de terem sido iniciados em outra sessão de shell, ou via interface gráfica. 

Todo processo em execução é identificado no sistema operacional através de um valor único, chamado pid (process idendificator). Esse identificador pode ser usado para o envio de sinais entre processos, como feito por um usuário a partir do shell.

O envio de um sinal a um processo pode ocorrer devido à ocorrência de algum evento durante sua execução, como uma exceção, ou então pode ser enviado devido a uma solicitação explícita de outro processo. De maneira geral, sinais são usados para parar ou interromper a execução de processos.

Para ver a lista completa de sinais disponíveis pode-se usar o comando kill com o parâmetro ```-l ($ kill -l )```. Também vale usar o manual online ($ man kill). 

- ps: utilitário que informa o status de processos. Ex: ps -ef, ps -aux
- kill: utilitário que envia um sinal (signal) para um processo especificado pelo seu pid. Ex: kill -l (lista sinais disponíveis); kill 1234; kill -9 666
- killall: envia um sinal para o processo especificado pelo seu nome. Ex: killall proc
- pkill: envia um sinal a um processo, identificado por diferentes atributos (pkill). ($ man pkill      // !!!)

Além do envio de sinais através do comando kill, a configuração do terminal de acesso apresenta combinações de teclas para o envio direto de alguns sinais relevantes no controle de execução de processos em foreground. Essas teclas são definidas com o comando stty, que trata da configuração do terminal,  e incluem sinais para suspender, parar, interromper, terminar e continuar a execução do processo.

**stty -a:** exibe a configuração dos comandos especiais do console. Entre as configurações, podem ser destacados:

**intr CHAR:** envia um sinal SIGINT (2). Ex: ```stty intr ^C```
**quit CHAR:** envia um sinal SIGQUIT (3) ao processo em foreground.
**susp CHAR:** envia um sinal SIGSTP (20), suspendendo a execução de um processo. Ex: ```stty susp ^Z```
**stop CHAR:** para a saída de dados (output) do processo em foreground.
**start CHAR:** reinicia a saída de dados (output) depois de tê-la interrompido.

Prioridades de processos
Processos têm prioridades estáticas, chamadas valor de nice, que variam de -20 a 19. -20 é o valor mais prioritário e 19 o menos. O valor padrão para essa prioridade é 0, que é um valor intermediário.

Na ativação de um processo e mesmo em tempo de execução, um usuário pode diminuir a prioridade de um processo, aumentando seu valor de nice. Assim, pode-se variar o valor de nice de 0 (valor padrão) até 19. Apenas o usuário root pode atribuir valores de prioridade na faixa de -1 a -20, que corresponde aos mais prioritários.

De maneira geral, é comum diminuir a prioridade de processos longos, sem interatividade no terminal, de forma que eles não prejudiquem o tempo de resposta de processos interativos.

-nice: executa um comando com baixa prioridade de escalonamento. Ex: nice -n +10 prog
- renice: ajusta a prioridade de um processo já criado.Ex: renice +1 pid, renice 20 pid
- ionice: ajusta a prioridade das operações de E/S do processo.
- nohup: inicia a execução de um programa imune a hangups (não é encerrado com o fim do shell a partir do qual foi iniciado). Ex: nohup prog &
- disown: remove um job especificado da tabela de jobs ativos do shell corrente. Opcionalmente, não o remove da tabela mas apenas faz com que ele não receba o sinal SIGHUP caso o shell o receba.

**Execução programada de programas**

Também é possível programar a ativação de processos em instantes específicos ou periodicamente. Para tanto, são usados os utilitários at e cron:

- at: enfileira um job para execução posterior. É preciso que o servidor atd esteja - sendo executado. Ex: at -f prog 00:00 01.01.05
- atq: examina os jobs selecionados para execução posterior
- atrm: remove os jobs selecionados para execução posterior
- atrun: executa jobs selecionados para execução posterior
- batch: executa comandos quando a carga (load) do sistema estiver abaixo de um valor especificado
- crontab: programa usado para instalar, desinstalar ou listar as tabelas usadas pelo daemon cron. Cada usuário pode ter sua própria tabela. Requer que o servidor crond esteja em execução.

Útil na criação de scripts, o comando sleep suspende temporariamente a execução de um processo:

- sleep: suspende a execução de um comando por pelo menos o tempo especificado em segundos. Ex: sleep 10; echo fim!

**Contabilização de uso de recursos pelos processos**

É possível contabilizar os recursos de processamento usado por processos:

- time: contabiliza o tempo de execução de um processo. Ex: time gcc ...
-  top: mostra processos com maior ocupação da UCP e controla suas execuções. 

**Terminando a execução de um processo**

O encerramento de processos é feito com o envio de um sinal apropriado. A partir do shell, há várias formas de fazê-lo:

**a)** para processo executando em foreground:       <**ctrl**> C

**b)** para processo em background:      fg; <**ctrl**> C

**c)** para processo iniciado por outra sessão de shell:

```ps -ef | grep [nome_prog ou "login”]; kill -9 pid```

```ps -U login; kill -9 pi```

```killall -9 nome_prog```

---
## Redirecionamento de E/S de processos

Programas podem escrever informações no terminal onde executam e podem ler dali dados de entrada para suas execuções. Pensando num program C, por exemplo, usa-se **printf** ou **fprintf(stdout, ...)** para imprimir na janela do programa. Para ler dados do terminal, pode-se usar **scanf**, **fscanf(stdin,... )**, **fgets( ..., stdin)**, entre outros.

Como pode-ser observar, há referências explícitas a stdin para entrada e stdout para saída, ou isso é assumido implicitamente nos comandos, como em printf e scanf.

Ocorre que o sistema operacional mantém, para cada processo, informações sobre os arquivos que estão e uso. Essas informações são salvas numa estrutura interna do SO chamada de vetor de arquivos abertos. Na prática, stdin, stdout e stderr são nomes lógicos que fazem referências às 3 primeiras desse vetor.

A entrada e saída de dados em processos no ambiente Unix é feita através da escrita e da leitura em 3 arquivos lógicos: stdin (0), stdout (1) e stderr (2).

Representados pelas 3 primeiras posições do vetor de arquivos abertos de cada processo, esses arquivos geralmente apontam para o terminal ou para a janela associada ao shell de ativação do processo. Esse direcionamento é herdado na cópia do vetor de arquivos que ocorre na criação de cada processo iniciado pelo shell.

Ajustes especiais indicados na linha de comando de ativação de um processo, entretanto, permitem redirecionar esses dados para outros arquivos, ou mesmo para a comunicação direta entre processos, através de pipes.

> ou 1>: redirecionamento da saída de dados de um processo (overwrite). Ex: ls > diret

>> ou 1>>: redirecionamento da saída de dados (append). Ex: ls >> diret

2> : redirecionamento das mensagens de erro. Ex: make >& arq_msg_erro

2>> : redirecionamento das mensagens de erro (append). Ex: prog 2>> msg_erro

< : redirecionamento da entrada de dados de um processo. Ex: prog1 < arq_dados

&>: redirecionamento de stdout e stderr para o mesmo local. Ex: prog &> saida

Nos exemplos acima, vê-se o redirecionamento da saída (stdout), da entrada (stdin) e das mensagens de erro (stderr), fazendo-os apontar para arquivos.

Além disso, há um outro mecanismo muito útil em sistemas Unix, chamado pipe. Trata-se de um mecanismo de comunicação entre processos, mantido numa área de memória do SO, mas que é usado para leitura e escrita como se fosse um arquivo.

Pipes também podem ser usados para o redirecionamento de E/S de processos, comumente fazendo com que os dados de saída gerados por um processo sejam direcionados como dados de entrada de outro processo. Assim, o pipe funciona como se fosse um buffer em memória, que acomoda os dados de saída que um processo gera, até que outro processo associado à leitura deste pipe os consuma. 

No shell, o uso de pipes no redirecionamento de E/S de processos é feito como segue:

| **(pipe):** cria um mecanismo de comunicação entre processos. Ex: ls -la | more

Em sistemas Unix há ainda um programa utilitário que permite receber a saída de um processo, via um pipe, e duplicar essa saída, fazendo com que ela vá tanto para um arquivo especificado quanto para a janela do terminal.

**tee**: copia os dados do arquivo padrão de entrada para o arquivo padrão de saída, fazendo opcionalmente uma cópia para outros arquivos de saída. Ex: p1 | tee result