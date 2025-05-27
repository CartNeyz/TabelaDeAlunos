#include <iostream>  // biblioteca para inclusao de informacao input & output
#include <iomanip>  // manipula formato de output por meio de formatadores, usado para determinar largura do campo, numero decimal afins...
#include <string> // usado para manipular cadeia de caracteres, tem palavras reservadas como length para manipular as quantidades de caracteres de uma string.
#include <vector> // armazenamento de listas de elementos com tamanho variável.
#include <chrono> // usado para manipulação do tempo nesse código, como por exemplo pausar um código por um tempo determinado, timers e afins
#include <thread> // usado para executar código simultaneamente ou pausar o programa por determinado tempo.

using namespace std;  // funcao reservada da base c++, usado para cortar o prefixo dos consoles input/output, não sendo mais necessario declarar std;; antes de qualquer comando de cout & cin

struct Aluno {
    string nome;
    string rgm;
    float A1 = 0, A2 = 0, AF = 0;
}; // cria uma classe chamado aluno que recebe as seguintes variaveis: seu nome, seu rgm e sua nota.

void Login() {
	cout << " _                 _       "<< endl;
	cout << "| |               (_)      "<< endl;
 	cout << "| |     ___   __ _ _ _ __  "<< endl;
	cout << "| |    / _ \\ / _` | | '_ \\ "<< endl;
	cout << "| |___| (_) | (_| | | | | |"<< endl;
	cout << "|______\\___/ \\__, |_|_| |_|"<< endl;
   	cout << "              __/ |        "<< endl;
    cout << "             |___/         "<< endl; // printa uma logo
    string usuario, senha; 
    const string usuarioCorreto = "Admin";
    const string senhaCorreta = "1234"; // declara os valores de acesso do login
	
    while (true) {
        cout << "=====REALIZE O LOGIN =====\n";
        cout << "Usuario: ";
        cin >> usuario;
        cout << "Senha: ";
        cin >> senha;  // recebe o usuario e senha do login

        if (usuario == usuarioCorreto && senha == senhaCorreta) {
            cout << "Login realizado com sucesso!\n";
            system("pause"); 
            system("cls"); // limpa o terminal
            break; // termina o código
        } else {
            cout << "Usuario ou senha incorretos. Tente novamente.\n\n"; 
        } // valida o acesso esteja correto, e pede novamente a senha caso esteja errado.
    }
}

// valida o acesso do login

int Filtrar(const vector<Aluno>& alunos) {
    int opcaofiltro;
    cout << "\nOrdenar por...";
    cout << "\n1. Aprovados";
    cout << "\n2. Reprovados";
    cout << "\n3. Voltar";
    cout << "\nEscolha uma opcao: ";
    cin >> opcaofiltro;
// printa o menu do código
    system("cls");

    if (alunos.empty()) {
        cout << "Nenhum aluno cadastrado.\n";
        system("pause");
        return opcaofiltro;
    } // combinacao da funcao reservada da string que verifica se o input está vazio com a checagem da memória temporaria, verifica se caso esteja vazio a tabela de alunos, printa que nao tem aluno, pausa o sistema até receber um input de continuacao e retorna a função opcaofiltro (o menu de opcoes)

    cout << left << setw(15) << "Nome"
         << setw(10) << "A1"
         << setw(10) << "A2"
         << setw(10) << "AF"
         << setw(15) << "Situacao" << endl;
// recebe informações input do usuario em ordem, e nessa ordem classifica cada input correspondente as variaveis, sendo nome, a1, a2, af, situacao.

    for (const Aluno& a : alunos) {
        float media = a.A1 + a.A2;
        string situacao;
// para cada aluno no banco de dados de aluno, declara-se a media deles por meio da soma das variaveis a1 e a2, e entao declara uma string chamada situacao
        if (media >= 6) {
            situacao = "Aprovado";
        } else {
            float novaMedia = (a.A1 < a.A2 ? a.AF + a.A2 : a.A1 + a.AF);
            situacao = novaMedia >= 6 ? "Aprovado c/ AF" : "Reprovado";
        }
// caso a soma das notas seja maior ou igual a 6 o aluno está aprovado, caso contrario se inicia uma formula de checagem que atualiza a variavel novaMedia, a lógica e a seguinte: se a1 for menor que a2, então substitui-se a menor nota pela nota de reforço (af), isso se aplica as duas somatórias
        if ((opcaofiltro == 1 && (situacao == "Aprovado" || situacao == "Aprovado c/ AF")) ||
            (opcaofiltro == 2 && situacao == "Reprovado")) {
            cout << left << setw(15) << a.nome
                 << setw(10) << a.A1
                 << setw(10) << a.A2
                 << setw(10) << a.AF
                 << setw(15) << situacao << endl;
        }
    }
// se o input for 1 irá retornar os alunos em estado de aprovação, até mesmo aqueles que necessitados, recorreram-se a nota de reforço. caso o input seja 2, então ira retornar os alunos que foram reprovados.

    cout << "\nPressione ENTER para retornar ao menu.";
    cin.ignore();
    cin.get();
    return opcaofiltro;
}
// no fim desse código todo de filtragem, então o console vai esperar a confirmação do usuario, caso ele queira continuar com o codigo, irá confirmar pelo enter, então o cin.ignore vai ignorar a quebra de linha do cout, enquanto o cin.get() vai pedir a tecla ENTER e somente ela, após isso o código vai retornar ao menu.

int Logo() {
    cout << " $$$$$$\\   $$$$$$\\  $$\\   $$\\  $$$$$$\\   $$$$$$\\  $$\\             $$\\       $$$$$$\\   $$$$$$\\   $$$$$$\\ " << endl;
    cout << "$$  __$$\\ $$  __$$\\ $$ |  $$ |$$  __$$\\ $$  __$$\\ $$ |            $$ |     $$  __$$\\ $$  __$$\\ $$  __$$\\ " << endl;
    cout << "$$ /  \\__|$$ /  \\__|$$ |  $$ |$$ /  $$ |$$ /  $$ |$$ |            $$ |     $$ /  $$ |$$ /  \\__|$$ /  \\__|" << endl;
    cout << "\\$$$$$$\\  $$ |      $$$$$$$$ |$$ |  $$ |$$ |  $$ |$$ |            $$ |     $$ |  $$ |$$ |$$$$\\ \\$$$$$$\\  " << endl;
    cout << " \\____$$\\ $$ |      $$  __$$ |$$ |  $$ |$$ |  $$ |$$ |            $$ |     $$ |  $$ |$$ |\\_$$ | \\____$$\\ " << endl;
    cout << "$$\\   $$ |$$ |  $$\\ $$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |            $$ |     $$ |  $$ |$$ |  $$ |$$\\   $$ |" << endl;
    cout << "\\$$$$$$  |\\$$$$$$  |$$ |  $$ | $$$$$$  | $$$$$$  |$$$$$$$$\\       $$$$$$$$\\ $$$$$$  |\\$$$$$$  |\\$$$$$$  |" << endl;
    cout << " \\______/  \\______/ \\__|  \\__| \\______/  \\______/ \\________|      \\________|\\______/  \\______/  \\______/ " << endl;
    return 0;
}
// printa a logo

int main() {
	Login();
	// executa a função armazenada login, ou seja, o código dela

    int opcao;
    vector<Aluno> alunos;
    Aluno aluno;
    Logo();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    system("cls");
// busca no vetor Aluno, alunos dentro dele, caso não tenha, irá receber alunos, printa a logo, o std::this_thread... faz o console dormir por 3 segundos, e então somente depois de 3 segundos ele executa o proximo comando, sendo ele system cls, que limpa o console.

    do {
    	system("cls");
    	cout << "   __  __                  "<< endl;
    	cout << "  |  \\/  |                 "<< endl;
		cout << "  | \\  / | ___ _ __  _   _ "<< endl;
		cout << "  | |\\/| |/ _ \\ '_ \\| | | |"<< endl;
		cout << "  | |  | |  __/ |
