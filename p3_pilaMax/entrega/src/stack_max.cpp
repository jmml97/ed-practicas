/**
  * @file stack_max.cpp
  * @brief Fichero de implementación del T.D.A. StackMax
  *
  * Permite elegir entre tres implementaciones, según la especificación escogida
  *
  */

#include "stack_max.hpp"

#if COMPILE_HEADER == 1
  #include "stack_max_list.cpp"
#elif COMPILE_HEADER == 2
  #include "stack_max_dv.cpp"
#else
  #include "stack_max_queue.cpp"
#endif

/* Fin fichero: stack_max.cpp */
