#include "ligne.hpp"
#include <Arduino.h>

#include "constantes.hpp"
#include "branchements.hpp"


bool centre()
{
  if (analogRead(C_Centre) < BLANC)
  {
    return true;
  }
  return false;
}

bool gauche()
{
  if (analogRead(C_Gauche) < BLANC)
  {
    return true;
  }
  return false;
}

bool droite()
{
  if (analogRead(C_Droite) < BLANC)
  {
    return true;
  }
  return false;
}
