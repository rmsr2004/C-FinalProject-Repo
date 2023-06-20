# C-FinalProject-Repo

Pretende-se desenvolver uma aplicação para auxiliar um funcionário de uma oficina na gestão dassuas reservas. A aplicação deverá manter informação sobre os clientes e as horas disponíveis para reservas, bem como as reservas em espera. A aplicação deve permitir realizar, de forma interativa, as seguintes operações:

• Reservar lavagem ou manutenção - um cliente faz uma reserva para lavar o carro ou para fazer a
sua manutenção.
• Pré-reserva de lavagem ou manutenção – um cliente pretende reservar uma lavagem ou uma
manutenção, mas não tem hora disponível e inscreve-se numa lista de espera para ter prioridade caso uma
reserva seja cancelada. • Cancelar uma reserva - eliminar uma reserva. Se houver uma pré-reserva compatível com o horário
e dia desocupado, esta será imediatamente enquadrada. • Cancelar uma pré-reserva - eliminar um pedido de pré-reserva. • Listar as reservas e as pré-reservas de lavagens e de manutenções ordenadas por data (as mais
antigas primeiro). • Listar as reservas e as pré-reservas de um cliente ordenadas por data (as mais recentes primeiro).

As vagas (horas de trabalho) vão das 8h00 às 18h00, sem hora de almoço. Uma lavagem de uma
viatura demora meia hora e uma manutenção uma hora. Quando uma operação termina é eliminada da
lista de reservas respetiva.

Na resolução deste problema, deve definir e usar estruturas de dados adequadas. A definição destas
estruturas deve ser feita num ficheiro fonte autónomo. Valorizam-se soluções que sejam eficazes do ponto
de vista do espaço de memória ocupado, nomeadamente soluções de ordenação que recorram a estruturas
de dados auxiliares com apontadores para os registos reais em vez de estruturas com os próprios registos.

Toda a informação relevante deverá ser armazenada em ficheiros de texto. A aplicação deve ter uma
opção para carregar a informação e outra para gravar o estado atual das reservas. O programa deve
também ser devidamente protegido.
