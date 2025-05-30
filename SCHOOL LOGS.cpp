#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

struct Aluno {
    string nome;
    string rgm;
    float A1 = 0, A2 = 0, AF = 0;
};

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
    const string senhaCorreta = "1234";

    while (true) {
        cout << "=====REALIZE O LOGIN =====\n";
        cout << "Usuario: ";
        cin >> usuario;
        cout << "Senha: ";
        cin >> senha;

        if (usuario == usuarioCorreto && senha == senhaCorreta) {
            cout << "Login realizado com sucesso!\n";
            system("pause");
            system("cls");
            break;
        } else {
            cout << "Usuario ou senha incorretos. Tente novamente.\n\n";
        }
    }
}

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
    }

    cout << left << setw(15) << "Nome"
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

        if ((opcaofiltro == 1 && (situacao == "Aprovado" || situacao == "Aprovado c/ AF")) ||
            (opcaofiltro == 2 && situacao == "Reprovado")) {
            cout << left << setw(15) << a.nome
                 << setw(10) << a.A1
                 << setw(10) << a.A2
                 << setw(10) << a.AF
                 << setw(15) << situacao << endl;
        }
    }

    cout << "\nPressione ENTER para retornar ao menu.";
    cin.ignore();
    cin.get();
    return opcaofiltro;
}

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

int main() {
    Login();

    int opcao;
    vector<Aluno> alunos;
    Aluno aluno;

    Logo();
    this_thread::sleep_for(chrono::milliseconds(3000));
    system("cls");

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

            case 3:
                EditarAluno(alunos);
                break;

            case 4:
                Filtrar(alunos);
                break;

            case 5:
                Logo();
                cout << "\nCodigo desenvolvido por Henrique Bergotti, Hugo Trindade, Eduardo Felipe e Lucas Henrique\n";
                cout << "Pressione ENTER para retornar.";
                cin.ignore();
                cin.get();
                break;

            case 6:
                cout << "Saindo...\n";
                break;

            default:
                cout << "Opcao invalida.\n";
                system("pause");
                break;
        }

    } while (opcao != 6);

    return 0;
}
