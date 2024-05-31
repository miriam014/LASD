
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main() {
  std::cout << "Lasd Libraries 2024" << std::endl;

  int scelta = - 1;
  while(scelta != 0)
  {
    std::cout << std::endl;
    std::cout << "1) Test professore" << std::endl;
    std::cout << "2) Test personale 1 esercizio" << std::endl;
    std::cout << "3) Test personale 2 esercizio" << std::endl;
    std::cout << "0) Per uscire dal programma" << std::endl;
    std::cin  >> scelta;

    if(scelta == 1)
      lasdtest();
    if(scelta == 2)
      mytest1();
    if(scelta == 3)
      mytest2();
  }


  return 0;
}
