/*******************************************************************************
 * crivo_eratostenes.c
 * Arthur Floresta Rezende - 476068
 *
 * Implementação do Crivo de Eratostenes em c, usando manipulação de bits
 * para lidar com a grande quatidade de memoria necessaria para executar-lo.
 *
 * Otimizacoes e correcoes:
 * 1) Ignorando numeros pares durante a iteracao principal e assim,
 * reduzindo o numero de iteracoes pela metade.
 * 2) Resolvido problemas com numeros impares e excecos com as entradas 0 e 1.
 *
 *
 * Exemplo de entrada: 1000000000
 * Saida esperada: 50847534
 ******************************************************************************/

//==============================================================================
// BIBLIOTECAS
//==============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//==============================================================================
// CONTANTES
//==============================================================================
unsigned short NUM_BITS;
unsigned int* is_prime;
long arr_size;

//------------------------------------------------------------------------------
// calculate_bits: calcula o tamanho do int fornecido pelo SO
//------------------------------------------------------------------------------
void calculate_bits() {
  unsigned int max_value = UINT_MAX;
  NUM_BITS = 1;
  while(max_value >>=  1) NUM_BITS++;
}

//------------------------------------------------------------------------------
// init_bit_array: inicia o vetor de bits usando inteiros
//------------------------------------------------------------------------------
int init_bit_array(long size) {
  arr_size = (size/NUM_BITS) + 1;
  is_prime = (int*) malloc(arr_size * sizeof(unsigned int));

  for(int i = 0; i < arr_size; i++) is_prime[i] = 0;
}

//------------------------------------------------------------------------------
// get_bit: retorna o valor do bit
//------------------------------------------------------------------------------
int get_bit(long pos) {
  unsigned long byte_index = pos/NUM_BITS;
  unsigned long bit_index = pos % NUM_BITS;
  unsigned long bit_mask = ( 1 << bit_index);

  return ((is_prime[byte_index] & bit_mask) == 0);
}

//------------------------------------------------------------------------------
// set_bit: seta o bit como 1
//------------------------------------------------------------------------------
void set_bit(long pos) {
  unsigned long byte_index = pos/NUM_BITS;
  unsigned long bit_index = pos % NUM_BITS;
  unsigned long bit_mask = ( 1 << bit_index);

  is_prime[byte_index] |= bit_mask;
}

//------------------------------------------------------------------------------
// solve: resolve o problema
//------------------------------------------------------------------------------
long solve(long size) {
  long answer = 1; // contando o 2

  set_bit(0);
  set_bit(1);
  set_bit(2);

  // loop ignorando numeros pares
  for(long i = 3; i <= size; i+=2) {
    if(get_bit(i)) {
      answer++;
      for(long j = i; j < size; j = j+i) set_bit(j);
    }
  }

  return answer;
}

//------------------------------------------------------------------------------
// METODO PRINCIPAL
//------------------------------------------------------------------------------
int main() {
  long n, answer;
  scanf("%ld", &n);

  if(n == 0 || n == 1) {
    answer = 0;
  }
  else {
    calculate_bits();
    init_bit_array(n);
    answer = solve(n);
  }

  printf("%ld\n", answer);

  free(is_prime);
  return 0;
}
