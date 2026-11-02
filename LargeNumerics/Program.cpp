// LargeNumerics.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include "BcdNatural.h"
#include <chrono>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    BcdNatural bn = BcdNatural(NumericString::Replicate("123456789012", 1000));
    BcdNatural rem = "0"_BcdN;
    BcdNatural bn1 = BcdNatural(NumericString::Replicate("987654321", 500));


    auto inicio = std::chrono::steady_clock::now();
    auto bn2 = bn.Divide(bn1, rem);
    auto fim = std::chrono::steady_clock::now();
    std::cout << "Divisão: " << std::chrono::duration<double>(fim - inicio).count() << " segundos\n";
    //std::cout << "Divisão: " << "A divisão de " + bn.AsString() + " \npor " + bn1.AsString() + " \né " + bn2.AsString() + " \ne resto " + rem.AsString() + "\n\n";

    inicio = std::chrono::steady_clock::now();
    auto bn6 = bn - bn1;
    fim = std::chrono::steady_clock::now();
    std::cout << "Subtração: " << std::chrono::duration<double>(fim - inicio).count() << " segundos\n";
    //std::cout << "Raiz cúbica de " + bn.AsString() + " \né " + bn3.AsString() + " \ne resto " + rem.AsString() + "\n\n";


    inicio = std::chrono::steady_clock::now();
    auto bn3 = bn.Root(3, rem);
    fim = std::chrono::steady_clock::now();
    std::cout << "Radiciação: " << std::chrono::duration<double>(fim - inicio).count() << " segundos\n";
    //std::cout << "Raiz cúbica de " + bn.AsString() + " \né " + bn3.AsString() + " \ne resto " + rem.AsString() + "\n\n";

    inicio = std::chrono::steady_clock::now();
    auto bn4 = bn >> 2;
    fim = std::chrono::steady_clock::now();
    std::cout << "ShiftRigth: " << std::chrono::duration<double>(fim - inicio).count() << " segundos\n";
    //std::cout << "ShiftRigth \né " + bn.AsString() + " \ne descartados " + bn4.AsString() + "\n\n";

    inicio = std::chrono::steady_clock::now();
    auto bn5 = bn << 2;
    fim = std::chrono::steady_clock::now();
    std::cout << "ShiftLeft: " << std::chrono::duration<double>(fim - inicio).count() << " segundos\n";
    //std::cout << "ShiftLeft \né " + bn.AsString() + " \ne descartados " + bn5.AsString() + "\n\n";

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
