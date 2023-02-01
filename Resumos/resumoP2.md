## PROCESSOS

Processos(entidade ativa) são programas(entidade passiva) em execução, um programa só pode ser executado na memoria principal do computador.

Um processo é uma parte da memória separada pelo sistema operacional para conter conter um progerama que será executado. Essa memória que foi separada possui diversas parte, entre elas:

* text section: codigo do programa
* program counter: codigo que está em execução
* stack: dados temporarios
* data section: variaveis globais
* heap: memoria alocada dinamicamente

Um processo pode ter vários estados:

* new: esta sendo criado
* running: esta sendo executado
* waiting: esperando um evento acontecer
* ready: esperando para ser alocado para um processador
* terminated: finalizou execução

Caminhos entre estados:

* ready -> running (escalonador alocou um processador para o processo)
* running -> ready (interrupção)
* wating -> ready (I/O completo)
* running -> waiting (I/O iniciado)

Bloco de controle de processo (process controle block) armazena informações associadas a cada processo:

* estado do processo
* program counter (localização da proxima instrução)
* CPU registers
* CPU scheduling information
* Informações de gerenciamento de memoria (memoria alocada para o processo)
* Accounting information
* Informação de status do I/O

Com vários contadores de programa(program counters) é possivel executar diferentes localizações ao mesmo tempo, também chamado de threads. Para isso é preciso armazenar os detalhes das threads e os contadores de programa no PCB.

O escalonamento de processos é feito entre os diverosos processos disponiveis para a proxima execução, com ele é possivel maximizar a utilização da CPU. O escalonador de processos mantém filas de escalonamento de processos.

* Job queue: conjunto de todos os processos no sistema
* Ready queue: conjunto de todos os processos que estão na memoria principal, ready e waiting para executar.
* Device queue: conjunto de processos waiting por um dispositivo I/O.
* Processos migram entre as várias filas  

Short-term scheduler(CPU schedulers) seleciona qual proximo processo deve ser executado na CPU. Ele é "invocado" frequentemente, por isso deve ser rápido

Long-term scheduler(job Scheduler) seleciona qual processo deve ser carregado na ready queue. Ele NÃO é "invocado" frequentemente e controla o grau de multiprogramming.

Os processos podem ser classificados como I/O-bound(passa mais tempo fazendo I/O) e CPU-bound(passa mais tempo na CPU). 

Quando a CPU muda de processo, o sistema tem que salvar o estado do processo antigo e carregar o estado do novo processo, isso é chamado de troca de contexto(context-switch). O contexto de um processo é representado no PCB.

A troca de contexto custa muito tempo, e durante esse tempo o sistema não faz nenhum trabalho util.

No termino do processo, ele executa a ultima declaração e faz um chamada de sistema(system call) exit() para deletar.

* Ele retorna as informações de status de filho para pai(através do wait())
* Os recursos alocado para o processo são desalocados pelo sistema operacional

Os processos pai podem terminar a execução de processos filhos usando a chamada de sistema abort(). Razões para fazer isso:

* O processo filho excedeu a quantidade de recursos alocados
* A tarefa do processo filho não é mais requisitada pelo processo pai
* O processo pai está terminando e o sistema operacional não permite que o processo filho continue(cascading termination, nem todos os sistemas operacionais funcionam assim)

Um processo pai pode esperar pelo termino de um processo filho a partir da chamada de sistema wait. A chamada retorna a informação de estatus e o pid(process id) do processo terminado. Se o processo não pai está esperando (ou seja, não chamou o wait()), então o processo se torna um zumbie. Se o processo pai terminou sem "invocar" o wait(), então o processo se torna orfão

Para processos se comunicarem existem dois métodos:

* Shared memory(memória compartilhada) **(caiu na prova)**
* Message passing(passgem de mensagem) **(caiu na prova)**

Shared memory:

Uma área da memória que é compartilhada entre processos que querem se comunicar. Essa comunicação é controlada pelos processos de usuário e não pelo sistema operacional.

Message passing:

Para que a comunicação ocorra sem a necessidade de depender em variáveis compartilhadas, pode-se usar duas operações, send(message) e receive(message) (sistema de mensagens), que é um mecanismo para processos se comunicarem e sincronizar suas ações. Mas, para isso é necessário estabelecer links de comunicação(comunication links), os links de comunicação podem ser feitos de duas formas:

1. Física: memória compartilhada / rede / barramento
2. Lógica: Direta ou indireta/ sincrona ou assincrona / automatica ou explicit buffering 

Pode ocorrer de dois ou mais processos estarem esperando indefinidamente por um evento que só pode ser causado por um dos processo que está em espera, isso é chamado de DEADLOCK. **(caiu na prova)**

Quando um processo fica indefinidamente na fila de bloqueados do semaforo, esse evento é chamado de STARVATION. **(caiu na prova)**

No evento de um processo de baixa prioridade impedir a execução de um processo de alta prioridade, esse problema de escalonamento é chamado de PRIORITY INVERSION. **(caiu na prova)**
 
## THREADS
	
A thread é uma unidade fundamental de utilização da CPU que forma a base para um sistema computacional multithreaded
	
Em uma arquitetura multicore ou multiprocessor é permitido o uso de paralelismo.

Diferença entre paralelismo e concorrencia:

* Paralelismo: mais de uma tarefa(processo ou thread) sendo executada ao mesmo tempo. => Necessita de um sistema multicore
* Concorrencia: mais de uma tarefa(processo ou thread) fazendo progresso, a partir do escalonamento. => Pode ocorrer em um sistema singlecore

As threads podem ser dividas em duas categorias, as user threads e as kernel threads. As user threads são gerencias pelas bibliotecas de threads a nível de usuário, as kernel threads são apoiadas pelo kernel. Assim existem várias formas dessas threads se comunicarem (user threads -> kernel threads)

1. Many-to-one, são várias threads de usuário mapeadas para uma unica thread de kernel. (Uma só pode estar no kernel por vez, isso elimina a possibilidade de multithread)
2. One-to-one, uma thread de usuário é mapeada para uma thread de kernel. (pode haver restrições de numero de thread para não sobrecarregar)
3. Many-to-many, várias threads de usuário mapeadas para várias threads de kernel.
4. Two-level, similar a M:M, além de que permite que uma thread de usuário seja conectada a uma thread de sistema.

Thread Pools(reservatorio de thread) são um espaço onde várias threads, préviamente criadas, esperam para serem chamadas. Possui vantagens quanto ao tempo para servir um pedido(uma vez que ela ja está criada), permite que o número de threads de uma aplicação esteja conectada ao limite da pool(reservatorio).

Cancelar uma thread é terminar ela antes que ela tenha finalizado sua tarefa. A thread que for cancelada é chamada de target thread. Elas podem ser terminadas asincronamente (termina a target thread imediatamente) ou cancelamento por despacho(permite a target thread verificar periodicamente se ela deve ser cancelada ou não)

Cada thread pode ter sua própria copia de informação a partir do thread-local storage(TLS), que é diferente de variáveis locais, pois a variáveis locais só são visiveis durante a invocação de um função, enquando a TLS é visivel através das invocações de funções.


## ESCALONAMENTO DA CPU

O escalonamento de processos na CPU torna possível o multiprograming, o que maximiza a utilização da CPU. A execução dos processos consiste em um ciclo onde a CPU está executando intruções e esperando I/O.(CPU-I/O Bursts, CPU bursts seguido de I/O bursts).

O short-term scheduler seleciona processos que estão na ready queue e aloca a CPU para um deles. A decisão de escalonamento da CPU pode acontecer em 4 estágios:

1. Quando o processo muda de running para waiting
2. Quando o processo muda de running para ready
3. Quando o processo muda de waiting para ready
4. Quando o processo termina

O escalonamento feito entre 1 e 4 é nonpreemptive. Em todos os outros o escalonamente é preemtive(por exemplo quando um processo está rodando a muito tempo e o SO retira ele da CPU para que outro processo tome seu lugar).

O modulo dispatcher concede o controle da CPU ao processo selecionado pelo short-term scheduler, isso envolve troca de contexto(context switch), mudar para modo de usuário, pular para a localização apropriada no programa de usuário para recomeçar o programa correspondente. O tempo que leva para o dispatcher para o processo que está em andamento e começar outro é chamado de dispatch latency.

Critérios para escalonamento:

* Utilização da CPU (objetivo do algoritmo: max)
* Throughput (objetivo do algoritmo: max)
* Turnaround time (objetivo do algoritmo: min)
* Waiting time (objetivo do algoritmo: min)
* Response time (objetivo do algoritmo: min)

Algoritmos de escalonamento **(caiu na prova)**:

* First Come, First Served
* Shortes-Job-First
* Length of Next CPU Burst
* Exponential Averaging
* Shortest-remaining-time-first
* Priority Scheduling
* Round Robin

A fila de ready é dividida em outras filas, a foreground e a background. Cada uma dessas filas tem seu proprio algoritmo

Quando o sistema tem suporte a threads são elas que são escalonadas no processador, não os processsos. Nos modelos many-to-one e many-to-many as threads de usuário devem ser escalonadas para threads de kernel, que por sua vez são escalonadas para as CPUs disponíveis.

Em um sistema multicore (com várias CPUs disponíveis) o escalonamente é mais complexo e pode ser feito de várias formas:

* Homogeneous processors
* Asymmetric multiprocessing
* Symmectric multiprocessing(SMP, mais comum): cada processador faz seu escalonamento a partir de uma fila comum de processos ready, ou cada um tem sua própria fila de processos ready 
* Processor affinity

No SMP é necessário manter todas as CPUs carregadas para ter eficiência. Para isso é preciso ter load balancing para manter a taxa de trabalho equilibrada entre as CPUs, quando tem uma CPU sobrecarregada os processos são retirados dela(push migration) é alocados em outra CPU(pull migration) menos sobrecarregada.


## GERENCIAMENTO DE MEMÓRIA

Como a memória principal  e os registradores são os únicos armazenamentos que a CPU pode acessar diretamente, então o programa precisa ser levado do disco à memória e colocado em um processo para ser executado pela CPU. A unidade de memória vê apenas um, fluxo de endereços + solicitações de leitura, ou endereços + solicitações de dados e escrita.
Enquanto os registradores são acessados em um clock de CPU (ou menos), o acesso à memória pode demorar vários ciclos, resultando em um stall(bolha). Para diminuir a frequencia de acesso á memória a cache é utilizada como uma memória intermediária entre os registradores da CPU e a momória principal.

Um registrador de base e um registrador de limite são utilizados para difinir o local do endereço lógico. Como medida de proteção, a CPU precisa verifica se cada acesso à memoria gerado está entre o registrador de base e o registrador limite.

Programas no HD que estão prontos para serem alocados na memória principal ficam na input queue. Os endereços são representados de diferentes maneiras de acordo com o estágio na "vida" do programa.

* Source code: endereços são simbolicos
* Compiled code(codigo compilado): endereços são vinculados a endereços relocáveis(14 bytes do início desse módulo)
* O vinculador ou carregador ligará endereços relocáveis a endereços absolutos (74014)
* Cada vínculo mapea um espaço de endereço para outro.

O vinculo de instruções e dados para endereços de memória podem acontecer em três estágios diferentes:

* Compile time(tempo de compilação): se a localização na memória é conhecida é possível gerar absolute code.
* Load time(tempo de carregamento): se a localização na memória não é conhecida é necessário gerar relocatable code.
* Execution time(tempo de execução): vínculo é adiado até o tempo de execução se o processo pode ser mudado de um segmento de memória para outro durante sua execução.

O endereço lógico é conectado a um endereço físico diferente. Enquanto o endereço lógico/endereço virtual é gerado pela CPU o endereço físico é enxergado pela unidade de memória. Em tempo de compilação e tempo de carregamento o endereço lógico/virtual e físico são os mesmos, eles se diferem no tempo de execução.

A memory management unity(MMU) mapeia os endereços lógicos para endereços físicos. Uma das formas mais simples é o valor do relocation register ser somado a todo endereço gerado por um processo de usuário(sempre enxerga endereço lógico) no momento em que é mandado para a memória. O base register agora é chamado de relocation register.

Caso o proximo processo a ser alocado na CPU não estiver na memória é necessário liberar espaço na memória, alocando um processo da memória no backing store(lugar no disco em que processos podem ser alocados temporariamente) e alocar o processo requerido do backing store para a memória (roll out, roll in). Atualmente não é comum, só acontece quando o espaço disponível na memória é extremamente baixo. 

A memória principal deve ter suporte para processos de usuário e processos do SO, para isso ele divide a memória em duas partes. A parte com os primeiros endeços físicos são destinados ao sistema operacional, enquanto os endereços físicos mais elevados são para processos de usuário, onde cada processo é contido em uma secção contígua da memória. Para proteger os processos de usuário o base register contém o valor do menor endereço físico, enquanto o limit register contém o alcance dos endereços lógicos - cada endereço lógico deve ser menor que o limit register. 

A memória é divida em partições, quanto um processo chega ele é alocado na memória em um buraco grande o suficiente para caber ele. Quando um processo sai ele deixa essa partição livre e as partições livres adjacentes são unidas.

Um dos problemas é a escolha das partições para alocar o processo.

* First fit: aloca o primeiro buraco(hole) que tem tamanho o suficiente para acomodar o processo.
* Best fit: aloca o menor buraco(hole) suficiente para acomodar o processo(para isso é necessário procurar na lista inteira)
* Worst fit: aloca o maior buraco(hole)(também é necessário procurar pela list inteira)

A fragmentação pode ser externa(quando o total de espaços livre existe, é suficiente, mas não é contiguo), ou pode ser interna(quando o espaço da partição alocado para o processo é maior do que o processo precisa)

Para diminuir a fragmentação da memória, a memória é divida em partições iguais chamadas de frames e divide a memória lógica em blocos do mesmo tamanho chamada de paginas. Para fazer a tradução de endereços lógicos para endereços físicos é usada a tabela de páginas. O endereço gerado pela CPU(lógico) é divido em page number(indice na tabela de páginas que contém o endereço base para cada pagina na memória física) e page offset(combinado com o endereço base, define o endereço da memória física que é mandado para a unidade de memória)

Segmentação é um suporte a visão de usuário provida pelo esquema de gerenciamento de memória. O segmento é um unidade lógica como:

* Main program
* Procedure
* Function
* Method
* Object
* Local variables, globas variable
* Common block
* Stack
* Symbol table
* Arrays

O endereço lógico consistem em dois números: <segment number, offset>. A tabela de segmento mapeia endereços físicos de duas dimensões, cada entrada da tabela tem a base, o endereço físico onde o segmento reside an memória e o limit, que especifica o tamanho do segmento. Além disso, tamém tem o bit de proteção associado a cada entrada.

## MEMÓRIA VIRTUAL (caiu na prova)

O programa precisa estar na memória para ser executado, mas não é necessário que todo ele esteja na memória. Isso permite uma criação de processos mais eficiente, mais programas executanto concorrentemente, menos I/O para carregar ou swap de processos.

Geralmente a stack cresce de cima para baixo(do endereço lógico mais alto para o mais baixo) e a heap cresce de baixo para cima(do endereço lógico mais baixo para o mais alto)

É possível trazer um processo inteiro para a memória em tempo de carregamento, ou trazer uma página somente quando é necessária. Quando o swap só aloca a página na memória quando ela é necessária é chamado de lazy swapper(pager)

Se tem uma referencia a uma página, a primeira referência a essa página será um armadilha para o SO: Page Fault. Então o SO procura em outra tabela para decidir se a referencia foi invalida, ou a página só não está na memória.
