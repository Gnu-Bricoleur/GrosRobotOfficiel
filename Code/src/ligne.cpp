#include "ligne.hpp"
#include <Arduino.h>

#include "constantes.hpp"
#include "branchements.hpp"


bool centre()
{
  if (analogRead(C_Centre) < BLANC && analogRead(C_Droite) > NOIR && analogRead(C_Gauche) > NOIR)
  {
    return true;
  }
  return false;
}

bool gauche()
{
  if (analogRead(C_Gauche) > NOIR && analogRead(C_Centre) < BLANC && analogRead(C_Droite) < BLANC)
  {
    return true;
  }
  return false;
}

bool droite()
{
  if (analogRead(C_Gauche) < BLANC && analogRead(C_Centre) > NOIR && analogRead(C_Droite) < BLANC)
  {
    return true;
  }
  return false;
}
