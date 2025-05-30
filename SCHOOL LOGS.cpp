#include <iostream>  // biblioteca para inclusao de informacao input & output
#include <iomanip>  // manipula formato de output por meio de formatadores, usado para determinar largura do campo, numero decimal afins...
#include <string> // usado para manipular cadeia de caracteres, tem palavras reservadas como length para manipular as quantidades de caracteres de uma string.
#include <vector> // armazenamento de listas de elementos com tamanho variável.
#include <chrono> // usado para manipulação do tempo nesse código, como por exemplo pausar um código por um tempo determinado, timers e afins
#include <thread> // usado para executar código simultaneamente ou pausar o programa por determinado tempo.

using namespace std; // funcao reservada da base c++, usado para cortar o prefixo dos consoles input/output, não sendo mais necessario declarar std;; antes de qualquer comando de cout & cin

struct Aluno {
    string nome;
    string rgm;
    float A1 = 0, A2 = 0, AF = 0;
};
// cria uma classe chamado aluno que recebe as seguintes variaveis: seu nome, seu rgm e sua nota.

void Login() {
    cout << " _                 _       " << endl;
    cout << "| |               (_)      " << endl;
    cout << "| |     ___   __ _ _ _ __  " << endl;
    cout << "| |    / _ \\ / _` | | '_ \\" << endl;
    cout << "| |___| (_) | (_| | | | | |" << endl;
    cout << "|______\\___/ \\__, |_|_| |_|" << endl;
    cout << "              __/ |        " << endl;
    cout << "             |___/         " << endl;

    string usuario, senha;
    const string usuarioCorreto = "Admin";
    const string senhaCorreta = "1234"; // declara os valores de acesso do login

    while (true) {
        cout << "=====REALIZE O LOGIN =====\n";
        cout << "Usuario: ";
        cin >> usuario;
        cout << "Senha: ";
        cin >> senha;
        // recebe o usuario e senha do login

        if (usuario == usuarioCorreto && senha == senhaCorreta) {
            cout << "Login realizado com sucesso!\n";
            system("pause");
            system("cls"); // limpa o terminal
            break;
        } else {
            cout << "Usuario ou senha incorretos. Tente novamente.\n\n";
        }// valida o acesso esteja correto, e pede novamente a senha caso esteja errado.
    }
}
// valida o acesso do login
void EditarAluno(vector<Aluno>& alunos) {
    string rgm;
    cout << "\nInsira o RGM do Aluno que deseja editar: ";
    cin >> rgm;

    for (auto& aluno : alunos) {
        if (aluno.rgm == rgm) {
            cin.ignore();

            cout << "\nDigite o novo nome (ou pressione ENTER para nao alterar): ";
            string novoNome;
            getline(cin, novoNome);
            if (!novoNome.empty()) {
                aluno.nome = novoNome;
            }

            cout << "\nDigite o novo RGM do aluno: ";
            string novoRGM;
            getline(cin, novoRGM);
            while (novoRGM.length() != 8) {
                cout << "\nInsira um RGM valido de 8 digitos: ";
                getline(cin, novoRGM);
            }
            aluno.rgm = novoRGM;

            cout << "\nInsira a nova nota A1: ";
            float novaNotaA1;
            cin >> novaNotaA1;
            while (novaNotaA1 < 0 || novaNotaA1 > 5) {
                cout << "Insira uma nota valida (0-5): ";
                cin >> novaNotaA1;
            }
            aluno.A1 = novaNotaA1;

            cout << "\nInsira a nova nota A2: ";
            float novaNotaA2;
            cin >> novaNotaA2;
            while (novaNotaA2 < 0 || novaNotaA2 > 5) {
                cout << "Insira uma nota valida (0-5): ";
                cin >> novaNotaA2;
            }
            aluno.A2 = novaNotaA2;

            cout << "\nInsira a nova nota AF: ";
            cin >> aluno.AF;

            float novaMedia = (aluno.A1 < aluno.A2 ? aluno.AF + aluno.A2 : aluno.A1 + aluno.AF);
            string situacao = novaMedia >= 6 ? "Aprovado c/ AF" : "Reprovado";

            system("cls");
            cout << "\nSituacao do Aluno: " << situacao << endl;
            cout << "\nNome: " << aluno.nome
                 << " - Nota A1: " << aluno.A1
                 << " - Nota A2: " << aluno.A2
                 << " - Situacao: " << situacao << endl;
            return;
        }
    }
    cout << "\nAluno nao encontrado." << endl;
}

int Filtrar(const vector<Aluno>& alunos) {
    int opcaofiltro;
    cout << "\nOrdenar por...";
    cout << "\n1. Aprovados";
    cout << "\n2. Reprovados";
    cout << "\n3. Voltar";
    cout << "\nEscolha uma opcao: ";
    cin >> opcaofiltro;

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
} // printa a logo

int main() {
    Login(); // executa a funcao login no inicio do codigo

    int opcao;
    vector<Aluno> alunos;
    Aluno aluno;

    Logo();
    this_thread::sleep_for(chrono::milliseconds(3000));
    system("cls");
    // busca no vetor Aluno, alunos dentro dele, caso não tenha, irá receber alunos, printa a logo, o std::this_thread... faz o console dormir por 3 segundos, e então somente depois de 3 segundos ele executa o proximo comando, sendo ele system cls, que limpa o console.

    do {
        system("cls");
        cout << "\n Menu \n";
        cout << "1. Tabela de Notas\n";
        cout << "2. Incluir Notas\n";
        cout << "3. Editar Alunos\n";
        cout << "4. Filtrar\n";
        cout << "5. Creditos\n";
        cout << "6. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        // cria um laço de repetição que tem como principio o print do menu, tendo 6 opções, dependendo do input (6) o console retorna uma função especifica, cada uma dessas funções está armazenada em uma switch case, o input recebido será declarado pelo computador como a opção escolhida pelo usuario

        switch (opcao) {
            case 1:
                if (alunos.empty()) {
                    cout << "Nenhum aluno cadastrado.\n";
                    system("pause");
                } else {
                    cout << left << setw(15) << "Nome"
                         << setw(10) << "RGM"
                         << setw(10) << "A1"
                         << setw(10) << "A2"
                         << setw(10) << "AF"
                         << setw(15) << "Situacao" << endl;

                    for (const Aluno& a : alunos) {
                        float media = a.A1 + a.A2;
                        string situacao;

                        if (media >= 6) {
                            situacao = "Aprovado";
                        } else {
                            float novaMedia = (a.A1 < a.A2 ? a.AF + a.A2 : a.A1 + a.AF);
                            situacao = novaMedia >= 6 ? "Aprovado c/ AF" : "Reprovado";
                        }

                        cout << left << setw(15) << a.nome
                             << setw(10) << a.rgm
                             << setw(10) << a.A1
                             << setw(10) << a.A2
                             << setw(10) << a.AF
                             << setw(15) << situacao << endl;
                    }
                }
                cout << "\nPressione ENTER para retornar ao menu.";
                cin.ignore();
                cin.get();
                break;
// O código começa verificando se tem alunos cadastrados na tabela, caso não tenha, então ele vai printar dizendo que ninguem foi cadastrado, pausa o sistema e então retorna ao menu. caso tenha alunos cadastrados, retorna uma tabela contendo o nome dele, rgm, nota e situacao, e como alternativa de checagem o console executa uma formula condicional para checar se o aluno está realmente aprovado
            case 2:
                cin.ignore();
                cout << "Digite o nome do aluno: ";
                getline(cin, aluno.nome);

                cout << "Digite o RGM do aluno (8 caracteres): ";
                getline(cin, aluno.rgm);
                while (aluno.rgm.length() != 8) {
                    cout << "RGM invalido. Insira um RGM com 8 caracteres: ";
                    getline(cin, aluno.rgm);
                }

                cout << "Digite a nota A1: ";
                cin >> aluno.A1;
                while (aluno.A1 < 0 || aluno.A1 > 5) {
                    cout << "Digite A1 novamente (0-5): ";
                    cin >> aluno.A1;
                }

                cout << "Digite a nota A2: ";
                cin >> aluno.A2;
                while (aluno.A2 < 0 || aluno.A2 > 5) {
                    cout << "Digite A2 novamente (0-5): ";
                    cin >> aluno.A2;
                }

                if ((aluno.A1 + aluno.A2) < 6) {
                    cout << "Voce foi reprovado. Digite a nota da AF: ";
                    cin >> aluno.AF;
                } else {
                    aluno.AF = 0;
                }

                alunos.push_back(aluno);
                break;
                // Esta funcao vai pedir o nome do aluno, o  cin.ignore vai limpar o buff apos o recebimento da variavel input (para prevenir do console entrar em conflito com o laço de repetição, dessa forma ele vai identificar os prints e ignora-los), apos receber essa variavel input e declarar ela como nome do aluno iremos para o rgm, agora é escrito um comando de laço de repeticao: o console pede o rgm e inicia uma formula de condicional que verifica que caso a quantidades de caracteres da string seja menor que 8 e maior que 8, ira pedir para inserir um rgm valido, em outras palavras se a quantidade de caracteres dessa string nao for identica a 8 ele ira printar um erro, isso vai se repetir até que ele tenha a quantidade correta. Apos isso vai pedir as notas, seguindo a mesma formula, com o diferencial que o input é tratado como int e nao string, isso pesa na forma como se manipula essa informação, então caso o valor do input seja maior que 5 é pedido novamente a nota, caso fosse menor que 0 tambem. e por ultimo pede a nota de reforço, caso a soma dessas notas seja menor que 6 se considera reprovado, e entao para aprovar o aluno, o mesmo deve inserir uma nota de reforço, caso não haja necessidade, considera-se a nota de reforço igual a 0, não influenciando nas formulas das demais funções

            case 3:
                EditarAluno(alunos);
                break;
                // Esse código utiliza da função filtrar, e dentro dessa função se usa os valores (alunos) armazenados no vetor Aluno, o código se encerra.

            case 4:
                Filtrar(alunos);
                break;
// É printado a logo do projeto, o console printa o nome dos integrantes, pede o enter para prosseguir, ignore vai ignorar o buffer anterior, o cin.get vai pedir o enter e o system cls vai limpar o terminal, o código se encerra
            case 5:
            	system("cls");
                Logo();
                cout << "\nCodigo desenvolvido por Henrique Bergotti, Hugo Trindade, Eduardo Felipe, Lucas Henrique e Anderson Marquetti\n";
                cout << "Pressione ENTER para retornar.";
                cin.ignore();
                cin.get();
                break;

            case 6:
                cout << "Saindo...\n";
                break;
// O mais facil, o console printa saindo... e o codigo se encerra
            default:
                cout << "Opcao invalida.\n";
                system("pause");
                break;
        }

    } while (opcao != 6);
// caso o usuario insira uma opcao que nao é presente no menu, se printa que o codigo é invalido e retorna o menu  
    return 0;
}// no fim, sempre ira retornar a funcao principal menus
