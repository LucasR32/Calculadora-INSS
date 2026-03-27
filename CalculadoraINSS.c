#include <stdio.h>

int main()
{
    double salario = 0.0;
    double desconto_inss = 0.0;
    double desconto_vt = 0.0;

    double valor_passagem;
    int qtd_por_dia;

    // ====================== FAIXAS DO INSS 2026 ======================
    const double FAIXA1_LIMITE = 1621.00;
    const double FAIXA2_LIMITE = 2902.84;
    const double FAIXA3_LIMITE = 4354.27;
    const double TETO_INSS      = 8475.55;

    const double ALIQ1 = 0.075;
    const double ALIQ2 = 0.09;
    const double ALIQ3 = 0.12;
    const double ALIQ4 = 0.14;

    // ====================== ENTRADA DE DADOS ======================
    printf("Qual o valor do seu salário bruto?\n");
    scanf("%lf", &salario);

    while (salario <= 0.0) {
        printf("Salário não pode ser menor ou igual a 0. Digite novamente:\n");
        scanf("%lf", &salario);
    }

    // --- Vale-Transporte ---
    printf("Qual o valor de uma passagem (ida ou volta)?\n");
    scanf("%lf", &valor_passagem);

    printf("Quantas passagens você utiliza por dia para ir para o trabalho?\n");
    scanf("%d", &qtd_por_dia);

    // Cálculo do gasto mensal com transporte
    // 1 passagem por dia = ida + volta (2 passagens/dia)
    // Considera 22 dias úteis por mês (padrão empresarial)
    double passagens_por_mes = qtd_por_dia * 2.0 * 22.0;
    double gastos_transporte = valor_passagem * passagens_por_mes;

    // ====================== CÁLCULO INSS ======================
    double base = salario;

    // 1ª faixa
    if (base > FAIXA1_LIMITE) {
        desconto_inss += FAIXA1_LIMITE * ALIQ1;
        base -= FAIXA1_LIMITE;
    } else {
        desconto_inss += base * ALIQ1;
        base = 0.0;
    }

    // 2ª faixa
    if (base > 0.0) {
        double valor_faixa = (base > (FAIXA2_LIMITE - FAIXA1_LIMITE)) ? 
                             (FAIXA2_LIMITE - FAIXA1_LIMITE) : base;
        desconto_inss += valor_faixa * ALIQ2;
        base -= valor_faixa;
    }

    // 3ª faixa
    if (base > 0.0) {
        double valor_faixa = (base > (FAIXA3_LIMITE - FAIXA2_LIMITE)) ? 
                             (FAIXA3_LIMITE - FAIXA2_LIMITE) : base;
        desconto_inss += valor_faixa * ALIQ3;
        base -= valor_faixa;
    }

    // 4ª faixa (até o teto)
    if (base > 0.0) {
        double valor_faixa = (base > (TETO_INSS - FAIXA3_LIMITE)) ? 
                             (TETO_INSS - FAIXA3_LIMITE) : base;
        desconto_inss += valor_faixa * ALIQ4;
    }

    // ====================== CÁLCULO VALE-TRANSPORTE ======================
    double limite_vt = salario * 0.06;   // máximo de 6% do salário

    if (gastos_transporte > limite_vt) {
        desconto_vt = limite_vt;         // desconta no máximo 6%
    } else {
        desconto_vt = gastos_transporte; // desconta apenas o gasto real
    }

    // ====================== RESULTADO FINAL ======================
    double salario_liquido = salario - desconto_inss - desconto_vt;

    printf("\n--- Resumo de Descontos ---\n");
    printf("Salário Bruto:             R$ %.2lf\n", salario);
    printf("Desconto INSS:             R$ %.2lf\n", desconto_inss);
    printf("Gasto real com transporte: R$ %.2lf\n", gastos_transporte);
    printf("Desconto Vale-Transporte:  R$ %.2lf\n", desconto_vt);
    printf("Salário Líquido:           R$ %.2lf\n", salario_liquido);

    return 0;
}