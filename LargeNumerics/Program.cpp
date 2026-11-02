// LargeNumerics.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include "BcdNatural.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
	auto bn = "123456789012123456789012123456789012123456789012123456789012123456789012123456789012123456789012123456789012123456789012123456789012123456789012123456789012123456789012123456789012123456789012123456789012123456789012123456789012123456789012"_BcdN,
        rem = "0"_BcdN;

    auto bn1 = bn.Root(3, rem);
    std::cout << "Raiz cúbica de " + bn.ToString() + " \né " + bn1.ToString() + " \ne resto " + rem.ToString() + "\n\n";

    auto bn2 = bn.Divide(bn1, rem);
    std::cout << "A divisão de " + bn.ToString() + " \npor " + bn1.ToString() + " \né " + bn2.ToString() + " \ne resto " + rem.ToString() + "\n\n";

    std::cout << "Pressione Enter para continuar...";
    std::cin.get();

    return 0;
}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
/***********/
/*** EOF ***/
/***********/
