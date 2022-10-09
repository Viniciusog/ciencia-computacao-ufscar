# Conhecendo o sistema computacional: do boot ao prompt
## Professor: Hélio Crestana Guardia
## Universidade Federal de São Carlos
---

### BIOS

Usando algum sistema computacional ao qual você tem acesso, vamos examinar o carregamento inicial do sistema operacional. 
Ao ligar o computador observe se há indicação de alguma combinação de teclas a serem pressionadas para ativar acesso à interface de configuração dos parâmetros de inicialização e operação desses sistema.
Se possível, ative o programa de configuração e observe os seguintes parâmetros:

- configurações do processador
- configurações de memória
- configurações dos controladores de periféricos presentes na placa-mãe
- configuração das unidades de armazenamento detectadas
- configurações de sequência de dispositivos para busca carregamento do bloco de iniciação do sistema
- configurações de senhas de acesso a esse programa!
- medições da temperatura do processador e da placa-mãe
- opções de ajuste de valores default e de salvamento das alterações realizadas (cuidado com isso!)
- ... o que mais houver para consultar ou configurar no seu sistema...


Se a memória RAM é volátil, onde está armazenado esse programa de controle? (observe que ele funciona mesmo que não exista um HD ou SSD)
Onde são salvos os parâmetros de configuração que podem ser alterados? (há uma bateria em formato de moeda na placa-mãe? Para que serve?)

Ai, ai, ai, me esqueci que não é possível estar lendo essas questões enquanto o sistema estiver nessa fase de configuração da BIOS... (dá para usar o smartphone enquanto isso? melhor anotar o que é preciso observar...)

Hélio

---
### Quão rápido? Por quê?

Você tem um cronômetro à mão? Use-o para medir o tempo que leva para:

- executar o programa da BIOS ou UEFI (do momento em que o computador é ligado até que inicie-se o carregamento do SO)
- carregar o SO, até que ele esteja disponível para uso
- se for um notebook, ou algum outro sistema com opção de "stand-by", meça esse tempo e considere o que pode ser diferente nos 2 casos; vale pensar também onde possíveis informações de controle para restabelecimento do estado de uso foram salvas...
  
Os tempos de espera são razoáveis? 

Qual será que é a atividade que consome mais tempo nesse processo?

Será que há algo que pudesse ser feito para reduzir o tempo até que o sistema esteja disponível para uso?

---

### Controle de acesso

Com o SO  carregado, analise o processo de identificação de usuário para controle de acesso ao sistema.

Quais mecanismos estão disponíveis? Nome de usuário e senha?

Alguma forma de biometria? Reconhecimento facial?

Você considera que esse sistema é seguro ao prevenir o uso por uma pessoa não autorizada?

Será que os procedimentos de autenticação requeridos do usuário e os atrasos inerentes são vistos como adequados pelos usuários?

---

### Dispositivos detectados pelo SO

Quais dispositivos físicos foram detectados no sistema computacional em uso?

Para quem não está usando um sistema virtualizado, é possível examinar a lista de dispositivos que o programa da BIOS do computador exibe antes do boot do sistema. Essa lista de dispositivos é mantida na forma de uma tabela com estruturas de dados padronizadas que o SO pode consultar (SMBIOS), ao invés de ter que testar cada barramento em busca dos dispositivos presentes. 

Na fase de boot, o SO vai tentar carregar controladores para os dispositivos para os quais tenha suporte. 

Uma vez conectado ao sistema, o usuário pode consultar esses dispositivos de diferentes formas:

Num sistema Linux, por exemplo, usando a interface gráfica, é possível examinar a ferramenta de configuração e verificar quais são os dispositivos. 
Num sistema Linux, dentro das opções de configurações do sistema é possível ver os dispositivos configurados.
Num sistema Windows, junto às configurações do sistema (Settings) é possível ver informações sobre os dispositivos e as configurações do sistema. Dentro das "Ferramentas Administrativas" também é possível acessar o "Gerenciamento do Computador", onde há informações sobre o "Gerenciador de dispositivos". 
Num sistema MacOS, é possível examinar "About this Mac -> System Report...".
Seja lá qual for o sistema operacional em uso, basta procurar por alguma ferramenta de configuração / informação...

Veja: processador, memória, unidades de armazenamento, interfaces de rede (com e sem fio), bluetooth, câmera de vídeo, áudio, barramentos (PCI, USB), controladores de disco (SATA, SCSI, ...), dispositivos USB, ... e o que mais houver.

Em geral, se o SO está detectando esses dispositivos, é porque há algum software controlador para esse dispositivo (device driver) para esse SO.

---
### Gerenciador de tarefas

O que está em execução no sistema operacional?

Em geral, deve haver alguma ferramenta do tipo "Monitor do Sistema", "Activity Monitor", "Gerenciador de Tarefas", ou coisa que o valha. Em linha de comando, interagindo diretamente com um programa shell, é possível ativar o programa top, por exemplo.

Nessas ferramentas, é possível ver informações sobre o uso do(s) processador(es), do sistema de arquivos, da memória, das interfaces de rede.

Também é possível ver informações detalhadas sobre os processos, que estão associados aos programas em execução. Processos são uma abstração relevante do SO. Na maior parte dos sistemas há ainda o conceito de threads, que são "linhas de execução" associadas aos processos (detalhes numa próxima unidade deste curso...).

Quantos processadores existem? E quantos programas (processos)? Há processos com mais de uma thread?

Como será que o SO consegue alternar o uso do(s) processador(es) para a execução de tantas tarefas (processos ou threads) ao mesmo tempo?

Observando os programas, é possível ver seus estados? Há programas parados, à espera de entrada e saída de dados? Isso pode estar associado à técnica de multiprogramação!

Será que o mecanismo de time-sharing está sendo usado pelo SO?

Como é o consumo de CPU das tarefas? Como é o consumo de memória das tarefas? 

Xi, há tanto a explorar por aqui... sejamos curiosos com o SO e com os sistemas que usamos!

Hélio